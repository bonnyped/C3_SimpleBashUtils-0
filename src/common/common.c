#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

/*common functions */
void usage(int argc, char *name_of_program) {
    if(argc == 1){
        printf("Используйте опции, параметры и аргуемнты функции %s\n", name_of_program);
        exit(1);
        }
}

FILE *open_file(char *file_to_open) {
    FILE *file_ptr;
    
    file_ptr = fopen(file_to_open, "r");
    if(!file_ptr) {
        printf("Нет такого файла или каталога\n");
     } else 
     return file_ptr;
}

void print_opened_file_without_the_flag(FILE *opened_file) {
    char c;

    while((c = fgetc(opened_file)) != EOF){ printf("%c", c); }
}

