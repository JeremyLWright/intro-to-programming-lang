import java.io.*;

class IntWithGcdRecursiveOperator
{
    public IntWithGcdRecursiveOperator(int val)
    {
        value = val;
    }
    
    public int getValue() 
    {
        return value;
    }


    public int OpGcd(final IntWithGcdRecursiveOperator val)
    {
        return gcd(value, val.getValue());
    }

    private int gcd(int u, int v)
    {
        if(v == 0)
            return u;
        else
            return(gcd(v, u % v));
    }

    private int value;

}
