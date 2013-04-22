#ifndef EVENT_HEADER
#define EVENT_HEADER

template <class T>
class Event {

    private:
        const T time;

    public:

        Event(T _time = 0) : time(_time) {}
        virtual ~Event() {}

        T get_time() { return time; }

        virtual void dispatch() = 0;

        bool operator< (Event<T> * evnt) {

        		if(time < evnt->time) {
        			return true;
        		}
        		else {
        			return false;
        		}

        }

        bool operator> (Event<T> * evnt) {

        		if(time > evnt->time) {
        			return true;
        		}
        		else {
        			return false;
        		}

        }

        bool operator== (Event<T> * evnt) {

        		if(time == evnt->time) {
        			return true;
        		}
        		else {
        			return false;
        		}

        }

};

#endif
