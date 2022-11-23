#ifndef COMMON_H
#define COMMON_H

// #include <getopt.h>


struct count_cat {int b, e, n, s, t, v, E, T;};
struct count_grep {int e, i, v, c, l, n, h, s, f, o;};

void usage(int argc, char *name_of_program);
FILE *open_file(char *file_to_open);

void check_options_cat(int argc, char **argv, int *number_of_element_of_argv, int *count_of_flags, struct count_cat *flags);
void scan_selected_flags_in_struct_and_print(int argc, char **argv, int *number_of_element_of_argv, struct count_cat *flags, int *count_of_flags);
void print_flag_n(char current, char next, int number_of_string_in_opened_file, int *numbering);
void print_flag_E(char current, char next, int number_of_string_in_opened_file);
void print_flag_b(char current, char next, int number_of_string_in_opened_file, int *numbering);
void print_flag_s(char current, char next, int *counter_n, int count_of_flags);
void print_flag_T(char current, int no_another_flag);
void print_flag_v(char current, int no_another_flag);

void print_opened_file_without_the_flag(FILE *opened_file);
void check_options_grep(int argc, char **argv, struct count_grep *flags);

#endif
