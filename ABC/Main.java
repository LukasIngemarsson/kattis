import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.Arrays;

class Main {
    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);

        int[] ints = new int[]{io.getInt(), io.getInt(), io.getInt()};
        String order = io.getWord();

        Arrays.sort(ints);
        int A = ints[0];
        int B = ints[1];
        int C = ints[2];
        for (int i = 0; i < 3; i++) {
            if (order.charAt(i) == 'A') {
                ints[i] = A;
            }
            
            else if (order.charAt(i) == 'B') {
                ints[i] = B;
            }
            
            else {
                ints[i] = C;
            }
        }
        io.println(ints[0] + " " + ints[1] + " " +  ints[2]);

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
