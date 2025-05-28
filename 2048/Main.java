import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.StringTokenizer;

class Main {
    final static int N = 4;

    static int[][] rotate(int[][] grid, boolean cw) {
        int[][] newGrid = new int[N][N];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (cw)
                    newGrid[j][(N - 1) - i] = grid[i][j];
                else
                    newGrid[(N - 1) - j][i] = grid[i][j];
            }
        }
        return newGrid;
    }

    public static void main(String[] args) {
        Kattio io = new Kattio(System.in);

        int[][] grid = new int[N][N];
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                grid[r][c] = io.getInt();
            }
        }

        int dir = io.getInt();
        // 0 -> rotate 0 (left)
        // 1 -> rotate -90 (up)
        // 2 -> rotate -180 (right)
        // 3 -> rotate -270 (down)

        for (int i = 0; i < dir; ++i)
            grid = rotate(grid, false);

        for (int r = 0; r < N; ++r) {
            int[] newRow = new int[N];
            int prev = -1, idx = 0;
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] == 0)
                    continue;

                if (prev == -1) {
                    prev = grid[r][c];
                }
                else if (grid[r][c] == prev) {
                    newRow[idx++] = 2 * prev;
                    prev = -1;
                }
                else {
                    newRow[idx++] = prev;
                    prev = grid[r][c];
                }
            }
            if (prev != -1)
                newRow[idx++] = prev;

            for (int i = 0; i < N; ++i) {
                grid[r][i] = newRow[i];
            }
        }

        for (int i = 0; i < dir; ++i)
            grid = rotate(grid, true);

        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (c > 0)
                    io.print(' ');
                io.print(grid[r][c]);
            }
            io.println();
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
