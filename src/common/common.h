#ifndef COMMON_H
#define COMMON_H
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFSIZE 8000

struct count_cat {
  int b, e, n, s, t, v, E, T;
};
struct count_grep {
  int e, i, v, c, l, n, h, s, f, o;
};

void usage(int argc, char *name_of_program);
FILE *open_file(char *file_to_open);

void check_options_cat(int argc, char **argv, int *number_of_element_of_argv,
                       int *count_of_flags, struct count_cat *flags);
void scan_selected_flags_in_struct_and_print(int argc, char **argv,
                                             int *number_of_element_of_argv,
                                             struct count_cat *flags,
                                             int *count_of_flags);
void print_flag_n(char current, char next, int number_of_string_in_opened_file,
                  int *numbering);
void print_flag_E(char current, char next, int number_of_string_in_opened_file);
void print_flag_b(char current, char next, int number_of_string_in_opened_file,
                  int *numbering);
void print_flag_s(char current, char next, int *counter_n, int count_of_flags);
void print_flag_T(char current, int no_another_flag);
void print_flag_v(char current, int no_another_flag);

char *read_string_from_file(FILE *opened_file, int capacity);
int count_max_str_length(FILE *opened_file, int *max_num_strings);
int file_name_positioning(int count_opt, struct count_grep *flags);
int check_options_grep(int argc, char **argv, struct count_grep *flags,
                       char *buffer_for_opt_arg, int *element_to_write,
                       int *max_num_strings, int *is_flag_opt);
void save_arg_opt_e(char *buffer, char *optarg, int capacity,
                    int *element_to_write);
void save_arg_opt_f(char *buffer, char *optarg, int *element_to_write);
int save_arg_of_option(char *argument, char *buffer, int start_write_element,
                       struct count_grep *flags,
                       int *max_number_of_string_in_file);
regex_t regex_compile(char *buffer, struct count_grep *flags);
int counting_capacity(char **argv, int position, int *max_num_strings,
                      struct count_grep *flags);
void print_lines_found(int argc, char **argv, int position,
                       int *max_number_strings, char *buffer, regex_t regexed,
                       struct count_grep *flags);
void print_if_more_than_one_file(int argc, char **argv, int position,
                                 int *argv_was_printed,
                                 struct count_grep *flags);
void print_l_flag(char **argv, int position, int *flag_for_l,
                  struct count_grep *flags);
void print_c_flag(char *line_from_file, struct count_grep *flags, int count,
                  int i, int *max_number, int *was_printed);
void print_n_flag(struct count_grep *flags, int iteration);
// void print_o_flag(char *line, int res_regexec, regex_t regexed,
// struct count_grep *flags, int iteration);
void print_matched_line(struct count_grep *flags, char *line_from_file);

#endif
