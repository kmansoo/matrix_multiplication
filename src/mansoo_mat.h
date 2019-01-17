#pragma once

#include <omp.h>

template <typename T>
class MSMat {
  public:
    MSMat(int size);
    ~MSMat();

    bool set(std::uint16_t row, std::uint16_t col, T value);

    bool mul(MSMat<T> &a, MSMat<T> &b);
    bool mul_using_mp(MSMat<T> &a, MSMat<T> &b);

    void print();

  private:
    int size_ = 0;
    int total_size_ = 0;

    T* matrix_ = NULL;
};

template<typename T>
MSMat<T>::MSMat(int size) {
  size_ = size;

  if (size_ < 2) {
    size_ = 2;

    std::cout << "Mat<T>::Mat, The matrix size must be 2 or greater." << std::endl;
  }

  total_size_ = size_ * size_;

  matrix_ = new T[total_size_];

  if (matrix_ == NULL) 
    std::cout << "Mat<T>::Mat, Not enough memory." << std::endl;
}

template<typename T>
MSMat<T>::~MSMat() {
  if (matrix_ != NULL) {
    delete matrix_;

    matrix_ = NULL;
  }
}

template<typename T>
bool MSMat<T>::set(std::uint16_t row, std::uint16_t col, T value) {
  if (matrix_ == NULL)
    return false;

  std::uint32_t pos = row * size_ + col;

  if (pos >= total_size_) {
    std::cout << "Mat<T>::set, Out of range of matrix." << std::endl;
    return false;
  }

  *(matrix_ + pos) = value;

  return true;
}

template<typename T>
bool MSMat<T>::mul(MSMat<T> &a, MSMat<T> &b) {
  if (a.size_ != b.size_ || a.size_ != this->size_) {
    std::cout << "Mat<T>::mul, Out of range of matrix." << std::endl;
    return false;
  }

  if (a.matrix_ == NULL || b.matrix_ == NULL || this->matrix_ == NULL) {
    std::cout << "Mat<T>::mul, Not enough memory." << std::endl;
    return false;
  }

  int idx_1, idx_2, idx_3;

  T* relative_mat_a;
  T* relative_mat_b;
  T* relative_mat_c;

  {
    for (idx_1 = 0; idx_1 < size_; idx_1++) { 
      for (idx_2 = 0; idx_2 < size_; idx_2++) { 
        relative_mat_a = a.matrix_ + idx_2 * size_ + idx_1;
        relative_mat_b = b.matrix_ + idx_1 * size_;
        relative_mat_c = this->matrix_ + idx_2 * size_;

        for (idx_3 = 0; idx_3 < size_; idx_3++) { 
          *relative_mat_c += *relative_mat_a * *relative_mat_b;

          relative_mat_c++;
          relative_mat_b++;
        }
      }
    }
  }

  return true;
}

template<typename T>
bool MSMat<T>::mul_using_mp(MSMat<T> &a, MSMat<T> &b) {
  if (a.size_ != b.size_ || a.size_ != this->size_) {
    std::cout << "Mat<T>::mul, Out of range of matrix." << std::endl;
    return false;
  }

  if (a.matrix_ == NULL || b.matrix_ == NULL || this->matrix_ == NULL) {
    std::cout << "Mat<T>::mul, Not enough memory." << std::endl;
    return false;
  }

  int idx_1, idx_2, idx_3;

  T* relative_mat_a;
  T* relative_mat_b;
  T* relative_mat_c;
  int tid, nthreads;
  int chunk = 10;

  T* mat_a = a.matrix_;
  T* mat_b = b.matrix_;
  T* mat_c = matrix_;

  #pragma omp parallel shared(mat_a, mat_b, mat_c, size_, nthreads) private( idx_1, idx_2, idx_3, relative_mat_a, relative_mat_b, relative_mat_c)
  {
    tid = omp_get_thread_num();

    if (tid == 0) {
      nthreads = omp_get_num_threads();
      //  printf("Starting matrix multiple example with %d threads\n", nthreads);
    }

    #pragma omp for schedule(static, chunk)
    for (idx_1 = 0; idx_1 < size_; idx_1++) { 
      for (idx_2 = 0; idx_2 < size_; idx_2++) { 
        relative_mat_a = mat_a + idx_2 * size_ + idx_1;
        relative_mat_b = mat_b + idx_1 * size_;
        relative_mat_c = mat_c + idx_2 * size_;

        for (idx_3 = 0; idx_3 < size_; idx_3++) { 
          *relative_mat_c += *relative_mat_a * *relative_mat_b;

          relative_mat_c++;
          relative_mat_b++;
        }
      }
    }
  }

  return true;
}

template<typename T>
void MSMat<T>::print() {
  if (matrix_ == NULL)
    return;

  auto value_pos = matrix_;

  for (auto row = 0; row < size_; ++row ) {
      for (auto col = 0; col < size_; ++col ) {
          printf("%3.1f\t", *value_pos);
          value_pos++;
      }

      printf("\n");
  }

  printf("\n");
}

//  test_mansoo_matrix_mul_size_3();
//  void test_mansoo_matrix_mul_size_n(int size);

void test_mansoo_matrix_mul_size_3();
void test_mansoo_matrix_mul_size_n(int size);