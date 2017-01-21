#include "../manipulation/manipulation.hpp"
#include "matrix.hpp"
#include <math.h>
#include <stdarg.h>
#include <string>
#include <vector>

double
duco::matrix::Matrix::SubDeterminate(std::vector<std::vector<double>> matrix) {
  double det = 0;
  int nrow = matrix[0].size(), ncol = matrix.size();
  if (nrow != ncol) {
    return (0);
  } else if (nrow == 2 && ncol == 2) {
    det = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
  } else {
    for (int i = 0; i < ncol; i++) {
      std::vector<std::vector<double>> submatrix;
      for (int j = 0; j < ncol; j++) {
        if (j == i) {
          j++;
          if (j == ncol) {
            break;
          }
        }
        std::vector<double> col;
        for (int k = 1; k < nrow; k++) {
          col.push_back(matrix[j][k]);
        }
        submatrix.push_back(col);
      }
      det += (pow(-1, i) * matrix[i][0] * SubDeterminate(submatrix));
      submatrix.clear();
    }
  }
  return (det);
}

duco::matrix::Matrix::Matrix(int nrow, int ncol, ...) {
  valcount = rows * cols;
  rows = nrow;
  cols = ncol;
  va_list ap;
  va_start(ap, ncol);
  for (int i = 0; i < rows; i++) {
    std::vector<double> row;
    for (int j = 0; j < cols; j++) {
      row.push_back(va_arg(ap, double));
    }
    vals.push_back(row);
  }
}

duco::matrix::Matrix::Matrix(const Matrix &clone) {
  vals = clone.vals;
  valcount = clone.valcount;
  rows = clone.rows;
  cols = clone.cols;
}

duco::matrix::Matrix::~Matrix() {
  vals.clear();
  valcount = 0;
  rows = 0;
  cols = 0;
}

double duco::matrix::Matrix::Determinate() {
  double det = SubDeterminate(vals);
  return (det);
}

void duco::matrix::Matrix::Transpose() {
  std::vector<std::vector<double>> newvals;
  for (int i = 0; i < cols; i++) {
    std::vector<double> row;
    for (int j = 0; j < rows; j++) {
      row.push_back(vals[j][i]);
    }
    newvals.push_back(row);
  }
  vals = newvals;
  int trow = rows, tcol = cols;
  rows = tcol;
  cols = trow;
}

void duco::matrix::Matrix::SumRows() {
  for (int i = 0; i < rows; i++) {
    for (int j = cols - 1; j > 0; j--) {
      vals[i][0] += vals[i][j];
      vals[i].erase(vals[i].begin() + j);
    }
  }
  cols = 1;
}

void duco::matrix::Matrix::SumCols() {
  for (int i = rows - 1; i > 0; i--) {
    for (int j = 0; j < cols; j++) {
      vals[0][j] += vals[i][j];
    }
    vals.erase(vals.begin() + i);
  }
  rows = 1;
}

double duco::matrix::Matrix::Sum() {
  double total = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      total += vals[i][j];
    }
  }
  return (total);
}

std::vector<std::vector<double>> duco::matrix::Matrix::GetMatrix() {
  return (vals);
}
