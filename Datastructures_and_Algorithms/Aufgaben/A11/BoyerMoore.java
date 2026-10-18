import java.util.ArrayList;
import java.util.Arrays;

public class BoyerMoore {
	public interface Heuristic {
		int Next(String t, String p, int i, int j);
	}

	// cmp führt den Vergleich aus , wenn das Ende des Musters unter t[i] liegt .
	// Im Erfolgsfall wird der Index i den Ergebnissen in res hinzugefügt.
	// cmp nutzt die übergebenen Heuristiken um den maximal mö glichen Versatz
	// für das Muster zu ermitteln und gibt diesen an den Aufrufer zurück.
	static protected int cmp(String t, String p, int i, ArrayList<Integer> res, Heuristic... heuristics) {
		int nextI = i + 1, j = p.length() - 1;
		// Vergleich von rechts ( hinten ) nach links ( vorne ) ...
		while (t.charAt(i) == p.charAt(j) && j > 0) {
			i = i - 1;
			j = j - 1;
		}
		if ((j == 0) && (t.charAt(i) == p.charAt(0))) {
			res.add(i);
		}
		// Alle Heuristiken durchgehen ...
		for (Heuristic h : heuristics) {
			int ih = h.Next(t, p, i, j);
			if (ih > nextI) { // besserer Versatz ?
				nextI = ih; // ja: übernehmen !
			}
		}

		return nextI;
	}

	// Sucht im Text t nach allen Vorkommen des Musters p. Zur Bestimmung der
	// Vers ä tze werden die übergebenen Heuristiken verwendet . Wird keine
	// Heuristik übergeben , verhält sich der Algorithmus wie die einfache
	// Textsuche !
	public static ArrayList<Integer> apply(String t, String p, Heuristic... h) {
		ArrayList<Integer> res = new ArrayList<Integer>();
		int i = p.length() - 1; // Position an der Musterende ausgerichtet wird

		while (i < t.length()) {
			i = cmp(t, p, i, res, h);
			System.out.println(i);
		}

		return res;
	}
	public static void main(String[] args) {
		Heuristic test = new Heuristic(){
			@Override
			public int Next(String t, String p, int i, int j) {
				return i;
			}};
		System.out.println(Arrays.toString(apply("mabmabmamab","mama",test).toArray()));
		System.out.println(Arrays.toString(apply("mabmabmamab","mama").toArray()));
	}
} // class BoyerMoore
