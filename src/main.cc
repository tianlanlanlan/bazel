#include <iostream>

bool foo() {
  // Test memory leak and out-of-bounds write
  int *ptr = (int *)malloc(sizeof(int) * 100);
  (void)ptr; // Suppress unused variable warning
  std::cout << "foo" << std::endl;

  int *array = new int[10];
  array[10] = 0; // 故意越界写入
  delete[] array;
  return true;
}

int main() {
  std::cout << "main" << std::endl;
  std::cout << "hello" << std::endl;
  foo();
  return 0;
}
