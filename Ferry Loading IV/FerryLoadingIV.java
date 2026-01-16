import java.io.*;
import java.util.ArrayList;

public class FerryLoadingIV {
    
        public static void main(String[] args) throws IOException {

           try {

                BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

                int c = Integer.parseInt(in.readLine()); 

                for (int i = 0; i < c; i++) {
                    String [] twoInts = in.readLine().split(" ");
                    int l = 100*Integer.parseInt(twoInts[0]);
                    int m = Integer.parseInt(twoInts[1]);
                    ArrayList<Integer> right = new ArrayList<Integer>();
                    ArrayList<Integer> left = new ArrayList<Integer>();

                    for (int j = 0; j < m; j++) {
                        String[] line = in.readLine().split(" ");
                        String dir = line[1];
                        int carLength = Integer.parseInt(line[0]);
                        if (dir.equals("right") && carLength <= l) {
                            right.add(carLength);
                        }
                        else if (dir.equals("left") && carLength <= l) {
                            left.add(carLength);
                        }
                    }

                    int count = 0;
                    int temp = l;
                    boolean isCar = true;
                    boolean isLeft = true;
                    boolean isRight = true;

                    while (isCar) {

                        if (!isLeft) {
                            count++;
                        }

                        temp = l;

                        while (isLeft) {
                            if (!left.isEmpty() && temp >= left.get(0)) {
                                temp -= left.get(0);
                                left.remove(0);
                            }

                            else {
                                count++;
                                if (left.isEmpty()) {
                                    isLeft = false;
                                }

                                break;
                            }
                        }

                        temp = l;

                        if (!isRight) {
                            if (!isLeft) {
                                isCar = false;
                            }

                            else {
                                count++;
                            }
                        }
        
                        while (isRight) {
                            if (!right.isEmpty() && temp >= right.get(0)) {
                                temp -= right.get(0);
                                right.remove(0);
                            }

                            else {
                                count++;
                                if (right.isEmpty()) {
                                    isRight = false;
                                }

                                break;
                            }
                        }

                        if (!isLeft && !isRight) {
                            isCar = false;
                        }
                    }

                        System.out.println(count);  
                }


           } catch (FileNotFoundException e) {
                System.out.println("File not found!");
           }
        }
}
