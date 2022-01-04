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
TEST(test_image_init_1) {
  Image *img = new Image;
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);
  string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
  std::ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  std::cout << actual << std::endl;
  ASSERT_EQUAL(actual, output_correct);
  delete img;
}

TEST(test_image_init){
  Image *img = new Image;
  Image_init(img, 1, 4);
  ASSERT_EQUAL(Image_width(img),1);
  delete img;
}

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
TEST(test_print) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {0, 0, 0};
  const Pixel green = {0, 0, 0};
  const Pixel blue = {0, 0, 0};
  const Pixel white = {0, 0, 0};

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
  correct << "0 0 0 0 0 0 \n";
  correct << "0 0 0 0 0 0 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img; // delete the Image
}
TEST(test_print_different) {
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

TEST(test_width){
  Image *img = new Image;
  Image_init(img, 2, 3);
  ASSERT_EQUAL(Image_width(img),2);
  delete img;
}
TEST(test_width_max){
  Image *img = new Image;
  Image_init(img, 500, 3);
  ASSERT_EQUAL(Image_width(img),500);
  delete img;
}
TEST(test_height){
  Image *img = new Image;
  Image_init(img, 2, 3);
  ASSERT_EQUAL(Image_height(img),3);
  delete img;
}
TEST(test_height_max){
  Image *img = new Image;
  Image_init(img, 2, 500);
  ASSERT_EQUAL(Image_height(img),500);
  delete img;
}
TEST(test_get_pixel){
  Image *img = new Image;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,0),red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,1),green));
  delete img;
}

TEST(test_set_pixel){
  Image *img = new Image;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,0),red));
  delete img;
}
TEST(test_Image_fill){
  Image *img = new Image;
  const Pixel red = {255, 0, 0};
  const int width=4;
  const int height = 6;
  Image_init(img, width, height);
  Image_fill(img,red);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,i,j),red));
    }
  }
  delete img;
}

TEST(test_Image_fill2){
  Image *img = new Image;
  const Pixel white = {255, 255, 255};
  const int width = 5;
  const int height = 3;
  Image_init(img, width, height);
  Image_fill(img,white);
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,i,j),white));
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
