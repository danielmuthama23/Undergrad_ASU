//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: 

import java.util.Comparator;

public class DeptNameComparator implements Comparator<Department> {
    public int compare(Department first, Department second) {
        // System.out.println(first.getDeptName() + " " + second.getDeptName());
        // System.out.println(first.getDeptName().compareTo(second.getDeptName()));
        return first.getDeptName().compareTo(second.getDeptName());
    }
}
