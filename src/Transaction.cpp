/*
 * Transaction.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */




#include <iostream>
#include <string>
/*      this is a class for the transaction that every member do with the time*/
#include "Transaction.h"

// constructor with parameters
Transaction::Transaction(string ID, string barcode, time_t date) : memberID(ID), bookBarcode(barcode), dueDate(date){}

