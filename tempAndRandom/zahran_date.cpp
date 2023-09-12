#include <ctime>
#include <iostream>

int main() {
    std::string empty_string[8];
    std::cout << "Hit CTRL-D to stop, enter anything else (or nothing) to continue\n";
    while(scanf("%s", &(empty_string[0])) != EOF) {
        std::time_t t = std::time(0); //Get time now
        std::tm *now = std::localtime(&t); //Struct tm as a pointer

        //Convert into year, month, and date

        std::string year = std::to_string(now->tm_year + 1900);

        //If dates are less than 10 append 0 in the front
        std::string month;
        std::string day;

        if((now->tm_mon + 1) < 10) {
            month = '0' + std::to_string(now->tm_mon + 1);
        } else {
            month = std::to_string(now->tm_mon + 1); 
        }

        if((now->tm_mday) < 10) {
            day = '0' + std::to_string(now->tm_mday); 
        } else {
            day = std::to_string(now->tm_mday);
        }

        //     Y/D/Y/M/Y/M/D/Y
        std::cout << year << month << day <<'\n';
        std::cout << year[0] << '/' << day[0] << '/' << year[1] << '/' << month[0] << '/' << year[2] << '/' << month[1] << '/' << day[1] << '/' << year[3] << '\n';
    }

    return 0;
}
