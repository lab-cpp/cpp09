#!/bin/bash
# ─────────────────────────────────────────────────────────────────────────────
# test.sh – Functional tests for ex00
# ─────────────────────────────────────────────────────────────────────────────

GREEN='\033[0;32m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m'

BINARY="./btc"

PASS=0
FAIL=0

assert_eq() {
    local description="$1"
    local expected="$2"
    local actual="$3"

    if [ "$actual" = "$expected" ]; then
        echo -e "${GREEN}[OK]${NC} $description"
        PASS=$((PASS + 1))
    else
        echo -e "${RED}[KO]${NC} $description"
        echo -e "   ${BOLD}Expected:${NC}\n$expected"
        echo -e "   ${BOLD}Got:     ${NC}\n$actual"
        FAIL=$((FAIL + 1))
    fi
}

echo -e "\n${BOLD}══════════════════════════════════════════${NC}"
echo -e "${BOLD}  Testing ex00${NC}"
echo -e "${BOLD}══════════════════════════════════════════${NC}\n"

make > /dev/null 2>&1
if [ ! -f "$BINARY" ]; then
    echo -e "${RED}Build failed – cannot run tests.${NC}"
    exit 1
fi

EXPECTED_OUTPUT="2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number."

ACTUAL=$($BINARY input.txt 2>&1)

assert_eq "BTC matches exact output from the subject examples" "$EXPECTED_OUTPUT" "$ACTUAL"

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
