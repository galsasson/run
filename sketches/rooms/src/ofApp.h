#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "ofxInterface.h"
#include "Player.h"
#include "Room.h"

using namespace ofxInterface;

class ofApp : public ofxiOSApp {
	
    public:
        void setup();
        void update();
        void draw();
        void exit();
	
        void touchDown(ofTouchEventArgs & touch);
        void touchMoved(ofTouchEventArgs & touch);
        void touchUp(ofTouchEventArgs & touch);
        void touchDoubleTap(ofTouchEventArgs & touch);
        void touchCancelled(ofTouchEventArgs & touch);

        void lostFocus();
        void gotFocus();
        void gotMemoryWarning();
        void deviceOrientationChanged(int newOrientation);


private:

	ofxInterface::Node scene;

	Player player;
	vector<Room*> rooms;

	ofVec2f prevTouch;

	void applyBounds();
	Room* getRoomAt(float x, float y);
	Room* getRoomIntersecting(const ofVec2f& p, const ofVec2f& s);
};


