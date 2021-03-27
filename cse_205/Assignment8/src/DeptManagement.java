//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: DeptManagement that implements Serializable so it can be serialized
//    		 	 Handles all of the departments

import java.io.*;
import java.util.ArrayList;

public class DeptManagement implements Serializable {
	// private instance variables
	ArrayList<Department> deptList;

	// constructor
	public DeptManagement() {
		this.deptList = new ArrayList<Department>();
	}

	// check if a dept exists
	public int deptExists(String deptName, String universityName) {
		// go through all depts and see if the name and uni match
		for (int i = 0; i < this.deptList.size(); i++) {
			if (
				this.deptList.get(i).getDeptName().equals(deptName) &&
				this.deptList.get(i).getUniversity().equals(universityName)
			) {
				return i;
			}
		}
		// return -1 if none are found
		return -1;
	}

	// check if a faculty exists
	public int facultyExists(String firstName, String lastName, String academicLevel) {
		// go through all faculty and see if any match first, last, and academic level
		for (int i = 0; i < this.deptList.size(); i++) {
			Faculty faculty = this.deptList.get(i).getFaculty();
			if (
				faculty.getFirstName().equals(firstName) &&
				faculty.getLastName().equals(lastName) &&
				faculty.getAcademicLevel().equals(academicLevel)
			) {
				return i;
			}
		}
		// return -1 if none are found
		return -1;
	}

	// add department to deptList
	public boolean addDepartment(
		String deptName,
		String university,
		int numOfMembers,
		String firstName,
		String lastName,
		String academicLevel
	) {
		// check if a dept exists, if not create and add to list
		if (this.deptExists(deptName, university) < 0) {
			this.deptList.add(
				new Department(
					deptName,
					university,
					numOfMembers,
					firstName,
					lastName,
					academicLevel
				)
			);
			return true;
		} else {
			return false;
		}
	}

	//***will remove all departments with the same name and university
	public boolean removeDepartment(String deptName, String universityName) {
		// check if department exists
		int exisitingDepart = this.deptExists(deptName, universityName);
		// if it does, remove it
		if (exisitingDepart >= 0) {
			this.deptList.remove(exisitingDepart);
			return true;
		} else {
			return false;
		}
	}

	// sort by department name using DeptNameComparator
	public void sortByDepartmentName() {
		Sorts.sort(this.deptList, new DeptNameComparator());
	}
	
	// sort by faculty number using FacultyNumberComparator
	public void sortByFacultyNumbers() {
		Sorts.sort(this.deptList, new FacultyNumberComparator());
	}
	
	// sort by dept faculty using DeptFacultyComparator
	public void sortByDeptFaculty() {
		Sorts.sort(this.deptList, new DeptFacultyComparator());
	}

	// list departments using the dept toString()
	public String listDepartments() {
		if (this.deptList.size() > 0) {
			String list = "\n";
			for (Department dept : this.deptList)
				list += dept;
			return list + "\n";
		} else {
			return "\nNo Department\n\n";
		}
	}

	// close the dept management by creating a new ArrayList
	public void closeDeptManagement() {
		this.deptList = new ArrayList<Department>();
	}
}