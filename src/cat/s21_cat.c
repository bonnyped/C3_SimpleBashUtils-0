#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"
#include "function_cat.h"

int main(int argc, char **argv) {
  int file_position = 1;
  struct count_cat flags = {0};

  usage(argc, argv[0]);
  check_options_cat(argc, argv, &file_position, &flags);
  print_result(argc, argv, &file_position, &flags);

  return 0;
}
