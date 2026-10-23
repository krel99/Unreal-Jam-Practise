# /specs

Spec-driven development for this project, kept small on purpose.

**Specs define the rules. Tests prove the spec. Code satisfies the tests.**
The human approves specs; AI agents draft them, implement them and review
against them. Tuning, feel and content are not specced (see
[`AGENT.md`](AGENT.md) §2).

```
idea ──► /spec (interview → draft → critic) ──► Draft ──► human approves ──► tests (by req ID) ──► code ──► AI review vs spec
                         ▲                                                                                    │
                         └───────────────────────────── Open Questions ◄─────────────────────────────────────┘
```

## Files

| File | Purpose |
|------|---------|
| [`AGENT.md`](AGENT.md) | Rules every AI agent must follow. Read this first. |
| [`GAME.md`](GAME.md) | One-page game brief: theme, core loop, list of systems. Fill in on day 1. |
| [`REVIEW.md`](REVIEW.md) | How changes are reviewed against specs (human + AI). |
| [`_template.md`](_template.md) | The spec format. `/spec` uses it. |
| [`features/`](features/) | One spec per feature, `<FeatureName>.md`, with its test right next to it as `<FeatureName>.spec.cpp`. |

The `/spec` skill lives in `.claude/skills/spec/`, and its critic agent in
`.claude/agents/spec-critic.md`.

## Quick start

1. Fill in `GAME.md`.
2. `/spec enemies chase the player and explode on contact`. It asks up to 4
   questions, drafts `features/<Name>.md`, has a separate agent critique
   it, and reports back. Add `--fast` to skip the questions and take its
   defaults.
3. Answer its open questions, then reply "approved" (or
   `/spec approve <Name>`).
4. *"Implement specs/features/<Name>.md"*. The agent writes tests named by
   requirement ID in `<Name>.spec.cpp`, then the code.
5. *"Review this change against its spec"*. It reports violations, drift,
   unspecified behaviour and untested requirements.
6. To change an approved spec: `/spec <Name>: <change>`.

## Example

```
features/
  HealthComponent.md         the spec (plain-English requirements + tuning)
  HealthComponent.spec.cpp   its test (C++, one block per requirement ID)
```
