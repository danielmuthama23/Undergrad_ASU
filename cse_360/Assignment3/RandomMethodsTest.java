/*****
 * Name: Tyler Fichiera
 * CSE 360 Spring 2022
 * Assignment 3: JUnit Tests
 *****/
import static org.junit.Assert.*;

import org.junit.Test;

public class RandomMethodsTest {
    /* Test daysInMonth method */
    @Test
    public void testJanuary() {
        assertEquals("January 1974 has 31 days", RandomMethods.daysInMonth(1, 1974));
    }

    @Test
    public void testFebruaryLeap() {
        assertEquals("February 2004 has 29 days", RandomMethods.daysInMonth(2, 2004));
    }

    @Test
    public void testFebruaryNotLeap() {
        assertEquals("February 2005 has 28 days", RandomMethods.daysInMonth(2, 2005));
    }

    @Test
    public void testMarch() {
        assertEquals("March 1974 has 31 days", RandomMethods.daysInMonth(3, 1974));
    }

    @Test
    public void testApril() {
        assertEquals("April 1974 has 30 days", RandomMethods.daysInMonth(4, 1974));
    }

    @Test
    public void testMay() {
        assertEquals("May 1974 has 31 days", RandomMethods.daysInMonth(5, 1974));
    }

    @Test
    public void testJune() {
        assertEquals("June 1974 has 30 days", RandomMethods.daysInMonth(6, 1974));
    }

    @Test
    public void testJuly() {
        assertEquals("July 1974 has 31 days", RandomMethods.daysInMonth(7, 1974));
    }

    @Test
    public void testAugust() {
        assertEquals("August 1974 has 31 days", RandomMethods.daysInMonth(8, 1974));
    }

    @Test
    public void testSeptember() {
        assertEquals("September 1974 has 30 days", RandomMethods.daysInMonth(9, 1974));
    }

    @Test
    public void testOctober() {
        assertEquals("October 1974 has 31 days", RandomMethods.daysInMonth(10, 1974));
    }

    @Test
    public void testNovember() {
        assertEquals("November 1974 has 30 days", RandomMethods.daysInMonth(11, 1974));
    }

    @Test
    public void testDecember() {
        assertEquals("December 1974 has 31 days", RandomMethods.daysInMonth(12, 1974));
    }

    @Test
    public void testUnknownMonth() {
        assertEquals("Unknown month number", RandomMethods.daysInMonth(13, 2001));
    }

    /* Test smallestNumber method with the smallest being in each of the three params */
    @Test
    public void testSmallestNumber1() {
        assertEquals(12, RandomMethods.smallestNumber(12, 100, 256), 1);
    }
    
    @Test
    public void testSmallestNumber2() {
        assertEquals(12, RandomMethods.smallestNumber(100, 12, 256), 1);
    }

    @Test
    public void testSmallestNumber3() {
        assertEquals(12, RandomMethods.smallestNumber(256, 100, 12), 1);
    }

    /* Test numberOfConsonants method */
    @Test
    public void testNumberOfConsonantsGiven() {
        assertEquals(24, RandomMethods.numberOfConsonants("The quick brown fox jumps over the lazy dog."));
    }

    @Test
    public void testNumberOfConsonantsAlphabet() {
        // should be 21 since 26 - 5 vowels = 25 consonants
        // included random punctuation and capital letters
        assertEquals(21, RandomMethods.numberOfConsonants("abcdefgh!ijkl.MnopqrS1TuvWxyz."));
    }

    @Test
    public void testNumberOfConsonantsNone() {
        assertEquals(0, RandomMethods.numberOfConsonants("aeiou"));
    }

    /* Test isPangram method */
    @Test
    public void testIsPangramTrue() {
        assertTrue(RandomMethods.isPangram("The quick brown fox jumps over the lazy dog."));
    }

    @Test
    public void testIsPangramFalse() {
        assertFalse(RandomMethods.isPangram("CSE360 is fun!"));
    }
}
