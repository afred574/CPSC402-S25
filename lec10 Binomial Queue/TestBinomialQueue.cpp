#include "BinomialQueue.h"
#include <iostream>
using namespace std;

int main( )
{
    int numItems = 101;
    BinomialQueue<int> h1;
    BinomialQueue<int> h2;
   
    int i = 37;
    int count = 0;

    cout << "Generating 100 numbers in random order" << endl;
    cout << "Insert even numbers into h1 and odd numbers into h2" << endl;
    
    //generating 1-100 in random order
    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
    {
        //print the values, ten on each line
        cout << i << " ";
        count ++;
        if (count % 10 == 0) 
            cout << endl;


        // if even, insert into h1
        if( i % 2 == 0 )
            h1.insert( i );

        // if odd, insert into h2
        else
            h2.insert( i );
    }
    
    cout << "Now merge h1 into h2" << endl;
    h2.merge( h1 );
    //h2 = h;

    cout << "Perform 100 deleteMin on h2" << endl;
    count = 0;
    for( i = 1; i < numItems; ++i )
    {
        int x;
        h2.deleteMin( x );

        //print the values, ten on each line
        cout << i << " ";
        count ++;
        if (count % 10 == 0) 
            cout << endl;
    }

    if( h1.isEmpty( ) && h2.isEmpty() )
        cout << "Now both h1 and h2 are empty" << endl;

    return 0;
}
