#ifndef FUNCTION_CAT_H
#define FUNCTION_CAT_H

#include "../common/common.h"

struct count_cat {
  int b, e, n, s, t, v, E, T;
};

void check_options_cat(int argc, char **argv, int *position,
                       struct count_cat *flags);
void print_result(int argc, char **argv, int *file_postion,
                  struct count_cat *flags);
void get_char_from_file(FILE *opened_file, struct count_cat *flags);
int print_s(char current, char next, int *new_line_char, int number_of_line);
void print_b(int number_of_line, int *count, char previos, char current,
             char next, struct count_cat *flags);
void print_n(int number_of_line, char previos, char current, char next,
             int *count);
int print_T(char current_char, int char_not_printed);
int print_v(char current, int char_not_printed);

#endif