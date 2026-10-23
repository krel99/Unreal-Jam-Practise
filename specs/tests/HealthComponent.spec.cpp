// Spec: specs/features/health-component.md (v0.1)
//
// Reference test written from the spec, before any implementation exists.
// Move to Source/<Module>/Private/Tests/ once the game module is created.
// Every Describe() names the requirement ID it proves. HEALTH-006 is covered
// implicitly: every test uses a bare NewObject with no owner or world.

#include "Misc/AutomationTest.h"
#include "HealthComponent.h"

BEGIN_DEFINE_SPEC(FHealthComponentSpec, "Jam.Health",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UHealthComponent* Health = nullptr;
	int32 DeathCount = 0;
END_DEFINE_SPEC(FHealthComponentSpec)

void FHealthComponentSpec::Define()
{
	BeforeEach([this]()
	{
		Health = NewObject<UHealthComponent>();
		DeathCount = 0;
		Health->OnDeath.AddLambda([this]() { ++DeathCount; });
	});

	Describe("HEALTH-001 initial state", [this]()
	{
		It("defaults MaxHealth to 100 and starts full and alive", [this]()
		{
			TestEqual("MaxHealth", Health->GetMaxHealth(), 100.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), Health->GetMaxHealth());
			TestFalse("IsDead", Health->IsDead());
		});
	});

	Describe("HEALTH-002 positive damage", [this]()
	{
		It("reduces health by the amount and returns it", [this]()
		{
			TestEqual("Returned", Health->ApplyDamage(30.f), 30.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 70.f);
		});

		It("clamps at zero and returns only the damage actually applied", [this]()
		{
			Health->ApplyDamage(80.f);
			TestEqual("Returned", Health->ApplyDamage(30.f), 20.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 0.f);
		});
	});

	Describe("HEALTH-003 non-positive damage", [this]()
	{
		It("ignores zero and negative damage", [this]()
		{
			TestEqual("Zero returns 0", Health->ApplyDamage(0.f), 0.f);
			TestEqual("Negative returns 0", Health->ApplyDamage(-10.f), 0.f);
			TestEqual("CurrentHealth unchanged", Health->GetCurrentHealth(), 100.f);
		});
	});

	Describe("HEALTH-004 death", [this]()
	{
		It("is dead and broadcasts OnDeath once when health reaches zero", [this]()
		{
			Health->ApplyDamage(100.f);
			TestTrue("IsDead", Health->IsDead());
			TestEqual("OnDeath count", DeathCount, 1);
		});

		It("ignores further damage and does not broadcast again", [this]()
		{
			Health->ApplyDamage(100.f);
			TestEqual("Returned", Health->ApplyDamage(10.f), 0.f);
			TestEqual("OnDeath count", DeathCount, 1);
		});
	});

	Describe("HEALTH-005 healing", [this]()
	{
		It("heals by the amount and clamps to MaxHealth", [this]()
		{
			Health->ApplyDamage(50.f);
			TestEqual("Partial heal", Health->Heal(20.f), 20.f);
			TestEqual("Clamped heal", Health->Heal(50.f), 30.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 100.f);
		});

		It("does nothing for non-positive amounts", [this]()
		{
			Health->ApplyDamage(50.f);
			TestEqual("Zero", Health->Heal(0.f), 0.f);
			TestEqual("Negative", Health->Heal(-5.f), 0.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 50.f);
		});

		It("does nothing when dead", [this]()
		{
			Health->ApplyDamage(100.f);
			TestEqual("Returned", Health->Heal(50.f), 0.f);
			TestEqual("CurrentHealth", Health->GetCurrentHealth(), 0.f);
			TestTrue("Still dead", Health->IsDead());
		});
	});
}
