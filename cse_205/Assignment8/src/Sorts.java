//   Assignment: ASU CSE205 Spring 2021 #8
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: Sort method using a selection sort

import java.util.Comparator;
import java.util.ArrayList;
import java.util.Collections;

public class Sorts {
	// insertion sort
	public static void sort(ArrayList<Department> deptList, Comparator<Department> xComparator) {
		int min;

		for (int index = 0; index < deptList.size() - 1; index++) {
			min = index;
			for (int s = index + 1; s < deptList.size(); s++) {
				if (xComparator.compare(deptList.get(s), deptList.get(min)) < 0) {
					min = s;
				}
			}

			// swap the items in the list
			Collections.swap(deptList, min, index);
		}
	}
}
