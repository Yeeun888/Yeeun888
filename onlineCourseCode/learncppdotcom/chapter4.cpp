
#ifndef IO_STREAM
#define IO_STREAM

#include <iostream>

#endif

#include <cstdint>
#include <iomanip> // for output manipulator std::setprecision()


//*Each variable has a diferent size with different characteristics
void typeOfVariablesWithSize() {

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

//* Signed numbers have a signed (+/-) and unsigned are only positive
void signedAndUnsigned() {
    signed int x;   
    unsigned int y; //cannot contain negative numbers

    //! Unsigned is generally bad practice as negative numbers wrap around
    //! to positive numbers making errors hard to diagnose
}

//* Integers can be created based on the fastest or least space based on the system
void integerTypes() {
    //Creates integer with least space possible on a system
    std::cout << sizeof(std::int_least8_t) << std::endl;
    std::cout << sizeof(std::int_least16_t) << std::endl;
    std::cout << sizeof(std::int_least32_t) << std::endl;
    std::cout << sizeof(std::int_least64_t) << std::endl;

    //Creates an integer that is fastest on the system
    std::cout << sizeof(std::int_fast8_t) << std::endl;
    std::cout << sizeof(std::int_fast16_t) << std::endl;
    std::cout << sizeof(std::int_fast32_t) << std::endl;
    std::cout << sizeof(std::int_fast64_t) << std::endl;

    //For system specific integers you can use std::size_t
    std::size_t exampleVariable{ 1 };
    //std::size_t is used to represent the size of things in memory. Such as 
    //array increments or sizes
}

//*Numbers can be stored precisely with floating points
//*however, they are not completely precise
void floatingPoints() {
    //First line is an integer, second line is a float
    std::cout << 5 << '\n';
    std::cout << 5.01f << '\n';

    //Precision is defaulted to 6 however that can be changed

    std::cout << 5.12345678f << '\n';
    std::cout << std::setprecision(10);
    std::cout << 5.12345678f << '\n';

    //floating points are not entirely accurate when it comes to super small decimals
    //resulting in rounding errors. 

    //rounding error example
    std::cout << std::setprecision(19);
    double d1{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1};
    std::cout << d1 << '\n';

    //Generating NaN and INF
    std::cout << 5.0/0 << '\n';
    std::cout << 0.0/0.0 << '\n'; //must be floating point.
                                  //division of "int 0/ int 0" results in 0
}

//*Bools are an integral type that store true or false
void boolExamples() {
    bool a{0}; //false
    bool b{1}; //true

    std::cout << "Variable a is " << a << " variable b is " << b << '\n';
    std::cout << std::boolalpha;
    std::cout << "Variable a is " << a << " variable b is " << b << '\n';

    #if 0
    std::cout << std::noboolalpha; //is used to turn true and false back to 0 and 1.
    #endif
}

//*Chars represent characters in ASCII and remain 
void charExamples() {
    //Char can store based on ASCII or direct characters
    char a1{'a'};
    char a2{98};

    //There are other chars other than \n that are useful
    std::cout << "item1\titem2\titem3" << '\n';
    std::cout << "item4444\titem5\titem666" << '\n';
}

//*Converting between different data types can be done with static_cast<type>()
void convertToType() {
    char a1{'a'};
    std::cout << static_cast<int>(a1) << '\n';
}

//*Variables can be made constant with the const keyword
//return variables should not be made const as it makes programs slower
void constVariable(const std::string inputText) {
    /**
     * inputText = "changed text here""" 
     * ^the line above will create an error
     */

    const int a{ 1 };
    const int b{ 2 };

    //a, b, and inputText cannot be changed
    constexpr addedVariable{ a + b }

    //Anything const and constexpr will always be evaluated at COMPILE-TIME
    //hence why it is more optimized. a+b will always evaluate to 3. There is
    //no use in the machine doing it over and over again when the program is
    //run
}

//*There are binary, hex, octal forms of numbers. That's it
void numberSystemNotes() {
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

//*Std::string input has to use std::getline
//std::cin cannot take whitespace and therefore buffers input because of it
void stringInput() {
    //example program that uses this 
    std::cout << "Enter you name: \n";
    std::string name{};
    std::getline(std::cin >> std::ws, name); //Reads a full line and 
                                             //inserts it into name

            //std::ws avoids leading whitespaces such as the \n when
            //entering to put input into the program
}

// When variables are passed around in cpp they are copied again into a new
// memory location. 
//*As strings are large variables, using string_view prevents new copies from 
//*being made. Instead referncing the location of the string directly. 
void stringView() {
    std::string_view exampleString{ "This is an example string" };
    std::cout << exampleString;

    //Here std::cout just prints exampleString instead of making an unnamed
    //copy to print again
}

int main() {
    convertToType();
    return 0;
}