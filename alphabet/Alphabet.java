import java.util.Scanner;
// doesn't work as wanted in kattis
public class Alphabet {

    static String alphabet = "abcdefghijklmnopqrstuvwxyz";
    public static void main (String[] args) {

        Scanner in = new Scanner(System.in);
        String text = in.nextLine();
        int count = 0;

        for (int i = 0; i < text.length(); i++) {
            int temp = 0, prev = -1;
            for (int k = i; k < text.length(); k++) {
                int ind = getIndex(text.charAt(k));
                if (ind > prev) {
                    temp++;
                    prev = ind;
                }
                
            }
            if (temp > count) {
                count = temp;
            }
        }
        System.out.println(alphabet.length() - count);
    }

    public static int getIndex(char c) {
        for (int j = 0; j < alphabet.length(); j++) {
            if (c == alphabet.charAt(j)) {
                return j;
            }
        }
        return -1;
    }
}