#include <ftw.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

char target[100] = { '\0' };
char path_array[100][100] = { '\0' };
int string_storage_index = 0;

void reset_string(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    str[i] = '\0';
  }
}

/* COLORS */
#define COLOR_RESET "\e[0m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GREEN "\e[0;32m"
#define COLOR_CYAN "\e[0;36m"


int callback(const char *path, const struct stat *statptr, int fileflags, struct FTW *pfwt) {
  extern char target[];
  extern int string_storage_index;
  bool slash_found = false;
  char store_potential_match[200] = { '\0' }; 

  for (int i = 0; i < strlen(path); i++) {
    if (path[i] == '/' && slash_found == false && path[i + 1] == target[0]) {
      slash_found = true;
      i++;
    }

    if (slash_found == true) {
      for (int j = 0; path[i] != '/'; j++) {
        store_potential_match[j] = path[i];
        if(store_potential_match[j] == '\0')
          break;

        i++;
      }
    }
        

    if (strcmp(store_potential_match, target) == 0) {
      strcpy(path_array[string_storage_index], path);
      string_storage_index++;
    }

      reset_string(store_potential_match);

      slash_found = false;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);
  int fd_limit = 100;
  int flags = 0;
  extern char target[];
  system("clear");

  if (argc != 2) {
    printf("INVALID ARGUMENTS: Supply one argument, Target folder name\n");
    return 1;
  }

  strcpy(target, argv[1]);
  /* recursive search */
  nftw(cwd, callback, fd_limit, flags);

  if (string_storage_index == 0) {
    printf("Target: %s NOT FOUND\n", target);
    return 1;
  } else {
    printf("Following paths were found with target: " COLOR_CYAN "%s\n", target);
  }

  for (int i = 0; i < string_storage_index; i++) {
    printf(COLOR_GREEN " MATCH: " COLOR_RESET "%s\n\n", path_array[i]);
  }

  printf(COLOR_RESET "Are you sure you want to delete these " COLOR_RED "directories?\n" COLOR_GREEN "y" COLOR_RESET "/" COLOR_RED "n\n" COLOR_RESET);
  
  int c;
  c = getchar();
  if(c == 'y') {
    for (int i = 0; i < string_storage_index; i++) {
      rmdir(path_array[i]);
      printf(COLOR_RED " DELETED: " COLOR_RESET "%s\n\n", path_array[i]);

    }
  }


  return 0;
}