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
  int constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  freeVM(&vm);

  return 0;
}
