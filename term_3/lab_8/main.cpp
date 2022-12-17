#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define MEM_DEFAULT 1
#define REPS_DEFAULT 1

#define BENCH(NAME, TYPE, ARG, TO_TEST)                                        \
  void bench_##NAME(TYPE ARG, int reps, int N) {                               \
    std::cout << "Test: " << #NAME << std::endl                                \
              << "repeat: " << reps << std::endl                               \
              << "size: " << N << std::endl;                                   \
    std::vector<double> results(reps);                                         \
    TYPE ARG##_copy = ARG;                                                     \
    for (int i = 0; i < reps; ++i) {                                           \
      ARG = ARG##_copy;                                                        \
      auto start = std::chrono::high_resolution_clock::now();                  \
      asm volatile("" ::"g"(start));                                           \
      for (int j = 0; j < N; ++j) {                                            \
        TO_TEST;                                                               \
      }                                                                        \
      auto end = std::chrono::high_resolution_clock::now();                    \
      asm volatile("" ::"g"(end));                                             \
      results[i] =                                                             \
          std::chrono::duration<double>(end - start).count() * 1000.0;         \
    }                                                                          \
    const auto average =                                                       \
        std::accumulate(results.begin(), results.end(), 0.0) / results.size(); \
    const auto sigma =                                                         \
        std::sqrt(std::accumulate(results.begin(), results.end(), 0.0,         \
                                  [&](const auto &i, const auto &j) {          \
                                    return i + std::pow(j - average, 2);       \
                                  }) /                                         \
                  results.size());                                             \
    std::cout << "Time(average \u2213 \u03c3): " << average << " \u2213 "      \
              << sigma << " ms" << std::endl                                   \
              << "Range(min \u2026 max):  "                                    \
              << *std::min_element(results.begin(), results.end())             \
              << " \u2026 "                                                    \
              << *std::max_element(results.begin(), results.end()) << " ms"    \
              << std::endl;                                                    \
  }

int maybe_readopt(int argc, char *argv[], int n, int def) {
  if (argc > n) {
    char *flag = nullptr;
    return std::strtoll(argv[n], &flag, 0);
  }
  return def;
}

BENCH(stack_push, std::stack<int>, stack, stack.push(1))
BENCH(stack_pop, std::stack<int>, stack, stack.pop())
BENCH(multiset_insert, std::multiset<int>, multiset, multiset.insert(1))
BENCH(multiset_erase, std::multiset<int>, multiset,
      multiset.erase(std::prev(multiset.end())))
BENCH(multiset_find, std::multiset<int>, multiset, multiset.find(std::rand()))

int main(int argc, char *argv[]) {
  std::srand(std::time(nullptr));

  int size = maybe_readopt(argc, argv, 1, MEM_DEFAULT);
  int reps = maybe_readopt(argc, argv, 2, REPS_DEFAULT);

  /* Для встроенного типа (например, int или char) провести временной анализ
   * заданных шаблонных классов на основных операциях: добавление, удаление,
   * поиск, сортировка. Использовать итераторы для работы с контейнерами.
   * Для получения времени выполнения операции засекать системное время
   * начала и окончания операции и автоматически генерировать большое
   * количество данных
   */
  {
    std::stack<int> stack;
    bench_stack_push(stack, reps, size);
  }
  {
    std::stack<int> stack;
    for (int i = 0; i < size; ++i)
      stack.push(std::rand());
    bench_stack_pop(stack, reps, size);
  }
  {
    std::multiset<int> multiset;
    bench_multiset_insert(multiset, reps, size);
  }
  {
    std::multiset<int> multiset;
    for (int i = 0; i < size; ++i)
      multiset.insert(std::rand());
    bench_multiset_erase(multiset, reps, size);
  }
  {
    std::multiset<int> multiset;
    for (int i = 0; i < size; ++i)
      multiset.insert(std::rand());
    bench_multiset_find(multiset, reps, size);
  }
  // {
  //   std::multiset<int> multiset;
  //   for (int i = 0; i < 10; ++i)
  //     multiset.insert(std::rand());
  //   for (const auto &i : multiset)
  //     std::cout << i << std::endl;
  // }
}
