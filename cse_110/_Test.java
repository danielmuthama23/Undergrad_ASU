public class _Test {
    public static void main(String[] args) {
        int num1 = 0;
        int num2 = 3;
        while ((num2 != 0) && (num1 / num2) >= 0) {
            num1 += 2;
            num2--;
        }
        System.out.println(num1 + " " + num2);

        int i = 1;
        int num = 1;
        while (i <= 3) {
            for (int j = 1; j <= i; j++) {
                System.out.print(num + " ");
                num *= 2;
            }
            i++;
        }
    }
}