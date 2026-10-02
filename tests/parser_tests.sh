#! /bin/bash

echo "running parser tests"
echo "running good tests"
./computor "0 * X^0 = 1 * X^0"

echo "running bad tests"
./computor "0 * X^0 = 1 * X^0 ="

echo "running undefined tests"
# multiple spaces at various locations
# extra + sign at the beginning
# missing ^1
# missing X^0
# missing number