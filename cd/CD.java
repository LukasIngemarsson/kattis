public class CD {
    
    public static void main (String[] args) {
        Kattio io = new Kattio(System.in, System.out);

        while (true) {
            int N = io.getInt();
            int M = io.getInt();

            if (N == 0 && M == 0) {
                System.exit(0);
            }

            int[] jack = new int[N];
            int[] jill = new int[M];
            int count = 0;
        
            for (int i = 0; i < N; i++) {
                jack[i] = io.getInt();
            }
    
            for (int j = 0; j < M; j++) {
                jill[j] = io.getInt();
            }

            int val = 0;
    
            for (int k = 0; k < N; k++) {
                for (int l = val; l < M; l++) {

                    if (jack[k] < jill[l]) {
                        val = l;
                        break;
                    }

                    else if (jack[k] == jill[l]) {
                        count++; 
                        val = l + 1;
                        break;
                    }
                }
            }
    
            System.out.println(count);
        }
    }
   
}
