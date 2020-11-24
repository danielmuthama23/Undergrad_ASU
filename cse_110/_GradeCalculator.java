import java.util.Scanner;

public class _GradeCalculator {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.println("CSE 110 Grade Calculator");
        System.out.println("------------------------");

        System.out.print("\nYour quiz points       : ");
        double yourQuizPoints = input.nextDouble();
        System.out.print("Total quiz points      : ");
        double totalQuizPoints = input.nextDouble();
        
        System.out.print("\nYour lab points        : ");
        double yourLabPoints = input.nextDouble();
        System.out.print("Total lab points       : ");
        double totalLabPoints = input.nextDouble();
        
        System.out.print("\nYour assignment points : ");
        double yourAssignmentPoints = input.nextDouble();
        System.out.print("Total assignment points: ");
        double totalAssignmentPoints = input.nextDouble();

        System.out.print("\nYour exam points       : ");
        double yourExamPoints = input.nextDouble();
        System.out.print("Total exam points      : ");
        double totalExamPoints = input.nextDouble();

        double quizPercent = (yourQuizPoints / totalQuizPoints) * 15;
        double labPercent = (yourLabPoints / totalLabPoints) * 30;
        double assignmentPercent = (yourAssignmentPoints / totalAssignmentPoints) * 25;
        double examPercent = (yourExamPoints / totalExamPoints) * 35;

        double gradePercent = quizPercent + labPercent + assignmentPercent + examPercent;

        System.out.println("\nQuizzes (15%)     : " + quizPercent);
        System.out.println("Labs (30%)        : " + labPercent);
        System.out.println("Assignments (25%) : " + assignmentPercent);
        System.out.println("Exams (35%)       : " + examPercent);
        System.out.println("--------------------");
        System.out.println("Total (105%)      : " + gradePercent);

        input.close();
    }
}