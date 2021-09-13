// CSE240 Fall 2021 HW3

// Tyler Fichiera
// State the IDE that you use: GCC

// COMMMAND: gcc -std=c99 -g hw03q1.c -o hw03q1 && ./hw03q1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#pragma warning(disable : 4996)  // compiler directive for Visual Studio only

// Read before you start:
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// You should not modify the function return types or parameters.
// You can assume that all inputs are valid. Ex: If prompted for an integer, the user will input an integer.

// Global Macro Values. They are used to define the size of 2D array of integers
#define NUM_ROWS 5
#define NUM_COLUMNS 5

#define NUM_STRINGS 5 
#define STRING_LENGTH 50

// macro to be used in Problem 4
#define square(num) num * num

// Forward Declarations
void printMatrix(int[NUM_ROWS][NUM_COLUMNS]);
void printAddScalar(int[NUM_ROWS][NUM_COLUMNS], int);
void squaredDiffMatrices(int[NUM_ROWS][NUM_COLUMNS], int[NUM_ROWS][NUM_COLUMNS]);
void rotateClockwiseMatrix(int[NUM_ROWS][NUM_COLUMNS]);
void verticalFlipMatrix(int[NUM_ROWS][NUM_COLUMNS]);
int numOfVowelsChar(char s[NUM_STRINGS * STRING_LENGTH]);
char* concatOriginalReverseStrings(char strings[NUM_STRINGS * STRING_LENGTH]);

// Problem 1: printMatrix (5 points)
// Traverse the 2D array of integers variable 'matrix' (input from main)
// and print the contents in the following format (actual contents may vary)
// 1 2 3 4 5
// 6 7 8 9 10
// 11 12 13 14 15
// 16 17 18 19 20
// 21 22 23 24 25
void printMatrix(int matrix[NUM_ROWS][NUM_COLUMNS]) {
	// two for loops: one to loop through rows, other for columns
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			printf("%i ", matrix[r][c]);
		}
		// go to new line after every row
		printf("\n");
	}
}

// Problem 2: printAddScalar (5 points)
// Traverse the 2D array of integers 'matrix', add scalar (input from main) to each element in the matrix
// and print it.
// e.g.
// int scalar = 10
// 1 2 3	    11 12 13
// 4 5 6	=>  14 15 16
// 7 8 9        17 18 19
void printAddScalar(int matrix[NUM_ROWS][NUM_COLUMNS], int scalar) {
	// two for loops: one to loop through rows, other for columns 
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			// add scalar to current int in matrix
			printf("%i ", matrix[r][c] + scalar);
		}
		// go to new line after every row
		printf("\n");
	}
}

// Problem 3: printSumDiagonal (5 points)
// Traverse the 2D array of integers 'matrix' and print the sum of the numbers in the matrix located diagonally
// from top left to bottom right position.
// e.g.
// 1 2 3		15
// 4 5 6	=>
// 7 8 9
void printSumDiagonal(int matrix[NUM_ROWS][NUM_COLUMNS]) {
    int sum = 0;
	// single for loop to interate through matrix square
	for (int i = 0; i < NUM_ROWS; i++) {
		// use same index to get the correct diagonal
		sum += matrix[i][i];
	}
	// print sum int and new line
	printf("%i\n", sum);
}


// Problem 4: squaredDiffMatrices (5 points)
// Traverse the 2D array of integers 'matrices' and print the difference of each squared value.
// Consider both matrices are of same dimensions.
// e.g.
// 1 2 3   1 2 3        0 0 0
// 4 5 6   1 2 3	=> 15 21 27
// 7 8 9   1 2 3 	   48 60 72
void squaredDiffMatrices(int matrix1[NUM_ROWS][NUM_COLUMNS], int matrix2[NUM_ROWS][NUM_COLUMNS]) {
	// two for loops: one to loop through rows, other for columns 
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			// use macro to get square of each index
			printf("%i ", square(matrix1[r][c]) - square(matrix2[r][c]));
		}
		// print new line after every row
		printf("\n");
	}
}

