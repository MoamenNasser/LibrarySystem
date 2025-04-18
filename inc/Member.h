/*
 * Member.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef MEMBER_H_
#define MEMBER_H_

#include "NotificationService.h"
#incluude "Observer.h"
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
        Member();
        // Constructor with name and ID (no defaults to avoid ambiguity)
        Member(const std::string &n, const std::string &id);


        // Constructor with all parameters
        Member(const std::string &n, const std::string &id, const std::string &mail, const std::string &phone);
        // Now I need getters and setters to control the data
        string getEmail()const;
        // function to return the phone number of the member
        string getPhoneNumber()const;
        // function to return the name of the member
        string getName() const;
        // function to return the member ID
        string getMemberID() const;

        // setters methods
        void setEmail(const string &new_mail);
        // function to set the phone number to the member
        void setPhoneNumber(const string &new_phone);
        // function to process the fine payment
        void processFinePayment(Member &member, double amount) ;

        // function to add fine to the member
        void addFine(double amount);
        // function to pay the fine
        bool payFine(double amount);

        // function to return the fine balance
        double getFineBalance()const;

        // function to check the ability to checkout more books (Limit is 5)
        bool canCheckoutMoreBooks();
        // function to check the ability to reserve books more books (Limit is 5)
        bool canReserveBook();

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
        void update(const std::string &message) override;

};






#endif /* MEMBER_H_ */
