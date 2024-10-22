#include <iostream>
#include <vector>
#include <string>

class PhoneNumber {
private:
    std::string number;

public:
    void setNumber(std::string cNumber) {
        number = {cNumber};
    }
    std::string getNumber() const {
        return number;
    }
};

class Contact {
private:
    std::string name;
    PhoneNumber phoneNumber;

public:
    std::string getName() const {
        return name;
    }

    PhoneNumber getPhoneNumber() const {
        return phoneNumber;
    }
};


class PhoneBook {
private:
    std::vector<Contact> contacts;

public:
    void addContact(const std::string& name, const PhoneNumber& phone) {
        contacts.emplace_back(name, phone);
    }

    Contact* findContactByName(const std::string& name) {
        for (auto& contact : contacts) {
            if (contact.getName() == name) {
                return &contact;
            }
        }
        return nullptr;
    }

    Contact* findContactByPhone(const PhoneNumber& phone) {
        for (auto& contact : contacts) {
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
        try {
            PhoneNumber phone(number);
            phoneBook.addContact(name, phone);
            std::cout << "Contact added!\n";
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << "\n";
        }
    }

    void call() {
        std::string input;
        std::cout << "Enter contact name or phone number: ";
        std::getline(std::cin, input);
        Contact* contact = phoneBook.findContactByName(input);
        if (!contact) {
            try {
                PhoneNumber phone(input);
                contact = phoneBook.findContactByPhone(phone);
            }
            catch (const std::invalid_argument&) {
                std::cout << "Invalid phone number format.\n";
                return;
            }
        }

        if (contact) {
            std::cout << "CALL " << contact->getPhoneNumber().getNumber() << '\n';
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
            try {
                PhoneNumber phone(input);
                contact = phoneBook.findContactByPhone(phone);
            }
            catch (const std::invalid_argument&) {
                std::cout << "Invalid phone number format.\n";
                return;
            }
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