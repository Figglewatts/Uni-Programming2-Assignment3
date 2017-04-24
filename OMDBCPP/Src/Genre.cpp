#include "Genre.h"

namespace omdb
{
    std::string genres[GENRE_COUNT] = {
        "Action",
        "Adventure",
        "Animation",
        "Biography",
        "Comedy",
        "Crime",
        "Drama",
        "Family",
        "Fantasy",
        "Film-Noir",
        "History",
        "Horror",
        "Music",
        "Musical",
        "Mystery",
        "Romance",
        "Sci-Fi",
        "Thriller",
        "War",
        "Western"
    };
    const int numberOfGenres = sizeof (genres) / sizeof (genres[0]);
    
    std::string genreString(unsigned int genre) {
        std::string genreText = "";
        int i = 0;
        while (genre != 0) {
            if (genre & 1) {
                if (genreText.length() > 0)
                    genreText += "/";
                genreText += genres[i];
            }
            genre >>= 1;
            i++;
        }

        return genreText;
    }
    
    void split(const std::string& s, char c, std::vector<string>& v) {
        std::string::size_type i = 0;
        std::string::size_type j = s.find(c);

        // if there are no delimiters
        if (j == std::string::npos) {
            v.push_back(s);
            return;
        }

        while (j != std::string::npos) {
            v.push_back(s.substr(i, j - i));
            i = ++j;
            j = s.find(c, j);

            if (j == std::string::npos)
                v.push_back(s.substr(i, s.length()));
        }
    }
    
    unsigned int findGenre(std::string& genreText) {
        std::vector<string> genreSplit;
        split(genreText, '/', genreSplit);

        unsigned int genreValue = 0;
        for (std::string s : genreSplit) {
            // for each genre check it's valid and add it's value to the genre
            for (int i = 0; i < numberOfGenres; i++) {
                if (s == genres[i])
                    genreValue += (1 << i);
            }
        }
        return genreValue;
    }
}