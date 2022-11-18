#ifndef COMMON_H
#define COMMON_H

void usage(int argc, char *name_of_program);
FILE *open_file(char *file_to_open);
void print_opened_file_without_the_flag(FILE *opened_file);

#endif
