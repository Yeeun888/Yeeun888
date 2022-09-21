#include <iostream>
#include <cstddef>

void chapter91() {
    //Compound data types
    
    /**
     * Compound data types are those that are constructed from integral data
     * types such as but are not limited to: arrays, pointers, functions, classes,
     * etc.
     * 
     * also yes, CHAPTER 9 - 12 IS JUST THIS BULLSHIT
     * it's like 20 reading hours bruh
     * 
     */
}

int chapter92() {
    //lvalues and rvalues

    int x{1}; //This is a modifiable rvalue expression
    const int y{2}; //non modifiable rvalue expression

    //in other words. rvalue = constant

    int a{x}; //Modifiable lvalue
    const int b{y}; //Non-modifiable lvalue

    //in this case variable a and b are the lvalues (not x and y)

    //lvalue = locator value. Basically values that evaluate to pointers or 
    //identifiers of other variables
    
    x = 1; //is a valid statement as the left side requies an modifiable lvalue
           //and the right requires an rvalue.
    x = y; //The statement on the bottom is valid as lvalues are implicitly 
           //converted into rvalues.

    return 0; // this is also an rvalue as it is non-identifiable
}

int chapter93() {
    //lvalue reference

    int x{ 5 }; //normal initilization of variable that occupies space 
    
    int& ref{ x };
    //int& ref{ 4 }; is considered illegal as it references an rvalue
    //using "&" aka Ampersand means reference

    ref += 1; //this changes X instead of ref since ref is just a reference
              //similar to
              //using GravitationalPull = long long double;

    //EXAMPLES OF MISTAKES AND INVALID CODE
    //double& invalOne{}; 1. is considered invalid because it is uninitizlied
                        //2. the reference must have the same type as the
                        //   referenced value

    const double constInt{ 6.5 };
    //double &refconst{constInt}; is also considered invalid due to referencing
    //                            a non-modifiable lvalue

    int y{ 6 };
    ref = y; 

    //Changes X to 6 instead of changing ref to y. 
    //Refernces cannot be reseated to take other values


    //side note: references are not objects and cannot be used to replace them
    //side note: references and the refereant( the object being referenced ) 
    //           have separate lifetimes.

    return 0;
}

void chapter94() {
    ///References const lvalue binding
    
    //Example of standard reference binding
    const int x{ 5 };
    const int& refx{ x };

    //trying to modify through ref or x is illegal. As const cannot be modified

    //can also be used to create read-only forms of variable
    int y{ 6 };
    const int& readOnlyY{ y };

    //temporary object initialization with lvalue
    const int& tempObject{ 7 };

    //7 is a temporary object and is then referenced through "tempObject"
    //the temporary object is anonymous and cannot ever be accessed. 
    //the object (and reference alike) have same lifetime
}

namespace chapter95 {
    //Notes on passing by value 

    void printPass(int y) { //y created temporarily 
        std::cout << y << '\n';
    } //y destoyed again

    void printRef(int& y) {
        std::cout << y << '\n';
    } //this code is also called pass by reference

    //While both functions look similar printRef is lesse expensive to initialize
    //As y is created and destoryed it wastes memory and time. Here instead
    //we can just reference the variable directly instead of copying

    //This matters in particular for classes which are expensive with many
    //objects

    //pass by reference allows the argument to be changed immediately. 
    //consider the following:

    void addOne(int& tempNum) {
        ++tempNum;
    }

    //Pass by reference to non-const parameters won't accept const references
    //to overcome this we can make the variables constant

    void printInt(const int& printConstInt) {
        std::cout << printConstInt << '\n';
    }

    const int intTest{ 50 };
    //printInt(intTest);
    //This function can take both const and non-const variables as parameters
}

void chapter96() {
    //Learning about pointers

    //What are pointers? Pointers are variables that hold memory addresses.
    //Unlike references, pointers are actual objects that occupy memory area.

    //Pointers are used to contain memory addresses

    int x{ 5 };
    std::cout << x << '\n'; //Prints value
    std::cout << &x << '\n';//Prints memory address (in hexadecimal)

    std::cout << *(&x) << '\n'; //* operator can be used to print value at memory
                                //address
    
    //Good practice is that pointers should always be initilized 

    int* ptrExample{ &x };
    std::cout << *ptrExample << '\n';

    //points must be of the same type of the object they are pointing towards
    //tbh idk why

    double doubleTest{ 69.420 };
    double* ptrDouble{ &doubleTest };

    //Unlike references, pointers can also be reseated.

    int y{ 6 };
    ptrExample = &y;

    std::cout << *ptrExample << '\n';
    std::cout << ptrExample << '\n';

    std::cout << sizeof(ptrExample) << '\n';
}

