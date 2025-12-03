/*
 sort.c

 This file takes the student data stored in the parallel arrays
 from gradebook.c and lets us sort it in different ways:
 - by ID
 - by name
 - by grade

 It also calculates simple statistics (min, max, and average grade).
 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "gradebook.h" 
#include "sort.h"       

// This function compares two names without caring about uppercase/lowercase.
// It returns a negative number if name a should come before b alphabetically,
// a positive number if a should come after b, and 0 if they are basically equal.
static int compare_names_ci(const char *a, const char *b) {
    // Keep comparing characters while both strings still have characters left
    while (*a && *b) {
        // Convert both characters to lowercase so "Alex" and "alex" match
        char ca = (char)tolower((unsigned char)*a);
        char cb = (char)tolower((unsigned char)*b);

        // If the characters are different, we can decide the order right here
        if (ca != cb) {
            return (int)(ca - cb);
        }

        // Move to the next character in each string
        a++;
        b++;
    }

    // If we reach the end of one of the names,
    // the shorter name should come first (e.g., "Ann" before "Anna")
    return (int)(tolower((unsigned char)*a) -
                 (int)tolower((unsigned char)*b));
}

// This function swaps two students in the gradebook at positions i and j.
// It makes sure that the ID, name, and grade all move together,
// so the three parallel arrays stay in sync.
static void swap_students(int i, int j) {
    // If both positions are the same, there is nothing to swap
    if (i == j) {
        return;
    }

    //Swap IDs
    // Temporarily store the ID at i
    int temp_id = student_ids[i];
    // Move ID at j into position i
    student_ids[i] = student_ids[j];
    // Put the saved ID into position j
    student_ids[j] = temp_id;

    //Swap grades
    // Temporarily store the grade at i
    float temp_grade = student_grades[i];
    // Move grade at j into i
    student_grades[i] = student_grades[j];
    // Put the saved grade into j
    student_grades[j] = temp_grade;

    //Swap names
    // Temporary buffer to hold one name while we swap
    char temp_name[MAX_NAME_LENGTH];
    // Copy the name at i into the temporary buffer
    strcpy(temp_name, student_names[i]);
    // Move name at j into i
    strcpy(student_names[i], student_names[j]);
    // Put the original name from i into j
    strcpy(student_names[j], temp_name);
}

// Sorts students by ID in ascending order (smallest ID first).
void sort_by_id(void) {
    // n is how many students we currently have stored
    int n = get_student_count();

    // Start at index 1, because a single element at index 0 is already "sorted"
    for (int i = 1; i < n; i++) {
        // We will move the element at j left until it is in the correct place
        int j = i;

        // While j is not at the beginning and the current ID is smaller than the previous ID
        while (j > 0 && student_ids[j] < student_ids[j - 1]) {
            // Swap the two students so the smaller ID moves left
            swap_students(j, j - 1);
            // Move j one step to the left and keep checking
            j--;
        }
    }
}

// Sorts students by name in alphabetical order (A–Z).
// This also uses insertion sort, but the comparison is done on names instead of IDs.
void sort_by_name(void) {
    int n = get_student_count();

    // Again, we start from index 1 because index 0 alone is already "sorted"
    for (int i = 1; i < n; i++) {
        int j = i;

        // While j is not at the beginning and the current name should come
        // before the previous name alphabetically
        while (j > 0 &&
               compare_names_ci(student_names[j], student_names[j - 1]) < 0) {
            // Swap the two students so the name that should come earlier moves left
            swap_students(j, j - 1);
            // Move left and keep checking until the name is in the right spot
            j--;
        }
    }
}

// Sorts students by grade from highest to lowest.
void sort_by_grade(void) {
    int n = get_student_count();

    for (int i = 1; i < n; i++) {
        int j = i;

        while (j > 0 && student_grades[j] > student_grades[j - 1]) {
            // Swap the students so higher grades move toward the front
            swap_students(j, j - 1);
            j--;
        }
    }
}

// This function looks at all the grades and figures out:
// - the minimum grade
// - the maximum grade
// - the average grade
// It returns 0 if there are no students, and 1 if stats were calculated.
int calculate_stats(float *min_grade, float *max_grade, float *avg_grade) {
    int n = get_student_count();

    // If there are no students, it cannot calculate
    if (n == 0) {
        return 0;
    }

    // Starts by using the first student's grade as our initial min, max, and sum
    float min_val = student_grades[0];
    float max_val = student_grades[0];
    float sum = student_grades[0];

    // Go through the rest of the students and update min, max, and sum
    for (int i = 1; i < n; i++) {
        float g = student_grades[i];

        // Update minimum if this grade is smaller
        if (g < min_val) {
            min_val = g;
        }

        // Update maximum if this grade is larger
        if (g > max_val) {
            max_val = g;
        }

        // Add this grade to the running total for average
        sum += g;
    }

    // Write the results back through the pointer arguments if they are not NULL
    if (min_grade) {
        *min_grade = min_val;
    }
    if (max_grade) {
        *max_grade = max_val;
    }
    if (avg_grade) {
        *avg_grade = sum / n;  // Average is total divided by how many students
    }

    // Return 1 to say that the stats were successfully calculated
    return 1;
}

// This function calls calculate_stats() and then prints the results.
// If there are no students, it will prints a simple message instead.
void show_stats(void) {
    float min_grade, max_grade, avg_grade;

    // If calculate_stats returns 0, that means there were no students
    if (!calculate_stats(&min_grade, &max_grade, &avg_grade)) {
        printf("No students in gradebook. Statistics not available.\n");
        return;
    }

    // If we get here, we have valid statistics to print
    printf("Grade statistics:\n");
    printf("  Minimum grade: %.2f\n", min_grade);
    printf("  Maximum grade: %.2f\n", max_grade);
    printf("  Average grade: %.2f\n", avg_grade);
}
