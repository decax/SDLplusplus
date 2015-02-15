#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

#include "GUI.h"
#include "Label.h"
#include "Button.h"
#include "Picture.h"
#include "List.h"
#include "Collection.h"

using namespace SDL;
using namespace std;

class Scrollbar : public Control
{
public:
	Scrollbar();
	
	Size contentSize;
};

Scrollbar::Scrollbar()
{
	SetSize(Size(10, 100));

	contentSize = GetSize();
}

int main(int argc, char *argv[])
{
	System system(System::SubSystem::EVERYTHING);
	Window window("Widgets", Size(1024, 768));
	Renderer renderer(window, Renderer::TypeFlag::SOFTWARE);

	Image imageObject; // TODO: investigate to why this is necessary...

	bool running = true;

	system.RegisterEvent(SDL::Event::QUIT,     [&](const Event &)  { running = false; });
	system.RegisterEvent(SDL::Event::KEY_DOWN, [&](const Event &e) { if (((const KeyboardEvent &)e).GetScancode() == Scancode::ESCAPE) running = false; });
	
	GUI gui(system, renderer);
	
	Label label;
	label.SetFont("Arial.ttf");
	label.SetText("allo");
	label.backgroundColor = Color::Red;
	label.color = Color::Black;

	Button button;
	button.SetFont("Arial.ttf");
	button.SetText("click me");
	button.SetPosition(Point(10, 100));
	button.OnClick([&]() { running = false;} );
	
	Picture picture1;
	picture1.SetImage(Image::Load("Zelda-Front.jpg"));
	picture1.SetSize(picture1.GetSize().GetScaledProportionalWidth(128));

	Picture picture2;
	picture2.SetImage(Image::Load("Metroid-Front.png"));
	picture2.SetSize(picture2.GetSize().GetScaledProportionalWidth(128));

	Picture picture3;
	picture3.SetImage(Image::Load("SuperMarioBros-Front.png"));
	picture3.SetSize(picture3.GetSize().GetScaledProportionalWidth(128));

	Picture picture4;
	picture4.SetImage(Image::Load("SuperMarioBros2-Front.jpg"));
	picture4.SetSize(picture4.GetSize().GetScaledProportionalWidth(128));

	Picture picture5;
	picture5.SetImage(Image::Load("SuperMarioBros3-Front.png"));
	picture5.SetSize(picture5.GetSize().GetScaledProportionalWidth(128));

	Collection picturesCollection;
	picturesCollection.backgroundColor = Color::Red;
	picturesCollection.SetPosition(Point(250, 200));
	picturesCollection.AddItem(picture1);
	picturesCollection.AddItem(picture2);
	picturesCollection.AddItem(picture3);
	picturesCollection.AddItem(picture4);
	picturesCollection.AddItem(picture5);
	
	List listConsoles;
	listConsoles.SetSize(Size(200, 200));
	listConsoles.SetPosition(Point(0, 200));
	listConsoles.backgroundColor = Color::Green;
	listConsoles.AddCellLabel("NES");
	listConsoles.AddCellLabel("Super Nintendo");
	listConsoles.AddCellLabel("Nintendo 64");
	listConsoles.AddCellLabel("Gamecube");
	listConsoles.AddCellLabel("Wii");
	listConsoles.AddCellLabel("Wii U");
	listConsoles.AddCellLabel("Gameboy");
	listConsoles.AddCellLabel("Gameboy Advance");
	listConsoles.AddCellLabel("Genesis");
	
	Scrollbar scrollbar;
	scrollbar.backgroundColor = Color::Blue;
	scrollbar.SetPosition(Point(400, 20));
	gui.AddControl(scrollbar);
	
	gui.AddControl(label);
	gui.AddControl(button);
//	gui.AddControl(picture);
	gui.AddControl(listConsoles);
	gui.AddControl(picturesCollection);
	
	while (running) {
		gui.Update();
		system.Update();

		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		renderer.SetDrawColor(Color::White);
		gui.Draw();
		
		renderer.Present();
	}

	return 0;
}