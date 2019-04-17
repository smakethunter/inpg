#include "gtest/gtest.h"
#include "matlab.hpp"
using namespace Matlab;
TEST(MatlabVectorTest, Tworzenie_z_rozmiaru) {
    Vector<int> v(2U);
    ASSERT_EQ(v.size(), 2U);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
}

TEST(MatlabVectorTest, Tworzenie_z_innego_wektora) {
    std::vector<int> vs{3, 6};
    Vector v(vs);

    ASSERT_EQ(v.size(), 2U);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 6);
}

TEST(MatlabVectorTest, norm) {
    std::vector<int> vs{1, 2, 2};
    Vector v(vs);

    EXPECT_EQ(v.norm(), 3);
}

TEST(MatlabVectorTest, add) {
    std::vector<int> vs1{4, 2};
    Vector<int> v1(vs1);
    std::vector<int> vs2{1, 3};
    Vector<int> v2(vs2);

    Vector<int> v_sum = add_vectors(v1, v2);

    ASSERT_EQ(v_sum.size(), 2U);
    EXPECT_EQ(v_sum[0], 5);
    EXPECT_EQ(v_sum[1], 5);
}
TEST(MatlabVectorTest, toString) {
    Vector<int> v(std::vector<int>{1, 2});

    std::string str = to_string(v);

    EXPECT_EQ(str, "[ 1, 2 ]");
}
TEST(MatlabVectorAuxTest,exceptionCatchingWhenAddingVectorsOfSameSizes)
{

    std::vector<int> vs1{4, 2};
    Vector<int> v1(vs1);
    std::vector<int> vs2{1, 3};
    Vector<int> v2(vs2);

    std::string sum=was_exception_raised_when_adding_vectors(v1,v2);
    EXPECT_EQ(sum,"");


}
TEST(MatlabVectorAuxTest,exceptionCatchingWhenAddingVectorsOfDifferentSizes)
{

    std::vector<int> vs1{4, 2};
    Vector v1(vs1);
    std::vector<int> vs2{1, 3,3 };
    Vector v2(vs2);

    std::string sum = was_exception_raised_when_adding_vectors(v1,v2);
    EXPECT_EQ(sum,"Different size of vectors: (2 and 3)");

}
