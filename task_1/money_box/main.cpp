#include <iomanip>
#include <iostream>

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

void deposit(int& balance) {
  int amount;
  std::cin >> amount;

  if (amount > 0) {
    balance += amount;
  } else {
    std::cout << "error\n";
  }
}

void withdraw(int& balance) {
  int amount;
  std::cin >> amount;

  if (amount > 0 && amount <= balance) {
    balance -= amount;
  } else {
    std::cout << "error\n";
  }
}

void print_balance(int& balance) { std::cout << balance << '\n'; }

void reset_balance(int& balance) { balance = 0; }

void add_scholarship(int& balance) { balance += 40'000; }

int main() {
  constexpr int N_COMMANDS = 5;

  const char* const commands[N_COMMANDS] = {"deposit", "withdraw", "balance",
                                            "reset", "scholarship"};

  void (*const command_functions[N_COMMANDS])(int&) = {
      deposit, withdraw, print_balance, reset_balance, add_scholarship};

  int balance = 0;

  while (true) {
    char cmd[50];
    std::cin >> std::setw(50) >> cmd;

    if (are_equal_strings(cmd, "stop")) {
      break;
    }

    bool command_found = false;

    for (int i = 0; i < N_COMMANDS; ++i) {
      if (are_equal_strings(cmd, commands[i])) {
        command_functions[i](balance);
        command_found = true;
        break;
      }
    }

    if (!command_found) {
      std::cout << "error\n";
    }
  }

  return 0;
}
