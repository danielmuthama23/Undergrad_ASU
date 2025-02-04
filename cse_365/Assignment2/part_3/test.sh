#!/bin/bash

#
# credit:
# https://adamdoupe.com/teaching/classes/cse365-intro-information-assurance-s20/assignment-1/test.sh
#

set +x
set +e

echo "checking for README"
if [ ! -e "./README" ]
then
        echo "Error: No README file"
        exit 1
fi

echo "checking for Makefile"
if [ ! -e "./Makefile" ]
then
        echo "Error: No Makefile file"
        exit 1
fi

echo "Running make"
make
rc=$?
if [ $rc -ne 0 ]
then
        echo "Error when running the make command"
        exit 1
fi

if [ ! -e "./secure_house" ]
then
        echo "Error: Running make did not create the secure_house file"
        exit 1
fi

if [ ! -x "./secure_house" ]
then
        echo "Error: secure_house is not executable"
        exit 1
fi

INPUT_CASE="INSERT KEY adam key
TURN KEY adam
ENTER HOUSE adam
INSERT KEY pat foobar
TURN KEY pat
ENTER HOUSE pat
WHO'S INSIDE?
"

CORRECT_OUTPUT="KEY key INSERTED BY adam
FAILURE adam UNABLE TO TURN KEY key
ACCESS DENIED
KEY foobar INSERTED BY pat
SUCCESS pat TURNS KEY foobar
ACCESS ALLOWED
pat
"

echo "Testing your program"
OUTPUT=$( echo -n "$INPUT_CASE" | ./secure_house selina foobar key2 key3)

# echo "$OUTPUT"

DIFF=$(diff -aBw <(echo "$OUTPUT") <(echo "$CORRECT_OUTPUT"))
rc=$?
if [ $rc -ne 0 ]
then
	echo "Error: did not pass the basic test case on the website."
	echo "$DIFF"
else
	echo "SUCCESS!"
fi