#ifndef FUNCTION_GREP_H
#define FUNCTION_GREP_H
#define BUFFSIZE 4000
#include <regex.h>
#include <stdio.h>

#include "../common/common.h"

struct count_grep {
  int e, i, v, c, l, n, h, s, f, o;
};

char *read_string_from_file(FILE *opened_file, int capacity, char **argv,
                            int position);
int count_max_str_length(FILE *opened_file, int *max_num_strings);
int check_options_grep(int argc, char **argv, struct count_grep *flags,
                       char *buffer_for_opt_arg, int *element_to_write,
                       int *is_flag_opt);
void save_arg_opt_e(char *buffer, char *optarg, int capacity,
                    int *element_to_write);
void save_arg_opt_f(char *buffer, char *optarg, int *element_to_write);
int save_arg_of_option(char *argument, char *buffer, int start_write_element,
                       struct count_grep *flags,
                       int *max_number_of_string_in_file);
void regex_compile(regex_t *re, char *buffer, struct count_grep *flags);
int counting_capacity(char **argv, int position, int *max_num_strings,
                      struct count_grep *flags);
void print_lines_found(int argc, char **argv, int position,
                       int *max_number_strings, regex_t regexed,
                       struct count_grep *flags);
void print_if_more_than_one_file(int argc, char **argv, int position,
                                 int *argv_was_printed,
                                 struct count_grep *flags);
void print_l_flag(char **argv, int position, int *flag_for_l,
                  struct count_grep *flags);
void print_c_flag(struct count_grep *flags, int count, int i, int *max_number,
                  int *was_printed);
void print_n_flag(struct count_grep *flags, int iteration);
void print_o_flag(char *line, int res_regexec, regex_t regexed,
                  struct count_grep *flags, int iteration, char **argv,
                  int position, int count);
void print_matched_line(struct count_grep *flags, char *line_from_file);

#endif