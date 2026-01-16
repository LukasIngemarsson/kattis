import java.util.Scanner;
import java.util.Stack;

class Main {
    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        char[] line = in.nextLine().toCharArray();
        Stack s = new Stack<>();

        for (int i = 0; i < line.length; i++) {
            if (line[i] != '<') {
                s.push(line[i]);
            }
            else {
                s.pop();
            }
        }

        char[] text = new char[s.size()];
        for (int i = text.length - 1; i >= 0; i--) {
            text[i] = s.pop().toString().charAt(0);
        }

        System.out.println(String.valueOf(text));
    }
}
