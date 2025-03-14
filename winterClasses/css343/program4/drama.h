#ifndef drama_H
#define drama_H
#include <string>
#include "movie.h"
using namespace std;

class Drama : public Movie
{

public:
	Drama(int stock, string director, string title, int year);
	Drama(const Drama &other);
	~Drama();

	bool operator<(const Movie &other) const override;

	string toString() const override;
	friend ostream &operator<<(ostream &stream, const Drama &movie);

private:
};
#endif