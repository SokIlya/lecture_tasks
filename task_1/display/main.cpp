#include <iomanip>
#include <iostream>

constexpr int N_ROWS = 5;
constexpr int N_COLS = 10;
constexpr int WORD_BUFFER_SIZE = N_COLS + 2;

bool are_equal_strings(const char* string1, const char* string2) {
  int i = 0;
  while (string1[i] != '\0' && string2[i] != '\0') {
    if (string1[i] != string2[i]) {
      return false;
    }
    ++i;
  }

  return string1[i] == string2[i];
}

int get_length_of_word(const char word[WORD_BUFFER_SIZE]) {
  for (int i = 0; i < WORD_BUFFER_SIZE; ++i) {
    if (word[i] == '\0') {
      return i;
    }
  }

  return -1;
}

void clear(char display[N_ROWS][N_COLS]) {
  for (int row = 0; row < N_ROWS; ++row) {
    for (int col = 0; col < N_COLS; ++col) {
      display[row][col] = ' ';
    }
  }
}

bool put(char display[N_ROWS][N_COLS], const int x, const int y,
         const char symbol) {
  if (y < 0 || y >= N_ROWS || x < 0 || x >= N_COLS) {
    return false;
  }

  display[y][x] = symbol;
  return true;
}

bool text(char display[N_ROWS][N_COLS], const int x, const int y,
          const char word[WORD_BUFFER_SIZE]) {
  int word_length = get_length_of_word(word);

  if (word_length == -1 || y < 0 || y >= N_ROWS || x < 0 ||
      x + word_length - 1 >= N_COLS) {
    return false;
  }

  for (int i = 0; i < word_length; ++i) {
    put(display, x + i, y, word[i]);
  }
  return true;
}

void print(const char display[N_ROWS][N_COLS]) {
  for (int row = 0; row < N_ROWS; ++row) {
    for (int col = 0; col < N_COLS; ++col) {
      std::cout << display[row][col];
    }
    std::cout << '\n';
  }
}

int main() {
  char display[N_ROWS][N_COLS];
  clear(display);

  while (true) {
    char cmd[WORD_BUFFER_SIZE];
    std::cin >> std::setw(WORD_BUFFER_SIZE) >> cmd;

    if (are_equal_strings(cmd, "quit")) {
      break;
    }

    if (are_equal_strings(cmd, "clear")) {
      clear(display);
    } else if (are_equal_strings(cmd, "put")) {
      int x;
      int y;
      char symbol;
      std::cin >> x >> y >> symbol;

      bool completed = put(display, x, y, symbol);

      if (!completed) {
        std::cout << "error\n";
      }
    } else if (are_equal_strings(cmd, "text")) {
      int x;
      int y;
      char word[WORD_BUFFER_SIZE];
      std::cin >> x >> y >> std::setw(WORD_BUFFER_SIZE) >> word;

      bool completed = text(display, x, y, word);

      if (!completed) {
        std::cout << "error\n";
      }
    } else if (are_equal_strings(cmd, "print")) {
      print(display);
    }
  }

  return 0;
}
