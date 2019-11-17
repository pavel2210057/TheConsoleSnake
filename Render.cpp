#include "Render.hpp"

MRenderable::MRenderable(MConsole& rConsole) :
	pConsole(&rConsole) {}

MRenderable::~MRenderable() = default;