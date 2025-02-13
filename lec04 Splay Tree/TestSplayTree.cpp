#include "SplayTree.h"
#include <iostream>

using namespace std;

int main() {
    SplayTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    cout << "Pre-Order Traversal before splay: ";
    tree.preOrderTraversal();
    cout << endl;
    cout << "Post-Order Traversal before splay: ";
    tree.postOrderTraversal();
    cout << endl;
    if (tree.contains(3))
        cout << "3 is in the tree\n"; 

    cout << "Pre-Order Traversal after splay: ";
    tree.preOrderTraversal();
    cout << endl;
    cout << "Post-Order Traversal after splay: ";
    tree.postOrderTraversal();
    cout << endl;
    return 0;
}
