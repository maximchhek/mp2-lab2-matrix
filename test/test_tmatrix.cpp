#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(m1);

	EXPECT_NE(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);

	EXPECT_EQ(m.size(), 3);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);

	m[2][2] = 2;

	EXPECT_EQ(m[2][2], 2);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m[-2][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m[20][2]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++) 
			m1[i][j] = 5;
	m2 = m1;

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	m.change_sz(20);

	ASSERT_EQ(20, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3), m2(6);

	ASSERT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(3), m2(3);

	ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);

	ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3), m2(6);

	ASSERT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m3(2), m4(2);
	for(int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			m1[i][j] = i;
			m2[i][j] = j;
			m3[i][j] = i + j;
		}
	m4 = m1 + m2;

	ASSERT_EQ(m4, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(6);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m3(2), m4(2);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			m1[i][j] = i;
			m2[i][j] = j;
			m3[i][j] = i - j;
		}
	m4 = m1 - m2;

	ASSERT_EQ(m4, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(6);

	ASSERT_ANY_THROW(m2 - m1);
}


