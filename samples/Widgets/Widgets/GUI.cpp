#include "GUI.h"

using namespace SDL;
using namespace std;

GUI::GUI(Renderer &p_renderer)
: renderer(p_renderer)
{
	ttf.Init();
}

void GUI::AddControl(Control &p_control)
{
	p_control.SetRenderer(renderer);
	p_control.CreateTextures();
	
	controls.push_back(&p_control);
}

void GUI::Update()
{
	for (auto control : controls) {
		control->Update();
	}
}

void GUI::Draw()
{
	for (auto control : controls) {
		control->Draw();
	}
}
