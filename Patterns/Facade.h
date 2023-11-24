#pragma once
#include <iostream>

//Printese in rotaiiiii

class AudioMP3 {
	bool loaded = false;
public:
	void loadAudio() {
		loaded = true;
		std::cout << "Loading audio...\n";
	}

	void playAudio() {
		if (loaded) {
			std::cout << "Playing audio...\n";
		}
		else {
			std::cout << "No audio loaded!\n";
		}
	}
};

class VideoBuffer {
	bool loaded = false;
	bool subtitles = false;
protected:
	void setSubtitles() {
		subtitles = true;
	}
public:
	void loadVideo() {
		loaded = true;
		std::cout << "Loading video...\n";
	}

	void playVideo() {
		if (loaded) {
			std::cout << "Playing video...\n";
		}
		else {
			std::cout << "No audio loaded!\n";
		}
	}
};

class Subtitles : public VideoBuffer {
	bool loaded = false;
public:
	void loadSubtitles() {
		loaded = true;
		setSubtitles();
		std::cout << "Loading subtitles...\n";
	}

};

class MovieLoader {
public:
	void loadMovie() {
		AudioMP3* audio = new AudioMP3();
		audio->loadAudio();
		VideoBuffer* video = new VideoBuffer();
		video->loadVideo();
		Subtitles* sub = new Subtitles();
		sub->loadSubtitles();

		video->playVideo();
		audio->playAudio();
		std::cout << "Enjoy the movie!";
	}
};