#include "GUI.h"

using namespace SDL;
using namespace std;

#include <iostream>

GUI::GUI(System &p_system, Renderer &p_renderer)
: system(p_system),
  renderer(p_renderer)
{
	ttf.Init();
	
	hoveredControl = nullptr;
	pressedControl = nullptr;
}

void GUI::AddControl(Control &p_control)
{
	p_control.SetRenderer(renderer);
	p_control.CreateTextures();
	
	controls.push_back(&p_control);
}

void GUI::Update()
{
	// GUI system has it own (non-destructive) event handling system
	const int maxEvents = 200;
	Event events[maxEvents];
	
	system.PumpEvents();
	int nbEvents = system.PeepEvents(events, maxEvents, System::EventAction::Peek, Event::FIRST, Event::LAST);
	
	for (int i = 0; i < nbEvents; i++)
	{
		switch (events[i].GetType()) {
			case Event::Type::MOUSE_MOTION:
			{
				const MouseMotionEvent &event = (const MouseMotionEvent &)events[i];
				
				// Check first if the mouse cursor leaved the current hovered control
				if (hoveredControl && !hoveredControl->GetRect().Contains(event.GetPosition()) && hoveredControl != pressedControl) {
					hoveredControl->Hover(false);
					hoveredControl = nullptr;
				}
				
				// Check if the mouse cursor hovers any control
				// TODO: have a list of hoverable controls instead of all controls
				for (auto control : controls) {
					if (control->GetRect().Contains(event.GetPosition())) {
						if (control != pressedControl) {
							hoveredControl = control;
							control->Hover(true);
						}
					}
				}
			}
			break;
				
			case Event::Type::MOUSE_BUTTON_DOWN:
			{
				const MouseButtonEvent &event = (const MouseButtonEvent &)events[i];
				
				// Check if the mouse cursor press any control
				// TODO: have a list of pressable controls instead of all controls
				for (auto control : controls) {
					if (control->GetRect().Contains(event.GetPosition())) {
						pressedControl = control;
						control->Press();
					}
				}
			}
			break;
				
			case Event::Type::MOUSE_BUTTON_UP:
			{
				const MouseButtonEvent &event = (const MouseButtonEvent &)events[i];
				
				// Check if we mouse was clicked up outside of the current pressed control
				if (pressedControl && !pressedControl->GetRect().Contains(event.GetPosition())) {
					pressedControl->Release(false);
				}
				
				// Check if the mouse cursor releases any control
				// TODO: have a list of pressable controls instead of all controls
				for (auto control : controls) {
					if (control->GetRect().Contains(event.GetPosition())) {
						if (control == pressedControl) {
							control->Release();
						}
					}
				}
				
				pressedControl = nullptr;
			}
				
			default:
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
