# 🛠️ Pipex - 42 School Project

## 📋 Project Overview

**Pipex** simulates the behavior of shell pipelines by chaining multiple commands together, connecting their inputs and outputs through pipes. The goal is to reproduce how the shell executes commands with pipes and redirections, handling file descriptors and process control in C.

The **bonus** extends the project to handle **here-documents** (heredoc), allowing interactive input until a delimiter is found.

---

## 💡 What I Learned

- 🧩 **Process management** using `fork()`, `execve()`, and `waitpid()`.
- 🔄 **Pipes** (`pipe()`) for inter-process communication.
- 📂 Handling **file descriptors**:
  - Redirecting standard input/output (`dup2()`)
  - Managing file opening/closing for input/output files
- 🚨 **Error handling** and process synchronization.
- 🔍 Parsing and executing commands using environment variables (`PATH`).
- ⛔ Preventing **resource leaks** (closing unused pipe ends).
- 🎯 Implementing the **here-document**

---

## 🛠 Technical Concepts Used

- **System calls**:
  - `fork()`, `execve()`, `pipe()`, `dup2()`, `close()`, `waitpid()`
- **File descriptor management** for chaining commands
- Parsing `PATH` environment variable to find command binaries
- Managing **multiple pipes** for chaining several commands
- Handling signals and interruptions gracefully (bonus)
- Implementing **here-documents** to emulate shell heredoc feature (bonus)

---

## 🔍 Project Highlights

- Built a minimal pipeline executor supporting **two or more commands**.
- Properly redirect stdin/stdout for each command to link the pipeline.
- Robust handling of invalid commands and error messages.
- Bonus: Implemented **here-document (heredoc)** feature allowing input until a delimiter is encountered.
- Support for edge cases like empty commands, missing files, or permission errors.
