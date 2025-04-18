#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ctime>
#include <algorithm>
#include <cmath>


/*          MACROS CAN BE CONFIGURED FOR FUTURE USAGE       */
#define ADDITIONAL_10_DAYS      10*24*60*60
#define FINE_PER_DAY        5.0
#define MAX_BOOKS_ALLOWED   5

using namespace std;


/*      Forward Declaration of the Library Class     */
//  This declaration helps me to overcome the circular dependencies

class Library;

/*      This is the abstract class used to handle the observer
        This can not be accessed using an object
        >> using the observer design pattern      */
class Observer 
{
    public:


        // Pure virtual function >> will be implemented in the child class
        virtual void update(const string &message) = 0;  
};


/*          class for the notification Service      */
class NotificationService
{
    public:

        // function to notify that the book is available or not
        void notifyAvailability(const string &memberID, const string &bookBarcode)
        {
            cout << "Notification bar: Book with barcode: " << bookBarcode << " is now available for member " << memberID << endl;
        }
        // function to notify the overdue
        void notifyOverdue(const string &memberID, const string &bookBarcode)
        {
            cout << "Notification Bar: Book with barcode " << bookBarcode << " is overdue for that member " << memberID<<endl;
        }

        // function to send an email to the member
        void sendEmail(const string &email, const string &subject, const string &body)
        {
            cout << "Sending Email to : " << email << "\nSubject: " << subject << "\nBody: "<< body << "\n";
        }

        //function to send a SMS message to the according phone number
        void sendSMS(const string &number, const string &message)
        {
            cout << "Sending SMS to: " << number << "\nMessage: "<<message <<"\n";
        }
};


/*          This Book class is the main class for each book inside the library      */
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
        Book() : author(""), title(""), subject(""), DateOfPublication(""), uniqueID("") {}

        // Another constructor with parameters
        Book(string author, string title, string subject, string DateOfPublication, string ID):author(author), title(title), subject(subject), DateOfPublication(DateOfPublication), uniqueID(ID) {}

        // function to update the book details author, title, subject and date of publication
        void updateBookDetails(string a, string t, string s, string Date)
        {
            author = a;
            title = t;
            subject = s;
            DateOfPublication = Date;

        }

};



/*          BookItem class that inherits from the base class Book       */
class BookItem : public Book
{
    public:
        string Barcode;
        bool InStock;
        int rackNumber;

        // Default constructor that sets the values 
        BookItem() : Barcode(""), InStock(true), rackNumber(0){}

        // another constructor to set the parameters that passed
        BookItem(string a, string t, string s, string Date, string id, string code, bool in, int number) : Book(a, t, s, Date, id), Barcode(code), InStock(true),rackNumber(number){}

        // function to update the rack number
        void updateRackNumber(int newRackNumber)
        {
            rackNumber = newRackNumber;
        }
};

/*          Member Class for every client come to the library and anybody       */
class Member : public Observer
{
    // private attributes
    private:
        string name;
        string memberID;
        string Email;
        string PhoneNumber;
        // this line ensures that the class member can see the notification class
        NotificationService notificationService; 
        double fineBalance;

    //public methods and variables
    public:
        // I need to store the checked out book and the time
        // 1. Key is the barcode of the book
        // 2. value is the time that this book checked out in
        unordered_map<string, time_t> checkedOutbooks_MAP;
        // Allocate set to store the reserved books
        unordered_set<string> reservedBooks;
        // default constructor to initialize the variables
        Member() : name(""), memberID(""), Email(""), PhoneNumber(""), fineBalance(0.0) {}

        // Constructor with name and ID (no defaults to avoid ambiguity)
        Member(const string &n, const string &id)
            : name(n), memberID(id), Email(""), PhoneNumber(""), fineBalance(0.0) {}

        // Constructor with all parameters
        Member(const string &n, const string &id, const string &mail, const string &phone)
            : name(n), memberID(id), Email(mail), PhoneNumber(phone), fineBalance(0.0) {}    
        // Now I need getters and setters to control the data
        string getEmail()const
        {
            return Email;
        }
        // function to return the phone number of the member
        string getPhoneNumber()const
        {
            return PhoneNumber;
        }
        // function to return the name of the member
        string getName() const
        {
            return name;
        }
        // function to return the member ID
        string getMemberID() const
        {
            return memberID;
        }

