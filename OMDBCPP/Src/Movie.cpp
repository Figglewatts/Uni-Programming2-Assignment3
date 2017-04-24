#include "Movie.h"

#include <limits>

namespace omdb {
    // default constructor

    Movie::Movie() {
        this->title = "";
        this->year = 0;
        this->rating = FilmRating::APPROVED; // arbitrary
        this->genre = Genre::Action; // arbitrary
        this->runtime = 0;
        this->numberOfScores = 0;
        this->meanScore = 0;
        this->cumulativeRating = 0;
    }

    // detail constructor, sets all values

    Movie::Movie(std::string title, unsigned int year, FilmRating rating,
            Genre genre, unsigned int runtime) {
        this->title = title;
        this->year = year;
        this->rating = rating;
        this->genre = genre;
        this->runtime = runtime;
        this->numberOfScores = 0;
        this->meanScore = 0;
        this->cumulativeRating = 0;
    }

    // copy constructor

    Movie::Movie(const Movie& other) {
        this->title = other.title;
        this->year = other.year;
        this->rating = other.rating;
        this->genre = other.genre;
        this->runtime = other.runtime;
        this->numberOfScores = other.numberOfScores;
        this->meanScore = other.meanScore;
        this->cumulativeRating = other.cumulativeRating;
    }

    // copy assignment operator

    Movie& Movie::operator=(const Movie& other) {
        if (this != &other) {
            this->title = other.title;
            this->year = other.year;
            this->rating = other.rating;
            this->genre = other.genre;
            this->runtime = other.runtime;
            this->numberOfScores = other.numberOfScores;
            this->meanScore = other.meanScore;
            this->cumulativeRating = other.cumulativeRating;
        }
        return *this;
    }

    bool Movie::operator==(const Movie& other) const {
        if (this == &other) return true;

        return this->title == other.title
                && this->year == other.year
                && this->rating == other.rating
                && this->genre == other.genre
                && this->runtime == other.runtime
                && this->meanScore == other.meanScore
                && this->cumulativeRating == other.cumulativeRating
                && this->numberOfScores == other.numberOfScores;
    }

    bool Movie::operator!=(const Movie& other) const {
        return !(*this == other);
    }

    bool Movie::operator>(const Movie& other) const {
        return this->year > other.year
                || (this->year == other.year) && (this->title < other.title);
    }

    bool Movie::operator<(const Movie& other) const {
        return this->year < other.year
                || (this->year == other.year) && (this->title < other.title);
    }

    bool Movie::operator>=(const Movie& other) const {
        return *this > other || *this == other;
    }

    bool Movie::operator<=(const Movie& other) const {
        return *this < other || *this == other;
    }

    // adds a user score to this Movie, updates numberOfScores, adds to
    // cumulativeRating, recalculates mean score

    void Movie::addScore(float rating) {
        numberOfScores++;
        cumulativeRating += rating;
        meanScore = cumulativeRating / numberOfScores;
    }

    // put a film formatted into an output stream

    std::ostream& operator<<(std::ostream& os, const Movie& movie) {
        os << "\"" << movie.title << "\",";
        os << movie.year << ",";
        os << "\"" << ratingString(movie.rating) << "\",\"";
        os << genreString(movie.genre) << "\",";
        os << movie.runtime << ",";
        os << movie.meanScore << ",";
        os << movie.numberOfScores;
        return os;
    }

    // extract a formatted film from an input stream

    std::istream& operator>>(std::istream& is, Movie& movie) {
        std::string rating;
        std::string genre;

        is >> std::ws;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '"');
        std::getline(is, movie.title, '"');
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        is >> movie.year;
        is.ignore(std::numeric_limits<std::streamsize>::max(), '"');
        std::getline(is, rating, '"');
        is.ignore(std::numeric_limits<std::streamsize>::max(), '"');
        std::getline(is, genre, '"');
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        is >> movie.runtime;
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        is >> movie.meanScore;
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        is >> movie.numberOfScores;
        is.ignore(std::numeric_limits<std::streamsize>::max(), 0x0A);

        movie.rating = findRating(rating);
        movie.genre = static_cast<Genre> (findGenre(genre));

        movie.cumulativeRating = 0;
        movie.meanScore = 0;

        return is;
    }
}