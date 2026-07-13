# MiniGit Lightweight

> A lightweight Git-inspired version control system built in **C++17** for learning the core concepts of version control.

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

MiniGit Lightweight is a simplified implementation of a Git-like version control system. It demonstrates how repositories, commits, object storage, and checkout operations work internally while intentionally keeping the command set minimal and easy to understand.

---

## Features

- Initialize a repository
- Stage files for commit
- View repository status
- Create commits
- Browse commit history
- Checkout previous commits
- SHA-1 based object storage
- Lightweight command-line interface

---

## Supported Commands

```bash
mini-git init

mini-git add <file>

mini-git status

mini-git commit -m "Commit message"

mini-git log

mini-git checkout <commit_hash>
```

---

## Getting Started

### Prerequisites

- C++17 compatible compiler
- OpenSSL library

### Build

```bash
g++ -std=c++17 *.cpp -o mini-git -lssl -lcrypto
```

### Example Workflow

```bash
# Initialize repository
./mini-git init

# Create a file
echo "Hello MiniGit" > hello.txt

# Stage file
./mini-git add hello.txt

# View repository status
./mini-git status

# Commit changes
./mini-git commit -m "Initial Commit"

# View commit history
./mini-git log

# Checkout a previous commit
./mini-git checkout <commit_hash>
```

---

## Repository Structure

```
.mini-git/
├── objects/        # Blob, tree and commit objects
├── refs/           # Repository references
├── HEAD            # Current repository state
├── index           # Staging area
└── config          # Author information
```

---

## Core Concepts Demonstrated

- Content-addressed storage using SHA-1
- Repository initialization
- File staging
- Commit creation
- Commit history traversal
- Checkout of previous repository states
- File snapshot management

---

## Design Decisions

This project intentionally focuses on the essential version control workflow.

The following advanced Git operations were removed to keep the implementation lightweight and educational:

- Branch creation
- Branch merging
- Commit diff

This makes the codebase easier to understand while still demonstrating the core principles behind modern version control systems.

---

## Technologies Used

- C++17
- STL
- `<filesystem>`
- OpenSSL (SHA-1)
- File I/O

---

## Future Improvements

- Improved error handling
- Colored terminal output
- Automated unit tests
- CMake build support
- Performance optimizations

---

Built to understand how Git works internally by implementing its core concepts from scratch.