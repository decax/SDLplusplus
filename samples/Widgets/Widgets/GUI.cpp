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
	
	mousePosition = Point(0, 0);
	
	system.RegisterEvent(Event::Type::MOUSE_MOTION,      bind(&GUI::OnMouseMotion, this, placeholders::_1));
	system.RegisterEvent(Event::Type::MOUSE_BUTTON_DOWN, bind(&GUI::OnMouseDown,   this, placeholders::_1));
	system.RegisterEvent(Event::Type::MOUSE_BUTTON_UP,   bind(&GUI::OnMouseUp,     this, placeholders::_1));
	system.RegisterEvent(Event::Type::MOUSE_WHEEL,       bind(&GUI::OnMouseWheel,  this, placeholders::_1));
}

GUI::~GUI()
{
	system.UnregisterEvent(Event::Type::MOUSE_MOTION,      bind(&GUI::OnMouseMotion, this, placeholders::_1));
	system.UnregisterEvent(Event::Type::MOUSE_BUTTON_DOWN, bind(&GUI::OnMouseDown,   this, placeholders::_1));
	system.UnregisterEvent(Event::Type::MOUSE_BUTTON_UP,   bind(&GUI::OnMouseUp,     this, placeholders::_1));
	system.UnregisterEvent(Event::Type::MOUSE_WHEEL,       bind(&GUI::OnMouseWheel,  this, placeholders::_1));
}

void GUI::OnMouseMotion(const Event &p_event)
{
	auto &event = (const MouseMotionEvent &)p_event;
	
	mousePosition = event.GetPosition();
	
	// Check first if the mouse cursor leaved the current hovered control
	if (hoveredControl && !hoveredControl->GetRect().Contains(mousePosition) && hoveredControl != pressedControl) {
		hoveredControl->Hover(false);
		hoveredControl = nullptr;
	}
	
	// Check if the mouse cursor hovers any control
	// TODO: have a list of hoverable controls instead of all controls
	for (auto control : controls) {
		if (control->GetRect().Contains(mousePosition)) {
			if (control != pressedControl) {
				hoveredControl = control;
				control->Hover(true);
			}
		}
	}
}

void GUI::OnMouseDown(const Event &p_event)
{
	auto &event = (const MouseButtonEvent &)p_event;
	
	// Check if the mouse cursor press any control
	// TODO: have a list of pressable controls instead of all controls
	for (auto control : controls) {
		if (control->GetRect().Contains(event.GetPosition())) {
			pressedControl = control;
			control->Press();
		}
	}
}

void GUI::OnMouseUp(const Event &p_event)
{
	auto &event = (const MouseButtonEvent &)p_event;
	
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

void GUI::OnMouseWheel(const Event &p_event)
{
	auto &event = (const MouseWheelEvent &)p_event;
	
	for (auto control : controls) {
		if (control->GetRect().Contains(mousePosition)) {
			control->Scroll(event.GetSize());
		}
	}
}

void GUI::AddControl(Control &p_control)
{
	p_control.SetRenderer(renderer);
	
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
