#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Movie.h"
#include "Screen.h"
#include "Customer.h"
#include "Ticket.h"

class FileManager {
private:
    std::string moviesFilePath;
    std::string screensFilePath;
    std::string customersFilePath;
    std::string ticketsFilePath;

public:
    FileManager(const std::string& dataDir = "Data/");
    ~FileManager();

    // Movies
    bool saveMovies(const std::vector<Movie>& movies);
    bool loadMovies(std::vector<Movie>& movies);

    // Screens
    bool saveScreens(const std::vector<Screen>& screens);
    bool loadScreens(std::vector<Screen>& screens);

    // Customers (Polymorphic Customer* pointers)
    bool saveCustomers(const std::vector<Customer*>& customers);
    bool loadCustomers(std::vector<Customer*>& customers);

    // Tickets (Dynamic array or vector)
    bool saveTickets(Ticket** tickets, int ticketCount);
    bool loadTickets(Ticket**& tickets, int& ticketCount, int& capacity);
};

#endif // FILEMANAGER_H
