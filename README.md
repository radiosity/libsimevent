#libsimwindow

I've written a number of event-based simulators in my life, and in the end I always end up recreating a simple event loop and event class. I've therefore decided to take a more dedicated approach, designing a modular re-usable component based around C++11.

libsimevent is the result of this work.  

EventList
-----
This is the superclass for all the list of events waiting to be called. Currently it has only one implementation, the ListEventList.

ListEventList
-----
This class provides an implementation of an EventList utilising a std::list as the storage interface. This should provide reasonable performance under most circumstances. 

BaseEvent
-----
This class provides the simplest Event, designed to be subclassed by users in order to create events that perform the functions that they require by overriding the dispatch() method. 

ClosureEvent
-----
This accepts an argument of a std::function and therefore can be fairly broadly used, but its true advantage is native support of C++11 lambdas and closures. This should make definition of event functions significantly cleaner. 
