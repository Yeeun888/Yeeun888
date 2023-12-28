#include <iostream>

double getHeight() {
    std::cout << "Please enter a the desired heigh of calculation: ";

    double dropHeight{};
    std::cin >> dropHeight;

    return dropHeight;
}

void outputCalculation(double h) {
    //double gravConstant{6.6743e-11};

    int time = 0; //Uses int because function works in increments of 1s
    double currentHeight = h;
    double initialHeight = h;
    double distanceFallen;

    while (currentHeight > 0) {
        distanceFallen = 0.5 * 9.81 * (time*time);
        currentHeight = initialHeight - distanceFallen;

        if(distanceFallen < h)
            std::cout << currentHeight << "m and " << time << '\n';
        else
            std::cout << "It is on the ground at " << time << " seconds";
        time = time + 1;
    } 
    
}

int main() {
    
    double dropHeight = getHeight();

    outputCalculation(dropHeight);

    return 0;
}