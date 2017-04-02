#ifndef GENRE_H
#define GENRE_H
#pragma once

#include <string>

namespace omdb
{
	// a bitfield storing film genres
	enum Genre
	{
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

	// used to combine flags
	inline Genre operator|(Genre a, Genre b)
	{
		return static_cast<Genre>(static_cast<int>(a) | static_cast<int>(b));
	}

	std::string genres[];

	std::string genreString(unsigned int genre);

	unsigned int findGenre(std::string& genreText);
}

#endif