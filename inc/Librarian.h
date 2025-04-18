/*
 * Librarian.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef LIBRARIAN_H_
#define LIBRARIAN_H_



class Librarian : public Member
{
    // I don't need to add variables for the librarian
    // Just adding the methods that the librarian should do to the clients
    public:
        // default constructor
        Librarian() : Member(){}
        // another constructor that sets the parameters
        Librarian(const string &n, const string &ID) : Member(n, ID) {}

        // function to add a book to the library object
        void addBook(Library &lib, BookItem book);
        // function to remove a book from the library object according to the barcode
        void removeBook(Library &lib, const string &barcode);
        // function to edit the book details
        void editBook(Library &lib, const string &barcode, const string &author, const string &title, const string &subject, const string &DateOfPublication, int rackNumber);
        // function to register a member to the system
        void registerMember(Library &lib, Member member);
        // function to cancel the membership of the member
        void cancelMembership(Library &lib, const string &memberID);


};



#endif /* LIBRARIAN_H_ */
