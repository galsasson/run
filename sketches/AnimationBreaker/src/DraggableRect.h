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
#include "ofxInterface.h"

class DraggableRect : public ofxInterface::Node
{
public:

	void setup(int id, float w, float h);

	void onTouchDown(ofxInterface::TouchEvent& event);
	void onTouchMove(ofxInterface::TouchEvent& event);
	void onTouchUp(ofxInterface::TouchEvent& event);

	void update(float dt);
	void draw();

	bool contains(const ofVec2f& p);

private:

	int id;
	
	ofVec2f touchOffset;
	bool bDragScale;

	bool scaleContains(const ofVec2f& local);

};
#endif /* defined(__AnimationBreaker__DraggableRect__) */
