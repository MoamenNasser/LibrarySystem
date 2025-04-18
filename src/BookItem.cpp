/*
 * BookItem.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */





    /*          BookItem class that inherits from the base class Book       */
    #include "BookItem.h"

    // Default constructor that sets the values
    BookItem::BookItem() : Barcode(""), InStock(true), rackNumber(0){}

    // another constructor to set the parameters that passed
    BookItem::BookItem(string a, string t, string s, string Date, string id, string code, bool in, int number) : Book(a, t, s, Date, id), Barcode(code), InStock(true),rackNumber(number){}

    // function to update the rack number
    void BookItem::updateRackNumber(int newRackNumber)
    {
        rackNumber = newRackNumber;
    }
