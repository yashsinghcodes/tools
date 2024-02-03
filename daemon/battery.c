#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define EXIT_NO_BAT 1
#define EXIT_PERM 2

int main(int argc, char **argv) {
    FILE *file;
    int capacity = -1;

    file = fopen("/sys/class/power_supply/BAT1/capacity", "r");
    if (file == NULL) {
      fprintf(stderr, "Error opening the file. Check permission");
      exit(EXIT_PERM);
    }
    while (true) {
        if (fscanf(file, "%d", &capacity) == 0) {
            fprintf(stderr, "Error No battery found");
            exit(EXIT_NO_BAT);
        }
        printf("%d\n", capacity);
        sleep(10);
        fflush(file);
        fseek(file, 0, SEEK_SET);
    }
    fclose(file);
  return 1;
}
