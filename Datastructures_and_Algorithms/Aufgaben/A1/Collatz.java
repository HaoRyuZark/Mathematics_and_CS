import java.util.Iterator;

/**
 * The {@code Collatz} class provides an iterable implementation of the Collatz sequence.
 * The sequence starts from a given positive integer and follows these rules:
 * <ul>
 *     <li>If the number is even, divide it by 2.</li>
 *     <li>If the number is odd, multiply it by 3 and add 1.</li>
 *     <li>The sequence ends when it reaches 1.</li>
 * </ul>
 */
public class Collatz implements Iterable<Integer> {

    /**
     * The starting number of the Collatz sequence.
     */
    private int start;

    /**
     * Constructs a new {@code Collatz} sequence with the given start value.
     *
     * @param start the starting number of the sequence (must be positive)
     * @throws IllegalArgumentException if {@code start} is not greater than zero
     */
    public Collatz(int start) {
        
        if (start <= 0) {
            throw new IllegalArgumentException("Invalid argument");
        }

        this.start = start;
    }

    /**
     * Returns an iterator that iterates over the Collatz sequence.
     *
     * @return an {@code Iterator} for the sequence
     */
    @Override
    public Iterator<Integer> iterator() {

        return new Iterator<Integer>() {
            
            int x = start;

            @Override
            public boolean hasNext() {
                return x > 0;
            }

            @Override
            public Integer next() {

                if (x == 1) {

                    x = 0;
                
                    return 1;
                }

                int current = x;
                x = (x % 2 == 0) ? x / 2 : ((3 * x) + 1);
                
                return current;
            }
        };
    }

}