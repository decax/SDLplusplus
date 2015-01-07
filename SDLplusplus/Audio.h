#pragma once

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include <string>
#include <vector>

namespace SDL {

class Audio
{
public:
	class Spec
	{
		friend class Wave;
		
	public:
		Spec() {}
		
//	private:
		SDL_AudioSpec spec;
	};

	class Wave
	{
	public:
		Wave(const std::string &filename);
		~Wave();
		
		void Play();
		
	private:
		Spec spec;
		
		uint8_t *buffer;
		uint32_t length;
		int position;
		
		static void MixSound(void *userData, uint8_t *stream, int length);
	};
	
	void Open(Spec desired);
	
	std::vector<std::string> GetDeviceNames() const;
	std::string GetCurrentAudioDriver() const;
	
private:
	
};
	
}
