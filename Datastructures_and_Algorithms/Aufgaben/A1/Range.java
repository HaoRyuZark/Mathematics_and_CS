import java.util.Iterator;

public class Range implements Iterable<Integer> {
	
	private int start;
	private int stop;
	
	public Range(int start, int stop) {
		this.start = start;
		this.stop = stop;
	}

	@Override
	public Iterator<Integer> iterator() {
		
		return new Iterator<Integer>() {
			private int pos = start;

			@Override
			public boolean hasNext() {
				return pos<stop;
			}

			@Override
			public Integer next() {
				int ret = pos;
				pos = pos + 1;
				return ret;
			}
	
		};
	}
	
	public static void main(String[] args) {
		
		for (int i: new Range(0, 5)) {
			System.out.println(i); 
		}
		
		System.out.println("");

		for (int i: new Digit(7348)) {
			System.out.println(i);
		}
	}

}
