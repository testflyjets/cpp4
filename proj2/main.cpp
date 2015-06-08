/*===========================================================================
 * Project #2 - CSE40478
 *
 * File:    main.cpp
 *===========================================================================*/
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

#include "dlist.h"
using namespace Project2;

#include "UnitTest++.h"

//-----------------------------------------------------------------------------
// Unit tests
//-----------------------------------------------------------------------------
TEST(defaultConstructor)
{
   dlist<double> ls;

   CHECK(ls.size() == 0);
}

TEST(copyConstructor_emptySource)
{
   dlist<short> ls1;
   dlist<short> ls2(ls1);

   CHECK(ls2.size() == 0);
}

TEST(copyConstructor_nonEmptySource)
{
   dlist<short> ls1;
   ls1.push_back(1);
   ls1.push_back(2);
   ls1.push_back(3);
   dlist<short> ls2(ls1);

   CHECK(ls2.size() == 3);
   CHECK(ls2.front() == 1);
   ls2.pop_front();
   CHECK(ls2.front() == 2);
   ls2.pop_front();
   CHECK(ls2.front() == 3);
}

TEST(iteratorRangeConstructor_nonEmptyRange)
{
   string data[] = { "the", "quick", "brown", "fox" };
   dlist<string> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls.size() == 4);
   CHECK(ls.front() == "the");
   ls.pop_front();
   CHECK(ls.front() == "quick");
   ls.pop_front();
   CHECK(ls.front() == "brown");
   ls.pop_front();
   CHECK(ls.front() == "fox");
}

TEST(iteratorRangeConstructor_emptyRange)
{
   string data[] = { "the", "quick", "brown", "fox" };
   dlist<string> ls(data, data);

   CHECK(ls.size() == 0);
}

TEST(iteratorRangeConstructor_fromVector)
{
	string data[] = { "the", "quick", "brown", "fox" };
	vector<string> v(data, data + sizeof(data) / sizeof(*data));
	dlist<string> ls(v.begin(), v.end());

	CHECK(equal(ls.begin(), ls.end(), v.begin()));
}

TEST(destructor_empty)
{
   dlist<std::string> *pLs = new dlist<std::string>();
   try
   {
      delete pLs;
   }
   catch (...)
   {
      CHECK(false);  // Destructor shouldn't throw
   }
}

TEST(destructor_nonEmpty)
{
   string data[] = { "the", "quick", "brown", "fox" };
   dlist<string> *pLs = new dlist<string>(data,
                                          data + sizeof(data) / sizeof(*data));
   try
   {
      delete pLs;
   }
   catch (...)
   {
      CHECK(false);  // Destructor shouldn't throw
   }
}

TEST(copyAssignmentOperator_emptySource)
{
   dlist<short> ls1;
   dlist<short> ls2;
   ls2 = ls1;

   CHECK(ls2.size() == 0);
}

TEST(copyAssignmentOperator_nonEmptySource)
{
   dlist<short> ls1;
   ls1.push_back(1);
   ls1.push_back(2);
   ls1.push_back(3);
   dlist<short> ls2;
   ls2 = ls1;

   CHECK(ls2.size() == 3);
   CHECK(ls2.front() == 1);
   ls2.pop_front();
   CHECK(ls2.front() == 2);
   ls2.pop_front();
   CHECK(ls2.front() == 3);
}

TEST(empty_empty)
{
   dlist<short> ls;
   
   CHECK(ls.empty());
}

TEST(empty_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(!ls.empty());
}

TEST(size_empty)
{
   dlist<short> ls;
   
   CHECK(ls.size() == 0);
}

TEST(size_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls.size() == 3);
}

TEST(front)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls.front() == 1);
}

TEST(back)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls.back() == 3);
}

TEST(pushFront_empty)
{
   dlist<short> ls;
   ls.push_front(1);

   CHECK(ls.size() == 1);
   CHECK(ls.front() == 1);
}

TEST(pushFront_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));
   ls.push_front(4);

   CHECK(ls.size() == 4);
   CHECK(ls.front() == 4);
}

TEST(popFront)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));
   ls.pop_front();

   CHECK(ls.size() == 2);
   CHECK(ls.front() == 2);
}

TEST(pushBack_empty)
{
   dlist<short> ls;
   ls.push_back(1);

   CHECK(ls.size() == 1);
   CHECK(ls.back() == 1);
}

TEST(pushBack_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));
   ls.push_back(4);

   CHECK(ls.size() == 4);
   CHECK(ls.back() == 4);
}

TEST(pop_back)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));
   ls.pop_back();

   CHECK(ls.size() == 2);
   CHECK(ls.back() == 2);
}

TEST(insert_empty_begin)
{
   dlist<short> ls;
   ls.insert(ls.begin(), 1);

   CHECK(ls.size() == 1);
   CHECK(ls.front() == 1);
}

TEST(insert_empty_end)
{
   dlist<short> ls;
   ls.insert(ls.end(), 1);

   CHECK(ls.size() == 1);
   CHECK(ls.front() == 1);
}

TEST(insert_nonEmpty)
{
   const short EXPECTED_DATA[] = { 4, 1, 5, 2, 6, 3 };
   short data[] = { 4, 1, 5, 2, 6, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls.size() == 6);
   CHECK(equal(ls.begin(), ls.end(), EXPECTED_DATA));
}

