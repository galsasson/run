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

	bDragScale = false;
}

void DraggableRect::onTouchDown(TouchEvent &event)
{
	ofVec2f local = toLocal(event.position);

	if (scaleContains(local)) {
		bDragScale = true;
		touchOffset = local-getSize();
	}
	else {
		touchOffset = local;
	}
}

void DraggableRect::onTouchMove(TouchEvent &event)
{
	ofVec2f parentPos = ((ofxUINode*)parent)->toLocal(event.position);

	if (bDragScale) {
		setSize((parentPos-touchOffset) - getPosition());
	}
	else {
		setPosition(parentPos-touchOffset);
	}
}

void DraggableRect::onTouchUp(TouchEvent &event)
{
	bDragScale = false;

}

bool DraggableRect::contains(const ofVec2f &p)
{
	ofVec2f local = toLocal(p);

	if (local.x >= 0 &&
		local.y >= 0 &&
		local.x < size.x &&
		local.y < size.y) {
		return true;
	}

	if (scaleContains(local)) {
		return true;
	}

	return false;
}

bool DraggableRect::scaleContains(const ofVec2f &local)
{
	if (local.x > size.x &&
		local.y > size.y &&
		local.x < size.x+30 &&
		local.y < size.y+30) {
		return true;
	}

	return false;
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
	ofSetColor(255, 0, 0);
	ofDrawEllipse(getWidth()/2, getHeight()/2, 10, 10);

	ofSetColor(50, 50, 255);
	ofNoFill();
	ofDrawRectangle(size.x, size.y, 30, 30);

	ofDrawBitmapString(ofToString(id), 0, 0);
}

