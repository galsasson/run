//
//  JointsTree.cpp
//  liquidfun
//
//  Created by Gal Sasson on 1/30/15.
//
//

#include "JointsTree.h"

void JointsTree::setup(ofxBox2d* _box2d, float x, float y)
{
	box2d = _box2d;
	m_world = box2d->getWorld();

	createChain(x, y);
}

void JointsTree::update(float dt)
{
	for (ofxBox2dRevoluteJoint* joint: joints)
	{
//		joint->setMotorSpeed(sin((float)ofGetFrameNum()/30)*10);
		float val = (sin((float)ofGetFrameNum()/20)+1)*1.05;
//		if (val < 0) val *= 100;
		float val2 = floor(val);
		joint->setMaxMotorTorque((val2>=2)?val2:0);
//		joint->setMotorSpeed(-1);
//		float speed = (val<0)?-100:1;
//		cout<<val<<" "<<val2<<endl;
//		joint->setMotorSpeed(speed);
	}

}

void JointsTree::draw()
{
	ofSetColor(50, 50, 50);
	for (int i=0; i<rects.size(); i++)
	{
		rects[i]->draw();
	}
}

void JointsTree::createChain(float x, float y)
{
	for (int i=0; i<20; i++) {
		ofxBox2dRect* r = new ofxBox2dRect();
		r->setPhysics((i==0)?0:0.1f, 0.53f, 0.1);
//		r->setup(m_world, 100+i*40, 50, 50, 20, -1);
		r->setup(m_world, x, y, 10, 4, -1);
		rects.push_back(r);

		if (i>=1) {
			ofxBox2dRevoluteJoint* joint = new ofxBox2dRevoluteJoint();
			joint->setup(m_world, rects[rects.size()-1-1]->getBody(), rects[rects.size()-1]->getBody(), ofVec2f(4.5, 0), ofVec2f(-4.5, 0));
			joints.push_back(joint);

//			if (i==1) {
				joint->setMotorSpeed(1);
				joint->setMaxMotorTorque(1);
				joint->enableMotor(true);
				joint->setLimits(-80, 80);
				joint->enableLimits(true);
//			}
		}



	}

}


void JointsTree::createBird()
{
	for (int i=0; i<2; i++) {
		ofxBox2dRect* r = new ofxBox2dRect();
		r->setPhysics(0.1f, 0.53f, 0.1);
		//		r->setPosition(50+i*10, 50);
		r->setup(m_world, ofRectangle(100+i*40, 50, 50, 20));
		r->alive = false;
		rects.push_back(r);

		if (i>=1) {
			ofxBox2dRevoluteJoint* joint = new ofxBox2dRevoluteJoint();
			joint->setup(m_world, rects[i-1]->getBody(), rects[i]->getBody(), ofVec2f(20, 10), ofVec2f(-20, 10));
			joints.push_back(joint);

			if (i==1) {
				joint->setMotorSpeed(10);
				joint->setMaxMotorTorque(200);
				joint->enableMotor(true);
			}
		}
		else {
			root = r;
		}

		
		
	}
	
}
