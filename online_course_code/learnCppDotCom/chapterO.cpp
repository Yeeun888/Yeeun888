#include <iostream>
#include <bitset>

void zero1() {
    //Manipulating Bits

    std::bitset<8> bits{ 0b0000'0101 };

    bits.set(3); //Set function makes bits at position true (1)
    bits.flip(4); //Flip changes the functino to opposite from before
    bits.reset(4); //Set bit back to zero

    std::cout << "Value of bit 3 " << bits.test(3) << '\n';
    std::cout << "All bits: " << bits;
}

void zero2() {
    //Bitwise Operators 

    std::bitset<4> x { 0b1100 };
    std::bitset<4> y { 0b0101 };

    y = y << 1; //Shift all bits to the left by 1    

    //Shifting bits further than the specified size means they are lost in time

    //Using operators on bits
    // &, |, ^ (XOR) and ~ (means not)
    //Stacking operators results in making them compounds rather than sequential

    std::cout << (std::bitset<4>{ 0b0001} & std::bitset<4>{ 0b0011} & std::bitset<4>{ 0b0111});
    /**
     * 0001 AND
     * 0011 AND
     * 0111 AND 
     * --------
     * 0001 
     */

    //Easier way is using bitwise assignment operators.
    // <<=, >>=, |=, &=, ^=

    std::bitset<4> test { 0b0010};
    test |= std::bitset<4>{ 0b1001};

    std::cout << "This is test: " << test;

}

void zero3() {
    //BITMASKS
    //Shit gets slightly complicated here
    //Not really just precision

    constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    //Testing a bit to see if it is on AND

    std::cout << "Bit in position 0 is " << ((flags & mask0) ? "ON \n" : "OFF \n");
    std::cout << "Bit in position 1 is " << ((flags & mask1) ? "ON \n" : "OFF \n");

    //A bit can also be set using OR
    flags |= mask1; //Turns on bit 1

    std::cout << "Bit in position 1 is " << ((flags & mask1) ? "ON \n" : "OFF \n");

    //Turning off bits can be done with a combination of AND and NOT together

    flags &= ~mask2; //Turn off bit2

    /**
     * Logic is that by inverting all the bits in the mask, there are many ones
     * except the zero in mask position. All the 1 bits are left on, and those that
     * are not on are then left off. Except in position mask wher it is 0. This is
     * how it forces the bit in position to become zero 
     */
    
    std::cout << "Bit in position 2 is " << ((flags & mask2) ? "ON \n" : "OFF \n");

    //Flipping a bit uses XOR ^= 

    std::cout << "Bit in position 3 is " << ((flags & mask3) ? "ON \n" : "OFF \n");
    flags ^= mask3;
    std::cout << "Bit in position 3 is " << ((flags & mask3) ? "ON \n" : "OFF \n");
    //Flipping multiple can be done with
    //flags ^= (mask0 | mask1 | mask2)
    //The same can be done with other bit operations
    
}

int main() {

    zero3();

    return 0;
}
