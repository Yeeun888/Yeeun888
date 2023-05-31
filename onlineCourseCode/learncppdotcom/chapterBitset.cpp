#include <stdio.h>
#include <iostream>
#include <bitset> //Used to include the bitset

//*Basic bitset operations 
void basicBitsetOperations() {
    std::bitset<8> eightBits{0b0001'0101};

    //Position of bits start from the end and indexed 0
    eightBits.set(3);  //0001'1101 - Makes 1
    eightBits.flip(3); //0001'0101 - Flips around
    eightBits.reset(4);//0000'0101 - Makes 0
}

//*Bits can also be done on operations
void bitsetOperation() {
    std::bitset<8> eightBits{0b0100'1101};

    //You can use << and >> to shift all bits left/right. 
    //All the trailing bits are filled in with zeroes.

    //Bit shifting has no side effects
    std::cout << (eightBits >> 1) << '\n';
    std::cout << eightBits << '\n';
    std::cout << '\n';

    //Shift and assign at the same time to permanently change eightBits
    eightBits <<= 1;
    
    std::cout << eightBits << '\n';
    //Not operator
    std::cout << ~eightBits << '\n';

    //AND, OR, XOR
    //note: XOR returns false when both are 0. Likewise true when one of them is 1. 
    //The operations are done 
}

int main() {
    bitsetOperation();
    return 0;
}