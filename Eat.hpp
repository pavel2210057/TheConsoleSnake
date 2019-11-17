#ifndef EAT_HPP
#define EAT_HPP

#include "Sector.hpp"

class MEat : public MSector {
	COORD consoleSize;
public:
	MEat(MConsole& rConsole);

	~MEat();

	void spawn();
};

#endif //!EAT_HPP