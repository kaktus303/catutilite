#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Упорядочить числа при выводе с флагом
// Добавть флаг -v -vT
int main(int argc, char *argv[])
{
    FILE *file;
    char symbole, last_symbole = 'a';
    int number = 1, v_flag = 0, n_flag = 0, e_flag = 0, b_flag = 0, s_flag = 0, t_flag = 0, execute_flag = 1, empty_string = 0, first_file = 1;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < strlen(argv[i]); ++j)
                if ((argv[i][j] == 'b' && argv[i][1] != '-') || strcmp(argv[i], "--number-nonblank") == 0)
                    b_flag = 1;
                else if ((argv[i][j] == 'e' || argv[i][j] == 'E') && argv[i][1] != '-')
                {
                    e_flag = 1;
                    if (argv[i][j] == 'e')
                        v_flag = 1;
                }
                else if ((argv[i][j] == 'n' && argv[i][1] != '-') || strcmp(argv[i], "--number") == 0)
                    n_flag = 1;
                else if ((argv[i][j] == 's' && argv[i][1] != '-') || strcmp(argv[i], "--squeeze-blank") == 0)
                    s_flag = 1;
                else if ((argv[i][j] == 't' || argv[i][j] == 'T') && argv[i][1] != '-')
                {
                    t_flag = 1;
                    if (argv[i][j] == 't')
                        v_flag = 1;
                }
                else if ((argv[i][j] == 'v' || argv[i][j] == 'V') && argv[i][1] != '-')
                    v_flag = 1;
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
                        printf("%6d\t", number);
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
                        printf("%6d\t", number);
                        number++;
                    }
                    if (last_symbole == '\n' && n_flag)
                    {
                        printf("%6d\t", number);
                        number++;
                    }
                    if (symbole == '\n' && e_flag)
                    {
                        printf("$");
                    }
                    if (t_flag && symbole == '\t')
                        printf("^I");
                    else if (v_flag == 1 && symbole >= 0 && symbole <= 31 && symbole != '\n' &&
                             symbole != '\t')
                    {
                        printf("^%c", symbole+64);
                    }
                    else printf("%c", symbole);
                    last_symbole = symbole;
                }
                fclose(file);
            }
            else
                {
                printf("cat: %s: No such file or directory\n", argv[i]);
                fclose(file);
                }
        }
    }
}
