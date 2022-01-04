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

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  delete mat; // delete the Matrix
}

TEST(test_matrix_init){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  ASSERT_TRUE(mat!=nullptr);
  ASSERT_TRUE(Matrix_width(mat)==3);
  delete mat;
}
TEST(test_matrix_init2){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 5);
  ASSERT_TRUE(mat!=nullptr);
  ASSERT_TRUE(Matrix_height(mat)==5);
  delete mat;
}

//tests to see if value is different
TEST(test_fill_edgecase) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 2;
  const int height = 2;
  const int value = -42;
  Matrix_init(mat,width,height);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_NOT_EQUAL(*Matrix_at(mat, r, c), 0);
    }
  }
  delete mat; // delete the Matrix
}

TEST(test_fill_case2) {
  Matrix *mat = new Matrix; 

  const int width = 4;
  const int height = 10;
  const int value = 42;
  Matrix_init(mat, 4, 10);
  Matrix_fill(mat, value);

  for(int i = 0; i < height; ++i){
    for(int j = 0; j < width; ++j){
      ASSERT_EQUAL(*Matrix_at(mat, i, j), 42);
    }
  }
  delete mat; 
}

//tests border values
TEST(test_fill_border){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  const int value = 20;
  const int test = 25;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,test);
 
  for(size_t i=0; i<height;++i){
    ASSERT_EQUAL(*Matrix_at(mat,i,0),test);
    ASSERT_EQUAL(*Matrix_at(mat,i,width-1),test);
  }
  for(size_t j=1; j<width-1;++j){
    ASSERT_EQUAL(*Matrix_at(mat,0,j),test);
    ASSERT_EQUAL(*Matrix_at(mat,height-1,j),test);
  }
  delete mat;
}
TEST(test_fill_border2){
  Matrix *mat = new Matrix;
  const int value = 9999;
  const int test = 0;
  Matrix_init(mat,MAX_MATRIX_WIDTH,MAX_MATRIX_HEIGHT);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,test);
  for(int i=0; i<MAX_MATRIX_HEIGHT;++i){
    for(int j=0; j<MAX_MATRIX_WIDTH;++j){
      if(i==0||i==MAX_MATRIX_HEIGHT-1||
      j==0||j==MAX_MATRIX_WIDTH-1){
        ASSERT_EQUAL(*Matrix_at(mat,i,j),test);
      }else{
        ASSERT_EQUAL(*Matrix_at(mat,i,j),value);
      }
    }
  }
  delete mat;
}

//tests matrix print
TEST(test_matrix_print){
  const int value = 10;
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 3);
  Matrix_fill(mat,value);
  ostringstream expected;
  expected << "3 3\n"
           << "10 10 10 \n"
           << "10 10 10 \n"
           << "10 10 10 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  delete mat;
}

TEST(test_matrix_print2){
  const int value = 15;
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,10);
  *Matrix_at(mat,3,4) = 0;
  ostringstream expected;
  expected << "5 5\n"
           << "10 10 10 10 10 \n"
           << "10 15 15 15 10 \n"
           << "10 15 15 15 10 \n"
           << "10 15 15 15 0 \n"
           << "10 10 10 10 10 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  delete mat;
}

TEST(test_one_by_one)
{
  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, 9999);
  ostringstream expected;
  expected << "1 1\n"
           << "9999 \n";
  ostringstream actual;
  Matrix_print(mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
  delete mat;
}

//test column
TEST(test_column){
  Matrix *mat = new Matrix;
  const int height = 4;
  const int width = 5;
  Matrix_init(mat,width,height);
  int *loc = (Matrix_at(mat,1,4));
  ASSERT_EQUAL(Matrix_column(mat,loc), 4);
  delete mat;
}
TEST(test_column_max){
  Matrix *mat = new Matrix;
  Matrix_init(mat,500,500);
  int *matrixptr = Matrix_at(mat,50,450);
  ASSERT_EQUAL(Matrix_column(mat,matrixptr),450);
  delete mat;
}
//test row
TEST(test_row){
  Matrix *mat = new Matrix;
  const int height = 4;
  const int width = 5;
  Matrix_init(mat,width,height);
  int *ptr1 = (Matrix_at(mat,1,4));
  ASSERT_EQUAL(Matrix_row(mat,ptr1), 1);
  delete mat;
}
TEST(test_row_max){
  Matrix *mat = new Matrix;
  Matrix_init(mat, 500, 500);
  int *matrixptr = Matrix_at(mat, 50, 450);
  ASSERT_EQUAL(Matrix_row(mat, matrixptr), 50);
  delete mat;
}

//tests matrix width value
TEST(test_matrix_width){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  ASSERT_EQUAL(Matrix_width(mat),5);
  delete mat;
}

//test Matrix at
TEST(test_matrix_at){
  Matrix *mat = new Matrix;
  const int height = 4;
  const int width = 5;
  const int value = 20;
  const int test = 15;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,test);
  ASSERT_EQUAL((*Matrix_at(mat,0,0)), 15);
  delete mat;
}

