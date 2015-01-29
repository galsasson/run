#include "ofApp.h"
#include "Resources.h"
#include "ofxTimeMeasurements.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableAlphaBlending();
	ofEnableAntiAliasing();
	ofEnableSmoothing();

	ofSetFrameRate(60);
	ofSetBackgroundAuto(false);


	// setup time measurements
	TIME_SAMPLE_SET_FRAMERATE(60.0f);
	TIME_SAMPLE_SET_DRAW_LOCATION(TIME_MEASUREMENTS_TOP_RIGHT);
	TIME_SAMPLE_DISABLE_AVERAGE();
	TIME_SAMPLE_SET_REMOVE_EXPIRED_THREADS(true);
	TIME_SAMPLE_GET_INSTANCE()->setDeadThreadTimeDecay(0.985);
//	TIME_SAMPLE_GET_INSTANCE()->drawUiWithFontStash("font/VeraMono.ttf");



	Resources::one().setup();

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.setFPS(30);

	box2d.createBounds();
	box2d.enableGrabbing();

	particleSystem.setup(box2d.getWorld(), 10000, 0, 12);


	for (int i=0; i<0; i++)
	{
		ofxBox2dRect* rect = new ofxBox2dRect();
		float density = ofRandom(0.1, 1);
		rect->setPhysics(density, 0.53f, 0.1);
		rect->setup(box2d.getWorld(), ofRandom(10, 500), 100, density*80, density*80);
		rects.push_back(rect);
	}

}

//--------------------------------------------------------------
void ofApp::update(){

#if 1
	box2d.update();

	int nParts = particleSystem.getParticleCount();
	ofxSprite** sprites = (ofxSprite**)particleSystem.getUserDataBuffer();
	b2Vec2* positions = particleSystem.getPositionBuffer();

	for (int i=0; i<nParts; i++) {
		sprites[i]->update();
		sprites[i]->setPosition(positions[i].x*OFX_BOX2D_SCALE, positions[i].y*OFX_BOX2D_SCALE, 0);
	}

#else
	for (ofxSprite* sprite : sprites) {
		sprite->update();
	}
#endif

	if (ofGetFrameNum()%60 == 0) {
		cout<<"Particles = "<<ofApp::sprites.size()<<endl;
	}
}


//#define BIND_ONCE
//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(255);

	ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
	// this is actually multiply
//	glBlendFunc(GL_DST_COLOR, GL_ZERO);

#ifdef BIND_ONCE
	if (sprites.size()>0) {
		sprites[0]->bindTex();
	}

	for (int i=0; i<sprites.size(); i++) {
		sprites[i]->drawNoBind();
	}

	if (sprites.size()>0) {
		sprites[0]->unbindTex();
	}
#else
	for (int i=0; i<sprites.size(); i++) {
		sprites[i]->draw();
	}
#endif

	ofSetColor(50);
	for (int i=0; i<rects.size(); i++)
	{
		rects[i]->draw();
	}
//	particleSystem.draw();

//	ofSetColor(0);
//	ofDrawBitmapString("particles: " + ofToString(particleSystem.getParticleCount()), 100, 100);
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
//	ofxBox2dRect* rect = new ofxBox2dRect();
//	rect->setPhysics(4.0f, 0.53f, 0.1);
//	rect->setup(box2d.getWorld(), touch.x, touch.y, 5, 5);
//	rects.push_back(rect);

//	if (touch.numTouches == 2) {
		createNewParticle(touch.id, touch.x, touch.y);
//	}
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
//	if (touch.numTouches == 2) {
		createNewParticle(touch.id, touch.x, touch.y);
//	}
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

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


void ofApp::createNewParticle(int id, float x, float y)
{
	ofxSprite* s = new ofxSprite();
	ofTexture* tex;
	if (x < ofGetWidth()/2) {
		tex = Resources::one().getTexture("x");
	}
	else {
		tex = Resources::one().getTexture("hollow-dot");
	}
	s->setup(tex, 0.125f, 0.125f, 11);
	s->setPosition(x, y, 0);
	s->setLoopType(ofxSprite::LOOP_NORMAL);
	s->setDirection(ofxSprite::FORWARD);
//	s->setTintColot(ofColor(255, 220));
	s->setFrameHold(4);
	s->setScale(ofRandom(30, 60));
	s->setAnchor(0.5f, 0.5f);
	s->play();
	sprites.push_back(s);

	particleSystem.createParticle(x, y, 0, 0, s);

}
