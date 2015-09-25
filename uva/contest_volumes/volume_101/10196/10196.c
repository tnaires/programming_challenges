#include <stdio.h>
#include <ctype.h>

#define SQUARE_COUNT 8
#define LINE_SIZE 10

#define BLANK_SQUARE '.'

#define BLACK_PAWN 'p'
#define BLACK_KNIGHT 'n'
#define BLACK_BISHOP 'b'
#define BLACK_ROOK 'r'
#define BLACK_QUEEN 'q'
#define BLACK_KING 'k'

#define WHITE_PAWN 'P'
#define WHITE_KNIGHT 'N'
#define WHITE_BISHOP 'B'
#define WHITE_ROOK 'R'
#define WHITE_QUEEN 'Q'
#define WHITE_KING 'K'

typedef enum { false, true } bool;
typedef enum { no_king, white_king, black_king } result;

typedef struct board {
  char pieces[SQUARE_COUNT][SQUARE_COUNT];
} Board;

bool is_empty(Board b) {
  int i, j;

  for (i = 0; i < SQUARE_COUNT; i++) {
    for (j = 0; j < SQUARE_COUNT; j++) {
      if (b.pieces[i][j] != BLANK_SQUARE) {
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

void print_results(result r, int game_count) {
  switch (r) {
    case no_king:
      printf("Game #%d: no king is in check.\n", game_count);
      break;
    case white_king:
      printf("Game #%d: white king is in check.\n", game_count);
      break;
    case black_king:
      printf("Game #%d: black king is in check.\n", game_count);
      break;
  }
}

bool check_black_pawn(Board b, int i, int j) {
  if (i + 1 < SQUARE_COUNT) {
    if (j - 1 >= 0 && b.pieces[i + 1][j - 1] == WHITE_KING) {
      return true;
    }

    if (j + 1 < SQUARE_COUNT && b.pieces[i + 1][j + 1] == WHITE_KING) {
      return true;
    }
  }

  return false;
}

bool check_white_pawn(Board b, int i, int j) {
  if (i - 1 >= 0) {
    if (j - 1 >= 0 && b.pieces[i - 1][j - 1] == BLACK_KING) {
      return true;
    }

    if (j + 1 < SQUARE_COUNT && b.pieces[i - 1][j + 1] == BLACK_KING) {
      return true;
    }
  }

  return false;
}

bool check_knight(Board b, int i, int j, char target_king) {
  if (i - 1 >= 0) {
    if (j - 2 >= 0 && b.pieces[i - 1][j - 2] == target_king) {
      return true;
    }

    if (j + 2 < SQUARE_COUNT && b.pieces[i - 1][j + 2] == target_king) {
      return true;
    }
  }

  if (i - 2 >= 0) {
    if (j - 1 >= 0 && b.pieces[i - 2][j - 1] == target_king) {
      return true;
    }

    if (j + 1 < SQUARE_COUNT && b.pieces[i - 2][j + 1] == target_king) {
      return true;
    }
  }

  if (i + 1 < SQUARE_COUNT) {
    if (j - 2 >= 0 && b.pieces[i + 1][j - 2] == target_king) {
      return true;
    }

    if (j + 2 < SQUARE_COUNT && b.pieces[i + 1][j + 2] == target_king) {
      return true;
    }
  }

  if (i + 2 < SQUARE_COUNT) {
    if (j - 1 >= 0 && b.pieces[i + 2][j - 1] == target_king) {
      return true;
    }

    if (j + 1 < SQUARE_COUNT && b.pieces[i + 2][j + 1] == target_king) {
      return true;
    }
  }

  return false;
}

bool check_bishop(Board b, int i, int j, char target_king, bool only_one_step) {
  int a, count;
  bool look_left = true, look_right = true;

  for (count = 1, a = i - 1; a >= 0; a--, count++) {
    int left = j - count;

    if (look_left && left >= 0) {
      char piece = b.pieces[a][left];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_left = false;
      }
    }

    int right = j + count;

    if (look_right && right < SQUARE_COUNT) {
      char piece = b.pieces[a][right];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_right = false;
      }
    }

    if (!look_left && !look_right) {
      break;
    }

    if (a == i - 1 && only_one_step) {
      break;
    }
  }

  look_left = true;
  look_right = true;

  for (count = 1, a = i + 1; a < SQUARE_COUNT; a++, count++) {
    int left = j - count;

    if (look_left && left >= 0) {
      char piece = b.pieces[a][left];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_left = false;
      }
    }

    int right = j + count;

    if (look_right && right < SQUARE_COUNT) {
      char piece = b.pieces[a][right];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_right = false;
      }
    }

    if (!look_left && !look_right) {
      break;
    }

    if (a == i + 1 && only_one_step) {
      break;
    }
  }

  return false;
}

