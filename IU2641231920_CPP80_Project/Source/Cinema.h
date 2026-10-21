#ifndef CINEMA_H
#define CINEMA_H

#include <vector>
#include <string>
#include "Movie.h"
#include "Screen.h"
#include "Customer.h"
#include "Ticket.h"
#include "FileManager.h"

class Cinema {
private:
    std::string cinemaName;
    std::vector<Movie> movies;
    std::vector<Screen> screens;
    std::vector<Customer*> customers; // Polymorphic collection of Customer pointers

    // Dynamic memory management for Tickets (Satisfies Entity* items = new Entity[capacity])
    Ticket** tickets;
    int ticketCount;
    int ticketCapacity;

    FileManager fileManager;
    int nextTicketId;

    // Helper functions for dynamic memory
    void allocateTicketArray(int capacity);
    void expandTicketArray();
    void clearTickets();

    // Helper search methods
    Movie* findMovieById(int id);
    Screen* findScreenById(int id);
    Customer* findCustomerById(int id);
    Customer* findCustomerByPhone(const std::string& phone);

    // Initial sample seed data
    void seedInitialData();

public:
    Cinema(const std::string& name = "CineStar Grand Multiplex");
    ~Cinema();

    // Core 9 Operations specified in Blueprint
    void addRecord();
    void displayRecords() const;
    void searchRecord() const;
    void updateRecord();
    void deleteRecord();
    void processMainTransaction(); // Main Ticket Booking Process
    void generateReport() const;
    void handleSaveLoad();
    void exitSystem();

    // Persistence wrappers
    void loadAllData();
    void saveAllData();
};

#endif // CINEMA_H
