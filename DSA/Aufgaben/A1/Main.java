public class Main {
    
    public static void main(String[] args) {
        
        for (int i: new Collatz(3)) {
            System.out.println(i);
        }

        for (char c: new Chars("Hallo")) {
            System.out.println(c);
            }
    }
}
