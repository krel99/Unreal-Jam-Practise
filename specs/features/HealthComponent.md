# Health Component

| Field    | Value       |
|----------|-------------|
| ID       | `HEALTH`    |
| Status   | Draft       |
| Version  | 0.1         |
| Owner    | krel99      |

> Sample spec. It shows the format, and it stays `Draft` until a human
> reviews it and sets `Approved`. Agents must not implement it before then.

## Summary

A reusable `UHealthComponent` that any actor (player, enemy, destructible)
can use to take damage, heal, and die. Jam games almost always need one, and
it's easy to unit test.

## Requirements

- **`HEALTH-001`**: `MaxHealth` MUST default to `100`. A newly created
  component MUST have `CurrentHealth == MaxHealth` and `IsDead() == false`.
- **`HEALTH-002`**: `ApplyDamage(Amount)` with `Amount > 0` MUST reduce
  `CurrentHealth` by `Amount`, clamped so it never goes below `0`. It MUST
  return the damage actually applied (e.g. 30 damage at 20 health returns 20).
- **`HEALTH-003`**: `ApplyDamage(Amount)` with `Amount <= 0` MUST NOT change
  `CurrentHealth` and MUST return `0`.
- **`HEALTH-004`**: When `CurrentHealth` reaches `0`, `IsDead()` MUST return
  `true` and `OnDeath` MUST broadcast **exactly once**. Later damage MUST
  return `0` and MUST NOT broadcast `OnDeath` again.
- **`HEALTH-005`**: `Heal(Amount)` with `Amount > 0` MUST increase
  `CurrentHealth` by `Amount`, clamped to `MaxHealth`, and return the amount
  actually healed. `Heal` MUST return `0` and do nothing when the component is
  dead or `Amount <= 0`.
- **`HEALTH-006`**: The behaviour in `HEALTH-001` to `HEALTH-005` MUST work on
  a component created with `NewObject` and no owning actor or world, so it can
  be unit tested.

## Implementer's Discretion

- Whether `MaxHealth` is `EditAnywhere`, `EditDefaultsOnly`, etc.
- Whether `ApplyDamage` also hooks into `AActor::OnTakeAnyDamage` (allowed,
  as long as the requirements above still hold without an owner).
- `OnDeath` is a native multicast delegate (`DECLARE_MULTICAST_DELEGATE`). A
  Blueprint-assignable wrapper may be added on top.

## Out of Scope

- Revive / respawn.
- Damage types, resistances, armour, invulnerability frames.
- Replication / multiplayer.
- UI (health bars).

## Open Questions

- [ ] Should changing `MaxHealth` at runtime rescale `CurrentHealth` or clamp
  it? *(Doesn't block HEALTH-001 to 006; the setter is out of scope until
  answered.)*

## Proposed Changes

| Req ID | Current text | Proposed text | Reason |
|--------|--------------|---------------|--------|

## Traceability

| Req ID | Test(s) | Code |
|--------|---------|------|
| `HEALTH-001` | `Jam.Health.HEALTH-001 ...` in `HealthComponent.spec.cpp` | not implemented |
| `HEALTH-002` | `Jam.Health.HEALTH-002 ...` | not implemented |
| `HEALTH-003` | `Jam.Health.HEALTH-003 ...` | not implemented |
| `HEALTH-004` | `Jam.Health.HEALTH-004 ...` | not implemented |
| `HEALTH-005` | `Jam.Health.HEALTH-005 ...` | not implemented |
| `HEALTH-006` | Covered by every test above (all use `NewObject`, no world) | not implemented |

## Change Log

| Version | Date | Change | By |
|---------|------|--------|----|
| 0.1 | 2026-10-23 | Initial sample spec | Claude (draft for review) |
