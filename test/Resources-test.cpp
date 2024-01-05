#include <iostream>

#include "Application.hpp"

using namespace std;

void loadFont() {
    cerr << "Test 1: Load fonts" << endl;
    FontHolder fonts;
    fonts.loadFontFromFile();
}

void loadTexture() {
    cerr << "Test 2: Load textures" << endl;
    TextureHolder textures;
    textures.loadTextureFromFile();
}

void loadSoundBuffer() {
    cerr << "Test 3: Load sound buffers" << endl;
    SoundBufferHolder soundBuffers;
    soundBuffers.loadSoundBufferFromFile();
}

void loadMusic() {
    cerr << "Test 4: Load music" << endl;
    MusicPlayer music;
}

int main() {
    loadFont();
    loadTexture();
    loadSoundBuffer();
    loadMusic();
    return 0;
}
