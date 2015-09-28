#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOT_INFORMED -1
#define LINE_LENGTH 82
#define MAX_BALLOTS 1000
#define MAX_CANDIDATES 20

typedef struct candidate {
  int number, vote_count;
  char name[LINE_LENGTH];
} Candidate;

typedef struct ballot {
  int votes[MAX_CANDIDATES];
} Ballot;

int get_n_cases() {
  int n_cases;
  char line[LINE_LENGTH];

  fgets(line, LINE_LENGTH, stdin);
  sscanf(line, "%d", &n_cases);
  fgets(line, LINE_LENGTH, stdin);

  return n_cases;
}

Candidate* get_candidates(int *total_candidates) {
  char line[LINE_LENGTH];
  int n_candidates, i;

  fgets(line, LINE_LENGTH, stdin);
  sscanf(line, "%d", &n_candidates);
  Candidate* candidates = (Candidate *) calloc(n_candidates, sizeof(Candidate));

  for (i = 0; i < n_candidates; i++) {
    fgets(candidates[i].name, LINE_LENGTH, stdin);
    candidates[i].number = i + 1;
    candidates[i].vote_count = 0;
  }

  *total_candidates = n_candidates;
  return candidates;
}

Ballot* get_ballots(int *total_votes) {
  char line[LINE_LENGTH];
  Ballot* ballots = (Ballot *) calloc(MAX_BALLOTS, sizeof(Ballot));
  int n_votes = 0, i = 0, j = 0, k;

  while (fgets(line, LINE_LENGTH, stdin)) {
    if (line[0] == '\n') {
      break;
    }

    char* token = strtok(line, " ");

    while (token) {
      n_votes++;
      ballots[i].votes[j++] = atoi(token);
      token = strtok(NULL, " ");
    }

    for (k = j; k < MAX_CANDIDATES; k++) {
      ballots[i].votes[k] = NOT_INFORMED;
    }

    i++;
    j = 0;
  }

  for (j = i; j < MAX_BALLOTS; j++) {
    for (k = 0; k < MAX_CANDIDATES; k++) {
      ballots[j].votes[k] = NOT_INFORMED;
    }
  }

  *total_votes = n_votes;
  return ballots;
}

Candidate* count_first_choices(Candidate* candidates, Ballot* ballots) {
  int i;

  for (i = 0; i < MAX_BALLOTS; i++) {
    if (ballots[i].votes[0] == NOT_INFORMED) {
      break;
    }

    candidates[ballots[i].votes[0] - 1].vote_count++;
  }

  return candidates;
}

char* check_first_choices(Candidate* candidates, int total_candidates, int total_votes) {
  int i;

  for (i = 0; i < total_candidates; i++) {
    double percent = (double) candidates[i].vote_count / total_votes;

    if (percent > 0.5) {
      return candidates[i].name;
    }
  }

  return NULL;
}

char* get_winner(Candidate* candidates, int total_candidates, Ballot* ballots, int total_votes) {
  char* winner;

  candidates = count_first_choices(candidates, ballots);
  winner = check_first_choices(candidates, total_candidates, total_votes);

  if (winner) {
    return winner;
  }

  return NULL;
}

int main() {
  int i, n_cases = get_n_cases();
  int total_candidates = 0, total_votes = 0;

  for (i = 0; i < n_cases; i++) {
    Candidate* candidates = get_candidates(&total_candidates);
    Ballot* ballots = get_ballots(&total_votes);

    printf("%s\n", get_winner(candidates, total_candidates, ballots, total_votes));

    if (i < n_cases - 1) {
      printf("\n");
    }

    free(ballots);
    free(candidates);
  }

  return 0;
}
