import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class GenealogicalResearch {

        static ArrayList<String> people = new ArrayList<String>();
        static ArrayList<String> dates = new ArrayList<String>();
        static ArrayList<String> mothers = new ArrayList<String>();
        static ArrayList<String> fathers = new ArrayList<String>();
        static int count = 1;

        public static void main(String[] args) throws IOException {

                BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
                String line = in.readLine();
                String com;
                String[] input;
                boolean lineBreak = false;

                while (true) {
                        if (line.equals("QUIT")) {
                                break;
                        }
                        input = line.split(" : ");
                        String[] comAndName = input[0].split(" ", 2);
                        input[0] = comAndName[1];
                        com = comAndName[0];

                        if (com.equals("BIRTH")) {
                                people.add(input[0]);
                                dates.add(input[1] + " -");
                                mothers.add(input[2]);
                                fathers.add(input[3]);
                        }

                        else if (com.equals("DEATH")) {
                                int ind = identify(input[0]);
                                dates.set(ind, dates.get(ind) + " " + input[1]);
                        }

                        else if (com.equals("ANCESTORS")) {
                                if (lineBreak) {
                                        System.out.println();
                                }
                                else {
                                        lineBreak = true;
                                }
                                System.out.println("ANCESTORS of " + input[0]);
                                familyTree(input[0]);
                        }

                        else if (com.equals("DESCENDANTS")) {
                                if (lineBreak) {
                                        System.out.println();
                                }
                                else {
                                        lineBreak = true;
                                }
                                System.out.println("DESCENDANTS of " + input[0]);
                                reverseFamilyTree(input[0]);

                        }
                        line = in.readLine();
                }
        }

        public static void familyTree(String person) {
                int id = identify(person);
                if (id > -1) {
                        String[] par = new String[] {fathers.get(id), mothers.get(id)};
                        Arrays.sort(par);

                        for (int i = 0; i < par.length; i++) {
                                for (int j = 0; j < count; j++) {
                                        System.out.print("  ");
                                }
                                System.out.print(par[i]);
                                id = identify(par[i]);
                                if (id > -1) {
                                        System.out.println(" " + dates.get(id));
                                        count++;
                                        familyTree(par[i]);
                                        count--;
                                } 
                                else {
                                        System.out.println();
                                }
                        }
                }
        }

        public static void reverseFamilyTree(String person) {
                ArrayList<String> chi = new ArrayList<>();
                for (int i = 0; i < people.size(); i++) {
                        if (person.equals((fathers.get(i))) || person.equals((mothers.get(i)))) {
                                chi.add(people.get(i));
                        }
                }
                if (!chi.isEmpty()) {
                        Collections.sort(chi);
                        for (int j = 0; j < chi.size(); j++) {
                                String c = chi.get(j);
                                for (int k = 0; k < count; k++) {
                                        System.out.print("  ");
                                }
                                System.out.println(c + " " + dates.get(identify(c)));
                                count++;
                                reverseFamilyTree(c);
                                count--;
                        }
                }
        }

        public static int identify(String person) {
                for (int z = 0; z < people.size(); z++) {
                        if (person.equals(people.get(z))) {
                                return z;
                        }
                }
                return -1;
        }
}
