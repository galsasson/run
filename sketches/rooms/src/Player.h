//
//  Player.h
//  rooms
//
//  Created by Gal Sasson on 2/21/15.
//
//

#ifndef __rooms__Player__
#define __rooms__Player__

#include <stdio.h>
#include "ofMain.h"

#include "ofxInterface.h"

using namespace ofxInterface;

class Player : public ofxInterface::Node
{
public:

	void setup();

	void update(float dt);
	void draw();

};
#endif /* defined(__rooms__Player__) */
