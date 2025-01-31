#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void arguments_sort(int *flags, int *files, int argc, char *argv[], int *capacity_flags, int *capacity_files)
{
}
void append(int *flags, int *flags_capasity, int *flags_number, int i, char *argv[])
{
    int trash = 1;
    for (int j = 0; j < *flags_number && trash == 1; ++j)
    {
        if (strcmp(argv[i], argv[flags[j]]) == 0)
            trash = 0;
    }
    if (trash == 1)
    {
        flags[*flags_number] = i;
        *flags_number++;
        if (*flags_number == *flags_capasity)
        {
            *flags_capasity *= 2;
            flags = realloc(flags, *flags_capasity);
        }
    }
}
int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    char symbole, last_symbole = 'a';
    int number = 2, n_flag = 0, e_flag = 0, b_flag = 0, s_flag = 0, t_flag = 0, flags_capasity = 2, flags_number = 0, execute_flag = 1, symbole_in_string = 0, first_file = 1;
    int *flags = malloc(sizeof(int) * flags_capasity);
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            if (strcmp(argv[i], "-b") == 0 && b_flag == 0)
                b_flag = 1;
            else if (strcmp(argv[i], "-e") == 0 && e_flag == 0)
                e_flag = 1;
            else if (strcmp(argv[i], "-n") == 0 && n_flag == 0)
                n_flag = 1;
            else if (strcmp(argv[i], "-s") == 0 && s_flag == 0)
                s_flag = 1;
            else if (strcmp(argv[i], "-t") == 0 && t_flag == 0)
                t_flag = 1;
            else
            {
                printf("cat: invalid option -- '%c'\nTry 'cat --help' for more information.\n", argv[i][1]);
                execute_flag = 0;
            }
        }
    }
    if (b_flag == 1 && n_flag == 1)
        n_flag = 0;
    for (int i = 1; i < argc && execute_flag == 1; ++i)
    {
        if (argv[i][0] != '-')
        {
            file = fopen(argv[i], "r");
            if (file)
            {
                if ((n_flag || b_flag) && first_file){
                    printf("    1  ");
                    first_file = 0;
                }
                while (fscanf(file, "%c", &symbole) == 1 && execute_flag == 1)
                {

                    if (symbole != '\n' && last_symbole == '\n' && b_flag)
                    {
                        printf("    %d  ", number);
                        number++;
                    }
                    if (symbole == '\n' && e_flag)
                    {
                        printf("$");
                    }
                    if (t_flag && symbole == '\t')
                        printf("^I");
                    else
                        printf("%c", symbole);

                    if (symbole == '\n' && n_flag)
                    {
                        printf("    %d  ", number);
                        number++;
                    }

                    last_symbole = symbole;
                }
            }
            else
                printf("cat: %s: No such file or directory\n", argv[i]);
        }
    }
    // printf("%s\n", argv[0]);

    // if (file)
    // {
    //       printf("1");
    //     // printf("YES");
    //     while (fscanf(file, "%c", &symbole) == 1 && execute_flag == 1)
    //     {

    //         printf("%c", symbole);
    //         if (symbole == '\n')
    //         {
    //             printf("    %d ", number);
    //             number++;
    //         }
    //     }
    // }
    // else
    // {
    //     printf("cat: %s: No such file or directory\n", argv[argc - 1]);
    // }
    
}
