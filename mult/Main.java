import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int f = in.nextInt(); 
        --n;
        while (n-- > 0) {
            int a = in.nextInt();

            if (a % f == 0) {
                System.out.println(a);
                f = in.nextInt(); 
                --n;
            }
        }

        in.close();
    }
}