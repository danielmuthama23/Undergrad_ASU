//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: 

import java.util.ArrayList;

public class DeptManagement {
	ArrayList<Department> deptList;

	public DeptManagement() {
		this.deptList = new ArrayList<Department>();
	}

	public int deptExists(String deptName, String universityName) {
		for (int i = 0; i < this.deptList.size(); i++) {
			if (
				this.deptList.get(i).getDeptName().equals(deptName) &&
				this.deptList.get(i).getUniversity().equals(universityName)
			) {
				return i;
			}
		}
		return -1;
	}

	public int facultyExists(String firstName, String lastName, String academicLevel) {
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
		return -1;
	}

	public boolean addDepartment(
		String deptName,
		String university,
		int numOfMembers,
		String firstName,
		String lastName,
		String academicLevel
	) {
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
		int exisitingDepart = this.deptExists(deptName, universityName);
		if (exisitingDepart >= 0) {
			this.deptList.remove(exisitingDepart);
			return true;
		} else {
			return false;
		}
	}

	public void sortByDepartmentName() {
		Sorts.sort(this.deptList, new DeptNameComparator());
	}
	
	public void sortByFacultyNumbers() {
		Sorts.sort(this.deptList, new FacultyNumberComparator());
	}
	
	public void sortByDeptFaculty() {
		Sorts.sort(this.deptList, new DeptFacultyComparator());
	}

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

	public void closeDeptManagement() {
		this.deptList = new ArrayList<Department>();
	}
}