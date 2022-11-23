#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "common.h"

// общие ф-ции

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

// ф-ции для Сat

void check_options_cat(int argc, char **argv, int *number_of_element_of_argv, int *count_of_flags, struct count_cat *flags) {
    char c;
    struct option long_opts[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0}
};

    while(c != -1){     
        if((c = getopt_long(argc, argv, "benstvET", long_opts, NULL)) != -1) {           
        *count_of_flags = *count_of_flags + 1;
        switch(c) {
            case 'b': 
                flags -> b = 'b';
                break;
            case 'e': 
                flags -> e = 'e';
                break;
            case 'E': 
                flags -> E = 'E';
                break;
            case 'n': 
                flags -> n = 'n';
                break;
            case 's': 
                flags -> s = 's';
                break;
            case 't': 
                flags -> t = 't';
                break;
            case 'T': 
                flags -> T = 'T';
                break;
            case 'v': 
                flags -> v = 'v';
                break;
            }
        } 
    }
    if(*count_of_flags > 0) {*number_of_element_of_argv = 2; }
}

void scan_selected_flags_in_struct_and_print(int argc, char **argv, int *number_of_element_of_argv, struct count_cat *flags, int *count_of_flags) {
    int numbering = 1, counter_n = 1;
    char current_char, next_char, post_next_char;
    while(*number_of_element_of_argv < argc) {
    FILE *opened_file;
    opened_file = open_file(argv[*number_of_element_of_argv]);
    if(opened_file != NULL) {
        if ((next_char = fgetc(opened_file)) != EOF) {
        int number_of_string_in_opened_file = 1;
        while((current_char = next_char)!= EOF) {
            next_char = fgetc(opened_file);
            if (*number_of_element_of_argv == 1){
            printf("%c", current_char);
            } else {
                if(flags -> e != 0) { flags -> E = flags -> v = *count_of_flags = 2; }
                if(flags -> t != 0) { flags -> T = flags -> v = *count_of_flags = 2; }
                if(flags -> n != 0) { print_flag_n(current_char, next_char, number_of_string_in_opened_file, &numbering); }
                if(flags -> E != 0) { print_flag_E(current_char, next_char, number_of_string_in_opened_file); }
                if(flags -> b != 0) { print_flag_b(current_char, next_char, number_of_string_in_opened_file, &numbering); }
                if(flags -> s != 0) { print_flag_s(current_char, next_char, &counter_n, *count_of_flags); }
                if(flags -> T != 0) { print_flag_T(current_char, *count_of_flags); }
                if(flags -> v != 0) { print_flag_v(current_char, *count_of_flags); }
                number_of_string_in_opened_file++;
                }
        }
        fclose(opened_file);
        *number_of_element_of_argv = *number_of_element_of_argv + 1;
        } 
    }
    }
}

void print_flag_n(char current, char next, int number_of_string_in_opened_file, int *numbering) {
    if(number_of_string_in_opened_file == 1){
        printf("%6d\t", *numbering);
        *numbering = *numbering + 1;
    } if (current != '\n'){
        printf("%c", current);
        } else { 
            if (next != EOF) {
                printf("%c%6d\t", current, *numbering);
                *numbering = *numbering + 1;
                } else { printf("%c", current); } 
        }
        }

void print_flag_E(char current, char next, int number_of_string_in_opened_file) {
    if(current == '\n' && number_of_string_in_opened_file == 1) { printf("$%c", current); }
        else if(next == '\n') { printf("%c$", current); }
        else { printf("%c", current); }
}

void print_flag_b(char current, char next, int number_of_string_in_opened_file, int *numbering) {
    if(current == '\n' && number_of_string_in_opened_file == 1 && next != '\n'){
            printf("%c%6d\t", current, *numbering);
            *numbering = *numbering + 1;
            } else if(current != '\n' && number_of_string_in_opened_file == 1) {
                printf("%6d\t%c", *numbering, current);
                *numbering = *numbering + 1;
                } else if(current == '\n' && next == '\n') { printf("%c", current); 
                } else if(current == '\n' && next != '\n' && next != EOF) {
                    printf("%c%6d\t", current, *numbering);
                    *numbering = *numbering + 1;
                    } else { printf("%c", current); }
}

void print_flag_s(char current, char next, int *counter_n, int count_of_flags) {
    if (*counter_n < 3 && count_of_flags == 1) { printf("%c", current); }
    else;
    if(current == '\n' && next == '\n') {*counter_n = *counter_n + 1; }
    if(next != '\n') { *counter_n = 1; }
}

void print_flag_T(char current, int no_another_flag) {
    current == 9 ? printf("^I") : (current <= 31 && current >= 0 && current != 9 && current != 10 || current == 127) ? : printf("%c", current);
}

void print_flag_v(char current, int no_another_flag) {
    if(current <= 31 && current >= 0 && current != 9 && current != 10) {
        printf("%c%c", '^', (current += 64));
    } else if(current == 127) { printf("%c%c", '^', (current - 64)); }
    else if (no_another_flag == 1) printf("%c", current);
}

// ф-ции для Grep

void print_opened_file_without_the_flag(FILE *opened_file) {
    char c;

    while((c = fgetc(opened_file)) != EOF){ printf("%c", c); }
}

void check_options_grep(int argc, char **argv, struct count_grep *flags) {
    char c, string_flags[12] = "e:f:ivclnhso";

    while((c = getopt_long(argc, argv, string_flags, NULL, NULL)) != -1) {
        switch (c){
            case 'e':
                flags -> e = 'e';
                break;
            case 'i':
                flags -> i = 'i';
                printf("%c\n", flags -> i);
                break;
            case 'v':
                flags -> v = 'v';
                break;
            case 'c':
                flags -> c = 'c';
                break;
            case 'l':
                flags -> l = 'l';
                break;
            case 'n':
                flags -> n = 'n';
                break;
            case 'h':
                flags -> h = 'h';
                break;
            case 's':
                flags -> s = 's';
                break;
            case 'f':
                flags -> f = 'f';
                break;
            case 'o':
                flags -> o = 'o';
                break;
        }
    }
}
