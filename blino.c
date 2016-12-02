#include <stdio.h>
#include <string.h>
#include <err.h>
#include "blino.h"

static void slurp(char *file, char **dest, size_t *size) {
  FILE *f = fopen(file, "r");
  if (!f) errx(1, "can't open %s for reading", file);

  char buf[BUFSIZ];
  ssize_t read;
  FILE *tmp = open_memstream(dest, size);
  while ((read = fread(buf, 1, BUFSIZ, f)))
    fwrite(buf, 1, read, tmp);

  fclose(tmp);
  fclose(f);
}

int main(int argc, char *argv[]) {
  char *code;
  size_t size;
  struct vm vm = { 0 };

  if (!strcmp(argv[1], "r") && argc == 3) { // run a compiled executable
    slurp(argv[2], &code, &size);
    memcpy(&vm, code, size); // compiled files are just a dumped vm
    run(&vm);
  }
  else if (!strcmp(argv[1], "j") && argc == 3) { // jit
    slurp(argv[2], &code, &size);
    compile(&vm, code, size);
    run(&vm);
  }
  else if (!strcmp(argv[1], "c") && argc == 4) { // compile
    FILE *f = fopen(argv[3], "w");
    if (!f) errx(1, "can't open %s for writing", argv[3]);
    slurp(argv[2], &code, &size);
    compile(&vm, code, size);
    fwrite(&vm, 1, sizeof(struct vm), f);
    fclose(f);
  }
  else errx(1, "args");

  return 0;
}
