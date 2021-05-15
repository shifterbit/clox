#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

static void resetStack(VM vm) {
  vm.stackTop = vm.stack;
}

void initVM(VM vm) {
  resetStack(vm);
}

void freeVM(VM vm) {
}

void push(VM vm, Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop(VM vm) {
  vm.stackTop--;
  return *vm.stackTop;
}


static InterpretResult run(VM vm) {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#ifdef DEBUG_TRACE_EXECUTION
  printf("          ");
  for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
    printf("[ ");
    printValue(*slot);
    printf(" ]");
  }
  printf("\n");
  disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));

#endif

  for(;;) {
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT_LONG:
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(vm, constant);
      break;
    }
    case OP_RETURN:
      printValue(pop(vm));
      printf("\n");
      return INTERPRET_OK;
    }
  }
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(VM vm, Chunk *chunk ) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run(vm);
}
