/*
 * Observer.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_


#include <string>

class Observer
{
    public:
        // Pure virtual function >> will be implemented in the child class
        virtual void update(const string &message) = 0;
};



#endif /* OBSERVER_H_ */
