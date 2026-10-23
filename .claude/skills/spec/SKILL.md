---
name: spec
description: Draft a new gameplay spec, or change an existing one, in specs/features/. Interviews the user briefly, writes the spec from the template, gets an independent critique from the spec-critic agent, revises, and hands it back as Draft for approval. Use when the user describes a new mechanic, system or rule ("enemies should...", "add a dash", "I want scoring"), asks to spec something, or asks to change an approved requirement.
argument-hint: "<idea> [--fast]  |  <FeatureName>: <change>  |  approve <FeatureName>"
---

# /spec: fast spec drafting

Goal: turn a rough idea into an approvable spec in minutes, so the human
spends their time deciding, not writing. You draft and deliberate. The human
approves. You never implement anything here: no tests, no code.

Input: `$ARGUMENTS`

## 0. Load context (always, silently)

Read these before anything else:
- `specs/AGENT.md`: especially §2, what needs a spec and what doesn't
- `specs/_template.md`: the exact format to produce
- `specs/GAME.md`: theme, core loop, and which systems exist
- the file list of `specs/features/`, and any spec the idea touches

Then pick the mode:
- `approve <FeatureName>` → go to §6.
- `<FeatureName>: <change>` where that spec exists → go to §5.
- anything else → a new spec, continue with §1.

## 1. Triage: does this need a spec at all?

Apply `specs/AGENT.md` §2. Decide before drafting:

- **Pure tuning, feel or content** (a speed, a shake, a sound, a level
  layout) → don't write a spec. Say so in one line, and name the
  `UPROPERTY` or asset it belongs to. Stop.
- **Mixed** → spec only the rules. Every number someone will tweak goes in
  *Tuning*, never in a requirement.
- **Overlaps an existing spec** → propose extending that spec (§5) instead of
  a new one.
- **Too big** (more than ~8 requirements, or two systems that could ship
  separately) → propose a split into named specs, ask which to draft first,
  then draft only that one.

## 2. Interview: one round, only what changes behaviour

Skip this step if `--fast` was passed, or the idea already answers it.

List what you'd have to guess to write testable requirements. Drop anything
that's tuning, feel, or that you can safely default. Ask **at most 4**
questions in a **single** AskUserQuestion call:
- Each question is a behaviour fork with a different test for each branch
  ("When the player dies: restart level / lose a life / game over?").
- Put your recommended option first, marked "(Recommended)", picked for a
  4-day jam: the simplest option that is still fun.
- Never ask about numbers. Pick a starting value and put it in *Tuning*.

Everything you didn't ask about becomes an explicit assumption: an
*Implementer's Discretion* entry, an *Out of Scope* entry, or a stated
default inside a requirement.

## 3. Draft

Write `specs/features/<FeatureName>.md` from the template, with
`Status: Draft`. `<FeatureName>` is PascalCase and matches the main class
without its `U`/`A` prefix. The ID prefix is short, upper case and not used
by any other spec.

Requirement rules:
- One testable statement each, MUST / MUST NOT / SHOULD. Name the function,
  property or event it's about.
- Cover edge cases: zero, negative, max, repeated calls, ordering, calls
  after the thing is "done" (dead, collected, round over).
- Prefer rules testable without a world. If one genuinely needs a world,
  say so in the requirement.
- No exact tuning values. "Clamped to MaxHealth", not "clamped to 100".
- *Out of Scope* lists the obvious next features someone would assume come
  with it. That list is the main guard against scope creep.

Do not write the `.spec.cpp` test file. Tests are written after approval.

## 4. Critique, then revise

Launch the `spec-critic` agent. Give it **only** the spec's path and the
paths in §0, not your reasoning or the interview answers, so its read is
independent of yours. It returns numbered findings.

For each finding:
- Clear fix (ambiguous wording, missing edge case, a number in a
  requirement) → apply it.
- Needs the human to decide (a behaviour fork) → add it under
  *Open Questions*, phrased so it can be answered in one word.
- Wrong or not worth it → drop it, and say why in one clause in your report.

Run a second critique only if the first one led to new or reworded
requirements. Never run more than two.

## 5. Changing an existing spec

- **Draft spec** → edit it directly, then run §4 on it.
- **Approved spec** → don't touch requirement text. Show the human the exact
  change (current text → new text, plus any new IDs) and ask them to confirm.
  On "yes", apply it. That confirmation is their approval. Without it, add the
  proposal under *Open Questions* instead.
- New requirements take the next unused number. Never renumber. Removed ones
  become `~~REMOVED~~` with a reason.
- Tuning, *Implementer's Discretion* and *Out of Scope* entries can be
  edited directly.

## 6. Approve

Only when the human explicitly says to approve (`/spec approve <Name>`, or
"approved" in reply to your report):
- If any Open Question blocks a requirement, list them and stop.
- Otherwise set `Status: Approved` and tell them it's ready to implement.

Never set `Approved` on your own judgement.

## 7. Report back

Keep it short. Findings live in the spec file, not in chat.

```
Drafted specs/features/<Name>.md (Draft): <N> requirements, <ID>-001..00N
Assumed: <one line per default you chose that the human might disagree with>
Open questions: <list, or "none — ready to approve">
Critic: <N> findings applied, <M> moved to open questions, <K> dropped (why)
Next: answer the open questions, or reply "approved".
```
