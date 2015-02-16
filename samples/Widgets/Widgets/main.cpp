#include <SDLplusplus/SDLplusplus.h>
#include <SDLplusplus/TTF.h>

#include <string>

#include "GUI.h"
#include "Label.h"
#include "Button.h"
#include "Picture.h"
#include "List.h"
#include "Collection.h"

#include <iostream>

using namespace SDL;
using namespace std;

class Game : public Control
{
public:
	Game(const std::string &title, const std::string &coverFilename);
	
	void SetTitle(const std::string &title);
	void SetCover(const std::string &coverFilename);
	
	void SetRenderer(SDL::Renderer &renderer) override;
	void DrawForeground() override;
	
	void SetPosition(const Point &position) override;
	
private:
	Picture cover;
	Label title;
	
	int maxWidth;
	
	void UpdateItemsPosition();
};

Game::Game(const std::string &p_title, const std::string &p_coverFilename)
{
	SetPosition(Point(0, 0));
	SetSize(Size(128, 128));

	SetTitle(p_title);
	SetCover(p_coverFilename);
	
	maxWidth = max(title.GetSize().Width, cover.GetSize().Width);
	
	SetSize(Size(maxWidth, cover.GetSize().Height + title.GetSize().Height));
}

void Game::SetTitle(const std::string &p_title)
{
	title.SetFont("Arial.ttf");
	title.SetText(p_title);
	title.SetAlignment(Label::Alignment::CENTER);
	
	UpdateItemsPosition();
}

void Game::SetCover(const std::string &p_coverFilename)
{
	cover.SetImage(Image::Load(p_coverFilename));
	cover.SetSize(cover.GetSize().GetScaledProportionalWidth(128));

	UpdateItemsPosition();
}

void Game::SetRenderer(SDL::Renderer &p_renderer)
{
	Control::SetRenderer(p_renderer);
	
	cover.SetRenderer(p_renderer);
	title.SetRenderer(p_renderer);
}

void Game::SetPosition(const Point &p_position)
{
	Control::SetPosition(p_position);
	
	UpdateItemsPosition();
}

void Game::UpdateItemsPosition()
{
	cover.SetPosition(Point(GetPosition().X + (maxWidth - cover.GetSize().Width) / 2, GetPosition().Y));
	title.SetPosition(Point(GetPosition().X + (maxWidth - title.GetSize().Width) / 2, GetPosition().Y + cover.GetSize().Height));
}

void Game::DrawForeground()
{
	Control::DrawForeground();
	
	cover.Draw();
	title.Draw();
}

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
	Renderer renderer(window, Renderer::TypeFlag::ACCELERATED);

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
	
	Game game1("The Legend of Zelda", "Zelda-Front.jpg");
	Game game2("Metroid", "Metroid-Front.png");
	Game game3("Super Mario Bros", "SuperMarioBros-Front.png");
	Game game4("Super Mario Bros 2", "SuperMarioBros2-Front.jpg");
	Game game5("Super Mario Bros 3", "SuperMarioBros3-Front.png");
	
	Collection picturesCollection;
	picturesCollection.backgroundColor = Color::Red;
	picturesCollection.SetSize(Size(600, 500));
	picturesCollection.SetPosition(Point(250, 200));
	picturesCollection.AddItem(game1);
	picturesCollection.AddItem(game2);
	picturesCollection.AddItem(game3);
	picturesCollection.AddItem(game4);
	picturesCollection.AddItem(game5);
	
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
		system.Update();

		gui.Update();

		renderer.SetDrawColor(Color::Black);
		renderer.Clear();
		
		renderer.SetDrawColor(Color::White);
		gui.Draw();
		
		renderer.Present();
	}

	return 0;
}