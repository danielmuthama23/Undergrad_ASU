//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: 

import java.io.Serializable;

public class Department implements Serializable {
	// private instance variables
	private String deptName, university;
	private int numOfMembers;
	private Faculty currentFaculty;

	// constructor
	public Department(
		String deptName,
		String university,
		int numOfMembers,		
		String firstName,
		String lastName,
		String academicLevel
	) {
		this.deptName = deptName;
		this.university = university;
		this.numOfMembers = numOfMembers;
		currentFaculty = new Faculty(firstName, lastName, academicLevel);
	}

	public String getDeptName() {
		return deptName;
	}

	// return university
	public String getUniversity() {
		return university;
	}

	public int getNumOfMembers() {
		return numOfMembers;
	}

	public Faculty getFaculty() {
		return currentFaculty;
	}

	public void setDeptName(String a) {
		deptName = a;
	}

	public void setNumOfMembers(int a) {
		numOfMembers = a;
	}

	public void setUniversity(String a) {
		university = a;
	}

	public void setFaculty(String firstName, String lastName, String academicLevel) {
		currentFaculty.setFirstName(firstName);
		currentFaculty.setLastName(lastName);
		currentFaculty.setAcademicLevel(academicLevel);
	}

	// return a string in a specified format
	public String toString() {
		return "\nDept. Name:\t\t" + deptName + "\n"
				+ "University:\t\t" + university + "\n"
				+ "# of Members:\t" + numOfMembers + "\n"
				+ "Faculty:\t\t" + currentFaculty.toString() + "\n";
	}
}
