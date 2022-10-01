#include <iostream>
#include <string_view>
#include <array>
#include <vector>

struct Rectangle {
    int length{};
    int width{};
};

void chapter111() {
    //chapter 11.1 on Arrays - Part 1

    //Array syntax
    int studentTestScores[30]{}; //Allocate 30 integers of space in an array
    double doubleScores[30]{}; //Allocate 30 double spaces in an array

    Rectangle rectangleCollection[5]{}; //An array of 5 rectange structs

    //note: the length of an array has to be a compile-time integer constant
}

enum StudentNames {
    kenny,
    kyle,
    stan,
    butters,
    budiman,
    max_students, //To represent the array size
};

//As to avoid poluting the namespace there are two things that can be done
//1. Put StudentNames inside a namespace
//2. Put them in an enum class. However, enum class doesn't allow for implicit
//   integer conversion. So overcome this with a static_cast.

void chapter112() {
    //Arrays can also be made without a strict definition of length
    //This concept saves time typing

    int testScores1[]{ 1, 4, 5, 7, 10 };

    int testScores2[max_students]{};
    testScores2[kenny] = 69;
}

//The contents of 11.4 can be seen in a different file

void chapter115() {
    //Multidimensional Arrays

    //Initialize with two subscripts

    int array[3][5]; //A 3 x 5 array, 3 is the rows and 5 is the columns
                    //cpp is row-major 

    //Size can also be automatically detected with entering one of the dimensions

    int array2[][4] {
        {1,2,3,4},
        {1,2},
        {3,3,4} //However one of them have to be filled. 
    };
}

void chapter116() {
    //C-style strings. A very interesting deprecated version of strings

    //Example of a C-style string. 

    char myString[]{ "Hello this is a string" };

    //These strings work much like arrays in the form of characters and can be
    //seen through printing them in a loop

    const int length{ static_cast<int>(std::size(myString))};

    for(int i{ 0 }; i < length; i++) { //Prints all ASCII characters
        std::cout << static_cast<int>(myString[i]) << ' '; 
    }

    //Important C-style string functions
    //Char[4]{ "this is a c-style string" }; generates an error for index overflow

    //Getting input
    //std::cin can get an unlimited amount of character. However because of
    //the limit impossed by c-style strings, it is impossible to get. 

    char name[255] {};
    std::cout << "Enter your name: ";
    std::cin.getline(name, std::size(name)); //Get 255 characters before deleting
                                             //the rest of the characters

    int strLength{ static_cast<int>(std::strlen(name)) };
    int strSize{ std::size(name) };

    //Useful functions for c-style strings
    //strcpy, strncat, strncmp
    //Look up documentatioon if necessary
}

void chapter117() {
    //String_view
    //std::string behaves a little bit like a compile-time constant such that,
    //it makes a copy of itself during initialization. Truth be told,
    //std::string does not know what the user initialized the std::string with
    //as such the data could disappear, not-exist, or even be invalid. 
    //
    //As such C++ does the only sane thing and copy that data for itself. This
    //guarantees functionality, data integrity, and behavior

    //However these behaviors are expensive as the string is being consistently 
    //copied around. Hence why std::string_view exists for read-only cases. 
    
    std::string_view str{ "Here is a read only string" };

    std::cout << str << '\n';
    //string_view also has many of the functions we are familiar too with string
    std::cout << str.length() << '\n';
    std::cout << str.substr(0, str.find(' ')) << '\n';

    //For legacy systems strings can be converted back to c-style

    std::string realString{ str }; //Have a temporary string_view to string
    auto cString {realString.c_str()};

    //Function to modify string_views and get a c-style string instantly.
    //Use data() function 
    std::cout << std::strlen(str.data()) << '\n'; 

    //This converts it into a c-style string that can utilize C-style functions
}

//void printSize(int array[]) does the same thing. There is no difference here
void printSize(int* ptrArray) {
    std::cout << "The size of the array is " << sizeof(ptrArray) << '\n'; 
}

