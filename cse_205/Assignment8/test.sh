javac src/Assignment8.java

java src/Assignment8 < tests/input1.txt > tests/myout1.txt
java src/Assignment8 < tests/input2.txt > tests/myout2.txt
java src/Assignment8 < tests/input3.txt > tests/myout3.txt
java src/Assignment8 < tests/input4.txt > tests/myout4.txt

diff tests/myout1.txt tests/output1.txt
diff tests/myout2.txt tests/output2.txt
diff tests/myout3.txt tests/output3.txt
diff tests/myout4.txt tests/output4.txt
