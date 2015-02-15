#include "Collection.h"

using namespace SDL;
using namespace std;

Collection::Collection()
{
	SetSize(Size(400, 400));
}

Collection::~Collection()
{
	items.clear();
}

void Collection::AddItem(Picture &picture)
{
	items.push_back(&picture);
}

void Collection::SetPosition(const SDL::Point &p_position)
{
	Control::SetPosition(p_position);
	
	UpdateItemsPosition();
}

void Collection::UpdateItemsPosition()
{
	Point lastPosition = GetPosition();
	Size lastSize = Size(0, 0);
	
	for (auto item : items) {
		lastPosition.X += lastSize.Width;
		
		if ((lastPosition.X + item->GetSize().Width) > rect.GetBottomRight().X) {
			lastPosition.X = GetPosition().X;
			lastPosition.Y += lastSize.Height;
		}
		
		item->SetPosition(lastPosition);
		
		lastSize = item->GetRect().Size;
	}
}

void Collection::SetRenderer(SDL::Renderer &p_renderer)
{
	Control::SetRenderer(p_renderer);
	
	for (auto item : items) {
		item->SetRenderer(p_renderer);
	}
	
	UpdateItemsPosition();
}

void Collection::DrawForeground()
{
	for (auto item : items) {
		item->Draw();
	}
}