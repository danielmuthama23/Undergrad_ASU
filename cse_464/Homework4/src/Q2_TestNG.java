import static org.junit.jupiter.api.Assertions.assertEquals;

import org.testng.annotations.Test;

public class Q2_TestNG {
	@Test
	void test_1() {
		// tests independent path 1
		String input = "";
		String expected = "";
		String result = Homework4.sortStr(input);
		assertEquals(result, expected);
	}
	
	@Test
	void test_2() {
		// tests independent path 2
		String input = "a";
		String expected = "a";
		String result = Homework4.sortStr(input);
		assertEquals(result, expected);
	}
	
	@Test
	void test_3() {
		// tests independent path 3
		String input = "aabb";
		String expected = "aabb";
		String result = Homework4.sortStr(input);
		assertEquals(result, expected);
	}
	
	@Test
	void test_4() {
		// tests independent path 4
		String input = "acbadc";
		String expected = "aabccd";
		String result = Homework4.sortStr(input);
		assertEquals(result, expected);
	}
}
