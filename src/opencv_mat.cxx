#include <iostream>
#include <stdio.h>

#include <opencv2/core.hpp>

#include "util.h"

/*
  CV_32FC1 //real float
  CV_32FC2 //complex float
  CV_64FC1 //real double
  CV_64FC2 //complex double
*/

using namespace cv;

void test_opencv_mat_mul(int size, bool is_float_type) {

  int data_type = CV_32FC1;

  if (!is_float_type)
    data_type = CV_64FC1;

  Mat a = Mat(size, size, data_type);
  Mat b = Mat(size, size, data_type);

  randu(a, Scalar::all(0), Scalar::all(1));
  randu(b, Scalar::all(0), Scalar::all(1));

  auto start_time = what_time_is_it_now();

  Mat c = a * b;

  auto end_time = what_time_is_it_now();

  std::cout << "test_opencv_mat_mul running time: " << end_time - start_time << " seconds." << std::endl;
}
