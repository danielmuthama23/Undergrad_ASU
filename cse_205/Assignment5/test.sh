find . -type f -name "*.class" -delete

javac Assignment5.java

java Assignment5 < input1.txt > myout1.txt
java Assignment5 < input2.txt > myout2.txt
java Assignment5 < input3.txt > myout3.txt
java Assignment5 < input4.txt > myout4.txt

diff myout1.txt output1.txt
diff myout2.txt output2.txt
diff myout3.txt output3.txt
diff myout4.txt output4.txt