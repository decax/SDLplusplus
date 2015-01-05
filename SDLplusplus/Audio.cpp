#include "Audio.h"

#include <SDL2/SDL.h>

namespace SDL {

Audio::Wave::Wave(const std::string &filename)
{
	SDL_LoadWAV_RW(SDL_RWFromFile(filename.c_str(), "rb"), 1, &spec.spec, &buffer, &length);

	spec.spec.callback = MixSound;
	spec.spec.userdata = this;
}
	
Audio::Wave::~Wave()
{
	SDL_FreeWAV(buffer);
}
	
void Audio::Wave::Play()
{
	Spec obtainedSpec;
	
	if (SDL_OpenAudio(&spec.spec, &obtainedSpec.spec) != 0) {
		// error
	}
	
	SDL_PauseAudio(0);
}
	
void Audio::Wave::MixSound(void *p_userData, uint8_t *p_bufferDest, int p_length)
{
	Wave *wave = (Wave *)p_userData;
	
	uint8_t *waveptr = wave->buffer + wave->position;
	int waveleft = wave->length - wave->position;
	
	while (waveleft <= p_length) {
		SDL_memcpy(p_bufferDest, waveptr, waveleft);
		p_bufferDest += waveleft;
		p_length -= waveleft;
		waveptr = wave->buffer;
		waveleft = wave->length;
		wave->position = 0;
	}
	SDL_memcpy(p_bufferDest, waveptr, p_length);
	wave->position += p_length;
}

std::string Audio::GetCurrentAudioDriver() const {
	auto audioDriver = SDL_GetCurrentAudioDriver();
	
	return audioDriver != nullptr ? audioDriver : "";
}
	
std::vector<std::string> Audio::GetDeviceNames() const
{
	std::vector<std::string> deviceNames;
	int numDevices = SDL_GetNumAudioDevices(1);
	
	deviceNames.reserve(numDevices);
	
	for (int i = 0; i < numDevices; i++) {
		deviceNames.push_back(SDL_GetAudioDeviceName(i, 1));
	}
	
	return deviceNames;
}

void Audio::Open(Spec desired)
{
	Spec obtainedSpec;
	
	if (SDL_OpenAudio(&desired.spec, &obtainedSpec.spec) != 0) {
		// error
	}
}
	
}