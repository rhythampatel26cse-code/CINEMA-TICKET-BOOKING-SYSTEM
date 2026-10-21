#include "Customer.h"
#include <iomanip>
#include <sstream>

// Base Class Implementation
Customer::Customer() : customerId(0), name("Unknown"), phone("0000000000") {}
Customer::Customer(int id, const std::string& name, const std::string& phone)
    : customerId(id), name(name), phone(phone) {}
Customer::~Customer() {}

int Customer::getCustomerId() const { return customerId; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }

void Customer::displayCustomer() const {
    std::cout << "  ID: " << std::setw(3) << std::left << customerId
              << " | Name: " << std::setw(18) << std::left << name
              << " | Phone: " << std::setw(12) << std::left << phone
              << " | Type: " << std::setw(10) << std::left << getCustomerType() << "\n";
}

// RegularCustomer Implementation
RegularCustomer::RegularCustomer() : Customer() {}
RegularCustomer::RegularCustomer(int id, const std::string& name, const std::string& phone)
    : Customer(id, name, phone) {}
RegularCustomer::~RegularCustomer() {}

double RegularCustomer::calculateDiscount(double /*originalAmount*/) const {
    return 0.0; // Standard price, no discount
}

std::string RegularCustomer::getCustomerType() const {
    return "REGULAR";
}

std::string RegularCustomer::serialize() const {
    std::ostringstream oss;
    oss << "REGULAR|" << customerId << "|" << name << "|" << phone;
    return oss.str();
}

// VIPCustomer Implementation
VIPCustomer::VIPCustomer() : Customer(), loyaltyPoints(100) {}
VIPCustomer::VIPCustomer(int id, const std::string& name, const std::string& phone, int points)
    : Customer(id, name, phone), loyaltyPoints(points) {}
VIPCustomer::~VIPCustomer() {}

int VIPCustomer::getLoyaltyPoints() const { return loyaltyPoints; }
void VIPCustomer::addLoyaltyPoints(int pts) { loyaltyPoints += pts; }

double VIPCustomer::calculateDiscount(double originalAmount) const {
    // 20% discount for VIP Customers
    return originalAmount * 0.20;
}

std::string VIPCustomer::getCustomerType() const {
    return "VIP";
}

void VIPCustomer::displayCustomer() const {
    std::cout << "  ID: " << std::setw(3) << std::left << customerId
              << " | Name: " << std::setw(18) << std::left << name
              << " | Phone: " << std::setw(12) << std::left << phone
              << " | Type: " << std::setw(10) << std::left << getCustomerType()
              << " | Points: " << loyaltyPoints << " (20% Off)\n";
}

std::string VIPCustomer::serialize() const {
    std::ostringstream oss;
    oss << "VIP|" << customerId << "|" << name << "|" << phone << "|" << loyaltyPoints;
    return oss.str();
}

// StudentCustomer Implementation
StudentCustomer::StudentCustomer() : Customer(), studentIdCard("STU-000") {}
StudentCustomer::StudentCustomer(int id, const std::string& name, const std::string& phone, const std::string& studentCard)
    : Customer(id, name, phone), studentIdCard(studentCard) {}
StudentCustomer::~StudentCustomer() {}

std::string StudentCustomer::getStudentIdCard() const { return studentIdCard; }

double StudentCustomer::calculateDiscount(double originalAmount) const {
    // 10% discount for Students
    return originalAmount * 0.10;
}

std::string StudentCustomer::getCustomerType() const {
    return "STUDENT";
}

void StudentCustomer::displayCustomer() const {
    std::cout << "  ID: " << std::setw(3) << std::left << customerId
              << " | Name: " << std::setw(18) << std::left << name
              << " | Phone: " << std::setw(12) << std::left << phone
              << " | Type: " << std::setw(10) << std::left << getCustomerType()
              << " | Card: " << studentIdCard << " (10% Off)\n";
}

std::string StudentCustomer::serialize() const {
    std::ostringstream oss;
    oss << "STUDENT|" << customerId << "|" << name << "|" << phone << "|" << studentIdCard;
    return oss.str();
}
