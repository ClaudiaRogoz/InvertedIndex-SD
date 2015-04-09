#!/bin/bash

NO_TESTS=9
EXEC=tema3
TEST_POINTS=10
TIMEOUT_TIME=(0 1 1 1 1 6 15 7 15 2)
TOTAL=0

timeout_test()
{
	test_no=$1
	# Get the input and ref files for the current test
	timeout=${TIMEOUT_TIME[$test_no]}
    input_path="tests/in/test"$test_no".in"
    ref_path="tests/out/test"$test_no".out"
	
	(time timeout $timeout ./$EXEC <$input_path >out.txt) 2>time.err
	TEST_RESULT=$?
}

valgrind_test()
{
	test_no=$1
	# Get the input and ref files for the current test
	timeout=${TIMEOUT_TIME[$test_no]}
    input_path="tests/in/test"$test_no".in"
    ref_path="tests/out/test"$test_no".out"
	
	valgrind --leak-check=full --error-exitcode=1 -q ./$EXEC <$input_path >out.txt 2>time.err
	TEST_RESULT=$?
}


# Check a single test and add the result to the total score. This function
# should _always_ receive a test number as the first and only argument
check_test()
{
    test_no=$1
	
    echo
    echo -n "Test: $test_no ...................... "
	
	if [ "$test_no" == "9" ]; then
		valgrind_test $test_no
	else
		timeout_test $test_no
	fi
	
    # Run the test, also consider the timeout
    if [ "$TEST_RESULT" == "124" ]; then
        echo "TIMEOUT [$timeout s]"
        rm -f out.txt
        rm -f time.err
		return
    elif [ "$test_no" == "9" -a "$TEST_RESULT" != "0" ]; then
		echo "DETECTED MEMORY LEAKS"
		tail -n 10 time.err
        rm -f out.txt
        rm -f time.err
		return
	fi
	
    # Check the result
    diff -bB -i $ref_path out.txt 2>&1 1> my_diff
    if test $? -eq 0; then
        echo "PASS"
		if [ -f time.err  ]; then
			cat time.err 
		fi
        TOTAL=$(expr $TOTAL + $TEST_POINTS)
    else
        echo "FAILED"
        echo "Diff result:"
        cat time.err
        cat my_diff | tail -n 10
    fi

    # Clean up
    rm -f my_diff
    rm -f out.txt
    rm -f time.err
}


# Check if the the exec exist
if test ! -x $EXEC; then
    echo "File Missing"
    exit 1
fi


if [[ $1 =~ [0-9] ]]; then
	check_test $1
else 
	for ((i=1;i<=$NO_TESTS;i++))
	do
		check_test $i
	done
fi	


# And the restul is ...
echo "TOTAL: $TOTAL/$(expr $TEST_POINTS \* $NO_TESTS)"

