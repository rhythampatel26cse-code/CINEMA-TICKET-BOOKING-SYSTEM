#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <iostream>

class Ticket {
private:
    int ticketId;
    int movieId;
    std::string movieTitle;
    int screenId;
    std::string seatCode; // e.g. "B3"
    int customerId;
    std::string customerName;
    std::string customerType;
    double originalPrice;
    double discountAmount;
    double finalPrice;
    std::string bookingDate;

public:
    // Constructors & Destructor
    Ticket();
    Ticket(int tId, int mId, const std::string& mTitle, int sId, 
           const std::string& seat, int cId, const std::string& cName, 
           const std::string& cType, double origPrice, double discount, 
           double finalP, const std::string& date);
    ~Ticket();

    // Getters
    int getTicketId() const;
    int getMovieId() const;
    std::string getMovieTitle() const;
    int getScreenId() const;
    std::string getSeatCode() const;
    int getCustomerId() const;
    std::string getCustomerName() const;
    std::string getCustomerType() const;
    double getOriginalPrice() const;
    double getDiscountAmount() const;
    double getFinalPrice() const;
    std::string getBookingDate() const;

    // Display
    void displayTicketCard() const;
    void displaySummary() const;

    // Serialization
    std::string serialize() const;
    static Ticket deserialize(const std::string& line);
};

#endif // TICKET_H
