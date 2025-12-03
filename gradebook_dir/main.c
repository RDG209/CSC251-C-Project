#include <stdio.h>
#include "gradebook.h"
#include "file.h" 
#include "sort.h"
#include "ui.h"

int main() {
    
    // 1. Load the students.txt data, no worries if none exists
    load_from_file();
    // 2. call ui show_menu();
    show_menu();
    // 3. save any changes before exiting, will create file if none existed before
    save_to_file();

    return 0;
}
