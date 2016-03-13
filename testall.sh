#!/bin/bash

mv testdump/c.output testdump/cold.output
echo "Testing."
echo "Test 1: \n" > testdump/c.output
cat test/test1.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 2: \n" >> testdump/c.output
cat test/test2.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 3: \n" >> testdump/c.output
cat test/test3.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 4: \n" >> testdump/c.output
cat test/test4.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 5: \n" >> testdump/c.output
cat test/test5.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 6: \n" >> testdump/c.output
cat test/test6.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 7: \n" >> testdump/c.output
cat test/test7.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 8: \n" >> testdump/c.output
cat test/test8.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 9: \n" >> testdump/c.output
cat test/test9.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 10: \n" >> testdump/c.output
cat test/test10.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 11: \n" >> testdump/c.output
cat test/test11.c | bin/print_ast >> testdump/c.output
echo "\n\n Test 12: \n" >> testdump/c.output
cat test/test12.c | bin/print_ast >> testdump/c.output
echo "Testing complete, look in testdump."
