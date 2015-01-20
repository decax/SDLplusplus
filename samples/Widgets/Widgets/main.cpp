#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

#include "GUI.h"
#include "Label.h"
#include "Button.h"

using namespace SDL;
using namespace std;

int main(int argc, char *argv[])
{
	System system(System::SubSystem::EVERYTHING);
	Window window("Widgets", Size(800, 600));
	Renderer renderer(window, Renderer::TypeFlag::SOFTWARE);

	bool running = true;

	GUI gui(system, renderer);
	
	Label label;
	label.SetText("allo");
	
	Button button;
	button.SetText("click me");
	button.SetPosition(Point(10, 100));
	button.OnClick([&]() { running = false;} );
	
	gui.AddControl(label);
	gui.AddControl(button);
	
	while (running) {
		
		gui.Update();
		
		system.PollEvent();
		
		auto events = system.Events;
		
		for (auto e : events) {
			switch (e.GetType()) {
					
				case Event::Type::QUIT:
					running = false;
					break;
					
				default:
					// don't care
					break;
			}
			
			system.Events.clear(); // TODO: find a way of doing this automatically
		}

		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		renderer.SetDrawColor(Color::White);
		gui.Draw();
		
		renderer.Present();
	}

	return 0;
}