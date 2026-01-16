import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Arrays;
import java.util.Locale;

class Main {
    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);

        while (true) {
            int f = io.getInt();

            if (f == 0) {
                break;
            }

            int r = io.getInt();
            int[] teethF = new int[f];
            int[] teethR = new int[r];
            float[] ratios = new float[f*r];
            for (int i = 0; i < f; i++) {
                teethF[i] = io.getInt();
            }
            for (int j = 0; j < r; j++) {
                teethR[j] = io.getInt();
            }
            int index = 0;
            for (int k = 0; k < r; k++) {
                for (int l = 0; l < f; l++) {
                    ratios[index] = (float) teethR[k]/teethF[l];
                    index++;
                }
            }

            Arrays.sort(ratios);
            float[] quos = new float[f*r - 1];
            for (int z = 0; z < f*r - 1; z++) {
                quos[z] = ratios[z + 1]/ratios[z];
            }
            Arrays.sort(quos);
            io.println(String.format(Locale.US, "%.2f", quos[f*r - 2]));
        }

        io.close();
    }
    
    static class Kattio extends PrintWriter {
        public Kattio(InputStream i) {
            super(new BufferedOutputStream(System.out));
            r = new BufferedReader(new InputStreamReader(i));
        }
        public Kattio(InputStream i, OutputStream o) {
            super(new BufferedOutputStream(o));
            r = new BufferedReader(new InputStreamReader(i));
        }

        public boolean hasMoreTokens() {
            return peekToken() != null;
        }

        public int getInt() {
            return Integer.parseInt(nextToken());
        }

        public double getDouble() { 
            return Double.parseDouble(nextToken());
        }

        public long getLong() {
            return Long.parseLong(nextToken());
        }

        public String getWord() {
            return nextToken();
        }

        private BufferedReader r;
        private String line;
        private StringTokenizer st;
        private String token;

        private String peekToken() {
            if (token == null) {
                try {
                    while (st == null || !st.hasMoreTokens()) {
                        line = r.readLine();
                        if (line == null) return null;
                        st = new StringTokenizer(line);
                    }
                    token = st.nextToken();
                } catch (IOException e) {}
            }
            return token;
        }

        private String nextToken() {
            String ans = peekToken();
            token = null;
            return ans;
        }
    }
}
