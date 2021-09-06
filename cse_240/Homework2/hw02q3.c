#include <stdio.h>
#pragma warning(disable : 4996) // needed in VS
 
// CSE 240 Fall 2021 Homework 2 Question 3 (25 points)
// Note: You may notice some warnings when you compile in GCC or VS, that is okay.
 
#define isNegative(x) ((x < 0) ? x : 0)
 
#define squaredAverageMacro(a, b) ((a * a + b * b) / 2)
 
int squaredAverageFunc(a, b) {
    return (a * a + b * b) / 2;
}
 
// Part 1:
// We want to pass the value of -1 to isNegative and expect the result of isNegative to be -1, why is the result 0? Correct the error (5 points)
void part1(int x) {
 
    int result;
    result = isNegative(x);
 
    printf("isNegative(-1) = %d \n\n", result);
 
    // Why did this error occur? Please provide the answer in your own words below.
    printf("Explanation: I removed the x++ incrementer because we want the true value of x as it is defined in the main method (as -1). If we increment it then becomes 0 which is not what we want to pass in.\n\n\n"); // (2.5 points)
}
 
 
// Part 2:
// We want to pass decremented value of x and incremented value of y to the macro and function to compare their outputs in VS and GCC.
// Run this program in Visual Studio(VS) and then again in GCC. Fill the blanks below with the output values for squaredAverageFunc and squaredAverageMacro.
// Then correct/edit this function so that polyFun and polyMacro produce same correct output of 20.         // (5 points)
// 
void part2(int x, int y) {                      // increment before passing to macro
    int x_copy = x, y_copy = y;
    
    //printf("%i\n", --x);
    //printf("%i\n", ++y);
    //printf("%i\n", --x_copy);
    //printf("%i\n", ++y_copy);
 
    // do the incrementing/decrementing outside of the macro call so that the inputs (x_copy and y_copy) are the correct values (0 and 4).
    x_copy++;
    y_copy--;
 
    // printf("%i\n", x_copy);
    // printf("%i\n", y_copy);
 
    printf("squaredAverageFunc(x, y) = %d \nsquaredAverageMacro(x, y) = %d \n\n", squaredAverageFunc(--x, ++y), squaredAverageMacro(x, y));
 
 
    // Replace the 4 blank spaces below with the actual output observed when running the code in VS and GCC.
    // The blanks should have the answers of unedited program. Keep the answers in blanks as they were, after editing the program.
    printf("In VS : the result of squaredAverageFunc = 20 and squaredAverageMacro = 29 \n");            // (5 points)
    printf("In GCC: the result of squaredAverageFunc = 20 and squaredAverageMacro = 29 \n\n");      // (5 points)
 
    // Explain in a short sentence why VS and GCC could possibly produce a different value for the same program and for the same input.
    printf("Explanation: I got the same output (20 & 29) using both methods. I ran it using Visual Studio on the computer at the computer lab and by using SSH into the general server and the command `gcc -g hw02q3.c -o hw02q3.`\n\n"); //  (2.5 points)
}
 
// Do not edit main()  
int main()
{
    int x = -1, y = 5;
 
    printf("Part 1:\n\n");
    part1(x);
    printf("Part 2:\n\n");
    part2(x, y);
 
    while (1);  // needed to keep console open in VS
    return 0;
}