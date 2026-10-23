# REVIEW.md — Reviewing changes against specs

The point of spec-driven review: **humans review intent, agents review
conformance.** A human decides *what* the game should do by approving a spec.
After that, most of the line-by-line checking ("does this code do what the
spec says?") can be done by an agent. Humans then spend their review time on
the spec and on the findings below, not on every diff.

## Who reviews what

| Change type                         | Human review | AI review |
|-------------------------------------|--------------|-----------|
| New spec / spec status → Approved   | **Required** | `/spec` runs a critic pass |
| Change to an approved requirement   | **Required** | Optional |
| Code + tests implementing a spec    | Skim findings | **Required** |
| Test changed without spec change    | **Required** | **Required** (flag it) |
| Tuning, feel, content               | Play it      | None |

## AI review checklist

Run each check and report findings in this order of severity:

1. **Spec violation**: code does something an approved requirement forbids,
   or fails to do something it requires.
2. **Spec drift**: approved requirement text, or a test's expectation, was
   changed without the human approving it.
3. **Unspecified behaviour**: a new or changed gameplay rule (see
   `AGENT.md` §2) that maps to no requirement ID. Either it needs a spec or
   it should be removed. Tuning values, feel and content are not findings.
4. **Untested requirement**: a requirement touched by the change has no test
   naming its ID, the test wouldn't fail if the behaviour broke, the test
   hard-codes a tuning value, or the test isn't in the spec's sibling
   `<FeatureName>.spec.cpp`.
5. **Secondary** (non-blocking): style, naming, performance, readability.
   Label clearly as non-blocking.

Each finding cites the requirement ID and the file/line. "Looks fine" is not a
finding. If there's nothing in categories 1–4, say so explicitly.

## Human review checklist (for specs)

- Is every requirement testable? Could two people write the same test from it?
- Are edge cases (zero, negative, max, repeated calls, ordering) stated?
- Are tweakable numbers in *Tuning*, not in requirements?
- Is *Out of Scope* explicit enough to stop scope creep?
- Are the *Open Questions* that block implementation resolved?
- Then set `Status: Approved` (or tell the agent "approved").
