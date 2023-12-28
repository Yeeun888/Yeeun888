#include <iostream>

//This section of the website mainly discusses user-defined types and how
//they are helpful

namespace monster {
    enum MonsterType {
        orc,
        goblin,
        troll,
        org, 
        skeleton,
    };
}

void chapter102() {
    //This space is more for notes as there are afew notes on enums
    //enums (enumerators) are those which exist as separate types   

    //It is worth noting that enumerators are worth putting in a namespace
    //to prevent polluting the global namespace

    //To initialize a goblin it is as follows
    monster::MonsterType firstMonster{ monster::goblin };

    //In the code above using the monster:: helps us access the namespace
    //MonsterType is the program-defined type
    //firstMonster is then the name of the variable or monster
    //monster::goblin is the the type of monster which is then accessible through namesapce
}

void chapter103() {
    //It is worth noting that all enumerators are implicitly assigned numbers

    //Enums can be printed using names through a series of if statements

    //Enums can also be assigned a size ans base

    enum Color : std::uint16_t {
        black, 
        blue, 
        red, 
    };

    //Using integers directly cannot go against

    Color color { static_cast<Color>(2) }; // it is red now
    color = static_cast<Color>(1); //now color is blue
}

enum class Animal {
        pig,
        chicken,
        goat,
        cat,
        dog,
        duck,
    };

void chapter104() {
    //Instead of poluting the global namesapce with enums or complex requirement
    //for the use of namespaces, we can use scoped namespaces.

    

    //Using a scoped enumerator removes the implicit conversion that is performed
    //to convert to num.

    //Scoped enumerators also allow direct comparisons rather than integer ones

    if (Animal::pig == Animal::chicken) {
        std::cout << "They are the name \n";
    }    

    
}

constexpr std::string_view getAnimalName(Animal animalName) {
    switch(animalName) {
        case Animal::cat:
            std::cout << "A cat has 4 legs";
            break;
        case Animal::chicken:
            std::cout << "A chicken has 2 legs;";
            break;
        default:
            std::cout << "xd";
        }
}

//10.5 USING STRUCTS
//Structs aka structures are a combination of member variables 
    
//Structs are ways of grouping variables together and define them under one object

struct Employee { //small note since structs are unique keywords, make sure the
    int id {};    //their names are captial in the beginning
    int age {};
    double wage {};
};

void chapter105() {
    Employee joe;
    joe.id = 14;
    joe.age = 8;
    joe.wage = 5.0;

    //These numbers can then be accessed in the same way and compared, modified,
    //etc. 
}

//Structs themself are considered an aggregate data type, meaning it can hold
//multiple data types. 

//So how do we initilize this sort of data without manually typing it out?

void chapter106() {
    //New structs can be initilized with braces immediately
    Employee para {15, 7, 8000.0}; //All variables are initilized according to 
                                   //struct order
    
    //lets say Para got a raise and had a birthday
    para = {para.id, 8, 9000.0 }; //We can reinitilize the variable with itself
                                  //while inputing new variables ourself. 
}

//Structs can be have default initialization

struct Fraction {
    int numerator {}; //compiler defaults this to 0. 
    int denominator { 1 }; //default initialization to 1. 
};

//Chapter 10.8 passing structs through functions

//As structs is a program-defined type they can also be returned by functions.
//Surprisingly, they can also be nested abit like namespaces

struct Company{
    struct Employee {
        int id{};
        int age{};
        double wage{};
    };

    int numberOfEmployees{};
    Employee CEO{};
};

Company createCompany() {
    //Add some useful code here 

    Company myCompany{ 7, {14, 69, 420000.0}};
    return myCompany; 
}

//CHAPTER 10.9 Using pointers and references with respect to structs
//Member selection with pointers and references

void printEmployeeInfo(const Employee& data) {
    std::cout << data.id << '\n';
    std::cout << data.age << '\n';
    std::cout << data.wage << '\n';
} 
//Here it is worth noting that data can be accessed through a reference immediately

void pointerDemo() {
    Employee Max{ 1, 34, 54.000 };

    Employee* ptr{ &Max };
    //Two ways to work with a the object through the pointer

    std::cout << (*ptr).age << '\n';
    // But this is ugly and requires manual dereference
    std::cout << ptr->age << '\n';
    //-> implicitly dereferences the object bring pointed at. 
}

//However structs can get repetitive, especially if they are data type dependent
//Imagine if such as the fraction type above we wanted double, int,... versions of
//that fraction. It would be a nightmare and difficult. Therefore we can make
//class templates. 

//CHAPTER 10.10 - Class Templates

template <typename T> struct Pair {
    T first{};
    T second{};
};

//Initilize them like template and structs alike, just combine the two knowledges
//together

void templateDemo() {
    Pair<int> p1{ 5, 6 };
    Pair<double> p2{ 5.0, 6.0 }; //Template generated struct, new double pairs
                                 //will use this newly generated template.
}

//We can also make a function using this class template
constexpr int max(Pair<int> p) {
    return (p.first > p.second ? p.first : p.second);
}

//Max can also be turned into a function
template <typename T> constexpr T max(Pair<T> p) {
    return (p.first > p.second ? p.first : p.second);
}

//OK COOL CPP FEATURE
//ALRIGHT 
//10.11 - CLASS TEMPLATE AUTOMATIC DEDUCTION (CTAD) omg this shit is so cool

//This part of the notes builds on line 186 btw

template<typename T>Pair(T t, T y)->Pair<T>;

void ctadDemo() {
    Pair<int> p1{ 1, 2 }; //All is good as now int is defined
    
    //so what if
    //Pair p2{ 1,2 }; compiler cannot deduce so we have to teach it how to deduce
    //types. Line 216 shows how it's done

    //Important note abt line 216 is var t and y are just placeholder names
    //and actually not used

    Pair p2{ 3, 4};

}

int main() {
    getAnimalName(Animal::cat);
    return 0;
}