/*

 This header declares the functions used for sorting student records
 and calculating simple statistics (min, max, and average grade).
 
*/

#ifndef SORT_H
#define SORT_H

// sorts students by ID in ascending order
void sort_by_id(void);

// sorts students by name in alphabetical order (A-Z)
void sort_by_name(void);

// sorts students by grade in descending order (highest to lowest)
void sort_by_grade(void);

// calculates min, max, and average grade; returns 0 if no students
int calculate_stats(float *min_grade, float *max_grade, float *avg_grade);

// prints min, max, and average grade, or a message if no students
void show_stats(void);

#endif
