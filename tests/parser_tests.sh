#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

valid_passed=0
invalid_passed=0
undefined_pretty_passed=0
undefined_ugly_passed=0
undefined_rest_passed=0

valid_total=0
invalid_total=0
undefined_pretty_total=0
undefined_ugly_total=0
undefined_rest_total=0

echo "======================"
echo "     PARSER TESTS"
echo "======================"

test_valid()
{
    test="$1"
    ((valid_total++))

    ./computor "$test"
    ret=$?

    if [ $ret -eq 0 ]; then
        printf "${GREEN}%s OK${NC}\n\n" "$test"
        ((valid_passed++))
    else
        printf "${RED}%s KO${NC}\n\n" "$test"
    fi
}

test_invalid()
{
    test="$1"
    ((invalid_total++))

    ./computor "$test"
    ret=$?

    if [ $ret -ne 0 ]; then
        printf "${GREEN}%s OK${NC}\n\n" "$test"
        ((invalid_passed++))
    else
        printf "${RED}%s KO${NC}\n\n" "$test"
    fi
}

test_undefined_pretty()
{
    test="$1"
    ((undefined_pretty_total++))

    ./computor "$test"
    ret=$?

    if [ $ret -eq 0 ]; then
        printf "${GREEN}%s${NC}\n\n" "$test"
        ((undefined_pretty_passed++))
    else
        printf "${RED}%s${NC}\n\n" "$test"
    fi
}

test_undefined_ugly()
{
    test="$1"
    ((undefined_ugly_total++))

    ./computor "$test"
    ret=$?

    if [ $ret -eq 0 ]; then
        printf "${GREEN}%s${NC}\n\n" "$test"
        ((undefined_ugly_passed++))
    else
        printf "${RED}%s${NC}\n\n" "$test"
    fi
}

test_undefined_rest()
{
    test="$1"
    ((undefined_rest_total++))

    ./computor "$test"
    ret=$?

    if [ $ret -eq 0 ]; then
        printf "${GREEN}%s${NC}\n\n" "$test"
        ((undefined_rest_passed++))
    else
        printf "${RED}%s${NC}\n\n" "$test"
    fi
}


echo
echo "---- GOOD TESTS ----"

# Basic valid equations.
test_valid "0 * X^0 = 1 * X^0"
test_valid "1 * X^1 = 1 * X^1"
test_valid "1 * X^2 = 2 * X^2"
test_valid "1 * X^3 = 2 * X^2"

# Decimal coefficients should be accepted.
test_valid "1.2 * X^2 = 2 * X^2"

# Different polynomial degrees should be accepted by the parser.
test_valid "1 * X^4 = 2 * X^2"

# Multiple terms on both sides.
test_valid "2 * X^2 + 3 * X^1 = 5 * X^2"
test_valid "2 * X^2 - 3 * X^1 = 5 * X^2"
test_valid "2 * X^2 + 3 * X^1 - 4 * X^0 = 5 * X^2"

# Repeated powers should still be valid syntax.
test_valid "2 * X^2 + 3 * X^1 - 4 * X^0 + 1 * X^2 - 2 * X^1 = 5 * X^2"

# Zero on either side.
test_valid "0 * X^0 = 0 * X^0"


echo
echo "---- BAD TESTS ----"

# Invalid variable / coefficient.
test_invalid "0 * X^a = 1 * X^0"
test_invalid "a * X^0 = 1 * X^0"

# More than one '='.
test_invalid "0 * X^0 = 1 * X^0 ="
test_invalid "0 * X^0 = 1 * X^0 = 2 * X^0"
test_invalid "0 * X^0 = = 1 * X^0"
test_invalid "1 * X^0 == 1 * X^0"
test_invalid "1 * X^0 = 1 * X^0 ="

# Empty or incomplete equations.
test_invalid ""
test_invalid "="
test_invalid "0 * X^0"
test_invalid "0 * X^0 ="
test_invalid "= 1 * X^0"

# Missing required pieces.
test_invalid "* X^0 = 1 * X^0"
test_invalid "1 * ^0 = 1 * X^0"
test_invalid "1 * X^ = 1 * X^0"
test_invalid "1 * X 0 + 1 * X^0 = 1 * X^0"

# Missing operators / duplicated operators.
test_invalid "* X^0 + 1 * X^0 = 1 * X^0"
test_invalid "1 *  ^0 + 1 * X^0 = 1 * X^0"
test_invalid "1 * X^0 + + 1 * X^0 = 1 * X^0"
test_invalid "1 * X^0 - - 1 * X^0 = 1 * X^0"
test_invalid "1 * X^0 + - 1 * X^0 = 1 * X^0"
test_invalid "1 * * X^0 + 1 * X^0 = 1 * X^0"

