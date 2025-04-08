#include <iostream>
#include "DisjSets.h"
using namespace std;

// Test main; all finds on same output line should be identical
int main( )
{
    
    //create an array of 8 elements
    DisjSets ds(8);
    
    //union 4 and 5
    ds.unionSets(ds.find(4), ds.find(5));

    //union 6 and 7
    ds.unionSets(ds.find(6), ds.find(7));

    //union 5 and 7
    ds.unionSets(ds.find(5), ds.find(7));
    
    //print 
    for (int i=0; i<8; i++)
    {
        cout << "Set containing " << i << ": ";
        cout << ds.find(i) << endl;
    }
    
    return 0;
}
