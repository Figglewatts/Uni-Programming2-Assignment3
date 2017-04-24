#ifndef MOVIEDATABASE_H
#define MOVIEDATABASE_H
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

#include "Movie.h"
#include "Ratings.h"

namespace omdb {
    // provides a database of Movie objects and various
    // functions to query the database and get a result

    class MovieDatabase {
    public:
        MovieDatabase();
        MovieDatabase(std::string moviesFilePath);
        MovieDatabase(const MovieDatabase& other);

        MovieDatabase& operator=(const MovieDatabase& other);
        Movie operator[](int index) const;
        friend std::ostream& operator<<(std::ostream& os,
                const MovieDatabase& other);
        friend std::istream& operator>>(std::istream& is,
                MovieDatabase& other);

        void add(Movie& m);
        void remove(Movie& m);

        void sort(std::function<bool(Movie&, Movie&) > sortFunc);

        // extract a database of a given Genre from this one

        template<typename PFunc>
        MovieDatabase extractDatabase(const PFunc pf, Genre match) const {
            MovieDatabase mdb;
            for (Movie m : movies) {
                // if the flags are the same
                if (((m.*pf)() & match) == match)
                    mdb.add(m);
            }
            return mdb;
        }

        // extract a database of a given type from this one

        template<typename PFunc, typename ReturnVal>
        MovieDatabase extractDatabase(const PFunc pf, ReturnVal match) const {
            MovieDatabase mdb;
            for (Movie m : movies) {
                // if the value matches
                if ((m.*pf)() == match)
                    mdb.add(m);
            }
            return mdb;
        }

        void applyRatings(Ratings& rdb);

        // get a movie of a given genre from the database
        // performs a linear search and returns first instance
        // returns nullptr if not found

        template<typename PFunc>
        Movie getMovie(const PFunc pf, Genre match) {
            for (int i = 0; i < movies.size(); i++) {
                if (((movies[i].*pf)() & match) == match)
                    return &movies[i];
            }

            return nullptr;
        }

        // get a movie of a given type from the database
        // performs a linear search and returns first instance
        // returns nullptr if not found

        template<typename PFunc, typename ReturnVal>
        Movie *getMovie(const PFunc pf, ReturnVal match) {
            for (int i = 0; i < movies.size(); i++) {
                if ((movies[i].*pf)() == match)
                    return &movies[i];
            }

            return nullptr;
        }

        // get a film with the longest given string parameter
        // compares length as opposed to alphabetical order

        Movie *getMax(std::string(Movie::*pf)() const) {
            int iMax = 0;
            for (int i = 1; i < this->size(); i++) {
                if ((movies[i].*pf)().length() >(movies[iMax].*pf)().length())
                    iMax = i;
            }
            return &movies[iMax];
        }

        // get a film with the longest given parameter

        template<typename PFunc>
        Movie *getMax(PFunc pf) {
            int iMax = 0;
            for (int i = 1; i < this->size(); i++) {
                if ((movies[i].*pf)() > (movies[iMax].*pf)())
                    iMax = i;
            }
            return &movies[iMax];
        }

        // get a film with the shortest given string parameter
        // compares length as opposed to alphabetical order

        Movie *getMin(std::string(Movie::*pf)() const) {
            int iMin = 0;
            for (int i = 1; i < this->size(); i++) {
                if ((movies[i].*pf)().length() < (movies[iMin].*pf)().length())
                    iMin = i;
            }
            return &movies[iMin];
        }

        // get a film with the shortest given parameter

        template<typename PFunc>
        Movie *getMin(PFunc pf) {
            int iMin = 0;
            for (int i = 1; i < this->size(); i++) {
                if ((movies[i].*pf)() < (movies[iMin].*pf)())
                    iMin = i;
            }
            return &movies[iMin];
        }

        // the following are member function pointers to Movie accessor methods
        // they are to be used with the template methods above to operate on
        // arbitrary parameters of Movie
        static std::string(Movie::*pget_title)() const;
        static unsigned int (Movie::*pget_year)() const;
        static FilmRating(Movie::*pget_rating)() const;
        static Genre(Movie::*pget_genre)() const;
        static unsigned int (Movie::*pget_runtime)() const;
        static float (Movie::*pget_meanRating)() const;
        static unsigned int (Movie::*pgetNumRatings)() const;

        inline int size() const {
            return movies.size();
        }
    private:
        std::vector<Movie> movies;
    };
}

#endif // MOVIEDATABASE_H