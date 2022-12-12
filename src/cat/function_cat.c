#include "function_cat.h"

#include <stddef.h>
#include <stdio.h>

#include "../common/common.h"

void check_options_cat(int argc, char **argv, int *position,
                       struct count_cat *flags) {
  char c = '0';
  extern int optind;
  struct option long_opts[] = {{"number-nonblank", 0, 0, 'b'},
                               {"number", 0, 0, 'n'},
                               {"squeeze-blank", 0, 0, 's'},
                               {0, 0, 0, 0}};

  while (c != -1) {
    if ((c = getopt_long(argc, argv, "benstvET", long_opts, NULL)) != -1) {
      switch (c) {
        case 'b':
          flags->b = 1;
          break;
        case 'e':
          flags->E = 1;
          flags->v = 1;
          flags->e = 0;
          break;
        case 'E':
          flags->E = 1;
          break;
        case 'n':
          flags->n = 1;
          break;
        case 's':
          flags->s = 1;
          break;
        case 't':
          flags->T = 1;
          flags->v = 1;
          flags->t = 0;
          break;
        case 'T':
          flags->T = 1;
          break;
        case 'v':
          flags->v = 1;
          break;
      }
    }
  }
  *position = optind;
}

void print_result(int argc, char **argv, int *file_postion,
                  struct count_cat *flags) {
  while (*file_postion < argc) {
    FILE *opened_file;
    opened_file = open_file(argv[*file_postion]);
    if (opened_file != NULL) {
      get_char_from_file(opened_file, flags);
    }
    fclose(opened_file);
    *file_postion = *file_postion + 1;
  }
}

void get_char_from_file(FILE *opened_file, struct count_cat *flags) {
  int number_of_line = 1;
  int counter_new_line_char = 0;
  int char_not_printed = 0;
  int count_for_b = 1;
  int count_for_n = 1;
  char previos_char, current_char, next_char;
  if ((next_char = fgetc(opened_file)) != EOF) {
    previos_char = next_char;
    while ((current_char = next_char) != EOF) {
      char_not_printed = 1;
      next_char = fgetc(opened_file);
      if (flags->s) {
        char_not_printed = print_s(current_char, next_char,
                                   &counter_new_line_char, number_of_line);
      }
      if (flags->b && char_not_printed == 1) {
        print_b(number_of_line, &count_for_b, previos_char, current_char,
                next_char, flags);
      }
      if (flags->n && char_not_printed == 1) {
        print_n(number_of_line, previos_char, current_char, next_char,
                &count_for_n);
      }
      if (char_not_printed == 1) {
        if (flags->E && current_char == '\n') {
          printf("$");
        }
        if (flags->E && (flags->b || flags->n) && number_of_line == 1 &&
            next_char == '\n') {
          printf("%c", current_char);
          char_not_printed = 0;
        }
        if (flags->T && char_not_printed == 1) {
          char_not_printed = print_T(current_char, char_not_printed);
        }
        if (flags->v && char_not_printed == 1) {
          char_not_printed = print_v(current_char, char_not_printed);
        }
        if (char_not_printed == 1) {
          printf("%c", current_char);
        }
      }
      if (current_char == '\n') {
        number_of_line++;
      }
      previos_char = current_char;
    }
  }
}

int print_s(char current, char next, int *new_line_char, int number_of_line) {
  int result = -1;
  if (current != '\n' && *new_line_char < 3) {
    *new_line_char = 0;
  }
  if (*new_line_char > 2 && next != '\n') {
    *new_line_char = 0;
  }
  if (((current == '\n' || next == '\n') && number_of_line == 1)) {
    *new_line_char = *new_line_char + 1;
  }
  if (next == '\n' && number_of_line != 1) {
    *new_line_char = *new_line_char + 1;
  }
  if (*new_line_char > 2) {
    result = 0;
  } else {
    result = 1;
  }
  return result;
}

void print_b(int number_of_line, int *count, char previos, char current,
             char next, struct count_cat *flags) {
  flags->n = 0;
  if (number_of_line == 1 && current != '\n' && *count == 1) {
    printf("%6d\t", *count);
    *count = *count + 1;
  }
  if (previos == '\n' && current != '\n') {
    printf("%6d\t", *count);
    *count = *count + 1;
  }
  if (current == '\n' && next == EOF) {
    ;
  }
}

void print_n(int number_of_line, char previos, char current, char next,
             int *count) {
  if (number_of_line == 1 && *count == 1) {
    printf("%6d\t", *count);
    *count = *count + 1;
  }
  if (number_of_line != 1 && previos == '\n' && next != EOF) {
    printf("%6d\t", *count);
    *count = *count + 1;
  } else if (previos == '\n' && current == '\n' && number_of_line != 1) {
    printf("%6d\t", *count);
  } else if (current == '\n' && next == EOF) {
    ;
  }
}

int print_T(char current_char, int char_not_printed) {
  int result = char_not_printed;
  if (current_char == 9) {
    printf("^I");
    result = 0;
  } else {
    ;
  }
  return result;
}

int print_v(char current, int char_not_printed) {
  int result = char_not_printed;
  if (current <= 31 && current >= 0 && current != 9 && current != 10) {
    printf("%c%c", '^', (current += 64));
    result = 0;
  } else if (current == 127) {
    printf("%c%c", '^', (current -= 64));
    result = 0;
  }
  return result;
}
