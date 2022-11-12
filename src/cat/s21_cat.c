#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void check_options(int argc, char **argv, int *is_flag);
void usage(int argc, char *name_of_program);
// int open_file(int is_flag, char *argv);

int main(int argc, char **argv) {
    int is_flag = 2;

    usage(argc, argv[0]);
    check_options(argc, argv, &is_flag);
    printf("%d\n", is_flag);
    return 0;
}

void usage(int argc, char *name_of_program){
    if(argc == 1){ 
        printf("Используй флаги и аргументы утилиты\n" );
        exit(1);
        } 
}

void check_options(int argc, char **argv, int *is_flag) {
    char c;
    int flag_of_end = 1;
    static struct option long_opts[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0}
    };

    while(c != -1){     
        if((c = getopt_long(argc, argv, "+benstvET", long_opts, NULL)) != -1) {           
        switch(c) {
            case 'b': 
                printf("Выбран флаг -b\n"); 
                break;
            case 'e': 
                printf("Выбран флаг -e\n"); 
                break;
            case 'E': 
                printf("Выбран флаг -E\n"); 
                break;
            case 'n': 
                printf("Выбран флаг -n\n"); 
                break;
            case 's': 
                printf("Выбран флаг -s\n"); 
                break;
            case 't': 
                printf("Выбран флаг -t\n"); 
                break;
            case 'T': 
                printf("Выбран флаг -T\n"); 
                break;
            case 'v': 
                printf("Выбран флаг -v\n"); 
                break;
            }    
        } else { *is_flag = *is_flag - 1; }
    }
}


// int open_file(int is_flag, char *argv) {
//     int num_of_element;
//     FILE *file_to_open;
//     if((file_to_open = fopen(argv[is_flag], 'r')) == NULL) {
//         printf("Невозможно открыть файл\n");
//     }
// }
    