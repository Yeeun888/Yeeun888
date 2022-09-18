#include <iostream>
#include <typeinfo>

void chapter81() {
    //Chapter 8.1 
    //Implicit Type Conversion
}

namespace n_chapter82 {
    //Numertic Proportions
    //Promotions from one type of number to another

    void printDouble(double d) {
        std::cout << d << '\n'; 
    }

    void printInt(int d) {
        std::cout << d << '\n';
    }
}

void chapter82() {
    //Numeric PROMOTIONS 8.2
    n_chapter82::printDouble(5.0);
    n_chapter82::printDouble(4.0f); //Requires float to double conversion

    n_chapter82::printInt(2);

    short s{ 5 };
    n_chapter82::printInt(s);       //short to int
    n_chapter82::printInt('a');     //char to int
    n_chapter82::printInt(true);    //bool to int
}


void chapter83() {
    //8.3 - Numeric CONVERSIONS
    //Basically converting shit to double or ints

    //Most important is narrowing conversions which drop specific parts of data
    int i1 = 3.5; //.5 elemtn is dropped
    int i2 = 3.0; //no data is technically lost

    //It is important to note that brace initilization disallows narrowing
    //conversions

    //IMPORTANT TAKEAWAYS 
    //1. Converting type into another with an unsupported range results in
    //undefined behavior

    int i{ 30000 };
    char c = i; //Char has range of -128 to 127

    std::cout << static_cast<int>(c);

    //2. Converting from larger integral type to smaller will work
    //as long as the final value still fits inside

    int j{ 4 };
    short k = j;

    std::cout << j; //No information is lost here.
}

void chapter84() {
    //Arithmetic Operators

    /**
     * In short there are operators that require operands to be of the same type
     * Typically what happens is that those operators convert the non same type
     * into the appropriate type. Conversion follows a set of priorities.  
     * 
     * ex = long double + int
     * 
     * since '+' operator requires same operands
     * then the int is turned into a long double (which has the highest priority)
     */

    //#include <typeinfo> is used for typeid().

    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; //show type
}

void chapter85() {
    //Explicit conversions
    int i = 10;
    int j = 4;
    
    //C-style casts (which should be avoided)

    double d = double(i)/j;
    //or (double)i/j; also works

    //Static cast is better because it avoids erros

    double e { static_cast<double>(i)/j };
    
}

void chapter86() {
    //defining how to work 

    //typedefs and type aliases are used to classify types of variables
    using Distance = double;
    //Distance can now be used as an alternative to double
    
    /**
     * Identical statement with typedef
     * 
     * typedef double Distance; 
     * 
     */

    Distance flightHeight{ 100 };

    //type alias is also used to make hard types easy to read
    using VectPairSI = std::vector<std::pair<std::string, int>>;

    //vectors can be used for backwards compatibility
}

void chapter87() {
    //Type deduction
    //using the auto keyword

    auto i = {3.0};

    //Auto is also useful incase functions that add to the variable 
    //turn it into a double or something else
}

auto autoFunction() {
    //type deductions for functions
    //auto as a keyword can be used to automatically deduct from a functions return
    //value

    if (true) {
        return 1;
    } else {
        return 0;
        /**
         * Important note. All return statements of the function must be of the 
         * same type so that the function will not return an error 
         * 
         */
    }
    
    //second important note: Functions cannot be forward declared

    return 0;
}

//Introduciton to function overloading 8.9 - 8.11

//Example of overloaded function

int add(int x, int y) {
    return x + y;
}

double add(float x, float y) {
    return x + y;
}

//Compiler can differentiate function based on the use of different parameters.

/**
 * A function can be differentiated with the compiler with:
 * 1. No of parameters
 * 2. Types of parameters (excluding typefers, alias, and const)
 * 
 * However cannot be differentiated based on return type.
 */

//Functions are also subject to overload resolution where 

//function overloading
//1. find matching functions
//2. no matching functions then convert through numeric promotions
//3. else use numeric ocnversion

//Shit don't get
//4. Function looks for objects based on class templates
//5. Ellipsis functions

//Resolving ambiguous matches can be done by static_casting the function 
//parameters

void print(int x, int y=10) {
    std::cout << "X is " << x << "and Y is " << y;
}

//NOTES ONLY RIGHT MOST VARIABLES CAN BE DEFAULTED
//void print(int x = 50, int y) is illegal)

void callPrint() {
    std::cout << "default print \n";
    print(5);
    std::cout << "modified print \n";
    print(5,40);
}

//CHAPTER 8.13 - TIME FOR TEMPLATES HEHEHEHE

template<typename T> T max(T x, T y) {
    return (x > y) ? x : y;
}

//the code above is the example of one such template, this template can then be
//called over and over again to generate the same function for different types
//of variables

//EXAMPLE non-standard templates
template<typename z> int nonStandardFunction(z var, double y) {
    return int(z + y);
}

//Templates can also have multiple typenames
template<typename A, typename B> auto maxNew(A x, B y) {
    return (x > y) ? x : y;
}
//things to notice in this
//1. there are two typenames such that if maxNew was called with int and float
//the comiler would not be confused and distrubute use one of the two variables
//for the function.

//2. The function return type is auto. Since if it were int, the return function
//would promote the answer to float and it would push an error to the function.
//Using auto helps avoid this issue

//3. There is no data lost here in this type of operation

void generateTemplates() {
   std::cout << max<int>(2, 3) << '\n'; 
   std::cout << max(2, 3) << '\n'; 
   //note that calling the template without a type of variable still works. 
   //this is because the compiler can perform argument deductuion for types
   //depending on the variables that were added. 

   //also possible
   std::cout << max<>(2, 3) << '\n'; 

   //This will call a function max() if it is made available (not the template)
   //this is always much preferred. 

    //FUNCTIONS WITH NON TEMPLATE PARAMETERS
    nonStandardFunction(1, 3.4);
    nonStandardFunction(1, 3.4f); //float can be promoted to double.
    nonStandardFunction(1.2f, 3.4f); //float is once again promoted
    
}

int main() {
    chapter84();
    callPrint();
    return 0;
}