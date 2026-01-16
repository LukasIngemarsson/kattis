import java.util.Arrays;
import java.util.Locale;

public class TourDeFrance {
    
    public static void main(String[] args) {
        
        Kattio io = new Kattio(System.in);

        while(true) {
            int f = io.getInt();

            if (f == 0) {
                break;
            }

            int r = io.getInt();
            int[] teethF = new int[f];
            int[] teethR = new int[r];
            float[] ratios = new float[f*r];
    
            for (int i = 0; i < f; i++) {
                teethF[i] = io.getInt();
            }
    
            for (int j = 0; j < r; j++) {
                teethR[j] = io.getInt();
            }
            
            int index = 0;
            for (int k = 0; k < r; k++) {
                for (int l = 0; l < f; l++) {
                    ratios[index] = (float) teethR[k]/teethF[l];
                    index++;
                }
            }

            Arrays.sort(ratios);
            float[] quos = new float[f*r - 1];
            
            for (int z = 0; z < f*r - 1; z++) {
                quos[z] = ratios[z + 1]/ratios[z];
            }

            Arrays.sort(quos);

            System.out.println(String.format(Locale.US, "%.2f", quos[f*r - 2]));
        }
    }
}

