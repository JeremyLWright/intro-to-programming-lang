import java.io.*;

class GcdProg /* driver */
{   public static void main (String args[])
    {   System.out.println("Input two integers:");
        BufferedReader in = new BufferedReader(
                new InputStreamReader(System.in));
        try /* must handle I/O exceptions */
        {   
            IntWithGcdRecursiveOperator x = new IntWithGcdRecursiveOperator(Integer.parseInt(in.readLine()));
            IntWithGcdRecursiveOperator y = new IntWithGcdRecursiveOperator(Integer.parseInt(in.readLine()));
            System.out.print("The gcd of " + x.getValue() + " and " + y.getValue() + " is ");
            System.out.println(x.OpGcd(y));
        }
        catch ( Exception e)
        {
            System.out.println(e);
            System.exit(1);
        }
    }
}
