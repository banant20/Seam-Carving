// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int row = 0; row < height; row++){
    for(int col = 0; col < width; col++){
      ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
    }
  }

  delete mat; // delete the Matrix
}

TEST(test_matrix_fill_border) {
    Matrix* mat = new Matrix;

    const int width = 1;
    const int height = 2;
    const int value = 10;
    Matrix_init(mat, 1, 2);
    Matrix_fill_border(mat, value);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            ASSERT_EQUAL(*Matrix_at(mat, row, col), value);
        }
    }
    delete mat;
}

TEST(test_matrix_fill_border2) {
    Matrix* mat = new Matrix;

    const int width = 7;
    const int height = 5;
    const int value = 10;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 0);

    for (int row = 1; row < height - 1; row++) {
        for (int col = 1; col < width - 1; col++) {
            ASSERT_TRUE(*Matrix_at(mat, row , col) == 10)
        }
    }
    for (int row = 1; row < height - 1; row++) {
        ASSERT_TRUE(*Matrix_at(mat, row, width - 1) == 0);
        ASSERT_TRUE(*Matrix_at(mat, row, 0) == 0);
    }
    for (int col = 0; col < width - 1; col++) {
        ASSERT_TRUE(*Matrix_at(mat, height - 1, col) == 0);
        ASSERT_TRUE(*Matrix_at(mat, 0, col) == 0);
    }
    
    delete mat;
}

TEST(edge_test_max) {
    Matrix* mat = new Matrix;
    const int width = 3;
    const int height = 5;
    const int max_value = 99;
    Matrix_init(mat, width, height);
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            *Matrix_at(mat, row, col) = row * width + col;
        }
    }
    *Matrix_at(mat, 4, 2) = max_value;
    ASSERT_EQUAL(Matrix_max(mat), max_value);
    delete mat;
}

TEST(test_matrix_print) {
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);

    *Matrix_at(mat, 0, 0) = 42;
    ostringstream expected;
    expected << "1 1\n"
        << "42 \n";
    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
}
TEST(test_matrix_init) {
    Matrix* mat = new Matrix;

    const int width = 5;
    const int height = 7;

    Matrix_init(mat, 5, 7);

    ASSERT_EQUAL(width, Matrix_width(mat));
    ASSERT_EQUAL(height, Matrix_height(mat));

    delete mat;
}

TEST(test_matrix_row) {
    Matrix* mat = new Matrix;

    Matrix_init(mat, 2, 2);

    int* ptr = Matrix_at(mat, 1, 0);

    ASSERT_EQUAL(Matrix_row(mat, ptr), 1);

    delete mat;
}

TEST(test_matrix_column) {
    Matrix* mat = new Matrix;

    Matrix_init(mat, 2, 2);

    int* ptr = Matrix_at(mat, 1, 0);

    ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

    delete mat;
}

TEST(test_matrix_column_of_min_value_in_row) {
    Matrix* mat = new Matrix;

    const int width = 3;
    const int height = 5;
    const int value = 60;

    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);

    *Matrix_at(mat, 0, 0) = 25;
    *Matrix_at(mat, 0, 1) = 26;
    *Matrix_at(mat, 0, 2) = 30;

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 2), 0);

    delete mat;
}
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
