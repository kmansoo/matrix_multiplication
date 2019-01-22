# matrix_multiplication

## How to build on Linux
```bash
cd ~/matrix_multiplication
mkdir build  
cd build
cmake ..
make
```

## How to build on macOS
The macOS's clang does not support OpenMP. So you need to install g++ 8.x using homebrew.
After installing g++ 8.x, you can build it with OpenMP.
'''bash
cd ~/matrix_multiplication
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++-8 ..
make
'''

## How to run
```bash
./bin/test_mat_mul 500

1       2       3
4       5       6
7       8       9

9       8       7
6       5       4
3       2       1

30      24      18
84      69      54
138     114     90

---- OpenCV matrix multiplication  ---------
 ==> The matrix size: 500
test_opencv_mat_mul running time: 0.0806658 seconds.
--------------------------------------------

---- New matrix multiplication  -------
 ==> The matrix size: 500
 ==> Type: int
test_mansoo_matrix_mul() running time: 0.108218 seconds.
test_mansoo_matrix_mul_using_mp() running time: 0.0263591 seconds.
--------------------------------------------

 ==> Type: float
test_mansoo_matrix_mul() running time: 0.0357001 seconds.
test_mansoo_matrix_mul_using_mp() running time: 0.0128779 seconds.
--------------------------------------------
```
