#pragma once

#include "ofMain.h"
#include "ofxUINode.h"
#include "DraggableRect.h"
#include "TextureButton.h"
#include "ofxSprite.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:

	void onNewSpriteClicked(TouchEvent& event);
	void onCreateSpritesClicked(TouchEvent& event);
	void onCreateRowClicked(TouchEvent& event);
	void onSpriteBoxUpdated(TouchEvent& event);

	void createSpriteBox(float x, float y);

	void updateSpriteImage(DraggableRect* rect);
	void transperifySpriteImage();

	ofImage spritePage;
	ofVec2f squareSize;
	ofVec2f spriteSize;
	float pageMargin;

	ofxUINode scene;
	vector<DraggableRect*> rects;
	TextureButton* page;

	int nextSpriteId;

	ofImage spriteImage;
	ofFbo spriteFbo;

	ofTexture sheetTexture;
	ofxSprite spriteAnimation;
};
