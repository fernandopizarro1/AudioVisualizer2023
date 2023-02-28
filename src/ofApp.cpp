#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup() {
    sound.load("beat.wav");           // Loads a sound file (in bin/data/)
    sound.setVolume(1);               // Sets the song volume
    ofSetBackgroundColor(36, 32, 56); // Sets the Background Color
}

//--------------------------------------------------------------
void ofApp::update() {
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate();               // Updates all sound players
    visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    progress = sound.getPosition();
}

//--------------------------------------------------------------
void ofApp::draw() {
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */

    // Progress Bar
    ofSetColor(256);
    ofFill();

    float pos = playing ? progress : lastPos;
    int percent = pos * 100;
    ofDrawBitmapString("Song Progress: " + ofToString(percent) + "%", 0, 30);
    ofRectangle pgbar(0,40,pos * ofGetWidth(),10);
    ofDrawRectangle(pgbar);

    // Mode Selection
    if (!playing) {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1') {
        drawMode1(amplitudes);
    } else if (mode == '2') {
        drawMode2(amplitudes);
    } else if (mode == '3') {
        drawMode3(amplitudes);
    } else if (mode == 'a') {
        ofDrawBitmapString("Visualizer is paused", 0, 15);
    }

    ofSetColor(256);
    if (songmode == 'x') {
        ofDrawBitmapString("No Mode Selected", ofGetWidth() / 2, 15);
        sound.setLoop(false);
    } else if (songmode == 'r') {
        ofDrawBitmapString("Repeat Mode Selected", ofGetWidth() / 2, 15);
        sound.setLoop(true);
    }

    // ofDrawBitmapString("Current Mouse Position: " + ofToString(cur_x) + ", " + ofToString(cur_y), 0, 30);
}
void ofApp::drawMode1(vector<float> amplitudes) {
    ofFill();        // Drawn Shapes will be filled in with color
    ofSetColor(256); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(0, 0, ofRandom(255));
    ofRectangle bars;
    int bands = amplitudes.size();
    int numbands = 0;
    for (int i = 0; i < bands; i++) {
        bars.x = numbands;
        numbands += ofGetWidth() / bands;
        bars.y = ofGetHeight() - 100;
        bars.width = ofGetWidth() / bands;
        bars.height = amplitudes[i] * 2;
        ofDrawRectRounded(bars,10);
    }
    ofSetBackgroundColor(56,32,36); // Sets the Background Color
}

void ofApp::drawMode2(vector<float> amplitudes) {
    ofSetLineWidth(5); // Sets the line width
    ofNoFill();        // Only the outline of shapes will be drawn
    ofSetColor(256);   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++) {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
    ofSetBackgroundColor(32,36,56);
}

void ofApp::drawMode3(vector<float> amplitudes) {
    ofSetColor(0); // This resets the color of the "brush" to white
    ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
    ofSetBackgroundColor(36,32,56);
    // YOUR CODE HERE
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // This method is called automatically when any key is pressed
    switch (key) {
    case 'p':
        if (playing) {
            sound.stop();
        } else {
            sound.play();
        }
        playing = !playing;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    case 'a':
        mode = 'a';
        break; 
    case 'd': 
        (song >= size) ? song -= size: song += 1; 
        if (playing) {
        sound.load(songs[song]);
        sound.play();
        } else {
            sound.load(songs[song]); }
        break;
    case '-': {
        if (sound.getVolume() > 0) {
        sound.setVolume(sound.getVolume() - 0.1); } 
        } break; 
    case '=': {
        if (sound.getVolume() < 1) {
        sound.setVolume(sound.getVolume() + 0.1); }
        } break; 
    case 'r': {
        if (songmode != 'r') {
            songmode = 'r';
        } else if (clicked) {
            songmode = 'x'; 
            clicked = false; 
        }
    } break; 
    }  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    clicked = true;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    cur_x = x;
    cur_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    sound.setPosition(double(x)/ofGetWidth());
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
//--------------------------------------------------------------