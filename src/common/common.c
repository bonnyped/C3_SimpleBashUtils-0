#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE
#include "common.h"

// общие ф-ции

void usage(int argc, char *name_of_program) {
  if (argc == 1) {
    fprintf(stderr, "Используйте опции, параметры и аргуемнты функции %s\n",
            name_of_program);
    exit(1);
  }
}

FILE *open_file(char *file_to_open) {
  FILE *file_ptr;
  file_ptr = fopen(file_to_open, "r");
  if (!file_ptr) {
    fprintf(stderr, "grep: %s: Нет такого файла или каталога\n", file_to_open);
    file_ptr = NULL;
  }
  return file_ptr;
}

// ф-ции для Сat
void check_options_cat(int argc, char **argv, int *number_of_element_of_argv,
                       int *count_of_flags, struct count_cat *flags) {
  char c = '0';
  struct option long_opts[] = {{"number-nonblank", 0, 0, 'b'},
                               {"number", 0, 0, 'n'},
                               {"squeeze-blank", 0, 0, 's'},
                               {0, 0, 0, 0}};

  while (c != -1) {
    if ((c = getopt_long(argc, argv, "benstvET", long_opts, NULL)) != -1) {
      *count_of_flags = *count_of_flags + 1;
      switch (c) {
        case 'b':
          flags->b = 'b';
          break;
        case 'e':
          flags->e = 'e';
          break;
        case 'E':
          flags->E = 'E';
          break;
        case 'n':
          flags->n = 'n';
          break;
        case 's':
          flags->s = 's';
          break;
        case 't':
          flags->t = 't';
          break;
        case 'T':
          flags->T = 'T';
          break;
        case 'v':
          flags->v = 'v';
          break;
      }
    }
  }
  if (*count_of_flags > 0) {
    *number_of_element_of_argv = 2;
  }
}

void scan_selected_flags_in_struct_and_print(int argc, char **argv,
                                             int *number_of_element_of_argv,
                                             struct count_cat *flags,
                                             int *count_of_flags) {
  int numbering = 1, counter_n = 1;
  char current_char, next_char, post_next_char;
  while (*number_of_element_of_argv < argc) {
    FILE *opened_file;
    opened_file = open_file(argv[*number_of_element_of_argv]);
    if (opened_file != NULL) {
      if ((next_char = fgetc(opened_file)) != EOF) {
        int number_of_string_in_opened_file = 1;
        while ((current_char = next_char) != EOF) {
          next_char = fgetc(opened_file);
          if (*number_of_element_of_argv == 1) {
            printf("%c", current_char);
          } else {
            if (flags->e != 0) {
              flags->E = flags->v = *count_of_flags = 2;
            }
            if (flags->t != 0) {
              flags->T = flags->v = *count_of_flags = 2;
            }
            if (flags->n != 0) {
              print_flag_n(current_char, next_char,
                           number_of_string_in_opened_file, &numbering);
            }
            if (flags->E != 0) {
              print_flag_E(current_char, next_char,
                           number_of_string_in_opened_file);
            }
            if (flags->b != 0) {
              print_flag_b(current_char, next_char,
                           number_of_string_in_opened_file, &numbering);
            }
            if (flags->s != 0) {
              print_flag_s(current_char, next_char, &counter_n,
                           *count_of_flags);
            }
            if (flags->T != 0) {
              print_flag_T(current_char, *count_of_flags);
            }
            if (flags->v != 0) {
              print_flag_v(current_char, *count_of_flags);
            }
            number_of_string_in_opened_file++;
          }
        }
        fclose(opened_file);
        *number_of_element_of_argv = *number_of_element_of_argv + 1;
      }
    }
  }
}

