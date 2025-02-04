// Tyler Fichiera

#include <stdio.h>

// CSE 240 Spring 2021 Homework 1 Question 3 (20 points)
// Before starting this assignment, please compile and run this program. 
// You will first notice that the program will not compile. Fix the errors and define the error types.
// Next, you will notice that the program is printing incorrect information. Fix the errors and define those error types.

int main() {

	// Problem 1: (4 points)
	// The statement below should cause the program to not compile. Correct the error(s). (2 points).

	float p = 20.18;

	// use formatter %.2f to show two decimals
	printf("p is equal to %.2f\n", p);

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Contextual \n\n");

	// Problem 2: (4 points)
	// Half of 50 is 25, why is the program printing that half of 50 is 0? Correct the error(s) (2 points).

	// change to int instead of double
	int q = 50;

	printf("Half of %i is %d\n", q, q / 2);

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");

	// Problem 3 (2 points)
	// Integer variable y is initialized to 100 and its value needs to be printed. Correct the error(s).(1 point)
	int y = 100;
	printf("y is %i\n", y);
 
    // Your answer should be either Syntactic, Semantic, or Contextual. (1 point)
	printf("Error Type: Semantic \n\n");
     
    // Give your explanation here:
    printf("The c formatter is for chars so I switched it to i because var y is an int. Semantically incorrect because it compiles but gives wrong result.\n\n");
	
	// Problem 4: (2 points)
	// Float variable f has been initialized to 3.14, why does the program seem to think otherwise? Correct the error(s) (2 points).
	float f = 3.14;

	if (f == 10)
		printf("f is equal to 10.\n");
	if (f > 10)
		printf("f is greater than 10.\n");
	if (f < 10)
		printf("f is less than 10.\n");

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");

	// Problem 5: (4 points)
	// Surely, 60 is an even number. Why is the program printing that 60 is an odd number? Correct the error(s) ( points).

	q = 60;

	if (q % 2 == 0)
		printf("%d is an even number.\n", q);
	if (q % 2 == 1)
		printf("%d is an odd number.\n", q);

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");

	// Problem 6: (4 points)
	// This bit of code is meant to print "Hello World!". Correct the error(s) (2 points).

	printf("Hello %s\n", "World!");

	// Define what type of error this is, your answer should replace the space next to "Error Type: " below (2 points).
	// Your answer should be either Syntactic, Semantic, or Contextual.
	printf("Error Type: Semantic \n\n");

	return 0;
}
