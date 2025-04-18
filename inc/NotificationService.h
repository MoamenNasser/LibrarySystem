/*
 * NotificationService.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Moamen
 */

#ifndef NOTIFICATIONSERVICE_H_
#define NOTIFICATIONSERVICE_H_

#include <iostream>
#include <string>
/*          class for the notification Service      */
class NotificationService
{
    public:
        // function to notify that the book is available or not
        void notifyAvailability(const string &memberID, const string &bookBarcode);
        // function to notify the overdue
        void notifyOverdue(const string &memberID, const string &bookBarcode);

        // function to send an email to the member
        void sendEmail(const string &email, const string &subject, const string &body);

        //function to send a SMS message to the according phone number
        void sendSMS(const string &number, const string &message);
};



#endif /* NOTIFICATIONSERVICE_H_ */
