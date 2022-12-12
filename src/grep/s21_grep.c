#include <regex.h>
#include <stdio.h>

#include "../common/common.h"
#include "function_grep.h"

int main(int argc, char **argv) {
  struct count_grep flags = {0};
  regex_t regexed = {0};
  char optarg[BUFFSIZE] = {0};
  int position_name_file = 1, element_mass_to_write = 0,
      max_number_of_string_in_file = 0, is_flag_opt = 0;
  usage(argc, argv[0]);
  position_name_file = check_options_grep(argc, argv, &flags, optarg,
                                          &element_mass_to_write, &is_flag_opt);
  if (((flags.e < 1) && (flags.f < 1) && (is_flag_opt == 1)) ||
      is_flag_opt == 0) {
    regex_compile(&regexed, argv[position_name_file], &flags);
    position_name_file++;
    print_lines_found(argc, argv, position_name_file,
                      &max_number_of_string_in_file, regexed, &flags);
  }
  if (flags.e > 0 || flags.f > 0) {
    if (optarg[element_mass_to_write - 1] == '|') {
      optarg[element_mass_to_write - 1] = '\0';
    }
    regex_compile(&regexed, optarg, &flags);

    print_lines_found(argc, argv, position_name_file,
                      &max_number_of_string_in_file, regexed, &flags);
  }
  return 0;
}
