#include <iomanip>
#include <iostream>

struct MinAndMax {
  int min;
  int max;
};

double get_mean(const int* array, const int size) {
  int sum = 0;

  for (int i = 0; i < size; ++i) {
    sum += array[i];
  }

  return (double)sum / size;
}

MinAndMax get_min_and_max(const int* array, const int size) {
  int min_value = array[0];
  int max_value = array[0];

  for (int i = 1; i < size; ++i) {
    min_value = array[i] < min_value ? array[i] : min_value;
    max_value = array[i] > max_value ? array[i] : max_value;
  }

  return MinAndMax{min_value, max_value};
}

int count_below_zero(const int* array, const int size) {
  int cnt_below_zero = 0;

  for (int i = 0; i < size; ++i) {
    if (array[i] < 0) {
      ++cnt_below_zero;
    }
  }

  return cnt_below_zero;
}

int main() {
  int n_days;
  std::cin >> n_days;

  int* temperature_array = new int[n_days];

  for (int i = 0; i < n_days; ++i) {
    std::cin >> temperature_array[i];
  }

  double mean_temperature = get_mean(temperature_array, n_days);
  std::cout << std::fixed << std::setprecision(1) << mean_temperature << '\n';

  MinAndMax min_and_max_temperature =
      get_min_and_max(temperature_array, n_days);
  std::cout << min_and_max_temperature.min << ' ' << min_and_max_temperature.max
            << '\n';

  int cnt_below_zero = count_below_zero(temperature_array, n_days);
  std::cout << cnt_below_zero << '\n';

  delete[] temperature_array;

  return 0;
}
