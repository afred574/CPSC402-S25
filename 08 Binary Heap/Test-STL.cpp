#include <iostream>
#include <queue>
using namespace std;

    // Test program
int main( )
{
    int numItems = 101;
    int counter = 0;
    priority_queue<int> h;
    int i = 37;
    int x;

    cout << "Insertion order: " << endl;

    
    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
      {
	cout << i << " ";
	counter++;
	if (counter % 10 == 0) cout << endl;
	
        h.push( i );
      }
    cout << endl;
    counter = 0;
    cout << "Removal order: " << endl;
    for( i = 1; i < numItems; i++ )
    {
      
        x = h.top( );
	h.pop();
	cout << x << " ";
        counter++;
        if (counter % 10 == 0) cout << endl;

	/*	
        if( x != i )
	cout << "Oops! " << i << endl; */
    }
    cout << endl;
    return 0;
}
