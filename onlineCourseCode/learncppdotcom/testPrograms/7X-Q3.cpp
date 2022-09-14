#include <iostream>
#include <random>

/**
 * Program layout
 * 2. Generate random number
 * 3. Guessing function
 * 4. Exit and print
 *   
 */
int GetUserInput(int GuessNumber);

int generateRandom(int low, int high) {
    
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

    std::mt19937_64 rn{ss};

    std::uniform_int_distribution finalNum{low, high};

    return finalNum(rn);
}

int testAnswer(int answer) {
    for(int i = 1; i <= 7; i++) {
        printf ("Guess #%i: ", i);
        
        static int guessNumber = i;
        int guess{};

        guess = GetUserInput(i);

        if(guess == answer) {
            std::cout << "Correct you win! \n";
            return 1;
        } else {
            (guess > answer) ? std::cout << "Your guess was too high.\n" : std::cout << "Your guess was too low.\n";
        }
    }

    std::cout << "Sorry you lose. The correct number was " << answer << '\n';
    return 0;
}

void clearLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int GetUserInput(int guessNumber) {
    while(true) {
        int temp{};
        std::cin >> temp;

        if(std::cin.fail()) {
            std::cin.clear();
            clearLine();
            std::cout << "Please print a number instead \n";
            std::cout << "Guess #" << guessNumber << ':';
        } else {
            clearLine();
            return temp;
        }

    }
    return 0;
}

bool playAgain() {
    while(true) {
        char ans {};
        std::cout << "Would you like the play the game again? (y/n): ";
        std::cin >> ans;

        switch(ans) {
            case 'y': return true;
            case 'n': return false;
        } 
    std::cout << "Please enter (y/n) instead \n";
    }    
}

int main() {
    const int rightAns = generateRandom(0,100); 

    //test code to get it correctly
    std::cout << "Let's play a game. I'm thinking of a number from 0 to 100. You have 7 tries to guess what it is. \n";

    testAnswer(rightAns);    
    
    if (playAgain() == true) {
        main();
    } else {
        std::cout << "Thank you for playing";
    }

    return 0;
}