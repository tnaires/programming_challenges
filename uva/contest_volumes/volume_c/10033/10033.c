#include <stdio.h>
#include <string.h>

#define REGISTER_COUNT 10
#define RAM_SIZE 1000
#define LINE_SIZE 5

typedef struct computer {
  int registers[REGISTER_COUNT];
  int ram[RAM_SIZE];
  int instruction_pointer, instruction_counter;
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

  c.instruction_pointer = 0;
  c.instruction_counter = 0;
  c = initialize_registers(c);
  c = initialize_ram(c);

  return c;
}

Computer load_program_from_stdin(Computer c) {
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

void dump_registers(Computer c) {
  printf("| 000 | 001 | 002 | 003 | 004 | 005 | 006 | 007 | 008 | 009 |\n");
  printf("| %.3d | %.3d | %.3d | %.3d | %.3d | %.3d | %.3d | %.3d | %.3d | %.3d |\n", c.registers[0], c.registers[1], c.registers[2], c.registers[3], c.registers[4], c.registers[5], c.registers[6], c.registers[7], c.registers[8], c.registers[9]);
}

int get_number_of_cases() {
  int number_of_cases;
  char line[LINE_SIZE];

  fgets(line, LINE_SIZE, stdin);
  sscanf(line, "%d", &number_of_cases);
  fgets(line, LINE_SIZE, stdin);

  return number_of_cases;
}

Computer _0ds(Computer c, int d, int s) {
  if (c.registers[s] != 0) {
    int location = c.registers[d];
    c.instruction_pointer = location;
  } else {
    c.instruction_pointer++;
  }

  return c;
}

Computer _2dn(Computer c, int d, int n) {
  c.registers[d] = n;
  c.instruction_pointer++;
  return c;
}

Computer _3dn(Computer c, int d, int n) {
  c.registers[d] += n;
  c.registers[d] %= 1000;
  c.instruction_pointer++;
  return c;
}

Computer _4dn(Computer c, int d, int n) {
  c.registers[d] *= n;
  c.registers[d] %= 1000;
  c.instruction_pointer++;
  return c;
}

Computer _5ds(Computer c, int d, int s) {
  c.registers[d] = c.registers[s];
  c.instruction_pointer++;
  return c;
}

Computer _6ds(Computer c, int d, int s) {
  c.registers[d] += c.registers[s];
  c.registers[d] %= 1000;
  c.instruction_pointer++;
  return c;
}

Computer _7ds(Computer c, int d, int s) {
  c.registers[d] *= c.registers[s];
  c.registers[d] %= 1000;
  c.instruction_pointer++;
  return c;
}

Computer _8da(Computer c, int d, int a) {
  c.registers[d] = c.ram[c.registers[a]];
  c.instruction_pointer++;
  return c;
}

Computer _9sa(Computer c, int s, int a) {
  c.ram[c.registers[a]] = c.registers[s];
  c.instruction_pointer++;
  return c;
}

Computer run_current_instruction(Computer c) {
  int instruction = c.ram[c.instruction_pointer];
  int command = instruction % 1000 / 100;
  int arg1 = instruction % 100 / 10;
  int arg2 = instruction % 10;

  switch (command) {
    case 0:
      c = _0ds(c, arg1, arg2);
      break;
    case 2:
      c = _2dn(c, arg1, arg2);
      break;
    case 3:
      c = _3dn(c, arg1, arg2);
      break;
    case 4:
      c = _4dn(c, arg1, arg2);
      break;
    case 5:
      c = _5ds(c, arg1, arg2);
      break;
    case 6:
      c = _6ds(c, arg1, arg2);
      break;
    case 7:
      c = _7ds(c, arg1, arg2);
      break;
    case 8:
      c = _8da(c, arg1, arg2);
      break;
    case 9:
      c = _9sa(c, arg1, arg2);
      break;
  }

  c.instruction_counter++;
  return c;
}

Computer run_program(Computer c) {
  while (c.instruction_pointer < RAM_SIZE) {
    int instruction = c.ram[c.instruction_pointer];

    if (instruction == 100) {
      c.instruction_counter++;
      break;
    } else if (instruction != 0) {
      c = run_current_instruction(c);
    }
  }

  return c;
}

int main() {
  int number_of_cases = get_number_of_cases();
  int i;

  for (i = 0; i < number_of_cases; i++) {
    Computer c = initialize_computer();
    c = load_program_from_stdin(c);
    c = run_program(c);
    printf("%d\n", c.instruction_counter);

    if (i < number_of_cases - 1) {
      printf("\n");
    }
  }

  return 0;
}
