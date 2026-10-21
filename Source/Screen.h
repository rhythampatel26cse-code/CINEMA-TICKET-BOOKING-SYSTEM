#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <iostream>

class Screen {
private:
    int screenId;
    std::string screenName;
    int rows;
    int cols;
    char** seatMatrix; // Meaningful dynamic memory: 2D dynamic array (char* / new char[cols])

    void allocateSeats();
    void deallocateSeats();

public:
    // Constructors & Destructor (Rule of Three)
    Screen();
    Screen(int id, const std::string& name, int r, int c);
    Screen(const Screen& other);            // Copy constructor
    Screen& operator=(const Screen& other); // Copy assignment operator
    ~Screen();                              // Destructor releasing dynamic memory

    // Getters
    int getScreenId() const;
    std::string getScreenName() const;
    int getRows() const;
    int getCols() const;
    int getTotalSeats() const;
    int getBookedSeatsCount() const;
    int getAvailableSeatsCount() const;

    // Seat operations
    bool isSeatAvailable(int r, int c) const;
    bool bookSeat(int r, int c);
    bool cancelSeat(int r, int c);
    void resetSeats();

    // Visual Seat Map
    void displaySeatLayout() const;
    void displaySummary() const;

    // Serialization
    std::string serialize() const;
    static Screen deserialize(const std::string& line);
};

#endif // SCREEN_H
