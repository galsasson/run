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

#include "TreeNode.h"

class JointsTree : ofNode
{
public:

	void setup();

	void update(float dt);
	void draw();

private:

	vector<TreeNode*> nodes;

};
#endif /* defined(__liquidfun__JointsTree__) */