void print_flag_n(char current, char next, int number_of_string_in_opened_file,
                  int *numbering) {
  if (number_of_string_in_opened_file == 1) {
    printf("%6d\t", *numbering);
    *numbering = *numbering + 1;
  }
  if (current != '\n') {
    printf("%c", current);
  } else {
    if (next != EOF) {
      printf("%c%6d\t", current, *numbering);
      *numbering = *numbering + 1;
    } else {
      printf("%c", current);
    }
  }
}

void print_flag_E(char current, char next,
                  int number_of_string_in_opened_file) {
  if (current == '\n' && number_of_string_in_opened_file == 1) {
    printf("$%c", current);
  } else if (next == '\n') {
    printf("%c$", current);
  } else {
    printf("%c", current);
  }
}

void print_flag_b(char current, char next, int number_of_string_in_opened_file,
                  int *numbering) {
  if (current == '\n' && number_of_string_in_opened_file == 1 && next != '\n') {
    printf("%c%6d\t", current, *numbering);
    *numbering = *numbering + 1;
  } else if (current != '\n' && number_of_string_in_opened_file == 1) {
    printf("%6d\t%c", *numbering, current);
    *numbering = *numbering + 1;
  } else if (current == '\n' && next == '\n') {
    printf("%c", current);
  } else if (current == '\n' && next != '\n' && next != EOF) {
    printf("%c%6d\t", current, *numbering);
    *numbering = *numbering + 1;
  } else {
    printf("%c", current);
  }
}

void print_flag_s(char current, char next, int *counter_n, int count_of_flags) {
  if (*counter_n < 3 && count_of_flags == 1) {
    printf("%c", current);
  } else
    ;
  if (current == '\n' && next == '\n') {
    *counter_n = *counter_n + 1;
  }
  if (next != '\n') {
    *counter_n = 1;
  }
}

void print_flag_T(char current, int no_another_flag) {
  current == 9 ? printf("^I") : (current <= 31 && current >= 0 && current != 9 && current != 10 || current == 127) ? : printf("%c", current);
  if (no_another_flag == 0) {
    printf("%c", current);
  }
}

void print_flag_v(char current, int no_another_flag) {
  if (current <= 31 && current >= 0 && current != 9 && current != 10) {
    printf("%c%c", '^', (current += 64));
  } else if (current == 127) {
    printf("%c%c", '^', (current - 64));
  } else if (no_another_flag == 1)
    printf("%c", current);
}

// ф-ции для Grep
int check_options_grep(int argc, char **argv, struct count_grep *flags,
                       char *buffer_for_opt_arg, int *element_to_write,
                       int *max_num_strings, int *is_flag_opt) {
  extern char *optarg;
  char *line_from_file, c, string_flags[12] = "e:f:ivclnhso";
  int max_capacity_file;
  FILE *opened_file;

  while ((c = getopt_long(argc, argv, string_flags, NULL, NULL)) != -1) {
    *is_flag_opt = 1;
    switch (c) {
      case 'e':
        flags->e += 1;
        max_capacity_file = strlen(optarg);
        save_arg_opt_e(buffer_for_opt_arg, optarg, max_capacity_file,
                       element_to_write);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        save_arg_opt_f(buffer_for_opt_arg, optarg, element_to_write);
        break;
      case 'o':
        flags->o = 1;
        break;
    }
  }
  return optind;
}

void save_arg_opt_e(char *buffer, char *optarg, int capacity,
                    int *element_to_write) {
  for (int i = 0; i < capacity; i++) {
    buffer[*element_to_write + i] = optarg[i];
  }
  buffer[*element_to_write + capacity] = '|';
  *element_to_write = *element_to_write + capacity + 1;
}

void save_arg_opt_f(char *buffer, char *optarg, int *element_to_write) {
  FILE *opened_file;
  opened_file = open_file(optarg);
  char current_char, next_char;
  int start = *element_to_write;
  next_char = getc(opened_file);
  if ((next_char != EOF)) {
    while ((current_char = next_char) != EOF) {
      buffer[start] = current_char;
      next_char = getc(opened_file);
      next_char == '\n' ? next_char = '|' : next_char;
      start++;
    }
  }
  *element_to_write = start;
  fclose(opened_file);
  // buffer[start - 1] == '|' ? buffer[start - 1] = '\0' : buffer[start - 1];
}

