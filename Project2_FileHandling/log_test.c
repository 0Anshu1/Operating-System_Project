#include "user.h"

int main() {
  char buffer[1024];

  // Perform some file operations
  int fd = open("logfile.txt", O_CREATE | O_WRONLY);
  if (fd < 0) {
    printf("Failed to create logfile.txt\n");
    exit();
  }
  write(fd, "Logging test", 12);
  close(fd);

  // Fetch logs
  int logsize = getlogs(buffer, sizeof(buffer));
  if (logsize < 0) {
    printf("Failed to retrieve logs\n");
  } else {
    printf("Logs:\n");
    printf("%s\n", buffer);
  }

  exit();
}

