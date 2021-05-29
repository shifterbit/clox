#include <stdio.h>
#include <stdbool.h> 
#include <string.h>

#include "common.h"
#include "scanner.h"



Scanner initScanner(const char *source) {
  Scanner scanner;
  scanner.start = source;
  scanner.current = source;
  scanner.line = 0;
  return scanner;
}

static _Bool isAtEnd(Scanner *scanner) {
  return *scanner->current == '\0';
}

static Token makeToken(Scanner *scanner, TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner->start;
  token.length = (int)(scanner->current - scanner->start);
  token.line = scanner->line;
  return token;
}

static Token errorToken(Scanner *scanner, const char *message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner->line;
  return token;
}

Token scanToken(Scanner *scanner) {
  scanner->start = scanner->current;
  if (isAtEnd(scanner)) {
    return makeToken(scanner, TOKEN_EOF);
  }

  return errorToken(scanner, "Unexpected character.");
}
