//
//  JointsTree.h
//  liquidfun
//
//  Created by Gal Sasson on 1/30/15.
//
//

#ifndef __liquidfun__JointsTree__
#define __liquidfun__JointsTree__

#include <stdio.h>
#include "ofMain.h"

#include "ofxBox2d.h"

#include "TreeNode.h"

class JointsTree : ofNode
{
public:

	void setup(ofxBox2d* box2d);

	void update(float dt);
	void draw();

private:

	void createJoint();

	ofxBox2d* box2d;
	b2World* m_world;

	b2Body* m_bodyA;
	b2Body* m_bodyB;

	void createChain();

	vector<ofxBox2dRect*> rects;

	vector<ofxBox2dRevoluteJoint*> joints;
};
#endif /* defined(__liquidfun__JointsTree__) */
