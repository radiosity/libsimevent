#include <iostream>
#include <list>
#include <boost/foreach.hpp>

#include "List_Event_List.hpp"

using namespace std;

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

#include <gtest/gtest.h>
#include <vector>

template <class T>
class TE : public Event<T> {

    vector<T> * vec;
    T val;

    public:
        TE(T _time, T _val, vector<T> * _vec) : Event<T>(_time), vec(_vec), val(_val) {

        }

        ~TE() {

        }

        void dispatch() {

            vec->push_back(val);

        }

};

void TestSimple(Event_List<int> * elist) {

	vector<int> * vec = new vector<int>();

	//test simple insertion

	TE<int> * evnt = new TE<int>(1, 10, vec);
	elist->add(evnt);

	elist->tick(1);

	ASSERT_EQ(vec->size(),1);
	ASSERT_EQ(vec->at(0), 10);

	delete vec;

}

void TestMultiple(Event_List<int> * elist) {

    vector<int> * vec = new vector<int>();

    //test multiple events at a single time

    TE<int> * evnt = new TE<int>(1,10,vec);
    elist->add(evnt);
    evnt = new TE<int>(1,20,vec);
    elist->add(evnt);

    elist->tick(1);

    ASSERT_EQ(vec->size(),2);
    ASSERT_EQ(vec->at(0), 10);
    ASSERT_EQ(vec->at(1), 20);

    delete vec;

}

void TestSparse(Event_List<int> * elist) {

	//shouldn't tick if tick invoked with nothing at that time period.

    vector<int> * vec = new vector<int>();

    //test multiple events at a single time

    TE<int> * evnt = new TE<int>(1,10,vec);
    elist->add(evnt);
    evnt = new TE<int>(3,20,vec);
    elist->add(evnt);

    elist->tick(1);

    ASSERT_EQ(vec->size(),1);
    ASSERT_EQ(vec->at(0), 10);

    elist->tick(2);

    //should NOT tick
    ASSERT_EQ(vec->size(),1);
    ASSERT_EQ(vec->at(0), 10);

    elist->tick(3);

    //should tick
    ASSERT_EQ(vec->size(),2);
    ASSERT_EQ(vec->at(0), 10);
    ASSERT_EQ(vec->at(1), 20);

    delete vec;

}

void TestSequential(Event_List<int> * elist) {

    vector<int> * vec = new vector<int>();

    //test sequential events

    TE<int> * evnt = new TE<int>(1,10,vec);
    elist->add(evnt);
    evnt = new TE<int>(2,20,vec);
    elist->add(evnt);

    elist->tick(1);

    ASSERT_EQ(vec->size(),1);
    ASSERT_EQ(vec->at(0), 10);

    elist->tick(2);

    ASSERT_EQ(vec->size(),2);
    ASSERT_EQ(vec->at(1), 20);

    delete vec;

}

void TestReordering(Event_List<int> * elist) {

    vector<int> * vec = new vector<int>();

    //test sequential events

    TE<int> * evnt = new TE<int>(2,20,vec);
    elist->add(evnt);
    evnt = new TE<int>(1,10,vec);
    elist->add(evnt);

    elist->tick(1);

    ASSERT_EQ(vec->size(),1);
    ASSERT_EQ(vec->at(0), 10);

    elist->tick(2);

    ASSERT_EQ(vec->size(),2);
    ASSERT_EQ(vec->at(1), 20);

    delete vec;

}

TEST(Event_List_Test, TestSimple) {

	Event_List<int> * elist = new List_Event_List<int>();
	TestSimple(elist);
	delete elist;

	elist	= new List_Event_List<int,true>();
	TestSimple(elist);
	delete elist;

}

TEST(Event_List_Test, TestMultiple) {

	Event_List<int> * elist = new List_Event_List<int>();
	TestMultiple(elist);
	delete elist;

	elist	= new List_Event_List<int,true>();
	TestMultiple(elist);
	delete elist;

}

TEST(Event_List_Test, TestSparse) {

	Event_List<int> * elist = new List_Event_List<int>();
	TestSparse(elist);
	delete elist;

	elist	= new List_Event_List<int,true>();
	TestSparse(elist);
	delete elist;

}


TEST(Event_List_Test, TestSequential) {

	Event_List<int> * elist = new List_Event_List<int>();
	TestSequential(elist);
	delete elist;

	elist	= new List_Event_List<int,true>();
	TestSequential(elist);
	delete elist;

}

TEST(Event_List_Test, TestReordering) {

	Event_List<int> * elist = new List_Event_List<int>();
	TestReordering(elist);
	delete elist;

	elist	= new List_Event_List<int,true>();
	TestReordering(elist);
	delete elist;

}






