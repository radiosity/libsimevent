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

#ifndef INSTRUMENTED_EVENT_LIST_HPP_
#define INSTRUMENTED_EVENT_LIST_HPP_

#include <list>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include "BaseEvent.hpp"
#include "EventList.hpp"

using std::list; 
using std::move;
using std::enable_if; 
using std::is_base_of;
using std::cout; 
using std::endl; 

using namespace boost::accumulators;

namespace libsim 
{
	
//Template metaprogramming baby
	
template<class T, class U, class Enable = void>
class InstrumentedEventList;

template <class T, class U>  
class InstrumentedEventList<T, U, typename enable_if<is_base_of<BaseEvent<U>, T>::value>::type > : public EventList<T,U> {

    private:
	list<T> data;
	accumulator_set<int, stats<tag::mean, tag::variance> > length;
	accumulator_set<int, stats<tag::mean> > infront;
	accumulator_set<int, stats<tag::mean> > inback;
	accumulator_set<int, stats<tag::mean> > inmiddle;

    public:
	
        InstrumentedEventList() = default; 
	InstrumentedEventList(InstrumentedEventList<T, U> const & cpy) : data(cpy.data) {}
	InstrumentedEventList(InstrumentedEventList<T, U> && mv) : data(move(mv.data)) {}
	InstrumentedEventList<T, U>& operator =(const InstrumentedEventList<T, U>& cpy) { data = cpy.data; }
	InstrumentedEventList<T, U>& operator =(InstrumentedEventList<T, U> && mv) { data = move(mv.data); }
        
	~InstrumentedEventList() {
		if( ! data.empty() ) {
			cout << "Danger, William Robinson. Event_List Destructor called while Events scheduled" << endl;
		}
		
		cout << "List_Event_List is instrumented, printing data" << endl;
		cout << "... Mean queue length was " << mean(length) << ", variance was " << variance(length) << endl;
		cout << "... Proportion of insertions at the front " << mean(infront) << endl;
		cout << "... Proportion of insertions in the middle " << mean(inmiddle) << endl;
		cout << "... Proportion of insertions at the back " << mean(inback) << endl;
	}

        void add(T evnt) override {

		if(data.empty()) {
			data.push_back(evnt);
			infront(1);
			inback(0);
			inmiddle(0);
		}
		else {

			//try to add it at the end
			auto riter = data.rbegin();
			auto iter = data.begin();

			if(evnt >= (*riter)) {
				//aka, the event being added is further off than the
				//oldest event currently in the queue.
				data.push_back(evnt);
				infront(0);
				inback(1);
				inmiddle(0);
			}
			else if (evnt <= (*iter)) {
				//aka, the event being added is younger than the next event in the queue.
				data.push_front(evnt);
				infront(1);
				inback(0);
				inmiddle(0);
			}
			else {
				//gutted. Now have to find the place for it to go.
				iter = upper_bound(data.begin(), data.end(), evnt);
				data.insert(iter, evnt);
				infront(0);
				inback(0);
				inmiddle(1);
			}

		}

        }

        void tick(U _time) override {
	  
		length(data.size());

		if(data.empty()) {
			return;
		}

		auto evnt = data.front();

		if(evnt.get_time() > _time) {
			return;
		}

		while(1) {

			if( evnt.get_time() > _time) {
				return;
			}
			else {
				data.pop_front();
				evnt.dispatch();

				if(data.empty()) {
					return;
				}

				evnt = data.front();
			}
		}

        }

        void run() override {

		while(!data.empty()) {

			length(data.size());
			
			T evnt = data.front();
			data.pop_front();
			evnt.dispatch();

		}

        }

};

}

#endif /* LIST_EVENT_LIST_HPP_ */