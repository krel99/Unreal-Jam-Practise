# <Feature name>

> Save as `specs/features/<FeatureName>.md`. Its tests go in
> `specs/features/<FeatureName>.spec.cpp`: same folder, same name.

**ID:** `<AREA>` (prefix for requirement IDs) · **Status:** Draft

> **Draft**: being written, don't build. **Approved**: agents may implement.

## Summary

One or two sentences: what this is and why the game needs it.

## Requirements

Each requirement is one testable statement. Use MUST / MUST NOT / SHOULD.
State inputs, outputs and edge cases. If you can't think of a test for it,
it isn't a requirement. If it's a number someone will tweak, it belongs in
*Tuning*, not here.

- **`<AREA>-001`**: <The system MUST ...>
- **`<AREA>-002`**: <...>

## Tuning

Values exposed as `UPROPERTY(EditDefaultsOnly)` for tweaking in the editor.
Not requirements, not asserted in tests, edit freely.

| Name | Starting value | What it does |
|------|----------------|--------------|
| `<MaxSpeed>` | `<600>` | <...> |

## Implementer's Discretion

Things deliberately left open. Agents may decide these without asking, and
must note what they chose.

- <e.g. internal data structures, delegate types>

## Out of Scope

Things this spec does **not** cover. Agents must not build them under this spec.

- <...>

## Open Questions

Unresolved questions, and proposed changes to approved requirements. A
question that affects a requirement blocks implementation of that requirement.

- [ ] <question> (affects `<AREA>-00X`)
- [ ] Proposed change to `<AREA>-00X`: <new text>. Why: <reason>
