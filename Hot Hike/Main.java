import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int[] temps = new int[n];
        for (int i = 0; i < n; ++i) {
            temps[i] = in.nextInt();
        }

        int d = -1, t = 41;
        for (int i = 0; i < n - 2; ++i) {
            if (Math.max(temps[i], temps[i+2]) < t) {
                t = Math.max(temps[i], temps[i+2]);
                d = i;
            }
        }
        System.out.printf("%d %d\n", d + 1, t);

        in.close();
    }
}