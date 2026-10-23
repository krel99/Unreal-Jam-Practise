# <Feature name>

> Save as `specs/features/<FeatureName>.md`. Its tests go in
> `specs/features/<FeatureName>.spec.cpp`: same folder, same name.

| Field    | Value                                      |
|----------|--------------------------------------------|
| ID       | `<AREA>` (prefix for requirement IDs)      |
| Status   | Draft \| Proposed \| Approved \| Implemented \| Deprecated |
| Version  | 0.1                                        |
| Owner    | <human who approves changes>               |

> Status meanings: **Draft**: being written, don't build. **Proposed**: ready
> for human review. **Approved**: agents may implement. **Implemented**: all
> requirements have passing tests. **Deprecated**: kept for history only.

## Summary

One or two sentences: what this is and why the game needs it.

## Requirements

Each requirement is one testable statement. Use MUST / MUST NOT / SHOULD.
State inputs, outputs, and edge cases. If you can't think of a test for it,
it isn't a requirement yet.

- **`<AREA>-001`**: <The system MUST ...>
- **`<AREA>-002`**: <...>

## Implementer's Discretion

Things deliberately left open. Agents may decide these without asking, and
must note what they chose.

- <e.g. internal data structures, file layout>

## Out of Scope

Things this spec does **not** cover. Agents must not build them under this spec.

- <...>

## Open Questions

Unresolved questions. A question that affects a requirement blocks
implementation of that requirement.

- [ ] <question> (affects `<AREA>-00X`)

## Proposed Changes

Agent- or human-proposed edits to approved requirements, waiting for approval.

| Req ID | Current text | Proposed text | Reason |
|--------|--------------|---------------|--------|

## Traceability

Filled in during implementation.

| Req ID | Test(s) | Code |
|--------|---------|------|
| `<AREA>-001` | | |

## Change Log

| Version | Date | Change | By |
|---------|------|--------|----|
| 0.1 | YYYY-MM-DD | Initial draft | |
