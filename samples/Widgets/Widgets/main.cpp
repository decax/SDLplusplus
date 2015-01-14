#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

#include "Label.h"
#include "Button.h"

class GUI
{
public:
	GUI(SDL::Renderer &renderer);
	
	void Update();
	void Draw();
	
private:
	SDL::Renderer &renderer;
	
	SDL::TTF ttf;
};

using namespace SDL;
using namespace std;

GUI::GUI(Renderer &p_renderer)
: renderer(p_renderer)
{
	ttf.Init();
}

void GUI::Update()
{
}

void GUI::Draw()
{

}

int main(int argc, char *argv[])
{
	System system(System::SubSystem::EVERYTHING);
	Window window("Widgets", Size(800, 600));
	Renderer renderer(window, Renderer::TypeFlag::SOFTWARE);

	GUI gui(renderer);
	
	Label label;
	label.SetFont("Arial.ttf");
	label.SetText("allo");
	
	Button button(renderer);
	button.SetFont("Arial.ttf");
	button.SetText("click me");
	button.SetPosition(Point(10, 100));
	
	bool running = true;
	
	while (running) {
		
		gui.Update();
		
		system.PollEvent();
		
		auto events = system.Events;
		
		for (auto e : events) {
			switch (e.GetType()) {
					
				case Event::Type::QUIT:
					running = false;
					break;
					
				case Event::Type::KEY_DOWN:
				case Event::Type::KEY_UP:
				{
					auto kbe = (const KeyboardEvent &)e;
					
					switch (kbe.GetScancode()) {
							
						case Scancode::ESCAPE:
							running = false;
							break;
							
						default:
							// don't care
							break;
					}
					
					break;
				}
					
				default:
					// don't care
					break;
			}
			
			system.Events.clear(); // TODO: find a way of doing this automatically
		}

		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		gui.Draw();
		
		renderer.SetDrawColor(Color::White);
		label.Draw(renderer);
		button.Draw();
		
		renderer.Present();
	}

	return 0;
}