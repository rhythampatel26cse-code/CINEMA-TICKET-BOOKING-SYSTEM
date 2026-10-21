================================================================================
CINEMA TICKET BOOKING SYSTEM
Course: Object-Oriented Programming (C++)
Project Code: CPP80
Student Name: Rhytham Patel
Student Enrollment Number: IU2641231920
================================================================================

1. PROJECT OVERVIEW
--------------------------------------------------------------------------------
The Cinema Ticket Booking System is an end-to-end management console application 
developed in C++ adhering strictly to Object-Oriented Programming (OOP) paradigms.
It streamlines daily cinema operations including movie scheduling, auditorium seat
reservation with an interactive 2D seat grid, customer categorization with 
polymorphic discounts, receipt generation, and comprehensive revenue analytics.

2. CORE OOP CONCEPTS DEMONSTRATED
--------------------------------------------------------------------------------
- Classes and Objects:
  Real-world domain models: Movie, Screen, Customer, Ticket, Cinema, and FileManager.

- Encapsulation:
  Strict private data members with validation-protected public getters/setters.

- Constructors & Destructors (Rule of Three):
  Overloaded default and parameterized constructors. The Screen class manages
  dynamic 2D seat arrays with full copy constructor, copy assignment operator,
  and deallocating destructor.

- Inheritance & Runtime Polymorphism:
  Abstract base class 'Customer' with pure virtual functions:
    * virtual double calculateDiscount(double amount) const = 0;
    * virtual std::string getCustomerType() const = 0;
  Specialized derived classes:
    * RegularCustomer: Standard pricing (0% discount).
    * VIPCustomer: Premium loyalty tier (20% discount).
    * StudentCustomer: Concession tier with Student ID verification (10% discount).
  Polymorphic dispatch dynamically calculates pricing at runtime via base pointers.

- Meaningful Dynamic Memory Management:
  * Screen uses dynamic 2D array allocation ('new char*[rows]' and 'new char[cols]').
  * Cinema implements dynamic array resizing for Ticket records ('new Ticket*[capacity]')
    and ensures safe deallocation using 'delete' and 'delete[]'.

- Robust File Persistence:
  FileManager serializes and deserializes all operational state across sessions:
  Data/movies.txt, Data/screens.txt, Data/customers.txt, and Data/tickets.txt.

3. FOLDER STRUCTURE
--------------------------------------------------------------------------------
IU2641231920_CPP80_Project/
  ├── .vscode/
  │     └── tasks.json
  ├── Source/
  │     ├── Movie.h & Movie.cpp
  │     ├── Screen.h & Screen.cpp
  │     ├── Customer.h & Customer.cpp
  │     ├── Ticket.h & Ticket.cpp
  │     ├── FileManager.h & FileManager.cpp
  │     ├── Cinema.h & Cinema.cpp
  │     └── main.cpp
  ├── Data/
  │     ├── movies.txt
  │     ├── screens.txt
  │     ├── customers.txt
  │     └── tickets.txt
  ├── Executable/
  │     └── Project.exe
  ├── .gitignore
  ├── ProjectReport.pdf
  ├── README.md
  └── README.txt

4. HOW TO COMPILE AND RUN
--------------------------------------------------------------------------------
OPTION A: Run the Pre-compiled Executable (Recommended)
  1. Open Command Prompt or PowerShell in the project directory.
  2. Run:
     .\Executable\Project.exe

OPTION B: Compile from Source using G++ / MinGW
  1. Open terminal in the project directory.
  2. Execute:
     g++ -std=c++17 -Wall -Wextra -static Source/main.cpp Source/Movie.cpp Source/Screen.cpp Source/Customer.cpp Source/Ticket.cpp Source/FileManager.cpp Source/Cinema.cpp -o Executable/Project.exe
  3. Launch:
     .\Executable\Project.exe

OPTION C: Visual Studio Code
  1. Open the folder in VS Code.
  2. Press Ctrl + Shift + B to build using configured tasks.json.
  3. Run .\Executable\Project.exe in the integrated terminal.

5. APPLICATION MENU GUIDE
--------------------------------------------------------------------------------
1. Add Record      : Add a new movie, auditorium screen, or register a customer.
2. Display Records : View all movies, screens & seat capacities, customers, or tickets.
3. Search Record   : Fast lookup by Movie ID/Title, Customer phone, or Ticket #.
4. Update Record   : Modify movie titles, show durations, ratings, or ticket pricing.
5. Delete Record   : Cancel a ticket booking (releases seat) or remove a movie listing.
6. Main Transaction: Interactive seat selection map [O]/[X] and discount checkout.
7. Report          : Real-time revenue analytics and per-screen occupancy rates.
8. Save / Load     : Manual persistence triggers (also saves automatically on exit).
9. Exit            : Clean memory release and persistence shutdown.
================================================================================
