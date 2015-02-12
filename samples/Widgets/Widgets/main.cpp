#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

#include "GUI.h"
#include "Label.h"
#include "Button.h"
#include "Picture.h"

using namespace SDL;
using namespace std;

int main(int argc, char *argv[])
{
	System system(System::SubSystem::EVERYTHING);
	Window window("Widgets", Size(800, 600));
	Renderer renderer(window, Renderer::TypeFlag::SOFTWARE);

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
	
	Image coverImage;
	
	Picture picture;
	picture.SetImage(coverImage.Load("Zelda-Front.jpg"));
	picture.SetPosition(window.GetSize().Center());
	
	gui.AddControl(label);
	gui.AddControl(button);
	gui.AddControl(picture);
	
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