#include "user.h"
#include "stat.h"

int main() {
  struct stat statbuf;

  // Create a file to test metadata
  int fd = open("metafile.txt", O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf("Failed to create metafile.txt\n");
    exit();
  }
  write(fd, "Metadata testing", 16);
  close(fd);

  // Get file metadata
  if (metadata("metafile.txt", &statbuf) < 0) {
    printf("Failed to retrieve metadata\n");
  } else {
    printf("Metadata for metafile.txt:\n");
    printf("Size: %d bytes\n", statbuf.size);
    printf("Type: %d\n", statbuf.type);
    printf("Device: %d\n", statbuf.dev);
    printf("Inode Number: %d\n", statbuf.ino);
  }

  exit();
}

