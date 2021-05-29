cmake_minimum_required(VERSION 3.1...3.20)


project(
  clox
  DESCRIPTION "Implementation of clox"
  LANGUAGES C)
 
set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/include/vm
  ${PROJECT_SOURCE_DIR}/include/parser
  )

set(TARGET clox)

set(CLOX_VM_SRC
  "src/vm/chunk.c"
  "src/vm/memory.c"
  "src/vm/debug.c"
  "src/vm/value.c"
  "src/vm/vm.c"
  )

set(CLOX_PARSER_SRC
  "src/parser/scanner.c"
  "src/parser/compiler.c"
  )

add_executable(${TARGET} src/main.c ${CLOX_VM_SRC} ${CLOX_PARSER_SRC})

