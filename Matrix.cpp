// Project UID af1f95f547e44c8ea88730dfb185559ds

#include <cassert>
#include "Matrix.h"
#include <iostream>

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);

    mat->width = width;
    mat->height = height;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
    assert(!(mat == nullptr));
    os << mat->width << " " << mat->height << std::endl;

    for (int row = 0; row < mat->height; row++) {
        for (int col = 0; col < mat->width; col++) {
            os << *Matrix_at(mat, row, col) << " ";
        }
        os << std::endl;
    }
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
    assert(!(mat == nullptr));
    return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
    assert(!(mat == nullptr));
    return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
    assert(!(mat == nullptr));
    int numElements = ptr - mat->data;
    int rowElements = (numElements / mat->width);

    return rowElements;
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
    assert(!(mat == nullptr));
    int numElements = 0;
    int columnElements = 0;

    numElements = ptr - mat->data;
    columnElements = (numElements % mat->width);

    return columnElements;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
    assert(!(mat == nullptr));
    assert(0 <= row && row < mat->height);
    assert(0 <= column && column < mat->width);

    return (column + (row * mat->width) + mat->data);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
    assert(!(mat == nullptr));
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column && column < Matrix_width(mat));

    const int* ptr = &(mat->data[(column + (row * mat->width))]);

    return ptr;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
    assert(!(mat == nullptr));

    for (int row = 0; row < mat->height; row++) {
        for (int col = 0; col < mat->width; col++) {
            *Matrix_at(mat, row, col) = value;
        }
    }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
    assert(!(mat == nullptr));
    for (int row = 0; row < mat->width; row++) {
        *Matrix_at(mat, mat->height - 1, row) = value;
        *Matrix_at(mat, 0, row) = value;
    }
    for (int col = 1; col < mat->height - 1; col++) {
        *Matrix_at(mat, col, mat->width - 1) = value;
        *Matrix_at(mat, col, 0) = value;
    }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
    assert(!(mat == nullptr));
    int max = *Matrix_at(mat, 0, 0);

    for (int row = 0; row < mat->height; row++) {
        for (int col = 0; col < mat->width; col++) {
            if (max < *Matrix_at(mat, row, col)) {
                max = *Matrix_at(mat, row, col);
            }
        }
    }
    return max;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
    assert(!(mat == nullptr));
    assert(0 <= row && row < Matrix_height(mat));
    assert(0 <= column_start && column_end <= Matrix_width(mat));
    assert(column_start < column_end);

    int minColumn = column_start;

    for (int col = column_start; col < column_end; col++) {
        if (*Matrix_at(mat, row, minColumn) > *Matrix_at(mat, row, col)) {
            minColumn = col;
        }
    }
    return minColumn;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
    assert(!(mat == nullptr));
    assert(0 <= row && row < mat->height);
    assert(0 <= column_start && column_end <= mat->width);
    assert(column_start < column_end);

    int min = *Matrix_at(mat, row, column_start);

    for (int col = column_start; col < column_end; col++) {
        if (min > *Matrix_at(mat, row, col)) {
            min = *Matrix_at(mat, row, col);
        }
    }
    return min;
}
