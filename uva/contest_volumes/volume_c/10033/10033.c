#include <stdio.h>
#include <string.h>

#define REGISTER_COUNT 10
#define RAM_SIZE 1000
#define LINE_SIZE 5

typedef struct computer {
  int registers[REGISTER_COUNT];
  int ram[RAM_SIZE];
} Computer;

Computer initialize_registers(Computer c) {
  int i;

  for (i = 0; i < REGISTER_COUNT; i++) {
    c.registers[i] = 0;
  }

  return c;
}

Computer initialize_ram(Computer c) {
  int i;

  for (i = 0; i < RAM_SIZE; i++) {
    c.ram[i] = 0;
  }

  return c;
}

Computer initialize_computer() {
  Computer c;

  c = initialize_registers(c);
  c = initialize_ram(c);

  return c;
}

Computer load_program(Computer c) {
  int i;
  char line[LINE_SIZE];

  for (i = 0; i < RAM_SIZE; i++) {
    if (fgets(line, LINE_SIZE, stdin)) {
      if (line[0] == '\n') {
        break;
      } else {
        int instruction;
        sscanf(line, "%d", &instruction);
        c.ram[i] = instruction;
      }
    } else {
      break;
    }
  }

  return c;
}

void dump_ram(Computer c) {
  int i;

  for (i = 0; i < RAM_SIZE; i++) {
    printf("%.3d - %.3d\n", i, c.ram[i]);
  }
}

int get_number_of_cases() {
  int number_of_cases;
  char line[LINE_SIZE];

  fgets(line, LINE_SIZE, stdin);
  sscanf(line, "%d", &number_of_cases);
  fgets(line, LINE_SIZE, stdin);

  return number_of_cases;
}

int run_program(Computer c) {
  return 0;
}

int main() {
  int number_of_cases = get_number_of_cases();
  int i;

  for (i = 0; i < number_of_cases; i++) {
    Computer c = initialize_computer();
    c = load_program(c);
    printf("%d\n", run_program(c));
  }

  return 0;
}
