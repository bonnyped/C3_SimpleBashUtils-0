#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"

int main(int argc, char **argv) {
  struct count_grep flags = {0};
  regex_t regexed;
  char optarg[BUFFSIZE], *line_from_file;
  int count_opt = 0, position_name_file = 1, element_mass_to_write = 0,
      max_number_of_string_in_file = 0, capacity = 0, is_flag_opt = 0;
  usage(argc, argv[0]);
  position_name_file =
      check_options_grep(argc, argv, &flags, optarg, &element_mass_to_write,
                         &max_number_of_string_in_file, &is_flag_opt);
  if (((flags.e < 1) && (flags.f < 1) && (is_flag_opt == 1)) ||
      is_flag_opt == 0) {
    regexed = regex_compile(argv[position_name_file], &flags);
    position_name_file++;
    print_lines_found(argc, argv, position_name_file,
                      &max_number_of_string_in_file, optarg, regexed, &flags);
  }
  if (flags.e > 0 || flags.f > 0) {
    optarg[element_mass_to_write - 1] = '\0';
    regexed = regex_compile(optarg, &flags);

    print_lines_found(argc, argv, position_name_file,
                      &max_number_of_string_in_file, optarg, regexed, &flags);
  }
  return 0;
}
