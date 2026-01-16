import java.util.Scanner;

class Main {
    public static void main (String[] args) {
          Scanner in = new Scanner(System.in);
          String a = in.nextLine();
          if (a.substring(0,3).equals("555")) {
              System.out.println("1");
          }
          
          else {
              System.out.println("0");
          }
    }
}