//tests matrix height value
TEST(test_matrix_height){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  ASSERT_EQUAL(Matrix_height(mat),3);
  delete mat;
}
//tests max matrix heiht
TEST(test_matrix_heightmax){
  Matrix *mat = new Matrix;
  const int height = 500;
  const int width = 5;
  Matrix_init(mat,width,height);
  ASSERT_EQUAL(Matrix_height(mat),500);
  delete mat;
}
//tests max matrix width
TEST(test_matrix_widthmax){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 500;
  Matrix_init(mat,width,height);
  ASSERT_EQUAL(Matrix_width(mat),500);
  delete mat;
}
//tests max matrix value
TEST(test_matrix_max){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  int * ptrArr = Matrix_at(mat,0,0);
  int i=1;
  for(int *ptr=ptrArr;ptr<ptrArr+(Matrix_height(mat)*Matrix_width(mat));++ptr){
    *ptr=i;
    ++i;
  }
  ASSERT_EQUAL(Matrix_max(mat),15);
  delete mat;
}

TEST(test_matrix_max2){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  Matrix_fill(mat, 10);
  
  *Matrix_at(mat,2,3) = 100;
  ASSERT_EQUAL(Matrix_max(mat), 100);
  
  delete mat;
  
}
TEST(test_matrix_maxneg){
   Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  Matrix_fill(mat, 10);
  *Matrix_at(mat,2,3) = -200;
  ASSERT_EQUAL(Matrix_max(mat), 10);
  delete mat;

}
TEST(test_matrix_max3){
  Matrix *mat = new Matrix;
  Matrix_init(mat,MAX_MATRIX_WIDTH,MAX_MATRIX_HEIGHT);
  Matrix_fill(mat,-10);
  *Matrix_at(mat,100,250)=-100;
  ASSERT_EQUAL(Matrix_max(mat),-10);
  delete mat;
}
//tests min column value
TEST(test_min_column){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  const int value = 20;
  const int test = 15;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,test);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,height-1,0,width),0);
  delete mat;
}
//Tests min_column_same_value
TEST(test_min_column_same_value){
  Matrix *mat = new Matrix;
  const int height = 5;
  const int width = 5;
  const int value = 20;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,value);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,height-1,0,width),0);
  *Matrix_at(mat,3,3) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,3,0,width),3);
  *Matrix_at(mat,3,0) = 1;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,3,0,width),0);
  *Matrix_at(mat, 3, 4) = 0;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,3,0,width),4);
  delete mat;
}
TEST(test_min_column_edge){
  Matrix *mat = new Matrix;
  Matrix_init(mat,2,2);
  *Matrix_at(mat,0,0) = -5;
  *Matrix_at(mat,0,1) = -5;
  *Matrix_at(mat,1,1) = -5;
  *Matrix_at(mat,1,0) = -5;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,0,0,1),0);
  delete mat;
}
TEST(test_min_edge){
  Matrix *mat = new Matrix;
  Matrix_init(mat,2,2);
  *Matrix_at(mat,0,0) = -5;
  *Matrix_at(mat,0,1) = -2;
  *Matrix_at(mat,1,1) = -6;
  *Matrix_at(mat,1,0) = -11;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,2),-5);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,0,2),-11);
  delete mat;
}
TEST(test_min_edge2){
  Matrix *mat = new Matrix;
  Matrix_init(mat,3,3);
  Matrix_fill(mat,5);
  *Matrix_at(mat,0,0) = -5;
  *Matrix_at(mat,0,1) = -2;
  *Matrix_at(mat,0,2) = -6;
  *Matrix_at(mat,1,0)=-10;
  *Matrix_at(mat,1,2)=-20;
  *Matrix_at(mat,2,0)=-21;
  *Matrix_at(mat,2,2)=-24;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,3),-6);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,0,3),-20);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,2,0,3),-24);
  delete mat;
}

TEST(test_min_value3) {
  Matrix *mat = new Matrix; 
  const int width = 6;
  const int height = 3;
  Matrix_init(mat, width, height);
  Matrix_fill(mat, 15);
  *Matrix_at(mat, 1, 0) = 12; 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 6), 12);
  *Matrix_at(mat, 0, 5) = 20; 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 6), 15);
  *Matrix_at(mat, 2, 5) = 2; 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 6), 2);
  delete mat; 
}

//Tests min  value
TEST(test_min_value2){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  const int value = -5;
  const int test = 20;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,test);
  Matrix_fill_border(mat,value);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,0,width),-5);
  delete mat;
}

//tests min value
TEST(test_min_value){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  const int value = 20;
  const int test = 15;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,value);
  Matrix_fill_border(mat,test);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,height-1,0,width),15);
  delete mat;
}
TEST(test_specific_spot){
  Matrix *mat = new Matrix;
  const int height = 3;
  const int width = 5;
  Matrix_init(mat,width,height);
  Matrix_fill(mat,100);
  *Matrix_at(mat,1,2) = 0;
  for(int i=0; i<height;++i){
    for(int j=0; j<width; ++j){
      if(i==1&&j==2){
        ASSERT_EQUAL(*Matrix_at(mat,i,j),0);
      }else{
        ASSERT_EQUAL(*Matrix_at(mat,i,j),100);
      }
    }
  }
  delete mat;
}
// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
