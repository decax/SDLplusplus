#include "GUI.h"

using namespace SDL;
using namespace std;

GUI::GUI(System &p_system, Renderer &p_renderer)
: system(p_system),
  renderer(p_renderer)
{
	ttf.Init();
	
	capturedControl = nullptr;
}

void GUI::AddControl(Control &p_control)
{
	p_control.SetRenderer(renderer);
	p_control.CreateTextures();
	
	controls.push_back(&p_control);
}

void GUI::Update()
{
	system.PollEvent();
	
	auto events = system.Events;
	
	for (auto e : events) {
		switch (e.GetType()) {
				
		case Event::Type::MOUSE_BUTTON_DOWN:
		case Event::Type::MOUSE_BUTTON_UP:
		{
			auto mouseButton = (const MouseButtonEvent &)e;
			
			for (auto control : controls) {
				if (control->GetRect().Contains(mouseButton.GetPosition()))
				{
					if (mouseButton.GetState() == MouseButtonEvent::PRESSED) {
						capturedControl = control;
						control->Press();
					}
					else if (control == capturedControl) {
						control->Release(true);
					}
				}
			}
			
			if (mouseButton.GetState() == MouseButtonEvent::RELEASED) {
				capturedControl = nullptr;
			}
		}
		break;
				
		case Event::Type::MOUSE_MOTION:
		{
			auto mouseMotion = (const MouseMotionEvent &)e;
			if (capturedControl) {
				if (!capturedControl->GetRect().Contains(mouseMotion.GetPosition())) {
					capturedControl->Release(false);
				}
				else if (capturedControl->IsStateNormal()) {
					capturedControl->Press();
				}
			}
		}
		break;
			
		default:
			// don't care
			break;
		}
	}
	
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
