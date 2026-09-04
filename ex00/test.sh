#!/bin/bash
# ─────────────────────────────────────────────────────────────────────────────
# test.sh – Functional tests for ex00
#
# Convention:
#   run_test "expected_output" [args_to_program...]
#   Each test prints [OK] or [KO] and records pass/fail counts.
# ─────────────────────────────────────────────────────────────────────────────

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BOLD='\033[1m'
NC='\033[0m'

BINARY="./program"    # Must match NAME in Makefile

PASS=0
FAIL=0

# ── Helpers ───────────────────────────────────────────────────────────────────

assert_eq() {
    local description="$1"
    local expected="$2"
    local actual="$3"

    if [ "$actual" = "$expected" ]; then
        echo -e "${GREEN}[OK]${NC} $description"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}[KO]${NC} $description"
        echo -e "   ${BOLD}Expected:${NC} $expected"
        echo -e "   ${BOLD}Got:     ${NC} $actual"
        FAIL=$((FAIL + 1))
    fi
}

assert_contains() {
    local description="$1"
    local needle="$2"
    local haystack="$3"

    if echo "$haystack" | grep -qF "$needle"; then
        echo -e "${GREEN}[OK]${NC} $description"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}[KO]${NC} $description"
        echo -e "   ${BOLD}Expected to contain:${NC} $needle"
        echo -e "   ${BOLD}Got:${NC} $haystack"
        FAIL=$((FAIL + 1))
    fi
}

assert_exit_code() {
    local description="$1"
    local expected_code="$2"
    local actual_code="$3"

    if [ "$actual_code" -eq "$expected_code" ]; then
        echo -e "${GREEN}[OK]${NC} $description (exit $actual_code)"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}[KO]${NC} $description"
        echo -e "   ${BOLD}Expected exit code:${NC} $expected_code"
        echo -e "   ${BOLD}Got:${NC} $actual_code"
        FAIL=$((FAIL + 1))
    fi
}

# ── Build ─────────────────────────────────────────────────────────────────────
echo -e "\n${BOLD}══════════════════════════════════════════${NC}"
echo -e "${BOLD}  Testing ex00${NC}"
echo -e "${BOLD}══════════════════════════════════════════${NC}\n"

make > /dev/null 2>&1
if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Build failed – cannot run tests.${NC}"
    exit 1
fi

# ── Tests ─────────────────────────────────────────────────────────────────────

# TODO: Replace these examples with your actual test cases

# Example 1: check output
ACTUAL=$($BINARY)
assert_eq "No args outputs Hello 42!" "Hello, 42!" "$ACTUAL"

# Example 2: check exit code
$BINARY > /dev/null 2>&1
assert_exit_code "Program exits with code 0" 0 $?

# ── Summary ───────────────────────────────────────────────────────────────────
echo ""
echo -e "${BOLD}══════════════════════════════════════════${NC}"
TOTAL=$((PASS + FAIL))
if [ "$FAIL" -eq 0 ]; then
    echo -e "${GREEN}${BOLD}  ✔ $PASS/$TOTAL tests passed${NC}"
else
    echo -e "${RED}${BOLD}  ✘ $FAIL/$TOTAL tests FAILED${NC}"
fi
echo -e "${BOLD}══════════════════════════════════════════${NC}\n"

[ "$FAIL" -eq 0 ]
