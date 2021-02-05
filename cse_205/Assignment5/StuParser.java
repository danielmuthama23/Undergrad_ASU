// Assignment #: 5
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: Helper class for parsing student info from
//               a string

public class StuParser {
    /** static method for parising student info from a given string */
    public static Student parseStringToStudent(String lineToParse) {
        String[] split = lineToParse.split("/"); // split string into array

        Student student;

        if (split[0].toLowerCase().equals("undergrad")) {
            // parse string from this format:
            // type/firstName/lastName/studentID/credits/rate/inState/programFee
            student = new UnderGrad(
                split[1],
                split[2],
                split[3],
                Integer.parseInt(split[4]),
                Double.parseDouble(split[5]),
                split[6].toLowerCase().equals("instate"),
                Double.parseDouble(split[7])
            );
        } else {
            // parse string from this format:
            // type/firstName/lastName/studentID/credits/rate/gradFee
            student = new Graduate(
                split[1],
                split[2],
                split[3],
                Integer.parseInt(split[4]),
                Double.parseDouble(split[5]),
                Double.parseDouble(split[6])
            );
        }

        return student;
    }
}