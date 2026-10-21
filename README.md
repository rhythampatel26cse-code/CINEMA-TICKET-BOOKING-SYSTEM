# 🎬 Cinema Ticket Booking System (CPP80)

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg?logo=c%2B%2B)](https://isocpp.org/)
[![Compiler](https://img.shields.io/badge/Compiler-MinGW%20%2F%20GCC%20%2F%20Clang-green.svg)](https://www.mingw-w64.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg?logo=windows)](https://microsoft.com)
[![Paradigm](https://img.shields.io/badge/Architecture-OOP%20%26%20Polymorphism-orange.svg)](#core-oop-concepts-demonstrated)

An end-to-end cinema management and seat reservation console application developed in **C++17** adhering strictly to **Object-Oriented Programming (OOP)** principles. The system streamlines theater operations including movie scheduling, auditorium seat management, customer categorization with polymorphic discounts, receipt generation, and real-time revenue analytics.

---

## 📌 Table of Contents
- [Key Features](#-key-features)
- [Core OOP Concepts Demonstrated](#-core-oop-concepts-demonstrated)
- [Project Structure](#-project-structure)
- [How to Build & Run](#-how-to-build--run)
  - [Option A: Run Pre-compiled Executable](#option-a-run-pre-compiled-executable-recommended)
  - [Option B: Compile from Source (CLI)](#option-b-compile-from-source-cli)
  - [Option C: Build & Run in Visual Studio Code](#option-c-build--run-in-visual-studio-code)
- [Menu Walkthrough & Operations](#-menu-walkthrough--operations)
- [Data Persistence](#-data-persistence)
- [Troubleshooting](#-troubleshooting)

---

## 🚀 Key Features

* **💺 Dynamic Visual Seat Map**: Real-time ASCII grid mapping of auditorium seats (`[O]` Available, `[X]` Booked) with row (A, B, C...) and column indexing.
* **🏷️ Polymorphic Tiered Discounts**:
  * **Regular Customer**: Standard rate (0% discount).
  * **Student Customer**: 10% concession with Student ID verification.
  * **VIP Customer**: 20% loyalty discount with reward point tracking.
* **🧾 Itemized Billing & Receipts**: Generates comprehensive receipts detailing original price, discount breakdown, taxes, allocated seat code, and unique ticket ID.
* **📊 Business Analytics & Reports**: Live tracking of gross revenue, total tickets issued, occupancy rate per screen, and capacity utilization.
* **💾 Automatic Data Persistence**: Preserves all movie catalogues, screen seat grids, customer profiles, and transaction records to flat-file storage between sessions.

---

## 🧠 Core OOP Concepts Demonstrated

| Concept | Implementation in Code |
| :--- | :--- |
| **Classes & Encapsulation** | Strict private member attributes with validated public getters/setters in `Movie`, `Screen`, `Customer`, `Ticket`, and `Cinema`. |
| **Inheritance & Polymorphism** | Abstract base class `Customer` with pure virtual functions `calculateDiscount()` and `getCustomerType()`, implemented by `RegularCustomer`, `VIPCustomer`, and `StudentCustomer`. |
| **Rule of Three** | `Screen` manages dynamic 2D array memory (`char** seatMatrix`) and implements an explicit **Destructor**, **Copy Constructor**, and **Copy Assignment Operator**. |
| **Dynamic Memory Management** | `Cinema` utilizes heap allocation for dynamic arrays of `Ticket*` pointers with runtime array expansion (`allocateTicketArray`, `expandTicketArray`, `clearTickets`). |
| **Separation of Concerns** | `FileManager` isolates all file serialization/deserialization logic away from business logic. |

---

## 📁 Project Structure

```
IU2641231920_CPP80_Project/
├── .vscode/
│   └── tasks.json              # VS Code build and run configurations
├── Data/                       # Flat-file database (plain text)
│   ├── movies.txt              # Movie catalog records
│   ├── screens.txt             # Screen configurations and seat states
│   ├── customers.txt           # Registered customers and loyalty tiers
│   └── tickets.txt             # Transaction log of booked tickets
├── Executable/
│   └── Project.exe             # Precompiled static Windows binary
├── Source/                     # C++ source code and headers
│   ├── Cinema.h / .cpp         # Main multiplex manager & operation handlers
│   ├── Customer.h / .cpp       # Polymorphic customer hierarchy
│   ├── FileManager.h / .cpp    # Persistence & file I/O operations
│   ├── Movie.h / .cpp          # Movie entity
│   ├── Screen.h / .cpp         # Screen layout & 2D dynamic seat matrix
│   ├── Ticket.h / .cpp         # Ticket entity & billing receipt generator
│   └── main.cpp                # Application entry point & interactive loop
└── README.md                   # Project documentation
```

---

## 💻 How to Build & Run

### Prerequisites
* Windows 10/11
* Any modern C++ compiler supporting C++17 (e.g. **MinGW-w64**, **G++**, **Clang**, or **MSVC**)

---

### Option A: Run Pre-compiled Executable (Recommended)
You can launch the pre-built static executable directly without installing build tools:

```powershell
# In PowerShell or Command Prompt from the project root:
.\Executable\Project.exe
```

---

### Option B: Compile from Source (CLI)

Run the following command in PowerShell or Command Prompt:

```powershell
# Compile all source files into the Executable directory
g++ -std=c++17 -Wall -Wextra -static Source/main.cpp Source/Movie.cpp Source/Screen.cpp Source/Customer.cpp Source/Ticket.cpp Source/FileManager.cpp Source/Cinema.cpp -o Executable/Project.exe

# Run the newly built binary
.\Executable\Project.exe
```

---

### Option C: Build & Run in Visual Studio Code

The project is pre-configured with `.vscode/tasks.json`:
1. Open this project folder in VS Code (`File` > `Open Folder...`).
2. Press `Ctrl + Shift + B` (or press `Ctrl + Shift + P` and choose **Tasks: Run Build Task**).
   * This executes the `Build Cinema System` task.
3. Open a terminal in VS Code and run `.\Executable\Project.exe` or run the **Run Cinema System** task.

---

## 📋 Menu Walkthrough & Operations

When the application runs, the following interactive menu is presented:

```text
  +------------------------ MAIN MENU --------------------------+
  |  1. Add Record                                              |
  |  2. Display Records                                         |
  |  3. Search Record                                           |
  |  4. Update Record                                           |
  |  5. Delete Record                                           |
  |  6. Main Transaction (Book Ticket & Select Seat)            |
  |  7. Report (Revenue & Occupancy Statistics)                 |
  |  8. Save / Load Records                                     |
  |  9. Exit                                                    |
  +-------------------------------------------------------------+
```

| Option | Operation | Description |
| :---: | :--- | :--- |
| **1** | **Add Record** | Add a new movie (duration, genre, price), create a new screen (rows, columns), or register a new customer with a discount tier. |
| **2** | **Display Records** | View all movie catalogues, screen capacities, registered customer lists, or complete booking logs. |
| **3** | **Search Record** | Query records by Movie ID/Title, Customer Phone Number, or Ticket ID. |
| **4** | **Update Record** | Modify existing movie titles, genre, rating, duration, or base ticket prices. |
| **5** | **Delete Record** | Cancel a ticket booking (automatically frees the seat on the auditorium map) or remove a movie listing. |
| **6** | **Main Transaction** | **Primary Flow**: Choose movie & screen &rarr; view live seat grid &rarr; pick seat code (e.g. `B3`) &rarr; select customer &rarr; calculate polymorphic discount &rarr; print itemized receipt & save ticket. |
| **7** | **Report** | Generates real-time financial summaries including total revenue, discount totals, and per-screen occupancy percentage. |
| **8** | **Save / Load** | Manually force-sync memory records with files in `Data/`. |
| **9** | **Exit** | Performs clean deallocation of all dynamic memory and auto-saves the latest data state to disk. |

---

## 💾 Data Persistence

All data files reside inside the `Data/` directory and use pipe-delimited (`|`) formatting:

* **`movies.txt`**: `<MovieID>|<Title>|<Genre>|<Duration>|<Rating>|<Price>`
* **`screens.txt`**: `<ScreenID>|<Name>|<Rows>|<Cols>|<SeatStringState>`
* **`customers.txt`**: `<Type>|<CustomerID>|<Name>|<Phone>|[ExtraField: Points / StudentID]`
* **`tickets.txt`**: `<TicketID>|<MovieID>|<Title>|<ScreenID>|<SeatCode>|<CustID>|<CustName>|<CustType>|<OriginalPrice>|<Discount>|<FinalPrice>|<Date>`

> **Note**: If `Data/` files are empty or missing, default seed data will automatically be populated on first boot.

---

## 🛠️ Troubleshooting

* **Seat Layout Display Issue**: Ensure your terminal / console window is set to at least 80 columns wide so the ASCII seat layout and tables align properly.
* **Compiler Not Found**: Ensure `g++` is added to your system `PATH`. Run `g++ --version` to verify.
* **Permission Issues**: If file saving fails, ensure the `Data/` folder has read/write permissions for the current user.
