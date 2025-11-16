/*
 gradebook.c
 Data Handling
 Alejandro Lule Hernandez

 This program will handle the functionality for storing and managing
 student data using parallel arrays. It supports basic operations like
 adding, find using ID, updating by ID, change grade, remove by ID,
 return students, get ID, Name, grade by position x
*/
#include <stdio.h>
#include <string.h>
#include "gradebook.h"

//Parallel Arrays storing student's ID, names, and grades and student count set to 0
int student_ids[MAX_STUDENTS];
char student_names[MAX_STUDENTS][MAX_NAME_LENGTH];
float student_grades[MAX_STUDENTS];
int student_count = 0;

//Adds a new student to gradebook 
void add_student(int id, const char *name, float grade) {
	//Determines if there's space available
	if(student_count >= MAX_STUDENTS) {
		printf("Error: gradebook is full!\n");
        	return;
	}
	//sets the new student's id, name, grade
	student_ids[student_count] = id;
	strncpy(student_names[student_count], name, MAX_NAME_LENGTH);
	student_grades[student_count] = grade;
	//Increments student count
	student_count++;
}

//Finds student by ID, then returns index or -1 if not found
int find_student(int id) {
	for (int i = 0; i < student_count; i++) {
		if (student_ids[i] == id) {
		return i;
		}
	}
	return -1;
}

//Updates student grade by ID
void update_student(int id, float new_grade) {
	int index = find_student(id);
	if (index == -1) {
		printf("Student with ID %d not found.\n", id);
		return;
	}
	student_grades[index] = new_grade;
}

//Deletes student by ID
void delete_student(int id) {
	int index = find_student(id);
	if (index == -1) {
		printf("Student with ID %d not found.\n", id);
		return;
	}

	//Shifting elements to fill in the gap
	for (int i = index; i < student_count - 1; i++) {
		student_ids[i] = student_ids[i + 1];
		strcpy(student_names[i], student_names[i + 1]);
		student_grades[i] = student_grades[i + 1];
	}
	//Decrement student count
	student_count--;
}

//Returns the student count
int get_student_count() {
	return student_count;
}

//Gets student data by position
void get_student_data(int position, int *id, char *name, float *grade) {
	//Determines if position entered is valid
	if (position < 0 || position >= student_count) {
		printf("Invalid position.\n");
		return;
	}
	//Returns Students Id, Name, and Grade 
	*id = student_ids[position];
	strcpy(name, student_names[position]);
	*grade = student_grades[position];
}

//Displays all students info(ID, Names, and Grades)
void print_all_students() {
	printf("\n--- Gradebook ---\n");
	for (int i = 0; i < student_count; i++) {
		printf("ID: %d | Name: %s | Grade: %.2f\n", student_ids[i], student_names[i], student_grades[i]);
	}
	printf("-----------------\n");
}

