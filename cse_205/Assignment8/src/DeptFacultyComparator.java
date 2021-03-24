//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: 

import java.util.Comparator;

public class DeptFacultyComparator implements Comparator<Department> {
	//First we compare the currentFaculty's last name, if they are same, we then compare
	//their first names. The departments should be listed in the alphabetical order of the
	//currentFaculty's last and first names
	public int compare(Department first, Department second) {
		return first.getFaculty().getLastName().equals(second.getFaculty().getLastName())
			? first.getFaculty().getFirstName().compareTo(second.getFaculty().getFirstName())
			: first.getFaculty().getLastName().compareTo(second.getFaculty().getLastName());
	}
}
