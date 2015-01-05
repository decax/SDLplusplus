#pragma once

#include <SDL2/SDL.h>

#include "GameController.h"

#include "Scancode.h"
#include "Rect.h"

namespace SDL {

class Event
{
public:
	enum Type
	{
		QUIT     = SDL_QUIT, 

		KEY_DOWN = SDL_KEYDOWN,
		KEY_UP   = SDL_KEYUP,
		
		MOUSE_BUTTON_DOWN = SDL_MOUSEBUTTONDOWN,
		MOUSE_BUTTON_UP   = SDL_MOUSEBUTTONUP,
		MOUSE_MOTION      = SDL_MOUSEMOTION,
		
		JOYSTICK_AXIS_MOTION    = SDL_JOYAXISMOTION,
		JOYSTICK_BALL_MOTION    = SDL_JOYBALLMOTION,
		JOYSTICK_HAT_MOTION     = SDL_JOYHATMOTION,
		JOYSTICK_BUTTON_DOWN    = SDL_JOYBUTTONDOWN,
		JOYSTICK_BUTTON_UP      = SDL_JOYBUTTONUP,
		JOYSTICK_DEVICE_ADDED   = SDL_JOYDEVICEADDED,
		JOYSTICK_DEVICE_REMOVED = SDL_JOYDEVICEREMOVED,
		
		CONTROLLER_AXIS_MOTION    = SDL_CONTROLLERAXISMOTION,
		CONTROLLER_BUTTON_DOWN    = SDL_CONTROLLERBUTTONDOWN,
		CONTROLLER_BUTTON_UP      = SDL_CONTROLLERBUTTONUP,
		CONTROLLER_DEVICE_ADDED   = SDL_CONTROLLERDEVICEADDED,
		CONTROLLER_DEVICE_REMOVED = SDL_CONTROLLERDEVICEREMOVED,
		CONTROLLER_DEIVE_REMAPPED = SDL_CONTROLLERDEVICEREMAPPED
	};
	
	Event(const SDL_Event &event);
	
	SDL_Event event;
	
	Type GetType() const;
};

inline Event::Type Event::GetType() const
{
	return (Type)event.type;
}
	
//	typedef struct SDL_KeyboardEvent
//	{
//		Uint32 type;        /**< ::SDL_KEYDOWN or ::SDL_KEYUP */
//		Uint32 timestamp;
//		Uint32 windowID;    /**< The window with keyboard focus, if any */
//		Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
//		Uint8 repeat;       /**< Non-zero if this is a key repeat */
//		Uint8 padding2;
//		Uint8 padding3;
//		SDL_Keysym keysym;  /**< The key that was pressed or released */
//	} SDL_KeyboardEvent;

class KeyboardEvent : public Event
{
public:
	enum State
	{
		PRESSED = SDL_PRESSED,
		RELEASED = SDL_RELEASED
	};
	
	
	enum KeyCode
	{
		// TODO
	};
	
	uint32_t GetWindowID() const;
	
	State GetState() const;
	bool IsRepeat() const;
	
	Scancode GetScancode() const;
	SDL_Keycode GetKeyCode() const;
};
	
inline uint32_t KeyboardEvent::GetWindowID() const
{
	return event.key.windowID;
}
	
inline KeyboardEvent::State KeyboardEvent::GetState() const
{
	return (State)event.key.state;
}
	
inline bool KeyboardEvent::IsRepeat() const
{
	return event.key.repeat > 0;
}
	
inline Scancode KeyboardEvent::GetScancode() const
{
	return (Scancode)event.key.keysym.scancode;
}
	
inline SDL_Keycode KeyboardEvent::GetKeyCode() const
{
	return event.key.keysym.sym;
}

//	typedef struct SDL_MouseMotionEvent
//	{
//		Uint32 type;        /**< ::SDL_MOUSEMOTION */
//		Uint32 timestamp;
//		Uint32 windowID;    /**< The window with mouse focus, if any */
//		Uint32 which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
//		Uint32 state;       /**< The current button state */
//		Sint32 x;           /**< X coordinate, relative to window */
//		Sint32 y;           /**< Y coordinate, relative to window */
//		Sint32 xrel;        /**< The relative motion in the X direction */
//		Sint32 yrel;        /**< The relative motion in the Y direction */
//	} SDL_MouseMotionEvent;

class MouseMotionEvent : public Event
{
public:
	uint32_t GetTimestamp() const;
	uint32_t GetWindowID() const;

