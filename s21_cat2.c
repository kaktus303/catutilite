#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool numberNoEmpty;
  bool markEnd;
  bool numberAll;
  bool squeeze;
  bool tab;
  bool v;

} Flags;

int analizFile(Flags flags, char *nameFile, int *index);
int readFlags(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  readFlags(argc, argv);
  return 0;
}

int readFlags(int argc, char *argv[]) {
  char *fileName;
  int returning = 0;
  Flags flags = {false, false, false, false, false, false};
  // printf("Number of arguments: %d\n", argc);
  for (int i = 1; i < argc; i++) {
    // printf("Argument %d: %s\n", i, argv[i]);
    if (argv[i][0] != '-' || strcmp(argv[i], "-") == 0 ||
        strcmp(argv[i], "--") == 0) {
      continue;
    } else {
      // printf("|||| = %c \n", argv[i][0]);

      if (argv[i][0] == '-' && argv[i][1] != '-') {
        for (size_t j = 1; j < strlen(argv[i]); j++) {
          if (argv[i][j] == 'b') {
            flags.numberNoEmpty = true;
            // printf("flag(b)");
          } else if (argv[i][j] == 'e') {
            flags.markEnd = true;
            flags.v = true;
            // printf("flag(e)");
          } else if (argv[i][j] == 'E') {
            flags.markEnd = true;
            // printf("flag(E)");
          } else if (argv[i][j] == 'n') {
            flags.numberAll = true;
            // printf("flag(n)");
          } else if (argv[i][j] == 's') {
            flags.squeeze = true;
            // printf("flag(s)");
          } else if (argv[i][j] == 't') {
            flags.tab = true;
            flags.v = true;
            // printf("flag(t)");
          } else if (argv[i][j] == 'T') {
            flags.tab = true;
            // printf("flag(T)");
          } else if (argv[i][j] == 'v') {
            flags.v = true;
            // printf("flag(v)");
          }
        }
      } else if (argv[i][0] == '-' && argv[i][1] == '-') {
        if (strcmp(argv[i], "--number") == 0) {
          // printf("flag(n)");
          flags.numberAll = true;
        } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
          flags.squeeze = true;
          // printf("flag(s)");
        } else if (strcmp(argv[i], "--number-nonblank") == 0) {
          flags.numberNoEmpty = true;
          // printf("flag(b)");
        }
      }
    }
  }

  int index = 0;
  if (flags.numberNoEmpty == true && flags.numberAll == true)
    flags.numberAll = false;
  for (int i = 1; i < argc; i++) {
    // printf("file = %c\n", argv[i][0]);
    //   printf("Argument %d: %s\n", i, argv[i]);
    if (argv[i][0] != '-' || strcmp(argv[i], "-") == 0 ||
        strcmp(argv[i], "--") == 0) {
      fileName = argv[i];
      // printf("name file = %s \n", fileName);
      if (analizFile(flags, fileName, &index) == 1) {
        returning = 1;
        break;
      }
    }
  }
  // if(flags.v==true)printf("GOIDA\n");
  return returning;
}
int analizFile(Flags flags, char *nameFile, int *index) {
  FILE *fp;
  int ch, pred = '\n', returning = 0;
  bool predLine = 0;
  fp = fopen(nameFile, "r");
  if (fp == NULL) {
    printf("Error open to file\n");
    returning = 1;
  } else {
    while ((ch = getc(fp)) != EOF) {
      // printf("(|%d|)", ch);
      if (!(flags.squeeze == true && pred == '\n' && ch == '\n' && predLine)) {
        if (pred == '\n' && ch == '\n')
          predLine = 1;
        else
          predLine = 0;

        if ((flags.numberAll == true ||
             (flags.numberNoEmpty == true && ch != '\n')) &&
            pred == '\n') {
          *index += 1;
          printf("%6d\t", *index);
        }
        if (flags.markEnd == true && ch == '\n') {
          if (pred == '\n' &&
              (flags.numberAll == true || flags.numberNoEmpty == true))
            printf("$");
          else
            printf("$");
        }
        if (flags.tab == true && ch == '\t')
          printf("^I");
        else {
          if (flags.v == true && ch >= 0 && ch <= 31 && ch != '\n' &&
              ch != '\t') {
            printf("^%c", ch + 64);
          } else
            printf("%c", ch);
        }
      }
      pred = ch;
    }
  }
  fclose(fp);
  return returning;
}