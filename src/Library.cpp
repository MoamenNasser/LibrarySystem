/*
 * Library.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */




#include "Library.h"

/*      The Library class that has all the important details of books, members, transaction and notification service    */

// function to add the book into the map with
// key : a string which is the book barcode
// value : a bookItem object(with all attributes of this book item)
void Library::addBook(BookItem book)
{
    books[book.Barcode] = book;
}
// function to remove a book from the map
void Library::removeBook(const string &barcode)
{
    books.erase(barcode);
}
// function to edit book detail according to the barcode
void Library::editBook(const string &barcode,const string &author, const string &title, const string &subject, const string &DateOfPublication, int rackNumber)
{
    // to make it more optimizable we can store the iterator inside a variable
    // this method is efficient for 2 reasons:
    // 1- Single Lookup >> enables me to avoid searching for the same key twice
    // 2- Direct Access >> the iterator directly refers to the key-value pair in the map
    // allowing me to modify the value of the BookItem without another search
    auto iterator = books.find(barcode);

    // after storing the iterator variable now I need to check if the book was found
    if(iterator != books.end())
    {
        // using the iterator to access the book and modigy it directly
        iterator -> second.updateBookDetails(author, title, subject, DateOfPublication);
        iterator -> second.updateRackNumber(rackNumber);
    }

}
// function to register a member to the system
void Library::registerMember(Member member)
{
    members[member.getMemberID()] = member;
}
// function to cancel the membership of a member according to ID
void Library::cancelMembership(const string &memberID)
{
    members.erase(memberID);
}
// function to Checks for overdue books and notifies the respective members
void Library::overdueCheck()
{
    time_t now = time(0);
    // iterating on the transactions and checks if the dueDate is less than
    for(const auto &transaction : transactions)
    {
        // checking if the date smaller than the current time stamp
        if(transaction.dueDate < now)
        {
            Notification.notifyOverdue(transaction.memberID, transaction.bookBarcode);
        }
    }
}
// This function returns the member that checked out a specific book
string Library::whoCheckedOutBook(const string& barcode) const
{
    // iterating on the transactions
    for (const auto& transaction : transactions)
    {
        // searching for the book that has a specific barcode
        if (transaction.bookBarcode == barcode)
        {
            // printing and returning the memberID of the member
            cout << "Book with barcode " << barcode << " is checked out by member " << transaction.memberID << endl;
            return transaction.memberID;
        }
    }

    cout << "No record found for book with barcode " << barcode << endl;
    return "";
}

// Function to checkout a book with a specified member
void Library::booksCheckedOutByMember(const string& memberID) const
{
    // iterator to find the member with this ID
    auto memberIt = members.find(memberID);
    // checking if the iterator points to nothing
    if (memberIt != members.end())
    {
        // Ensure checkedOutbooks_MAP is correctly referenced >> efficiency and read only access
        const auto& checkedOutbooks_MAP = memberIt->second.checkedOutbooks_MAP;
        if (!checkedOutbooks_MAP.empty())
        {
            cout << "Member " << memberID << " has checked out the following books:" << endl;
            // looping on the books map
            for (const auto& book : checkedOutbooks_MAP)
            {
                // assign the barcode and due date to the variables >> from the key-value pair
                const string& barcode = book.first;
                const time_t& dueDate = book.second;

                // Output the title of the book
                cout << "- " << books.at(barcode).title << endl;
            }
        }
        else
        {
            cout << "Member " << memberID << " has no books checked out." << endl;
        }
    }
    else
    {
        cout << "No member found with ID " << memberID << endl;
    }
}

