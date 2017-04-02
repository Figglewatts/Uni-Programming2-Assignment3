#include "Ratings.h"

#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace omdb
{
	/* -------------- BEGIN RATING -------------- */
	
	// default constructor
	Rating::Rating()
	{
		this->time = TimeCode();
		this->film = "";
		this->name = "";
		this->score = 0;
	}

	// value constructor
	Rating::Rating(TimeCode c, std::string name, std::string film, int score)
	{
		this->time = c;
		this->name = name;
		this->film = film;
		this->score = score;
	}

	// create a rating from a rating string
	Rating::Rating(std::string ratingString)
	{
		std::stringstream ss(ratingString);
		ss >> *this;
	}

	// copy constructor
	Rating::Rating(const Rating & other)
	{
		this->time = other.time;
		this->film = other.film;
		this->name = other.name;
		this->score = other.score;
	}

	// copy assignment operator
	Rating & Rating::operator=(const Rating & other)
	{
		if (this != &other)
		{
			this->time = other.time;
			this->film = other.film;
			this->name = other.name;
			this->score = other.score;
		}
		return *this;
	}

	bool Rating::operator>(const Rating & other)
	{
		return this->time > other.time;
	}

	bool Rating::operator<(const Rating & other)
	{
		return this->time < other.time;
	}

	bool Rating::operator>=(const Rating & other)
	{
		return this->time >= other.time;
	}

	bool Rating::operator<=(const Rating & other)
	{
		return this->time <= other.time;
	}

	// extract a rating from an input stream
	std::istream & operator>>(std::istream & is, Rating & rating)
	{
		is >> std::ws;
		is >> rating.time;
		is.ignore(std::numeric_limits<std::streamsize>::max(), '"');
		std::getline(is, rating.name, '"');
		is.ignore(std::numeric_limits<std::streamsize>::max(), '"');
		std::getline(is, rating.film, '"');
		is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
		is >> rating.score;
		return is;
	}

	// put a rating into an output stream
	std::ostream & operator<<(std::ostream & os, const Rating & rating)
	{
		os << rating.time << ",\"";
		os << rating.name << "\",\"";
		os << rating.film << "\",";
		os << rating.score;
		return os;
	}

	/* --------------- END RATING --------------- */

	/* -------------- BEGIN RATINGS ------------- */

	// default constructor
	Ratings::Ratings()
	{}

	// create a ratings database from a text file
	Ratings::Ratings(std::string ratingsFilePath)
	{
		std::ifstream file;
		file.open(ratingsFilePath, std::ios::in);
		if (file.is_open())
			file >> *this;
		else
			std::cerr << "Error opening ratings file." << std::endl;
	}

	// copy constructor
	Ratings::Ratings(const Ratings & other)
	{
		this->ratings = other.ratings;
	}

	// sort this database by a given comparator function
	void Ratings::sort(std::function<bool(Rating&, Rating&)> sortFunc)
	{
		std::sort(ratings.begin(), ratings.end(), sortFunc);
	}

	// copy assignment operator
	Ratings& Ratings::operator=(const Ratings& other)
	{
		if (this != &other)
		{
			this->ratings = other.ratings;
		}
		return *this;
	}

	// provides readonly access to internal vector of ratings
	Rating Ratings::operator[](unsigned int index) const
	{
		return this->ratings[index];
	}

	// extract a rating database from an input stream
	std::istream & operator>>(std::istream & is, Ratings & ratings)
	{
		// while we haven't reached the end of the input
		// read it rating by rating
		while (!is.eof())
		{
			Rating r;
			is >> r;
			ratings.ratings.push_back(r);
			is >> std::ws;
		}
		return is;
	}

	// put a rating database into an output stream
	std::ostream & operator<<(std::ostream & os, const Ratings & ratings)
	{
		// print each rating onto a line
		for (Rating r : ratings.ratings)
		{
			os << r << std::endl;
		}
		return os;
	}

	/* --------------- END RATINGS -------------- */
}