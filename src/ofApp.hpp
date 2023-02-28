#pragma once

#include "AudioVisualizer.hpp"
#include "ofMain.h"

class ofApp : public ofBaseApp {

  private:
    ofSoundPlayer sound;
    AudioVisualizer visualizer;
    ofRectangle pgbar; //progress bar

    bool playing = false;
    char mode = '1';
    char songmode = 'x';
    vector<string> songs = {"beat.wav","geesebeat.wav","pigeon-coo.wav","rock-song.wav"}; 
    bool clicked = false; 
    int size = songs.size() - 1; 

    int cur_x, cur_y = 0;
    float sound_length;

    float progress = 0;
    float lastPos = 0;
    int song = 0; // variable to skip songs 

  public:
    void setup();
    void update();
    void draw();

    void drawMode1(vector<float> amplitudes);
    void drawMode2(vector<float> amplitudes);
    void drawMode3(vector<float> amplitudes);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
