// file.h
#ifndef FILE_H
#define FILE_H

int file_exists(void);  /// declared first
void load_from_file(const char* filename); /// now will accept any filename
void save_to_file(const char* filename);

#endif
