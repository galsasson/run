//
//  Resources.h
//  RingViewer
//
//  Created by Gal Sasson on 1/7/15.
//
//

#ifndef __RingViewer__Resources__
#define __RingViewer__Resources__

#include <stdio.h>
#include "ofMain.h"

class Resources
{
public:

	static Resources& one()
	{
		static Resources instance;
		// Instantiated on first use.
		return instance;
	}

	void setup();

//	ofxFontStash* fontHeader;
//	ofxFontStash* fontBody;

	ofTexture* getTexture(const string& name);

private:
	Resources() {}

	void loadFonts();
	void loadTextures();

	bool loadTexture(const string& name, const string& filename, bool doMipmaps = false);
	map<string, ofTexture*> textures;

	// make sure there are no copies
	Resources(Resources const&);
	void operator=(Resources const&);


};
#endif /* defined(__RingViewer__Resources__) */
