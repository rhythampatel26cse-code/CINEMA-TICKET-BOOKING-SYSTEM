#include "Cinema.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

// Dynamic Memory Management for Tickets
void Cinema::allocateTicketArray(int capacity) {
    ticketCapacity = capacity;
    ticketCount = 0;
    tickets = new Ticket*[ticketCapacity];
    for (int i = 0; i < ticketCapacity; ++i) {
        tickets[i] = nullptr;
    }
}

void Cinema::expandTicketArray() {
    int newCapacity = ticketCapacity * 2;
    Ticket** newTickets = new Ticket*[newCapacity];
    for (int i = 0; i < ticketCount; ++i) {
        newTickets[i] = tickets[i];
    }
    for (int i = ticketCount; i < newCapacity; ++i) {
        newTickets[i] = nullptr;
    }
    delete[] tickets;
    tickets = newTickets;
    ticketCapacity = newCapacity;
}

void Cinema::clearTickets() {
    if (tickets != nullptr) {
        for (int i = 0; i < ticketCount; ++i) {
            delete tickets[i];
            tickets[i] = nullptr;
        }
        delete[] tickets;
        tickets = nullptr;
    }
    ticketCount = 0;
    ticketCapacity = 0;
}

Cinema::Cinema(const std::string& name) 
    : cinemaName(name), tickets(nullptr), ticketCount(0), ticketCapacity(0), nextTicketId(1001) {
    allocateTicketArray(20);
    loadAllData();
    if (movies.empty()) {
        seedInitialData();
        saveAllData();
    }
}

Cinema::~Cinema() {
    // Release dynamic polymorphic customers
    for (auto* c : customers) {
        delete c;
    }
    customers.clear();

    // Release dynamic tickets array
    clearTickets();
}

void Cinema::seedInitialData() {
    // Initial default Movies
    movies.push_back(Movie(101, "Interstellar Odyssey", "Sci-Fi", 169, "PG-13", 14.50));
    movies.push_back(Movie(102, "Shadows of Gotham", "Action", 140, "PG-13", 13.00));
    movies.push_back(Movie(103, "The Enchanted Forest", "Animation", 102, "U", 10.00));
    movies.push_back(Movie(104, "Midnight Echoes", "Thriller", 125, "R", 12.50));

    // Initial default Screens
    screens.push_back(Screen(1, "IMAX Grand", 5, 6)); // 30 seats
    screens.push_back(Screen(2, "Dolby Atmos 1", 4, 5)); // 20 seats
    screens.push_back(Screen(3, "Classic Cinema", 4, 4)); // 16 seats

    // Initial default Customers (Polymorphic instances)
    customers.push_back(new RegularCustomer(1, "John Doe", "9876543210"));
    customers.push_back(new VIPCustomer(2, "Sarah Connor", "9123456780", 250));
    customers.push_back(new StudentCustomer(3, "Alex Smith", "9988776655", "STU-8821"));
}

Movie* Cinema::findMovieById(int id) {
    for (auto& m : movies) {
        if (m.getMovieId() == id) return &m;
    }
    return nullptr;
}

Screen* Cinema::findScreenById(int id) {
    for (auto& s : screens) {
        if (s.getScreenId() == id) return &s;
    }
    return nullptr;
}

Customer* Cinema::findCustomerById(int id) {
    for (auto* c : customers) {
        if (c->getCustomerId() == id) return c;
    }
    return nullptr;
}

Customer* Cinema::findCustomerByPhone(const std::string& phone) {
    for (auto* c : customers) {
        if (c->getPhone() == phone) return c;
    }
    return nullptr;
}

