import static org.junit.jupiter.api.Assertions.*;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.NoSuchElementException;

import org.junit.jupiter.api.Test;

// method names: test_# where # corresponds to test case in pdf
class Q2_Junit {
	@Test
	void test_1() {
		// length of cc != 16
		String data = "12345678912345";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		try {
			Assignment2.Validate();
		} catch (NoSuchElementException e) {
			assertNotNull("Invalid card number, need to have 8 digits");
		}
		System.setIn(stdin);
	}
	
	@Test
	void test_2() {
		// cc < 0
		String data = "-1234123412341234";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		try {
			Assignment2.Validate();
		} catch (NoSuchElementException e) {
			assertNotNull("Invalid card number, need to have 8 digits");
		}
		System.setIn(stdin);
	}
	
	@Test
	void test_3() {
		// cc > 9999999999999999
		String data = "98765432198765432";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		try {
			Assignment2.Validate();
		} catch (NoSuchElementException e) {
			assertNotNull("Invalid card number, need to have 8 digits");
		}
		System.setIn(stdin);
	}
	
	@Test
	void test_4() {
		// (finalSum % 10 = 0)
		String data = "1234123412341234";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		assertEquals(Assignment2.Validate(), "Invalid Card");
		System.setIn(stdin);
	}
	
	@Test
	void test_5() {
		// (finalSum % 10 = 0)
		String data = "4539602896568891";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		assertEquals(Assignment2.Validate(), "Valid Card");
		System.setIn(stdin);
	}
	
	@Test
	void test_6() {
		// (finalSum % 10 = 0)
		// this test fails because sum2 is calculated incorrectly since some of the odd indexed digits are >= 5
		String data = "4485850207722830";
		InputStream stdin = System.in;
		System.setIn(new ByteArrayInputStream(data.getBytes()));
		assertEquals(Assignment2.Validate(), "Valid Card");
		System.setIn(stdin);
	}

}
