/*
 * List_Event_List.hpp
 *
 *  Created on: Jan 21, 2011
 *      Author: richardmartin
 */

#ifndef LIST_EVENT_LIST_HPP_
#define LIST_EVENT_LIST_HPP_

#include <list>
#include <algorithm>
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>

#include "Event_List.hpp"
#include "Event.hpp"

using namespace std;
using namespace boost::accumulators;

template <class T, bool U = false, bool V = false>
class List_Event_List : public Event_List<T>{

    private:
		list<Event<T> * > data;

    public:
		List_Event_List() : Event_List<T>() {
			 //data = list<Event<T> *>();
		}

        ~List_Event_List() {
        		if( ! data.empty() ) {
        			cout << "Danger, William Robinson. Event_List Destructor called while Events scheduled" << endl;
        		}

        		Event<T> * evnt;

			BOOST_FOREACH(evnt, data)
			{
					delete evnt;
			}

        }

        void add(Event<T> * evnt){

        		if(data.empty()) {
        			data.push_back(evnt);
        		}
        		else {

        			//try to add it at the end

        			typename list<Event<T> *>::reverse_iterator riter;
        			typename list<Event<T> *>::iterator iter;
        			riter = data.rbegin();
        			iter = data.begin();

        			if(evnt->get_time() >= (*riter)->get_time()) {
					//aka, the event being added is further off than the
					//oldest event currently in the queue.
					data.push_back(evnt);
				}
        			else if (evnt->get_time() <= (*iter)->get_time()) {
					//aka, the event being added is younger than the next event in the queue.
					data.push_front(evnt);
        			}
        			else {
        				//gutted. Now have to find the place for it to go.
        				iter = upper_bound(data.begin(), data.end(), evnt);

        				data.insert(iter, evnt);
        			}

        		}

        }

        void tick(T _time) {

        		if(data.empty()) {
        			return;
        		}

        		Event<T> * evnt = data.front();

        		if(evnt->get_time() < _time) {
        			return;
        		}

        		while(1) {

        			if( evnt->get_time() > _time) {
        				return;
        			}
        			else {
        				data.pop_front();
        				evnt->dispatch();

        				if(data.empty()) {
        					return;
        				}

					evnt = data.front();
        			}
        		}

        }

        void run() {

        		while(!data.empty()) {

        			Event<T> * evnt = data.front();
        			data.pop_front();
        			evnt->dispatch();

        		}

        }

};

template <class T, bool U>
class List_Event_List<T, true, U> : public Event_List<T>{

	public:
		accumulator_set<int, stats<tag::mean, tag::variance> > length;
		accumulator_set<int, stats<tag::mean> > infront;
		accumulator_set<int, stats<tag::mean> > inback;
		accumulator_set<int, stats<tag::mean> > inmiddle;

	private:
		list<Event<T> * > data;


	public:
		List_Event_List() : Event_List<T>() {
			 //data = list<Event<T> *>();
		}

    ~List_Event_List() {
    		if( ! data.empty() ) {
    			cout << "Danger, William Robinson. Event_List Destructor called while Events scheduled" << endl;
    		}

    		Event<T> * evnt;

		BOOST_FOREACH(evnt, data)
		{
				delete evnt;
		}

		if(U) cout << "List_Event_List is instrumented, printing data" << endl;
		if(U) cout << "\t Mean queue length was " << mean(length) << ", variance was " << variance(length) << endl;
		if(U) cout << "\t Proportion of insertions at the front " << mean(infront) << endl;
		if(U) cout << "\t Proportion of insertions in the middle " << mean(inmiddle) << endl;
		if(U) cout << "\t Proportion of insertions at the back " << mean(inback) << endl;

    }

    void add(Event<T> * evnt){

    		if(data.empty()) {
    			data.push_back(evnt);

    			infront(1);
    			inback(0);
    			inmiddle(0);

    		}
    		else {

    			//try to add it at the end

    			typename list<Event<T> *>::reverse_iterator riter;
    			typename list<Event<T> *>::iterator iter;
    			iter = data.begin();
    			riter = data.rbegin();

    			if(evnt->get_time() >= (*riter)->get_time()) {
    				//aka, the event being added is further off than the
    				//oldest event currently in the queue.
    				data.push_back(evnt);

    				infront(0);
    				inback(1);
    				inmiddle(0);

    			}
    			else if (evnt->get_time() <= (*iter)->get_time()) {
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

    void tick(T _time) {

    		length(data.size());

    		if(data.empty()) {
    			return;
    		}

    		Event<T> * evnt = data.front();

    		if(evnt->get_time() < _time) {
    			return;
    		}

    		while(1) {

    			if( evnt->get_time() > _time) {
    				return;
    			}
    			else {
    				data.pop_front();
    				evnt->dispatch();

    				if(data.empty()) {
    					return;
    			    }

				evnt = data.front();
    			}
    		}

    }

    void run() {

    		while(!data.empty()) {

    			length(data.size());

    			Event<T> * evnt = data.front();
    			data.pop_front();
    			evnt->dispatch();

    		}

    }


};

#endif /* LIST_EVENT_LIST_HPP_ */
