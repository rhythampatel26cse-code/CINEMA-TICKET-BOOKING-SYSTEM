#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

// Base Abstract Class demonstrating Inheritance and Runtime Polymorphism
class Customer {
protected:
    int customerId;
    std::string name;
    std::string phone;

public:
    // Constructors & Virtual Destructor
    Customer();
    Customer(int id, const std::string& name, const std::string& phone);
    virtual ~Customer();

    // Getters
    int getCustomerId() const;
    std::string getName() const;
    std::string getPhone() const;

    // Pure virtual functions (Runtime Polymorphism)
    virtual double calculateDiscount(double originalAmount) const = 0;
    virtual std::string getCustomerType() const = 0;

    // Virtual display and serialization
    virtual void displayCustomer() const;
    virtual std::string serialize() const = 0;
};

// Derived Class 1: Regular Customer
class RegularCustomer : public Customer {
public:
    RegularCustomer();
    RegularCustomer(int id, const std::string& name, const std::string& phone);
    virtual ~RegularCustomer();

    double calculateDiscount(double originalAmount) const override;
    std::string getCustomerType() const override;
    std::string serialize() const override;
};

// Derived Class 2: VIP Customer (Special loyalty discount)
class VIPCustomer : public Customer {
private:
    int loyaltyPoints;

public:
    VIPCustomer();
    VIPCustomer(int id, const std::string& name, const std::string& phone, int points = 100);
    virtual ~VIPCustomer();

    int getLoyaltyPoints() const;
    void addLoyaltyPoints(int pts);

    double calculateDiscount(double originalAmount) const override; // 20% discount
    std::string getCustomerType() const override;
    void displayCustomer() const override;
    std::string serialize() const override;
};

// Derived Class 3: Student / Senior Citizen Customer (Concession discount)
class StudentCustomer : public Customer {
private:
    std::string studentIdCard;

public:
    StudentCustomer();
    StudentCustomer(int id, const std::string& name, const std::string& phone, const std::string& studentCard);
    virtual ~StudentCustomer();

    std::string getStudentIdCard() const;

    double calculateDiscount(double originalAmount) const override; // 10% discount
    std::string getCustomerType() const override;
    void displayCustomer() const override;
    std::string serialize() const override;
};

#endif // CUSTOMER_H
