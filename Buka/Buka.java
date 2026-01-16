import java.math.BigInteger;
import java.util.Scanner;

public class Buka {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        BigInteger a = in.nextBigInteger();
        in.nextLine();
        String op = in.nextLine();
        BigInteger b = in.nextBigInteger();

        if (op.equals("+")) {
            System.out.println(a.add(b));
        }

        else if (op.equals("*")) {
            System.out.println(a.multiply(b));
        }
    }
}