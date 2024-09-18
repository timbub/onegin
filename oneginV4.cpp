#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <TXLib.h>
const int N = 14;
const int M = 50;

size_t size(FILE* input_file);
void input_buf(char* buffer, size_t size_file, FILE* input_file);
size_t input_indicator(char* buffer, char** indicator, size_t size_file, size_t num_string);
void output(char** input_indicator, size_t num_string);
int cmpstrings(const void* a, const void* b);
size_t change_rn(char* buffer, size_t size_file);

int main()
{
    FILE* input_file = NULL;
    input_file = fopen("onegin.txt","rb");
    if (input_file == NULL)
    {
        printf ("file is not open\n");
    }

    size_t size_file = size(input_file); // размер файла
    printf("size file %d\n", size_file);

    char* buffer = (char*) calloc(size_file, sizeof(char)); //буфер со строками
    input_buf(buffer, size_file, input_file);

    size_t num_string = change_rn (buffer, size_file); //кол-во строк
    printf("number strings %d\n", num_string);

    char** indicator = (char**) calloc(num_string, sizeof(char*)); // массив указателей

    size_t num_indicator = input_indicator(buffer, indicator, size_file, num_string); //кол-во записанных указателей
    printf("number input indicator %d\n", num_indicator);

    printf("the original text\n");
    output(indicator, num_string);

    qsort(indicator, num_indicator, sizeof(char**), cmpstrings);

    printf("the final text\n");
    output(indicator, num_string);

    free(buffer);
    free(indicator);
    fclose(input_file);
    return 0;
}

size_t size(FILE* input_file)
{
    fseek(input_file, 0L, SEEK_END);
    size_t size_file = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);
    return size_file;
}

void input_buf(char* buffer, size_t size_file, FILE* input_file)
{
    size_t k = fread(buffer, sizeof(char), (size_file)/sizeof(char), input_file);
    if (k != size_file)
    {
        printf("Wrong input to buffer %d\n", k);
    }

}

void output(char** indicator, size_t num_string)
{
        for(size_t i = 0; i < num_string; i++)
            printf("%s\n", indicator[i]);
}

size_t change_rn(char* buffer, size_t size_file)
{
    int num_string = 0;
    for (size_t i = 0; i < size_file; i++)
    {
        if (buffer[i] == '\n' || buffer[i] == '\r')
        {
            num_string++;
            buffer[i] = '\0';
        }
    }
    return num_string/2;
}

size_t input_indicator(char* buffer, char** indicator, size_t size_file, size_t num_string)
{
    indicator[0] = &buffer[0];
    size_t num_ind = 1;
    for (size_t i = 1; i < size_file;i++)
    {
        if (buffer[i] == '\0')
        {
            indicator[num_ind] = &buffer[i+2];
            num_ind++;
            i +=2;
        }
        if (num_ind == num_string)
        {
        break;
        }
    }
    return num_ind;
}

int cmpstrings(const void* a, const void* b)
{
    const char* arg1 = *(const char**)a;
    const char* arg2 = *(const char**)b;
    return strcmp(arg1, arg2);
}




