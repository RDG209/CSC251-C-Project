/*
 ui.c
 User Interface
 Luis Martinez
*/
#include "ui.h"
#include "gradebook.h"
#include "file.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper to clear input buffer after scanf
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Helper to get string input
void get_string_input(const char* prompt, char* buffer, size_t buffer_size) {
    printf("%s", prompt);
    // Use fgets to safely read a line including spaces
    if (fgets(buffer, buffer_size, stdin) != NULL) {
        // Remove the newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

// UI functions for menu options
void ui_add_student() {
    int id;
    char name[MAX_NAME_LENGTH];
    float grade;

    printf("Enter student ID: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("Invalid ID.\n"); return; }
    clear_input_buffer(); // Clear buffer after scanf
    get_string_input("Enter student name: ", name, MAX_NAME_LENGTH);
    printf("Enter student grade: ");
    if (scanf("%f", &grade) != 1) { clear_input_buffer(); printf("Invalid grade.\n"); return; }
    clear_input_buffer();

    add_student(id, name, grade);
    printf("Student added.\n");
}

void ui_show_student() {
    int id;
    printf("Enter student ID to find: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("Invalid ID.\n"); return; }
    clear_input_buffer();

    int pos = find_student(id); // Use find_student from (1)
    if (pos != -1) {
        int found_id;
        char found_name[MAX_NAME_LENGTH];
        float found_grade;
        get_student_data(pos, &found_id, found_name, &found_grade);
        printf("\nFound Student:\n");
        printf("ID: %d\nName: %s\nGrade: %.2f\n", found_id, found_name, found_grade);
    } else {
        printf("Student ID %d not found.\n", id);
    }
}

void ui_update_student() {
    int id;
    float new_grade;
    printf("Enter student ID to update: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("Invalid ID.\n"); return; }
    printf("Enter new grade: ");
    if (scanf("%f", &new_grade) != 1) { clear_input_buffer(); printf("Invalid grade.\n"); return; }
    clear_input_buffer();
    update_student(id, new_grade); // Use update_student from (1)
}

void ui_delete_student() {
    int id;
    printf("Enter student ID to delete: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("Invalid ID.\n"); return; }
    clear_input_buffer();
    delete_student(id); // Use delete_student from (1)
}

void ui_sort_students() {
    int choice;
    printf("\nSort by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Grade (High to Low)\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) { clear_input_buffer(); printf("Invalid choice.\n"); return; }
    clear_input_buffer();

    switch (choice) {
        case 1: sort_by_id(); break;
        case 2: sort_by_name(); break;
        case 3: sort_by_grade(); break;
        default: printf("Invalid choice.\n"); break;
    }
}

void ui_show_all_students() {
    show_all_students(); // Use function from (1)
}

void show_menu() {
    int choice;
    while (1) { // Infinite while loop for menu
        printf("\n--- Gradebook Menu ---\n");
        printf("1. Add student\n");
        printf("2. Show student by ID\n");
        printf("3. Update student grade\n");
        printf("4. Delete student\n");
        printf("5. Show all students\n");
        printf("6. Sort students\n");
        printf("7. Show statistics\n");
        printf("8. Save to file (students.txt)\n");
        printf("9. Load from file (students.txt)\n");
        printf("10. Close / Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clear_input_buffer(); // Clear buffer

        switch (choice) {
            case 1: ui_add_student(); break;
            case 2: ui_show_student(); break;
            case 3: ui_update_student(); break;
            case 4: ui_delete_student(); break;
            case 5: ui_show_all_students(); break;
            case 6: ui_sort_students(); break;
            case 7: show_stats(); break;
            case 8: save_to_file("students.txt"); break;
            case 9: load_from_file("students.txt"); break;
            case 10: printf("Goodbye!\n"); return; // Exit loop/function
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}
