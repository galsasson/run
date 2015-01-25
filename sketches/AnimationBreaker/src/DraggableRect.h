//
//  DraggableRect.h
//  AnimationBreaker
//
//  Created by Gal Sasson on 1/18/15.
//
//

#ifndef __AnimationBreaker__DraggableRect__
#define __AnimationBreaker__DraggableRect__

#include <stdio.h>
#include "ofxUINode.h"

class DraggableRect : public ofxUINode
{
public:

	void setup(int id, float w, float h);

	void onTouchDown(TouchEvent& event);
	void onTouchMove(TouchEvent& event);
	void onTouchUp(TouchEvent& event);

	void update(float dt);
	void draw();

private:

	int id;
	
	ofVec2f touchOffset;


};
#endif /* defined(__AnimationBreaker__DraggableRect__) */