#include "Picture.h"

using namespace SDL;
using namespace std;

Picture::Picture()
{
	SetSize(Size(128, 128));
}

void Picture::SetImage(const SDL::Surface &p_image)
{
	image = p_image;
	
	if (autoSize) {
		SetSize(image.GetSize());
	}
}

void Picture::CreateTextures()
{
	texture = Texture(*renderer, image);
}

void Picture::DrawForeground()
{
	Control::DrawForeground();
	
	renderer->Copy(texture, rect);
}