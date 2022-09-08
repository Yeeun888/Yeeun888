#include <iostream>

void chapter61() {
    //Compound statements 
    //This function is basically a compound statement. Basically enclosed spaces
    //of {} 

    //CPP Supports 256 levels of block nesting but it's better not to do.

    {
        const int x = 5; //Block ex
    }
}

//Chapter 6.2 Speaks on encapsulating functions in namespacers
namespace testName {
    void printMessage() {
        std::cout << "Hello this is a test message \n";
    }
}

void callNamespace() {
    testName::printMessage();

    /**
     * Important notes on namespaces
     * 
     * 1. They can easily be nested within each other 
     * 2. Only use name spaces when necessary or when distributing code
     */
}

void chapter63() {
    //Local Variables

    const int x = 7; //This variable is independent from chater61(). Because it is local
}

//Global Variables - Chapter 64

const int G_testNum = 5;

//using G as a prefix is a good practice for global variables

void chapter65() {
    //Variable shadowing

    int apples { 5 };

    {
        std::cout << apples << '\n'; //refers to outer block apples

        int apples { 10 }; //apples defined and hides "global" or outer variables

        std::cout << apples << '\n'; //refers to inner apples
        
    } //inner apples destoryed

    std::cout << apples << '\n'; 
} //Outer apple also destroyed. 

//Chapter 6.6 Internal Linkage

static int add(int x, int y) { //Static means it can only be accessed from this file
    return x+y;
}

//Linkages determine where the object can be accessed from. Rather than if it
//appears or not.

//Const global variables are internal linkage by default, non-const are external

//CHAPTER 6.7 - EXTERNAL LINKAGES

extern const int testInteger {5}; //Now it is externally accessible

//CHAPTER 6.9 - USING INLINE VARIABLES 

namespace constants {
    inline constexpr double pi {3.14159};
    //inline keyword allows the variable to be defined multiple times, given that
    //they are accurate. At compile-time only one will be taken

    //Given two conditions; 1. All inline variables are identical, 2. The inline
    //variables are not forward declarations i.e. they have to be present.
}

void chapter612() {
    using std::cout;
    cout << "This is a test \n";

} //Here the using std::cout expires and cannot be done in the same way again

int createIDvar() {
    //Static Local Variables

    static int IDvar = {1};
    IDvar++;

    std::cout << IDvar << '\n';
    return IDvar;
}

void chapter613() {
    //Inline expansion

    chapter612();

    //this function call becomes. It is more efficient and faster

    std::cout << "This is a test \n";
}

constexpr int greater(int x, int y) {
    return ((x > y) ? x : y);
}
//In C++20 consteval can be used instead of constexpr to force compile time 
//optimization

void chapter614() {
    //constexpr calls

    constexpr int g { greater(5, 6) }; //Is called at compile time

    int x{ 5 };
    std::cout << greater(x, 6) << '\n'; //Not compile time because is evaluated at runtime

    std::cout << greater(5, 6) << '\n'; //Depending on compiler no guarantee
}

//  chapter 6.15 UNNAMED AND INLNIE NAMESPACES

//unnamed namespaces to group functions
namespace {
    //insert functions here

    //The purpose of this is that namespaces have internal linkage
    //meaning that a large group of code can be grouped to just have internal 
    //linkage instead of using multiple static keywords.
}

//inline namespaces can be used for multiple versions of the same function
//to prevent older code breaking

inline namespace v1 {
    void printSomething() {
        std::cout << "v1\n";
    }
}

namespace v2 {
    void printSomething() {
        std::cout << "v2\n";
    }
}

void chapter615() {
    printSomething();
    v2::printSomething();
}

int main() {
    chapter615();

    return 0; 
}