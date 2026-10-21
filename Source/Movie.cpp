#include "Movie.h"
#include <iomanip>
#include <sstream>
#include <vector>

Movie::Movie() 
    : movieId(0), title("Unknown"), genre("General"), durationMinutes(0), rating("U"), baseTicketPrice(0.0) {}

Movie::Movie(int id, const std::string& title, const std::string& genre, 
             int duration, const std::string& rating, double price)
    : movieId(id), title(title), genre(genre), durationMinutes(duration), rating(rating), baseTicketPrice(price) {}

Movie::~Movie() {}

int Movie::getMovieId() const { return movieId; }
std::string Movie::getTitle() const { return title; }
std::string Movie::getGenre() const { return genre; }
int Movie::getDurationMinutes() const { return durationMinutes; }
std::string Movie::getRating() const { return rating; }
double Movie::getBaseTicketPrice() const { return baseTicketPrice; }

void Movie::setTitle(const std::string& newTitle) { title = newTitle; }
void Movie::setGenre(const std::string& newGenre) { genre = newGenre; }
void Movie::setDurationMinutes(int duration) { durationMinutes = duration; }
void Movie::setRating(const std::string& newRating) { rating = newRating; }
void Movie::setBaseTicketPrice(double price) { baseTicketPrice = price; }

void Movie::displayDetails() const {
    std::cout << "  ID: " << std::setw(3) << std::left << movieId
              << " | Title: " << std::setw(24) << std::left << title
              << " | Genre: " << std::setw(12) << std::left << genre
              << " | Time: " << std::setw(3) << durationMinutes << "m"
              << " | Rating: " << std::setw(5) << rating
              << " | Base: $" << std::fixed << std::setprecision(2) << baseTicketPrice << "\n";
}

std::string Movie::serialize() const {
    std::ostringstream oss;
    oss << movieId << "|" << title << "|" << genre << "|" 
        << durationMinutes << "|" << rating << "|" << baseTicketPrice;
    return oss.str();
}

Movie Movie::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, '|')) {
        tokens.push_back(token);
    }
    if (tokens.size() >= 6) {
        int id = std::stoi(tokens[0]);
        std::string title = tokens[1];
        std::string genre = tokens[2];
        int duration = std::stoi(tokens[3]);
        std::string rating = tokens[4];
        double price = std::stod(tokens[5]);
        return Movie(id, title, genre, duration, rating, price);
    }
    return Movie();
}
