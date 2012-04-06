import java.io.*;

class IntWithGcdRecursive
{
    public IntWithGcdRecursive(int val)
    {
        value = val;
    }
    
    public int getValue() 
    {
        return value;
    }


    public int gcd(int u, int v)
    {
        if(v == 0)
            return u;
        else
            return(gcd(v, u % v));
    }

    private int value;

}
