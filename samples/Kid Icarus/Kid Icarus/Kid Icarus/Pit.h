#include <SDLplusplus/SDLplusplus.h>

#include "Animation.h"
#include "Time.h"

#include "Type.h"

class Pit
{
public:
	Pit(SDL::Renderer &renderer);
	
	void SetDirection(Direction direction, bool moving = true);
	
	void Crouch(bool enable = true);
	void LookUp(bool enable = true);
	
	void Update(const Time &time);
	void Draw();
	
private:
	SDL::Renderer *renderer;

	Vector2 position;
	SDL::Size size;
	
	Vector2 speed;
	Vector2 defaultSpeed;
	
	SDL::Texture texture;
	SDL::Rect *texturePositions;
	
	Direction direction;
	
	bool crouching;
	bool lookingUp;
	
	enum AnimationType
	{
		IDLE,
		RUNNING,
		CROUCHING,
		LOOKING_UP
	};
	
	Animation *animation;
	Animation animations[4];
};
