/*
 
 Sorting and Statistics

 This file sorts the students and computes grade statistics.
 
*/

#include <stdio.h>
#include <ctype.h>
#include "gradebook.h"
#include "sort.h"

// case-insensitive string comparison
static int name_compare_ci(const char *a, const char *b) {
    while (*a && *b) {
        char ca = (char)tolower((unsigned char)*a);
        char cb = (char)tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

// sort by ID (ascending order)
void sort_by_id(void) {
    int n = get_student_count();

    for (int i = 1; i < n; i++) {
        int j = i;

        while (j > 0) {
            int id_j = get_student_id_at(j);
            int id_prev = get_student_id_at(j - 1);

            if (id_j < id_prev) {
                swap_student_positions(j, j - 1);
                j--;
            } else break;
        }
    }
}

// sorts by name (A to Z)
void sort_by_name(void) {
    int n = get_student_count();

    for (int i = 1; i < n; i++) {
        int j = i;

        while (j > 0) {
            const char *name_j = get_student_name_at(j);
            const char *name_prev = get_student_name_at(j - 1);

            if (name_j == NULL || name_prev == NULL) break;

            if (name_compare_ci(name_j, name_prev) < 0) {
                swap_student_positions(j, j - 1);
                j--;
            } else break;
        }
    }
}

// sort by highest to lowest grades
void sort_by_grade(void) {
    int n = get_student_count();

    for (int i = 1; i < n; i++) {
        int j = i;

        while (j > 0) {
            float g_j = get_student_grade_at(j);
            float g_prev = get_student_grade_at(j - 1);

            if (g_j > g_prev) {
                swap_student_positions(j, j - 1);
                j--;
            } else break;
        }
    }
}

// calculates min, max, average
int calculate_stats(float *min_grade, float *max_grade, float *avg_grade) {
    int n = get_student_count();
    if (n == 0) return 0;

    float g0 = get_student_grade_at(0);
    float minv = g0;
    float maxv = g0;
    float sum = g0;

    for (int i = 1; i < n; i++) {
        float g = get_student_grade_at(i);
        if (g < minv) minv = g;
        if (g > maxv) maxv = g;
        sum += g;
    }

    *min_grade = minv;
    *max_grade = maxv;
    *avg_grade = sum / n;

    return 1;
}

// print stats
void show_stats(void) {
    float minv, maxv, avg;

    if (!calculate_stats(&minv, &maxv, &avg)) {
        printf("No students. Statistics unavailable.\n");
        return;
    }

    printf("Grade statistics:\n");
    printf("  Minimum grade: %.2f\n", minv);
    printf("  Maximum grade: %.2f\n", maxv);
    printf("  Average grade: %.2f\n", avg);
}
