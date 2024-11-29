import java.math.BigInteger;
import java.util.Scanner;

public class DiffProb {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (in.hasNextBigInteger()) {
                BigInteger a = in.nextBigInteger();
                BigInteger b = in.nextBigInteger();
                System.out.println((a.subtract(b)).abs());
        }
    }
}