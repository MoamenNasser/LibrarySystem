/*
 * NotificationService.cpp
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */




/*          class for the notification Service      */
#include "NotificationService.h"
// function to notify that the book is available or not
void NotificationService::notifyAvailability(const string &memberID, const string &bookBarcode)
{
    cout << "Notification bar: Book with barcode: " << bookBarcode << " is now available for member " << memberID << endl;
}
// function to notify the overdue
void NotificationService::notifyOverdue(const string &memberID, const string &bookBarcode)
{
    cout << "Notification Bar: Book with barcode " << bookBarcode << " is overdue for that member " << memberID<<endl;
}

// function to send an email to the member
void NotificationService::sendEmail(const string &email, const string &subject, const string &body)
{
    cout << "Sending Email to : " << email << "\nSubject: " << subject << "\nBody: "<< body << "\n";
}

//function to send a SMS message to the according phone number
void NotificationService::sendSMS(const string &number, const string &message)
{
    cout << "Sending SMS to: " << number << "\nMessage: "<<message <<"\n";
}