bool check_rook(Board b, int i, int j, char target_king, bool only_one_step) {
  int a;
  bool look_up = true, look_down = true, look_left = true, look_right = true;

  for (a = 1; a < SQUARE_COUNT; a++) {
    if (look_up && i - a >= 0) {
      char piece = b.pieces[i - a][j];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_up = false;
      }
    }

    if (look_down && i + a < SQUARE_COUNT) {
      char piece = b.pieces[i + a][j];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_down = false;
      }
    }

    if (look_left && j - a >= 0) {
      char piece = b.pieces[i][j - a];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_left = false;
      }
    }

    if (look_right && j + a < SQUARE_COUNT) {
      char piece = b.pieces[i][j + a];

      if (piece == target_king) {
        return true;
      } else if (piece != BLANK_SQUARE) {
        look_right = false;
      }
    }

    if (!look_up && !look_down && !look_left && !look_right) {
      break;
    }

    if (a == 1 && only_one_step) {
      break;
    }
  }

  return false;
}

bool check_queen(Board b, int i, int j, char target_king) {
  return check_rook(b, i, j, target_king, false) || check_bishop(b, i, j, target_king, false);
}

bool check_king(Board b, int i, int j, char target_king) {
  return check_rook(b, i, j, target_king, true) || check_bishop(b, i, j, target_king, true);
}

result check_kings(Board b) {
  int i, j;

  for (i = 0; i < SQUARE_COUNT; i++) {
    for (j = 0; j < SQUARE_COUNT; j++) {
      char piece = b.pieces[i][j];

      switch (piece) {
        case BLACK_PAWN:
          if (check_black_pawn(b, i, j)) {
            return white_king;
          }

          break;
        case WHITE_PAWN:
          if (check_white_pawn(b, i, j)) {
            return black_king;
          }

          break;
        case BLACK_KNIGHT:
          if (check_knight(b, i, j, WHITE_KING)) {
            return white_king;
          }

          break;
        case WHITE_KNIGHT:
          if (check_knight(b, i, j, BLACK_KING)) {
            return black_king;
          }

          break;
        case BLACK_BISHOP:
          if (check_bishop(b, i, j, WHITE_KING, false)) {
            return white_king;
          }

          break;
        case WHITE_BISHOP:
          if (check_bishop(b, i, j, BLACK_KING, false)) {
            return black_king;
          }

          break;
        case BLACK_ROOK:
          if (check_rook(b, i, j, WHITE_KING, false)) {
            return white_king;
          }

          break;
        case WHITE_ROOK:
          if (check_rook(b, i, j, BLACK_KING, false)) {
            return black_king;
          }

          break;
        case BLACK_QUEEN:
          if (check_queen(b, i, j, WHITE_KING)) {
            return white_king;
          }

          break;
        case WHITE_QUEEN:
          if (check_queen(b, i, j, BLACK_KING)) {
            return black_king;
          }

          break;
        case BLACK_KING:
          if (check_king(b, i, j, WHITE_KING)) {
            return white_king;
          }

          break;
        case WHITE_KING:
          if (check_king(b, i, j, BLACK_KING)) {
            return black_king;
          }

          break;
      }
    }
  }

  return no_king;
}

void analyze_board(Board b, int game_count) {
  result r = check_kings(b);
  print_results(r, game_count);
}

int main() {
  char line[LINE_SIZE];
  int i, j, game_count = 0;
  Board b;

  do {
    for (i = 0; i < SQUARE_COUNT; i++) {
      fgets(line, LINE_SIZE, stdin);

      for (j = 0; j < SQUARE_COUNT; j++) {
        b.pieces[i][j] = line[j];
      }
    }

    fgets(line, LINE_SIZE, stdin);

    if (is_empty(b)) {
      break;
    } else {
      game_count++;
      analyze_board(b, game_count);
    }
  } while (true);

  return 0;
}
