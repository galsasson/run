//
//  DraggableRect.cpp
//  AnimationBreaker
//
//  Created by Gal Sasson on 1/18/15.
//
//

#include "DraggableRect.h"


void DraggableRect::setup(int _id, float w, float h)
{
	id = _id;
	setSize(w, h);

	ofAddListener(eventTouchDown, this, &DraggableRect::onTouchDown);
	ofAddListener(eventTouchMove, this, &DraggableRect::onTouchMove);
	ofAddListener(eventTouchUp, this, &DraggableRect::onTouchUp);
}

void DraggableRect::onTouchDown(TouchEvent &event)
{
	touchOffset = toLocal(event.position);
}

void DraggableRect::onTouchMove(TouchEvent &event)
{
	ofVec2f parentPos = ((ofxUINode*)parent)->toLocal(event.position);
	setPosition(parentPos-touchOffset);
}

void DraggableRect::onTouchUp(TouchEvent &event)
{

}

void DraggableRect::update(float dt)
{

}

void DraggableRect::draw()
{
	ofSetColor(50, 255, 50);
	ofSetLineWidth(2);
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofFill();
	ofDrawEllipse(getWidth()/2, getHeight()/2, 5, 5);

	ofDrawBitmapString(ofToString(id), 0, 0);
}

