#include <iostream>
#include <limits>
#include "Cinema.h"

void displayBanner() {
    std::cout << "\n";
    std::cout << "  ===============================================================\n";
    std::cout << "  *                                                             *\n";
    std::cout << "  *               CINEMA TICKET BOOKING SYSTEM                  *\n";
    std::cout << "  *            Object-Oriented Programming (C++)                *\n";
    std::cout << "  *                 Project Code: CPP80                         *\n";
    std::cout << "  *                 Enrollment: IU2641231920                    *\n";
    std::cout << "  *                                                             *\n";
    std::cout << "  ===============================================================\n";
}

void displayMainMenu() {
    std::cout << "\n  +------------------------ MAIN MENU --------------------------+\n";
    std::cout << "  |  1. Add Record                                              |\n";
    std::cout << "  |  2. Display Records                                         |\n";
    std::cout << "  |  3. Search Record                                           |\n";
    std::cout << "  |  4. Update Record                                           |\n";
    std::cout << "  |  5. Delete Record                                           |\n";
    std::cout << "  |  6. Main Transaction (Book Ticket & Select Seat)            |\n";
    std::cout << "  |  7. Report (Revenue & Occupancy Statistics)                 |\n";
    std::cout << "  |  8. Save / Load Records                                     |\n";
    std::cout << "  |  9. Exit                                                    |\n";
    std::cout << "  +-------------------------------------------------------------+\n";
    std::cout << "  Enter your choice (1-9): ";
}

int main() {
    displayBanner();

    // Create system object
    Cinema cinema("CineStar Grand Multiplex");

    int choice = 0;
    while (choice != 9) {
        displayMainMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [Invalid input! Please enter a number between 1 and 9]\n";
            continue;
        }

        switch (choice) {
            case 1:
                cinema.addRecord();
                break;
            case 2:
                cinema.displayRecords();
                break;
            case 3:
                cinema.searchRecord();
                break;
            case 4:
                cinema.updateRecord();
                break;
            case 5:
                cinema.deleteRecord();
                break;
            case 6:
                cinema.processMainTransaction();
                break;
            case 7:
                cinema.generateReport();
                break;
            case 8:
                cinema.handleSaveLoad();
                break;
            case 9:
                cinema.exitSystem();
                std::cout << "  Program ended cleanly. Goodbye!\n\n";
                break;
            default:
                std::cout << "  [Invalid choice! Please choose an option from 1 to 9]\n";
                break;
        }
    }

    return 0;
}
