import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Locale;
import java.io.IOException;

public class AboveAverage {

    public static void main (String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int C = Integer.parseInt(in.readLine());

        for (int i = 0; i < C; i++) {
            String[] line = in.readLine().split(" ");

            int total = 0;
            for (int j = 1; j < line.length; j++) {
                total += Integer.parseInt(line[j]);
            }
            total = total/(Integer.parseInt(line[0]));
            int count = 0;
            for (int j = 1; j < line.length; j++) {
                if (Integer.parseInt(line[j]) > total) {
                    count++;
                }
            }
            float perc = (float) 100*count/(Integer.parseInt(line[0]));
            System.out.println(String.format(Locale.US, "%.3f", perc) + "%");

        }
     }
}