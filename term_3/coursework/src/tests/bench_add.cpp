#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

#include "../sorted_string_array.hpp"

#define MEM_DEFAULT 1


int maybe_readopt(int argc, char *argv[], int n, int def) {
  if (argc > n) {
    char *flag = nullptr;
    return std::strtoll(argv[n], &flag, 0);
  }
  return def;
}


int main(int argc, char *argv[]) {
  int size = maybe_readopt(argc, argv, 1, MEM_DEFAULT);


  std::cout << "Test: "
            << "bench_add" << std::endl
            << "size: " << size << " -- " << 10 * size << std::endl;

  for (int i = 1; i < 10; ++i) {
    coursework::SortedStringArray ssa(std::to_string(i) + ".ssa");
    auto start = std::chrono::high_resolution_clock::now();
    asm volatile("" ::"g"(start));

    const auto nsize = i * size;
    for (int j = 0; j < nsize; ++j) {
      // ssa.add("1");  // abcd
      // ssa.add(std::to_string(j));  // 2
      ssa.add(std::to_string(std::rand()));  // 3
    }
    auto end = std::chrono::high_resolution_clock::now();
    asm volatile("" ::"g"(end));

    std::cout << "(" << nsize << ", "
              << std::chrono::duration<double>(end - start).count() * 1000.0
              << ")" << std::endl;
  }
}
