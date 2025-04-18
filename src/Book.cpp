/*
 * Book.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */



/*          This Book class is the main class for each book inside the library      */
#include "Book.h"

// Default constructor >> mandatory if I use the class inside a map
Book::Book() : author(""), title(""), subject(""), DateOfPublication(""), uniqueID("") {}

// Another constructor with parameters
Book::Book(string author, string title, string subject, string DateOfPublication, string ID):author(author), title(title), subject(subject), DateOfPublication(DateOfPublication), uniqueID(ID) {}

// function to update the book details author, title, subject and date of publication
void Book::updateBookDetails(string a, string t, string s, string Date)
{
    author = a;
    title = t;
    subject = s;
    DateOfPublication = Date;

}

