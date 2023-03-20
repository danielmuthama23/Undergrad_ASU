import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

class ParamterizedTests {

	@ParameterizedTest
	@CsvSource({
		"'',''", // empty string
		"a,a",
		"aabb,aabb",
		"acbadc,aabccd"
	})
	void test(String input, String expected) {
		assertEquals(expected, Homework4.sortStr(input));
	}
}
