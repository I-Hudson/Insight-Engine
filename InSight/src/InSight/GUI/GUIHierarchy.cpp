#include "GUI/GUIHierarchy.h"

namespace InSight::GUI
{
	GUIHierarchy::GUIHierarchy()
	{
		mActiveEntity = nullptr;
	}

	GUIHierarchy::GUIHierarchy(EntityManager* aEntityManager)
	{
		//set entiy manager
		mEntityManager = aEntityManager;
		mActiveEntity = nullptr;
	}

	GUIHierarchy::GUIHierarchy(EntityManager* aEntityManager, const glm::vec2& aPosition, const glm::vec2& aSize) :
		GUIBase(aPosition, aSize)
	{
		//set entiy manager
		mEntityManager = aEntityManager;
		mActiveEntity = nullptr;
	}

	GUIHierarchy::GUIHierarchy(const glm::vec2& aPosition, const glm::vec2& aSize) :
		GUIBase(aPosition, aSize)
	{
		mActiveEntity = nullptr;
	}

	GUIHierarchy::~GUIHierarchy()
	{
	}

	void GUIHierarchy::draw()
	{
		//set window pos and size
		ImGui::SetNextWindowPos(mPosition);
		ImGui::SetNextWindowSize(mSize);

		//begin next gui element
		ImGui::Begin("GUI Hierarchy");

		ImGui::TextColored(ImVec4(0, 170, 0, 1), "Entity List:");

		//for each entitiy in scene add here
		if (mEntityManager != nullptr)
		{
			int i = 0;
			ImGui::BeginChild("Scrolling");
			for (auto& entity : mEntityManager->getEntities())
			{
				/*if (ImGui::Button(entity->getID().c_str(), ImVec2(mSize.x * 1.0f, mSize.y * 0.15f)))
				{
					if (mActiveEntity != entity)
					{
						mActiveEntity = entity;
						std::string log("Active Entitiy has changed: ");
						log += mActiveEntity->getID();
						EN_TRACE(log);
					}
				}*/
				bool isSelected = false;
				if (mActiveEntity != entity)
				{
					isSelected = true;
				}

				ImGui::PushID(i);
				if (ImGui::Selectable(entity->getID().c_str(), isSelected))
				{
					mActiveEntity = entity;
				}
				ImGui::PopID();
				i++;
			}
			ImGui::EndChild();
		}
		else
		{
			ImGui::Text("No Entity Manager set.");
		}

		ImGui::End();
	}

	void GUIHierarchy::setEntityManager(EntityManager* aEntityManager)
	{
		//set entiy manager
		mEntityManager = aEntityManager;
	}

	Entity* GUIHierarchy::getActiveEntitiy()
	{
		//get pointer to active entity 
		return mActiveEntity;
	}
}