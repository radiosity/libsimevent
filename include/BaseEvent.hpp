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

#ifndef EVENT_HEADER
#define EVENT_HEADER

template <class T>
class BaseEvent {

    private:
        const T time;

    public:

        BaseEvent(T _time = 0) : time(_time) {}
	BaseEvent(BaseEvent<T> const & cpy): time(cpy.time) {}
	BaseEvent(BaseEvent<T> && mv) : time(mv.time) {}
	BaseEvent<T>& operator =(const BaseEvent<T>& cpy) { time = cpy.time; }
	BaseEvent<T>& operator =(BaseEvent<T> && mv) { time = mv.time; }
        virtual ~BaseEvent() {}

        T get_time()  const{ return time; }

        virtual void dispatch() = 0;

        bool operator< (BaseEvent<T> * evnt) {
		if(time < evnt->time) {
			return true;
		}
		return false;
        }

        bool operator> (BaseEvent<T> * evnt) {
		if(time > evnt->time) {
			return true;
		}
		return false;
        }

        bool operator== (BaseEvent<T> * evnt) {
		if(time == evnt->time) {
			return true;
		}
		return false; 
	}
	
	 bool operator< (BaseEvent<T> &evnt) {
		if(time < evnt.time) {
			return true;
		}
		return false;
        }

        bool operator> (BaseEvent<T> &evnt) {
		if(time > evnt.time) {
			return true;
		}
		return false;
        }
	
	bool operator==(BaseEvent<T> &evnt) {
		if(time == evnt.time) {
			return true;
		}
		return false;
	}

};

#endif
