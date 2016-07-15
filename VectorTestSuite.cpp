#include <gtest/gtest.h>
#include <gmock/gmock.h>
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

TEST(ObjectCostruction, defaultConstructorWithGivenAllocator)
{
    Vector<int, std::allocator<int>> out(std::allocator<int>());
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

TEST(ObjectCostruction, rangeConstructorWithGivenAllocator)
{
    std::string str = "lambada";
    Vector<char, std::allocator<char>> out(str.begin(), str.end(), std::allocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i]);
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

TEST(ObjectCostruction, initializerListConstructorWithGivenAllocator)
{
    std::initializer_list<char> str = {'c', 'h', 'a', 'c', 'h', 'a'};
    Vector<char, std::allocator<char>> out(std::move(str), std::allocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], *(str.begin() + i));
    }
}

TEST(ObjectCostruction, copyConstructor)
{
    Vector<int> numbers = {3, 4, 5, 6, 2, 91, 113};
    Vector<int> out(numbers);
    checkVectorSizeAndCapcity(out, numbers.size());
    ASSERT_TRUE(out == numbers);
}

TEST(ObjectCostruction, copyConstructorVitchGivenAllocator)
{
    Vector<char, std::allocator<char>> str = {'a', 'k', 'u', 'k', 'u'};
    Vector<char, std::allocator<char>> out(str, std::allocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i]);
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


TEST(ObjectCostruction, moveConstructorVitchGivenAllocator)
{
    Vector<char, std::allocator<char>> str = {'a', 'k', 'u', 'k', 'u'};
    Vector<char, std::allocator<char>> out(std::move(str), std::allocator<char>());
    checkVectorSizeAndCapcity(out, str.size());
    for(std::size_t i = 0; i < str.size(); ++i)
    {
        ASSERT_EQ(out[i], str[i]);
    }
}

TEST(Allocator, getDefaultAllocator)
{
    Vector<int> vec;
    ASSERT_EQ(vec.get_allocator(), std::allocator<int>());
}

TEST(Allocator, getGivenAllocator)
{
    const auto& alloc = std::allocator<int>();
    Vector<int, std::allocator<int>> vec(alloc);
    ASSERT_TRUE(vec.get_allocator() == std::allocator<int>());
}

struct Cat
{
    using value_type = Cat;
    Cat(std::string name) :name(name) {}
    Cat(const Cat& cat): legsAmoutn(cat.legsAmoutn), name(cat.name) {}
    Cat(Cat&& cat): legsAmoutn(std::move(cat.legsAmoutn)), name(std::move(cat.name)) {}
    ~Cat(){}
    
    Cat& operator=(Cat& cat)
    {
        name = cat.name;
        legsAmoutn = cat.legsAmoutn;
        return *this;
    }
    
    Cat& operator=(Cat&& cat)
    {
        name = std::move(cat.name);
        legsAmoutn = std::move(cat.legsAmoutn);
        return *this;
    }
    
    int legsAmoutn = 4;
    std::string name;
};

bool operator==(const Cat& lhs, const Cat& rhs)
{
    return lhs.legsAmoutn == rhs.legsAmoutn && lhs.name == rhs.name;
}

TEST(EmplaceBack, emplaceCat)
{
    Vector<Cat> emplacedCat;
    std::string name = "Dog";
    emplacedCat.emplace_back(name);
    Vector<Cat> createdCat = {Cat(name)};
    ASSERT_TRUE(emplacedCat == createdCat);
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

TEST_F(VectorTestSuite, pushBackTrivialType)
{
    Vector<int> emptyVector;
    for(std::size_t i = 0; i < longVectorWithAllocator.size(); ++i)
    {
        emptyVector.push_back(longVectorWithAllocator[i]);
    }
    
    ASSERT_TRUE(emptyVector == longVectorWithAllocator);
}

TEST_F(VectorTestSuite, pushBackCustomType)
{
    Vector<Cat> emptyVector;
    for(std::size_t i = 0; i < longVector.size(); ++i)
    {
        emptyVector.push_back(longVector[i]);
    }
    
    ASSERT_TRUE(emptyVector == longVector);
}

TEST_F(VectorTestSuite, clearTrivialType)
{
    Vector<int> emptyVector;
    longVectorWithAllocator.clear();
    ASSERT_TRUE(emptyVector == longVectorWithAllocator);
}

TEST_F(VectorTestSuite, clearCustomType)
{
    Vector<Cat> emptyVector;
    shortVector.clear();
    ASSERT_TRUE(emptyVector == shortVector);
}

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

TEST_F(VectorTestSuite, copyAssigmentLongerToShorterTrivialType)
{
    shortVectorWithAllocator = longVectorWithAllocator;
    ASSERT_TRUE(longVectorWithAllocator == shortVectorWithAllocator);
}

TEST_F(VectorTestSuite, copyAssigmentShorterToLongerTrivialType)
{
    longVectorWithAllocator = shortVectorWithAllocator;
    ASSERT_TRUE(longVectorWithAllocator == shortVectorWithAllocator);
}

TEST_F(VectorTestSuite, moveAssigmentLongerToShorter)
{
    auto copyOfLongVector(longVector);
    shortVector = std::move(longVector);
    ASSERT_TRUE(shortVector == copyOfLongVector);
    ASSERT_EQ(longVector.size(), 0);
}

TEST_F(VectorTestSuite, moveAssigmentShorterToLonger)
{
    auto copyOfShortVector(shortVector);
    longVector = std::move(shortVector);
    ASSERT_TRUE(longVector == copyOfShortVector);
    ASSERT_EQ(shortVector.size(), 0);
}

TEST_F(VectorTestSuite, moveAssigmentLongerToShorterTrivialType)
{
    auto copyOfLongVector(longVectorWithAllocator);
    shortVectorWithAllocator = std::move(longVectorWithAllocator);
    ASSERT_TRUE(shortVectorWithAllocator == copyOfLongVector);
    ASSERT_EQ(longVectorWithAllocator.size(), 0);
}

TEST_F(VectorTestSuite, moveAssigmentShorterToLongerTrivialType)
{
    auto copyOfShortVector(shortVectorWithAllocator);
    longVectorWithAllocator = std::move(shortVectorWithAllocator);
    ASSERT_TRUE(longVectorWithAllocator == copyOfShortVector);
    ASSERT_EQ(shortVectorWithAllocator.size(), 0);
}

TEST_F(VectorTestSuite, assignFromInitializerList)
{
    shortVector = {Cat("Red"), Cat("Jhon"), Cat("Anubis")};
    ASSERT_TRUE(shortVector == longVector);
}

TEST_F(VectorTestSuite, assignFromInitializerListTrivialType)
{
    longVectorWithAllocator = {13, 99};
    ASSERT_TRUE(shortVectorWithAllocator == longVectorWithAllocator);
}