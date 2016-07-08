#include <gtest/gtest.h>
#include "Vector.hpp"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

class TestingClassForVector
{
    
};

TEST(ObjectCostruction, defaultConstructor)
{
    Vector<int> intVector;
    Vector<std::string> stringVector;
    Vector<float> floatVector;
}

TEST(ObjectCostruction, defaultConstructorWithAllocator)
{
    
}