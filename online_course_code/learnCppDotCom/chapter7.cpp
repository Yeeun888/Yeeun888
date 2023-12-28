#include <iostream>
#include <random>
#include <chrono>

void chapter72() {
    //If statements and blocks

    //Best note is becareful of scopes involved in if statements

    if(true)
        int x{ 5 };
    else 
        int x{ 6 };

    //However because blocks are implicitly inserted then it means that as
    //the statement executes, there is no X.
}

namespace chapter74 {
    int printDigitName(int x) {
        switch (x) {
            case 1:
                std::cout << "this is one";
                return 0;
            case 2:
                std::cout << "this is two";
                return 0;
            case 3:
                std::cout << "this is three, here we break!";
                break; //Go to end of switch block meaning
            default:
                std::cout << "default";
                return 0;

            //Using case allows for scaling of if statements very quickly.
        } 
        //After break code execution begins here 
        return 0;
    }    
}

namespace chaper75 {
    int programFallthrough(int x) {
        switch(x) {
            switch(x) {                 //If switch receives 2 it will go to 2
                case 1:                 //and print 2, 3, 4, 5
                    std::cout << "1";   //this is called fallthrough
                case 2:
                    std::cout << "2";
                    [[fallthrough]]; //Indicate intentional fallthrough as to
                case 3:              //to not raise compiler warning
                    std::cout << "3";
                case 4: {
                    int testVar{ 5 }; //Variables defined in block!
                    std::cout << "4";
                }
                case 5: 
                    std::cout << "5";
            }
        }

        return 0;
    }
}
    
void chapter76(bool skip) {
    //Goto statements 
    //It is worth nothing that these statements are considered bad practice as they
    //are unoptimized in many ways.

    tryAgain:
    
    if (skip == false) {
        
        std::cout << "Please give me a truth. \n";
        goto tryAgain;
    }
    
    std::cout << "Finally it's true!";

    /**
     * goto skip; 
     * 
     * int x { 5 }; DON'T SKIP OVER UNINITALIZED VARIABLES! This causes errors
     *              and is considered illegal. 
     * skip:
     * 
     * x += 3;      God knows what the answer to this would be. 
     * 
     */
}

int chapter77(int level) {
    //Demonstration of while loops
    
    for(int lateral = 1; level >= lateral; ++lateral) {
        
        int range{ lateral };
        int count{ level };

        while(count > 0) {
            if(count <= range) {
                std::cout << count << ' ';
            } else {
                std::cout << "  ";
            }
            --count;
        }

        std::cout << '\n';
    } //bro this shit is a work off art go fuck urself learncpp.com
    #ifdef LOOP1
    while(level > 0) {
        for(int baselength = level; baselength > 0; --baselength) {
            std::cout << baselength << ' ';
        }

        std::cout << '\n';
        --level;
    }
    #endif

    return 0;
}

void chapter78() {
    /**
     * Do-while loops
     * Are useful when something has to be evaluated atleast once before running 
     * or checking a conditional.
     */
        // selection must be declared outside of the do-while so we can use it later
   
    int selection{};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection != 1 && selection != 2 &&
        selection != 3 && selection != 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';
}

void chapter79() {
    //For statements 
    
    /**
     * for(init statement; conditional to continune; success statement) {
     *     add code here!
     * } 
     * 
     */

    for(int i = 5; i > 0; --i) {
        std::cout << i << '\n';
    }

    //Dual variable loops using commas as a way of separating statements

    for(int x {0}, y{ 9 }; x < 10; ++x, --y) {
        std::cout << x << " and " << y << '\n';
    }
}

//Return vs Break vs Continue 
//Return immediately returns to the caller
//Break on the other hand only breaks the loop (while, for, do-while, etc)
//Continue breaks only one iteration of the loop before it happens again (conditionally)

void chapter711() {
    //using std::exit()
    #include <cstdlib> //to use std::exit 

    std::exit(0); //Explicitly stops execution of the program
                  //It is an issue as it does not clearup running variables
                  //so we use std::atexit(); instead

    //std::atexit(chapter77); //Example function, inside just add a function

    std::abort(); //causes program to terminal abnormally.
    
    //Addtional two ways of halting a program
    //but does not remove items from memory nor clean up anything
    //should be avoided
    
    std::terminate();
    std::abort(); //allow developers to restart program where it is stopped with memory information
}

