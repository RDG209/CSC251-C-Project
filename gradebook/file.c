//file.c
#include <stdio.h>
#include "gradebook.h" // access the right arrays

void load_from_file(void) {
    if (!file_exists()) { // T=1, F=0
        return;   // don't load any data if false
    }
    
    FILE *record = fopen("students.txt", "r");
    
    // Error catcher
    if (record == NULL) {
        printf("ERROR IN OPENING students.txt FOR READING\n");
        return;
    }
    
    int id;
    char name[100];
    float grade;
    
    while (fscanf(record, "%d,%99[^,],%f", &id, name, &grade) == 3) { // ensures all three data points can be found
        add_student(id, name, grade);
    }
    
    fclose(record);
}

void save_to_file(void) {
    FILE *record = fopen("students.txt", "w");
    if (record == NULL) {
        printf("ERROR IN OPENING students.txt FOR WRITING\n");
        return;
    }
    
    for (int i = 0; i < get_student_count(); i++) {
        int id = get_student_id(i);
        char name[100];
        float grade;
        get_student_data(i, &id, name, &grade);  // make sure to use *id *name *grade for the real function
        fprintf(record, "%d,%s,%.2f\n", id, name, grade);
    }
    fclose(record);
}

int file_exists(void) {
    FILE *record = fopen("students.txt", "r");
    if (record != NULL) {
        fclose(record);
        return 1;  // file exist
    } else {
        return 0;  // file no exist
    }
}
