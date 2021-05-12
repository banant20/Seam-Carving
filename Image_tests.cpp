// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(tests_image_print_edge) {
    Image* img = new Image;
    const string expected = "P3\n2 2\n255\n51 52 53 1 2 3 \n101 102 103 151 152 153 \n";
    const string P3 = "P3\n2 2\n255\n51 52 53 1 2 3\n101 102 103 151 152 153";
    string actual;
    istringstream in;
    ostringstream out;

    in.str(P3);
    Image_init(img, in);
    Image_print(img, out);
    actual = out.str();

    ASSERT_EQUAL(actual, expected);

    delete img;
}

TEST(test_image_init) {
    Image* img = new Image;

    const int width = 5;
    const int height = 7;

    Image_init(img, 5, 7);

    ASSERT_EQUAL(width, Image_width(img));
    ASSERT_EQUAL(height, Image_height(img));

    delete img;
}

TEST(test_image_width) {
    Image* img = new Image;

    const int width = 5;

    Image_init(img, 5, 1);

    ASSERT_EQUAL(Image_width(img), width);

    delete img;
}

TEST(test_image_height) {
    Image* img = new Image;

    const int height = 7;

    Image_init(img, 1, 7);

    ASSERT_EQUAL(Image_height(img), height);

    delete img;
}

TEST(test_image_fill) {
    Image* img = new Image;

    Image_init(img, 255, 255);
    Pixel p = { 22, 64, 37 };
    Image_fill(img, p);

    for (int row = 0; row < Image_height(img) - 1; row++) {
        for (int col = 0; col < Image_width(img) - 1; col++) {
            Pixel firstPixel = Image_get_pixel(img, row + 1, col + 1);
            Pixel secondPixel = Image_get_pixel(img, row, col);

            ASSERT_TRUE(Pixel_equal(firstPixel, secondPixel));
        }
    }
    delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
