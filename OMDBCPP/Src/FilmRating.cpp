#include "FilmRating.h"

namespace omdb
{
    FilmRating findRating(std::string r) {
        for (int i = 0; i < (int) FilmRating::Count; i++) {
            if (r == ratings[i])
                return static_cast<FilmRating> (i);
        }
    }
}