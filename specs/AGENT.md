# AGENT.md — Rules for AI agents working in this repo

You are working in a **spec-driven** codebase. Specs in `/specs/features/` are
the source of truth for behaviour. Code and tests are derived from them, never
the other way round. Humans own the specs; you own turning approved specs into
tests and code, and checking that code matches its spec.

Read this file before any task that touches gameplay code, tests or specs.

---

## 1. The hard rules

These are not guidelines. If a rule blocks you, stop and say so.

1. **No behaviour without a spec.** Do not add or change gameplay behaviour
   that isn't described by a requirement in an `Approved` spec. If the task
   needs behaviour no spec covers, write or update a spec draft (see §3) and
   stop for human approval.
2. **Only build from `Approved` specs.** `Draft` and `Proposed` specs may be
   discussed and edited. They may not be implemented.
3. **Never silently edit an approved requirement.** You may propose a change
   (see §3). You may not reword, loosen, or delete an `Approved` requirement
   to fit the code you wrote.
4. **Tests come from the spec, not from the code.** Every requirement ID has
   at least one test that names that ID. Write the test from the requirement
   text, ideally before the implementation.
5. **Never change a test just to make it pass.** If a test fails, fix the
   code. Change the test only if the spec changed, or if the test misreads
   the spec. Say which one in your summary.
6. **Ambiguity is a stop signal, not a judgement call.** If a requirement can
   be read two ways, don't pick one. Add it to the spec's *Open Questions*
   and ask. Small things the spec explicitly leaves to the implementer are
   fine to decide. Note the decision in your summary.
7. **Stay in scope.** Do only what the spec and the task ask for. No drive-by
   refactors, no extra features, no speculative options.

## 2. Workflow for implementing a spec

1. Read the spec in full, including *Out of Scope* and *Open Questions*.
   Unresolved questions that affect the requirements you're about to build
   block the work.
2. For each requirement, write or update its test(s). Put the requirement ID
   in the test name (e.g. `HEALTH-002`).
3. Implement the minimum code that makes those tests pass.
4. Fill in the spec's *Traceability* table: requirement → test → code.
5. Run the tests. Report results honestly, including failures and anything
   you couldn't run (e.g. no editor available in your environment).
6. Summarise using the template in §5.

## 3. Changing or proposing specs

- New feature → copy `specs/_template.md` to
  `specs/features/<area>-<short-name>.md`, set `Status: Draft`, fill it in.
- Change to an approved spec → don't edit the requirement in place. Add an
  entry under *Proposed Changes* in that spec with the requirement ID, the
  current text, the proposed text and why. A human applies it and bumps the
  version.
- Requirement IDs are permanent. Never reuse or renumber an ID. Removed
  requirements are marked `~~REMOVED~~` with a reason, not deleted.

## 4. Reviewing code (AI review pass)

When asked to review a change, review it **against the spec**, not against
your taste. Use `specs/REVIEW.md`. In short:

- Every changed behaviour maps to a requirement ID. Flag any behaviour that
  doesn't (**unspecified behaviour**).
- Every requirement touched has a test that names its ID and would fail
  without the change. Flag gaps (**untested requirement**).
- Flag code that contradicts a requirement (**spec violation**). This
  outranks every other finding.
- Flag edits to approved spec text or to tests that aren't backed by a
  spec change (**spec drift**).
- Anything else (style, naming, performance) is secondary. Label it so.

## 5. Summary format

End implementation or review work with:

```
Spec: specs/features/<file>.md (vX, Status)
Requirements covered: HEALTH-001, HEALTH-002, ...
Tests: <added/changed test names> — <pass/fail/not run + why>
Decisions made (implementer's discretion): <list or "none">
Open questions raised: <list or "none">
Out-of-spec changes: <list or "none">
```

## 6. Project conventions (Unreal)

- Gameplay code lives under `Source/<Module>/`. Tests live in
  `Source/<Module>/Private/Tests/` as Unreal Automation Specs
  (`BEGIN_DEFINE_SPEC`), named `<Thing>.spec.cpp`.
- Test paths start with `Jam.` (e.g. `Jam.Health`) so they can be run as a
  group: `-ExecCmds="Automation RunTests Jam; Quit"`.
- Prefer logic that can be tested without a running world (plain UObjects or
  components with no world dependency). Spec requirements should say when a
  world is genuinely needed.
- Until a module exists, reference tests live in `specs/tests/`. Move them
  into the module when it's created.
