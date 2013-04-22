#ifndef EVENT_LIST_HEADER
#define EVENT_LIST_HEADER

#include "Event.hpp"

template <class T>
class Event_List{

    public:

		Event_List() {};
		virtual ~Event_List() {};

        virtual void add(Event<T> * evnt) = 0;
        virtual void run() = 0;
        virtual void tick(T _time) = 0;

};

#endif
