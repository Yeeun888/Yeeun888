#include <iostream>
#include <iterator> // for std::size

int getUserInput() {
    while (true) {
        std::cout << "Enter a number between 1 and 9: ";
        
        int x{};
        std::cin >> x;

        // if the user entered something invalid
        if (std::cin.fail())
        {
            std::cin.clear(); // reset any error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer
        } else {
            return x;
        }
    }
}

int main()
{
    int findNum = getUserInput();

    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };

    for (int index{ 0 }; index < static_cast<int>(std::size(array)); ++index)
    {
        std::cout << array[index] << ' ';
    }

    std::cout << '\n';


    for (int index{ 0 }; index < static_cast<int>(std::size(array)); ++index)
    {
        if(array[index] == findNum) {
            printf("The number %i has index %i", array[index], index);
            break;
        }
    }
    std::cout << '\n';
    return 0;
}