void chapter118() {
    //Pointers and fucking arrays
    //Most important information here is that all arrays decay into pointers
    //of the first variable that they have.

    int array[5]{ 1,2,3,4,5 };

    //Concept demonstration
    std::cout << &array[0] << '\n';
    std::cout << array << '\n';

    //As arrays are depreciated into pointers, they cannot do "normal" array
    //functions. Passing the array, dereferencing it, and such will result in 
    //array specific behaviors.

    //For instance,
    std::cout << "This is the size of an array " << sizeof(array) << 
    " and the pointer " << sizeof(&array) << '\n';

    //This is an important concept as arrays are typically passed to functions 
    //as pointers themselves

    printSize(array);

    //Note: Array in structs and classes do not decay. The more you know.
}

void chapter119() {
    //Pointer arithmetic (very interesting indeed)

    //Pointers can do "integer operations" however in doing so it results in 
    //the pointers being added by the size of the data type it is holding.

    int x{ 5 };
    int* xPtr{ &x };

    std::cout << xPtr << '\n'; //All addresses are shifted by 4 as the size of
    std::cout << xPtr + 1 << '\n'; //int is 4 bytes
    std::cout << xPtr + 2 << '\n';
    std::cout << xPtr + 3 << '\n';

    //This is best demonstrated with an array
    int array[5]{ 1,2,3,4,5 };

    //Arrays are laid out sequentially in memory so 
    std::cout << "Element 0 is at address: " << &array[0] << '\n';
    std::cout << "Element 1 is at address: " << &array[1] << '\n';
    std::cout << "Element 2 is at address: " << &array[2] << '\n';
    std::cout << "Element 3 is at address: " << &array[3] << '\n';

    //Pointers can thuse be used to iterate through an array and then be dereferenced
    //Here is an example

    int length{ std::size(array) };
    for(int* pos = array; pos != (array + length); pos++) {
        std::cout << *pos;
    }
}

void chapter1110() {
    //to be completely honest I have no clue what this chapter does

    //The purpose of this chapter is to illustrate the difference between
    //how std::cout treats c-style string literals and arrays

    int nArray[]{ 1,2,3,4,5 };
    char cArray[]{ "Hi there" };
    const char* name{ "Alex" };

    std::cout << nArray << '\n';
    std::cout << cArray << '\n'; //Doesnt decay into pointers
    std::cout << name << '\n';

    //When it comes to working with pointers and characters be careful as it
    //can lead to unintended effects./
}

void chapter1111() {
    //Dynamic memory allocation
    //Dyanmic memory allocation allows the OS to decide to size of memory
    //allocated to an object. This is done thorugh the keywords 'new' and 
    //'delete'

    //Previous lessons used statically allocated or automatic allocation. Both
    //required some form of information on the size of the object being allocated

    int* ptr1{ new int };

    //Here the pointer acts as an access point towards the object
    *ptr1 = 3;

    //They can also be directly initialized
    int* ptr2{ new int{ 5 } };

    //Deleting the "contents" instead of the actual memory itself
    delete ptr2;
    delete ptr1;

    //Dangling pointers and memory leaks demonstration. Do not run.
    #ifdef DANGLING_POINTERS

    //Now that ptr1 and ptr2 are deleted try are dangling pointers. 

    std:;cout << *ptr; //Results in undefined behavior
    int* secondPtr{ ptr1 }; //Also a dangling pointer as ptr1 has no address;

    //To avoid this use nullptr
    ptr1 = nullptr;
    ptr2 = nullptr;

    {
        int* ptr3{ new int{} };
    }
    //Now ptr3 is out of scope and so the address that ptr3 held is now 
    //permanently lost. This is called memory leak. 

    //Basically allocating memory without deleting it results in memory leaks 
    //if replaced such as.

    int* ptrLeak{ new int{} };

    int value{ 5 };
    ptrLeak = &value; //A leak since old memory is lost
    ptrLeak = new int{}; //Also a leak since old new int is lost

    #endif

    //Failure of new
    //If the OS does not have enough memory new can fail in rare instances
    int* value1 { new (std::nothrow) int }; //becomes nullptr is there is it cannot
                                            //be allocated. 
}

void chapter1112() {
    //Dyamically allocating arrays. Allowing arrays to immediately work on runtime

    std::cout << "Enter a positive integer: ";
    int length{};
    std::cin >> length;

    int* array{ new int[length]{} };

    delete[] array; //Using array form of new and delete a.k.a new[] and delete[]
}

