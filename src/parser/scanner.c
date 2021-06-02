#include <stdio.h>
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

static bool isAtEnd(Scanner *scanner) { return *scanner->current == '\0'; }

static char advance(Scanner *scanner) {
  scanner->current++;
  return scanner->current[-1];
}

static char peek(Scanner *scanner) {
  return *scanner->current;
}

static bool match(Scanner *scanner, char expected) {
  if (isAtEnd(scanner)) {
    return false;
  }

  if (*scanner->current != expected) {
    return false;
  }

  scanner->current++;
  return true;
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

static void skipWhitespace(Scanner *scanner) {
  for (;;) {
    char c = peek(scanner);
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance(scanner);
      break;
    default:
      return;

    }
  }
}

Token scanToken(Scanner *scanner) {
  scanner->start = scanner->current;
  if (isAtEnd(scanner)) {
    return makeToken(scanner, TOKEN_EOF);
  }

  char c = advance(scanner);
  switch (c) {
  case '(':
    return makeToken(scanner, TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(scanner, TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(scanner, TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(scanner, TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(scanner, TOKEN_SEMICOLON);
  case ',':
    return makeToken(scanner, TOKEN_COMMA);
  case '.':
    return makeToken(scanner, TOKEN_DOT);
  case '-':
    return makeToken(scanner, TOKEN_MINUS);
  case '+':
    return makeToken(scanner, TOKEN_PLUS);
  case '/':
    return makeToken(scanner, TOKEN_SLASH);
  case '*':
    return makeToken(scanner, TOKEN_STAR);
  case '!':
    return makeToken(scanner, match(scanner, '=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return makeToken(scanner, match(scanner, '=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return makeToken(scanner, match(scanner, '=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return makeToken(scanner, match(scanner, '=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  }

  return errorToken(scanner, "Unexpected character.");
}
