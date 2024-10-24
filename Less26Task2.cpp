#include <iostream>
#include <vector>
#include <string>

class PhoneNumber {
private:
    std::string number;

public:
    void setNumber(std::string cNumber) {
        bool itNum{ true };
        if (cNumber.length() == 10 && cNumber[0] == '+') {
            for (int i{ 1 }; i < 10; i++) {
                if (cNumber[i] < '0' || cNumber[i] > '9') itNum = { false };
            }
        }
        else {
            std::cout << "inncorrect phone num\n";
            return;
        }
        if (itNum) {
            number = { cNumber };
        }
        else {
            std::cout << "inncorrect phone num\n";
        }

    }
    std::string getNumber() {
        return number;
    }
};

class Contact {
private:
    std::string name;
    PhoneNumber phoneNumber;

public:
    void setName(std::string &cSetName) {
        name = { cSetName };
    }

    void setPhoneNum(PhoneNumber &PhoneNum4set) { 
        phoneNumber = { PhoneNum4set };
    }

    std::string getName() {
        return name;
    }

    PhoneNumber getPhoneNumber() {
        return phoneNumber;
    }
};


class PhoneBook {
private:
    std::vector<Contact> vecContacts;

public:
    void addContact(Contact &newContact) {       
        vecContacts.push_back(newContact);                   
    }

    Contact* findContactByName(std::string& name) {
        for (auto& contact : vecContacts) {
            if (contact.getName() == name) {
                return &contact;
            }
        }
        return nullptr;
    }

    Contact* findContactByPhone(PhoneNumber& phone) {
        for (auto& contact : vecContacts) {
            if (contact.getPhoneNumber().getNumber() == phone.getNumber()) {
                return &contact;
            }
        }
        return nullptr;
    }
};

class MobilePhone {
private:
    PhoneBook phoneBook;

public:
    void addContact() {
        std::string name, number;
        std::cout << "Enter contact name: ";
        std::getline(std::cin, name);
        std::cout << "Enter phone number: ";
        std::getline(std::cin, number);
        
        Contact newContact;

        PhoneNumber phone;
        phone.setNumber(number);
        newContact.setPhoneNum(phone);
        newContact.setName(name);

        phoneBook.addContact(newContact);          
        std::cout << "Contact added!\n";
        
    }

    void call() {
        std::string input;
        std::cout << "Enter contact name or phone number: ";
        std::getline(std::cin, input);
        Contact* contact;
        contact = phoneBook.findContactByName(input);
        if (!contact) {
            
            PhoneNumber phone;
            phone.setNumber(input);
            contact = phoneBook.findContactByPhone(phone);
            //if error
            //    std::cout << "Invalid phone number format.\n";
            //    return;
            
        }

        if (contact) {
            std::cout << "CALL " << contact->getPhoneNumber().getNumber() << std::endl;
        }
        else {
            std::cout << "Contact not found.\n";
        }
    }
    void sms() {
        std::string input, message;
        std::cout << "Enter contact name or phone number: ";
        std::getline(std::cin, input);
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);

        Contact* contact = phoneBook.findContactByName(input);
        if (!contact) {
            
            PhoneNumber phone;
            phone.setNumber(input);
            contact = phoneBook.findContactByPhone(phone);
            
            //if error
            //    std::cout << "Invalid phone number format.\n";
            //    return;
            
        }

        if (contact) {
            std::cout << "SMS to " << contact->getPhoneNumber().getNumber() << ": " << message << '\n';
        }
        else {
            std::cout << "Contact not found.\n";
        }
    }
};

int main() {
    MobilePhone phone;
    std::string command;

    while (true) {
        std::cout << "Enter command (add, call, sms, exit): ";
        std::getline(std::cin, command);

        if (command == "add") {
            phone.addContact();
        }
        else if (command == "call") {
            phone.call();
        }
        else if (command == "sms") {
            phone.sms();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}