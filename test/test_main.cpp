﻿#include "gtest/gtest.h"
#include "../inc/matrix.h"
#include "../inc/ver.h"
#include "../inc/utils.h"

TEST(ver_test_case, ver_major_test) {
  EXPECT_GE(ver_major(), 1);
}

TEST(ver_test_case, ver_minor_test) {
  EXPECT_GE(ver_minor(), 1);
}

TEST(ver_test_case, ver_patch_test) {
  EXPECT_GE(ver_patch(), 1);
}

TEST(matrix_test_case, default_ctor_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat;
  EXPECT_EQ(mat.size(), 0);
}

TEST(matrix_test_case, at_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat;

  mat[5][101] = 100;
  EXPECT_EQ(mat.size(), 1);
  EXPECT_EQ(mat[5][101], 100);

  mat[5][101] = 0;
  EXPECT_EQ(mat.size(), 0);
  EXPECT_EQ(mat[5][101], 0);
}

TEST(matrix_test_case, copy_ctor_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat1;
  mat1[12][67] = 100;

  mat_t mat2(mat1);
  EXPECT_EQ(mat2.size(), 1);
  EXPECT_EQ(mat2, mat1);
}

TEST(matrix_test_case, move_ctor_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat1;
  mat1[92][1] = 100;
  mat_t mat2(std::forward<decltype(mat1)>(mat1));
  
  EXPECT_EQ(mat2.size(), 1);
  EXPECT_EQ(mat2[92][1], 100);
  EXPECT_EQ(mat1.size(), 0);
  EXPECT_EQ(mat1[92][1], 0);
}

TEST(matrix_test_case, swap_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat1;
  mat1[92][1] = 100;
  mat_t mat2;
  mat2[1][92] = -100;
  std::swap(mat1, mat2);

  EXPECT_EQ(mat2.size(), 1);
  EXPECT_EQ(mat2[92][1], 100);
  EXPECT_EQ(mat1.size(), 1);
  EXPECT_EQ(mat1[1][92], -100);
}

TEST(matrix_test_case, empty_val_test) {
  using mat0_t = mat::matrix<int, 0>;
  mat0_t mat0;
  EXPECT_EQ(mat0[75][31], 0);

  mat0[75][31] = 0;
  EXPECT_EQ(mat0.size(), 0);
  EXPECT_EQ(mat0[75][31], 0);

  using mat1_t = mat::matrix<int, 1>;
  mat1_t mat1;
  EXPECT_EQ(mat1[75][31], 1);

  mat1[75][31] = 1;
  EXPECT_EQ(mat1.size(), 0);
  EXPECT_EQ(mat1[75][31], 1);
}

TEST(matrix_test_case, iter_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat;
  EXPECT_EQ(mat.begin(), mat.end());

  mat[5][75] = 3;
  mat[98][7] = 7;
  mat[8][5]  = 10;
  mat[25][3] = 100;
  mat[6][11] = -100;

  size_t size = 0;
  for(auto it: mat) {
    size_t x;
    size_t y;
    int v;
    std::tie(x, y, v) = it;
    EXPECT_EQ(mat[x][y], v);
    size++;
  }
  EXPECT_EQ(mat.size(), size);

  size = 0;
  for(auto it = mat.begin(); it != mat.end(); ++it) {
    size_t x;
    size_t y;
    int v;
    std::tie(x, y, v) = *it;
    EXPECT_EQ(mat[x][y], v);
    size++;
  }
  EXPECT_EQ(mat.size(), size);
}

TEST(matrix_test_case, canonical_assignment_test) {
  using mat_t = mat::matrix<int, 0>;
  mat_t mat;

  ((mat[78][56] = 231) = 0) = -21;
  EXPECT_EQ(mat.size(), 1);
  EXPECT_EQ(mat[78][56], - 21);
}

TEST(matrix_test_case, matrix_5_dimensions_test) {
  using mat_t = mat::matrix<int, 0, 5>;
  mat_t mat;
  EXPECT_EQ(mat.size(), 0);
  
  mat[1][2][3][4][5] = 10;
  EXPECT_EQ(mat.size(), 1);

  size_t x1, x2, x3, x4, x5;
  int v;
  auto it = mat.begin();
  std::tie(x1, x2, x3, x4, x5, v) = *it;
  EXPECT_EQ(x1, 1);
  EXPECT_EQ(x2, 2);
  EXPECT_EQ(x3, 3);
  EXPECT_EQ(x4, 4);
  EXPECT_EQ(x5, 5);
  EXPECT_EQ(v, 10);
}

TEST(utils_test_case, gen_tuple_test) {
  bool is_same = std::is_same<std::tuple<int>,
                              utils::gen_tuple_t<1, int>::type>::value;
  EXPECT_EQ(is_same, true);
  is_same = std::is_same<std::tuple<int, int, int, int, int>,
                         utils::gen_tuple_t<5, int>::type>::value;
  EXPECT_EQ(is_same, true);
}

TEST(utils_test_case, append_tuple_test) {
  bool is_same = std::is_same<std::tuple<int, bool>,
                              utils::append_tuple_t<std::tuple<int>, bool>::type>::value;
  EXPECT_EQ(is_same, true);
  is_same = std::is_same<std::tuple<int, int, int, int, int, bool>,
                         utils::append_tuple_t<utils::gen_tuple_t<5, int>::type, bool>::type>::value;
  EXPECT_EQ(is_same, true);
}

TEST(utils_test_case, get_subtuple_test) {
  auto tuple = std::make_tuple<int, int, int, int, bool>(1, 2, 3, 4, true);

  auto subtuple = utils::get_subtuple(tuple, std::make_index_sequence<3>{});
  EXPECT_EQ(std::get<0>(subtuple), 1);
  EXPECT_EQ(std::get<1>(subtuple), 2);
  EXPECT_EQ(std::get<2>(subtuple), 3);

  bool is_same = std::is_same<std::tuple<int, int, int>, decltype(subtuple)>::value;

  EXPECT_EQ(is_same, true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
