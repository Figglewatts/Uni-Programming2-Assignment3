#include "Genre.h"

#include <vector>
using namespace std;

namespace omdb
{
	// array used for string conversion
	string genres[] = 
	{
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
	const int numberOfGenres = sizeof(genres) / sizeof(genres[0]);

	// traverse bitfield and build string based on flags set
	string genreString(unsigned int genre)
	{
		string genreText = "";
		int i = 0;
		while (genre != 0)
		{
			if (genre & 1)
			{
				if (genreText.length() > 0)
					genreText += "/";
				genreText += genres[i];
			}
			genre >>= 1;
			i++;
		}

		return genreText;
	}

	// source: 
	// https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s07.html
	void split(const string& s, char c, vector<string>& v)
	{
		string::size_type i = 0;
		string::size_type j = s.find(c);

		// if there are no delimiters
		if (j == string::npos)
		{
			v.push_back(s);
			return;
		}

		while (j != string::npos)
		{
			v.push_back(s.substr(i, j-i));
			i = ++j;
			j = s.find(c, j);

			if (j == string::npos)
				v.push_back(s.substr(i, s.length()));
		}
	}

	// split string into individual genres and set flags based on each one
	unsigned int findGenre(string& genreText)
	{
		vector<string> genreSplit;
		split(genreText, '/', genreSplit);

		unsigned int genreValue = 0;
		for (string s : genreSplit)
		{
			// for each genre check it's valid and add it's value to the genre
			for (int i = 0; i < numberOfGenres; i++)
			{
				if (s == genres[i])
					genreValue += (1 << i);
			}
		}
		return genreValue;
	}
}