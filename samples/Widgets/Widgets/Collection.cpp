#include "Collection.h"

#include <iostream>

using namespace SDL;
using namespace std;

Collection::Collection()
{
	SetSize(Size(400, 400));
	offset = Size(10, 10);
	
	contentPosition	= Point(0, 0);
}

Collection::~Collection()
{
	items.clear();
}

void Collection::AddItem(Control &p_control)
{
	items.push_back(&p_control);
}

void Collection::SetPosition(const SDL::Point &p_position)
{
	Control::SetPosition(p_position);
	
	UpdateItemsPosition();
}

void Collection::UpdateItemsPosition()
{
	Point lastPosition = GetPosition() + contentPosition;
	Size lastSize = Size(0, 0);
	
	Size curOffset = Size(0, 0);
	
	for (auto item : items) {
		lastPosition.X += lastSize.Width + curOffset.Width;
		
		if ((lastPosition.X + item->GetSize().Width) > rect.GetBottomRight().X) {
			lastPosition.X = GetPosition().X + contentPosition.X;
			
			curOffset.Width = 0;
			curOffset.Height = offset.Height;
			
			lastPosition.Y += lastSize.Height + curOffset.Height;;
		}
		
		item->SetPosition(lastPosition);
		
		curOffset.Width = offset.Width;
		
		lastSize = item->GetRect().Size;
	}
}

void Collection::Scroll(const SDL::Size &size)
{
	contentPosition += size;
	
	UpdateItemsPosition();
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
	auto oldClipRect = renderer->GetClipRect();
	renderer->SetClipRect(rect);

	for (auto item : items) {
		item->Draw();
	}

	renderer->SetClipRect(oldClipRect);
}