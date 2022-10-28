#include <iostream>

int factorial(int num) {
    //Question 1 on factorials
    static int ans{ 1 };

    if(num != 0) {
        ans *= num;
        factorial(num - 1);
    }
    return ans;
}

//Correct factorial answer
int factorial_correct(int num) {
    if (num <= 0)
        return 1;

    return factorial_correct(num - 1) * num;
}

void numberAddiiton(int num) {

    if(num == 0) {
        return;
    }

    numberAddiiton(num / 2);

    std::cout << num % 2;
}

int main() {
    numberAddiiton( 128 );
    return 0;
}