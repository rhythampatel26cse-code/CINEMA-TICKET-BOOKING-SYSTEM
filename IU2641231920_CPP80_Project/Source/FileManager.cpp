#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

FileManager::FileManager(const std::string& dataDir) {
    moviesFilePath = dataDir + "movies.txt";
    screensFilePath = dataDir + "screens.txt";
    customersFilePath = dataDir + "customers.txt";
    ticketsFilePath = dataDir + "tickets.txt";
}

FileManager::~FileManager() {}

bool FileManager::saveMovies(const std::vector<Movie>& movies) {
    std::ofstream outFile(moviesFilePath);
    if (!outFile.is_open()) {
        std::cerr << "  [Error] Unable to open " << moviesFilePath << " for writing.\n";
        return false;
    }
    for (const auto& m : movies) {
        outFile << m.serialize() << "\n";
    }
    outFile.close();
    return true;
}

bool FileManager::loadMovies(std::vector<Movie>& movies) {
    std::ifstream inFile(moviesFilePath);
    if (!inFile.is_open()) {
        return false;
    }
    movies.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            movies.push_back(Movie::deserialize(line));
        }
    }
    inFile.close();
    return true;
}

bool FileManager::saveScreens(const std::vector<Screen>& screens) {
    std::ofstream outFile(screensFilePath);
    if (!outFile.is_open()) {
        std::cerr << "  [Error] Unable to open " << screensFilePath << " for writing.\n";
        return false;
    }
    for (const auto& s : screens) {
        outFile << s.serialize() << "\n";
    }
    outFile.close();
    return true;
}

bool FileManager::loadScreens(std::vector<Screen>& screens) {
    std::ifstream inFile(screensFilePath);
    if (!inFile.is_open()) {
        return false;
    }
    screens.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            screens.push_back(Screen::deserialize(line));
        }
    }
    inFile.close();
    return true;
}

bool FileManager::saveCustomers(const std::vector<Customer*>& customers) {
    std::ofstream outFile(customersFilePath);
    if (!outFile.is_open()) {
        std::cerr << "  [Error] Unable to open " << customersFilePath << " for writing.\n";
        return false;
    }
    for (const auto* c : customers) {
        if (c != nullptr) {
            outFile << c->serialize() << "\n";
        }
    }
    outFile.close();
    return true;
}

bool FileManager::loadCustomers(std::vector<Customer*>& customers) {
    std::ifstream inFile(customersFilePath);
    if (!inFile.is_open()) {
        return false;
    }
    // Clean old dynamic objects
    for (auto* c : customers) {
        delete c;
    }
    customers.clear();

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 4) {
            std::string type = tokens[0];
            int id = std::stoi(tokens[1]);
            std::string name = tokens[2];
            std::string phone = tokens[3];

            if (type == "REGULAR") {
                customers.push_back(new RegularCustomer(id, name, phone));
            } else if (type == "VIP") {
                int points = (tokens.size() >= 5) ? std::stoi(tokens[4]) : 100;
                customers.push_back(new VIPCustomer(id, name, phone, points));
            } else if (type == "STUDENT") {
                std::string card = (tokens.size() >= 5) ? tokens[4] : "STU-GEN";
                customers.push_back(new StudentCustomer(id, name, phone, card));
            }
        }
    }
    inFile.close();
    return true;
}

bool FileManager::saveTickets(Ticket** tickets, int ticketCount) {
    std::ofstream outFile(ticketsFilePath);
    if (!outFile.is_open()) {
        std::cerr << "  [Error] Unable to open " << ticketsFilePath << " for writing.\n";
        return false;
    }
    for (int i = 0; i < ticketCount; ++i) {
        if (tickets[i] != nullptr) {
            outFile << tickets[i]->serialize() << "\n";
        }
    }
    outFile.close();
    return true;
}

bool FileManager::loadTickets(Ticket**& tickets, int& ticketCount, int& capacity) {
    std::ifstream inFile(ticketsFilePath);
    if (!inFile.is_open()) {
        return false;
    }
    // Clean old tickets
    for (int i = 0; i < ticketCount; ++i) {
        delete tickets[i];
    }
    ticketCount = 0;

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        Ticket t = Ticket::deserialize(line);
        // Expand dynamic array if needed
        if (ticketCount >= capacity) {
            int newCap = (capacity == 0) ? 10 : capacity * 2;
            Ticket** newArr = new Ticket*[newCap];
            for (int i = 0; i < ticketCount; ++i) {
                newArr[i] = tickets[i];
            }
            delete[] tickets;
            tickets = newArr;
            capacity = newCap;
        }
        tickets[ticketCount++] = new Ticket(t);
    }
    inFile.close();
    return true;
}