        // setters methods
        void setEmail(const string &new_mail)
        {
            Email = new_mail;

        }
        // function to set the phone number to the member
        void setPhoneNumber(const string &new_phone)
        {
            PhoneNumber = new_phone;
        }
        // function to process the fine payment
        void processFinePayment(Member &member, double amount) 
        {
            // if the payment return true == success payment
            if (member.payFine(amount)) 
            {
                cout << "Payment processed successfully." << endl;
            } 
            else 
            {
                cout << "Payment failed. Please check the amount and try again." << endl;
            }
        }

        // function to add fine to the member 
        void addFine(double amount)
        {
            // adding the amount to the fine balance
            fineBalance += amount;
            // printing the amount and member ID
            cout << "Fine of " << amount << " is applied to the member with ID: " << memberID << " and the total outstanding fines: " << fineBalance << endl;
        }
        // function to pay the fine
        bool payFine(double amount)
        {
            // checking if the amount is negative
            if(amount <= 0)
            {
                cout << "Invalid Payment amount" << endl;
            }
            // checking if the amount if higher than the fineBalance 
            if(amount > fineBalance)
            {
                cout << "Payment Exceeds outstanding fine Balance"<<endl;
                return false;
            }
            // decrement the fineBalance with the according amount
            fineBalance -= amount;
            cout << "Payment of " << amount <<" Received From the Member with ID: " << memberID << " and the remaining balance is: " << fineBalance<<endl;
            return true;

        }

        // function to return the fine balance
        double getFineBalance()const
        {
            return fineBalance;
        }

        // function to check the ability to checkout more books (Limit is 5)
        bool canCheckoutMoreBooks()
        {
            if(checkedOutbooks_MAP.size() >= MAX_BOOKS_ALLOWED)
            {
                cout << "Member with ID " << memberID << " has reached the maximum number of checkouts of books"<<endl;
                return false;
            }
            if(fineBalance >0 )
            {
                cout << "Member with ID " << memberID << " has outstanding fines of " << fineBalance << " Must be paid before checking out more books" << endl;
                return false;
            }

            return true;
        }
        // function to check the ability to reserve books more books (Limit is 5)
        bool canReserveBook()
        {
            return (reservedBooks.size() < MAX_BOOKS_ALLOWED);
        }

        // function to search a book from a catalog in the library passed
        void searchForAbook(const Library &lib, const string &author = "", const string &title = "", const string &subject = "", const string &DateOfPublication = "") const;

        // function to checkout the selected book
        bool checkoutBook(Library &lib, const string &barcode);
        // function to return a book 
        bool returnBook(Library &lib, const string &barcode);
        // function to reserve a book
        bool reserveBook(Library &lib, const string &barcode);
        // function to renew the book 
        bool renewBook(Library &lib, const string &barcode);
        // function to add fine to the member

        // This function override the function in the abstract class observer to send notification for the member with the message
        void update(const string &message) override 
        {
            cout << "Notification for " << name << ": " << message << endl;
            // Sending an email and SMS to the member
            NotificationService notificationService;
            notificationService.sendEmail(Email, "Library Notification", message);
            notificationService.sendSMS(PhoneNumber, message);
        }

};

/*          A class for the Librarian that will deal with clients      */
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


/*      this is a class for the transaction that every member do with the time*/
class Transaction
{
    // 
    public:
        string memberID;
        string bookBarcode;
        time_t dueDate;

        // constructor with parameters
        Transaction(string ID, string barcode, time_t date) : memberID(ID), bookBarcode(barcode), dueDate(date){}

};

