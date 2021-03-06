#pragma once

#ifndef __PP_BLUR_H__
#define __PP_BLUR_H__

#include "GBuffer.h"
#include "Shader/BaseShader.h"
#include "PP/PPEffect.h"

class PPBlur : public PPEffect
{
public:
	//Constructor
	PPBlur();
	//Destructor
	~PPBlur();

	//override
	void		draw() override;
	void		destroy() override;

	//set final image to blur
	void		setFinalImage(unsigned int& aImage);

private:

	//shaders
	BaseShader* mBlurShader;
	BaseShader* mCompositeShader;
	//final rendered image from deferred 
	unsigned int mFinalImage;

	//horizontal texture size
	float mHorizontalSize;
	//verticla texture size
	float mVerticalSize;

	//buffers
	GBuffer* mHorBuffer;
	GBuffer* mVerBuffer;
};

#endif // __PP_BLUR_H__
