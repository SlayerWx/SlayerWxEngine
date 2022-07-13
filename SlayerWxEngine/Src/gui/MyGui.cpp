#include "MyGui.h"
#include <vector>
MyGui::MyGui()
{
	DataManager::Get();
}

MyGui::~MyGui()
{
	DataManager::Get()->clearLevelEntities();
}

void MyGui::CreateContext(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

void MyGui::BeginUpdate()
{
	ImGui_ImplGlfwGL3_NewFrame(); 
}
void MyGui::Update()
{
 
    
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

void MyGui::Inspector()
{
	float _entityPositionSpeed = 0.1f;
	float _entityRotationSpeed = 0.1f;
	float _entityScaleSpeed = 0.2f;
	
	
	if (DataManager::Get()->getSelectedEntity() != NULL)
	{

		if (DataManager::Get()->getLevelEntities().size() > 0)
		{
			//Entity* aux = DataManager::Get()->getSelectedEntity();
			//std::cout << aux->GetPositionX() << std::endl;
			//ImGui::Button("previous");
			//ImGui::Button("next");
			//ImGui::Text("a");
			//ImGui::Text("Transform");
			//ImGui::DragFloat3("Position ", (float*)&DataManager::Get()->getSelectedEntity()->position, _entityPositionSpeed, -100, 100,"%.3f");
			//ImGui::Text("Rotation");
			//ImGui::DragFloat3("rotation ", (float*)&DataManager::Get()->getSelectedEntity()->rotation, _entityRotationSpeed, -360, 360,"%.3f");
			//ImGui::Text("Scale");
			//ImGui::DragFloat3("scale ", (float*)&DataManager::Get()->getSelectedEntity()->localScale, _entityScaleSpeed, 0.1f, 100, "%.3f");
			//ImGui::Separator();
		}

	}
	
}
void MyGui::EndUpdate()
{
	ImGui::Render();
}

void MyGui::EndEngine()
{
	ImGui_ImplGlfwGL3_Shutdown();
}

//static float f = 0.0f;
//ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
//if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
//show_demo_window ^= 1;
//if (ImGui::Button("Another Window"))
//show_another_window ^= 1;
//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
