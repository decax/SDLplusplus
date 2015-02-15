#include "List.h"

#include "Label.h"

using namespace SDL;
using namespace std;

List::List()
{
	SetSize(Size(100, 200));
}

List::~List()
{
	for (auto control : cells)
		delete control;
	
	cells.clear();
}

void List::SetRenderer(SDL::Renderer &p_renderer)
{
	Control::SetRenderer(p_renderer);
	
	for (auto control : cells) {
		control->SetRenderer(p_renderer);
	}
}

void List::AddCellLabel(std::string p_text)
{
	Label *label = new Label();
	label->SetFont("Arial.ttf");
	label->SetText(p_text);
	
	if (renderer != nullptr) {
		label->SetRenderer(*renderer);
	}
	
	cells.push_back(label);
	
	UpdateCellsPosition();
}

void List::SetPosition(const SDL::Point &p_position)
{
	rect.Position = p_position;
	
	UpdateCellsPosition();
}

void List::UpdateCellsPosition()
{
	Point lastPosition = rect.Position;
	Size lastSize = Size(0, 0);
	
	for (auto control : cells) {
		lastPosition += lastSize;
		
		control->SetPosition(lastPosition);
		
		lastSize.Height = control->GetRect().Size.Height;
	}
}

void List::DrawForeground()
{
	for (auto control : cells) {
		control->Draw();
	}
}

