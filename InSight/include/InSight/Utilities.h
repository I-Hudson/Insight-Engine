#ifndef __UTILITIES_H_
#define __UTILITIES_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Debug.h"

#define ARRAY_SIZE(a)(sizeof(a) / sizeof(a[0]))

// a utility class with static helper methods
class Utility
{
public:

	// utilities for timing; Get() updates timers and returns time since last Get call
	static void		resetTimer();
	static float	tickTimer();
	static float	getDeltaTime();
	static float	getTotalTime();

	// utility for mouse / keyboard movement of a matrix transform (suitable for camera)
	static void		freeMovement(glm::mat4& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up = glm::vec3(0,1,0));

	// loads a BaseShader from a file and creates it for the specified stage
	static unsigned int	loadShader(const char* a_filename, unsigned int a_type);

	// creates a BaseShader program, links the specified BaseShader stages to it, and binds the specified input/output attributes if they are used
	static unsigned int	createProgram(unsigned int a_vertexShader, unsigned int a_controlShader, unsigned int a_evaluationShader, unsigned int a_geometryShader, unsigned int a_fragmentShader,
									  unsigned int a_inputAttributeCount = 0, const char** a_inputAttributes = nullptr,
									  unsigned int a_outputAttributeCount = 0, const char** a_outputAttributes = nullptr);

	static void TestShaderStatus(const unsigned int& a_uiShaderId, unsigned int a_uiStatus, int& a_iSuccessFlag, const char* a_shaderType);

	static unsigned int createTexture(int aLevel, int aInternalFormat,
										int aWidth, int aHeight,
										int aBoarder, GLenum aFormat,
										GLenum aType, const void* aPixels);

	static void loadTextureFromFile(const char* aFileName, unsigned int& aTexture);

private:
	// helper function for loading BaseShader code into memory
	static unsigned char*	fileToBuffer(const char* a_szPath);


};

#endif // __UTILITIES_H_