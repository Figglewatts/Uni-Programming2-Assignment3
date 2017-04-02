#include "FilmRating.h"

namespace omdb
{
	// array used for string representation of rating
	std::string ratings[] = 
	{
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
	int numRatings = sizeof(ratings) / sizeof(ratings[0]);

	// converts a string to a FilmRating
	FilmRating findRating(std::string r)
	{
		for (int i = 0; i < numRatings; i++)
		{
			if (r == ratings[i])
				return static_cast<FilmRating>(i);
		}
	}
}