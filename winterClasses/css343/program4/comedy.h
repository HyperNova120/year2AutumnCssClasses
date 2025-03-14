#ifndef comedy_H
#define comedy_H
#include <string>
#include "movie.h"
using namespace std;

class Comedy : public Movie
{
public:
	Comedy(int stock, string director, string title, int year);
	Comedy(const Comedy &other);
	~Comedy();

	bool operator<(const Movie &other) const override;

	string toString() const override;
	friend ostream &operator<<(ostream &stream, const Comedy &movie);

private:
};
#endif