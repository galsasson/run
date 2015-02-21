#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

}

//--------------------------------------------------------------
void ofApp::update()
{
}


//--------------------------------------------------------------
void ofApp::draw()
{
	ofClear(255);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch)
{
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch)
{
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
