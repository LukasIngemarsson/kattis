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
        Kattio in = new Kattio(System.in);

        int h = in.getInt(), w = in.getInt(); 

        char[][] grid = new char[h][w];
        for (int r = 0; r < h; ++r) {
            String row = in.getWord();
            grid[r] = row.toCharArray();
        }

        int[][] dp = new int[h][w];
        dp[0][0] = 0;
        for (int c = 1; c < w; ++c) {
            dp[0][c] = dp[0][c-1] + ((grid[0][c] == 'I') ? 1 : 0);
        }
        for (int r = 1; r < h; ++r) {
            dp[r][0] = dp[r-1][0] + ((grid[r][0] == 'I') ? 1 : 0);
        }
        for (int r = 1; r < h; ++r) {
            for (int c = 1; c < w; ++c) {
                dp[r][c] = Math.max(dp[r-1][c], dp[r][c-1]) + (grid[r][c] == 'I' ? 1 : 0);
            }
        }

        System.out.println(dp[h-1][w-1]);

        in.close();
    }
}

class Kattio extends PrintWriter {
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
	if (token == null) 
	    try {
		while (st == null || !st.hasMoreTokens()) {
		    line = r.readLine();
		    if (line == null) return null;
		    st = new StringTokenizer(line);
		}
		token = st.nextToken();
	    } catch (IOException e) { }
	return token;
    }

    private String nextToken() {
	String ans = peekToken();
	token = null;
	return ans;
    }
}
