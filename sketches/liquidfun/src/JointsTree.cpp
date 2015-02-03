//
//  JointsTree.cpp
//  liquidfun
//
//  Created by Gal Sasson on 1/30/15.
//
//

#include "JointsTree.h"

void JointsTree::setup(ofxBox2d* _box2d)
{
	box2d = _box2d;
	m_world = box2d->getWorld();

	createChain();
}

void JointsTree::update(float dt)
{

}

void JointsTree::draw()
{
	ofSetColor(50, 50, 50);
	for (int i=0; i<rects.size(); i++)
	{
		rects[i]->draw();
	}

	for (int i=0; i<joints.size(); i++)
	{
		joints[i]->draw();
	}
}

void JointsTree::createChain()
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
				joint->setMotorSpeed(1000);
				joint->setMaxMotorTorque(2000000);
				joint->enableMotor(true);
			}
		}



	}

}

void JointsTree::createJoint()
{
	//body and fixture defs - the common parts
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;

	//two shapes
	b2PolygonShape boxShape;
	boxShape.SetAsBox(2,2);
	b2CircleShape circleShape;
	circleShape.m_radius = 2;

	//make box a little to the left
	bodyDef.position.Set(1, 10);
	fixtureDef.shape = &boxShape;
	m_bodyA = m_world->CreateBody( &bodyDef );
	m_bodyA->CreateFixture( &fixtureDef );

	//and circle a little to the right
	bodyDef.position.Set( 6, 10);
	fixtureDef.shape = &circleShape;
	m_bodyB = m_world->CreateBody( &bodyDef );
	m_bodyB->CreateFixture( &fixtureDef );
}
