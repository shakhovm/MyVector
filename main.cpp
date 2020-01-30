#include <gtest/gtest.h>
#include <string>
#include "MyVector.h"
using namespace std;
class VectorFixture : public :: testing::Test {

};


TEST_F(VectorFixture, init) {
    MyVector<int> v;

    v.reserve(2);
    EXPECT_EQ(v.capacity(), 2);
    MyVector<string> v1(2);
    EXPECT_EQ(v1.capacity(), 4);
    EXPECT_EQ(v1.size(), 2);
    EXPECT_EQ(v1.front(), "");
    EXPECT_EQ(v1[1], "");

    v1[0] = "hi";

    EXPECT_EQ(v1[0], "hi");
    MyVector<int> v2(2, 7);
    EXPECT_EQ(v2[1], 7);
    MyVector<int> v3(v2);
    EXPECT_EQ(v3, v2);
    MyVector<int> v4;
    v4 = v3;
    EXPECT_EQ(v3, v4);
}

TEST_F(VectorFixture, vectors) {
    MyVector<MyVector<int>> v;

    for (int i = 0; i < 10; ++i) {
        v.emplace_back(4, i);
    }


    EXPECT_EQ(v[4][1], 4);
    v.insert(v.begin() + 3, MyVector<int>(2, 1));
    EXPECT_EQ((*(v.begin() + 3)).size(), 2);
}

TEST_F(VectorFixture, pushes)
{
    MyVector<int> v;
    for(int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    v.insert(v.begin() + 4, 120);
    EXPECT_EQ(*(v.begin() + 4), 120);
    MyVector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
    v.insert(v.begin(), v1.begin(), v1.end());



    EXPECT_EQ(v.size(), 18);

    v.insert(v.begin() + 3, {11, 11, 12, 12});
    EXPECT_EQ(v.size(), 22);
    EXPECT_EQ(v[5], 12);
    v.erase(v.begin() + 4);
    EXPECT_EQ(v[4], 12);

    my_transform(v.begin(), v.end(), v.begin(), [](int x){return x*2;});
    EXPECT_EQ(v[4], 24);

}

TEST_F(VectorFixture, clear)
{
    MyVector<int> v;
    for(int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    v.clear();
    for(int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    EXPECT_EQ(v.size(), 10);
    EXPECT_EQ(v.front(), 0);
    EXPECT_EQ(v.back(), 9);
    v.pop_back();
    EXPECT_EQ(v.size(), 9);
}

TEST_F(VectorFixture, erase)
{
    auto *v = new MyVector<int>();
    for(int i = 0; i < 10; ++i)
    {
        v->push_back(i);
    }

    v->erase(v->begin() + 5);
    EXPECT_EQ(v->size(), 9);

    EXPECT_EQ(v->operator[](5), 6);
    delete v;

}

TEST_F(VectorFixture, comparing)
{
    MyVector<int> vector1 = {1, 2, 3, 4, 5, 6, 7, 8};
    MyVector<int> vector2(vector1);
    EXPECT_EQ(vector1, vector2);
    EXPECT_GE(vector1, vector2);
    EXPECT_LE(vector1, vector2);
    vector2.push_back(9);
    EXPECT_NE(vector1, vector2);
    EXPECT_GT(vector2, vector1);
    EXPECT_GE(vector2, vector1);
    vector2[0] = 0;

    EXPECT_LT(vector2, vector1);
    EXPECT_LE(vector2, vector1);
}


TEST_F(VectorFixture, resize)
{
    MyVector<int> vector1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector1.resize(30, 10);
    EXPECT_EQ(vector1.size(), 30);
    EXPECT_EQ(vector1.capacity(), 60);
    vector1.resize(10, 0);
    EXPECT_EQ(vector1.size(), 10);
    EXPECT_EQ(vector1.capacity(), 60);

    vector1.shrink_to_fit();
    EXPECT_EQ(vector1.capacity(), vector1.size());
}


