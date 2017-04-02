#ifndef MOVIE_H
#define MOVIE_H
#pragma once

#include <string>
#include <iostream>

#include "FilmRating.h"
#include "Genre.h"

namespace omdb
{
	// provides a representation of a film complete with
	// title, year, rating, genre, and runtime
	class Movie
	{
	public:
		Movie();
		Movie(std::string title, unsigned int year, FilmRating rating, 
			Genre genre, unsigned int runtime);
		Movie(const Movie& other);

		Movie& operator=(const Movie& other);
		bool operator==(const Movie& other) const;
		bool operator!=(const Movie& other) const;
		bool operator>(const Movie& other) const;
		bool operator<(const Movie& other) const;
		bool operator>=(const Movie& other) const;
		bool operator<=(const Movie& other) const;

		friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
		friend std::istream& operator>>(std::istream& is, Movie& movie);

		void addScore(float score);

		inline std::string get_title() const { return title; }
		inline unsigned int get_year() const { return year; }
		inline FilmRating get_rating() const { return rating; }
		inline Genre get_genre() const { return genre; }
		inline unsigned int get_runtime() const { return runtime; }
		inline float get_meanRating() const { return meanScore; }
		inline unsigned int get_numberOfRatings() const 
		{ 
			return numberOfScores; 
		}

	private:
		std::string title; // title of the film
		unsigned int year; // year of release
		FilmRating rating; // film's official age rating
		Genre genre; // the genre of the film, can be multiple
		unsigned int runtime; // film's runtime
		float meanScore = 0; // the mean user score of the film
		unsigned int numberOfScores = 0; // the number of scores this film has

		// the total score, used for mean calculation
		float cumulativeRating = 0; 
	};
}

#endif // MOVIE_H