#include "Event.hpp"

#include <gtest/gtest.h>

template <class T>
class Test_Event : public Event<T>
{
public:
	Test_Event(T _time) : Event<T>(_time) {};
	~Test_Event() {};
	void dispatch() {}
};

TEST(Event_Test, ReturnsCorrectValues) {

    Test_Event<int> * evnt = new Test_Event<int>(0);

    ASSERT_EQ(evnt->get_time(), 0);

    delete evnt;

}

TEST(Event_Test, LessThan) {

	Test_Event<int> * event1 = new Test_Event<int>(0);

	Test_Event<int> * event2 = new Test_Event<int>(1);

	ASSERT_TRUE(*event1 < event2);

	delete event2;
	delete event1;

}

TEST(Event_Test, GreatherThan) {

	Test_Event<int> * event1 = new Test_Event<int>(1);

	Test_Event<int> * event2 = new Test_Event<int>(0);

	ASSERT_TRUE(*event1 > event2);

	delete event2;
	delete event1;

}

TEST(Event_Test, Equality) {

	Test_Event<int> * event1 = new Test_Event<int>(1);

	Test_Event<int> * event2 = new Test_Event<int>(1);

	ASSERT_TRUE(*event1 == event2);

	delete event2;
	delete event1;

}



