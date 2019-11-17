#ifndef RENDER_HPP
#define RENDER_HPP

#include "Console.hpp"

class MRenderable {
protected:
	MConsole* pConsole;
public:
	MRenderable(MConsole& rConsole);

	~MRenderable();

	virtual void clear() = 0;

	virtual void draw() = 0;
};

#endif //!RENDER_HPP