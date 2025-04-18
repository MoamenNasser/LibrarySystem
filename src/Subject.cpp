/*
 * Subject.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */





#include "Subject.h"
// Library Class acts as the subject of the observer design pattern
// These 3 methods related to the observers design pattern >> could be attached to a subject class but I preferred to add them to Library
void Subject::addObserver(const std::string &bookBarcode, Observer *observer)
{
    observers[bookBarcode].push_back(observer);
}
// This function remove an observer from the observers map
void Subject::removeObserver(const std::string &bookBarcode, Observer *observer)
{
    // here is the observer vector that i want to delete
    auto &obs = observers[bookBarcode];
    // remove function takes the first element of the vector and last element of the vector
    // and the last parameter is the observer to be deleted
    // remove function rearrange the vector elements
    // using erase function is mandatory because the remove function didn't change the size of the vector
    // So I want to delete the garbage elements so I used erase function to delete the garbage element that shifted by the remove function
    // The first element of the function is the return of the remove which points to the start of the garbage
            /*      remove shifts the unwanted elements to the end
                    erase trims the vector to remove the shifted elements
            */
    obs.erase(remove(obs.begin(), obs.end(), observer), obs.end());
}
// This function is used to notify the observers
void Subject::notifyObservers(const string &bookBarcode)
{
    // first I want to find the observer (Key-Value) pairs from the map
    auto observerListIterator = observers.find(bookBarcode);
    // checks if the key exist in the map
    if(observerListIterator != observers.end())
    {
        // looping on the observers
        for (Observer *observer : observers[bookBarcode])
        {
            // this line calls the update method with the message
            observer->update("The Book with barcode : " + bookBarcode + " is Now Available");
        }
    }

}
