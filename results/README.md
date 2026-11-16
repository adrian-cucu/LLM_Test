# Result storage

Create one directory per model submission batch, using a stable run ID. Copy `template/run.json` to `<run-id>/run.json`. For each evaluated case, store the raw response (optional) and extracted candidate at `<run-id>/<case-id>/response.txt` and `candidate.c`. The evaluator writes reports into the run directory. Keep separate run directories for repeated samples or changed settings. Do not overwrite original dataset sources.
