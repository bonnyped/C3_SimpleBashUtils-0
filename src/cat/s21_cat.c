#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct count {int b, e, n, s, t, E, T;} ;

void check_options(int argc, char **argv);
void usage(int argc, char *name_of_program);
void print_flag_n(char current, char next, int *numbering);

// void print(struct count);

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
    char c, current_char, next_char;
    int number_of_element_of_file = 1, numbering = 1;
    static struct option long_opts[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0}
    };

    while(c != -1){     
        if((c = getopt_long(argc, argv, "+benstET", long_opts, NULL)) != -1) {           
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
            }    
        } 
    }
    
    while(number_of_element_of_file < argc) {
    FILE *file_to_open;
    if((file_to_open = fopen(argv[number_of_element_of_file], "r")) == NULL) {
        printf("Нет такого файла или каталога\n");
    } else {
        if ((next_char = fgetc(file_to_open)) != EOF) {
        int number_of_string_in_opened_file = 1;
        while((current_char = next_char)!= EOF) {
            // printf("1%c1\n", current_char); 
            next_char = fgetc(file_to_open);
            if (number_of_element_of_file == 1){
            printf("%c", current_char);
            current_char = next_char;
            } else {
                if(flags.n == 'n') {
                    if(number_of_string_in_opened_file == 1){
                        printf("%6d  ", numbering);
                        numbering++;
                        number_of_string_in_opened_file++;
                    }
                    print_flag_n(current_char, next_char, &numbering); 
                    current_char = next_char;
            }
        }
        }
        }
        fclose(file_to_open);
    number_of_element_of_file++;
    } 
}
}

void print_flag_n(char current, char next, int *numbering) {
    if (current == '\n'){
        if (next != EOF) {
        printf("%c%6d  ", current, *numbering);
        *numbering = *numbering + 1;
        } else {
            printf("%c", current);
        }
        } else {
            printf("%c", current);
            }
}



// void print_flag_b(struct count) {
//     printf(" %d  %d  %d  %d  %d  %d  %d ", flags.b, flags.e, flags.n, flags.s, flags.t, flags.E, flags.T);
// }