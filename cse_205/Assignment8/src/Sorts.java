//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: 

import java.util.Comparator;
import java.util.ArrayList;

public class Sorts {
	public static void sort(ArrayList<Department> deptList, Comparator<Department> xComparator) {
		int min;

		for (int index = 0; index < deptList.size() - 1; index++) {
			min = index;
			for (int s = index + 1; s < deptList.size(); s++) {
				// System.out.println(xComparator.compare(deptList.get(index), deptList.get(min)));
				if (xComparator.compare(deptList.get(index), deptList.get(min)) < 0) {
					min = s;
				}
			}

			Department temp = deptList.get(min);
			deptList.set(min, deptList.get(index));
			deptList.set(index, temp);
		}
	}
}
