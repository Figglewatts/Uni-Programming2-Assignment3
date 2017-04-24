#ifndef FILMRATING_H
#define FILMRATING_H
#pragma once

#include <string>

namespace omdb {
    // an enum to store the age rating of a film

    enum class FilmRating : int {
        G,
        TV14,
        M,
        PG13,
        NA,
        R,
        NOTRATED,
        PG,
        PASSED,
        X,
        UNRATED,
        APPROVED,
        Count
    };

    // array used for string representation of rating
    std::string ratings[(int) FilmRating::Count] = {
        "G",
        "TV-14",
        "M",
        "PG-13",
        "N/A",
        "R",
        "NOT RATED",
        "PG",
        "PASSED",
        "X",
        "UNRATED",
        "APPROVED"
    };

    // converts a film rating to its string representation

    inline std::string ratingString(FilmRating r) {
        return ratings[(int) r];
    }

    // converts a string to a FilmRating

    FilmRating findRating(std::string r);
}

#endif // FILMRATING_H