/*
 * Member.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */





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
        Member(const std::string &n, const std::string &id)
            : name(n), memberID(id), Email(""), PhoneNumber(""), fineBalance(0.0) {}

        // Constructor with all parameters
        Member(const std::string &n, const std::string &id, const std::string &mail, const std::string &phone)
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
            fineBalance += amount;
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
        void update(const std::string &message) override
        {
            cout << "Notification for " << name << ": " << message << std::endl;

            // Sending an email and SMS to the member
            NotificationService notificationService;
            notificationService.sendEmail(Email, "Library Notification", message);
            notificationService.sendSMS(PhoneNumber, message);
        }

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
