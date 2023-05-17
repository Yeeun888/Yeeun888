//*Header file lesson

//*Header's help so that only forward declarations can be added in files

#ifndef SQUARE_H //This is a header guard. If chapter2head.h is already 
#define SQUARE_H //included in another file, then SQUARE_H is already 
                 //defined therefore leaving this code out. 

int findArea(int sideLength); //Where findArea is a file in anotherFile

#endif

//The use of headers is such that the same code doesn't get copied twice
//it is also much more efficient as changing the source code means that
//the header automatically defines new changes for old code. 