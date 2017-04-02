#ifndef FILMRATING_H
#define FILMRATING_H
#pragma once

#include <string>

namespace omdb
{
	// an enum to store the age rating of a film
	enum class FilmRating : int
	{
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
		APPROVED
	};

	std::string ratings[];

	// converts a film rating to its string representation
	inline std::string ratingString(FilmRating r)
	{
		return ratings[(int)r];
	}

	FilmRating findRating(std::string r);
}

#endif // FILMRATING_H