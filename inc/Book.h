/*
 * Book.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef BOOK_H_
#define BOOK_H_


/*          This Book class is the main class for each book inside the library      */
#include    <string.h>
class Book
{

    // defining the public variables and methods
    public:
        string author;
        string title;
        string subject;
        string DateOfPublication;
        string uniqueID;
// Default constructor >> mandatory if I use the class inside a map
    Book();

    // Another constructor with parameters
    Book(string author, string title, string subject, string DateOfPublication, string ID);

    // function to update the book details author, title, subject and date of publication
    void updateBookDetails(string a, string t, string s, string Date);
};



#endif /* BOOK_H_ */
