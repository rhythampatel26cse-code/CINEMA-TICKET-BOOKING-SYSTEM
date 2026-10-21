#include "Ticket.h"
#include <iomanip>
#include <sstream>
#include <vector>

Ticket::Ticket()
    : ticketId(0), movieId(0), movieTitle("N/A"), screenId(0), seatCode("A1"),
      customerId(0), customerName("Guest"), customerType("REGULAR"),
      originalPrice(0.0), discountAmount(0.0), finalPrice(0.0), bookingDate("2026-10-13") {}

Ticket::Ticket(int tId, int mId, const std::string& mTitle, int sId, 
               const std::string& seat, int cId, const std::string& cName, 
               const std::string& cType, double origPrice, double discount, 
               double finalP, const std::string& date)
    : ticketId(tId), movieId(mId), movieTitle(mTitle), screenId(sId), seatCode(seat),
      customerId(cId), customerName(cName), customerType(cType),
      originalPrice(origPrice), discountAmount(discount), finalPrice(finalP), bookingDate(date) {}

Ticket::~Ticket() {}

int Ticket::getTicketId() const { return ticketId; }
int Ticket::getMovieId() const { return movieId; }
std::string Ticket::getMovieTitle() const { return movieTitle; }
int Ticket::getScreenId() const { return screenId; }
std::string Ticket::getSeatCode() const { return seatCode; }
int Ticket::getCustomerId() const { return customerId; }
std::string Ticket::getCustomerName() const { return customerName; }
std::string Ticket::getCustomerType() const { return customerType; }
double Ticket::getOriginalPrice() const { return originalPrice; }
double Ticket::getDiscountAmount() const { return discountAmount; }
double Ticket::getFinalPrice() const { return finalPrice; }
std::string Ticket::getBookingDate() const { return bookingDate; }

void Ticket::displayTicketCard() const {
    std::cout << "\n  +--------------------------------------------------------------+\n";
    std::cout << "  |                   CINEMA BOOKING RECEIPT                     |\n";
    std::cout << "  |             CINEMA TICKET BOOKING SYSTEM - CPP80             |\n";
    std::cout << "  +--------------------------------------------------------------+\n";
    std::cout << "  |  Ticket Number : #" << std::setw(6) << std::left << ticketId 
              << "       Date: " << std::setw(12) << std::left << bookingDate << "       |\n";
    std::cout << "  |  Movie Title   : " << std::setw(42) << std::left << movieTitle << "|\n";
    std::cout << "  |  Auditorium    : Screen " << std::setw(3) << std::left << screenId
              << "          Seat Reserved : " << std::setw(13) << std::left << seatCode << "|\n";
    std::cout << "  |  Customer Name : " << std::setw(20) << std::left << customerName 
              << "Category: " << std::setw(15) << std::left << customerType << "|\n";
    std::cout << "  +--------------------------------------------------------------+\n";
    std::cout << "  |  Base Price    : $" << std::setw(8) << std::fixed << std::setprecision(2) << originalPrice 
              << "                                         |\n";
    std::cout << "  |  Discount      : -$" << std::setw(7) << discountAmount 
              << "                                         |\n";
    std::cout << "  |  TOTAL PAID    : $" << std::setw(8) << finalPrice 
              << "   [ PAYMENT SUCCESSFUL ]               |\n";
    std::cout << "  +--------------------------------------------------------------+\n\n";
}

void Ticket::displaySummary() const {
    std::cout << "  Ticket #" << std::setw(4) << std::left << ticketId
              << " | Movie: " << std::setw(20) << std::left << movieTitle
              << " | Screen: " << std::setw(2) << screenId
              << " | Seat: " << std::setw(3) << seatCode
              << " | Customer: " << std::setw(14) << std::left << customerName
              << " | Paid: $" << std::fixed << std::setprecision(2) << finalPrice << "\n";
}

std::string Ticket::serialize() const {
    std::ostringstream oss;
    oss << ticketId << "|" << movieId << "|" << movieTitle << "|"
        << screenId << "|" << seatCode << "|" << customerId << "|"
        << customerName << "|" << customerType << "|" << originalPrice << "|"
        << discountAmount << "|" << finalPrice << "|" << bookingDate;
    return oss.str();
}

Ticket Ticket::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    if (tokens.size() >= 12) {
        int tId = std::stoi(tokens[0]);
        int mId = std::stoi(tokens[1]);
        std::string mTitle = tokens[2];
        int sId = std::stoi(tokens[3]);
        std::string seat = tokens[4];
        int cId = std::stoi(tokens[5]);
        std::string cName = tokens[6];
        std::string cType = tokens[7];
        double origPrice = std::stod(tokens[8]);
        double disc = std::stod(tokens[9]);
        double finalP = std::stod(tokens[10]);
        std::string date = tokens[11];
        return Ticket(tId, mId, mTitle, sId, seat, cId, cName, cType, origPrice, disc, finalP, date);
    }
    return Ticket();
}