/**
 * Notes section for chapter 7.13 - Code coverage 
 * 
 * Code coverage is the concept of how much code is covered during the 
 * execution of a function.  
 * 
 * 1. Loops are tested using the 0,1,2 method to test in respect for different
 * values
 * 
 * 2. Aim for 100% code coverage during testing
 * 3. Another concept is branch coverage where the whole block of code
 * can execute but does not go thorugh all possibilities
 * 
 * for instance:
 * 
 * if (x > y) { some code here } //testing for x > y would execute all the code
 * but what if x < y, then something else would occur!
 */

double chapter715() {
    //Error handling
    //unlike python error handling in cpp should be done with anticipation
    //and grit??

    int x{ 5 };
    int y{ 0 };

    if(y == 0) {
        std::cerr << "Error: Dividing by zero is illegal \n";
        //std::exit()
    }

    return static_cast<double>(x) / y;
}

void chapter716() {
    //Example invalid input

    std::cout << "Enter a double value: \n";

    double testD{};

    std::cin.ignore(100, '\n'); //Ignore upto 100 characters in bugger
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //means ignore maximum amount of characters.

    std::cin >> testD;
}

//Example program that handles bad input, non-conversion inputs

void ignoreLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble() {
    while (true) { //User is able to keep giving input until the program is called to exit
        std::cout << "Enter a double value: ";
        double x{};
        std::cin >> x;

        /**
         * Let's say the user puts an invalid input such as 'k' then the following
         * will happen 
         *
         * 1. it will put cin into "failure mode"
         * 2. K will be stuck in the buffer and thus will keep screwing us over
         * everytime we want to call an input 
         * 
         * thus we must check if std::cin failed with 
         * std::cin.fail() which is a boolean value for extraction success
         * 
         * however !std::cin is much more elegant and smart looking xD
         */
        
        if (!std::cin) { //meaning that it failed in some way
            std::cin.clear(); //get out of failure mode
            ignoreLine(); //removes the buffer that we already have
        } else {
            ignoreLine();
            return x;
        }
    }
}

/**
 * If std::cin is overflowed ex: entering 40,000 into std::int16_t then it will
 * assign the largest possible number and enter into failure mode. Other additonal
 * inputs are completely skipped and initialized with zero * 
 */

//Notes for CHAPTER 7.17 - ASSERTS AND STATIC ASSERTS

void getGravity() {
    float grav{};

    std::cout << "Give me the value of gravity: ";
    std::cin >> grav;

    assert(grav > 0.0 && "Gravity was found to be negative"); //careful performance penalty
    
    //Will raise an error given that gravity is more negative
    //btw this works because strings always evaluate to 1, when assert
    //is raised here this message will pop up as an error message.

    //Static_assert can be used as a compile-time check rather than run-time
    static_assert(sizeof(long) == 8, "long muyst be 8 bytes"); 

    //reoplace 8 with 9 to cause to program to crash
}

unsigned int chapter718() {
    //Introduction to Random Number Generation

    //Function basics:
    //1. Stated functions are functions that continue to hold a state/value 
    //when called
    //2. Non-stated means functions that are functions that are reset
    //every time they are called

    //function LCG16() - PRNG FUNCTION
    //meaning psudo RNG function

    static unsigned int s_state{ 5325 }; //The first seed 

    s_state = 80151450987 * s_state + 186489; //Modifying s_state

    return s_state % 32768;

    //Just a demonstration fucntion. Objectively it's bad but it serves to 
    //show what it is like

}

void printMerseeneTwister() {
    //Generate a random number using the Mersenne Twister
    std::mt19937_64 mc{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())}; //Seeding with clock
    std::mt19937_64 mr{ std::random_device{}() }; //Generate with a random device
    //Careful as random device is implementation dependent

    std::uniform_int_distribution die6{ 1,6 }; //uniform distribution of numbers

    std::cout << die6(mr);
}

int main() {
    int x = chapter77(5);
    getGravity();
    return 0;
}