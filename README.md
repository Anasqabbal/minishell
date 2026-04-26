# Minishell

![Score](https://img.shields.io/badge/score-100%2F100-success)
![C](https://img.shields.io/badge/language-C-blue)
![System](https://img.shields.io/badge/concept-OS%20Shell-success)

## 📌 Overview
**Minishell** is one of the most comprehensive projects in the 1337 (42 Network) curriculum. The goal is to recreate a simplified version of `bash`. It parses user input, handles environment variables, and executes commands exactly as a real shell would.

Building a shell from scratch is a rite of passage for systems software engineers. It requires a profound understanding of process creation, file descriptor manipulation, signal handling, and rigorous memory management.

## 💡 Core Concepts Explored
### System Calls & Process Management
**Definition:** A shell is a command-line interpreter that provides a user interface for the Unix-like operating systems. It parses user input and executes commands using underlying system calls like `fork`, `execve`, and `waitpid`.
**Problem Solved:** It abstracts the complexity of the OS kernel, allowing users and scripts to easily manage files, execute programs, and control processes without writing C programs to invoke kernel functions directly.

## 🚀 Features
- **Prompt:** Displays a custom prompt and utilizes `readline` for input and history.
- **Lexer & Parser:** Tokenizes input and correctly constructs Abstract Syntax Trees (AST) or command tables.
- **Expansions:** Expands environment variables (`$VAR`) and handles the exit status variable (`$?`).
- **Quotes Handling:** Correctly interprets single (`'`) and double (`"`) quotes.
- **Redirections:** Supports `<`, `>`, `<<` (here_doc), and `>>`.
- **Pipes:** Connects standard output of one command to the input of another (`|`).
- **Built-ins:** Implements `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signals:** Gracefully handles `ctrl-C`, `ctrl-D`, and `ctrl-\`.

## 📥 How to Clone
To clone this project, use the following command:
```bash
git clone git@github.com:Anasqabbal/minishell.git
cd minishell
```

## 🛠️ Usage
Compile the shell:
```bash
make
```
Run the generated executable:
```bash
./minishell
```

## 🧠 What I Learned
- Complex state machines and parsing logic.
- Advanced process synchronization using `fork`, `execve`, and `waitpid`.
- Comprehensive manipulation of environment variables.
- Ensuring robust stability and preventing memory leaks in an infinite loop environment.

## 🌐 Connect with me
[![GitHub](https://img.shields.io/badge/GitHub-black?logo=github)](https://github.com/Anasqabbal)
[![LinkedIn](https://img.shields.io/badge/-IN-0A66C2?logo=linkedin&logoColor=0a66c2)](https://www.linkedin.com/in/anasqabbal/)

