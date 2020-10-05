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

        double totalPercents = 105;
        // if (totalQuizPoints > 0) totalPercents += 15;
        // if (totalLabPoints > 0) totalPercents += 30;
        // if (totalAssignmentPoints > 0) totalPercents += 25;
        // if (totalExamPoints > 0) totalPercents += 35;

        double quizPercent = (yourQuizPoints / totalQuizPoints) * (15 / totalPercents) * 100;
        double labPercent = (yourLabPoints / totalLabPoints) * (30 / totalPercents) * 100;
        double assignmentPercent = (yourAssignmentPoints / totalAssignmentPoints) * (25 / totalPercents) * 100;
        double examPercent = (yourExamPoints / totalExamPoints) * (35 / totalPercents) * 100;

        double gradePercent = quizPercent + labPercent + assignmentPercent + examPercent;

        System.out.println(gradePercent);

        System.out.println("Quizzes (15%)     : " + quizPercent);
        System.out.println("Labs (30%)        : " + labPercent);
        System.out.println("Assignments (25%) : " + assignmentPercent);
        System.out.println("Exams (35%)       : " + examPercent);
        System.out.println("--------------------");
        System.out.println("Total (105%)      : " + gradePercent);

        input.close();
    }
}