#include <iostream>

using namespace std;

bool ShouldNeverBeCalled()
{
    cout << "You Should Never See This" << endl;
    return true;
}

int main(int argc, const char *argv[])
{
    if(true || ShouldNeverBeCalled())
        cout << "See!" << endl;
    return 0;
}

// Outputs:
// See!
