#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <HelperClasses.h>
#include <array>
#include <scoped_allocator>
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

TEST(ObjectCostruction, defaultConstructorWithAddingAllocator)
{
    Vector<int, AddingAllocator<int>> out(AddingAllocator<int>());
}

template <class T>
void checkVectorSizeAndCapcity(T& out, int numberOfElements)
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
    std::array<int, 7> numbers = {3, 4, 5, 6, 2, 91, 113};
    Vector<int> out(numbers.begin(), numbers.end());
    checkVectorSizeAndCapcity(out, numbers.size());
    for(std::size_t i = 0; i < numbers.size(); ++i)
    {
        ASSERT_EQ(out[i], numbers[i]);
    }
}

TEST(ObjectCostruction, rangeConstructorWithAddingAllocator)
{
    std::string str = "lambada";
    Vector<char, AddingAllocator<char>> out(str.begin(), str.end(), AddingAllocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i] + 1);
    }
}

TEST(ObjectCostruction, initializerListConstructor)
{
    std::initializer_list<int> numbers = {3, 4, 5, 6, 2, 91, 113};
    Vector<int> out(numbers);
    checkVectorSizeAndCapcity(out, numbers.size());
    for(std::size_t i = 0; i < numbers.size(); ++i)
    {
        ASSERT_EQ(out[i], *(numbers.begin() + i));
    }
}

TEST(ObjectCostruction, initializerListConstructorWithAddingAllocator)
{
    std::initializer_list<char> str = {'c', 'h', 'a', 'c', 'h', 'a'};
    Vector<char, AddingAllocator<char>> out(std::move(str), AddingAllocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], *(str.begin() + i) + 1);
    }
}

TEST(ObjectCostruction, copyConstructor)
{
    Vector<int> numbers = {3, 4, 5, 6, 2, 91, 113};
    Vector<int> out(numbers);
    checkVectorSizeAndCapcity(out, numbers.size());
    ASSERT_TRUE(out == numbers);
}

TEST(ObjectCostruction, copyConstructorVitchAddingAllocator)
{
    Vector<char, AddingAllocator<char>> str = {'a', 'k', 'u', 'k', 'u'};
    Vector<char, AddingAllocator<char>> out(str, AddingAllocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i] + 1);
    }
}

TEST(ObjectCostruction, moveConstructor)
{
    Vector<int> numbers = {3, 4, 5, 6, 2, 91, 113};
    Vector<int> out(std::move(numbers));
    checkVectorSizeAndCapcity(out, numbers.size());
    for(std::size_t i = 0; i < numbers.size(); ++i)
    {
        ASSERT_EQ(out[i], numbers[i]);
    }
}


TEST(ObjectCostruction, moveConstructorVitchAddingAllocator)
{
    Vector<char, AddingAllocator<char>> str = {'a', 'k', 'u', 'k', 'u'};
    Vector<char, AddingAllocator<char>> out(std::move(str), AddingAllocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i]);
    }
}

class VectorTestSuite : public ::testing::Test 
{
protected:
    VectorTestSuite(): longVectorWithAllocator({3, 0, 13, 24}, std::allocator<int>()),
                       shortVectorWithAllocator({13, 99}, std::allocator<int>())
    {}
    Vector<Cat> longVector = {Cat("Red"), Cat("Jhon"), Cat("Anubis")};
    Vector<Cat> shortVector = {Cat("Fluffy"), Cat("Silly")};
    Vector<int, std::allocator<int>> longVectorWithAllocator;
    Vector<int, std::allocator<int>> shortVectorWithAllocator;
};

TEST_F(VectorTestSuite, copyAssigmentLongerToShorter)
{
    shortVector = longVector;
    ASSERT_TRUE(longVector == shortVector);
}

TEST_F(VectorTestSuite, copyAssigmentShorterToLonger)
{
    longVector = shortVector;
    ASSERT_TRUE(longVector == shortVector);
}

TEST_F(VectorTestSuite, moveAssigmentLongerToShorter)
{
    auto copyOfLongVector(longVector);
    shortVector = std::move(longVector);
//    ASSERT_TRUE(shortVector == copyOfLongVector);
}

TEST_F(VectorTestSuite, moveAssigmentShorterToLonger)
{
//    auto copyOfShortVector(shortVector);
//    longVector = std::move(shortVector);
//    ASSERT_TRUE(longVector == copyOfShortVector);
}