#include <stdlib.h>
#include <stdio.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"
#include "memory.h"

static void resetStack(VM *vm) {
  vm->stackCount = 0;
}

void initVM(VM *vm) {
  vm->stack = NULL;
  vm->stackCapacity = 0;
  resetStack(vm);
}

void freeVM(VM *vm) {
  
}

void push(VM *vm, Value value) {
  if (vm->stackCapacity < vm->stackCount + 1) {
    int oldCapacity = vm->stackCapacity;
    vm->stackCapacity = GROW_CAPACITY(oldCapacity);
    vm->stack = GROW_ARRAY(Value, vm->stack, oldCapacity, vm->stackCapacity);
  }

  vm->stack[vm->stackCount] = value;
  vm->stackCount++;
}

Value pop(VM *vm) {
  vm->stackCount--;
  return vm->stack[vm->stackCount];
}


static InterpretResult run(VM *vm) {
#define READ_BYTE() (*vm->ip++)
#define READ_CONSTANT() (vm->chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                           \
  do {                                          \
    double b = pop(vm);                           \
    double a = pop(vm);                           \
    push(vm ,a op b);                             \
  } while (false)
#ifdef DEBUG_TRACE_EXECUTION
  printf("          ");
  for (Value *slot = vm->stack; slot < vm->stackCapacity; slot++) {
    printf("[ ");
    printValue(*slot);
    printf(" ]");
  }
  printf("\n");
  disassembleInstruction(vm->chunk, (int)(*vm->ip - *vm->chunk->code));
#endif

  for(;;) {
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      Value constant = READ_CONSTANT();
      push(vm, constant);
      break;
    }
    case OP_CONSTANT_LONG: {
      Value constants[3] = { READ_CONSTANT(), READ_CONSTANT(), READ_CONSTANT() };
      push(vm, constants[0] + constants[1] + constants[2]);
    }
    case OP_ADD: {
      BINARY_OP(+);
      break;
    }
    case OP_SUBTRACT: {
      BINARY_OP(-);
      break;
    }
    case OP_MULTIPLY: {
      BINARY_OP(*);
      break;
    };
    case OP_DIVIDE: {
      BINARY_OP(/);
      break;
    }
    case OP_NEGATE: {
      push(vm, -pop(vm));
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
#undef BINARY_OP
}

InterpretResult interpret(VM *vm, Chunk *chunk ) {
  vm->chunk = chunk;
  vm->ip = vm->chunk->code;
  return run(vm);
}
