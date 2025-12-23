# ENSEA Shell (enseash)

## Project Overview

**enseash** is a custom Unix-like shell developed as a hands-on project to understand core operating system concepts such as process creation (`fork`), command execution (`execvp`), pipes, input/output redirection, background processes, signal handling, and timing measurements.

The shell progressively implements features across multiple exercises (ex1.c to ex9.c), building a fully functional mini-shell that supports:

- Basic command execution
- Built-in `exit` command
- Exit status and signal display in the prompt
- Execution time measurement (in milliseconds)
- Argument parsing
- Input/output redirection (`<`, `>`)
- Pipes (`|`)
- Background processes (`&`) with job control and completion notification

The final version is in **ex9.c**, which integrates all previous features.

## Features

- **Welcome message** on startup
- Custom prompt: `enseash % ` (initial) → `enseash [exit:X|YYYms] % ` or `enseash [sign:Z|YYYms] % ` (after commands)
- Supports `exit` to quit gracefully with "Bye bye..."
- Displays command exit status (`exit:X`) or terminating signal (`sign:Z`)
- Measures and displays command execution time in milliseconds
- Handles pipes (`cmd1 | cmd2`)
- Supports input/output redirection (`< file`, `> file`)
- Runs commands in background with `&`, assigns job IDs, and notifies on completion with elapsed time
- Supports up to 32 concurrent background jobs
- Robust error handling (command not found, fork failures, etc.)

## How to Compile and Run

The project includes a **Makefile** for easy compilation.

### Build
```bash
make