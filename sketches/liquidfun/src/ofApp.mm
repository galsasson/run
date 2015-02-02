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
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

	// setup time measurements
	TIME_SAMPLE_SET_FRAMERATE(60.0f);
	TIME_SAMPLE_SET_DRAW_LOCATION(TIME_MEASUREMENTS_TOP_LEFT);
	TIME_SAMPLE_DISABLE_AVERAGE();
	TIME_SAMPLE_SET_REMOVE_EXPIRED_THREADS(true);
	TIME_SAMPLE_GET_INSTANCE()->setDeadThreadTimeDecay(0.985);
//	TIME_SAMPLE_DISABLE();
//	TIME_SAMPLE_GET_INSTANCE()->drawUiWithFontStash("font/VeraMono.ttf");


	bFire = false;

	Resources::one().setup();

	box2d.init();
	box2d.setGravity(0, 30);
	box2d.setFPS(20);
	box2d.setIterations(10, 20);

	box2d.createBounds();
	box2d.enableGrabbing();

	particleSystem.setup(box2d.getWorld(), 10000, 0, 6);

	ofPolyline line;
	line.addVertex(0, 540);
	line.addVertex(220, 360);
	line.addVertex(260, 350);
	line.addVertex(370, 380);
	line.addVertex(550, 500);
	line.addVertex(710, 530);
	line.addVertex(775, 380);
	line.addVertex(850, 325);
	line.addVertex(ofGetWidth(), 260);
	box2d.createEdge(line, b2_staticBody, 0.5);


	for (int i=0; i<10; i++)
	{
		ofxBox2dRect* rect = new ofxBox2dRect();
		float density = ofRandom(0.3, 5);
		rect->setPhysics(density, 0.53f, 0.1);
		float size = ofMap(density, 0.3, 5, 40, 70, true);
		rect->setup(box2d.getWorld(), ofRandom(10, 500), 100, size, size);
		rects.push_back(rect);
	}

	viewRect = ofRectangle(300, 200, ofGetWidth()-300, ofGetHeight()-200);

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
		sprites[i]->setPosition(box2d.boxToWorld(positions[i]));
	}

#else
	for (ofxSprite* sprite : sprites) {
		sprite->update();
	}
#endif

	if (bFire) {
		createNewParticle(0, firePos);
	}
}


#define BIND_ONCE
//--------------------------------------------------------------
void ofApp::draw()
{
//	ofBackground(255);

	ofPushMatrix();
	ofTranslate(-viewRect.x, -viewRect.y);
	float s = ofGetWidth() / viewRect.width;
	ofScale(s, s);

	ofSetColor(255);
	Resources::one().getTexture("background")->draw(0, 0);

//	drawSprites();


	ofSetColor(50);
	for (int i=0; i<rects.size(); i++)
	{
		rects[i]->draw();
	}

	ofSetColor(200, 50, 50);
	ofFill();
	ofDrawEllipse(firePos, 20, 20);

//	box2d.draw();

	particleSystem.draw();
	ofPopMatrix();

	ofSetColor(0);
	ofDrawBitmapString("particles: " + ofToString(particleSystem.getParticleCount()), 300, 10);

}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch)
{
	if (touch.x < ofGetWidth()*0.3f) {
		bFire = true;
	}
	else {
		firePos = toWorld(ofVec2f(touch.x, touch.y));
	}

//	createNewParticle(touch.id, toWorld(ofVec2f(touch.x, touch.y)));


}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch)
{
	if (touch.x < ofGetWidth()*0.3f) {

	}
	else {
		firePos = toWorld(ofVec2f(touch.x, touch.y));
	}


//	createNewParticle(touch.id, toWorld(ofVec2f(touch.x, touch.y)));


}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch)
{
	if (touch.x < ofGetWidth()*0.3f) {
		bFire = false;
	}

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

void ofApp::createNewParticle(int id, const ofVec2f &p)
{
	return createNewParticle(id, p.x, p.y);
}


void ofApp::createNewParticle(int id, float x, float y)
{
	ofxSprite* s = new ofxSprite();
	ofTexture* tex;
	if (x < ofGetWidth()/2) {
		tex = Resources::one().getTexture("x-trans");
	}
	else {
		tex = Resources::one().getTexture("hollow-dot");
	}
	s->setup(tex, 0.125f, 0.125f, 12);
	s->setPosition(x, y, 0);
	s->setLoopType(ofxSprite::LOOP_NORMAL);
	s->setDirection(ofxSprite::FORWARD);
	s->setTintColot(ofColor(0));
	s->setFrameHold(4);
	s->setScale(ofRandom(10, 30));
	s->setAnchor(0.5f, 0.5f);
	s->play();
	sprites.push_back(s);

	particleSystem.createParticle(x, y, 0, 0, s);

}


void ofApp::drawSprites()
{
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
}


ofVec2f ofApp::toWorld(const ofVec2f &p)
{
	cout<<"p = "<<p<<", w = "<<p - viewRect.getTopLeft() * (ofGetWidth() / viewRect.width)<<endl;
	return p - viewRect.getTopLeft() * (ofGetWidth() / viewRect.width);
}
