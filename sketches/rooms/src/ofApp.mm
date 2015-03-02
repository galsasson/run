#include "ofApp.h"
#include "Constants.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);


	ofxInterface::TouchManager::one().setup(&scene);

	player.setup();
	player.setPlane(1);
	player.setPosition(30, 30);
	scene.addChild(&player);

	ofVec2f minRoomSize(100, 80);
	ofVec2f maxRoomSize(400, 300);
	ofVec2f roomSize((ofGetWidth()-C::screenPadding*2)/3, (ofGetHeight()-C::screenPadding*2)/3);
	ofVec2f pos(C::screenPadding, C::screenPadding);

	for (int i=0; i<9; i++) {
		Room* r = new Room();
		r->setup(roomSize.x, roomSize.y);
		r->setPosition(C::screenPadding + (i%3)*roomSize.x, C::screenPadding + (i/3)*roomSize.y);

		float xMap = ofRandom(-5, 5);
		float yMap = ofRandom(-5, 5);
		r->setPlayerTranslation([xMap, yMap] (const ofVec2f& delta) -> ofVec2f {
			return ofVec2f(xMap, yMap)*delta;
		});
		rooms.push_back(r);
		scene.addChild(r);
	}

}

//--------------------------------------------------------------
void ofApp::update()
{
	float dt = 1.0f / 60;

	player.update(dt);
}


//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(255);

	scene.render();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch)
{
	prevTouch = ofVec2f(touch.x, touch.y);
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch)
{
	ofVec2f delta = ofVec2f(touch.x, touch.y) - prevTouch;
	prevTouch = ofVec2f(touch.x, touch.y);

	for (Room* r : rooms) {
		if (r->contains(player.getPosition())) {
			player.move(r->getPlayerTranslation(delta));
			applyBounds();
			return;
		}
	}

	player.move(delta/2);
	applyBounds();
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch)
{
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}

void ofApp::applyBounds()
{
	// screen bounds
	if (player.getX()<0) {
		player.setX(0);
	}
	else if (player.getX() > ofGetWidth()-1) {
		player.setX(ofGetWidth()-1);
	}
	if (player.getY() < 0) {
		player.setY(0);
	}
	else if (player.getY() > ofGetHeight()-1) {
		player.setY(ofGetHeight()-1);
	}

}


Room* ofApp::getRoomAt(float x, float y)
{
	ofVec2f p = ofVec2f(x, y);

	for (Room* r : rooms) {
		if (r->contains(p)) {
			return r;
		};
	}

	return NULL;
}

