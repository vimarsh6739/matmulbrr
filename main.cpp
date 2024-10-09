#include "matmul.h"
#include <iostream>
#include <sys/time.h>

#define NTRIALS 20

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  return (tv.tv_sec * 1.0 + tv.tv_usec * 1e-6);
}

bool check(double *a, double *b, double *c, int n) {

  bool flag = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      double acc = 0.0;
      for (int k = 0; k < n; ++k) {
        acc += a[i * n + k] * b[k * n + j];
      }
      if (c[i * n + j] != acc) {
        flag = false;
        break;
      }
    }
    if (!flag)
      break;
  }

  return flag;
}

int main(int argc, char *argv[]) {
  // check code correctness
  std::srand(std::time(nullptr));

  // Setup input matrices(will set a CLI later)
  for (int m = 128; m <= 2048; m *= 2) {

    double *a = new double[m * m];
    double *b = new double[m * m];
    double *c = new double[m * m];
    std::cout << "input size : " << m << "\n";

    for (int i = 0; i < m * m; ++i) {
      a[i] = (i + 1) * 1.0;
      b[i] = a[i];
      c[i] = 0.0;
    }
    std::cout << "finished init:" << std::endl;
    // // bench naive
    // double s1 = get_time();
    // for (int nt = 0; nt < NTRIALS; ++nt) {
    //   matmul_naive(a, b, c, m);
    // }
    // double e1 = get_time();
    // std::cout << "naive time : " << (e1 - s1) << std::endl;

    // bench cached

    double s2 = get_time();
    for (int nt = 0; nt < NTRIALS; ++nt) {
      matmul_cached(a, b, c, m);
    }
    double e2 = get_time();
    std::cout << "cached time : " << (e2 - s2) << std::endl;

    // bench transposed

    double s3 = get_time();
    for (int nt = 0; nt < NTRIALS; ++nt) {
      matmul_transposed(a, b, c, m);
    }
    double e3 = get_time();
    std::cout << "transposed time : " << (e3 - s3) << std::endl;
    std::cout << "============" <<std::endl;
    // delete memory allocated
    delete[] a;
    delete[] b;
    delete[] c;
  }

  return 0;
}
// int main(int argc, char *argv[]) {
//   std::cout << "benchmark some matmuls here" << std::endl;
// 	// matmul_naive(nullptr, nullptr, nullptr, 1);
// 	return 0;
// }
