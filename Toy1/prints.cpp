#include "FuncLibrary.h"

// prints pyramid of stars height a
void starTrees(int a){ 
    int rows;

    cout << "Enter number of rows: ";
    cin >> rows;

    for(int i = 1; i <= rows; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            cout << "* ";
        }
        cout << "\n";
    }
    return;
}  

// returns hello + " " + string
string hello(string a) {
    cout << "hello, " << a << endl;
    return;
}

// returns our names
string meetCatWalk() {
    cout << "Meet the members of CatWalk: " << endl;
    cout << "Laurence D'Ercole" << endl;
    cout << "Jessica Lam" << endl;
    cout << "Issac Navarro" << endl;
    cout << "Britney Vi" << endl;
    return;
}

// prints string 
void print(string a) {
    cout << a << endl;
    return;
} 