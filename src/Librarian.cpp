/*
 * Librarian.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */





/*          A class for the Librarian that will deal with clients      */
#include "Librarian.h"
#include "Library.h"
#include "BookItem.h"
#include "Member.h"

// Librarian class methods
/*
        The librarian can do different things according to PDF
        1- add a new book to the library
        2- remove an existing book
        3- edit details of any book
        4- register a new member to the system
        5- cancel membership of any member
*/
void Librarian::addBook(Library &lib, BookItem book)
{
    lib.addBook(book);
}

// function to remove a book according to the bar code
void Librarian::removeBook(Library &lib, const string &barcode)
{
    lib.removeBook(barcode);

}

/*              function to edit a detail of a book     */
void Librarian::editBook(Library &lib, const string &barcode, const string &author, const string &title, const string &subject, const string &DateOfPublication, int rackNumber)
{
    lib.editBook(barcode, author, title, subject, DateOfPublication, rackNumber);
}

/*          function  to register a member into the library     */
void Librarian::registerMember(Library &lib, Member member)
{
    lib.registerMember(member);
}

/*          function to cancel the membership of the member     */
void Librarian::cancelMembership(Library &lib, const string &memberID)
{
    lib.cancelMembership(memberID);
}