/*      The Library class that has all the important details of books, members, transaction and notification service    */
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
        // Library Class acts as the subject of the observer design pattern
        // These 3 methods related to the observers design pattern >> could be attached to a subject class but I preferred to add them to Library
        void addObserver(const string &bookBarcode, Observer *observer) 
        {
            // adding the observer to the vector of observers
            observers[bookBarcode].push_back(observer);
        }
        // This function remove an observer from the observers map
        void removeObserver(const string &bookBarcode, Observer *observer) 
        {
            // here is the observer vector that i want to delete
            auto &obs = observers[bookBarcode];
            // remove function takes the first element of the vector and last element of the vector
            // and the last parameter is the observer to be deleted
            // remove function rearrange the vector elements
            // using erase function is mandatory because the remove function didn't change the size of the vector
            // So I want to delete the garbage elements so I used erase function to delete the garbage element that shifted by the remove function
            // The first element of the function is the return of the remove which points to the start of the garbage
                    /*      remove shifts the unwanted elements to the end
                            erase trims the vector to remove the shifted elements
                    */
            obs.erase(remove(obs.begin(), obs.end(), observer), obs.end());
        }
        // This function is used to notify the observers
        void notifyObservers(const string &bookBarcode) 
        {
            // first I want to find the observer (Key-Value) pairs from the map
            auto observerListIterator = observers.find(bookBarcode);
            // checks if the key exist in the map
            if(observerListIterator != observers.end())
            {
                // looping on the observers
                for (Observer *observer : observers[bookBarcode]) 
                {
                    // this line calls the update method with the message
                    observer->update("The Book with barcode : " + bookBarcode + " is Now Available");
                }
            }

        }
        // function to add the book into the map with
        // key : a string which is the book barcode
        // value : a bookItem object(with all attributes of this book item)
        void addBook(BookItem book)
        {
            books[book.Barcode] = book;
        }
        // function to remove a book from the map
        void removeBook(const string &barcode)
        {
            books.erase(barcode);
        }
        // function to edit book detail according to the barcode
        void editBook(const string &barcode,const string &author, const string &title, const string &subject, const string &DateOfPublication, int rackNumber)
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
        void registerMember(Member member)
        {
            members[member.getMemberID()] = member;
        }
        // function to cancel the membership of a member according to ID
        void cancelMembership(const string &memberID)
        {
            members.erase(memberID);
        }
        // function to Checks for overdue books and notifies the respective members
        void overdueCheck()
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
        string whoCheckedOutBook(const string& barcode) const 
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
        void booksCheckedOutByMember(const string& memberID) const 
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


/*          Member Class methods        */
// function to search for a book 
void Member :: searchForAbook(const Library &lib, const string &author, const string &title, const string &subject, const string &DateofPublication) const
{
    lib.searchaBookInCatalog(author, title, subject, DateofPublication);

}

/*      function to checkout book          */
bool Member::checkoutBook(Library &lib, const string &barcode)
{
    // I need to handle the payment restriction
    if(!canCheckoutMoreBooks())
    {
        return false;
    }
    // checking member can checkout more books or not
    if(!lib.checkoutBook(memberID, barcode))
    {
        cout << "Inable to checkout book with the barcode: " << barcode << endl;
        return false;
    }
    // Add the book to member's checked out books with due date of additional 10 days from now
    time_t now = time(0);
    time_t NEW_dueDate = now + ADDITIONAL_10_DAYS; 
    // updating the due date
    checkedOutbooks_MAP[barcode] = NEW_dueDate;
    cout << "Member with ID " << memberID << " Successfully checked out book with barcode "<< barcode << " and the DueDate is: " << ctime(&NEW_dueDate);  
    return true;
    
}

/*      function to return a book       */
bool Member::returnBook(Library &lib, const string &barcode)
{
    return lib.returnBook(memberID, barcode);
}

/*      function to reserve a book      */
bool Member::reserveBook(Library &lib, const string &barcode)
{
    return lib.reserveBook(memberID, barcode);
}

/*      function to renew a book    */
bool Member::renewBook(Library &lib, const string &barcode)
{
    return lib.renewBook(memberID, barcode);
}



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


/*      Library Class Methods   */
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
    // Now we need to delete this book from the member's checked out books
    members[memberID].checkedOutbooks_MAP.erase(barcode);
    // Here we notify all observers that want this book
    notifyObservers(barcode);
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

/*          function to renew the subscription of a book with additional 10 days       */
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

