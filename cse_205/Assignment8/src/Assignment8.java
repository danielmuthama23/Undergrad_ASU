//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: The Assignment 8 class displays a menu of choices to a user
//               and performs the chosen task. It will keep asking a user to
//               enter the next choice until the choice of 'Q' (Quit) is
//               entered.

import java.io.*;

public class Assignment8 {
	public static void main(String[] args) {
		// method scoped variables
		String deptName, numOfFacultyStr, nameOfUniversity;
		String firstName, lastName, academicLevel;
		String university;
		char input;
		int numOfFaculty;

		String line;
		String filename;

		// create a DeptManagement object. This is used throughout this class.
		DeptManagement deptManage1 = new DeptManagement();

		try {
			// print out the menu
			printMenu();

			// create a BufferedReader object to read input from a keyboard
			InputStreamReader isr = new InputStreamReader(System.in);
			BufferedReader stdin = new BufferedReader(isr);

			do {
				System.out.print("\nWhat action would you like to perform?\n");
				line = stdin.readLine().trim(); // first read a line
				input = line.charAt(0);
				input = Character.toUpperCase(input);

				// check if a user entered only one character
				if (line.length() == 1) {
					switch (input) {
						case 'A':
							// Add Department
							System.out.print("Please enter the department information:\n");
							System.out.print("Enter department name:\n");
							deptName = stdin.readLine().trim();
							System.out.print("Enter number of faculty:\n");
							numOfFacultyStr = stdin.readLine().trim();
							numOfFaculty = Integer.parseInt(numOfFacultyStr);
							System.out.print("Enter university name:\n");
							nameOfUniversity = stdin.readLine().trim();
							System.out.print("Enter faculty first name:\n");
							firstName = stdin.readLine().trim();
							System.out.print("Enter faculty last name:\n");
							lastName = stdin.readLine().trim();
							System.out.print("Enter faculty academic level:\n");
							academicLevel = stdin.readLine().trim();

							// add department
							boolean addedDepartment = deptManage1.addDepartment(
								deptName,
								nameOfUniversity,
								numOfFaculty,
								firstName,
								lastName,
								academicLevel
							);
							if (addedDepartment) {
								System.out.print("Department added\n");
							} else {
								System.out.print("Department NOT added\n");
							}
							break;
						case 'C':
							// Create a new department management
							deptManage1 = new DeptManagement();
							break;
						case 'D':
							// Search by department's name and the university
							System.out.print("Please enter the department name to search:\n");
							deptName = stdin.readLine().trim();
							System.out.print("Please enter the university name to search:\n");
							university = stdin.readLine().trim();

							// check if department exists
							if (deptManage1.deptExists(deptName, university) >= 0) {
								System.out.print(deptName + " at " + university + " is found\n");
							} else {
								System.out.print(deptName + " at " + university + " is NOT found\n");
							}
							break;
						case 'E':
							// search faculty
							System.out.print("Please enter the faculty first name to search:\n");
							firstName = stdin.readLine().trim();
							System.out.print("Please enter the faculty last name to search:\n");
							lastName = stdin.readLine().trim();
							System.out.print("Please enter the faculty academic level to search:\n");
							academicLevel = stdin.readLine().trim();

							// check if faculty exists
							if (deptManage1.facultyExists(firstName, lastName, academicLevel) >= 0) {
								System.out.print("Faculty: " + firstName + " " + lastName + ", " + academicLevel + " is found\n");
							} else {
								System.out.print("Faculty: " + firstName + " " + lastName + ", " + academicLevel + " is NOT found\n");
							}
							break;
						case 'L':
							// List departments
							System.out.print(deptManage1.listDepartments());
							break;
						case 'N':
							// sort departments alphabetically
							Sorts.sort(deptManage1.deptList, new DeptNameComparator());
							System.out.print("sorted by department names\n");
							break;
						case 'O':
							// sort by faculty numbers in increasing order
							Sorts.sort(deptManage1.deptList, new FacultyNumberComparator());
							System.out.print("sorted by faculty numbers\n");
							break;
						case 'P':
							// sort by current faculty in alphabetical order
							Sorts.sort(deptManage1.deptList, new DeptFacultyComparator());
							System.out.print("sorted by current faculty name\n");
							break;
						case 'Q':
							// Quit
							break;
						case 'R':
							System.out.print("Please enter the department name to remove:\n");
							deptName = stdin.readLine().trim();
							System.out.print("Please enter the university name to remove:\n");
							university = stdin.readLine().trim();
						
							// Remove a department
							if (deptManage1.removeDepartment(deptName, university)) {
								System.out.print(deptName + " at " + university + " is removed\n");
							} else {
								System.out.print(deptName + " at " + university + " is NOT removed\n");
							}
							break;
						case 'T':
							// Close DeptManagement
							deptManage1.closeDeptManagement();
							System.out.print("Department management system closed\n");
							break;
						case 'U':
							// Write Text to a File
							System.out.print("Please enter a file name that we will write to:\n");
							filename = stdin.readLine().trim();

							System.out.print("Please enter a string to write inside the file:\n");
							String fileContent = stdin.readLine().trim();

							try {
								// create FileWriter and add content to it
								FileWriter writer = new FileWriter(filename);
								writer.write(fileContent);
								writer.close();
								System.out.print(filename + " is written\n");
							} catch (Exception e) {
								System.out.print("Write string inside the file error\n");
							}
							break;
						case 'V':
							// Read Text from a File
							System.out.print("Please enter a file name which we will read from:\n");
							filename = stdin.readLine().trim();

							try {
								// create BufferReader and read the first line
								BufferedReader br = new BufferedReader(new FileReader(filename)); 
								System.out.print(filename + " was read\n");
								System.out.print("The first line of the file is:\n" + br.readLine() + "\n");
								br.close();
							} catch (FileNotFoundException e) {
								System.out.print(filename + " not found error\n");
							} catch (Exception e) {
								System.out.print("Read string from the file error\n");
							}
							break;
						case 'W':
							// Serialize DeptManagement to a File
							System.out.print("Please enter a file name which we will write to:\n");
							filename = stdin.readLine().trim();

							try {
								// create FileOutputStream and ObjectOutputStream to write serialized object to file
								FileOutputStream fos = new FileOutputStream(filename);
         						
								ObjectOutputStream out = new ObjectOutputStream(fos);
								out.writeObject(deptManage1);
								out.close();

								// close the Streams
								fos.close();
							} catch (FileNotFoundException e) {
								System.out.print("Not serializable exception\n");
							} catch (IOException e) {
								System.out.print("Data file written exception\n");
							}
							break;
						case 'X':
							// Deserialize DeptManagement from a File
							System.out.print("Please enter a file name which we will read from:\n");
							filename = stdin.readLine().trim();

							try {
								// create FileOutputStream and ObjectOutputStream to read serialized object in file
								FileInputStream fi = new FileInputStream(filename);
								ObjectInputStream in = new ObjectInputStream(fi);
								deptManage1 = (DeptManagement)in.readObject();
								in.close();
								fi.close();

								System.out.print(filename + " was read\n");
							} catch (ClassNotFoundException e) {
								System.out.print("Class not found exception\n");
							} catch (NotSerializableException e) {
								System.out.print("Not serializable exception\n");
							} catch (IOException e) {
								System.out.print("Data file read exception\n");
							}
							break;
						case '?':
							// Display Menu
							printMenu();
							break;
						default:
							System.out.print("Unknown action\n");
							break;
					}
				} else {
					System.out.print("Unknown action\n");
				}
				// do unity a user quits
			} while ( input != 'Q' || line.length () != 1);
		// catch all exceptions
		} catch (IOException exception) {
			System.out.print("IO Exception\n");
		}
	}

	/** The method printMenu displays the menu to a user **/
	public static void printMenu() {
		System.out.print(
			"Choice\t\tAction\n" +
			"------\t\t------\n" +
			"A\t\tAdd a department\n" +
			"C\t\tCreate a DeptManagement\n" +
			"D\t\tSearch a department\n" +
			"E\t\tSearch a faculty\n" +
			"L\t\tList departments\n" +
			"N\t\tSort by department names\n" +
			"O\t\tSort by department faculty numbers\n" +
			"P\t\tSort by current faculty name\n" +
			"Q\t\tQuit\n" +
			"R\t\tRemove a department\n" +
			"T\t\tClose DeptManagement\n" +
			"U\t\tWrite strings to a text file\n" +
			"V\t\tRead strings from a text file\n" +
			"W\t\tSerialize DeptManagement to a data file\n" +
			"X\t\tDeserialize DeptManagement from a data file\n" +
			"?\t\tDisplay Help\n"
		);
	}
}