void chapter97() {
    //Null pointers

    //While it's best to initilize pointers, sometimes they are left empty to
    //be initilized later. Here we have to use null pointers.

    //Ways of initilizing null pointers
    int* ptr1 {}; //completely empty
    int* ptr2 { nullptr }; //much better with nullptr keyword
    
    //Legacy and old ways of doing pointers
    int* ptr3 { 0 };
    int* ptr4 { NULL };

    //Important note: DO NOT DEREFENCE NULLPOINTERS AS THEY RESULT IN UNDEFINED
    //BEHAVIOR

    //Conditional to check fo nullptr. Nullptr is implicitly a boolean on it's 
    //own

    if(ptr1 == nullptr) {
        std::cout << "ptr is null\n";
    } else {
        std::cout << "ptr is non-null\n";
    }

    //Good practice:
    //Pointers should be set to valid object overall or to just set to nullptr.
    //With nullptr atleast the values of said values can be tested. 
}

void chapter98() {
    //Constant Pointers, both in values and in the object itself

    const int x{ 5 };
    int y{ 6 };

    const int* xptr{ &x }; //pointer to const X, but the actual xptr is not constant
    //xptr = &y; 
    const int* yptr{ &y }; //Any changes trhough yptr will not happen as it is constant

    int* const const_yptr{ &y }; //y isnt' const. But memory address cannot be changed

    //putting all the shit together we get

    const int* const const_yptr22{ &y }; //Pointer address, and variable cannot be changed
                                         //A true read-only
}

int printByAddress(std::string* ptr) {
    std::cout << *ptr << '\n';

    return 0;
}

void chapter99() {
   std::string stringTest{ "This is a string "};

   printByAddress(&stringTest); 
}

//Function overloading can also be done with nullptr_t types 

void print(std::nullptr_t) {
    std::cout << "it is nullptr_t\n"; 
} //nullptr_t is a type recognized by the compiler

void print(int*) {
    std::cout << "it is a int*\n";
}

//Slightly confusing concept on how to return functions by reference
//CHAPTER 9.11 RETURN BY REFERENCE

//Return by reference is useful in two ways, to reference a static variable
//without having to make a copy, or to refer to another variable. 

namespace chapter911 {
    const std::string& getProgramName() {
        static const std::string programName{ "VSCODE" };

        return programName;
    }

    void printName() {
        std::cout << "This program is called " << getProgramName() << '\n';
    } //This actually references programName rather than getting a copy of it

    //Another example of wher return by reference is useful is in returning
    //parameters that were given. For instance

    const std::string& firstAlphabetical(const std::string& a, const std::string& b) {
        return (a < b) ? a : b;
    }

    void compareStrings() {
        std::string hello { "hello" };
        std::string world { "world" };

        std::cout << firstAlphabetical(hello, world);
    }

    int& max(int& x, int& y) {          
        return (x > y) ? x : y;
    }    

    void compareMax() {
        int a{ 5 };
        int b{ 6 };

        max(a, b) = 7;
    }
}

void chapter912() {
    //Type deducation with pointers, references, and const

    //By default auto drops doubles

    const double foo{ 5.0 };
    const double bar{ 6.0 };

    auto x{ foo };
    auto y{ bar };

    //This can be reapplied by stating const with the auto

    const auto a{ foo };
    const auto b{ bar }; 

    //The same is true for references

    auto ref1 { chapter911::firstAlphabetical("hello", "world") }; 
    //The code above is not a reference anymroe as intended by the functon 
    //line 264

    auto& ref2 { chapter911::firstAlphabetical("hello", "world") }; 

    const auto& ref3 { chapter911::firstAlphabetical("hello", "world") }; 
    //Top and low-level cos reapplied. One implicitly and one through reference

    std::string originalString{ "When the wind is slow, when the fire's high" };
    std::string* stringPtr{ &originalString };

    auto ptr1{ stringPtr };
    auto* ptr2{ stringPtr }; 

    //Both of the above are valid as auto immediately deduces pointers
}
int main() {
    chapter911::compareStrings();
    return 0;
}