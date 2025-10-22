package Thread_Programming;
// the code in the book had Integer (which i found, is now, deprecated. thus the code is from perplexity(AI).)
import java.util.concurrent.*;

class Summation implements Callable<Integer> {
    private int upper;

    public Summation(int upper) {
        this.upper = upper;
    }

    // The thread will execute this method
    @Override
    public Integer call() {
        int sum = 0;
        for (int i = 1; i <= upper; i++) {
            sum += i;
        }
        // Using Integer.valueOf() instead of deprecated new Integer()
        return Integer.valueOf(sum);
    }
}

public class JavaThreads {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java ThreadProgramming.JavaThreads <upper_limit>");
            return;
        }

        int upper = Integer.parseInt(args[0]);

        // Create a single-thread executor
        ExecutorService pool = Executors.newSingleThreadExecutor();

        // Submit Summation task
        Future<Integer> result = pool.submit(new Summation(upper));

        try {
            // Retrieve and print the result
            System.out.println("sum = " + result.get());
        } catch (InterruptedException | ExecutionException ie) {
            ie.printStackTrace();
        } finally {
            // Always shut down the ExecutorService
            pool.shutdown();
        }
    }
}