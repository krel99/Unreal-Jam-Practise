# /specs

Spec-driven development for this project, kept small on purpose.

**Specs define behaviour. Tests prove the spec. Code satisfies the tests.**
Humans approve specs; AI agents implement and review against them.

```
idea ──► spec (Draft) ──► human review ──► Approved ──► tests (by req ID) ──► code ──► AI review vs spec
                ▲                                                                          │
                └──────────── Proposed Changes / Open Questions ◄──────────────────────────┘
```

## Files

| File | Purpose |
|------|---------|
| [`AGENT.md`](AGENT.md) | Rules every AI agent must follow. Read this first. |
| [`REVIEW.md`](REVIEW.md) | How changes are reviewed against specs (human + AI). |
| [`_template.md`](_template.md) | Copy this to start a new spec. |
| [`features/`](features/) | One spec per feature, `<FeatureName>.md`, with its test right next to it as `<FeatureName>.spec.cpp`. |

## Quick start

1. Copy `_template.md` to `features/<FeatureName>.md`, write requirements with
   IDs like `HEALTH-001`.
2. Review it yourself (checklist in `REVIEW.md`), resolve open questions, set
   `Status: Approved`.
3. Ask an agent: *"Implement specs/features/HealthComponent.md"*. It will
   write tests named by requirement ID in `HealthComponent.spec.cpp`, then
   code, then fill in the traceability table.
4. Ask an agent: *"Review this change against its spec"*. It reports
   violations, drift, unspecified behaviour and untested requirements.

## Example

```
features/
  HealthComponent.md         the spec (plain-English requirements)
  HealthComponent.spec.cpp   its test (C++, one block per requirement ID)
```
