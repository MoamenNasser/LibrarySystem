/*
 * Transaction.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef TRANSACTION_H_
#define TRANSACTION_H_



#include <iostream>
#include <string>
/*      this is a class for the transaction that every member do with the time*/
class Transaction
{
    //
    public:
        string memberID;
        string bookBarcode;
        time_t dueDate;

        // constructor with parameters
        Transaction(string ID, string barcode, time_t date);

};

#endif /* TRANSACTION_H_ */