# Completely malformed input.
test_invalid "hello"
test_invalid "X"
test_invalid "X^1"
test_invalid "3 * X^1"
test_invalid "1 * 2 = 3"


echo
echo "---- UNDEFINED / PRETTY ----"

# These are not necessarily written in the canonical format,
# but are reasonable inputs for a parser to accept.

# Compact equations without the usual '*' and '^0' notation.
test_undefined_pretty "0 = 1X"
test_undefined_pretty "0 = X"
test_undefined_pretty "0 = 1 + X"
test_undefined_pretty "0 = 1 + X^1"

# Negative exponents may be considered valid polynomial syntax
# by some parsers, even though they are outside the usual subject.
test_undefined_pretty "0 * X^-1 = 1 * X^0"


echo
echo "---- UNDEFINED / UGLY ----"

# These inputs are close enough to valid syntax that a permissive
# parser might accept them, but rejecting them is also reasonable.

# Missing spaces around operators.
test_undefined_ugly "0* X^0 = 1 * X^0"
test_undefined_ugly "0 *X^0 = 1 * X^0"
test_undefined_ugly "0*X^0 = 1 * X^0"
test_undefined_ugly "0 * X^0= 1 * X^0"
test_undefined_ugly "0 * X^0 =1 * X^0"
test_undefined_ugly "0 * X^0=1 * X^0"
test_undefined_ugly "0*X^0=  1 * X^0"

# Spaces inside a term.
test_undefined_ugly "0 * X ^0 = 1 *  X^0"
test_undefined_ugly "0 * X^ 0 = 1 *  X^0"
test_undefined_ugly "0 * X ^ 0 = 1 *  X^0"

# Multiple spaces between tokens.
test_undefined_ugly "0  * X^0 = 1 * X^0"
test_undefined_ugly "0 *  X^0 = 1 * X^0"
test_undefined_ugly "0 * X^0  = 1 * X^0"
test_undefined_ugly "0 * X^0 =  1 * X^0"
test_undefined_ugly "0 * X^0 = 1  * X^0"
test_undefined_ugly "0 * X^0 = 1 *  X^0"

# Leading unary operators.
test_undefined_ugly "+ 1 * X^0 = 1 * X^0"

# Implicit multiplication.
test_undefined_ugly "1 X^0 = 1 * X^0"
test_undefined_ugly "1X^0 = 1 * X^0"

# Missing exponent / variable parts.
test_undefined_ugly "1 * X = 1 * X^1"
test_undefined_ugly "1 = 1 * X^0"


echo
echo "---- UNDEFINED / REST ----"

# Extremely large exponents / coefficients.
# These mainly test integer overflow, conversion limits,
# and implementation-defined numeric boundaries.

# Decimal and large exponents are useful boundary cases.
test_undefined_rest "1 * X^4.2 = 2 * X^2"
test_undefined_rest "1 * X^42 = 2 * X^2"
test_undefined_rest "1 * X^1023 = 2 * X^2"

test_undefined_rest "1 * X^4200 = 2 * X^2"
test_undefined_rest "1 * X^2147483648 = 2 * X^2"
test_undefined_rest "1 * X^21474836480 = 2 * X^2"

test_undefined_rest "2147483647 * X^0 = 2 * X^1"
test_undefined_rest "-2147483648 * X^0 = 2 * X^1"
test_undefined_rest "2147483648 * X^0 = 1 * X^1"
test_undefined_rest "-2147483649 * X^0 = 1 * X^1"
test_undefined_rest "21474836470 * X^0 = 1 * X^1"
test_undefined_rest "-21474836480 * X^0 = 1 * X^1"

# Very small decimal coefficients.
test_undefined_rest "-2147483648 * X^0 = 0.000001 * X^1"
test_undefined_rest "1 * X^0 = 0.000000000001 * X^1"

# Unary operators in the middle of an expression.
# Whether these are accepted depends on the grammar.
test_undefined_rest "1 * X^0 + +1 * X^0 = 1 * X^0"
test_undefined_rest "1 * X^0 - -1 * X^0 = 1 * X^0"
test_undefined_rest "1 * X^0 + -1 * X^0 = 1 * X^0"
test_undefined_rest "1 * X^0 - +1 * X^0 = 1 * X^0"


echo
echo "======================"
echo "         REPORT"
echo "======================"
printf "Valid:             %d/%d passed\n" "$valid_passed" "$valid_total"
printf "Invalid:           %d/%d passed\n" "$invalid_passed" "$invalid_total"
printf "Undefined pretty:  %d/%d passed\n" "$undefined_pretty_passed" "$undefined_pretty_total"
printf "Undefined ugly:    %d/%d passed\n" "$undefined_ugly_passed" "$undefined_ugly_total"
printf "Undefined rest:    %d/%d passed\n" "$undefined_rest_passed" "$undefined_rest_total"
