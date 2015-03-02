//
//  Room.h
//  rooms
//
//  Created by Gal Sasson on 2/21/15.
//
//

#ifndef __rooms__Room__
#define __rooms__Room__

#include <stdio.h>
#include "ofMain.h"

#include "ofxInterface.h"

using namespace ofxInterface;

class Room : public ofxInterface::Node
{
public:

	void setup(float w, float h);

	void setPlayerTranslation(const std::function<ofVec2f(const ofVec2f&)>& func);
	ofVec2f getPlayerTranslation(const ofVec2f& delta);


	void update(float dt);
	void draw();

private:

	ofColor color;
	vector<ofVec2f> topDoors;
	vector<ofVec2f> rightDoors;
	vector<ofVec2f> bottomDoors;
	vector<ofVec2f> leftDoors;

	std::function<ofVec2f(const ofVec2f&)> function;
};

#endif /* defined(__rooms__Room__) */
