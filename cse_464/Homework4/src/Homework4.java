public class Homework4 {	
	public static void insertionSort(int array[]) {
		int n = array.length;
		for (int j = 1; j < n; j++) {
			int key = array[j];
			int i = j- 1;
			while ((i > -1) && (array [i] > key)) {
				array [i+1] = array [i];
				i--;
			}
			array[i+1] = key;
		}
	}
	
	public static String sortStr(String str) {
		char char_array[] = str.toCharArray();
		char temp;
		int i = 0;
		while (i < char_array.length) {
			int j = i + 1;
			while (j < char_array.length) {
				if (char_array[j] < char_array[i]) {
					temp = char_array[i];
					char_array[i] = char_array[j];
					char_array[j] = temp;
				}
				j += 1;
			}
			i += 1;
		}
		String returnStr = String.valueOf(char_array);
		return returnStr;
	}
}
