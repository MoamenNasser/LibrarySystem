/*
 * BookItem.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef BOOKITEM_H_
#define BOOKITEM_H_


/*          BookItem class that inherits from the base class Book       */
#include "Book.h"
#include <string>

class BookItem : public Book
{
    public:
        string Barcode;
        bool InStock;
        int rackNumber;
    // Default constructor that sets the values
    BookItem();

    // another constructor to set the parameters that passed
    BookItem(string a, string t, string s, string Date, string id, string code, bool in, int number);
    // function to update the rack number
    void updateRackNumber(int newRackNumber);
};




#endif /* BOOKITEM_H_ */
