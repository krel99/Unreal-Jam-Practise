# AGENT.md — Rules for AI agents working in this repo

You are working in a **spec-driven** codebase. Specs in `/specs/features/` are
the source of truth for gameplay rules. Code and tests are derived from them,
never the other way round. The human owns the specs; you own turning approved
specs into tests and code, and checking that code matches its spec.

Read this file before any task that touches gameplay code, tests or specs.
To create or change a spec, use the `/spec` skill.

---

## 1. The hard rules

These are not guidelines. If a rule blocks you, stop and say so.

1. **No gameplay rule without a spec.** Do not add or change anything listed
   under "needs a spec" in §2 unless an `Approved` spec describes it. If the
   task needs a rule no spec covers, draft one with `/spec` and stop for
   approval.
2. **Only build from `Approved` specs.** `Draft` specs may be discussed and
   edited. They may not be implemented.
3. **Never silently edit an approved requirement.** Propose the change under
   the spec's *Open Questions* (see §4). You may not reword, loosen, or delete
   an `Approved` requirement to fit the code you wrote.
4. **Tests come from the spec, not from the code.** Every requirement ID has
   at least one test that names that ID. Write the test from the requirement
   text, ideally before the implementation.
5. **A spec and its test are a pair: same folder, same name.**
   `specs/features/HealthComponent.md` is tested by
   `specs/features/HealthComponent.spec.cpp`, and nowhere else. Never put a
   spec's tests in another folder or split them across files.
6. **Never change a test just to make it pass.** If a test fails, fix the
   code. Change the test only if the spec changed, or if the test misreads
   the spec. Say which one in your summary.
7. **Ambiguity is a stop signal, not a judgement call.** If a requirement can
   be read two ways, don't pick one. Add it to the spec's *Open Questions*
   and ask. Things the spec lists under *Implementer's Discretion* are yours
   to decide. Note the decision in your summary.
8. **Stay in scope.** Do only what the spec and the task ask for. No extra
   features, no speculative options. Refactoring that the change needs
   (`AGENTS.md`: refactor first, then change behaviour) is in scope. Do it as
   a separate step that changes no behaviour and keeps tests green.
   Refactoring code the change doesn't touch is not in scope.

## 2. What needs a spec, and what doesn't

**Needs a spec**: rules the game must get right, and that could silently
break:
- state and its transitions (alive/dead, round start/end, pickup collected)
- rules and their edge cases (damage, scoring, win/lose, spawning, cooldowns)
- relationships between values ("damage never takes health below 0",
  "score doubles while combo is active")

**Does not need a spec**: just do it, keep it out of spec'd logic:
- **Tuning values**: speeds, damage numbers, timings, ranges, curves, spawn
  rates, colours. Expose them as `UPROPERTY(EditDefaultsOnly)` with a sensible
  default and list them under the spec's *Tuning* section. Their exact values
  are never requirements and are never asserted in tests.
- **Feel and juice**: camera shake, hit-stop, particles, sounds, animation.
- **Content**: levels, meshes, materials, UI layout, audio assets.
- **Tooling**: debug commands, editor scripts.

If you're unsure whether something is a rule or a tuning value, ask: "If this
changed, would a test need to change?" If no, it's tuning.

## 3. Workflow for implementing a spec

1. Read the spec in full, including *Out of Scope* and *Open Questions*.
   Unresolved questions that affect the requirements you're about to build
   block the work.
2. For each requirement, write or update its test(s) in the spec's sibling
   `<FeatureName>.spec.cpp`. Put the requirement ID in the test name
   (e.g. `HEALTH-002`). Read tuning values from the object under test; never
   hard-code them.
3. Implement the minimum code that makes those tests pass.
4. Build and run the tests. Report results honestly, including failures and
   anything you couldn't run.
5. Summarise using the template in §6.

## 4. Changing specs

- New feature → use `/spec`. It writes `specs/features/<FeatureName>.md`
  (PascalCase, matching the main class without its `U`/`A` prefix, e.g.
  `HealthComponent`) with `Status: Draft`. Its test file will be
  `specs/features/<FeatureName>.spec.cpp`.
- Change to an approved requirement → don't edit it in place. Add an Open
  Question: `Proposed change to HEALTH-00X: <new text>. Why: <reason>`. The
  human approves it in chat or by editing the spec. Only then apply it.
- Requirement IDs are permanent. Never reuse or renumber an ID. Removed
  requirements are marked `~~REMOVED~~` with a reason, not deleted.
- Tuning values and *Implementer's Discretion* entries can be edited freely.

## 5. Reviewing code (AI review pass)

When asked to review a change, review it **against the spec**, not against
your taste. Use `specs/REVIEW.md`. In short:

- Flag code that contradicts a requirement (**spec violation**). This
  outranks every other finding.
- Flag edits to approved spec text or to tests that the human didn't approve
  (**spec drift**).
- Flag new gameplay rules that map to no requirement ID (**unspecified
  behaviour**). Tuning, feel and content are not findings.
- Flag requirements touched by the change that lack a test naming their ID
  (**untested requirement**).
- Anything else (style, naming, performance) is secondary. Label it so.

## 6. Summary format

End implementation or review work with:

```
Spec: specs/features/<file>.md (Status)
Requirements covered: HEALTH-001, HEALTH-002, ...
Tests: <added/changed test names> — <pass/fail/not run + why>
Decisions made (implementer's discretion): <list or "none">
Open questions raised: <list or "none">
Out-of-spec changes: <list or "none">
```

## 7. Project conventions (Unreal)

- Gameplay code lives under `Source/<Module>/`. Tests do **not**; they live
  next to their spec in `specs/features/` as Unreal Automation Specs
  (`BEGIN_DEFINE_SPEC`). The `.spec.cpp` suffix is Unreal's name for that
  test format.
- Test paths start with `Jam.` (e.g. `Jam.Health`) so they can be run as a
  group: `-ExecCmds="Automation RunTests Jam; Quit"`.
- **C++ for behaviour, Blueprints for content.** Anything a spec requirement
  describes is written in C++, so it can be tested and reviewed as text.
  Blueprints subclass those C++ classes and only pick meshes, sounds, VFX,
  UI layout and tuning values. Spec'd logic never goes in a Blueprint graph.
- Blueprints are binary `.uasset` files made in the Unreal Editor. If you
  can't run the editor, report an issue.
- Prefer logic that can be tested without a running world (plain UObjects or
  components with no world dependency). Spec requirements should say when a
  world is genuinely needed.
- Unreal only compiles files inside a module, so the game project must pull
  `specs/features/*.spec.cpp` into its build (e.g. an editor-only test
  module that adds `specs/features/` as a source directory). Set this up
  when the project is created. Never "fix" the build by moving tests out of
  `specs/`.
