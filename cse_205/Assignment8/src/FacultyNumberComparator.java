//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: class for FacultyNumberComparator used for comparing to Department's num of members

import java.util.Comparator;

public class FacultyNumberComparator implements Comparator<Department> {
    public int compare(Department first, Department second) {
        // check if num of members are the same and then compare which one is greater
        return first.getNumOfMembers() == second.getNumOfMembers() ? 0 :
            first.getNumOfMembers() > second.getNumOfMembers() ? 1 : -1;
    }
}
