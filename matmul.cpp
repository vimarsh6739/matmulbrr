#include "matmul.h"
#include <cstdlib>

void transpose(double *__restrict__ At, double *__restrict__ A, const int N) {

  const int TS = 32;

  // Why 32? Magic(jk I autotuned it).
  for (int i = 0; i < N; i += TS) {
    for (int j = 0; j < N; j += TS) {
      for (int ii = i; ii < i + TS; ++ii) {
        for (int jj = j; jj < j + TS; ++jj) {
          At[jj * N + ii] = A[ii * N + jj];
        }
      }
    }
  }
}

void matmul_naive(double *__restrict__ A, double *__restrict__ B,
                  double *__restrict__ C, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double cc = 0.0;
      for (int k = 0; k < N; ++k) {
        cc += A[i * N + k] * B[k * N + j];
      }
      C[i * N + j] = cc;
    }
  }
}

void matmul_cached(double *__restrict__ A, double *__restrict__ B,
                   double *__restrict__ C, int N) {
  // life is amazing, becuase C is 0 initialized in my lib.
  for (int i = 0; i < N; ++i) {
    // should still be cache friendly even if we initialize it
    // Loop interchange so our L1 friends don't miss B
    for (int k = 0; k < N; ++k) {
      // Force A's load into a register
      double aa = A[i * N + k];
      for (int j = 0; j < N; ++j) {
        C[i * N + j] += aa * B[k * N + j];
      }
    }
  }
}

void matmul_transposed(double *__restrict__ A, double *__restrict__ B,
                       double *__restrict__ C, int N) {

  double *Bt = (double *)malloc(N * N * sizeof(double));

  transpose(Bt, B, N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      double cc = 0.0;
      // this loop should be cache friendly now??
      for (int k = 0; k < N; ++k) {
        cc += A[i * N + k] * Bt[j * N + k];
      }
      C[i * N + j] = cc;
    }
  }

  free(Bt);
}
