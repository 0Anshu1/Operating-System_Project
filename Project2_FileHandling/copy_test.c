#include "user.h"
int main() {
  int fd = open("source.txt", O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf("Failed to create source.txt\n");
    exit();
  }
  write(fd, "Copy this content.", 18);
  close(fd);
  if (copy("source.txt", "destination.txt") < 0) {
    printf("Failed to copy file\n");
  } else {
    printf("File copied successfully from source.txt to destination.txt\n");
  }
  fd = open("destination.txt", O_RDONLY);
  if (fd < 0) {
    printf("Copied file does not exist\n");
  } else {
    printf("Copied file exists and can be opened\n");
    close(fd);
  }

  exit();
}

