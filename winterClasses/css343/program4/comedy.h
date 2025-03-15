#ifndef comedy_H
#define comedy_H
#include <string>
#include "movie.h"
using namespace std;

class Comedy : public Movie
{
public:
	/// @brief constructor
	Comedy(int stock, string director, string title, int year);
	/// @brief copy constructor
	/// @param other Comedy to copy
	Comedy(const Comedy &other);
	/// @brief deconstructor
	~Comedy();

	/// @brief less than override
	/// @param other Movie to compare against
	/// @return true if less than other, false if not
	bool operator<(const Movie &other) const override;

	/// @brief get string version of Comedy info
	/// @return string of Comedy
	string toString() const override;

	/// @brief ostream override
	friend ostream &operator<<(ostream &stream, const Comedy &movie);
};
#endif