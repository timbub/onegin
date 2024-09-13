#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
const int N = 14;
const int M = 50;

size_t size(FILE* input_file);
void input_buf(char* buffer, size_t size_file, FILE* input_file);
size_t input_indicator(char* buffer, char** indicator, size_t size_file, size_t num_string);
void sort_bubble(char** input_indicator, size_t N);
void output(char** input_indicator, size_t num_string);
void numeration(int index[N]);
size_t change_rn(char* buffer, size_t size_file);

int main()
{
    char text[N][M] = {};
    int index[N] = {};
    numeration(index);

    FILE* input_file = NULL;
    input_file = fopen("onegin.txt","rb");
    if (input_file == NULL)
    {
        printf ("file is not open\n");
    }

    size_t size_file = size(input_file);
    printf("size file %d\n", size_file);

    char* buffer = (char*) calloc(size_file, sizeof(char));
    input_buf(buffer, size_file, input_file);

    size_t num_string = change_rn (buffer, size_file);
    printf("number strings %d\n", num_string);

    char** indicator = (char**) calloc(num_string, sizeof(char*)); // массив указателей

    size_t num_indicator = input_indicator(buffer, indicator, size_file, num_string);
    printf("number input indicator %d\n", num_indicator); 

    sort_bubble(indicator, num_indicator);
    output(indicator, num_string);
    free(buffer);
    free(indicator);
    fclose(input_file);
    // подчистить память!!!
    return 0;
}

size_t size(FILE* input_file)
{
    fseek(input_file, 0L, SEEK_END);
    size_t size_file = ftell(input_file);
    fseek(input_file, 0L, SEEK_SET);
    return size_file;
}

void sort_bubble(char** indicator, size_t N)
{
    for (int x = 0; x < N;x++)
    {
        for(int i = 0; i < N - 1; i++)
        {
            if (strcmp(indicator[i], indicator[i+1]) > 0)
            {
                printf("CHANGE!!! %d\n", i);
                char* a = indicator[i];
                indicator[i] = indicator[i+1];
                indicator[i+1] = a;
            }
        }
    }
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
        for(int i = 0; i < num_string; i++)
            printf("%s\n", indicator[i]); 
}

void numeration(int index[N])
{
    for (int i = 0; i < N; i++)
    {
        index[i] = i;
    }
}
size_t change_rn(char* buffer, size_t size_file)
{   
    int num_string = 0;
    for (int i = 0; i < size_file; i++)
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
    int num_ind = 1;
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


