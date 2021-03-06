/*
Copyright (c) 2013, Richard Martin
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Richard Martin nor the
      names of its contributors may be used to endorse or promote products
      derived from this softwarwe without specwific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL RICHARD MARTIN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include <iostream>

#define BOOST_TEST_MAIN 
#include <boost/test/included/unit_test.hpp>

#include "BaseEvent.hpp"

using std::cout;
using std::endl; 
using namespace libsim;

//Declare a simptle dummy subclass 
template <class T>
class TestEvent : public BaseEvent<T>
{
public:
	TestEvent(T _time) : BaseEvent<T>(_time) {};
	~TestEvent() {};
	void dispatch() { }
};

BOOST_AUTO_TEST_CASE(event_test_get) {
	
	auto evnt = TestEvent<int>(0);

	BOOST_CHECK_EQUAL(evnt.get_time(),  0);
	
}

BOOST_AUTO_TEST_CASE(event_test_less_than) {

	auto event1 = TestEvent<int>(0);
	auto event2 = TestEvent<int>(1);

	BOOST_CHECK(event1 != event2);
	BOOST_CHECK(event1 < event2);
	BOOST_CHECK(!(event2 < event1));

}

BOOST_AUTO_TEST_CASE(event_test_greater_than) {

	auto event1 = TestEvent<int>(1);
	auto event2 = TestEvent<int>(0);

	BOOST_CHECK(event1 != event2);
	BOOST_CHECK(event1 > event2);
	BOOST_CHECK(!(event2 > event1));

}

BOOST_AUTO_TEST_CASE(event_test_equals) {

	auto event1 = TestEvent<int>(1);
	auto event2 = TestEvent<int>(1);

	BOOST_CHECK(event1 == event2);
	BOOST_CHECK(!(event1 > event2));
	BOOST_CHECK(!(event2 > event1));	

}

BOOST_AUTO_TEST_CASE(event_test_copy) {
	
	auto event1 = TestEvent<int>(1);
	auto event2 = event1; 
	
	BOOST_CHECK(event1 == event2);
	BOOST_CHECK(!(event1 > event2));
	BOOST_CHECK(!(event2 > event1));	
	
}

#include <utility>

#include "ClosureEvent.hpp"

using std::function;

BOOST_AUTO_TEST_CASE(closure_test_get) {
	
	function<void()> func = [](){};

	auto evnt = ClosureEvent<int>(func, 0);

	BOOST_CHECK_EQUAL(evnt.get_time(),  0);
	
}

BOOST_AUTO_TEST_CASE(closure_test_less_than) {
	
	function<void()> func = [](){};

	auto event1 = ClosureEvent<int>(func, 0);
	auto event2 = ClosureEvent<int>(func, 1);

	BOOST_CHECK(event1 < event2);

}

BOOST_AUTO_TEST_CASE(closure_test_greater_than) {
	
	function<void()> func = [](){};

	auto event1 = ClosureEvent<int>(func, 1);
	auto event2 = ClosureEvent<int>(func, 0);

	BOOST_CHECK(event1 != event2);
	BOOST_CHECK(event1 > event2);
	BOOST_CHECK(!(event1 < event2));

}

BOOST_AUTO_TEST_CASE(closure_test_equals) {
	
	function<void()> func = [](){};

	auto event1 = ClosureEvent<int>(func, 1);
	auto event2 = ClosureEvent<int>(func, 1);

	BOOST_CHECK(event1 == event2);

}

BOOST_AUTO_TEST_CASE(closure_test_copy) {
	
	function<void()> func = [](){};
	
	auto event1 = ClosureEvent<int>(func, 1);
	auto event2 = event1; 
	
	BOOST_CHECK(event1 == event2);
	
}

BOOST_AUTO_TEST_CASE(closure_test_dispatch) {
	
	int val = 0; 
	
	function<void()> func = [&](){ val = 1; };
	
	auto event1 = ClosureEvent<int>(func, 0);
	event1.dispatch();

	BOOST_CHECK_EQUAL(1, val);
	
}

#include "ListEventList.hpp"

BOOST_AUTO_TEST_CASE(list_test_through) {
	
	int val = 0; 
	
	function<void()> func = [&](){ val = 1; };
	
	auto event1 = ClosureEvent<int>(func, 0);
	
	auto cont = ListEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.run();

	BOOST_CHECK_EQUAL(1, val);
	
}

BOOST_AUTO_TEST_CASE(list_insertion_straight) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val = 2; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 1);
	
	auto cont = ListEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event2);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(1, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(2, val);
	
}

BOOST_AUTO_TEST_CASE(list_insertion_middle) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val = 2; };
	function<void()> func3 = [&](){ val = 3; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 1);
	auto event3 = ClosureEvent<int>(func3, 2);
	
	auto cont = ListEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event3);
	cont.add(event2);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(1, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(2, val);
	
	cont.tick(2);
	BOOST_CHECK_EQUAL(3, val);
	
}

BOOST_AUTO_TEST_CASE(list_insertion_same) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val += 1; };
	function<void()> func3 = [&](){ val = 3; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 0);
	auto event3 = ClosureEvent<int>(func3, 1);
	
	auto cont = ListEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event2);
	cont.add(event3);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(2, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(3, val);
	
}

#include "DequeEventList.hpp"

BOOST_AUTO_TEST_CASE(deque_test_through) {
	
	int val = 0; 
	
	function<void()> func = [&](){ val = 1; };
	
	auto event1 = ClosureEvent<int>(func, 0);
	
	auto cont = DequeEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.run();

	BOOST_CHECK_EQUAL(1, val);
	
}

BOOST_AUTO_TEST_CASE(deque_insertion_straight) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val = 2; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 1);
	
	auto cont = DequeEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event2);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(1, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(2, val);
	
}

BOOST_AUTO_TEST_CASE(deque_insertion_middle) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val = 2; };
	function<void()> func3 = [&](){ val = 3; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 1);
	auto event3 = ClosureEvent<int>(func3, 2);
	
	auto cont = DequeEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event3);
	cont.add(event2);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(1, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(2, val);
	
	cont.tick(2);
	BOOST_CHECK_EQUAL(3, val);
	
}

BOOST_AUTO_TEST_CASE(deque_insertion_same) {
	
	int val = 0; 
	
	function<void()> func1 = [&](){ val = 1; };
	function<void()> func2 = [&](){ val += 1; };
	function<void()> func3 = [&](){ val = 3; };
	
	auto event1 = ClosureEvent<int>(func1, 0);
	auto event2 = ClosureEvent<int>(func2, 0);
	auto event3 = ClosureEvent<int>(func3, 1);
	
	auto cont = DequeEventList<ClosureEvent<int>, int>();
	cont.add(event1);
	cont.add(event2);
	cont.add(event3);
	
	cont.tick(0);
	BOOST_CHECK_EQUAL(2, val);
	
	cont.tick(1);
	BOOST_CHECK_EQUAL(3, val);
	
}

#include "InstrumentedEventList.hpp"

BOOST_AUTO_TEST_CASE(instrumented_container) {
	
	auto cont = InstrumentedEventList<TestEvent<int>, int>();
	
	for(int i = 0; i < 30; i++) {
	  
		auto evnt = TestEvent<int>(i);
		
		cont.add(evnt);
	  
	}
	
	cont.run();
	
}




