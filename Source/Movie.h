#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>

class Movie {
private:
    int movieId;
    std::string title;
    std::string genre;
    int durationMinutes;
    std::string rating; // e.g., "PG-13", "R", "U/A"
    double baseTicketPrice;

public:
    // Constructors & Destructor
    Movie();
    Movie(int id, const std::string& title, const std::string& genre, 
          int duration, const std::string& rating, double price);
    ~Movie();

    // Getters and Setters
    int getMovieId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getDurationMinutes() const;
    std::string getRating() const;
    double getBaseTicketPrice() const;

    void setTitle(const std::string& newTitle);
    void setGenre(const std::string& newGenre);
    void setDurationMinutes(int duration);
    void setRating(const std::string& newRating);
    void setBaseTicketPrice(double price);

    // Display
    void displayDetails() const;

    // Serialization helper
    std::string serialize() const;
    static Movie deserialize(const std::string& line);
};

#endif // MOVIE_H
