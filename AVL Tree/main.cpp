#include "iterator.h"
using namespace std;

int main()
{
    Dictionary<int, string> tree1;

    tree1.insert(1, "a");
    tree1.insert(7, "b");
    tree1.insert(8, "c");
    tree1.insert(4, "d");
    tree1.insert(5, "e");
    tree1.insert(8, "f");
    tree1.insert(7, "g");
    tree1.insert(14, "h");
    tree1.insert(11, "i");

    cout << endl << "2D Display of Tree1" << endl;
    //display2D
    tree1.display2D();
    tree1.erase(4);
    tree1.erase(2);
    tree1.erase(1);
    //copy constructor
    Dictionary<int, string> tree2 = tree1;
    cout << endl << "InOrder display of Tree2 = Tree1 after erasing nodes {1,2,4}" << endl;
    //displayInOrder
    tree2.displayInOrder();
    //clear()
    tree1.clear();
    cout << endl << "InOrder and 2D display of Tree1 after using clear()" << endl;
    tree1.display2D();
    tree1.displayInOrder();
    //height()
    cout << endl << "Tree1 height = " << tree1.height() << " Tree2 height = " << tree2.height() << endl;
    //belongs()
    if(tree2.belongs(3))
        cout << endl << "Element with ID 3 belongs to Tree2" << endl;
    //getMax()
    cout << endl << "Highest value of ID in Tree2 is " << tree2.getMax() << endl;
    //iterator
    Dictionary<int, string>::iterator iter2 = tree2.iter();
    cout << endl << "Iterator starts at root" << endl;
    tree2.node(iter2);
    iter2++;
    iter2++;
    cout << endl << "Iterator++ ++ " << endl;
    tree2.node(iter2);

    return 0;
}
