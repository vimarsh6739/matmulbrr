#pragma once

void transpose(double* At, double* A, const int N);

void matmul_naive(double *A, double *B, double *C, int N);

void matmul_cached(double *A, double *B, double *C, int N);

void matmul_transposed(double *A, double *B, double *C, int N);
