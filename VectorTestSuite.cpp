#include <gtest/gtest.h>
#include <Allocator.h>
#include "Vector.hpp"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

TEST(ObjectCostruction, defaultConstructor)
{
    Vector<int> intVector;
    Vector<std::string> stringVector;
    Vector<float> floatVector;
}

TEST(ObjectCostruction, defaultConstructorWithAllocator)
{
    Vector<int, Allocator<int>> out(Allocator<int>());
}

template <class T>
void checkVectorSizeAndCapcity(Vector<T>& out, int numberOfElements)
{
    ASSERT_EQ(out.size(), numberOfElements);
    ASSERT_EQ(out.capacity(), numberOfElements);
}

TEST(ObjectCostruction, fillConstructor)
{
    int numberOfElements = 10;
    Vector<int> out(numberOfElements);
    checkVectorSizeAndCapcity(out, numberOfElements);
    for(int i = 0; i < numberOfElements; ++i)
    {
        ASSERT_EQ(out[i], int());
    }
}

TEST(ObjectCostruction, fillWithGivenValuesConstructor)
{
    int numberOfElements = 13;
    double valueOfElements = 7;
    Vector<double> out(numberOfElements, valueOfElements);
    checkVectorSizeAndCapcity(out, numberOfElements);
    for(int i = 0; i < numberOfElements; ++i)
    {
        ASSERT_EQ(out[i], valueOfElements);
    }
}

TEST(ObjectCostruction, rangeConstructor)
{
    
}