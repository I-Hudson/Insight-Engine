#include "Component/CameraComponent.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>

namespace InSight
{
	void CameraComponent::init()
	{
		//set mTransoform and mPorjectionMatrix
		mTransoform = entity->getComponent<TransformComponent>();
		mProjectionMatrix = glm::mat4();
	}

	void CameraComponent::update()
	{
		//update position of view
		Utility::freeMovement(*getCameraMatrix(), Utility::getDeltaTime(), 5, glm::vec3(0, 1, 0));
	}

	void CameraComponent::gui()
	{
		if (ImGui::CollapsingHeader("Camera Component"))
		{
			bool hasChanged = false;
			//fov
			if (ImGui::SliderFloat("FOV", &mFOV, 0.1f, 0.7f))
			{
				hasChanged = true;
			}

			//asspect
			if (ImGui::InputFloat("Aspect", &mAspect))
			{
				hasChanged = true;
			}

			//near plane
			if (ImGui::SliderFloat("Near Plane", &mFrustrumPlanes.x, 0.1f, 1000.0f))
			{
				hasChanged = true;
			}

			//far plane
			if (ImGui::SliderFloat("Far Plane", &mFrustrumPlanes.y, 0.1f, 1000.0f))
			{
				hasChanged = true;
			}

			if (hasChanged)
			{
				setProjectionMatrix(glm::perspective(glm::pi<float>() * mFOV, mAspect, mFrustrumPlanes.x, mFrustrumPlanes.y));
			}
		}
	}

	void CameraComponent::setCameraMatrix(glm::mat4& aCameraMatrix)
	{
		//set mTransoform and mPorjectionViewMatrix
		mTransoform->setTransformMatrix(aCameraMatrix);
		mProjectionViewMatrix = mProjectionMatrix * *getViewMatrix();
	}

	void CameraComponent::setProjectionMatrix(glm::mat4 aProjectionMatrx)
	{
		//set mPorjectionMatrix
		mProjectionMatrix = aProjectionMatrx;
	}

	void CameraComponent::setPosition(const glm::vec3 & a_position)
	{
		mTransoform->setPosition({ a_position, 1.0f });
	}

	void CameraComponent::setRotation(float a_angle)
	{
		glm::vec3 pos = mTransoform->getPosition()->xyz;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::rotate(glm::mat4(1.0f), glm::radians(a_angle), glm::vec3(0, 0, 1));

		mTransoform->setTransformMatrix(transform);

		mViewMatrix = glm::inverse(*mTransoform->getTransformMatrix());
		mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
	}

	void CameraComponent::setCameraPropertiesPre(float aFOV, float aAspect, float aNearPlane, float aFarPlane)
	{
		//set camera prespective props
		mFOV = aFOV;
		mAspect = aAspect;
		mFrustrumPlanes = glm::vec2(aNearPlane, aFarPlane);

		setProjectionMatrix(glm::perspective(glm::pi<float>() * mFOV, mAspect, mFrustrumPlanes.x, mFrustrumPlanes.y));
	}

	void CameraComponent::setCameraPropertiesOrt(float a_left, float a_right, float a_bottom, float a_top)
	{
		setProjectionMatrix(glm::ortho(a_left, a_right, a_bottom, a_top));
	}

	void CameraComponent::recalculateViewMatrix()
	{
		mViewMatrix = glm::inverse(*mTransoform->getTransformMatrix());
		mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
	}

	void CameraComponent::invertPitch()
	{
		//invert pitch
		mTransoform->invertPitch();
	}

	glm::mat4* CameraComponent::getCameraMatrix()
	{
		//return a pointer for transform matrix
		return mTransoform->getTransformMatrix();
	}

	glm::mat4* CameraComponent::getProjectionMatrix()
	{
		//return a pointer for projection matrix
		return &mProjectionMatrix;
	}

	glm::mat4* CameraComponent::getProjectionViewMatrix()
	{
		//return a pointer for porjection View matrix
		mProjectionViewMatrix = mProjectionMatrix * *getViewMatrix();
		return &mProjectionViewMatrix;
	}

	glm::mat4* CameraComponent::getViewMatrix()
	{
		//return a pointer for view matrix
		mViewMatrix = glm::inverse(*mTransoform->getTransformMatrix());
		return &mViewMatrix;
	}

	glm::mat4 * CameraComponent::getInvprojectionMatrix()
	{
		//return a pointer for inverse projection matrix
		mInvProjection = glm::inverse(mProjectionMatrix);
		return &mInvProjection;
	}

	glm::mat4 * CameraComponent::getInvViewMatrix()
	{
		//return a pointer for inverse view matrix
		mInvView = glm::inverse(mViewMatrix);
		return &mInvProjection;
	}

	void CameraComponent::printCameraMatrix()
	{
		//print to console camera matrix values
		std::stringstream ss;
		glm::mat4 mCameraMatrix = *mTransoform->getTransformMatrix();

		ss << "00: " << mCameraMatrix[0].x << "	01: " << mCameraMatrix[0].y << "	02: " << mCameraMatrix[0].z << "	03: " << mCameraMatrix[0].w << "\n"
			<< "10: " << mCameraMatrix[1].x << "	11: " << mCameraMatrix[1].y << "	12: " << mCameraMatrix[1].z << "	13: " << mCameraMatrix[1].w << "\n"
			<< "20: " << mCameraMatrix[2].x << "	21: " << mCameraMatrix[2].y << "	22: " << mCameraMatrix[2].z << "	23: " << mCameraMatrix[2].w << "\n"
			<< "30: " << mCameraMatrix[3].x << "	31: " << mCameraMatrix[3].y << "	32: " << mCameraMatrix[3].z << "	33: " << mCameraMatrix[3].w;

		std::cout << ss.str() << std::endl;
	}

	int CameraComponent::Save()
	{
		return GetUnqiueID();
	}
}