// 1. ADD RECORD
void Cinema::addRecord() {
    std::cout << "\n  --- [ ADD RECORD MENU ] ---\n";
    std::cout << "  1. Add New Movie\n";
    std::cout << "  2. Add New Screen\n";
    std::cout << "  3. Register New Customer\n";
    std::cout << "  Select option (1-3): ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [Invalid Input]\n";
        return;
    }

    if (choice == 1) {
        int id, dur;
        std::string title, genre, rating;
        double price;
        std::cout << "  Enter Movie ID: ";
        std::cin >> id;
        std::cin.ignore();
        if (findMovieById(id) != nullptr) {
            std::cout << "  [Error] Movie ID already exists!\n";
            return;
        }
        std::cout << "  Enter Movie Title: ";
        std::getline(std::cin, title);
        std::cout << "  Enter Genre: ";
        std::getline(std::cin, genre);
        std::cout << "  Enter Duration (mins): ";
        std::cin >> dur;
        std::cout << "  Enter Rating (U / PG-13 / R): ";
        std::cin >> rating;
        std::cout << "  Enter Base Ticket Price ($): ";
        std::cin >> price;

        movies.push_back(Movie(id, title, genre, dur, rating, price));
        std::cout << "  [Success] Movie '" << title << "' added successfully!\n";
    } else if (choice == 2) {
        int id, rows, cols;
        std::string name;
        std::cout << "  Enter Screen ID: ";
        std::cin >> id;
        std::cin.ignore();
        if (findScreenById(id) != nullptr) {
            std::cout << "  [Error] Screen ID already exists!\n";
            return;
        }
        std::cout << "  Enter Screen Name: ";
        std::getline(std::cin, name);
        std::cout << "  Enter Number of Rows (max 8): ";
        std::cin >> rows;
        if (rows > 8) rows = 8;
        std::cout << "  Enter Number of Columns (max 8): ";
        std::cin >> cols;
        if (cols > 8) cols = 8;

        screens.push_back(Screen(id, name, rows, cols));
        std::cout << "  [Success] Screen '" << name << "' created with " << (rows * cols) << " seats!\n";
    } else if (choice == 3) {
        int id, type;
        std::string name, phone;
        std::cout << "  Enter Customer ID: ";
        std::cin >> id;
        std::cin.ignore();
        if (findCustomerById(id) != nullptr) {
            std::cout << "  [Error] Customer ID already exists!\n";
            return;
        }
        std::cout << "  Enter Customer Name: ";
        std::getline(std::cin, name);
        std::cout << "  Enter Phone Number: ";
        std::getline(std::cin, phone);
        std::cout << "  Select Customer Category:\n";
        std::cout << "    1. Regular Customer (0% discount)\n";
        std::cout << "    2. VIP Customer (20% discount)\n";
        std::cout << "    3. Student Customer (10% discount)\n";
        std::cout << "  Choice (1-3): ";
        std::cin >> type;

        if (type == 2) {
            customers.push_back(new VIPCustomer(id, name, phone, 150));
            std::cout << "  [Success] VIP Customer registered with 150 bonus points!\n";
        } else if (type == 3) {
            std::string cardId;
            std::cout << "  Enter Student ID Card: ";
            std::cin >> cardId;
            customers.push_back(new StudentCustomer(id, name, phone, cardId));
            std::cout << "  [Success] Student Customer registered!\n";
        } else {
            customers.push_back(new RegularCustomer(id, name, phone));
            std::cout << "  [Success] Regular Customer registered!\n";
        }
    } else {
        std::cout << "  [Invalid choice]\n";
    }
}

// 2. DISPLAY RECORDS
void Cinema::displayRecords() const {
    std::cout << "\n  --- [ DISPLAY RECORDS MENU ] ---\n";
    std::cout << "  1. View All Movies\n";
    std::cout << "  2. View All Screens & Capacities\n";
    std::cout << "  3. View All Registered Customers\n";
    std::cout << "  4. View All Booked Tickets\n";
    std::cout << "  Select option (1-4): ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (choice == 1) {
        std::cout << "\n  ======================= AVAILABLE MOVIES =======================\n";
        for (const auto& m : movies) {
            m.displayDetails();
        }
        std::cout << "  ===============================================================\n";
    } else if (choice == 2) {
        std::cout << "\n  ====================== SCREENS & AUDITORIUMS ===================\n";
        for (const auto& s : screens) {
            s.displaySummary();
        }
        std::cout << "  ===============================================================\n";
    } else if (choice == 3) {
        std::cout << "\n  ===================== REGISTERED CUSTOMERS =====================\n";
        for (const auto* c : customers) {
            c->displayCustomer(); // Polymorphic invocation
        }
        std::cout << "  ===============================================================\n";
    } else if (choice == 4) {
        std::cout << "\n  ====================== BOOKED TICKETS LOG =====================\n";
        if (ticketCount == 0) {
            std::cout << "  No tickets have been booked yet.\n";
        } else {
            for (int i = 0; i < ticketCount; ++i) {
                tickets[i]->displaySummary();
            }
        }
        std::cout << "  ===============================================================\n";
    }
}

