#include <iostream>
#include <array>

//Introduction to object oriented programming - CHAPTER 13

//Chapter 13.2 - classes 

class TestClass {
    public:
        using ID = int; //Member type
        ID employeeOne{ }; //Member variables 

        std::string_view nameOne{ };

        void IDandName() {
            printName();
            printID(); //Functions can be nested inside a class, and they can call
                         //each other.
        }

        void printName() { //Referred to as member functions
            std::cout << nameOne << '\n';
        }

        void printID() {
            std::cout << employeeOne << '\n';
        }
};

void chapter132() {
    TestClass Harry{ 2, "Harry Styles" };
    Harry.IDandName();
}

//Chapter 13.3 - Public and Private members in a class
//More interesting behavior on classes

//Classea have public and private 
class DateClass {
    int day{}; //Note all members of the class are private by default
    int month{};
    int year{};

    public: 
        void setDate(int newDay, int newMonth, int newYear) {
            day = newDay;
            month = newMonth;
            year = newYear;
        }

        void print() {
            std::cout << "D/M/Y: " << day << ' ' << month << ' ' << year << '\n';
        }

        void copyDateOf(DateClass d) {
            day = d.day;        //Note that a class can access private members of
            month = d.month;    //the same class type. Access specifiers are unique
            year = d.year;      //to the class not the object!
        }
};

class Stack {
    private:
        std::array<int, 10> array{};
        int currentPointer = 0;

    public:
        void reset() {
            for(int i{ 0 }; i < array.max_size(); ++i) {
                array.data()[i] = 0;
            }
        }

        bool push(int a) {

            if(currentPointer == 9) {
                return false;
            }

            array.data()[currentPointer] = a;
            currentPointer += 1;

            return true;
        }

        bool pop() {
            if(currentPointer == 0) {
                return false; 
            }

            array.data()[currentPointer] = 0;
            currentPointer -= 1;

            return true;
        }

        bool print() {
            std::cout << "( ";
            for(int i{ 0 }; i < currentPointer; ++i) {
                std::cout << array[i] << ' ';
            }
            std::cout << ')';

            return true;
        }
    
};

//13.4 - Small notes on return values
//It's best that values that are read only are returned as const reference 

class readValue {
    private:
        int nonConst { 5 };
        const int yesConst { 4 };

    public:
        int& getValue() {
            return nonConst;
        }

        const int& getValueConst() {
            return yesConst;
        }
};

int chapter134() {
    readValue test;
    test.getValue() = 3;

    //Line below will not compile. Believe me pls.
    //test.getValueConst() = 4;
   
    return 0;
}

//13.5 - This is a constructor and how it is made.
class constructorDemo{
    private:
        int num{};

    public:
        constructorDemo() = default; //Tells compiler to write a default constructor

        constructorDemo(int i) {
            num = i;
        }
};

//13.6 - Constructing classes with direct/uniform initialization instead of assignment

class TestInitialization {
    private:
        int var1 {};
        const int var2{};
        double var3 {};

    public:
        TestInitialization(int one, const int two, double three):
            var1{ one },
            var2{ two },
            var3{ three } {}

        void printVariables() {
            std::cout << var1 << ' ' << var2 << ' ' << var3;
        }
};

void chapter136() {
    TestInitialization test{1, 5, 6.0}; //Notice that const is able to be initialized
    test.printVariables();
}

//Notes for chapter 13.7
//Basically constructor can be used overlappingling like functions xD

void chapter137() {

}

//Chapter 13.8 - Delegating Constructors
//Basically constructors that can call other constructors. 

//Important Notes: Constructors cannot delegate and 

class Mouse{
    private:
        int buttons{2};
        std::string brand{"Corsair"};

    public:
        Mouse() {

        }

        Mouse(int i_Buttons = 0, std::string_view i_Brand = ""): buttons{ i_Buttons }, brand{ i_Brand } {
            //Execute some code here
        }

        //Constructor can call Mouse(int, std::string_view) as shown below
        Mouse(std::string_view i_Brand = "Logitech"): Mouse(0, i_Brand ) {
            //Insert some code here
            //Although you can't call another constructor.

            //Why? Because you end up making an anonymous object whose name
            //(not that there was one) is discarded immediately. 
        }

        void reset() {
            *this = Mouse(2, "Corsair");
        }        
};

void chapter138() {
    Mouse mouse{"Log"};
}

//Chapter 13.9 - Destrutors

class Array {
    private:
        int* m_array{};
        int m_length{};
    
    public:
        Array(int length) { //Constructor to make a new array
            assert(length > 0);

            m_array = new int[static_cast<std::size_t>(length)]{};
            m_length = length;
        }

        //Use a tilde to signifiy a destuctor
        ~Array() {
            delete[] m_array;
        }

        //Other functions for an array
        void setValue(int index, int value) { m_array[index] = value; }

        int getValue(int index) { return m_array[index]; }
        int getLength() { return m_length; }
};

void chapter139() {
    Array array1(5);

    array1.~Array(); //array1 can be manually destroyed 
} //array1 is automatically destroyed once it leaves the scope

//Chapter 13.10 - this pointer and chaining arguments REALLY INTERSTING
class Calc {
    private: 
        int m_value{ 0 };
    public:
        Calc(int m_value) {
            this->m_value = m_value; //Overload the same variablename. 
        }

        //Another way to use it is to chain functions

        Calc& add(int value) { m_value += value; return *this; } //changes the value of the object
        Calc& sub(int value) { m_value -= value; return *this; } //before returning it as an address
        Calc& multi(int value) { m_value *= value; return *this; } //that can be modified again

        int getValue() { return m_value; }
};

void chapter1310() {
    //Pay attention here where now it can be chained
    Calc test(3);

    test.add(3).sub(1).multi(43); //Now the functions can be used in sequential order

    test.getValue();
}

//Chapter 13.11 - Class code and header files
//Important note here is that members of a class can be defined outside of a class.
//this is important as it allows programs to be split allowing for faster compile times.

//For example
class Car {
    private:
        int wheels{};
        int chairs{};

    public:
        Car(int w, int c);

        void buildCar(int w, int c);
};

Car::Car(int w, int c) {
    buildCar(w, c);
}

void Car::buildCar(int w, int c) {
    wheels = w;
    chairs = c; 
}
//As you can see the members are defined outside of the class.
//this can be helpful with the use of header files. 

//Chapter 13.12 - CONST MEMBERS AND FUNCTIONS 
//Const classes are mode with the const keyword. Const classes have their members
//become constant

class Simple {
    private:
        int x{};
    public:
        Simple(int input) : x{ input } {};

        int getValue() const { return x; }; //Make the function const
                                           //only const functions can access const members
};

//Chapter 13.13 - Static member variables
//Basically all static members are shared among types of the same class

//Chapter 13.14 - Static member functions
//These are useful for accessing static member variables withou having to create an object
class testClass {

        static inline int testVariable{ 0 };
        static const int var2{ 2 };
    public:
        static int getValue() {
            return testVariable;
        }
};

//13.5 - Friend functions
//They are basically function prototypes which can be forward declared inside a class
//such that they have access to private members of the class. 

//For instance
class Accumulator {
    private:
        int m_value{ 0 };
    public:
        void add(int value) { m_value += value; }

        friend void reset(Accumulator& accumulator);
};

void reset(Accumulator& accumulator) {
    accumulator.m_value = 0; //As you can see the function can access member variables that are private
} 

//Timing the code
//Use a timer object and then output elapsed time. 

int main() {
    chapter138();
}
