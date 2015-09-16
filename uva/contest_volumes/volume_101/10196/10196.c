#include <stdio.h>

#define SQUARE_COUNT 8
#define LINE_SIZE 10

typedef enum { false, true } bool;

typedef struct board {
  char pieces[SQUARE_COUNT][SQUARE_COUNT];
} Board;

bool is_empty(Board b) {
  int i, j;

  for (i = 0; i < SQUARE_COUNT; i++) {
    for (j = 0; j < SQUARE_COUNT; j++) {
      if (b.pieces[i][j] != '.') {
        return false;
      }
    }
  }

  return true;
}

void print_board(Board b) {
  int i, j;

  for (i = 0; i < SQUARE_COUNT; i++) {
    for (j = 0; j < SQUARE_COUNT; j++) {
      printf("%c", b.pieces[i][j]);
    }

    printf("\n");
  }
}

int main() {
  char line[LINE_SIZE];
  int i, j;
  Board b;

  do {
    for (i = 0; i < SQUARE_COUNT; i++) {
      fgets(line, LINE_SIZE, stdin);

      for (j = 0; j < SQUARE_COUNT; j++) {
        b.pieces[i][j] = line[j];
      }
    }

    fgets(line, LINE_SIZE, stdin);
  } while (!is_empty(b));

  return 0;
}
