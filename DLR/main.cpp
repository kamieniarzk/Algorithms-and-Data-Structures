#include <iostream>
#include "DLR.h"
#include "iterator.h"
#include "produce.h"

//Created by
//Kamieniarz Kacper
//EITI
//Book Number 293065

using namespace std;

int main()
{
    //PUSH AND DISPLAY FUNCTIONS

    cout << "--------------------------------------------------------------------------";
    cout << "\n----PUSH AND DISPLAY FUNCTIONS----\n";
    DLR<int, string> ring1;
    ring1.push(1, "a");
    ring1.push(2, "b");
    ring1.push(3, "c");
    ring1.push(4, "d");
    ring1.push(5, "e");
    DLR<int, string> ring2;
    ring2.push(8, "f");
    ring2.push(10, "g");
    ring2.push(12, "h");
    ring2.push(14, "i");
    ring2.push(16, "j");
    cout << "DISPLAY OF ring1 AND ring2 AFTER INSERTING ELEMENTS USING push() FUNCTION \n\n";
    cout << "ring1\n" << ring1 << "\nring2\n" << ring2;
    cout << "DISPLAY OF ELEMENT WITH ID 3 FROM ring1 USING displayByKey FUNCTION\n";
    ring1.displayByKey(3);
    cout << "\nCALLING FUNCTION displayByKey WITH NON-EXISTING ID\n";
    ring1.displayByKey(6);

    //CONSTRUCTORS AND OPERATORS

    DLR<int, string> ring3 = ring1 + ring2;
    cout << "\n--------------------------------------------------------------------------\n";
    cout << "----CONSTRUCTORS AND OPERATORS----\n";
    cout << "\nCREATING ring3 USING COPY CONSTRUCTOR AND + OPERATOR, THEN DISPLAYING IT USING displayRing()\n";
    ring3.displayRing();
    ring1.removeByKey(1);
    ring1.removeByKey(2);
    ring1.removeByKey(3);
    ring1.removeByKey(4);
    ring1.pushAfterKey(5, 6, "x");
    ring1.pushBeforeKey(6, 7, "y");
    cout << "\n--------------------------------------------------------------------------\n";

    //REMOVING FUNCTIONS

    cout << "----REMOVING FUNCTIONS----";
    cout << "\nUSING removeByKey ON ring1 AND INSERTING ELEMENTS USING pushBeforeKey and pushAfterKey\n" << ring1 << endl;
    ring1.clear();
    ring1.clear();
    cout << "\nDISPLAYING ring1 AFTER USING clear() TWICE\n";
    cout << "\n--------------------------------------------------------------------------\n";

    //BOOL OPERATORS


    cout << "----BOOL OPERATORS----";
    if(ring2.contain(12, "h"))
        cout << "\nTEST OF contain() FUNCTION ON ring2\n";
    if(ring1 > ring2)
        cout << "\nring 1 > ring2\n";
    if(ring1 <= ring2)
        cout << "\nring 1 <= ring2\n";
    if(ring1 != ring2)
        cout << "\nring 1 != ring2\n";
    cout << "\n--------------------------------------------------------------------------\n";

    //PRODUCE FUNCTION


    cout << "----PRODUCE FUNCTION----";

    cout << "\nCOUT OF produce() FUNCTION WITH ring1(empty) AND ring2\n";

    cout << produce(ring1, 2, 2, true, ring2, 5, 1, false, 5, false);
    ring1.push(1, "a");
    ring1.push(2, "b");
    ring1.push(3, "c");
    ring1.push(4, "d");
    ring1.push(5, "e");

    cout <<"\nCOUT OF produce() FUNCTION WITH ring1 non empty AND ring3\n";
    cout << produce(ring1, 1, 2, true, ring3, 1, 3, false, 2, true);


}

