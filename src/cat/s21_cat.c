#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"

int main(int argc, char **argv) {
    int number_of_element_of_argv = 1, count_of_flags = 0;
    struct count_cat flags = {0};
    
    usage(argc, argv[0]);
    check_options_cat(argc, argv, &number_of_element_of_argv, &count_of_flags, &flags);
    scan_selected_flags_in_struct_and_print(argc, argv, &number_of_element_of_argv, &flags, &count_of_flags);

    return 0;
}

