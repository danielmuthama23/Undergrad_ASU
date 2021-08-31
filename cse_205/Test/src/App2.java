public class App2 {
    // public static void quickSort(int[] elements, int from, int to)   {     if ( from < to )       {       int p = partition(elements, from, to);       quickSort(elements, from, p);       quickSort(elements, p+1, to);      }    } //end of quickSort method

    // public static int partition(int[] elements, int from, int to)  {    int pivot = elements[from];    int i = from -1;        int j = to + 1;    while (i < j )      {       i++;       while (elements[i] < pivot)           i++;          j--;         while (elements[j] > pivot)            j--;         {           int temp = elements[i];           elements[i] = elements[j];           elements[j] = temp;         }   p(elements);  }      return j;  }


    public static void p(Comparable[] x) {
        for (Comparable a : x) {
            System.out.print(a);
        }
        System.out.println();
    }

    // static void rvereseArray(int arr[], int start, int end)
    // {
    //     int temp;
    //     if (start >= end)
    //         return;
    //     temp = arr[start];
    //     arr[start] = arr[end];
    //     arr[end] = temp;
    //     rvereseArray(arr, start+1, end-1);
    // }

    public static void selectionSort (Comparable[] data)   {      int min;      for (int index = 0; index < data.length-1; index++)      {         min = index;         for (int scan = index+1; scan < data.length; scan++)            if (data[scan].compareTo(data[min]) < 0)               min = scan;         swap (data, min, index);  p(data);    }   }

    private static void swap (Comparable[] data, int index1, int index2)   {       Comparable temp = data[index1];       data[index1] = data[index2];       data[index2] = temp;   }

    public static void main() {
        Comparable[] x = {18,12,3,8,1};

        selectionSort(x);
        // quickSort(x, 0, x.length-1);

        p(x);
    }
}
