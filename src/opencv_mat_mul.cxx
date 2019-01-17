#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>

#include "time_util.h"
/*

  CV_32FC1 //real float
  CV_32FC2 //complex float
  CV_64FC1 //real double
  CV_64FC2 //complex double

*/

using namespace std;
using namespace cv;

void PrintArray(float* mat, int size) {
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

void test_opencv_mat_mul(int size) {
  Mat a = Mat(size, size, CV_32FC1);
  Mat b = Mat(size, size, CV_32FC1);

  randu(a, Scalar::all(0), Scalar::all(1));
  randu(b, Scalar::all(0), Scalar::all(1));

  auto start_time = what_time_is_it_now();

  Mat c = a * b;

  auto end_time = what_time_is_it_now();

  //  cout << "a = \n" << format(a, Formatter::FMT_NUMPY) << ";" << endl <<
  //  endl; cout << "b = \n" << format(b, Formatter::FMT_NUMPY) << ";" << endl
  //  << endl; cout << "c = \n" << format(c, Formatter::FMT_NUMPY) << ";" <<
  //  endl << endl;

  cout << "test_opencv_mat_mul running time: " << end_time - start_time
       << " seconds." << endl;
}

void test_matrix_mul_normal(int size) {
  float** A;
  float** B;
  float** C;

  A = new float*[size];
  B = new float*[size];
  C = new float*[size];

  for (auto i = 0; i < size; i++) {
    A[i] = new float[size];
    B[i] = new float[size];
    C[i] = new float[size];
  }

  auto start_time = what_time_is_it_now();

  for (auto i = 0; i < size; i++) {
    for (auto j = 0; j < size; j++) {
      for (auto k = 0; k < size; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  auto end_time = what_time_is_it_now();

  cout << "test_mansoo_matrix_mul1 running time: " << end_time - start_time << " seconds." << endl;
}

void mansoo_matrix_mul(float* mat_a, float* mat_b, float* mat_c, int size) {
  auto mat_b_index_table = new float*[size];

  for (auto index = 0; index < size; index++)
    mat_b_index_table[index] = mat_b + size * index;

  auto start_time = what_time_is_it_now();

  auto row_start_pos_1 = 0;
  auto relative_mat_c = mat_c;

  for (auto idx_1 = 0; idx_1 < size; idx_1++) {

    for (auto idx_2 = 0; idx_2 < size; idx_2++) {
      auto row_start_pos_2 = 0;
      
      auto relative_mat_a = mat_a + idx_1 * size;
    
      auto start_pos = mat_b_index_table;

      float sum = 0.0f;

      for (auto idx_3 = 0; idx_3 < size; idx_3++) {
        sum += *relative_mat_a * *(*start_pos + idx_2);

        start_pos++;      //  <--- 비용이 많이 듦
        relative_mat_a++; //  
      }

      *(relative_mat_c + idx_2) = sum;

      row_start_pos_2 += size;
    }

    relative_mat_c += size;
  }

  auto end_time = what_time_is_it_now();

  cout << "mansoo_matrix_mul running time: " << end_time - start_time << " seconds." << endl;
}

void test_mansoo_matrix_mul_size_3() {

  cout << "test_mansoo_matrix_mul_size_3..." << endl;

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

  PrintArray(mat_a, 3);
  PrintArray(mat_b, 3);
  PrintArray(mat_c, 3);
}

void test_mansoo_matrix_mul_size_n(int size) {
  cout << "test_mansoo_matrix_mul_size_n(): " << size << endl;

  float* mat_a;
  float* mat_b;
  float* mat_c;

  mat_a = new float[size * size];
  mat_b = new float[size * size];
  mat_c = new float[size * size];

  mansoo_matrix_mul(mat_a, mat_b, mat_c, size);
}

int main(int argc, char** argv) {
    srand(time(NULL));

    //  test_opencv_mat_mul(10000);
    //  test_mansoo_matrix_mul1(1500);
    test_mansoo_matrix_mul_size_3();
    test_mansoo_matrix_mul_size_n(1000);

    return 0;
}
