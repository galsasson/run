//
//  TreeNode.h
//  liquidfun
//
//  Created by Gal Sasson on 1/30/15.
//
//

#ifndef __liquidfun__TreeNode__
#define __liquidfun__TreeNode__

#include <stdio.h>
#include "ofMain.h"

class TreeNode : ofNode
{
public:

	void setup(float length);

	void update(float dt);
	void draw();

private:

	float length;
	
};
#endif /* defined(__liquidfun__TreeNode__) */
