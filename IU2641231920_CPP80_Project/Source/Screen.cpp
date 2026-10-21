#include "Screen.h"
#include <iomanip>
#include <sstream>
#include <vector>

void Screen::allocateSeats() {
    if (rows <= 0 || cols <= 0) {
        seatMatrix = nullptr;
        return;
    }
    // Dynamic memory allocation for 2D seat matrix
    seatMatrix = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        seatMatrix[i] = new char[cols];
        for (int j = 0; j < cols; ++j) {
            seatMatrix[i][j] = 'O'; // 'O' = Open/Available, 'X' = Booked
        }
    }
}

void Screen::deallocateSeats() {
    if (seatMatrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] seatMatrix[i];
        }
        delete[] seatMatrix;
        seatMatrix = nullptr;
    }
}

Screen::Screen() : screenId(0), screenName("Standard Screen"), rows(5), cols(6), seatMatrix(nullptr) {
    allocateSeats();
}

Screen::Screen(int id, const std::string& name, int r, int c) 
    : screenId(id), screenName(name), rows(r), cols(c), seatMatrix(nullptr) {
    allocateSeats();
}

// Copy Constructor (Deep copy)
Screen::Screen(const Screen& other) 
    : screenId(other.screenId), screenName(other.screenName), rows(other.rows), cols(other.cols), seatMatrix(nullptr) {
    allocateSeats();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            seatMatrix[i][j] = other.seatMatrix[i][j];
        }
    }
}

// Copy Assignment Operator (Deep copy & clean previous)
Screen& Screen::operator=(const Screen& other) {
    if (this != &other) {
        deallocateSeats();
        screenId = other.screenId;
        screenName = other.screenName;
        rows = other.rows;
        cols = other.cols;
        allocateSeats();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                seatMatrix[i][j] = other.seatMatrix[i][j];
            }
        }
    }
    return *this;
}

// Destructor
Screen::~Screen() {
    deallocateSeats();
}

int Screen::getScreenId() const { return screenId; }
std::string Screen::getScreenName() const { return screenName; }
int Screen::getRows() const { return rows; }
int Screen::getCols() const { return cols; }
int Screen::getTotalSeats() const { return rows * cols; }

int Screen::getBookedSeatsCount() const {
    int count = 0;
    if (seatMatrix == nullptr) return 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (seatMatrix[i][j] == 'X') count++;
        }
    }
    return count;
}

int Screen::getAvailableSeatsCount() const {
    return getTotalSeats() - getBookedSeatsCount();
}

bool Screen::isSeatAvailable(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols || seatMatrix == nullptr) {
        return false;
    }
    return seatMatrix[r][c] == 'O';
}

bool Screen::bookSeat(int r, int c) {
    if (isSeatAvailable(r, c)) {
        seatMatrix[r][c] = 'X';
        return true;
    }
    return false;
}

bool Screen::cancelSeat(int r, int c) {
    if (r >= 0 && r < rows && c >= 0 && c < cols && seatMatrix != nullptr) {
        if (seatMatrix[r][c] == 'X') {
            seatMatrix[r][c] = 'O';
            return true;
        }
    }
    return false;
}

void Screen::resetSeats() {
    if (seatMatrix == nullptr) return;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            seatMatrix[i][j] = 'O';
        }
    }
}

void Screen::displaySeatLayout() const {
    std::cout << "\n  ================= SCREEN: " << screenName << " (ID: " << screenId << ") =================\n";
    std::cout << "  ----------------------- [ CINEMA SCREEN ] -----------------------\n\n";
    std::cout << "      ";
    for (int j = 0; j < cols; ++j) {
        std::cout << "  " << (j + 1) << "  ";
    }
    std::cout << "\n";

    for (int i = 0; i < rows; ++i) {
        char rowLetter = static_cast<char>('A' + i);
        std::cout << "   " << rowLetter << "  ";
        for (int j = 0; j < cols; ++j) {
            if (seatMatrix[i][j] == 'O') {
                std::cout << "[ O ]";
            } else {
                std::cout << "[ X ]";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n  Legend: [ O ] = Available   |   [ X ] = Booked\n";
    std::cout << "  Available: " << getAvailableSeatsCount() << " / " << getTotalSeats() << " seats\n";
    std::cout << "  ===============================================================\n\n";
}

void Screen::displaySummary() const {
    std::cout << "  Screen ID: " << std::setw(3) << std::left << screenId
              << " | Name: " << std::setw(15) << std::left << screenName
              << " | Capacity: " << std::setw(3) << getTotalSeats()
              << " | Booked: " << std::setw(3) << getBookedSeatsCount()
              << " | Available: " << std::setw(3) << getAvailableSeatsCount() << "\n";
}

std::string Screen::serialize() const {
    std::ostringstream oss;
    oss << screenId << "|" << screenName << "|" << rows << "|" << cols << "|";
    if (seatMatrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                oss << seatMatrix[i][j];
            }
        }
    }
    return oss.str();
}

Screen Screen::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    if (tokens.size() >= 4) {
        int id = std::stoi(tokens[0]);
        std::string name = tokens[1];
        int r = std::stoi(tokens[2]);
        int c = std::stoi(tokens[3]);
        Screen sc(id, name, r, c);
        if (tokens.size() >= 5) {
            std::string state = tokens[4];
            int idx = 0;
            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (idx < static_cast<int>(state.length())) {
                        if (state[idx] == 'X') {
                            sc.bookSeat(i, j);
                        }
                        idx++;
                    }
                }
            }
        }
        return sc;
    }
    return Screen();
}
