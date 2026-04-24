// #include "user/ulib.c"
#include "user/user.h"

int main(int argc, char* argv[]) {
  int i;
  char* count;

  if (argc < 1) {
    pause(0);
    exit(1);
  }

  count = argv[1];
  i = atoi(count);

  pause(i);

  exit(0);
}