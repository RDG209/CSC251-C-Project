/*
 gradebook.h
*/
//Guards prevent the header from being processed multiple times
#ifndef GRADEBOOK_H
#define GRADEBOOK_H

//Constants declarations
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

//Global arrays for student data
extern int student_ids[MAX_STUDENTS];
extern char student_names[MAX_STUDENTS][MAX_NAME_LENGTH];
extern float student_grades[MAX_STUDENTS];
extern int student_count;

//Function declarations
void add_student(int id, const char *name, float grade);
int find_student(int id);
void update_student(int id, float new_grade);
void delete_student(int id);
int get_student_count();
void get_student_data(int position, int *id, char *name, float *grade);
void print_all_students();

/// necessary added functions
int get_student_id(int index);
void show_all_students(void);

#endif
