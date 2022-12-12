#include "function_grep.h"

#include "../common/common.h"

int check_options_grep(int argc, char **argv, struct count_grep *flags,
                       char *buffer_for_opt_arg, int *element_to_write,
                       int *is_flag_opt) {
  extern char *optarg;
  char c, string_flags[12] = "e:f:ivclnhso";
  unsigned max_capacity_file;

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
  char c;
  int i = 0;
  FILE *opened_file;
  opened_file = open_file(optarg);
  if (opened_file != NULL) {
    while ((c = fgetc(opened_file)) != EOF) {
      if (c == '\n' && i != 0 && buffer[*element_to_write - 1] != '|') {
        buffer[*element_to_write] = '|';
      } else if (c == '\n' && buffer[i - 1] == '|') {
        buffer[*element_to_write] = c;
        i++;
        buffer[*element_to_write + 1] = '|';
        *element_to_write = *element_to_write + 1;
      } else {
        buffer[*element_to_write] = c;
      }
      *element_to_write = *element_to_write + 1;
      i++;
    }
    fclose(opened_file);
  }
}

char *read_string_from_file(FILE *opened_file, int capacity, char **argv,
                            int position) {
  char *line;
  line = malloc(sizeof(char) * capacity);
  line[0] = '\0';
  fgets(line, capacity, opened_file);
  if (line == NULL) {
    fprintf(stderr, "s21_grep:%s: Не удалось считать строку\n", argv[position]);
    exit(1);
  }
  return line;
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
  }
  *max_num_strings = count;
  return max * 4;
}

void regex_compile(regex_t *re, char *buffer, struct count_grep *flags) {
  regcomp(re, buffer,
          flags->i == 1 ? (REG_EXTENDED | REG_ICASE) : REG_EXTENDED);
}

int counting_capacity(char **argv, int position, int *max_num_strings,
                      struct count_grep *flags) {
  int capacity;
  FILE *opened_file;
  if ((opened_file = fopen(argv[position], "r")) == NULL) {
    if (flags->s == 0) {
      fprintf(stderr, "s21_grep: %s: Нет такого файла или каталога\n",
              argv[position]);
    }
    capacity = -1;
  } else {
    capacity = count_max_str_length(opened_file, max_num_strings);
  }
  if (opened_file != NULL) {
    fclose(opened_file);
  }
  return capacity;
}

void print_lines_found(int argc, char **argv, int position,
                       int *max_number_strings, regex_t regexed,
                       struct count_grep *flags) {
  int capacity, regexeced, flag_for_l, files_count, count, matched_in_string,
      flag_c_was_printed, argv_was_printed, argv_plus_count_was_printed;
  char *line_from_file = {0};
  files_count = (argc - position - 1);
  for (; position < argc; position++) {
    if ((capacity = counting_capacity(argv, position, max_number_strings,
                                      flags)) != -1) {
      FILE *opened_file;
      opened_file = open_file(argv[position]);
      count = 0;
      flag_for_l = 0;
      flag_c_was_printed = 0;
      argv_plus_count_was_printed = 0;
      argv_was_printed = 0;
      for (int i = 0; i < *max_number_strings; i++) {
        matched_in_string = 0;
        line_from_file =
            read_string_from_file(opened_file, capacity, argv, position);
        if (i + 1 == *max_number_strings) {
          int tmp = strlen(line_from_file);
          if (line_from_file[tmp - 1] != '\n') {
            line_from_file[tmp] = '\n';
            line_from_file[tmp + 1] = '\0';
          }
        }
        regexeced = regexec(&regexed, line_from_file, 0, NULL, 0);
        if ((flags->v == 0 ? regexeced == 0 : regexeced != 0)) {
          matched_in_string = 1;
          count++;
        }
        if (matched_in_string == 1) {
          if (files_count > 0 && flags->l == 0 && flags->h == 0) {
            if ((flags->c > 0 && argv_was_printed == 0) ||
                (flags->c == 0 && flags->o == 0)) {
              printf("%s:", argv[position]);
              argv_was_printed = 1;
            }
          }
          print_l_flag(argv, position, &flag_for_l, flags);
          print_c_flag(flags, count, i, max_number_strings,
                       &flag_c_was_printed);
          print_o_flag(line_from_file, regexeced, regexed, flags, i, argv,
                       position, files_count);
          print_n_flag(flags, i);
          print_matched_line(flags, line_from_file);
        }
        free(line_from_file);
      }
      if (flag_c_was_printed == 0 && flags->c > 0 && flags->l == 0) {
        if (files_count > 0 && flags->l == 0 && flags->h == 0 &&
            argv_was_printed == 0) {
          printf("%s:%d\n", argv[position], count);
          argv_plus_count_was_printed++;
        }
        if (argv_plus_count_was_printed == 0) {
          printf("%d\n", count);
        }
      }
      fclose(opened_file);
    }
  }
  regfree(&regexed);
}

void print_l_flag(char **argv, int position, int *flag_for_l,
                  struct count_grep *flags) {
  if (*flag_for_l == 0 && flags->l > 0) {
    printf("%s\n", argv[position]);
    *flag_for_l = *flag_for_l + 1;
    flags->c = 0;
    flags->o = 0;
    flags->n = 0;
  }
}

void print_c_flag(struct count_grep *flags, int count, int i, int *max_number,
                  int *was_printed) {
  if (flags->c > 0) {
    flags->o = 0;
    flags->n = 0;
    if (i + 1 == *max_number) {
      printf("%d\n", count);
      *was_printed = *was_printed + 1;
    }
  }
}

void print_n_flag(struct count_grep *flags, int iteration) {
  int number_of_string = iteration + 1;
  if (flags->n > 0 && flags->o == 0) {
    printf("%d:", number_of_string);
  }
}

void print_o_flag(char *line, int res_regexec, regex_t regexed,
                  struct count_grep *flags, int iteration, char **argv,
                  int position, int count) {
  regmatch_t pmatch;
  unsigned start_to_search = 0, length = strlen(line);
  int number_of_string = iteration + 1;

  if (flags->o > 0 && res_regexec == 0) {
    while (start_to_search < length - 1) {
      regexec(&regexed, line + start_to_search, 1, &pmatch, 0);
      if ((line[pmatch.rm_eo] != '\0' && line[pmatch.rm_so] != '\n' &&
           length != 1 && pmatch.rm_eo != pmatch.rm_so)) {
        if (count > 0 && flags->l == 0 && flags->h == 0) {
          printf("%s:", argv[position]);
        }
        if (flags->n > 0) {
          printf("%d:", number_of_string);
        }
        for (; pmatch.rm_so < pmatch.rm_eo; pmatch.rm_so++) {
          printf("%c", line[start_to_search + pmatch.rm_so]);
        }
        start_to_search += pmatch.rm_eo;
        printf("\n");
      } else {
        start_to_search = length;
      }
    }
  }
}

void print_matched_line(struct count_grep *flags, char *line_from_file) {
  if (flags->l == 0 && flags->c == 0 && flags->o == 0) {
    printf("%s", line_from_file);
  }
}
