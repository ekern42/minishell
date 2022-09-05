#include <stdio.h>


int main(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    printf("argc = %d\n", argc);
    while (i < argc)
    {
        j = 0;
        while (argv[i][j] != '\0')
        {
            //printf("argv[i][j] = %c\n", argv[i][j]);
            j++;
        }
        i++;
    }
    //printf("\n");
}
