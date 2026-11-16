# C Refactoring Study

A reproducible benchmark for comparing how language models refactor small C programs, especially code resembling embedded and systems work. Each case has a stable ID, a compilable original program, a manifest entry describing its intended quality concerns, and a place to archive model outputs and evaluation reports.

## Scope

The initial corpus contains 14 self-contained C11 programs, including four larger firmware-style examples with multiple interacting functions: a telemetry frame decoder, a thermal controller, a UART command dispatcher, and a bounded event queue. They are synthetic benchmark fixtures, not copied from production firmware. Cases cover naming and readability, duplicated logic, magic numbers, protocol parsing, state machines, unsafe string handling, resource cleanup, integer conversion, global state, control flow, and input validation. Some cases intentionally embody behavioral or safety defects. Treat all source files as untrusted test inputs and run them only in an isolated environment.

This project does not call LLM APIs or include an automated evaluation script. Researchers submit the same prompt manually, then compile and analyze saved candidates with the documented tools. SonarQube analysis is run through its normal project scanner/server workflow.

## Quick start

Requirements: a C11 compiler (`gcc` or `clang`), and optionally `cppcheck`, `clang-tidy`, and a configured SonarQube scanner/server.

Compile an original case from the project root, for example:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
  dataset/cases/CR-001/original.c -o /tmp/CR-001
```

Add a model response under `results/<run-id>/<case-id>/candidate.c`. Copy `results/template/run.json` to the run directory and fill it in before evaluation. Compile a candidate with the same flags as its original, then optionally run:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
  results/run-001/CR-001/candidate.c -o /tmp/CR-001-candidate
cppcheck --enable=warning,style,performance,portability --std=c11 \
  results/run-001/CR-001/candidate.c
clang-tidy results/run-001/CR-001/candidate.c -- -std=c11 -Wall -Wextra -Wpedantic
```

Record compiler diagnostics and analyzer output alongside the candidate (for example, in `results/<run-id>/<case-id>/`). Compile each case separately. Do not execute the generated programs unless the case is run in an isolated working directory; CR-005 intentionally contains an unsafe original, and CR-006 creates a file.

## Dataset format

`dataset/manifest.json` is the authoritative case index. Each entry records its ID, source path, language standard, topic tags, intent, expected observable behavior, and evaluation notes. Case IDs are permanent identifiers; do not recycle them. Preserve originals when preparing outputs. Candidate files must be complete standalone C translation units with a `main` function, matching the case's public behavior unless the refactoring explicitly documents a behavior change.

To add a case:

1. Add a unique `CR-###` directory under `dataset/cases/` with `original.c`.
2. Add its metadata to `dataset/manifest.json` and keep paths relative to the project root.
3. Record expected behavior and known limitations so correctness can be reviewed independently of static-analysis scores.

## Manual model protocol

Use `prompts/refactor.md` verbatim for every model and case. Submit one case at a time, include only the original source and fixed prompt, and save the model's complete code response unchanged as `candidate.c`. Record the provider, displayed model/version, date, interface, settings visible to the operator, and any response truncation in `run.json`. Do not repair, format, or otherwise edit a candidate before its first evaluation. If a model gives prose around its code, extract the code into `candidate.c` and preserve the full raw response as `response.txt`.

For fair comparisons, freeze the corpus revision, prompt revision, tool versions, compiler flags, and analyzer configuration before collecting outputs. Randomized model settings should be recorded; where the interface allows it, use deterministic settings. Repeat runs should have separate run IDs.

## Evaluation and interpretation

Record compiler and analyzer versions, exact commands, exit codes, and diagnostics for every candidate. Static-analysis findings are signals for human review, not correctness proof. Different tool versions and configurations can change findings.

SonarQube: `sonar-project.properties.example` documents the project key, source path and C-family plugin property placeholders. Configure a SonarQube server and a compatible C/C++ analyzer/plugin separately, scan one candidate tree at a time, and archive the scanner output and server/plugin versions with the run. SonarQube's C analysis availability and licensing depend on the installed edition/plugin. Avoid combining findings from different server/plugin versions as if directly comparable.

Compare candidates on at least: compilability, behavioral preservation (review or case-specific tests), analyzer findings by severity/rule, and human-reviewed readability/maintainability. Do not interpret fewer warnings as automatically better code.

## Layout

```text
dataset/       originals and manifest
prompts/       fixed submission prompt
results/       run metadata template and candidate-output location
```

## License and research ethics

The corpus is original synthetic material provided under the MIT License. Record provenance for any future third-party code and verify its license before inclusion. Cite this repository revision and tool versions in reports. Never place credentials, private prompts, or personally identifiable information in results.
