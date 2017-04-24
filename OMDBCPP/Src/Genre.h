#ifndef GENRE_H
#define GENRE_H
#pragma once

#include <string>
#include <vector>

namespace omdb {
    // a bitfield storing film genres

    enum Genre {
        Action = 0x1,
        Adventure = 0x2,
        Animation = 0x4,
        Biography = 0x8,
        Comedy = 0x10,
        Crime = 0x20,
        Drama = 0x40,
        Family = 0x80,
        Fantasy = 0x100,
        FilmNoir = 0x200,
        History = 0x400,
        Horror = 0x800,
        Music = 0x1000,
        Musical = 0x2000,
        Mystery = 0x4000,
        Romance = 0x8000,
        SciFi = 0x10000,
        Thriller = 0x20000,
        War = 0x40000,
        Western = 0x80000
    };

    const static int GENRE_COUNT = 20;

    // used to combine flags

    inline Genre operator|(Genre a, Genre b) {
        return static_cast<Genre> (static_cast<int> (a) | static_cast<int> (b));
    }
    
    // traverse bitfield and build string based on flags set
    std::string genreString(unsigned int genre);

    // source: 
    // https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s07.html

    void split(const std::string& s, char c, std::vector<string>& v);

    // split string into individual genres and set flags based on each one

    unsigned int findGenre(std::string& genreText);
}

#endif