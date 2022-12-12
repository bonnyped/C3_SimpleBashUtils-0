#include "common.h"

#include <stdio.h>
#include <stdlib.h>

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
    fprintf(stderr, "%s: Нет такого файла или каталога\n", file_to_open);
    exit(1);
  }
  return file_ptr;
}