// Problem 5: rotateClockwiseMatrix (10 points)
// Take the 2D array of integers 'matrix' and print the matrix rotated 90 degrees clockwise.
// **Hint: Use printMatrix to print the result**
// e.g.
// 1 2 3	    7 4 1
// 4 5 6	=>  8 5 2
// 7 8 9        9 6 3
void rotateClockwiseMatrix(int matrix[NUM_ROWS][NUM_COLUMNS]) {
	// create new matrix
	int matrix2[NUM_ROWS][NUM_COLUMNS];
	// two for loops: one to loop through rows, other for columns
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			// by comparing the indexes before and after rotation,
			// I found this was the correct way to transform a matrix
			matrix2[c][NUM_COLUMNS - r - 1] = matrix[r][c];
		}
	}
	// use function from problem 1 to to re-print the matrix
	printMatrix(matrix2);
}

// Problem 6: verticalFlipMatrix (10 points)
// Take the 2D array of integers 'matrix' and print the matrix flipped vertically.
// **Hint: Use printMatrix to print the result**
// e.g.
// 1 2 3	    3 2 1
// 4 5 6	=>  6 5 4
// 7 8 9        9 8 7
void verticalFlipMatrix(int matrix[NUM_ROWS][NUM_COLUMNS]) {
	// create new matrix
	int matrix2[NUM_ROWS][NUM_COLUMNS];
	// two for loops: one to loop through rows, other for columns
	for (int r = 0; r < NUM_ROWS; r++) {
		for (int c = 0; c < NUM_COLUMNS; c++) {
			// by comparing the indexes before and after the flip,
			// I found this was the correct way to transform a matrix
			matrix2[r][NUM_COLUMNS - c - 1] = matrix[r][c];
		}
	}
	// use function from problem 1 to to re-print the matrix
	printMatrix(matrix2);
}

// Problem 7: concatOriginalReverseStrings (5 points)
// Make a new string by concatenating the original string to its reverse.
// You CANNOT use any string functions except for strlen().
// e.g.
// Hi Hello   => Hi HelloolleH iH
char* concatOriginalReverseStrings(char strings[NUM_STRINGS * STRING_LENGTH]) {
	int len = strlen(strings);
	char *new_string = (char *)malloc(2 * len + 1);

	// this loop copys the original string to new_string
	for (int i = 0; i < len; i++) {
		new_string[i] = strings[i];
	}

	// this loop reverses the original string and adds it to new_string
	for (int j = 0; j <= len; j++) {
		new_string[len + j] = strings[len - j - 1];
	}
	
	return new_string;
}

// Problem 8: numOfVowelsChar (5 points)
// Count all occurrences of vowel characters.
int numOfVowelsChar(char s[NUM_STRINGS * STRING_LENGTH]) {
    // Enter code below
	int c = 0;
	// an arr of vowels upper and lower case
	char volews[10] = "aeiouAEIOU";

	// loop through all chars in inputted string
	for (int i = 0; i < strlen(s); i++) {
		// check to see if it is in the vowel array
		for (int j = 0; j < 10; j++) {
			if (s[i] == volews[j]) {
				// add to counter if it is a vowel
				c++;
				break;
			}
		}
	}

	return c;
}

// You should study and understand how this main() works.
// *** DO NOT modify it in any way ***
int main() {
	printf("CSE240 HW3: 2D Integer Arrays\n\n");

	int matrix1[NUM_ROWS][NUM_COLUMNS] =
	{
		{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10},
		{11, 12, 13, 14, 15},
		{16, 17, 18, 19, 20},
		{21, 22, 23, 24, 25}
	};

	int matrix2[NUM_ROWS][NUM_COLUMNS] = {
	        {1, 2, 3, 4, 5},
	        {1, 2, 3, 4, 5},
	        {1, 2, 3, 4, 5},
	        {1, 2, 3, 4, 5},
	        {1, 2, 3, 4, 5}
	};

	int scalar = 10;

	printMatrix(matrix1);
	printf("\n\n");

	printAddScalar(matrix1, scalar);
	printf("\n\n");

	printSumDiagonal(matrix1);
	printf("\n\n");

	squaredDiffMatrices(matrix1, matrix2);
	printf("\n\n");

	rotateClockwiseMatrix(matrix1);
	printf("\n\n");

	verticalFlipMatrix(matrix1);

	char words[NUM_STRINGS * STRING_LENGTH];
	printf("\nEnter sentence with max 5 words: ");
	fgets(words, sizeof(words), stdin);
	words[strcspn(words, "\n")] = 0;
	// printf("%s", words);
	char* new_string = concatOriginalReverseStrings(words);
	printf("\nNew string: %s", new_string);

	printf("\nNumber of occurences of vowels: %d", numOfVowelsChar(words));
	int i = getchar();
	i = getchar(); // Keep console open
	return 0;
}
