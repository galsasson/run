#include "ofApp.h"

#define PAGE_W 8.5f
#define PAGE_H 11.0f

#define DPI		600

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetFrameRate(60);
//	ofEnableAlphaBlending();
//	ofEnableSmoothing();


	ofVec2f squareSize(0.5f*DPI, 0.5f*DPI);
	float margin = 1*DPI;

	// allocate page fbo
	pageSize = ofVec2f(PAGE_W*DPI, PAGE_H*DPI);
	fbo.allocate(pageSize.x, pageSize.y);

	fbo.begin();
	ofClear(255);

	ofNoFill();
	ofSetLineWidth(1);
	ofSetColor(0);
	for (float y=margin; y<fbo.getHeight()-margin; y+=squareSize.y)
	{
		for (float x=margin; x<fbo.getWidth()-margin; x+=squareSize.x)
		{
			cout<<"x = "<<x<<", y = "<<y<<endl;
			ofDrawRectangle(x, y, squareSize.x, squareSize.y);
		}
	}

	fbo.end();

	ofImage img;
	img.allocate(fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR_ALPHA);
	fbo.getTexture().readToPixels(img.getPixels());
	img.save("AnimationPage.png");
}

//--------------------------------------------------------------
void ofApp::update()
{


}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(255);

	ofPushMatrix();
	float scaleFactor = (float)ofGetWindowHeight() / fbo.getHeight();
	ofScale(scaleFactor, scaleFactor);

	ofSetColor(255);
	fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
