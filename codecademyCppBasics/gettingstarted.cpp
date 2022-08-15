//Preprocessory Directive to import libraries
#include <iostream>
#include <vector>
#include <string>

/* multi
line comment */

using namespace std;

void myFunction() {
    //this is a sample function that can be called
}

void inputOutput() {
    cout << "This is a message" << endl; //endl is used to endline

    int age;
    cout << "What is your age? ";
    cin >> age;    
}

void variablesAndIncrement() {

    //const cannot be changed at all. 
    const double pi = 3.14;

    //interseting observations with pre-increment vs post-increment
    int x = 10, y = 10, z;
    
    //++x = pre-increment
    //x++ = post-increment

    z = ++x;//z will be 11 because the addition happens first

    z = x++;//z will be 10 but X is 11 since addition happens after
    
}
void referencesandmemory() {
    int highscore = 55;
    int& top = highscore;

    //top changes with highscore
    //you can't reassign top. It causes undesired behavior
}

int main()
{
    variablesAndIncrement();
}