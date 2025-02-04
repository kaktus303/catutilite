#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Упорядочить числа при выводе с флагом
// Добавть флаг -v -vT
int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    char symbole, last_symbole = 'a';
    int number = 1, n_flag = 0, e_flag = 0, b_flag = 0, s_flag = 0, t_flag = 0, execute_flag = 1, empty_string = 0, first_file = 1;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
                if (argv[i][j] == 'b')
                    b_flag = 1;
                else if (argv[i][j] == 'e')
                    e_flag = 1;
                else if (argv[i][j] == 'n')
                    n_flag = 1;
                else if (argv[i][j] == 's')
                    s_flag = 1;
                else if (argv[i][j] == 't')
                    t_flag = 1;
                else
                {
                    printf("cat: invalid option -- '%c'\nTry 'cat --help' for more information.\n", argv[i][j]);
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
                while (fscanf(file, "%c", &symbole) == 1 && execute_flag == 1)
                {
                    if ((n_flag || b_flag) && first_file && number == 1)
                    {
                        printf("    1  ");
                        number++;
                        first_file = 0;
                    }
                    if (empty_string == 1 && symbole == '\n' && s_flag)
                        continue;
                    if (last_symbole == '\n' && symbole == '\n')
                        empty_string = 1;
                    else
                        empty_string = 0;
                    if (symbole != '\n' && last_symbole == '\n' && b_flag)
                    {
                        printf("    %d  ", number);
                        number++;
                    }
                    if (last_symbole == '\n' && n_flag)
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

                    last_symbole = symbole;
                }
            }
            else
                printf("cat: %s: No such file or directory\n", argv[i]);
        }
    }
}
