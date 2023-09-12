// Writteni not sure 
// Fixed by Maximus Philips Chan z5457349
//
// Interactive program to scan in and display the details of students in a
// class.

//Note: Main was horrendous

#include <stdio.h>

//TODO use these enums and #defines to clean up the code
#define MAX_CLASS_SIZE 20
#define MAX_EXAM_MARK 40
#define MAX_ASSIGMENTS_MARK 60
#define NOT_FOUND -1

enum loop_sentinal { STOP_LOOPING, KEEP_LOOPING };
enum command {HELP, PRINT_STUDENT, PRINT_CLASS, QUIT, INVALID_COMMAND };
enum degree_type {UGRD, PGRD, INVALID_DEGREE};
enum major {
    COMPA1,
    COMPD1,
    COMPE1,
    COMPI1,
    COMPJ1,
    COMPN1,
    COMPS1,
    COMPY1,
    NONE
};

struct student {
    int z_id;
    int major;
    int degree_type;
    double assignments_mark;
    double exam_mark;
    double course_grade;
};

//---------------------------- Start of Code -----------------------------------

//Simple Function
int get_class_size() {
    int class_size;
    printf("Enter Class Size: ");
    scanf("%d", &class_size); 
    return class_size;
}

//Functions below are part of create_student function

void print_major(int major_num) {
    int major = major_num;
    if (major == 0) {
        printf("Computer Science\n");
    } else if (major == 1) {
        printf("Database Systems\n");
    } else if (major == 2) {
        printf("eCommerce Systems\n");
    } else if (major == 3) {
        printf("Artificial Intelligence\n");
    } else if (major == 4) {
        printf("Programming Languages\n");
    } else if (major == 5) {
        printf("Computer Networks\n");
    } else if (major == 6) {
        printf("Embedded Systems\n");
    } else if (major == 7) {
        printf("Security Engineering\n");
    } else {
        printf("None\n");
    } 
}

double get_exam_mark() {
    printf("Enter exam mark (out of %d): ", 40);
    double exam_mark;
    scanf("%lf", &exam_mark);

    if (exam_mark > 40) {
        exam_mark = 40;
    } else if (exam_mark < 0) {
        exam_mark = 0;
    }

    return exam_mark;
}

void modify_struct(struct student *new_student, int degree_type, 
int scanned_degree_type) {
    if (scanned_degree_type == 0 || scanned_degree_type == 1) {
        degree_type = scanned_degree_type;
    }
    new_student->degree_type = degree_type;

    new_student->major = 8;
    if (new_student->degree_type == 0) {
        // Print Major Prompt
        printf("Select Major: \n");
        int major = 0;
        while (major <= 8) {
            printf("%d: ", major);
            // print major text
            print_major(major);
            major++;
        }
        // scanning in the major
        int scanned_major;
        scanf("%d", &scanned_major);
        major = 8;
        if (scanned_major >= 0 && scanned_major < 8) {
            major = scanned_major;
        }

        new_student->major = major;
    }
}

struct student create_student(int i) {
    printf("Student %d: \n", i + 1);
    struct student new_student;
    printf("Enter zID: ");
    scanf("%d", &new_student.z_id);

    // Printing the Degree type prompt
    printf("Select Degree Type: \n");
    printf("0: Undergraduate\n");
    printf("1: Postgraduate\n");

    // scanning the degree type
    int scanned_degree_type;
    scanf("%d", &scanned_degree_type);
    int degree_type = 2;

    modify_struct(&new_student, degree_type, scanned_degree_type);

    printf("Enter Assignments mark (out of %d): ", 60);
    double assignments_mark;
    scanf("%lf", &assignments_mark);

    if (assignments_mark > 60) {
        assignments_mark = 60;
    } else if (assignments_mark < 0) {
        assignments_mark = 0;
    }

    double exam_mark = get_exam_mark();

    new_student.assignments_mark = assignments_mark;
    new_student.exam_mark = exam_mark;
    new_student.course_grade = exam_mark + assignments_mark;

    return new_student; 
}

//Commands in the form of functions
void command_zero() {
    printf("Enter a number corresponding to one of the following commands: \n");
    printf("0 (Help): Display program instructions\n");
    printf("1 (Display Student): Print the details of a specific student\n");
    printf("2 (Display Class): Print the details of all students in a class\n");
    printf("3 (Quit): Exit the program\n");
}

void command_one(struct student *class, int class_size) {
    printf("Enter Student zID: ");
    int z_id;
    scanf("%d", &z_id);

    int i = 0;
    int student_index = -1;
    while (i < class_size) {
        if (class[i].z_id == z_id) {
            student_index = i;
        }
        i++;
    }

    if (student_index == -1) {
        printf("No student with that zID exists\n");
    } else {
        printf("z%07d: {\n", class[student_index].z_id);
        //Print student Details
        printf("\tDegree Type: ");
        if (class[student_index].degree_type == 0) {
            printf("Undergraduate\n");
        } else if (class[student_index].degree_type == 1) {
            printf("Postgraduate\n");
        } else {
            printf("INVALID\n");
        }

        if (class[student_index].degree_type == 0) {
            printf("\tMajor: "); 
            print_major(class[student_index].major);
        }

        printf("\tAssignments Mark: %3.02lf/%d\n", class[student_index].
        assignments_mark, 60);
        printf("\tExam Mark: %3.02lf/%d\n", class[student_index].exam_mark, 40);
        printf("\tCourse Grade: %3.02lf/%d\n", class[student_index].course_grade
        , 60 + 40);
        printf("}\n");
    }
}

void command_two(struct student *class, int class_size) {
    printf("Students: \n");
    int i = 0;
    while (i < class_size) {
        struct student student = class[i];
        //Print Student Details
        printf("z%07d: {\n", student.z_id);
        printf("\tDegree Type: ");
        if (student.degree_type == 0) {
            printf("Undergraduate\n");
        } else if (student.degree_type == 1) {
            printf("Postgraduate\n");
        } else {
            printf("INVALID\n");
        }
    
        if (student.degree_type == 0) {
            printf("\tMajor: ");
            print_major(student.major);
        }
    
        printf("\tAssignments Mark: %3.02lf/%d\n", student.assignments_mark, 60);
        printf("\tExam Mark: %3.02lf/%d\n", student.exam_mark, 40);
        printf("\tCourse Grade: %3.02lf/%d\n", student.course_grade, 60 + 40);
        printf("}\n");
        i++;
    } 
}

//---------------------------- End of Code -----------------------------------

//TODO CLEAN UP THIS CODE
int main(void) {
    int class_size = get_class_size();

    if (class_size <= 0 || class_size > 20) {
        printf("Class Size must be between 1 and %d\n", 20);
        // Exit the program early
        return 0;
    }

    struct student class[20];

    int i = 0;
    while (i < class_size) {
        class[i] = create_student(i); ++i;
    }

    int is_looping = 1;
    while (is_looping) {
        printf("Enter Command Number (0 for Help): ");

        // scan in command
        int scanned_command;
        scanf("%d", &scanned_command);
        int command = 4;
        if (scanned_command >= 0 && scanned_command <= 3) {
            command = scanned_command;
        }
        if (command == 0) {
            command_zero();
        } else if (command == 1) {
            command_one(&class[0], class_size);
        } else if (command == 2) {
            command_two(&class[0], class_size);
        } else if (command == 3) {
            is_looping = 0;
        } else {
            printf("Invalid Command\n");
        }
    }

    printf("Exiting Program\n");

    return 0;
}
