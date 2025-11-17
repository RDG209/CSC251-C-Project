/*
 main.c
 Alejandro Lule Hernandez
 Program to test gradebook.c using 3 hardcoded students
 Will test Data Handling Functions like Adding students, Updating grade,
 Deleting students, Searching students, Displaying all students info
*/
#include <stdio.h>
#include "gradebook.h"

int main() {
	//Test add_student; Adds 3 hardcoded students and displays students
	add_student(101, "Alice", 89.6);
	add_student(102, "Bob", 82.6);
	add_student(103, "Charlie", 76.3);
	print_all_students();

	//Test update_student; Updates student grade using ID and displays students
	update_student(103, 80.0);
	printf("\nUpdated Charlie's grade:\n");
	print_all_students();

	//Test delete_student; Deletes student using ID and displays students
	delete_student(102);
	printf("\nDeleted Bob:\n");
	print_all_students();

	//Test find_student; Searches for student using ID and displays position
	int pos = find_student(101);
	if (pos != -1)
		printf("\nFound Alice at position %d\n", pos);

	//Initializes student data ID, name, and grade
	int id;
	char name[50];
	float grade;
	//Test get_student_data; Displays students data by position
	get_student_data(0, &id, name, &grade);
	printf("\nStudent at position 0: ID=%d, Name=%s, Grade=%.2f\n", id, name, grade);

	//Test get_student_count; Displays the number of students
	printf("\nTotal students: %d\n", get_student_count());

	return 0;
}
