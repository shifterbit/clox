#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  VM vm;
  Chunk chunk;
  initVM(&vm);
  initChunk(&chunk);

  writeConstant(&chunk, 23, 123);
  writeChunk(&chunk, OP_NEGATE, 123);
  writeChunk(&chunk, OP_RETURN, 125);
  disassembleChunk(&chunk, "test chunk");
  interpret(&vm, &chunk);
  freeVM(&vm);
  freeChunk(&chunk);

  return 0;
}
