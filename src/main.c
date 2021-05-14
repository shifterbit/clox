#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;
  initVM();
  interpret(&chunk);
  initChunk(&chunk);
  int constant = addConstant(&chunk, 257);
  writeChunk(&chunk, OP_CONSTANT_LONG, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  freeVM();

  return 0;
}
