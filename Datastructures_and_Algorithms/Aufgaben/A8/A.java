import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class GreedySportkurs {

	public static ArrayList<Sportkurs> greedySportkurswahl(ArrayList<Sportkurs> alleKurse){
		// TODO
	}
	
	public static void main(String[] args) {
		ArrayList<Sportkurs> beispiel1 = new ArrayList<Sportkurs>();
		beispiel1.add(new Sportkurs(8,15));
		beispiel1.add(new Sportkurs(16,23));
		beispiel1.add(new Sportkurs(14,17));
		
		System.out.println(greedySportkurswahl(beispiel1));

		ArrayList<Sportkurs> beispiel2 = new ArrayList<Sportkurs>();
		beispiel2.add(new Sportkurs(13,19));
		beispiel2.add(new Sportkurs(11,12));
		beispiel2.add(new Sportkurs(16,18));
		beispiel2.add(new Sportkurs(21,23));
		beispiel2.add(new Sportkurs(17,21));
		beispiel2.add(new Sportkurs(17,18));
		beispiel2.add(new Sportkurs(14,16));
		beispiel2.add(new Sportkurs(18,20));
		beispiel2.add(new Sportkurs(20,22));
		beispiel2.add(new Sportkurs(11,14));
		
		System.out.println(greedySportkurswahl(beispiel2));
	}
}
record Sportkurs(int a, int e) implements Comparable<Sportkurs> {
		@Override
		public int compareTo(Sportkurs o) {
			return this.e - o.e;
		}
		@Override
		public final String toString() {
		return a + "--" + e;
		}
	};
