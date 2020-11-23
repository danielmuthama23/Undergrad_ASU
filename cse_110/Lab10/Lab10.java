/*
AUTHOR: Tyler Fichiera
FILENAME: Lab10.java
SPECIFICATION: Source for Lab 10
FOR: CSE 110 Lab #10
TIME SPENT: 20 mins
*/

package Lab10;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Lab10 {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        /* Create an array of Student */
        final int NUM_STUDENTS = 10;

        // init array for students
        Student[] gradebook = new Student[NUM_STUDENTS];

        try {
            // create filereader for the correct txt file
            FileReader fr = new FileReader("lab10_student_data.txt");
            // create buffer reader from the contents of lab10_student_data.txt
            BufferedReader inFile = new BufferedReader(fr);

            for (int i = 0; i < NUM_STUDENTS; i++) {
                // read line one at a time
                String line = inFile.readLine();
                // parse fullname
                String fullName = line.substring(0, line.indexOf(","));
                // parse id
                String id = line.substring(fullName.length() + 1, line.lastIndexOf(","));
                // parse grade and convert to double
                double grade = Double.parseDouble(line.substring(line.lastIndexOf(",") + 1));
                // create student
                Student student = new Student(fullName, id, grade);
                // add to arrat
                gradebook[i] = student;
                // print out using toString method
                System.out.printf("Read %d: %s\n", i + 1, student);
            }

            inFile.close(); // close file
        } catch (IOException ex) {
            System.out.println(ex);
        }

        // print new line for formatting
        System.out.println();

        /* Find out duplicate student records by .equals() */
        for (int i = 0; i < NUM_STUDENTS; i++) {
            for (int j = i + 1; j < NUM_STUDENTS; j++) {
                // compare the two objects using the custom equals method
                if (gradebook[i].equals(gradebook[j])) {
                    // print out info for mathing objects
                    System.out.printf(
                      "\"%s\" and \"%s\": %s\n",
                      gradebook[i].getFullName(),
                      gradebook[j].getFullName(),
                      gradebook[i].getId()
                    );
                }
            }
        }
    }
}
