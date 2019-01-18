#include <iostream>

#include <stdlib.h>
#include <time.h>

#include "opencv_mat_mul.h"
#include "mansoo_mat.h"

#include "util.h"

void check_mansoo_matrix_mul() {
  auto mat_a = MSMat<float>(3);
  auto mat_b = MSMat<float>(3);
  auto mat_c = MSMat<float>(3);

  float value = 1;

  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      mat_a.set(row, col, value);
      mat_b.set(row, col, 10.0f - value);
      mat_c.set(row, col, 0);

      value++;
    }
}

#ifdef USE_OPENMP
    mat_c.mul_using_mp(mat_a, mat_b);
#else
  mat_c.mul(mat_a, mat_b);
#endif

  mat_a.print();
  mat_b.print();
  mat_c.print();
}

template <typename T>
void test_mansoo_matrix_mul(int size) {
  auto mat_a = MSMat<T>(size);
  auto mat_b = MSMat<T>(size);
  auto mat_c = MSMat<T>(size);

  mat_a.fill_ones();
  mat_b.fill_ones();
  mat_c.fill_zeros();

  auto start_time = what_time_is_it_now();

  mat_c.mul(mat_a, mat_b);

  auto end_time = what_time_is_it_now();

  std::cout << "test_mansoo_matrix_mul() running time: " << end_time - start_time << " seconds." << std::endl;

  //  mat_a.print();
  //  mat_b.print();
  //  mat_c.print();
}

template <typename T>
void test_mansoo_matrix_mul_using_mp(int size) {
  auto mat_a = MSMat<T>(size);
  auto mat_b = MSMat<T>(size);
  auto mat_c = MSMat<T>(size);

  mat_a.fill_ones();
  mat_b.fill_ones();
  mat_c.fill_zeros();

  auto start_time = what_time_is_it_now();

  auto result = mat_c.mul_using_mp(mat_a, mat_b);

  auto end_time = what_time_is_it_now();

  if (result)
    std::cout << "test_mansoo_matrix_mul_using_mp() running time: " << end_time - start_time << " seconds." << std::endl;

  //  mat_a.print();
  //  mat_b.print();
  //  mat_c.print();
}

 int main(int argc, char* argv[]) {
  srand(time(NULL));

  int mat_size = 100;

  if (argc == 2) {
      mat_size = atoi(argv[1]);

      if (mat_size < 2) {
          std::cout << "The matrix size must be greater than 2." << std::endl;
          return -1;
      }
  }
  else {
      std::cout << "Input the matrix size that must be greater than 2." << std::endl;
      std::cout << "Usage: test_mat_mul [matrix_size]" << std::endl << std::endl;
      return -1;
  }

  check_mansoo_matrix_mul();

  std::cout << "---- OpenCV matrix multiplication  ---------" << std::endl;
  std::cout << " ==> The matrix size: " << mat_size << std::endl;
  test_opencv_mat_mul(mat_size, true);
  std::cout << "--------------------------------------------" << std::endl << std::endl;

  std::cout << "---- New matrix multiplication  -------" << std::endl;
  std::cout << " ==> The matrix size: " << mat_size << std::endl;
  std::cout << " ==> Type: int" << std::endl;
  test_mansoo_matrix_mul<int>(mat_size);
  test_mansoo_matrix_mul_using_mp<int>(mat_size);
  std::cout << "--------------------------------------------" << std::endl << std::endl;
  
  std::cout << " ==> Type: float" << std::endl;
  test_mansoo_matrix_mul<float>(mat_size);
  test_mansoo_matrix_mul_using_mp<float>(mat_size);
  std::cout << "--------------------------------------------" << std::endl << std::endl;

  return 0;
}
