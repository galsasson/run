//
//  Room.cpp
//  rooms
//
//  Created by Gal Sasson on 2/21/15.
//
//

#include "Room.h"


void Room::setup(float w, float h)
{
	setSize(w, h);

	color = ofColor::fromHsb(ofRandom(0, 255), 255, 255);
	cout<<color.getHue()<<" "<<color.getSaturation()<<" "<<color.getBrightness()<<endl;
	cout<<ofColor::limit()<<endl;
}

void Room::setPlayerTranslation(const std::function<ofVec2f (const ofVec2f &)> &func)
{
	function = func;
}

ofVec2f Room::getPlayerTranslation(const ofVec2f &delta)
{
	return function(delta);
}

void Room::update(float dt)
{

}


void Room::draw()
{
	ofSetColor(color, 100);
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());

	ofSetColor(0);
	ofSetLineWidth(2);
	ofNoFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());
}