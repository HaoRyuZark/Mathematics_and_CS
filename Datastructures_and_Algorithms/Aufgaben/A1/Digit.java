import java.util.Iterator;

public class Digit implements Iterable<Integer> {

    private String val;

    public Digit(int val) {
        
        val = (val < 0)? -1 * val : val;
        this.val = String.valueOf(val);
    }

    @Override
    public Iterator<Integer> iterator() {
        
        return new Iterator<Integer>() {

            int index = val.length() - 1;

			@Override
			public boolean hasNext() {
				return index != -1;
			}

            @Override
			public Integer next() {

                char ret = val.charAt(index);
                this.index--;

                return Integer.parseInt(ret + "");
            }
        };
    }


    

}
