import java.util.regex.Pattern;
import java.util.concurrent.TimeUnit;
import org.junit.*;
import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.Select;

public class calcTest {
	private WebDriver driver;
	private String baseUrl;
	private boolean acceptNextAlert = true;
	private StringBuffer verificationErrors = new StringBuffer();

	@Before
	public void setUp() throws Exception {
		System.setProperty("webdriver.chrome.driver","C:\\Users\\tfichier\\HW6\\chromedriver.exe");
		driver = new ChromeDriver();  
		baseUrl = "http://webstrar99.fulton.asu.edu/";
		driver.manage().timeouts().implicitlyWait(30, TimeUnit.SECONDS);
	}

	@Test
	public void testAdd() throws Exception {
		// test 5 + 5 = 10
		driver.get(baseUrl + "/page2/Default.aspx");
		driver.findElement(By.name("num1")).clear();
		driver.findElement(By.name("num1")).sendKeys("5");
		driver.findElement(By.name("num2")).clear();
		driver.findElement(By.name("num2")).sendKeys("5");
		WebElement ope = driver.findElement(By.id("add"));
		//Radio Button1 is selected
		ope.click();
		
		driver.findElement(By.name("calc")).click();
		
		//driver.findElement(By.name("submit")).click();
		assertEquals("10", driver.findElement(By.name("res")).getAttribute("value"));
	}
	
	@Test
	public void testSub() throws Exception {
		// test 10 - 5 = 5
		driver.get(baseUrl + "/page2/Default.aspx");
		driver.findElement(By.name("num1")).clear();
		driver.findElement(By.name("num1")).sendKeys("10");
		driver.findElement(By.name("num2")).clear();
		driver.findElement(By.name("num2")).sendKeys("5");
		WebElement ope = driver.findElement(By.id("sub"));
		//Radio Button2 is selected
		ope.click();
		
		driver.findElement(By.name("calc")).click();
		
		//driver.findElement(By.name("submit")).click();
		assertEquals("5", driver.findElement(By.name("res")).getAttribute("value"));
	}
	
	@Test
	public void testMul() throws Exception {
		// test 5 x 5 = 25
		driver.get(baseUrl + "/page2/Default.aspx");
		driver.findElement(By.name("num1")).clear();
		driver.findElement(By.name("num1")).sendKeys("5");
		driver.findElement(By.name("num2")).clear();
		driver.findElement(By.name("num2")).sendKeys("5");
		WebElement ope = driver.findElement(By.id("mul"));
		//Radio Button3 is selected
		ope.click();
		
		driver.findElement(By.name("calc")).click();
		
		//driver.findElement(By.name("submit")).click();
		assertEquals("25", driver.findElement(By.name("res")).getAttribute("value"));
	}
	
	@Test
	public void testDiv() throws Exception {
		// test 25 / 5 = 5
		driver.get(baseUrl + "/page2/Default.aspx");
		driver.findElement(By.name("num1")).clear();
		driver.findElement(By.name("num1")).sendKeys("25");
		driver.findElement(By.name("num2")).clear();
		driver.findElement(By.name("num2")).sendKeys("5");
		WebElement ope = driver.findElement(By.id("div"));
		//Radio Button4 is selected
		ope.click();
		
		driver.findElement(By.name("calc")).click();
		
		//driver.findElement(By.name("submit")).click();
		assertEquals("5", driver.findElement(By.name("res")).getAttribute("value"));
	}
}