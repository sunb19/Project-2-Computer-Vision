// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  assert(img!=nullptr);
  assert(width>0&&width<=MAX_MATRIX_WIDTH);
  assert(height>0&&height<=MAX_MATRIX_HEIGHT);
  img->width=width;
  img->height=height;
  Matrix_init(&img->red_channel,img->width,img->height);
  Matrix_init(&img->green_channel,img->width,img->height);
  Matrix_init(&img->blue_channel,img->width,img->height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  assert(img!=nullptr);
  string p3;
  int maxRGBValue;
  is>>p3>>img->width>>img->height>>maxRGBValue;
  int redValue; 
  int greenValue; 
  int blueValue;
  Image_init(img,img->width,img->height);
  Matrix_init(&img->red_channel,img->width,img->height);
  Matrix_init(&img->green_channel,img->width,img->height);
  Matrix_init(&img->blue_channel,img->width,img->height);
  for(size_t i=0; i<img->height;++i){
    for(size_t j=0; j<img->width;++j){
      is>>redValue>>greenValue>>blueValue;
        Pixel p;
        p.r=redValue;
        p.g=greenValue;
        p.b=blueValue;
        Image_set_pixel(img,i,j,p);
      
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  assert(img!=nullptr);
  os<<"P3"<<endl;
  os<<img->width<<" "<<img->height<<endl;
  os<<"255"<<endl;
  
  for(size_t i = 0; i<img->height;++i){
    for(size_t j =0; j<img->width;++j){
      os<<*Matrix_at(&(img->red_channel),i,j)<<" "<<*Matrix_at(&(img->green_channel),i,j)
      <<" "<<*Matrix_at(&(img->blue_channel),i,j)<<" ";
    }
    os<<"\n";
  }

}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  assert(img!=nullptr);
  return img->width;  
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  assert(img!=nullptr);
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(img!=nullptr);
  assert(0<=row&&row<Image_height(img));
  assert(0<=column&&column<Image_width(img));
  Pixel p;
  p.r=*Matrix_at(&img->red_channel,row,column);
  p.g=*Matrix_at(&img->green_channel,row,column);
  p.b=*Matrix_at(&img->blue_channel,row,column);
  return p;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(img!=nullptr);
  assert(0<=row&&row<Image_height(img));
  assert(0<=column&&column<Image_width(img));
  *Matrix_at(&img->red_channel,row,column) = color.r;
  *Matrix_at(&img->green_channel,row,column) = color.g;
  *Matrix_at(&img->blue_channel,row,column) = color.b;
} 

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  assert(img!=nullptr);
  Matrix_fill(&img->red_channel,color.r);
  Matrix_fill(&img->green_channel,color.g);
  Matrix_fill(&img->blue_channel,color.b);
}
