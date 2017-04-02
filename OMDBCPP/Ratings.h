#ifndef RATINGS_H
#define RATINGS_H
#pragma once

#include "TimeCode.h"

#include <string>
#include <vector>
#include <functional>

namespace omdb
{
	// provides a container for storing a review about a film
	class Rating
	{
	private:
		TimeCode time;
		std::string name;
		std::string film;
		int score;
	public:
		Rating();
		Rating(TimeCode c, std::string name, std::string film, int score);
		Rating(std::string ratingString);
		Rating(const Rating& other);

		Rating& operator=(const Rating& other);
		bool operator>(const Rating& other);
		bool operator<(const Rating& other);
		bool operator>=(const Rating& other);
		bool operator<=(const Rating& other);
		friend std::istream& operator>>(std::istream& is, Rating& rating);
		friend std::ostream& operator<<(std::ostream& os, 
			const Rating& rating);

		inline TimeCode get_time() const { return time; }
		inline std::string get_name() const { return name; }
		inline std::string get_film() const { return film; }
		inline int get_score() const { return score; }
	};

	// provides a database of ratings on films, can be applied to MovieDatabase
	// to update Movie scores
	class Ratings
	{
	private:
		std::vector<Rating> ratings;
	public:
		Ratings();
		Ratings(std::string ratingsFilePath);
		Ratings(const Ratings& other);

		void sort(std::function<bool(Rating&, Rating&)> sortFunc);

		Ratings& operator=(const Ratings& other);
		Rating operator[](unsigned int index) const;
		friend std::istream& operator>>(std::istream& is, Ratings& ratings);
		friend std::ostream& operator<<(std::ostream& os, 
			const Ratings& ratings);

		inline int size() const { return ratings.size(); }
	};
}

#endif // RATINGS_H