# cpp-template

> **GitHub Template** for 42 School C++ modules.
> Every new module repo should be created from this template.

---

## Repository Structure

```
cpp-template/
├── .github/
│   └── workflows/
│       └── ci.yml          ← GitHub Actions CI/CD pipeline
├── .clang-format           ← Code style configuration
├── .gitignore              ← Compiled artifacts ignored by git
├── Makefile                ← Module-level build & test runner
├── README.md               ← This file (replace with module notes)
└── ex00/                   ← Example exercise scaffold
    ├── Makefile
    ├── main.cpp
    └── test.sh
```

Each module follows the pattern:
```
cppXX/
├── Makefile      ← builds & tests all exercises
├── README.md     ← theoretical notes for the module
└── exNN/
    ├── Makefile  ← 42 flags: -Wall -Wextra -Werror -std=c++98
    ├── *.hpp
    ├── *.cpp
    └── test.sh   ← functional tests (run by CI)
```

---

## CI/CD Pipeline

The CI runs automatically on every push/PR to `main` or `develop`.

| Job | What it does |
|-----|-------------|
| **Discover** | Scans for `ex*/Makefile` directories |
| **Compile** | Builds each exercise in parallel (matrix) |
| **Test** | Runs `test.sh` per exercise + Valgrind smoke test |
| **Format** | Checks `clang-format` compliance (advisory warning) |
| **Norm** | Checks forbidden keywords + strict 42 compile flags |
| **CI Gate** | Blocks merge if compile / test / norm fail |

### Status Badge
Replace `ORG/REPO` with your organization and repository name:

```markdown
![CI](https://github.com/ORG/REPO/actions/workflows/ci.yml/badge.svg)
```

---

## Local Development

```bash
# Build all exercises
make

# Run all test.sh scripts
make test

# Clean .o files
make clean

# Remove .o and binaries
make fclean

# Rebuild from scratch
make re

# List exercises discovered
make list
```

Inside a single exercise:
```bash
cd ex00
make          # compile
./test.sh     # run functional tests
make fclean   # clean up
```

---

## 42 Rules enforced by CI

| Rule | Enforcement |
|------|-------------|
| `-Wall -Wextra -Werror -std=c++98` | **Build fails** if any warning exists |
| `using namespace` forbidden | **Norm job fails** |
| `friend` keyword forbidden | **Norm job fails** |
| `printf / malloc / free` forbidden | **Norm job fails** |
| No memory leaks | Valgrind smoke test (warning) |
| Code style | `clang-format` check (advisory) |

---

## Adding a New Exercise

1. Copy `ex00/` to `ex01/`, `ex02/`, etc.
2. Edit `NAME` and `SRCS` in the new `Makefile`.
3. Write your implementation (`.cpp` / `.hpp`).
4. Add your test cases to `test.sh`.
5. Push – CI will pick up the new directory automatically.

---

## Code Style

Style is governed by `.clang-format` (Allman braces, 4-space indent, 100-col limit).

Auto-fix all files:
```bash
find . -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```
