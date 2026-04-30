#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

#define DIRSIZ 14

void find(char* path, char* filename);
void itr(char* path, char* filename);

int main(int argc, char* argv[]) {
  int i;

  if (argc < 2) {
    printf("usage: find <path> <filename>\n");
    exit(1);
  }

  find(argv[1], argv[2]);
}

void find(char* path, char* filename) {
  // in curr path, iterate all files, print, advance path ptr
  // find ./xv6 ls.c
  int fd;
  char buf[512], *p;
  struct dirent de;

  // NOTE: if we reached rock-bottom, search and print.
  if ((strcmp(path, ".") == 0) || (strcmp(path, "..") == 0)) {
    itr(path, filename);
    return;
  }

  if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
    printf("find: path too long\n");
    exit(1);
  }

  strcpy(buf, path);
  p = buf + strlen(buf);

  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0) {
      continue;
    }
    memmove(p, de.name, DIRSIZ);
    p[DIRSIZ] = 0;
  }

  close(fd);
}

void itr(char* path, char* filename) {}