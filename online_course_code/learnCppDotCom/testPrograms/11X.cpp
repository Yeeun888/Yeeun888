#include <iostream>
#include <array>
#include <numeric>
#include <vector>
#include <random>

enum class playerItems {
    healthPotion,
    torch,
    arrow,
};

struct stats {
    std::array<int, 3>amounts {};
};

int countTotalItems(stats &human) {
    return std::reduce(human.amounts.begin(), human.amounts.end());
}

int question1_main() {
    //Creating a game question
    stats human1{ {2,5,10} };
    std::cout << countTotalItems(human1) << '\n';
    std::cout << human1.amounts.at( static_cast<int>(playerItems::torch) );
    return 0;
}

struct students{
    std::string name{};
    int grade{};
};

int question2_main() {
    std::vector<students> studentDatabase{};

    int askedTimes{};
    std::cout << "How many students would you like the enter? ";
    std::cin >> askedTimes;

    for(int i = 0; i < askedTimes; ++i) {
        std::cout << "Student name: ";
        std::string temp1{};
        std::cin >> temp1;

        std::cout << "Student grade: ";
        int temp2{};
        std::cin >> temp2;

        studentDatabase.push_back(students {temp1, temp2});
    }

    for( students i : studentDatabase) {
        std::cout << i.name << " has a grade of " << i.grade << '\n';
    }
    return 0;
}

//Is question 3
void swapIntegers(int& a, int& b) {
    std::swap(a, b);
}

void question4_main(const char* string) {
    while(*string != '\0') {
        std::cout << *string << '\n';
        string++;
    }
}

//Below is question 6
enum class ranks {
    two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace, max_amount,
};

enum class suits {
    diamond, clubs, heart, spade, max_amount,
};

struct card {
    ranks rank{};
    suits suit{};
};

void printSuit(const card& printCard) {
    std::string ranksArray[]{ "2","3","4","5","6","7","8","9","10", "J", "Q", "K", "A" };
    char suitsArray[]{ 'D', 'C', 'H', 'S' };
    std::cout << ranksArray[static_cast<int>(printCard.rank)] << 
    suitsArray[static_cast<int>(printCard.suit)];
}

std::array<card, 52> createDeck() {

    std::array<card, 52> fullDeck{};
    
    int size{fullDeck.size()};

    int counter { 0 };

    for(size_t i = 0; i < static_cast<int>(ranks::max_amount); ++i) {
        for(size_t j = 0; j < static_cast<int>(suits::max_amount); ++j) {
            card x{ static_cast<ranks>(i), static_cast<suits>(j) };
            fullDeck[counter] = x;
            ++counter;
        }
    }

    counter = 0;

    return fullDeck;
}

void shuffleDeck(std::array<card, 52>& deck) {
    static std::mt19937_64 mt{ static_cast<std::mt19937_64::result_type>(std::time(nullptr)) };

    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(card testedCard) {
    if(static_cast<int>(testedCard.rank) == 8 || static_cast<int>(testedCard.rank) == 9 || static_cast<int>(testedCard.rank) == 10 || static_cast<int>(testedCard.rank) == 11) {
        return 10;
    } else if (static_cast<int>(testedCard.rank) == 12) {
        return 11;
    } else { return static_cast<int>(testedCard.rank) + 2; }
}

void question6_main() {
    std::array x = createDeck();

    shuffleDeck(x);
    for(int i = 0; i < 52; ++i) {
        printSuit(x[i]);
        std::cout << ' ';
    }

    std::cout << std::endl;

    printSuit(x[20]);
    int z = getCardValue(x[20]);
    std::cout << z;
}

int takeCard() {
    static int cardNum{ 0 };
    ++cardNum;
    return cardNum;
}

int compareDeck(int player, int dealer);

bool playBlackjack(std::array<card, 52> deck) {
    std::vector<card> dealerCards = { deck[takeCard()] };
    std::vector<card> playerCards{ deck[takeCard()], deck[takeCard()] };

    int playerFinalValue{};
    int dealerFinalValue{};

    std::cout << "The dealer has one card, you get two cards to start. Your cards are: \n";
    printSuit(playerCards[0]); std::cout << " and "; printSuit(playerCards[1]); std::cout << '\n';
    while(true) {
        std::cout << "Hit (h) or stand (s), partner? ";
        
        char option{};
        std::cin >> option;
        if(option == 'h') {
            playerCards.push_back(deck[takeCard()]);
        } else if (option == 's') {
            std::cout << "You choose to stand \n";
            break;
        } else {
            std::cout << "Try another option \n";
            continue;
            }
        std::cout << "Your cards of ";
        for(card i : playerCards) { printSuit(i); std::cout << ' '; };

        playerFinalValue = 0;
        for(card i : playerCards) { playerFinalValue += getCardValue(i); };
        
        std::cout << "Have a value of " << playerFinalValue << '\n';

        if(playerFinalValue > 21) {
            std::cout << "You loose noob";
            return false;
        }
    }

    std::cout << "Now the dealer goes. \n";

    while(true) {
        for(card i : dealerCards) { printSuit(i); std::cout << ' '; };
        std::cout << '\n';
        //Calculate dealer deck value
        dealerFinalValue = 0;
        for(card i : dealerCards) { dealerFinalValue += getCardValue(i); };
        
        if(dealerFinalValue <= 17) {
            dealerCards.push_back(deck[takeCard()]);
            continue;
        } 

        if(dealerFinalValue > 21) {
            std::cout << "The dealer has lost. GG. \n";
            return false;
        }
        
        break;     
    }

    compareDeck(playerFinalValue, dealerFinalValue);
    return true;
}

int compareDeck(int player, int dealer) {
    if (player == dealer)
    {
        std::cout << "Equal game, equal decks. Draw. ";
        return 0;
    }

    if(player > dealer) {
        std::cout << "You win.";
        return 0;
    }

    std::cout << "You lose. ";
    return 0;
}

int question7_main() {
    std::array deck = createDeck();
    shuffleDeck(deck);
    bool winState = playBlackjack(deck);

    return 0;    
}

int main() {
    question7_main();

    return 0;
}