// function to checkout a book according to the member ID and book barcode
bool Library::checkoutBook(const string &memberID, const string &barcode)
{

    // check if the book is available or not
    if(books.find(barcode) == books.end() || !books[barcode].InStock)
    {
        return false;
    }
    // check the availability to checkout more books
    if(!members[memberID].canCheckoutMoreBooks())
    {
        return false;
    }

    books[barcode].InStock = false;
    // get the current time stamp
    time_t now = time(0);
    // adding the transaction to the vector
    transactions.push_back(Transaction(memberID, barcode, now + ADDITIONAL_10_DAYS));
    // adding a 10 days additional for the member according to hid ID
    members[memberID].checkedOutbooks_MAP[barcode] = now + ADDITIONAL_10_DAYS;
    return true;


}
// function to return a book
bool Library::returnBook(const string &memberID, const string &barcode)
{
    // making 2 variables to store the iterator of the book and member
    auto bookIterator = books.find(barcode);
    auto memberIterator = members.find(memberID);
    // checks if the books exists in the map or not + checks if the book is not in the member's checked out books
    if(books.find(barcode) == books.end() || members[memberID].checkedOutbooks_MAP.find(barcode) == members[memberID].checkedOutbooks_MAP.end())
    {
        return false;
    }
    // this line avoid copying the entire map >> we can modify through the reference
    auto &checkedOutbooks_MAP = memberIterator -> second.checkedOutbooks_MAP;
    // searching for a book according to its barcode
    auto bookRecord = checkedOutbooks_MAP.find(barcode);

    if(bookRecord == checkedOutbooks_MAP.end())
    {
        // then book isn't checked by this member
        return false;
    }
    // get the current time stamp
    time_t now = time(0);
    // assign the due date into a variable with same type
    time_t dueDate = bookRecord->second;
    // checking if the current time stamp bigger than the due date
    if(now > dueDate)
    {
        // calculate number of overdue days
        int daysOverdue = (now - dueDate) / (24*60*60);
        // adding fine to the a variable then assign it to the member
        double fine_added = daysOverdue * FINE_PER_DAY;
        cout << "Book with barcode: "<< barcode << " is overdue by " << daysOverdue << " days and the fine allowed is:  "<< fine_added;
        cout << endl;
        // here add the fine function in the member class
        memberIterator->second.addFine(fine_added);
    }
    // change the value of availability to true >> it is restocked because it has returned
    books[barcode].InStock = true;
    // Now we need to delete this cook from the member's checked out books
    members[memberID].checkedOutbooks_MAP.erase(barcode);
    // Here we notify all observers that want this book
    notifyObservers(barcode);
    return true;
}
// function to renew a book
bool Library::renewBook(const string &memberID, const string &barcode)
{
    // checking if the book exists or not and the book with bar code exist in the checkoutbooks of this member exists or not >> if not return false
    if (books.find(barcode) == books.end() || members[memberID].checkedOutbooks_MAP.find(barcode) == members[memberID].checkedOutbooks_MAP.end())
    return false;

    // calculating the current time stamp
    time_t now = time(0);
    // adding 10 days to the current time stamp then assign it to the member
    members[memberID].checkedOutbooks_MAP[barcode] = now + ADDITIONAL_10_DAYS;
    // looping over the transactions
    for (auto &transaction : transactions)
    {
        // checking if the barcode given matched the transaction barcode and memberID matched the transaction memberID
        if (transaction.bookBarcode == barcode && transaction.memberID == memberID)
        {
            // adding more 10 days for the member
            transaction.dueDate = now + ADDITIONAL_10_DAYS;
            break;
        }
    }

    return true;
}
// function to reserve a book
bool Library::reserveBook(const string &memberID, const string &barcode)
{
    // checking if the book exists and the member can reserve more books or not
    if (books.find(barcode) == books.end() || members[memberID].canReserveBook())
    {
        // inserting this book inside the reservedBooks set of the member with this ID
        members[memberID].reservedBooks.insert(barcode);
        return true;
    }
    return false;
}
// function to search for a book in the catalog
void Library::searchaBookInCatalog(const string &author, const string &title, const string &subject, const string &DateOfPublication) const
{
        // looping over the books map
    for (const auto &book : books)
    {
    // checking for each pair (title, author, subject and Date of Publication)
        if ((title.empty() || book.second.title == title) &&
            (author.empty() || book.second.author == author) &&
            (subject.empty() || book.second.subject == subject) &&
            (DateOfPublication.empty() || book.second.DateOfPublication == DateOfPublication))
            {
                cout << "Found book: " << book.second.title << " by " << book.second.author << endl;
            }
    }
}


