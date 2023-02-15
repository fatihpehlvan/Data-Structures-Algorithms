import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public final class ReadCSVFile {
    public static int[] csvToArrayList(String path) {
        ArrayList<Integer> data = new ArrayList<>();
        try {
            int count = 1;
            String line = "";
            BufferedReader br = new BufferedReader(new FileReader(path));
            while ((line = br.readLine()) != null)
            {
                if (count == 1) {
                    count++;
                    continue;
                }
                int number = Integer.parseInt(line.split(",")[7]);
                data.add(number);
            }
        } catch (
                IOException e) {
            e.printStackTrace();
        }
        int[] array = new int[data.size()];
        for (int i = 0; i < data.size(); i++) array[i] = data.get(i);
        return array;
    }
}
