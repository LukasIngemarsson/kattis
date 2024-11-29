import java.util.Scanner;

public class DivvyingUp {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int tot = 0;
        for (int i = 0; i < n; i++) {
            tot += in.nextInt();
        }
        if (tot%3==0) {
            System.out.println("yes");
        }
        else {
            System.out.println("no");
        }
    }
}
