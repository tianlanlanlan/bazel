#include <iostream>
#include <limits>

bool test_asan_issues() {
  // Test memory leak and out-of-bounds write
  int *ptr = (int *)malloc(sizeof(int) * 100);
  (void)ptr; // Suppress unused variable warning
  std::cout << "foo" << std::endl;

  int *array = new int[10];
  array[10] = 0; // 故意越界写入
  delete[] array;
  return true;
}

void test_c() {
  {
    int a[10];
    a[0] = 10;
    printf("*a = %u, a = %p, &a = %p\n", *a, a, &a); // 你会发现 a == &a
  }

  std::numeric_limits<int>::max();

  {}
}

int main() {
  std::cout << "main" << std::endl;

  test_asan_issues();

  std::numeric_limits<int>::infinity();

  test_c();

  return 0;
}
