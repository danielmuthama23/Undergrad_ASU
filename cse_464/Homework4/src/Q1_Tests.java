import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class Q1_Tests {
	@Test
	void test_1() {
		// tests independent path 1
		int[] input = {3};
		int[] expected = {3};
		Homework4.insertionSort(input);
		assertArrayEquals(input, expected);
	}
	
	@Test
	void test_2() {
		// tests independent path 2
		int[] input = {2,3,4,5,10};
		int[] expected = {2,3,4,5,10};
		Homework4.insertionSort(input);
		assertArrayEquals(input, expected);
	}
	
	@Test
	void test_3() {
		// tests independent path 3
		int[] input = {3,4,6,4,9,3};
		int[] expected = {3,3,4,4,6,9};
		Homework4.insertionSort(input);
		assertArrayEquals(input, expected);
	}
}