char *read_string_from_file(FILE *opened_file, int capacity) {
  char *line;
  line = malloc(sizeof(char) * capacity);
  fgets(line, capacity, opened_file);
  if (line != NULL) {
    return line;
  }
}

int count_max_str_length(FILE *opened_file, int *max_num_strings) {
  int current_capacity = 0, max = 0, count = 0;
  char c, next_c;
  next_c = fgetc(opened_file);
  while ((c = next_c) != EOF) {
    next_c = fgetc(opened_file);
    if (c != '\n' && next_c == EOF) {
      count++;
    }
    if (c != '\n') {
      current_capacity++;
    } else {
      current_capacity++;
      if (current_capacity > max) {
        max = current_capacity;
      }
      count++;
      current_capacity = 0;
    }
    // if (c != '\n' && (next_c = fgetc(opened_file) == EOF)) {
    //   count++;
    // }
  }
  *max_num_strings = count;
  return max * 4;
}

regex_t regex_compile(char *buffer, struct count_grep *flags) {
  regex_t re;
  regcomp(&re, buffer, flags->i == 1 ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
  return re;
}

int counting_capacity(char **argv, int position, int *max_num_strings,
                      struct count_grep *flags) {
  int capacity;
  FILE *opened_file;
  if ((opened_file = fopen(argv[position], "r")) == NULL) {
    if (flags->s == 0) {
      fprintf(stderr, "grep: %s: Нет такого файла или каталога\n",
              argv[position]);
    }
    capacity = -1;
  } else {
    capacity = count_max_str_length(opened_file, max_num_strings);
    fclose(opened_file);
  }
  return capacity;
}

void print_lines_found(int argc, char **argv, int position,
                       int *max_number_strings, char *buffer, regex_t regexed,
                       struct count_grep *flags) {
  int capacity = 0, flag = 0, regexeced, count = 0, flag_for_l = 0;
  char *line_from_file;
  (argc - position - 1) > 0 ? flag = 1 : flag;
  for (position; position < argc; position++) {
    if ((capacity = counting_capacity(argv, position, max_number_strings,
                                      flags)) != -1) {
      FILE *opened_file;
      opened_file = open_file(argv[position]);
      for (int i = 0; i < *max_number_strings; i++) {
        line_from_file = read_string_from_file(opened_file, capacity);
        if (i == *max_number_strings - 1) {
          int tmp = strlen(line_from_file);
          if (line_from_file[tmp - 1] != '\n') {
            line_from_file[tmp] = '\n';
            line_from_file[tmp + 1] = '\0';
          }
        }
        regexeced = regexec(&regexed, line_from_file, 0, NULL, 0);
        if ((flags->v == 0 ? regexeced == 0 : regexeced != 0)) {
          if (flags->l > 0) {
            if (flag_for_l == 0) {
              printf("%s\n", argv[position]);
              flag_for_l = 1;
            }
          } else if (flags->c > 0 && flags->l == 0) {
            count++;
          } else {
            if (flag == 1 && flags->h == 0) {
              printf("%s:", argv[position]);
              if (flags->n > 0 && flags->c == 0) {
                printf("%d:", i + 1);
              }
              // if (flags->n > 0 && flags->c == 0) {
              //   printf("%d:", i + 1);
              // }
              printf("%s", line_from_file);
            } else {
              if (flags->n > 0 && flags->c == 0) {
                printf("%d:", i + 1);
              }
              printf("%s", line_from_file);
            }
          }
        }
        free(line_from_file);
      }
      if (flags->c > 0 && flags->l == 0) {
        printf("%d\n", count);
      }
      fclose(opened_file);
    }
  }
  regfree(&regexed);
}