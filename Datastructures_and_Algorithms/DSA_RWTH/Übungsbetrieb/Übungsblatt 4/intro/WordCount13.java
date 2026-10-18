import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class WordCount13 {
        static int x = 13;
        static int y = Math.abs((new Random()).nextInt());
        
        public static int hash(String w) {
                int h = 0;
                for(int i=0; i<w.length(); i++) {
                        h = h*x+w.charAt(i);
                }
                return Math.abs(h);
        }
        
        public static void main(String args[]) throws IOException {
                String filename = args[0];
                List<String> words = Files.readAllLines(Paths.get(filename));
                int m = 100000;
                long count = 0;
                ArrayList<LinkedList<String>> slot = new ArrayList<>();
                for(int i=0; i<m; i++) {
                        slot.add(new LinkedList<String>());
                }
                for(String w: words) {
                        LinkedList<String> list = slot.get(hash(w) % m);
                        if(!list.contains(w)) {
                                count = count + 1;
                                list.add(w);
                        }
                }
                System.out.println(count+" different words in "+filename+".");
        }
}
