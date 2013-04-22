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
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
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

#include "Event.hpp"

using std::cout;
using std::endl; 

//Declare a simple dummy subclass 
template <class T>
class Test_Event : public Event<T>
{
public:
	Test_Event(T _time) : Event<T>(_time) {};
	~Test_Event() {};
	void dispatch() {}
};

BOOST_AUTO_TEST_CASE(event_test_get) {
	
	Test_Event<int> * evnt = new Test_Event<int>(0);

	BOOST_CHECK_EQUAL(evnt->get_time(),  0);

	delete evnt;
	
}

BOOST_AUTO_TEST_CASE(event_test_less_than) {

	Test_Event<int> * event1 = new Test_Event<int>(0);

	Test_Event<int> * event2 = new Test_Event<int>(1);

	BOOST_CHECK(*event1 < event2);

	delete event2;
	delete event1;

}

BOOST_AUTO_TEST_CASE(event_test_greater_than) {

	Test_Event<int> * event1 = new Test_Event<int>(1);

	Test_Event<int> * event2 = new Test_Event<int>(0);

	BOOST_CHECK(*event1 > event2);

	delete event2;
	delete event1;

}

BOOST_AUTO_TEST_CASE(event_test_equals) {

	Test_Event<int> * event1 = new Test_Event<int>(1);

	Test_Event<int> * event2 = new Test_Event<int>(1);

	BOOST_CHECK(*event1 == event2);

	delete event2;
	delete event1;

}