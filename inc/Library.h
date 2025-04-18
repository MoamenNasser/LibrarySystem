/*
 * Library.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#ifndef Library_H_
#define Library_H_


#include <iostream>
#include <string>
#include <vector>

#include <ctime>
#include <algorithm>
#include <cmath>

#include "Observer.h"
#include "BookItem.h"
#include "Member.h"
#include <unordered_map>
#include <unordered_set>
class Library
{
    private:
        // private attributes which are mainly encapsulated and hidden
        // Key is the barcode of the book and the value is the BookItem Class
        unordered_map<string, BookItem>books;
        // Key is the member ID and the value is the Member class
        unordered_map<string, Member> members;
        // this is a vector that stores all the transactions done which type is Transaction class
        // These are the attributes inside the Transaction: memberID, bookBarcode, dueDate
        vector<Transaction> transactions;
        // an Object from the NotificationService Class
        NotificationService Notification;
        // Map for the observers
        // Key is the book bar code and the value is a vector of pointers to the Observer class
        // using vector allows me to register (multiple observers)
        // This vector holds all the observers that are interested in the events
        unordered_map<string, vector<Observer*>> observers;

    public:

        // function to add the book into the map with
        // key : a string which is the book barcode
        // value : a bookItem object(with all attributes of this book item)
        void addBook(BookItem book);
        // function to remove a book from the map
        void removeBook(const string &barcode);
        // function to edit book detail according to the barcode
        void editBook(const string &barcode,const string &author, const string &title, const string &subject, const string &DateOfPublication, int rackNumber);
        // function to register a member to the system
        void registerMember(Member member);
        // function to cancel the membership of a member according to ID
        void cancelMembership(const string &memberID);
        // function to Checks for overdue books and notifies the respective members
        void overdueCheck();
        // This function returns the member that checked out a specific book
        string whoCheckedOutBook(const string& barcode) const;

        // Function to checkout a book with a specified member
        void booksCheckedOutByMember(const string& memberID)const;

        // function to checkout a book according to the member ID and book barcode
        bool checkoutBook(const string &memberID, const string &barcode);
        // function to return a book
        bool returnBook(const string &memberID, const string &barcode);
        // function to renew a book
        bool renewBook(const string &memberID, const string &barcode);
        // function to reserve a book
        bool reserveBook(const string &memberID, const string &barcode);
        // function to search for a book in the catalog
        void searchaBookInCatalog(const string &author, const string &title, const string &subject, const string &DateOfPublication) const;

};

#endif



#endif /* LIBRARY_H_ */
