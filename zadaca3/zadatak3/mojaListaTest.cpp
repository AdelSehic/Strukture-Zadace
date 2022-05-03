#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
// #include <list>
#include "lista.hpp"

#include <initializer_list>

// template<typename T>
// using list = std::list<T>;

TEST_CASE("Expects to construct empty array") {
  list<int> list;
  CHECK_EQ(list.size(), 0);
}

TEST_CASE("Expects to initialize list<int> using initializer_list") {
  list<int> list{1, 2, 3, 4, 5, 0, -1, -2, -3, -4, -5};
  CHECK_EQ(list.size(), 11);
  auto it = list.begin();
  for (auto i = 1; i <= 5; ++i)
    CHECK_EQ(*(it++), i);
}

TEST_CASE("Expects to have a proper copy constructor") {
  list<int> list1{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  list<int> list2 = list1;
  CHECK_EQ(list1.size(), 10);
  CHECK_EQ(list2.size(), 10);
  auto it1 = list1.begin();
  auto it2 = list2.begin();
  for (auto i = 9; i >= 0; --i) {
    CHECK_EQ(*(it1++), i + 1);
    CHECK_EQ(*(it2++), i + 1);
  }
  it1 = list1.begin();
  it2 = list2.begin();
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&(*it1), &(*it2));
}

TEST_CASE("Expects to have a proper move constructor") {
  list<int> list1{1, 3, 5, 7, 9};
  list<int> list2 = std::move(list1);
  CHECK_EQ(list2.size(), 5);
  auto it = list2.begin();
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(*(it++), 2 * i + 1);
  }
  CHECK_EQ(list1.size(), 0);
}


TEST_CASE("Expects to have a proper copy operator=") {
  list<int> list1{0, 2, 4, 6, 8};
  list<int> list2{1, 3, 5, 7, 9, 12, 15};
  list2 = list1;
  // Did you replace the size?
  CHECK_EQ(list2.size(), 5);
  auto it1=list1.begin();
  auto it2=list2.begin();
  for (auto i = 0; i < 5; ++i) {
    CHECK_EQ(*(it1++), 2 * i);
    CHECK_EQ(*(it2++), 2 * i);
  }
  it1=list1.begin();
  it2=list2.begin();
  // check that zero elements have different addresses, that's the only way we
  // know copy is done properly
  CHECK_NE(&(*it1), &(*it2));
}

TEST_CASE("Expects to be able to append copy operator=") {
  list<int> list1{0, 2, 4, 6, 8};
  list<int> list2{1, 3, 5, 7, 9};
  list<int> list3{-5, -4, -3, -2, -1, 0};
  list1 = list2 = list3;
  CHECK_EQ(list1.size(), 6);
  CHECK_EQ(list2.size(), 6);
  auto it1=list1.begin();
  auto it2=list2.begin();
  auto it3=list3.begin();

  for (auto i = 0; i < 6; ++i) {
    CHECK_EQ(*(it1++), i - 5);
    CHECK_EQ(*(it2++), i - 5);
    CHECK_EQ(*(it3++), i - 5);
  }
}

TEST_CASE("Expects to have a proper move operator=") {
  list<int> list1{0, 2, 4, 6};
  list<int> list2{1, 3, 5, 7, 9};
  list2 = std::move(list1);
  CHECK_EQ(list1.size(), 0);
  auto it = list2.begin();
  for (auto i = 0; i < 4; ++i) {
    CHECK_EQ(*it, 2 * i);
    it++;
  }
  CHECK_EQ(list2.size(), 4);
}

TEST_CASE("Expects to be able to append move operator=") {
  list<int> list1{0, 2, 4, 6, 8};
  list<int> list2{1, 3, 5, 7, 9};
  list<int> list3{-5, -4, -3, -2, -1, 0};
  list1 = list2 = std::move(list3);
  CHECK_EQ(list1.size(), 6);
  CHECK_EQ(list2.size(), 6);
  CHECK_EQ(list3.size(), 0);
  int i = -5;
  for(auto it = list1.begin();it!=list1.end();++it)
  {
    CHECK_EQ(*it,i++);
  }
  i = -5;
  for(auto it = list2.begin();it!=list2.end();++it)
  {
    CHECK_EQ(*it,i++);
  }
}

TEST_CASE("Expects pop_back(), front() and back() to be implemented") {
  list<int> list1{1, 2, 3};
  CHECK_EQ(list1.back(), 3);
  CHECK_EQ(list1.front(), 1);
  list1.pop_back();
  CHECK_EQ(list1.back(), 2);
  CHECK_EQ(list1.front(), 1);
  list1.pop_back();
  CHECK_EQ(list1.back(), 1);
  CHECK_EQ(list1.front(), 1);
}

// TEST_CASE("Expects operator== and operator!= to be implemented") {
//   list<int> list1{4, 5, 1, 2, 3, 7, 6};
//   list<int> list2{4, 5, 1, 2, 3, 7, 6};
//   CHECK_EQ(list1, list2);
//   list1.pop_back();
//   CHECK_NE(list1, list2);
// }

// Not implemented in std but you can try implementing it
TEST_CASE("Expects find to be implemented") {
  list<int> list1{4, 5, 1, 2, 3, 7, 6};
  auto it = list1.find(1);
  CHECK_EQ(*it,1);
  it = list1.find(10);
  CHECK_EQ(it,list1.end());
}


TEST_CASE("Expects insert and erase to be implemented") {
  list<int> list1{1,3,5};
  auto it = list1.begin();
  list1.erase(it);
  it = list1.begin();
  list1.insert(it,2);
  it = list1.begin();
  list1.insert(it,1);
  it = list1.begin();
  it++;
  it++;
  it++;
  list1.insert(it,4);
  auto it1=list1.begin();
  for (auto i = 1; i < 6; ++i) {
    CHECK_EQ(*(it1++), i);
  }
}

TEST_CASE("Expects push_front, push_back, pop_front, pop_back to be implemented") {
  list<int> list1{1};
  list1.push_front(0);
  list1.push_back(2);
  list1.pop_front();
  list1.pop_back();
  CHECK_EQ(list1.size(),1);
  CHECK_EQ(*(list1.begin()),1);
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 10000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 10000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}

// CHALLENGE
// If you can make these tests finish in less than a minute each, you've done a
// great job

TEST_CASE("Expects to be able to accommodate 100000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 100000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 1000000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 1000000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 10000000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 10000000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}

TEST_CASE("Expects to be able to accommodate 100000000 number") {
  list<int> list1;
  unsigned long long i = 0;
  while (i < 100000000) {
    list1.push_back(++i);
    CHECK_EQ(list1.size(), i);
  }
}
