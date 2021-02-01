#include "FuncLibrary.h"
using namespace std; 

int main() {
    cout << "Hello, World" << endl;

    // Initialize a Fibonacci relation sequence.
    fibonacci_init(1, 1);
    // Write out the sequence values until overflow.
    do {
        std::cout << fibonacci_index() << ": "
            << fibonacci_current() << std::endl;
    } while (fibonacci_next());
    // Report count of values written before overflow.
    std::cout << fibonacci_index() + 1 <<
        " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << std::endl;
    

    add(16, 4); 
    sub(4, 5); 

    starTrees(4); 
    hello("world");
    meetCatWalk();
    print("Hello I love you Jessica <3");     
    print("Hello I love you too Britney <3");
    return 0;
}