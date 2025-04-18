/*
 * Subject.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "Observer.h"
#include <unordered_map>
#include <vector>


class Subject
{
    public:
        // Map for the observers
        // Key is the book bar code and the value is a vector of pointers to the Observer class
        // using vector allows me to register (multiple observers)
        // This vector holds all the observers that are interested in the events
        unordered_map<string, vector<Observer*>> observers;
        // These 3 methods related to the observers design pattern >> could be attached to a subject class but I preferred to add them to Library
        void addObserver(const string &bookBarcode, Observer *observer);
        // This function remove an observer from the observers map
        void removeObserver(const string &bookBarcode, Observer *observer);
        // This function is used to notify the observers
        void notifyObservers(const string &bookBarcode);
};




#endif /* SUBJECT_H_ */
