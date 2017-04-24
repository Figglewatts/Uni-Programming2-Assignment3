#include "MovieDatabase.h"

#include <fstream>

#include "Ratings.h"

namespace omdb {
    // set the static member function pointers
    std::string(Movie::*MovieDatabase::pget_title)(void) const = &Movie::get_title;
    unsigned int (Movie::*MovieDatabase::pget_year)(void) const = &Movie::get_year;
    FilmRating(Movie::*MovieDatabase::pget_rating)(void) const = &Movie::get_rating;
    Genre(Movie::*MovieDatabase::pget_genre)(void) const = &Movie::get_genre;
    unsigned int (Movie::*MovieDatabase::pget_runtime)(void) const = &Movie::get_runtime;
    float (Movie::*MovieDatabase::pget_meanRating)(void) const = &Movie::get_meanRating;
    unsigned int (Movie::*MovieDatabase::pgetNumRatings)(void) const = &Movie::get_numberOfRatings;

    // default constructor

    MovieDatabase::MovieDatabase() {
    }

    // load a database from a text file

    MovieDatabase::MovieDatabase(std::string moviesFilePath) {
        std::ifstream file;
        file.open(moviesFilePath, std::ios::in);
        if (file.is_open())
            file >> *this;
        else
            std::cerr << "Error opening movies file." << std::endl;
    }

    // copy constructor

    MovieDatabase::MovieDatabase(const MovieDatabase & other) {
        this->movies = other.movies;
    }

    // copy assignment operator

    MovieDatabase & MovieDatabase::operator=(const MovieDatabase & other) {
        if (this != &other) {
            this->movies = other.movies;
        }
        return *this;
    }

    // array access operator, provides readonly access to internal vector

    Movie MovieDatabase::operator[](int index) const {
        return movies[index];
    }

    void MovieDatabase::add(Movie & m) {
        movies.push_back(m);
    }

    void MovieDatabase::remove(Movie & m) {
        for (int i = 0; i < movies.size(); i++) {
            if (movies[i] == m)
                movies.erase(movies.begin() + i);
        }
    }

    // sorts the internal vector according to a provided sorting function

    void MovieDatabase::sort(std::function<bool(Movie&, Movie&) > sortFunc) {
        std::sort(movies.begin(), movies.end(), sortFunc);
    }

    // apply a ratings database to this movie database
    // updates the scores of all films with a rating
    // prints progress to cout

    void MovieDatabase::applyRatings(Ratings& rdb) {
        for (int i = 0; i < rdb.size(); i++) {
            std::cout << (i + 1) << "/" << rdb.size() << "\r";
            getMovie(pget_title, rdb[i].get_film())->addScore(rdb[i].get_score());
        }
        std::cout << std::endl;
    }

    // put a database into an output stream

    std::ostream & operator<<(std::ostream& os, const MovieDatabase & other) {
        for (Movie m : other.movies) {
            os << m << std::endl;
        }
        return os;
    }

    // read a database from an input stream

    std::istream & operator>>(std::istream& is, MovieDatabase & other) {
        // while we haven't reached the end of the stream
        // read it movie by movie
        while (!is.eof()) {
            Movie m = Movie();
            is >> m;
            other.add(m);
            is >> std::ws;
        }
        return is;
    }
}