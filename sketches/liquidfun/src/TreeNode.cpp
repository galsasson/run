//
//  TreeNode.cpp
//  liquidfun
//
//  Created by Gal Sasson on 1/30/15.
//
//

#include "TreeNode.h"


void TreeNode::setup(float _length)
{
	length = _length;
}



void TreeNode::update(float dt)
{

}

void TreeNode::draw()
{
	ofPushMatrix();
	ofMultMatrix(getGlobalTransformMatrix());


	ofSetColor(255);
	ofSetLineWidth(1);
	ofDrawLine(0, 0, length, 0);

	ofPopMatrix();
}