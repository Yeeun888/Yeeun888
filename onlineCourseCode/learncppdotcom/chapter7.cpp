#include <iostream>

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

int main() {
    int x = chapter77(5);
    return 0;
}