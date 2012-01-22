import java.io.*;
class IntWithGcd
{   
    public IntWithGcd( int val ) 
    {
        value = val;
    }

    public int getValue() 
    {
        return value;
    }

    public int gcd ( int v )
    {   int z = value; /* “imperative” version */
        int y = v;
        while ( y != 0 )
        {   int t = y;
            y = z % y;
            z = t;
        }
        return z;
    }

    protected int value;
}
