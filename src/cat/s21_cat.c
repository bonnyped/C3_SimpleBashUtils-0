#include <stdio.h>
#include <stdlib.h>

void memory_allocation(char *pointer, int *capacity);

int main(int argc, char *argv[]) {
    char ch, *file_output_data;
    int capacity = 1000, count = 1;
    file_output_data = malloc (capacity * sizeof(char));
    if(!file_output_data){
        printf("Невозможно выделить память\n");
        exit(1);
    }
    // printf("%s\n", argv[1]);
    FILE *f;
    if ((f = fopen(argv[1], "r")) == NULL){
        printf("Невозможно открыть файл\n");
        exit(1);
    } else {
    while((ch=fgetc(f)) != EOF) {
    if (count > (capacity / 2)) { memory_allocation(file_output_data, &capacity); }
    file_output_data[count - 1] = ch;
    count++;
    // printf(" ok\n");
    }
    }
    fclose(f);

    for(int i = 0; i < count; i++) {
        printf("%c", file_output_data[i]);
    }

free(file_output_data);
return 0;
}

void memory_allocation(char *pointer, int *capacity) {
    *capacity = *capacity * 2;
    pointer = realloc(pointer, *capacity);
    if(!pointer){
        printf("Невозможно выделить память\n");
        exit(1);
    }
}