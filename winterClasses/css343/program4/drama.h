#ifndef drama_H
#define drama_H
#include <string>
#include "movie.h"
using namespace std;

class Drama : public Movie
{

public:
	/// @brief constructor
	Drama(int stock, string director, string title, int year);

	/// @brief copy constructor
	/// @param other Drama to copy
	Drama(const Drama &other);

	/// @brief deconstructor
	~Drama();

	/// @brief less than override
	/// @param other Movie to test against
	/// @return true if less than other, false if not
	bool operator<(const Movie &other) const override;

	/// @brief get string version of Drama info
	/// @return string of Drama
	string toString() const override;

	/// @brief ostream override
	friend ostream &operator<<(ostream &stream, const Drama &movie);
};
#endif