	Point GetPosition() const;
	Point GetRelativePosition() const;
};
	
inline uint32_t MouseMotionEvent::GetTimestamp() const
{
	return event.motion.timestamp;
}

inline uint32_t MouseMotionEvent::GetWindowID() const
{
	return event.motion.windowID;
}

inline Point MouseMotionEvent::GetPosition() const
{
	return Point(event.motion.x, event.motion.y);
}

inline Point MouseMotionEvent::GetRelativePosition() const
{
	return Point(event.motion.xrel, event.motion.yrel);
}

	
//	typedef struct SDL_MouseButtonEvent
//	{
//		Uint32 type;        /**< ::SDL_MOUSEBUTTONDOWN or ::SDL_MOUSEBUTTONUP */
//		Uint32 timestamp;
//		Uint32 windowID;    /**< The window with mouse focus, if any */
//		Uint32 which;       /**< The mouse instance id, or SDL_TOUCH_MOUSEID */
//		Uint8 button;       /**< The mouse button index */
//		Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
//		Uint8 padding1;
//		Uint8 padding2;
//		Sint32 x;           /**< X coordinate, relative to window */
//		Sint32 y;           /**< Y coordinate, relative to window */
//	} SDL_MouseButtonEvent;
	
class MouseButtonEvent : public Event
{
public:
	enum State
	{
		PRESSED  = SDL_PRESSED,
		RELEASED = SDL_RELEASED
	};
	
	State GetState() const;
	uint32_t GetTimestamp() const;
	uint32_t GetWindowID() const;
	
	uint8_t GetButton() const;
	
	Point GetPosition() const;
};
	
inline MouseButtonEvent::State MouseButtonEvent::GetState() const
{
	return (State)event.button.state;
}

inline uint32_t MouseButtonEvent::GetTimestamp() const
{
	return event.button.timestamp;
}

inline uint32_t MouseButtonEvent::GetWindowID() const
{
	return event.button.windowID;
}

inline uint8_t MouseButtonEvent::GetButton() const
{
	return event.button.button;
}
	
inline Point MouseButtonEvent::GetPosition() const
{
	return Point(event.button.x, event.button.y);
}
	
	
//	typedef struct SDL_JoyButtonEvent
//	{
//		Uint32 type;        /**< ::SDL_JOYBUTTONDOWN or ::SDL_JOYBUTTONUP */
//		Uint32 timestamp;
//		SDL_JoystickID which; /**< The joystick instance id */
//		Uint8 button;       /**< The joystick button index */
//		Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
//		Uint8 padding1;
//		Uint8 padding2;
//	} SDL_JoyButtonEvent;
class JoystickButtonEvent : public Event
{
public:
	uint8_t GetButton() const;
};
	
inline uint8_t JoystickButtonEvent::GetButton() const
{
	return event.jbutton.button;
}

//typedef struct SDL_ControllerButtonEvent
//{
//	Uint32 type;        /**< ::SDL_CONTROLLERBUTTONDOWN or ::SDL_CONTROLLERBUTTONUP */
//	Uint32 timestamp;
//	SDL_JoystickID which; /**< The joystick instance id */
//	Uint8 button;       /**< The controller button (SDL_GameControllerButton) */
//	Uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
//	Uint8 padding1;
//	Uint8 padding2;
//} SDL_ControllerButtonEvent;

class ControllerButtonEvent : public Event
{
public:
	GameController::Button GetButton() const;
};

inline GameController::Button ControllerButtonEvent::GetButton() const
{
	return (GameController::Button)event.cbutton.button;
}
	
}