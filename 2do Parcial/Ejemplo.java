import java.util.Scanner;
import java.io.*;

class GFG {
    public static void main(String[] args)
    {
        // Step 1: Create Scanner object
        Scanner sc = new Scanner(System.in);

        // Step 2: Prompt user for input
        System.out.print("Enter an integer: ");

        // Step 3: Read integer input
        int number = sc.nextInt();

        // Step 4: Print the entered integer
        System.out.println("You entered: " + number);

        // Close the scanner
        sc.close();
        // f is to ensures that numbers are float DATA TYPE
        float f1 = 1.5f;
        float f2 = 2.0f;

        // to store the multiplied value
        float p = f1 * f2;

        // to print the product
        System.out.println("The product is: " + p);
    }
    static int Fib_Even_Sum(int N)
    {
        if (N <= 0)
            return 0;

        int fib[] = new int[2 * N + 1];
        fib[0] = 0;
        fib[1] = 1;

        // Initializing the sum
        int s = 0;

        // Adding remaining numbers
        for (int j = 2; j <= 2 * N; j++) {
            fib[j] = fib[j - 1] + fib[j - 2];

            // Only considering even indexes
            if (j % 2 == 0)
                s += fib[j];
        }
@
@@@@
        return s;
    }

    // The Driver code
    public static void main(String[] args)
    {
        int N = 11;

        // Prints the sum of even-indexed numbers
        System.out.println(
            "Even sum of fibonacci series till number " + N
            + " is: " + +Fib_Even_Sum(N));
    }
}
}