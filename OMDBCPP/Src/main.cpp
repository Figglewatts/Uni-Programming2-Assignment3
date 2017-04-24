#include <iostream>
using namespace std;

#include <Windows.h>

#include "Movie.h"
#include "MovieDatabase.h"
#include "TimeCode.h"
#include "Ratings.h"
using namespace omdb;

int main(int argc, char** argv) {
    cout << "Loading Film Database..." << endl;
    MovieDatabase parse = MovieDatabase("movies.txt");

    cout << "Loading ratings..." << endl;
    Ratings ratings = Ratings("ratings.txt");

    cout << "Applying ratings..." << endl;
    parse.applyRatings(ratings);

    // Task #1, chronological order of release year
    cout << "Task #1: chronological order of release year" << endl;
    parse.sort([](Movie& a, Movie & b) -> bool {
        return a < b; // ascending order
    });
    cout << parse << endl << endl;

    // Task #2, Third longest Film-Noir
    cout << "Task #2: Third longest Film-Noir" << endl;
    MovieDatabase filmNoir = parse.extractDatabase(MovieDatabase::pget_genre,
            Genre::FilmNoir);
    filmNoir.sort([](Movie& a, Movie & b) -> bool {
        return a.get_runtime() > b.get_runtime(); // descending order
    });
    cout << filmNoir[2] << endl << endl;

    // Task #3, 10th highest rated Sci-Fi
    cout << "Task #3: 10th highest rated Sci-Fi" << endl;
    MovieDatabase sciFi = parse.extractDatabase(MovieDatabase::pget_genre,
            Genre::SciFi);
    sciFi.sort([](Movie& a, Movie & b) -> bool {
        return a.get_meanRating() > b.get_meanRating(); // descending order
    });
    cout << sciFi[9] << endl << endl;

    // Task #4, Highest rated film
    cout << "Task #4: Highest rated film" << endl;
    // "The numbers all go to eleven. Look, right across the board, 
    // eleven, eleven, eleven and..."
    cout << *parse.getMax(MovieDatabase::pget_meanRating) << endl << endl;

    // Task #5, Film with longest title
    cout << "Task #5: Film with longest title" << endl;
    cout << *parse.getMax(MovieDatabase::pget_title) << endl << endl;

    // Task #6, 101st user rating, chronologically
    cout << "Task #6: 101st user rating, chronologically" << endl;
    Ratings inOrderRatings = Ratings(ratings);
    cout << "Sorting ratings..." << endl;
    inOrderRatings.sort([](Rating& a, Rating & b) -> bool {
        return a < b;
    });
    cout << inOrderRatings[100] << endl << endl;

    cout << "Press ENTER to continue...";
    cin.ignore();

    return 1;
}