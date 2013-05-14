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
DISCLAIMED. IN NO EVENT SHALL RICHARD MARTIN BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <utility>

using std::move; 

namespace libsim
{

template <class T>
class BaseEvent {

    protected:
        T etime;

    public:
        BaseEvent(T _time = 0) : etime(_time) {}
	BaseEvent(BaseEvent<T> const & cpy): etime(cpy.etime) {}
	BaseEvent(BaseEvent<T> && mv) : etime(move(mv.etime)) {}
	BaseEvent<T>& operator =(const BaseEvent<T>& cpy) { etime = cpy.etime; return *this; }
	BaseEvent<T>& operator =(BaseEvent<T> && mv) { etime = move(mv.etime); return *this; }
        virtual ~BaseEvent() {}

        T get_time() const { return etime; }

        virtual void dispatch() {};
	
	bool operator< (const BaseEvent<T> &evnt) const {
		if(etime < evnt.etime) {
			return true;
		}
		return false;
        }
	
	bool operator <=(const BaseEvent<T> &evnt) const {
		if(etime == evnt.etime || etime < evnt.etime) {
			return true; 
		}
		return false; 
	}

        bool operator> (const BaseEvent<T> &evnt) const {
		if(etime > evnt.etime) {
			return true;
		}
		return false;
        }
	
	bool operator >=(const BaseEvent<T> &evnt) const {
		if(etime == evnt.etime || etime > evnt.etime) {
			return true;
		}
		return false; 
	}
	
	bool operator==(const BaseEvent<T> &evnt) const {
		if(etime == evnt.etime) {
			return true;
		}
		return false;
	}
	
	bool operator!= (const BaseEvent<T> &evnt) const {
		return (!(this == &evnt));
	}

};

}
#endif
