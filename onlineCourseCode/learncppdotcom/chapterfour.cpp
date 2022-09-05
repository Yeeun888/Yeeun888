#ifndef IO_STREAM
#define IO_STREAM
#include <iostream>

#endif

#include <iomanip>
#include <stdint.h> //For fixed size headers
//#include <cstdint> is also usable instead of <stdint.h> to go through std namespace
//Beginning Note: Chapter 3 was filled with strategies on debugging and thus has not notes

void chapter43() {

    //Add sizeof() to display the size and use of each

    std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
    std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
    std::cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes\n";
    std::cout << "char16_t:\t" << sizeof(char16_t) << " bytes\n";
    std::cout << "char32_t:\t" << sizeof(char32_t) << " bytes\n";
    std::cout << "short:\t\t" << sizeof(short) << " bytes\n";
    std::cout << "int:\t\t" << sizeof(int) << " bytes\n";
    std::cout << "long:\t\t" << sizeof(long) << " bytes\n";
    std::cout << "long long:\t" << sizeof(long long) << " bytes\n";
    std::cout << "float:\t\t" << sizeof(float) << " bytes\n";
    std::cout << "double:\t\t" << sizeof(double) << " bytes\n";
    std::cout << "long double:\t" << sizeof(long double) << " bytes\n";
}

void chapter44() {
    //Integers contain a bit describing their positive/negative state
    //which makes them "signed" integers

    //Default integer types which are signed:
    short s;        //16 
    int i;          //16
    long l;         //32
    long long ll;   //64

    /**
     * Unsigned integers are not good to use in general as they generate 
     * unpredictable results 
     */
}

void chapter45() {
    //Integers can be unsigned, meaning they can hold only poositive values
    //Now instead of 2^(n-1) they can hold 2^n-1 values

    unsigned short us;
    unsigned int is;
    unsigned long ul;
    unsigned long long ull;

    //The occasional unsigned is good to improve performance and leverage it's well
    //defined behavior
            
}

void chapter46() {
    //C99 defined set of fixed-width integers 

    int8_t i = 124; 

    //Fast (performance) and least (smallest) types of integers
    int_fast16_t fast16 = 31000;
    int_least16_t least16 = 31000;

    std::cout << sizeof(fast16) <<  " and " << sizeof(least16);
}

void chapter48() {
    //Interesting about floating point numbers 
    //#define FLOATDEMO
    #ifdef FLOATDEMO
    //Smallest space complexity to largest
    float fValue{0.004};
    double dValue{0.6689};
    long double ldValue{12034914.1595};

    //use f to denotate float literal. Double is still best though
    float x{5.0000005f};
    double y{5.0000005};

    std::cout << std::setprecision(16);
    std::cout << x << "and" << y << '\n';

    //Demonstrationg literal percision
    std::cout << 9.87654321f << '\n';
    std::cout << 9.87654321;
    #endif
    //NaN and INF

    #define NANIF
    #ifdef NANIF

    double zero {0};
    double posinf {5.0 / 0};
    std::cout << posinf << '\n';

    double neginf {-5.0/0};
    std::cout << neginf << '\n';

    double nan{zero / zero};
    std::cout << nan << '\n'; //means Not a Number (NaN)

    #endif

}

void chapter49() {
    //bool demonstration

    bool tr{1};
    bool fal{0};

    std::cout << tr << " and " << fal << '\n';
    std::cout << std::boolalpha;
    std::cout << tr << " and " << fal << '\n';

    //Important note: when accepting values through cin they are only (1 and 0)
}

void chapter410(bool tf) {
    //if statements
    if (tf == 1) 
        std::cout << "it is true";
    else 
        std::cout << "it is false";
    //Using curly braces can be ommited if the executed statement is one line
}

void q1chapter410() {
    std::cout << "Enter a number through 1 to 9: ";

    int input{};
    std::cin >> input;

    if(input == 2)
        std::cout << "It is a prime";
    else if(input == 3)
        std::cout << "It is a prime";
    else if(input == 5)
        std::cout << "It is a prime";
    else if(input == 7)
        std::cout << "It is a prime";
    else 
        std::cout << "It is not a prime";

}

void chapter411() {
    //characters
    char ch2{'a'};
    char ch1{97};

    //When dealing with a string like input char operator<< std::cin will buffer 
    //all the characters
}

void chapter412() {
   //Side note: int8_t and uint8_t have same bytes as characters and thus can be convered
   float x{5.0};
   x = static_cast<int>(x);

   std::cout << x; 
}

void q1chapter412() {
    std::cout << "Enter a single character: ";

    char intTest = {};
    std::cin >> intTest;

    std::cout << "You entered '" << intTest << "', which has an ASCII code " << static_cast<int>(intTest);
}

void chapter413() {
    //Const prevents the variable ever from being changed.  
    const int age { 30 };
    
}

void chapter414() {
    const int cint{ 5 }; //cint cannot be changed anymore. This is an optimization

    //Expressions that are constant can use constexpr

    constexpr int sum{ 4 + 5 };
    constexpr int something{ sum }; 
    //this is constexpr because all of the initilizers are known at compiletime
    //Unknown intitilizers at compile time will throw an error
}

void chapter415() {
    float f{ 4.1f }; 
    //Letters behind "usually" numbers denotate what they literally represent
    //such that floats are not inserts into integers, or doubles into floats, etc.
    
}

void chapter416() {
    //There are 4 primary numerical systems avaiable in cpp:
    //Decimal (10), Binary (2), Octal (8), and Hexadecimal (16)

    //How to prefice value types for values
    
    int x{ 012 }; //the 0 before represents octal
    int y{ 0xFFA45}; //the 0x represent hexadecimal
    int z{ 0b0100'1001}; //0b represents binary 

    //Important Note: 0b is a C++14+ feature 
    //Quotation marks (') can also be used to spaceout binary values except in the beginning

    //Likewise modifiers can be used to manipulate io
    //For instance:
    std::cout << std::hex << x << '\n';
    std::cout << std::oct << z << '\n';

    //Binary values are different 

    #include<bitset>

    std::cout << std::bitset<8>{0b10100001} << '\n';

    //std::bitset is a type

    std::bitset<4> bin1 { 0b1100 };

}

void chapter417() {
    //Notes on std::string;

    //Taking string input with std::cin can not take whitespace and will buffer
    //instead use std::getline

    std::cout << "Please enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws , name);
    
     //Read a full line of text into name
     //std::ws is a function modifier that changed std::cin

    std::cout << name.length(); //Fucntion name for str length
    //length is what we call a member class
}

void chapter418() {
    //c++17 feature right here
    //when displaying strings through pointers they are copies of the same string
    //therefore are considered inefficient

    //We can use std::string view as a read-only way of accessing strings
    //this also makes no copies of the initial string

    #include <typeinfo>

    std::string_view s{ "this is a string" };

    std::cout << s << '\n';

    std::string sconv = static_cast<std::string>(s);

    std::cout << sconv << '\n';

    std::cout << typeid(s).name() << " and " << typeid(sconv).name();
}


int main() {
    chapter418();
    
    return 0;
}

