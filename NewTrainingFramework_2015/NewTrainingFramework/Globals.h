#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals
{
	static const int screenWidth = 960;
	static const int screenHeight = 720;
	static const float updateIterval = 0.001;
	static float timeSinceLastUpdate= 0;
	static GLfloat alpha = 0.0, step = 0.1;
	static Matrix M;
};

#endif // !GLOBALS_H