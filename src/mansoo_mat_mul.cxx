#include <iostream>
#include <omp.h>

#include <stdio.h>

#include "time_util.h"

void print_array(float* mat, int size) {
    int i, j;
    
    auto start_pos = mat;

    for ( i = 0; i < size; ++i ) {
        for ( j = 0; j < size; ++j )
            printf("%3.1f\t", *(start_pos + j));

        start_pos += size;

        printf("\n");
    }

    printf("\n");
}

void mansoo_matrix_mul(float* mat_a, float* mat_b, float* mat_c, int size) {
  auto mat_b_index_table = new float*[size];

  for (auto index = 0; index < size; index++)
    mat_b_index_table[index] = mat_b + size * index;

  auto start_time = what_time_is_it_now();
  auto relative_mat_c = mat_c;

  int idx_1, idx_2, idx_3;
  float* relative_mat_a;
  float** start_pos;
  float sum;
  int tid, nthreads;
  int chunk = 10;

  #pragma omp parallel shared(mat_a, mat_b, mat_c, size,  mat_b_index_table, nthreads) private(idx_1, idx_2, idx_3, sum, relative_mat_a, start_pos)
  {
    tid = omp_get_thread_num();

    if (tid == 0) {
      nthreads = omp_get_num_threads();

      printf("Starting matrix multiple example with %d threads\n", nthreads);
    }

    /*** Initialize matrices ***/
    #pragma omp for schedule(static, chunk)

    for (idx_1 = 0; idx_1 < size; idx_1++) {
      for (idx_2 = 0; idx_2 < size; idx_2++) {
        relative_mat_a = mat_a + idx_1 * size;
        start_pos = mat_b_index_table;

        sum = 0.0f;
        
        for (idx_3 = 0; idx_3 < size; idx_3++) {
          sum += *relative_mat_a * *(*start_pos + idx_2);

          start_pos++;      //  <--- 비용이 많이 듦
          relative_mat_a++; //  
        }

        *(relative_mat_c + idx_2) = sum;
      }

      relative_mat_c += size;
    }
  }

  auto end_time = what_time_is_it_now();

  std::cout << "mansoo_matrix_mul running time: " << end_time - start_time << " seconds." << std::endl;
}

void test_mansoo_matrix_mul_size_3() {

  std::cout << "test_mansoo_matrix_mul_size_3..." << std::endl;

  int size = 3;

  float* mat_a;
  float* mat_b;
  float* mat_c;

  mat_a = new float[size * size];
  mat_b = new float[size * size];
  mat_c = new float[size * size];

  mat_a[0] = 1; mat_a[1] = 2; mat_a[2] = 3;
  mat_a[3] = 4; mat_a[4] = 5; mat_a[5] = 6;
  mat_a[6] = 7; mat_a[7] = 8; mat_a[8] = 9;

  mat_b[0] = 9; mat_b[1] = 8; mat_b[2] = 7;
  mat_b[3] = 6; mat_b[4] = 5; mat_b[5] = 4;
  mat_b[6] = 3; mat_b[7] = 2; mat_b[8] = 1;

  mat_c[0] = 0; mat_c[1] = 0; mat_c[2] = 0;
  mat_c[3] = 0; mat_c[4] = 0; mat_c[5] = 0;
  mat_c[6] = 0; mat_c[7] = 0; mat_c[8] = 0;

  mansoo_matrix_mul(mat_a, mat_b, mat_c, 3);

  /*
    A 행렬:
    1	2	3	
    4	5	6	
    7	8	9	

    B 행렬:
    9	8	7	
    6	5	4	
    3	2	1	

    AxB 행렬:
    30	24	18	
    84	69	54	
    138	114	90
  */

  print_array(mat_a, 3);
  print_array(mat_b, 3);
  print_array(mat_c, 3);
}

void test_mansoo_matrix_mul_size_n(int size) {
  std::cout << "test_mansoo_matrix_mul_size_n(): " << size << std::endl;

  float* mat_a;
  float* mat_b;
  float* mat_c;

  mat_a = new float[size * size];
  mat_b = new float[size * size];
  mat_c = new float[size * size];

  mansoo_matrix_mul(mat_a, mat_b, mat_c, size);
}

int main(int argc, char* argv[]) {

  srand(time(NULL));

  test_mansoo_matrix_mul_size_3();
  test_mansoo_matrix_mul_size_n(2000);

  return 0;
}
