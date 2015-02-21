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

class JointsTree
{
public:

	void setup(ofxBox2d* box2d, float x, float y);
	void setPosition(float x, float y);

	void update(float dt);
	void draw();

private:

	ofxBox2d* box2d;
	b2World* m_world;
	ofxBox2dRect* root;

	void createChain(float x, float y);
	void createBird();

	vector<ofxBox2dRect*> rects;

	vector<ofxBox2dRevoluteJoint*> joints;
};
#endif /* defined(__liquidfun__JointsTree__) */
