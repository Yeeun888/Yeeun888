#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    //Argc is how many arguments thereare
    //argv is the actual arguments (in the form of array)
    std::cout << argc << '\n';

    for(int i{ 0 }; i < argc; ++i) {
        std::cout << argv[i] << '\n';
    }

    //Convert argument 1 into an integer (since it is received in string)
    std::stringstream convert{ argv[1] };

    int myint{};
    if(!(convert >> myint))
        myint = 0;

    std::cout << myint << '\n';
}