#ifndef SECTOR_HPP
#define SECTOR_HPP

#include "Render.hpp"

class MSector : public MRenderable {
protected:
	COORD position;
	size_t sectorSize;
	char* drawable;
	char* clearMask;
public:
	MSector(MConsole& rConsole, COORD position = { 0, 0 });

	~MSector();

	void move(COORD offset);

	void setDrawable(char* drawable);

	void setClearMask(char* clearMask);

	void setPosition(COORD position);

	virtual void clear() override;

	virtual void draw() override;

	COORD getPosition();

	size_t getSectorSize();
};

//COORD operators defs
COORD operator+(COORD, COORD);
bool operator==(COORD, COORD);

#endif //!SECTOR_HPP