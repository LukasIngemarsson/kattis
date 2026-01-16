import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

public class Recount {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        HashMap<String,Integer> cands = new HashMap<>();

        while (true) {
            String line = in.readLine();

            if (line.equals("***")) {
                String top = "";
                int lead = 0;
                boolean tie = false;
                for (String can : cands.keySet()) {
                    if (lead < cands.get(can)) {
                        top = can;
                        lead = cands.get(can);
                        tie = false;
                    }
                    else if (lead == cands.get(can)) {
                        tie = true;
                    }
                }
                if (tie) {
                    System.out.println("Runoff!");
                }
                else {
                    System.out.println(top);
                }
                break;
            }

            if (cands.containsKey(line)) {
                int c = cands.get(line);
                c++;
                cands.put(line, c);
            }

            else {
                cands.put(line, 1);
            }
        }
    }
}