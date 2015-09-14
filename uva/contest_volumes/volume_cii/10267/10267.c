#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CMD_LENGTH 50
#define ARG_LENGTH 5
#define DELIMITERS " \n"
#define TABLE_SIZE 250
#define DEFAULT_COLOR 'O'
#define FILENAME_LENGTH 13

/* Queue */
typedef struct node {
  int x, y;
  struct node *next;
} *Node;

typedef struct node *Queue;

Node new_node(int x, int y) {
  Node n = (Node) malloc(sizeof(struct node));
  n->x = x;
  n->y = y;
  n->next = NULL;

  return n;
}

Queue new_queue() {
  Queue q = (Queue) malloc(sizeof(struct node));
  q = NULL;
  return q;
}

Queue enqueue(Queue q, int x, int y) {
  Node n = new_node(x, y);

  if (q == NULL) {
    q = n;
  } else {
    n->next = q;
    q = n;
  }

  return q;
}

Node first(Queue q) {
  if (q) {
    Node current = q;

    while (current->next) {
      current = current->next;
    }

    return current;
  } else {
    return NULL;
  }
}

Queue dequeue(Queue q) {
  if (q == NULL) {
    return NULL;
  }

  Node current = q;
  Node prev = NULL;

  while (current->next) {
    prev = current;
    current = current->next;
  }

  if (prev) {
    prev->next = NULL;
  } else {
    q = NULL;
  }

  free(current);
  return q;
}

void print_queue(Queue q) {
  if (q) {
    Node curr = q;

    while (curr) {
      printf("x = %d\n", curr->x);
      curr = curr->next;
    }
  } else {
    printf("Queue is empty.\n");
  }
}

void free_queue(Queue q) {
  Node n = dequeue(q);

  while (n != NULL) {
    free(n);
    n = dequeue(q);
  }
}

/* Table */
typedef struct _table {
	char pixels[TABLE_SIZE][TABLE_SIZE];
	int rows, cols;
} table;

table C(table t) {
	int i, j;
	
	for (i = 0; i < t.rows; i++) {
		for (j = 0; j < t.cols; j++) {
			t.pixels[i][j] = DEFAULT_COLOR;
		}
	}
	
	return t;
}

table I(int m, int n) {
	table result;
	result.rows = n;
	result.cols = m;
	
	return C(result);
}

table L(table t, int x, int y, char c) {
	t.pixels[y - 1][x - 1] = toupper(c);
	return t;
}

table K(table t, int x1, int y1, int x2, int y2, char c) {
	int xleft, xright;
	
	if (x1 < x2) {
		xleft = x1;
		xright = x2;
	} else {
		xleft = x2;
		xright = x1;
	}
	
	int ytop, ybottom;
	
	if (y1 < y2) {
		ytop = y1;
		ybottom = y2;
	} else {
		ytop = y2;
		ybottom = y1;
	}
	
	int i, j;
	
	for (i = xleft - 1; i < xright; i++) {
		for (j = ytop - 1; j < ybottom; j++) {
			t.pixels[j][i] = toupper(c);
		}
	}
	
	return t;
}

table V(table t, int x, int y1, int y2, char c) {
	return K(t, x, y1, x, y2, c);
}

table H(table t, int x1, int x2, int y, char c) {
	return K(t, x1, y, x2, y, c);
}

table fill_table(table t, int x, int y, char old_color, char new_color) {
  Queue q = new_queue();
  q = enqueue(q, x, y);
  Node n = first(q);

  while (n) {
    int n_x = n->x, n_y = n->y;
    int left, right;

    for (left = n_x; left >= 0; left--) {
      if (t.pixels[n_y][left] != old_color) {
        break;
      }
    }

    for (right = n_x; right < t.cols; right++) {
      if (t.pixels[n_y][right] != old_color) {
        break;
      }
    }

    q = dequeue(q);
    left++; right--;
    int i;

    for (i = left; i <= right; i++) {
      t.pixels[n_y][i] = new_color;

      if (n_y - 1 >= 0 && t.pixels[n_y - 1][i] == old_color) {
        q = enqueue(q, i, n_y - 1);
      }

      if (n_y + 1 < t.rows && t.pixels[n_y + 1][i] == old_color) {
        q = enqueue(q, i, n_y + 1);
      }
    }

    n = first(q);
  }

  free_queue(q);
  return t;
}

table F(table t, int x, int y, char new_color) {
  x--; y--;
  new_color = toupper(new_color);
  char old_color = t.pixels[y][x];

  if (old_color == new_color) {
    return t;
  }

  return fill_table(t, x, y, old_color, new_color);
}

void S(table t, char filename[]) {
	int i, j;
	char filename_dos[FILENAME_LENGTH + 1];
	
	strncpy(filename_dos, filename, FILENAME_LENGTH);
	printf("%s\n", filename_dos);
	
	for (i = 0; i < t.rows; i++) {
		for (j = 0; j < t.cols; j++) {
			printf("%c", t.pixels[i][j]);
		}
		
		printf("\n");
	}
}

int main() {
	char line[CMD_LENGTH];
	table t;
	
	while (fgets(line, CMD_LENGTH, stdin)) {
		char *token = strtok(line, DELIMITERS);
		char cmd = token[0];
		
		switch (cmd) {
			case 'I':
			case 'C':
			case 'L':
			case 'V':
			case 'H':
			case 'K':
			case 'F':
			case 'S':
			case 'X':
				break;
			default:
				continue;
		}
		
		char *args[5];
		int arg_count = 0;
		
		do {
			token = strtok(NULL, DELIMITERS);
			
			if (token) {
				args[arg_count] = token;
				arg_count++;
			} else {
				break;
			}
		} while (1 == 1);
		
		switch (cmd) {
			case 'I':
				t = I(atoi(args[0]), atoi(args[1]));
				break;
			case 'C':
				t = C(t);
				break;
			case 'L':
				t = L(t, atoi(args[0]), atoi(args[1]), args[2][0]);
				break;
			case 'V':
				t = V(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), args[3][0]);
				break;
			case 'H':
				t = H(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), args[3][0]);
				break;
			case 'K':
				t = K(t, atoi(args[0]), atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4][0]);
				break;
			case 'F':
				t = F(t, atoi(args[0]), atoi(args[1]), args[2][0]);
				break;
			case 'S':
				S(t, args[0]);
				break;
			case 'X':
				return 0;
				break;
		}
	}

	return 0;
}
