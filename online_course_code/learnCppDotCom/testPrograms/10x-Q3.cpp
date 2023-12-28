#include <iostream>

template <typename T> struct Triad {
    T int1{};
    T int2{};
    T int3{};
};

template <typename T> Triad(T,T,T) -> Triad<T>;

int main() {
   	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments

    return 0;
}