// 3. SEARCH RECORD
void Cinema::searchRecord() const {
    std::cout << "\n  --- [ SEARCH RECORD MENU ] ---\n";
    std::cout << "  1. Search Movie (by ID or Title)\n";
    std::cout << "  2. Search Customer (by Phone)\n";
    std::cout << "  3. Search Ticket (by Ticket #)\n";
    std::cout << "  Select option (1-3): ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (choice == 1) {
        std::cout << "  Enter Movie ID to search (or 0 to search by Title): ";
        int id;
        std::cin >> id;
        if (id != 0) {
            bool found = false;
            for (const auto& m : movies) {
                if (m.getMovieId() == id) {
                    std::cout << "\n  [Movie Found]:\n";
                    m.displayDetails();
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "  [Not Found] No movie with ID " << id << ".\n";
        } else {
            std::cout << "  Enter Title keyword: ";
            std::string kw;
            std::cin.ignore();
            std::getline(std::cin, kw);
            bool found = false;
            for (const auto& m : movies) {
                if (m.getTitle().find(kw) != std::string::npos) {
                    m.displayDetails();
                    found = true;
                }
            }
            if (!found) std::cout << "  [Not Found] No movie title matching '" << kw << "'.\n";
        }
    } else if (choice == 2) {
        std::cout << "  Enter Customer Phone Number: ";
        std::string phone;
        std::cin >> phone;
        bool found = false;
        for (const auto* c : customers) {
            if (c->getPhone() == phone) {
                std::cout << "\n  [Customer Found]:\n";
                c->displayCustomer();
                found = true;
                break;
            }
        }
        if (!found) std::cout << "  [Not Found] No customer found with phone " << phone << ".\n";
    } else if (choice == 3) {
        std::cout << "  Enter Ticket ID: #";
        int tId;
        std::cin >> tId;
        bool found = false;
        for (int i = 0; i < ticketCount; ++i) {
            if (tickets[i]->getTicketId() == tId) {
                tickets[i]->displayTicketCard();
                found = true;
                break;
            }
        }
        if (!found) std::cout << "  [Not Found] No ticket found with ID #" << tId << ".\n";
    }
}

// 4. UPDATE RECORD
void Cinema::updateRecord() {
    std::cout << "\n  --- [ UPDATE RECORD MENU ] ---\n";
    std::cout << "  Enter Movie ID to update: ";
    int mId;
    if (!(std::cin >> mId)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    Movie* movie = findMovieById(mId);
    if (movie == nullptr) {
        std::cout << "  [Error] Movie ID " << mId << " not found!\n";
        return;
    }

    std::cout << "  Current Details:\n";
    movie->displayDetails();

    std::cout << "\n  What would you like to update?\n";
    std::cout << "  1. Update Title\n";
    std::cout << "  2. Update Base Ticket Price\n";
    std::cout << "  3. Update Duration & Rating\n";
    std::cout << "  Choice (1-3): ";
    int op;
    std::cin >> op;
    std::cin.ignore();

    if (op == 1) {
        std::cout << "  Enter New Title: ";
        std::string newTitle;
        std::getline(std::cin, newTitle);
        movie->setTitle(newTitle);
        std::cout << "  [Success] Movie title updated!\n";
    } else if (op == 2) {
        std::cout << "  Enter New Price ($): ";
        double newP;
        std::cin >> newP;
        movie->setBaseTicketPrice(newP);
        std::cout << "  [Success] Movie ticket price updated!\n";
    } else if (op == 3) {
        std::cout << "  Enter New Duration (mins): ";
        int dur;
        std::string rat;
        std::cin >> dur;
        std::cout << "  Enter New Rating: ";
        std::cin >> rat;
        movie->setDurationMinutes(dur);
        movie->setRating(rat);
        std::cout << "  [Success] Movie duration and rating updated!\n";
    }
}

// 5. DELETE RECORD
void Cinema::deleteRecord() {
    std::cout << "\n  --- [ DELETE RECORD MENU ] ---\n";
    std::cout << "  1. Cancel / Delete Ticket Booking\n";
    std::cout << "  2. Remove Movie from Catalog\n";
    std::cout << "  Select option (1-2): ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (choice == 1) {
        std::cout << "  Enter Ticket ID to cancel: #";
        int tId;
        std::cin >> tId;

        int foundIdx = -1;
        for (int i = 0; i < ticketCount; ++i) {
            if (tickets[i]->getTicketId() == tId) {
                foundIdx = i;
                break;
            }
        }

        if (foundIdx == -1) {
            std::cout << "  [Error] Ticket #" << tId << " not found!\n";
            return;
        }

        // Release the seat on the screen
        int sId = tickets[foundIdx]->getScreenId();
        std::string seatCode = tickets[foundIdx]->getSeatCode();
        Screen* sc = findScreenById(sId);
        if (sc != nullptr && seatCode.length() >= 2) {
            int r = seatCode[0] - 'A';
            int c = std::stoi(seatCode.substr(1)) - 1;
            sc->cancelSeat(r, c);
        }

        delete tickets[foundIdx];
        // Shift elements
        for (int i = foundIdx; i < ticketCount - 1; ++i) {
            tickets[i] = tickets[i + 1];
        }
        tickets[ticketCount - 1] = nullptr;
        ticketCount--;

        std::cout << "  [Success] Ticket #" << tId << " canceled and seat " << seatCode << " released!\n";
    } else if (choice == 2) {
        std::cout << "  Enter Movie ID to remove: ";
        int mId;
        std::cin >> mId;

        auto it = std::find_if(movies.begin(), movies.end(), [mId](const Movie& m) {
            return m.getMovieId() == mId;
        });

        if (it != movies.end()) {
            std::cout << "  [Success] Movie '" << it->getTitle() << "' removed from catalog.\n";
            movies.erase(it);
        } else {
            std::cout << "  [Error] Movie ID " << mId << " not found.\n";
        }
    }
}

// 6. MAIN TRANSACTION: COMPLETE BOOKING PROCESS
void Cinema::processMainTransaction() {
    std::cout << "\n=================================================================\n";
    std::cout << "            START MAIN TRANSACTION: BOOK CINEMA TICKETS           \n";
    std::cout << "=================================================================\n";

    if (movies.empty()) {
        std::cout << "  [Notice] No movies currently available for booking.\n";
        return;
    }
    if (screens.empty()) {
        std::cout << "  [Notice] No screens configured.\n";
        return;
    }

    // Step 1: Select Movie
    std::cout << "\n  --- STEP 1: SELECT MOVIE ---\n";
    for (const auto& m : movies) {
        m.displayDetails();
    }
    std::cout << "  Enter Movie ID: ";
    int mId;
    std::cin >> mId;
    Movie* selectedMovie = findMovieById(mId);
    if (selectedMovie == nullptr) {
        std::cout << "  [Error] Invalid Movie selection!\n";
        return;
    }

    // Step 2: Select Screen
    std::cout << "\n  --- STEP 2: SELECT SCREEN / AUDITORIUM ---\n";
    for (const auto& s : screens) {
        s.displaySummary();
    }
    std::cout << "  Enter Screen ID: ";
    int sId;
    std::cin >> sId;
    Screen* selectedScreen = findScreenById(sId);
    if (selectedScreen == nullptr) {
        std::cout << "  [Error] Invalid Screen selection!\n";
        return;
    }

    if (selectedScreen->getAvailableSeatsCount() == 0) {
        std::cout << "  [Housefull] Screen is completely booked out!\n";
        return;
    }

    // Step 3: Interactive Visual Seat Map
    std::cout << "\n  --- STEP 3: SEAT SELECTION ---\n";
    selectedScreen->displaySeatLayout();

    std::cout << "  Enter Seat Row Letter (e.g., A, B, C): ";
    char rowChar;
    std::cin >> rowChar;
    rowChar = static_cast<char>(toupper(rowChar));
    int r = rowChar - 'A';

    std::cout << "  Enter Seat Column Number (e.g., 1, 2, 3): ";
    int c;
    std::cin >> c;
    c = c - 1; // 0-indexed

    if (!selectedScreen->isSeatAvailable(r, c)) {
        std::cout << "  [Error] Seat " << rowChar << (c + 1) << " is already taken or invalid!\n";
        return;
    }

    std::string seatCode = std::string(1, rowChar) + std::to_string(c + 1);

    // Step 4: Customer Identification & Polymorphic Discount
    std::cout << "\n  --- STEP 4: CUSTOMER DETAILS ---\n";
    std::cout << "  Enter Customer Phone Number: ";
    std::string phone;
    std::cin >> phone;

    Customer* cust = findCustomerByPhone(phone);
    if (cust == nullptr) {
        std::cout << "  New customer detected. Enter Customer Name: ";
        std::string name;
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "  Select Membership Category:\n";
        std::cout << "    1. Regular (Standard Price)\n";
        std::cout << "    2. VIP (20% Discount)\n";
        std::cout << "    3. Student (10% Discount)\n";
        std::cout << "  Choice (1-3): ";
        int cType;
        std::cin >> cType;

        int newCustId = 100 + static_cast<int>(customers.size()) + 1;
        if (cType == 2) {
            cust = new VIPCustomer(newCustId, name, phone, 100);
        } else if (cType == 3) {
            std::cout << "  Enter Student ID Number: ";
            std::string sCard;
            std::cin >> sCard;
            cust = new StudentCustomer(newCustId, name, phone, sCard);
        } else {
            cust = new RegularCustomer(newCustId, name, phone);
        }
        customers.push_back(cust);
    }

    std::cout << "  Customer confirmed: " << cust->getName() 
              << " (" << cust->getCustomerType() << ")\n";

    // Step 5: Pricing Calculation (RUNTIME POLYMORPHISM in action)
    double basePrice = selectedMovie->getBaseTicketPrice();
    double discount = cust->calculateDiscount(basePrice); // Polymorphic dynamic binding!
    double finalPrice = basePrice - discount;

    // Step 6: Confirmation & Booking
    selectedScreen->bookSeat(r, c);

    if (ticketCount >= ticketCapacity) {
        expandTicketArray();
    }

    int tId = nextTicketId++;
    Ticket* newTicket = new Ticket(tId, selectedMovie->getMovieId(), selectedMovie->getTitle(),
                                   selectedScreen->getScreenId(), seatCode,
                                   cust->getCustomerId(), cust->getName(),
                                   cust->getCustomerType(), basePrice, discount, finalPrice, "2026-10-13");

    tickets[ticketCount++] = newTicket;

    std::cout << "\n  ================= BOOKING COMPLETED SUCCESSFULLY ================\n";
    newTicket->displayTicketCard();
}

// 7. REPORT GENERATION
void Cinema::generateReport() const {
    std::cout << "\n  ===============================================================\n";
    std::cout << "               CINEMA MANAGEMENT & REVENUE REPORT                 \n";
    std::cout << "  ===============================================================\n";

    double totalRevenue = 0.0;
    for (int i = 0; i < ticketCount; ++i) {
        totalRevenue += tickets[i]->getFinalPrice();
    }

    std::cout << "  Total Tickets Sold   : " << ticketCount << "\n";
    std::cout << "  Gross Revenue        : $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";
    std::cout << "  Registered Customers : " << customers.size() << "\n";
    std::cout << "  Active Screens       : " << screens.size() << "\n\n";

    std::cout << "  --- SCREEN OCCUPANCY BREAKDOWN ---\n";
    for (const auto& s : screens) {
        double occupancy = 0.0;
        if (s.getTotalSeats() > 0) {
            occupancy = (static_cast<double>(s.getBookedSeatsCount()) / s.getTotalSeats()) * 100.0;
        }
        std::cout << "  Screen #" << s.getScreenId() << " (" << s.getScreenName() << "): "
                  << s.getBookedSeatsCount() << " / " << s.getTotalSeats() << " seats ("
                  << std::fixed << std::setprecision(1) << occupancy << "% Occupancy)\n";
    }

    std::cout << "\n  --- REVENUE BREAKDOWN BY MOVIE ---\n";
    for (const auto& m : movies) {
        double movieRev = 0.0;
        int movieTickets = 0;
        for (int i = 0; i < ticketCount; ++i) {
            if (tickets[i]->getMovieId() == m.getMovieId()) {
                movieRev += tickets[i]->getFinalPrice();
                movieTickets++;
            }
        }
        std::cout << "  Movie: " << std::setw(24) << std::left << m.getTitle()
                  << " | Tickets: " << std::setw(3) << movieTickets
                  << " | Revenue: $" << std::fixed << std::setprecision(2) << movieRev << "\n";
    }
    std::cout << "  ===============================================================\n\n";
}

// 8. SAVE / LOAD OPERATIONS
void Cinema::handleSaveLoad() {
    std::cout << "\n  --- [ PERSISTENCE & FILE HANDLING ] ---\n";
    std::cout << "  1. Save All Data to Files\n";
    std::cout << "  2. Reload All Data from Files\n";
    std::cout << "  Select option (1-2): ";
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (choice == 1) {
        saveAllData();
        std::cout << "  [Success] All records successfully persisted to 'Data/' directory!\n";
    } else if (choice == 2) {
        loadAllData();
        std::cout << "  [Success] Records successfully reloaded from 'Data/' directory!\n";
    }
}

void Cinema::saveAllData() {
    fileManager.saveMovies(movies);
    fileManager.saveScreens(screens);
    fileManager.saveCustomers(customers);
    fileManager.saveTickets(tickets, ticketCount);
}

void Cinema::loadAllData() {
    fileManager.loadMovies(movies);
    fileManager.loadScreens(screens);
    fileManager.loadCustomers(customers);
    fileManager.loadTickets(tickets, ticketCount, ticketCapacity);
    if (ticketCount > 0) {
        nextTicketId = tickets[ticketCount - 1]->getTicketId() + 1;
    }
}

void Cinema::exitSystem() {
    std::cout << "\n  Saving all data before exiting...\n";
    saveAllData();
    std::cout << "  Data saved. Thank you for using Cinema Ticket Booking System!\n";
}
