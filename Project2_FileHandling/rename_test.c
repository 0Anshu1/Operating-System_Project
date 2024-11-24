#include "user.h"

int main() {

  int fd = open("oldfile.txt", O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf("Failed to create oldfile.txt\n");
    exit();
  }
  write(fd, "This is a test file.", 21);
  close(fd);

  // Renaming
  if (rename("oldfile.txt", "newfile.txt") < 0) {
    printf("Failed to rename file\n");
  } else {
    printf("File renamed successfully from oldfile.txt to newfile.txt\n");
  }

  fd = open("newfile.txt", O_RDONLY);
  if (fd < 0) {
    printf("Renamed file does not exist\n");
  } else {
    printf("Renamed file exists and can be opened\n");
    close(fd);
  }

  exit();
}

