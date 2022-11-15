#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct count {int b, e, n, s, t, v, E, T;} ;
void check_options(int argc, char **argv);
void usage(int argc, char *name_of_program);
void print_flag_n(char current, char next, int *numbering, int number_of_string_in_opened_file);
void print_flag_E(char current, char next, int number_of_string_in_opened_file);
void print_flag_b(char current, char next, int number_of_string_in_opened_file, int *numbering);
void print_flag_s(char current, char next, int *counter_n);
void print_flag_T(char current);
void print_flag_v(char current, int no_another_flag);

int main(int argc, char **argv) {
    usage(argc, argv[0]);
    check_options(argc, argv);
    return 0;
}

void usage(int argc, char *name_of_program){
    if(argc == 1){ 
        printf("Используй флаги и аргументы утилиты\n" );
        exit(1);
        } 
}

void check_options(int argc, char **argv) {
    struct count flags = {0};
    char c, current_char, next_char, post_next_char;
    int number_of_element_of_file = 1, numbering = 1, counter_n = 1, count_of_flags = 0;
    static struct option long_opts[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0}
    };

    while(c != -1){     
        if((c = getopt_long(argc, argv, "+benstvET", long_opts, NULL)) != -1) {           
        count_of_flags++;
        switch(c) {
            case 'b': 
                flags.b = 'b';
                number_of_element_of_file = 2; 
                break;
            case 'e': 
                flags.e = 'e';
                number_of_element_of_file = 2; 
                break;
            case 'E': 
                flags.E = 'E';
                number_of_element_of_file = 2; 
                break;
            case 'n': 
                flags.n = 'n';
                number_of_element_of_file = 2; 
                break;
            case 's': 
                flags.s = 's';
                number_of_element_of_file = 2; 
                break;
            case 't': 
                flags.t = 't';
                number_of_element_of_file = 2; 
                break;
            case 'T': 
                flags.T = 'T';
                number_of_element_of_file = 2; 
                break;
            case 'v': 
                flags.v = 'v';
                number_of_element_of_file = 2; 
                break;
            }    
        } 
    }
    
    while(number_of_element_of_file < argc) {
    FILE *file_to_open;
    if((file_to_open = fopen(argv[number_of_element_of_file], "r")) == NULL) { printf("Нет такого файла или каталога\n"); 
    } else {
        if ((next_char = fgetc(file_to_open)) != EOF) {
        int number_of_string_in_opened_file = 1;
        while((current_char = next_char)!= EOF) {
            next_char = fgetc(file_to_open);
            if (number_of_element_of_file == 1){
            printf("%c", current_char);
            } else {
                if(flags.e != 0) { flags.E = flags.v = count_of_flags = 2; }
                if(flags.t != 0) { flags.T = flags.v = count_of_flags = 2; }
                if(flags.n != 0) { print_flag_n(current_char, next_char, &numbering, number_of_string_in_opened_file); }
                if(flags.E != 0) { print_flag_E(current_char, next_char, number_of_string_in_opened_file); }
                if(flags.b != 0) { print_flag_b(current_char, next_char, number_of_string_in_opened_file, &numbering); }
                if(flags.s != 0) { print_flag_s(current_char, next_char, &counter_n); }
                if(flags.T != 0) { print_flag_T(current_char); }
                if(flags.v != 0) { print_flag_v(current_char, count_of_flags); }
                }
                if (current_char == '\n') { number_of_string_in_opened_file++; }
        }
        fclose(file_to_open);
        number_of_element_of_file++;
        } 
    }
    }
}

void print_flag_n(char current, char next, int *numbering, int number_of_string_in_opened_file) {
    if(number_of_string_in_opened_file == 1){
        printf("%6d  ", *numbering);
        *numbering = *numbering + 1;
    }
    if (current == '\n'){
        if (next != EOF) {
        printf("%c%6d  ", current, *numbering);
        *numbering = *numbering + 1;
        } else { printf("%c", current); } 
    } else { printf("%c", current); }
}

void print_flag_E(char current, char next, int number_of_string_in_opened_file) {
    if(current == '\n' && number_of_string_in_opened_file == 1) { printf("$%c", current); }
        if(next == '\n') { printf("%c$", current); }
        else { printf("%c", current); }
}

void print_flag_b(char current, char next, int number_of_string_in_opened_file, int *numbering) {
    if(current == '\n' && number_of_string_in_opened_file == 1 && next != '\n'){
            printf("%c%6d  ", current, *numbering);
            *numbering = *numbering + 1;
            } else if(current != '\n' && number_of_string_in_opened_file == 1) {
                printf("%6d  %c", *numbering, current);
                *numbering = *numbering + 1;
                } else if(current == '\n' && next == '\n') { printf("%c", current); 
                } else if(current == '\n' && next != '\n' && next != EOF) {
                    printf("%c%6d  ", current, *numbering);
                    *numbering = *numbering + 1;
                    } else { printf("%c", current); }
}

void print_flag_s(char current, char next, int *counter_n) {
    if (*counter_n < 3) { printf("%c", current); }
    else;
    if(current == '\n' && next == '\n') {*counter_n = *counter_n + 1; }
    if(next != '\n') { *counter_n = 1; }
}

void print_flag_T(char current) {
    if(current == 9) { printf("^I"); }
    else printf("%c", current);
}

void print_flag_v(char current, int no_another_flag) {
    if(current <= 31 && current >= 0 && current != 9 && current != 10) {
        printf("%c%c", '^', (current += 64));
    } else if(current == 127) { printf("%c%c", '^', (current - 64)); }
    else if (no_another_flag == 1) printf("%c", current);
}
