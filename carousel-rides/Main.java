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

        double EPS = 1e-9;

        while (true) {
            int n = in.getInt(), m = in.getInt();

            if (n == 0  && m == 0)
                break;

            int t = 0, c = 0;
            double q = -1; 
            for (int i = 0; i < n; ++i) {
                double a = in.getDouble(), b = in.getDouble();

                if (a > m)
                    continue;
                if (a / b > q || (Math.abs(a / b - q) < EPS && a > t)) {
                    t = (int)a; 
                    c = (int)b;
                    q = a / b;
                }
            }
            if (q == -1)
                System.out.println("No suitable tickets offered");
            else
                System.out.printf("Buy %d tickets for $%d\n", t, c);
        }

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
