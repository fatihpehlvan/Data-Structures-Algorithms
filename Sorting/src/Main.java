import java.io.IOException;
import java.util.Arrays;
import java.util.Collections;

public class Main
{

    public static void main(String[] args) throws IOException {
        // Read csv file and store necessary elements in an in array
        int[] data1 = ReadCSVFile.csvToArrayList(args[0]);
        call(data1, "Tests on Random Data");
        MergeSort.mergeSort(data1);
        call(data1, "Tests on Sorted Data");
        reverse(data1);
        call(data1, "Test on Reversely Sorted Data");
    }
    static void call(int[] data, String title) throws IOException {
        int index = 0;
        int[] counter = {512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 251281};
        double[][] arr = new double[4][10];
        for (int i : counter){
            double insertion = 0;
            double merge = 0;
            double pigeonhole = 0;
            double counting = 0;
            for (int j = 0; j < 10; j++){
                insertion += InsertionSort.insertionSort(Arrays.copyOfRange(data, 0, i));
                merge += MergeSort.mergeSort(Arrays.copyOfRange(data, 0, i));
                pigeonhole += PigeonholeSort.pigeonholeSort(Arrays.copyOfRange(data, 0, i));
                counting += CountingSort.countingSort(Arrays.copyOfRange(data, 0, i));
            }
            arr[0][index] = insertion / 10;
            arr[1][index] = merge / 10;
            arr[2][index] = pigeonhole / 10;
            arr[3][index] = counting / 10;
            index++;
        }
        Show.showAndSaveChart(title, counter, arr);
        for (double[] i : arr)
            System.out.println(Arrays.toString(i));
    }
    static void reverse(int[] arr){
        int n = arr.length;
        int i, t;
        for (i = 0; i < n / 2; i++) {
            t = arr[i];
            arr[i] = arr[n - i - 1];
            arr[n - i - 1] = t;
        }
    }
}