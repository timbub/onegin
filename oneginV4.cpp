#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <TXLib.h>
const size_t SKIP_r_n = 2;

FILE* open_file();
size_t size(FILE* input_file);
void input_buf(char* buffer, size_t size_file, FILE* input_file);
void input_indicator(char* buffer, struct start_end_str* indicator, size_t size_file, size_t num_string);
void output(struct start_end_str* indicator, size_t num_string);
int cmpstrings(const void* a, const void* b);
size_t proccess_buffer(char* buffer, size_t size_file);
void end_programm(char* buffer, struct start_end_str* indicator, FILE* input_file);

struct start_end_str
{
    char* start;
    size_t len;
}; 
// TODO: структура для онегина char* buffer, char** lines, 

// OneginStruct onegin_struct = {};
// onegin_construct ();
// sort ();
// onegin_destructor (); 
int main()
{
    
    FILE * input_file = open_file();

    size_t size_file = size(input_file); // размер файла
    printf("size file %d\n", size_file);

    char* buffer = (char*) calloc(size_file, sizeof(char)); //буфер со строками
    input_buf(buffer, size_file, input_file);

    size_t num_string = proccess_buffer(buffer, size_file); //кол-во строк
    printf("number strings %d\n", num_string);

    struct start_end_str* indicator = (struct start_end_str*) calloc(num_string, sizeof(struct start_end_str)); // массив указателей

    input_indicator(buffer, indicator, size_file, num_string); //запись указателей

    printf("\\---the original text---\\ \n");
    output(indicator, num_string);

    qsort(indicator, num_string, sizeof(struct start_end_str), cmpstrings);

    printf("\\---the final text---\\ \n");
    output(indicator, num_string);

    end_programm(buffer, indicator, input_file);
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

void output(struct start_end_str* indicator, size_t num_string)
{
        for(size_t i = 0; i < num_string; i++)
        {
            printf("%s\n", indicator[i].start);
        }
        printf("\n");
}

size_t proccess_buffer(char* buffer, size_t size_file) // TODO: название process_buffer
{
    int num_string = 0;
    for (size_t i = 0; i < size_file; i++)
    {
        if (buffer[i] == '\n')
        {
            num_string++;
            buffer[i] = '\0';
        } else if (buffer[i] == '\r')
        {
            buffer[i] = '\0';
        }
        
    }
    return num_string;
}

void input_indicator(char* buffer, struct start_end_str* indicator, size_t size_file, size_t num_string)
{
    indicator[0] = {&buffer[0], strlen(&buffer[0])};
    size_t num_ind = 1;
    for (size_t i = 1; i < size_file;i++)
    {
        if (buffer[i] == '\0')
        {
            indicator[num_ind] = {&buffer[i + 2], strlen(&buffer[i + 2])};
            num_ind++;
            i += SKIP_r_n;
        }
        if (num_ind == num_string)
        {
            break;
        } 
    }
    if (num_ind != num_string)
    {
        printf("number input indicator = %d does not match with number strings\n", num_ind);
    }
}

int cmpstrings(const void* a, const void* b)
{
    const char* arg1_start = (*(const struct start_end_str*)a).start;
    const size_t arg1_len = (*(const struct start_end_str*)a).len;
    const char* arg2_start = (*(const struct start_end_str*)b).start;
    const size_t arg2_len = (*(const struct start_end_str*)b).len;
    for (int i = 0; i < min(arg1_len, arg2_len); i++)
    {
        if (arg1_start[arg1_len - 1 - i] > arg2_start[arg2_len - 1 - i])
        {
            return 1;
        } else if (arg1_start[arg1_len - 1 - i] < arg2_start[arg2_len - 1 - i]) 
        {
            return -1;
        }
    }
    return 1;
}

void end_programm(char* buffer, struct start_end_str* indicator, FILE* input_file)
{
    free(buffer);
    free(indicator);
    fclose(input_file);
}

FILE* open_file()
{
    FILE* input_file = NULL;
    input_file = fopen("onegin.txt","rb");
    if (input_file == NULL)
    {
        printf ("file is not open\n");
    }
    return input_file;
}