TEST(erase)
{
   const short EXPECTED_DATA[] = { 1, 3 };
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   dlist<short>::iterator i = ++ls.begin();
   i = ls.erase(i);

   CHECK(ls.size() == 2);
   CHECK(*i = 3);
   CHECK(equal(ls.begin(), ls.end(), EXPECTED_DATA));
}

TEST(operatorEquals_equal)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls1 == ls2);
}

TEST(operatorEquals_notEqual)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data) - 1);

   CHECK(!(ls1 == ls2));
}

TEST(operatorNotEqual_equal)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(!(ls1 != ls2));
}

TEST(operatorNotEqual_notEqual)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data) - 1);

   CHECK(ls1 != ls2);
}

TEST(operatorLessThan_lessThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data) - 1);
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls1 < ls2);
}

TEST(operatorLessThan_notLessThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(!(ls1 < ls2));
}

TEST(operatorLessThanOrEquals_lessThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data) - 1);
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls1 <= ls2);
}

TEST(operatorLessThanOrEquals_equals)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls1 <= ls2);
}

TEST(operatorLessThanOrEquals_greaterThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data) - 1);

   CHECK(!(ls1 <= ls2));
}

TEST(operatorGreaterThan_greaterThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data) - 1);

   CHECK(ls1 > ls2);
}

TEST(operatorGreaterThan_notGreaterThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(!(ls1 > ls2));
}

TEST(operatorGreaterThanOrEquals_lessThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data) - 1);
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(!(ls1 >= ls2));
}

TEST(operatorGreaterThanOrEquals_equals)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data));

   CHECK(ls1 >= ls2);
}

TEST(operatorGreaterThanOrEquals_greaterThan)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls1(data, data + sizeof(data) / sizeof(*data));
   dlist<short> ls2(data, data + sizeof(data) / sizeof(*data) - 1);

   CHECK(ls1 >= ls2);
}

TEST(begin_empty)
{
   dlist<short> ls;

   CHECK(ls.begin() == ls.end());
}

TEST(begin_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(*ls.begin() == 1);
}

TEST(end_empty)
{
   dlist<short> ls;

   CHECK(ls.end() == ls.begin());
}

TEST(end_nonEmpty)
{
   short data[] = { 1, 2, 3 };
   dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

   CHECK(*(--ls.end()) == 3);
}

TEST(beginEnd_vectorFromDlist)
{
	string data[] = { "the", "quick", "brown", "fox" };
	dlist<string> ls(data, data + sizeof(data) / sizeof(*data));
	vector<string> v(ls.begin(), ls.end());

	CHECK(equal(v.begin(), v.end(), ls.begin()));
}

static bool isEven(short s)
{
	return s % 2 == 0;
}

TEST(copyIf)
{
	// Source data
	short sourceData[] = { 1, 2, 3, 4, 5, 6 };
	dlist<short> sourceLs(
		sourceData,
		sourceData + sizeof(sourceData) / sizeof(*sourceData));

	// Copy to destination
	dlist<short> result;
	copy_if(sourceLs.begin(), sourceLs.end(), back_inserter(result), isEven);

	// Verify result contains filtered data
	short expectedData[] = { 2, 4, 6 };
	dlist<short> expected(
		expectedData,
		expectedData + sizeof(expectedData) / sizeof(*expectedData));

	CHECK(equal(result.begin(), result.end(), expected.begin()));
}

TEST(find)
{
	// Source data
	short data[] = { 1, 2, 3, 4, 5, 6 };
	dlist<short> ls(data, data + sizeof(data) / sizeof(*data));

	// Find the 2
	dlist<short>::iterator i = find(ls.begin(), ls.end(), 2);

	// Verify result
	CHECK(i != ls.end());
	dlist<short>::iterator pos(ls.begin());
	CHECK(i == ++pos);
}

TEST(accumulate)
{
   const int EXPECTED_RESULT = 55;

   dlist<int> dl;
   dlist<int>::iterator i;
   i = dl.insert(dl.begin(), 5);
   i = dl.insert(i, 4);
   i = dl.insert(i, 3);
   i = dl.insert(i, 2);
   i = dl.insert(i, 1);
   dl.insert(dl.end(), 6);
   dl.insert(dl.end(), 7);
   dl.insert(dl.end(), 8);
   dl.insert(dl.end(), 9);
   dl.insert(dl.end(), 10);

   CHECK(EXPECTED_RESULT == accumulate(dl.begin(), dl.end(), 0));
}

void reverseString(string &s)
{
   reverse(s.begin(), s.end());
}

TEST(for_each)
{
   string inputData[] = { "the", "quick", "brown", "fox" };
   dlist<string> dlInput(inputData, inputData + 4);
   string resultData[] = { "eht", "kciuq", "nworb", "xof" };
   dlist<string> dlResult(resultData, resultData + 4);

   for_each(dlInput.begin(), dlInput.end(), reverseString);

   CHECK(dlResult == dlInput);
}

int square(int i)
{
   return i * i;
}

TEST(transform)
{
   int inputData[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   dlist<int> dlInput(inputData, inputData + 10);
   int resultData[] = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
   deque<int> dqResult(resultData, resultData + 10);

   deque<int> dqTransformed;
   transform(dlInput.begin(),
             dlInput.end(),
             back_inserter(dqTransformed),
             square);

   CHECK(dqResult == dqTransformed);
}

int main()
{
   return UnitTest::RunAllTests();
}