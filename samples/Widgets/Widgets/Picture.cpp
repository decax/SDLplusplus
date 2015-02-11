#include "Picture.h"

using namespace SDL;
using namespace std;

void Picture::SetImage(const SDL::Surface &p_image)
{
	image = p_image;
}

void Picture::CreateTextures()
{
	texture = Texture(*renderer, image);
}

void Picture::Draw()
{
	renderer->Copy(texture, Rect(position, Size(128, 128)));
}