/*      Function to search a book into the catalog      */
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

/*              MAIN APPLICATION FOR TEST               */
int main()
{
    // Initialize library and librarian
    Library lib;
    Librarian librarian("Alice Johnson", "EMP001");

    // Add books to the library
    BookItem book1("George Orwell", "1984", "Dystopian", "1949", "B001", "BC001", true, 1);
    BookItem book2("J.R.R. Tolkien", "The Hobbit", "Fantasy", "1937", "B002", "BC002", true, 1);
    librarian.addBook(lib, book1);
    librarian.addBook(lib, book2);

    // Register members
    Member member1("John Doe", "M001", "john.doe@example.com", "1234567890");
    Member member2("Jane Smith", "M002", "jane.smith@example.com", "0987654321");
    lib.registerMember(member1);
    lib.registerMember(member2);

    // Member 1 checks out a book
    member1.checkoutBook(lib, "BC001");

    // Fast forward time by 12 days to simulate overdue
    time_t currentTime = time(0) + 12 * 24 * 60 * 60;
    time_t originalTime = time(0); // Store original time

    // Simulate time change (this is conceptual; actual implementation may vary)
    // Note: Manipulating system time is not recommended; use mocks or dependency injection for testing

    // Member 1 returns the book (overdue)
    member1.returnBook(lib, "BC001");

    // Check member's fine balance
    cout << "Member " << member1.getMemberID() << " has an outstanding fine of $" << member1.getFineBalance() << endl;

    // Member 1 attempts to checkout another book without paying fine
    member1.checkoutBook(lib, "BC002"); // Should fail due to outstanding fine

    // Member 1 pays the fine
    member1.processFinePayment(member1, member1.getFineBalance()); // Pays full fine

    // Member 1 attempts to checkout another book after paying fine
    member1.checkoutBook(lib, "BC002"); // Should succeed


    /*
    Library lib;
    Librarian librarian("Moamen", "EMP101");

    BookItem book1("Bjarne Stroustrup", "C++ Programming", "Programming", "1997", "B001", "BC001", true ,1);
    librarian.addBook(lib, book1);

    Member member("Moamen Nasser", "M001", "nasermoamenaz20@gmail.com", "01112864312");
    lib.registerMember(member);

    // Member subscribes to notifications about the book
    lib.addObserver("BC001", &member);

    // Check out and return the book, triggering notifications
    member.checkoutBook(lib, "BC001");
    member.returnBook(lib, "BC001");
    */


    /*
    Library lib;
    Librarian librarian("Moamen", "EMP101");
//BookItem(string a, string t, string s, string Date, string id, string code, bool in, int number) : Book(a, t, s, Date, id), Barcode(code), rackNumber(number), InStock(true){}

    BookItem book1("Bjarne Stroustrup", "C++ Programming", "Programming", "1997", "B001", "BC001", true ,1);
    BookItem book2("TEST Stroustrup", "C Programming", "Programming", "1870", "B002", "BC002",true, 2);
    BookItem book3("Bjarne Stroustrup", "JAVA Programming", "Programming", "1997", "B003", "BC003",true, 3);
    BookItem book4("Bjarne Stroustrup", "GO Programming",  "Programming", "1997", "B004", "BC004",true, 4);
    BookItem book5( "Bjarne Stroustrup", "JS Programming","Programming", "1997", "B005", "BC005",true, 5);

    librarian.addBook(lib, book1);
    librarian.addBook(lib, book2);
    librarian.addBook(lib, book3);
    librarian.addBook(lib, book4);
    librarian.addBook(lib, book5);

    Member member("Moamen Nasser", "M001");
    lib.registerMember(member);
    member.checkoutBook(lib, "M001");
    cout << "\nTEST \n";
    member.checkoutBook(lib, "BC001");
    member.checkoutBook(lib, "BC002");

    member.searchForAbook(lib,"", "C++ Programming", "", "");
    member.searchForAbook(lib,"", "C Programming", "", "");

    //member.returnBook(lib, "BC001");
    //member.returnBook(lib, "BC002");

    lib.overdueCheck();
    */
    return 0;
}
