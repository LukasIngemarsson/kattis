import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class Main {
    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);

        while (true) {
            int N = io.getInt();
            int M = io.getInt();

            if (N == 0 && M == 0) {
                break;
            }

            int[] jack = new int[N];
            int[] jill = new int[M];
            int count = 0;
            for (int i = 0; i < N; i++) {
                jack[i] = io.getInt();
            }
            for (int j = 0; j < M; j++) {
                jill[j] = io.getInt();
            }
            int val = 0;
            for (int k = 0; k < N; k++) {
                for (int l = val; l < M; l++) {
                    if (jack[k] < jill[l]) {
                        val = l;
                        break;
                    }
                    else if (jack[k] == jill[l]) {
                        count++; 
                        val = l + 1;
                        break;
                    }
                }
            }
            io.println(count);
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
