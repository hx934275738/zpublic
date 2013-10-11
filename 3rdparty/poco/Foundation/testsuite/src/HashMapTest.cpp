//
// HashMapTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/HashMapTest.cpp#2 $
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "HashMapTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/HashMap.h"
#include "Poco/Exception.h"
#include <map>


using Poco::HashMap;


HashMapTest::HashMapTest(const std::string& name): CppUnit::TestCase(name)
{
}


HashMapTest::~HashMapTest()
{
}


void HashMapTest::testInsert()
{
	const int N = 1000;

	typedef HashMap<int, int> IntMap;
	IntMap hm;
	
	assert (hm.empty());
	
	for (int i = 0; i < N; ++i)
	{
		std::pair<IntMap::Iterator, bool> res = hm.insert(IntMap::ValueType(i, i*2));
		assert (res.first->first == i);
		assert (res.first->second == i*2);
		assert (res.second);
		IntMap::Iterator it = hm.find(i);
		assert (it != hm.end());
		assert (it->first == i);
		assert (it->second == i*2);
		assert (hm.count(i) == 1);
		assert (hm.size() == i + 1);
	}		
	
	assert (!hm.empty());
	
	for (int i = 0; i < N; ++i)
	{
		IntMap::Iterator it = hm.find(i);
		assert (it != hm.end());
		assert (it->first == i);
		assert (it->second == i*2);
	}
	
	for (int i = 0; i < N; ++i)
	{
		std::pair<IntMap::Iterator, bool> res = hm.insert(IntMap::ValueType(i, 0));
		assert (res.first->first == i);
		assert (res.first->second == i*2);
		assert (!res.second);
	}		
}


void HashMapTest::testErase()
{
	const int N = 1000;

	typedef HashMap<int, int> IntMap;
	IntMap hm;

	for (int i = 0; i < N; ++i)
	{
		hm.insert(IntMap::ValueType(i, i*2));
	}
	assert (hm.size() == N);
	
	for (int i = 0; i < N; i += 2)
	{
		hm.erase(i);
		IntMap::Iterator it = hm.find(i);
		assert (it == hm.end());
	}
	assert (hm.size() == N/2);
	
	for (int i = 0; i < N; i += 2)
	{
		IntMap::Iterator it = hm.find(i);
		assert (it == hm.end());
	}
	
	for (int i = 1; i < N; i += 2)
	{
		IntMap::Iterator it = hm.find(i);
		assert (it != hm.end());
		assert (*it == i);
	}

	for (int i = 0; i < N; i += 2)
	{
		hm.insert(IntMap::ValueType(i, i*2));
	}
	
	for (int i = 0; i < N; ++i)
	{
		IntMap::Iterator it = hm.find(i);
		assert (it != hm.end());
		assert (it->first == i);
		assert (it->second == i*2);		
	}
}


void HashMapTest::testIterator()
{
	const int N = 1000;

	typedef HashMap<int, int> IntMap;
	IntMap hm;

	for (int i = 0; i < N; ++i)
	{
		hm.insert(IntMap::ValueType(i, i*2));
	}
	
	std::map<int, int> values;
	IntMap::Iterator it = hm.begin();
	while (it != hm.end())
	{
		assert (values.find(it->first) == values.end());
		values[it->first] = it->second;
		++it;
	}
	
	assert (values.size() == N);
}


void HashMapTest::testConstIterator()
{
	const int N = 1000;

	typedef HashMap<int, int> IntMap;
	IntMap hm;

	for (int i = 0; i < N; ++i)
	{
		hm.insert(IntMap::ValueType(i, i*2));
	}
	
	std::map<int, int> values;
	IntMap::ConstIterator it = hm.begin();
	while (it != hm.end())
	{
		assert (values.find(it->first) == values.end());
		values[it->first] = it->second;
		++it;
	}
	
	assert (values.size() == N);
}


void HashMapTest::testIndex()
{
	typedef HashMap<int, int> IntMap;
	IntMap hm;

	hm[1] = 2;
	hm[2] = 4;
	hm[3] = 6;
	
	assert (hm.size() == 3);
	assert (hm[1] == 2);
	assert (hm[2] == 4);
	assert (hm[3] == 6);
	
	try
	{
		const IntMap& im = hm;
		int x = im[4];
		fail("no such key - must throw");
	}
	catch (Poco::NotFoundException&)
	{
	}
}


void HashMapTest::setUp()
{
}


void HashMapTest::tearDown()
{
}


CppUnit::Test* HashMapTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("HashMapTest");

	CppUnit_addTest(pSuite, HashMapTest, testInsert);
	CppUnit_addTest(pSuite, HashMapTest, testErase);
	CppUnit_addTest(pSuite, HashMapTest, testIterator);
	CppUnit_addTest(pSuite, HashMapTest, testConstIterator);
	CppUnit_addTest(pSuite, HashMapTest, testIndex);

	return pSuite;
}
