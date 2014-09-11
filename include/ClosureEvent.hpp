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

#ifndef CLOSUREEVENT_HEADER
#define CLOSUREEVENT_HEADER

#include <functional>
#include <utility>

#include "BaseEvent.hpp"

using std::function;
using std::move;

namespace libsim 
{

template <class T>
class ClosureEvent : public BaseEvent<T> {
	
private:
	function<void()> f; 
	
public:
	
        ClosureEvent(function<void()> _f, T _time = 0) : BaseEvent<T>(_time), f(_f) {}
	ClosureEvent(ClosureEvent<T> const & cpy): BaseEvent<T>(cpy), f(cpy.f) {}
	ClosureEvent(ClosureEvent<T> && mv) : BaseEvent<T>(move(mv)), f(move(mv.f)) {}
	ClosureEvent<T>& operator =(const ClosureEvent<T>& cpy) { 
		BaseEvent<T>::operator=(cpy); 
		f = cpy.f; 
		return *this;
	}
	ClosureEvent<T>& operator =(ClosureEvent<T> && mv) { 
		BaseEvent<T>::operator=(move(mv)); 
		f = move(mv.f); 
		mv.f = [](){};
		return *this; 
	}
        virtual ~ClosureEvent() {}
		
	virtual void dispatch() override final { f(); }
	
	bool operator< (const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator<(evnt);
        }
	
	bool operator <=(const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator<=(evnt);
	}

        bool operator> (const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator>(evnt);
        }
	
	bool operator >=(const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator>=(evnt);
	}
	
	bool operator==(const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator==(evnt);
	}
	
	bool operator!= (const ClosureEvent<T> &evnt) const {
		return BaseEvent<T>::operator!=(evnt);
	}
		
};

}

#endif
