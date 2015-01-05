#include "Event.h"

namespace SDL {

Event::Event(const SDL_Event &p_event)
: event(p_event)
{
}

}