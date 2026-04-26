#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("usage: sixfive <file1> <file2>..\n");
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    int fd = open(argv[i], O_RDONLY);
    if (fd < 0) {
      printf("cannot read file: %s", argv[i]);
      exit(1);
    }

    char c;
    int num = 0;

    while (read(fd, &c, 1) == 1) {
      if (c >= '0' && c <= '9') {
        num = num * 10 + (c - '0');
      } else {
        if (num != 0 && (num % 5 == 0 || num % 6 == 0)) {
          printf("%d\n", num);
        }
        num = 0;
      }
    }

    if (num != 0 && (num % 5 == 0 || num % 6 == 0)) {
      printf("%d\n", num);
    }

    close(fd);
  }

  exit(0);
}