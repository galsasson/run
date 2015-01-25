#include "ofApp.h"

#include "TouchManager.h"

#include "BitmapTextButton.h"

#define PAGE_W 8.5f
#define PAGE_H 11.0f

#define DPI		600


//--------------------------------------------------------------
void ofApp::setup(){

	ofEnableAntiAliasing();
	ofEnableAlphaBlending();

	nextSpriteId = 0;

	spritePage.load("scan1.png");

	squareSize = ofVec2f(0.5f*DPI, 0.5f*DPI);
	spriteSize = ofVec2f(256, 256);
	spriteImage.allocate(spriteSize.x, spriteSize.y, OF_IMAGE_COLOR_ALPHA);
	spriteFbo.allocate(spriteSize.x, spriteSize.y, GL_RGBA);

	pageMargin = 1*DPI;

	TouchManager::one().setup(&scene);

	page = new TextureButton();
	page->setup(&spritePage.getTexture());
	scene.addChild(page);

//	for (float y=margin; y<spritePage.getHeight()-margin; y+=squareSize.y)
//	{
//		for (float x=margin; x<spritePage.getWidth()-margin; x+=squareSize.x)
//		{
//			DraggableRect* rect = new DraggableRect();
//			rect->setup(squareSize.x, squareSize.y);
//			rect->setPosition(x, y);
//			rect->setPlane(1);
//			scene.addChild(rect);
//			rects.push_back(rect);
//		}
//	}

	page->setScale((float)ofGetWindowHeight() / spritePage.getHeight() * 2);


	// add buttons

	float y = 0;

	BitmapTextButton* btn = new BitmapTextButton();
	btn->setup("New Sprite-box");
	btn->setPosition(ofGetWindowWidth()-btn->getWidth(), y);
	btn->setPlane(2);
	scene.addChild(btn);
	ofAddListener(btn->eventClick, this, &ofApp::onNewSpriteClicked);
	y += btn->getHeight() + 5;

	btn = new BitmapTextButton();
	btn->setup("Create Sprite-box Row");
	btn->setPosition(ofGetWindowWidth()-btn->getWidth(), y);
	btn->setPlane(2);
	scene.addChild(btn);
	ofAddListener(btn->eventClick, this, &ofApp::onCreateRowClicked);
	y += btn->getHeight() + 5;

	btn = new BitmapTextButton();
	btn->setup("Generate Sprites");
	btn->setPosition(ofGetWindowWidth()-btn->getWidth(), y);
	btn->setPlane(2);
	scene.addChild(btn);
	ofAddListener(btn->eventClick, this, &ofApp::onCreateSpritesClicked);
}

void ofApp::onNewSpriteClicked(TouchEvent &event)
{
	createSpriteBox(0, 0);
}

void ofApp::onCreateRowClicked(TouchEvent &event)
{
	for (float x=pageMargin; x<spritePage.getWidth()-pageMargin; x+=squareSize.x)
	{
		createSpriteBox(x, pageMargin);
	}

}

void ofApp::createSpriteBox(float x, float y)
{
	DraggableRect* rect = new DraggableRect();
	rect->setup(nextSpriteId, spriteSize.x, spriteSize.y);
	rect->setPosition(x, y);
	rect->setPlane(1);
	page->addChild(rect);
	rects.push_back(rect);

	ofAddListener(rect->eventTouchDown, this, &ofApp::onSpriteBoxUpdated);
	ofAddListener(rect->eventTouchMove, this, &ofApp::onSpriteBoxUpdated);

	nextSpriteId++;
}

void ofApp::onSpriteBoxUpdated(TouchEvent &event)
{
	DraggableRect* rect = (DraggableRect*)event.receiver;
	updateSpriteImage(rect);
}

void ofApp::onCreateSpritesClicked(TouchEvent &event)
{
	ofFbo fbo;
	fbo.allocate(spriteSize.x*8, spriteSize.y*8);
	fbo.begin();
	ofClear(0);
	fbo.end();


	ofVec2f drawPointer(0, 0);

	for (int i=0; i<rects.size(); i++) {
		updateSpriteImage(rects[i]);

		fbo.begin();
		spriteFbo.draw(drawPointer);
		fbo.end();

		drawPointer.x += spriteImage.getWidth();
		if (drawPointer.x >= fbo.getWidth()) {
			drawPointer.y += spriteImage.getHeight();
			drawPointer.x = 0;
		}
	}

	ofImage img;
	img.allocate(fbo.getWidth(), fbo.getHeight(), OF_IMAGE_COLOR_ALPHA);
	fbo.getTexture().readToPixels(img.getPixels());
	img.save("spritePage.png");


	ofLoadImage(sheetTexture, "spritePage.png");
	spriteAnimation.setup(&sheetTexture, spriteSize.x, spriteSize.y, rects.size());
	spriteAnimation.setFrameHold(4);
	spriteAnimation.setLoopType(ofxSprite::LOOP_NORMAL);
	spriteAnimation.setDirection(ofxSprite::FORWARD);
	spriteAnimation.play();
}

void ofApp::updateSpriteImage(DraggableRect *rect)
{
	ofVec2f pos = rect->getPosition();

	spriteFbo.begin();
	ofClear(0);

	spritePage.drawSubsection(0, 0,
							  spriteFbo.getWidth(), spriteFbo.getHeight(),
							  pos.x, pos.y,
							  spriteFbo.getWidth(), spriteFbo.getHeight());

	spriteFbo.end();

//	spriteFbo.getTexture().readToPixels(spriteImage.getPixels());
}

//--------------------------------------------------------------
void ofApp::update(){
	spriteAnimation.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofClear(128);

	scene.render();

	float sampleW = spriteFbo.getWidth();
	float sampleH = spriteFbo.getHeight();

	ofSetColor(0, 128);
	ofFill();
	ofDrawRectangle(ofGetWindowWidth()-sampleW-20, ofGetWindowHeight()-sampleH-20, sampleW+20, sampleH+20);

	ofSetColor(255);
	spriteFbo.draw(ofGetWindowWidth()-sampleW, ofGetWindowHeight()-sampleH);

	ofPushMatrix();
	ofTranslate(ofGetWindowWidth()-sampleW/2, ofGetWindowHeight()-sampleH-sampleH/2);
	ofScale(0.5, 0.5);
	spriteAnimation.draw();
	ofPopMatrix();
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
	TouchManager::one().touchMove(0, ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	TouchManager::one().touchDown(0, ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	TouchManager::one().touchUp(0, ofVec2f(x, y));
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