//short program for 11.12 Q1 no need for a new file

void program1112() {
    std::cout << "How many names would you like to enter? ";
    
    int names{};
    std::cin >> names;

    //Dyanamically allocate an array
    auto* array{ new std::string [names]{} };

    for(int i { 1 }; i <= names; ++i) {
        std::cout << "Enter name #" << i << ' ';
          
        std::cin >> array[i];
    }

    std::sort(array, array + names);
    
    for(int i { 0 }; i <= names; ++i) {
        std::cout << array[i];
    }

    delete[] array;
}

void chapter1113() {
    //Using for each loops. Basically the equivalent for looping in range in py
    constexpr int scores[] { 84, 54, 99, 21, 43 };
    int maxScore{ 0 };

    for( auto score : scores ) {
        (maxScore < score) ? maxScore = score : NULL;
    }

    std::cout << maxScore;

    //Notes:
    //for each loops can be used on non-array objects which can be iterated through
    //for each loops don't work with pointers to arrays (as they are now pointers)
    //as of cpp20 init statements can be added in the beginning

    //CPP20 standard
    /**
     * for(init-statement; element name : looped object) {
     *     statement inside
     * }
     * 
     */
}

int program1113() {
    constexpr std::string_view names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holy"};

    std::cout << "Enter a name: ";
    std::string inputName{};
    std::cin >> inputName;

    for( auto name : names ) {
        if(name == inputName) {
            std::cout << name << " was found.";
        }
    }

    return 0;
}

void chapter1114() {
    //Void pointers. Thank God this chapter is much easier

    //Void pointers are pointers that "do not know" or specify rather what is the
    //type of object it is pointing towards

    int value{ 5 };
    void* ptr{ &value };

    //The nature of void pointers does not allow it to do pointer arithmetic
    //or dereferencing

    //Dereferencing has to be done with static_cast

    std::cout << *static_cast<int*>( ptr );
}

void chapter1115() {
    //Welcome to hell

    //Pointers to pointers. Yes. 

    int value{ 5 };
    int* ptr{ &value };
    int** ptrptr{ &ptr }; //got it?

    //Useful for dynamically allocating an array of int pointers

    int** array{ new int*[10] }; 
    delete[] array;

    //It can also be used to dynamically allocate a two dimensional array. 
    //however the process is much more complex.

    //dynamically allocate a 1 dimensional array before expanding it with a loop

    int** array1 { new int*[10] }; //Rows, this code is sort of placeholder
    for(int count{ 0 }; count < 10 ; ++count) {
        array1[count] = new int[5]; //Columns
    }
    //10x5 dynamically allocated array

    //Deleting them is also required to be done in a loop as each column is an
    //independent array

    for(int count{ 0 }; count < 10; ++count) {
        delete[] array1[count];
    }
    delete[] array1;
}

template<typename T, std::size_t size> 
void printArray(const std::array<T, size>& myArray); //Function forward declaration

void chapter1116() {
    //Using std::array

    //std::array is used for creating arrays that don't decay into pointers
    std::array<int, 3> myArray1 { 1,2,3 };

    //The type and size are essential. They have to be part of the syntax.

    std::array myArray2 { 1,2,3 }; //Type and size deduction can also be done

    //arrays also support at and size functions
    myArray1.at(0) = 3; //Change integer at index 0 to 3
    std::cout << myArray1.size() << '\n'; //Is type size_t not int!

    //std arrays also don't decay and can be passed to functions
    //however, the size and type are all essential part of an array's information.
    //Therefore templates can be used
    printArray(myArray1);
    
    struct House {
        int number{};
        int stories{};
        int roomsPerStory{};
    };

    //structs can be initialized into the forms of arrays always use an extra set
    //of braces you dumb fuck dogshit language

    std::array<House, 3> houses {
        {
            { 13, 4, 30 }, 
            { 14, 3, 10 }, 
            { 15, 3, 40 } 
        }
    }
}

template<typename T, std::size_t size> //object type and size of array
void printArray(const std::array<T, size>& myArray) { //it is a reference
    for(auto element : myArray) {
        std::cout << element << ' ';
    }

    std::cout << '\n';
}

int main() {
    chapter1116();
    return 0;
}
