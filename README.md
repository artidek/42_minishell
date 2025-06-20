# Minishell

Minishell is a group project developed as part of the 42 School curriculum. The goal of this project is to create a minimal Unix shell that replicates the core behaviors of common Linux shells. This repository showcases a collaborative effort between two students: [@artidek](https://github.com/artidek) and [@gvardovski](https://github.com/gvardovski).

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Authors](#authors)
- [License](#license)

---

## About the Project

This project is an educational exercise designed to deepen our understanding of process management, signal handling, input parsing, and the design of robust C applications. Minishell attempts to mimic the behavior of a standard shell, supporting built-in commands and handling complex user input scenarios.

## Features

- Execution of built-in shell commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
- Execution of external programs found in `$PATH`
- Support for pipes (`|`), redirections (`>`, `<`, `>>`, `<<`)
- Environment variable expansion
- Quoting and escaping rules for input parsing
- Signal handling (e.g., `SIGINT`, `SIGQUIT`)
- Custom prompt and command history
- Minimal memory leaks (valgrind clean)

## Installation

To build Minishell, clone this repository and run:

```sh
git clone https://github.com/artidek/42_minishell.git
cd 42_minishell
make
```

Requirements:
- GNU Make
- GCC (or compatible C compiler)
- GNU Readline library
- Standard Linux environment

## Usage

After building, launch the shell with:

```sh
./minishell
```

You will be greeted by a prompt. From there, you can type commands as you would in a standard shell.

### Example commands

```sh
echo "Hello, World!"
export PATH="/usr/bin"
ls -l | grep minishell
cat < infile | grep foo > outfile
```

## Project Structure

- `main.c` — Entry point of the shell
- `builtins/` — Implementation of built-in commands
- `command_processor/` — Parsing and execution of command sequences and redirections
- `expand/` — Variable and parameter expansion logic
- `includes/` — Header files and public structures
- `input_processor/` — Input handling and prompt logic
- `libft/` — Custom C library functions (as required by 42 school)
- `utils/` — Utility functions and helpers

Other files:
- `Makefile` — Build instructions
- `ms.subject.pdf` — 42 project subject specification

> **Note:** Directory listing may be incomplete. For the full list, see the [repository contents](https://github.com/artidek/42_minishell/tree/main/).

## Contributing

This project follows the 42 School collaboration policy and is developed by two students as a mandatory group assignment. Contributions outside of the original team are not accepted.

## Authors

- [@artidek](https://github.com/artidek)
- [@gvardovski](https://github.com/gvardovski)

## License

This project is intended for educational purposes and does not currently include a specific license. Please refer to the 42 School policy regarding code reuse and sharing.

---

*Project repository: [https://github.com/artidek/42_minishell](https://github.com/artidek/42_minishell)*
