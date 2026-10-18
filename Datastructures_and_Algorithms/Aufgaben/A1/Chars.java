import java.util.Iterator;

/**
 * The {@code Chars} class provides an iterable wrapper around a {@code String},
 * allowing iteration over its characters using the enhanced for-loop or an explicit iterator.
 */
public class Chars implements Iterable<Character> {
    
    /**
     * The sequence of characters to be iterated over.
     */
    private String sequence;

    /**
     * Constructs a new {@code Chars} instance with the given string.
     *
     * @param seq the string to be wrapped as an iterable sequence
     */
    public Chars(String seq) {

        this.sequence = seq;
    }

    /**
     * Returns an iterator over the characters in the sequence.
     *
     * @return an {@code Iterator} of {@code Character} objects
     */
    @Override
    public Iterator<Character> iterator() {

        return new Iterator<Character>() {
            
             char[] seq = sequence.toCharArray();
             int index = 0;

             @Override
             public boolean hasNext() {
                return index < seq.length;
             }

             @Override
             public Character next() {

                return seq[index++];
             }

        };
    }
}
