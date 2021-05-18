#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  VM vm;
  Chunk chunk;
  initVM(&vm);
  interpret(&vm, &chunk);
  initChunk(&chunk);

  writeConstant(&chunk, 23, 123);
  writeChunk(&chunk, OP_RETURN, 124);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  freeVM(&vm);

  return 0;
}
