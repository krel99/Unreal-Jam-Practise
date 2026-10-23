// Spec: HealthComponent.md (same folder)
//
// Written from the spec, before any implementation exists.
// Every Describe() names the requirement ID it proves. HEALTH-006 is covered
// implicitly: every test uses a bare NewObject with no owner or world.
// MaxHealth is a tuning value, so tests read it instead of assuming 100.

#include "Misc/AutomationTest.h"
#include "HealthComponent.h"

BEGIN_DEFINE_SPEC(FHealthComponentSpec, "Jam.Health",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UHealthComponent* Health = nullptr;
	float Max = 0.f;
	int32 DeathCount = 0;
END_DEFINE_SPEC(FHealthComponentSpec)

void FHealthComponentSpec::Define()
{
	BeforeEach([this]()
	{
		Health = NewObject<UHealthComponent>();
		Max = Health->GetMaxHealth();
		DeathCount = 0;
		Health->OnDeath.AddLambda([this]() { ++DeathCount; });
	});

	Describe("HEALTH-001 initial state", [this]()
	{
		It("starts at MaxHealth and alive", [this]()
		{
			TestTrue("MaxHealth is positive", Max > 0.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), Max);
			TestFalse("IsDead", Health->IsDead());
		});
	});

	Describe("HEALTH-002 positive damage", [this]()
	{
		It("reduces health by the amount and returns it", [this]()
		{
			TestEqual("Returned", Health->ApplyDamage(Max * 0.25f), Max * 0.25f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), Max * 0.75f);
		});

		It("clamps at zero and returns only the damage actually applied", [this]()
		{
			Health->ApplyDamage(Max * 0.75f);
			TestEqual("Returned", Health->ApplyDamage(Max * 0.5f), Max * 0.25f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 0.f);
		});
	});

	Describe("HEALTH-003 non-positive damage", [this]()
	{
		It("ignores zero and negative damage", [this]()
		{
			TestEqual("Zero returns 0", Health->ApplyDamage(0.f), 0.f);
			TestEqual("Negative returns 0", Health->ApplyDamage(-10.f), 0.f);
			TestEqual("CurrentHealth unchanged", Health->GetCurrentHealth(), Max);
		});
	});

	Describe("HEALTH-004 death", [this]()
	{
		It("is dead and broadcasts OnDeath once when health reaches zero", [this]()
		{
			Health->ApplyDamage(Max);
			TestTrue("IsDead", Health->IsDead());
			TestEqual("OnDeath count", DeathCount, 1);
		});

		It("ignores further damage and does not broadcast again", [this]()
		{
			Health->ApplyDamage(Max);
			TestEqual("Returned", Health->ApplyDamage(Max * 0.1f), 0.f);
			TestEqual("OnDeath count", DeathCount, 1);
		});
	});

	Describe("HEALTH-005 healing", [this]()
	{
		It("heals by the amount and clamps to MaxHealth", [this]()
		{
			Health->ApplyDamage(Max * 0.5f);
			TestEqual("Partial heal", Health->Heal(Max * 0.25f), Max * 0.25f);
			TestEqual("Clamped heal", Health->Heal(Max), Max * 0.25f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), Max);
		});

		It("does nothing for non-positive amounts", [this]()
		{
			Health->ApplyDamage(Max * 0.5f);
			TestEqual("Zero", Health->Heal(0.f), 0.f);
			TestEqual("Negative", Health->Heal(-5.f), 0.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), Max * 0.5f);
		});

		It("does nothing when dead", [this]()
		{
			Health->ApplyDamage(Max);
			TestEqual("Returned", Health->Heal(Max), 0.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 0.f);
			TestTrue("Still dead", Health->IsDead());
		});
	});
}
