#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"

#include "ofxUINode.h"
#include "ofxLiquidFun.h"
#include "ofxSprite.h"

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

	void createNewParticle(int id, float x, float y);
	void createNewParticle(int id, const ofVec2f& p);

	void drawSprites();

	ofVec2f toWorld(const ofVec2f& p);

	ofxUINode scene;

	ofxBox2d box2d;
	vector<ofxBox2dRect*> rects;
	vector<ofxSprite*> sprites;

	ofxBox2dParticleSystem particleSystem;

	ofxSprite* sp;

	ofFbo fbo;

	ofRectangle viewRect;

	bool bFire;
	ofVec2f firePos;
};


