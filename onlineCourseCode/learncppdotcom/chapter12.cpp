#include <iostream>
#include <vector>
#include <cstdarg>
#include <array>

int sampleFunc() {
    std::cout << "Hello World";
    return 0;
}

int foo() { return 1; }
int bar() { return 2; }

void callFunction(int (*returnIntFunction)()); //Forward delcaration for function.

void chapter121() {
    //Chapter 12.1 on function pointers. Very interesting!
    //Function pointers are used for the purpoose of 

    //Normal function calls are just jumping to a specific address of memory
    int (*samplePtr)()(&sampleFunc);
    //pointer to function samplePtr points to sampleFunc takes no parameters and returns int

    //Calling a function with pointers
    (*samplePtr)(); //Call sampleFunc through samplePtr

    //Functions can also be passed as arguments through this method. Such as below.
    callFunction(bar);

    //However all of this is very tedious so using std::function is much more helpful
    std::function<int()> stdPtr{ &sampleFunc };
}

void callFunction(int (*returnIntFunction)() = foo) { //Provides a default function
    std::cout << returnIntFunction() << '\n';
}

//Alternateive callfunction with using
using intFunction = int (*)();
void callFunction_using(intFunction func) {
    std::cout << func << '\n';
}

int callMe() {
    return 0;
}

void chapter122() {
    //Understanding the behavior of the call stack and heap.

    //The heap is where aall dynamic memory allocation is done. Fairly striaght
    //forward.

    //The call stack is a fast way of allocating memory in a stack form. It follows
    //a first in last out (LIFO) type of behavior. 

    //A call stack happens when functions are called. This includes the location of
    //memory of the function and the variables that are passed through. Passing 
    //value is typically results in the value going through the call stack. 

    callMe(); //Call me is added to the call stack.

              //one the program finishes it exits here back and is removed form the stack

}

void chapter123() {
    //12.3 std::vector and stack behavior usage. 

    //Vectors can be inspected based on length and capacity. Here is a demonstration

    std::vector array {0, 1, 2};
    std::cout << "Vector size: " << array.size() << " Vector capacity: " << array.capacity() << '\n';
    array.push_back(3); 
    array.push_back(4);
    std::cout << "Vector size: " << array.size() << " Vector capacity: " << array.capacity() << '\n';
    array.pop_back();
    array.pop_back();
    std::cout << "Vector size: " << array.size() << " Vector capacity: " << array.capacity() << '\n';

    //Note that capacity does not always follow size. It is resized as needed.
    //Vectors can also be used to display stack behavior using the functions:
    //push_back(), pop_back() which inserts and removes an element respectively. 
    //with back() which displays the top element. 

}

//Example function used in the call stack
void countDown(int count) {
    std::cout << "push " << count << '\n';

    if(count > 0) {
        countDown(count - 1);
    }

    std::cout << "pop " << count << '\n';
}

void chapter124() {
    //Recursion, the call stack hell

    //Recurrision floods the call stack with information and halts execution order.

    //This is better demonstrated with recursion on the function above. 
    countDown(5);
} //fuck recursion

void chapter125() {
    //Available in testprograms
}

void chapter126(int a, ...) {
    //Using ellipsis
    std::va_list list;

    va_start(list, a); //A represents the amount of expected variables

    for( int i{ 0 }; i < a; ++i ) {
        std::cout << va_arg(list, int) << ' '; //Access using va_arg
    }

    va_end(list); //clean this up xDDD
}

void chapter127() {
    //Using Lambda functions (i.e. anonymous functions)

    constexpr std::array<std::string_view, 4> testArray{ "Apple", "Banana", "Walnut", "Lemon" };
    const auto found { std::find_if(testArray.begin(), testArray.end(), 

    [](std::string_view str){ return (str.find("nut") != std::string_view::npos);
    
    })};

    //Example function to find something with nut

    /**
     * [ Capture-clause ] ( parameters here ) { function body }
     */

    
}

void chapter128() {
    //Lambda captures
    //Capture clauses allow the lambda to access local variables 
    //By nature Lambda's don't have access to local variables

    std::array<std::string, 4> msg{ "this", "is", "a", "message" };
    std::string str{ "is" };

    auto found{ std::find_if(msg.begin(), msg.end(), [str](std::string testStr){
        return (testStr.find(str) != std::string::npos);
    }) };

    std::cout << *found;
    
    //Madify values(that are copied by the lambda) directly with mutable i.e
    // []() mutable { //insert code };

    //Capture by refernce demonstration

    int y{ 0 };

    //Decrement by one
    auto increment{ [&y](){ ++y; } };

    increment(); increment(); //call the lambda twice

    //Captures can also be automatic with [=] and [&]
}

int main() {
    chapter128();
    return 0;
}