//
//  Resources.cpp
//  RingViewer
//
//  Created by Gal Sasson on 1/7/15.
//
//

#include "Resources.h"

void Resources::setup()
{
//	loadFonts();

	loadTextures();
}


ofTexture* Resources::getTexture(const string &name)
{
	if (textures.find(name) == textures.end()) {
		ofLogError("Resources::getTexture", "no such texture: %s", name.c_str());
		return NULL;
	}

	return textures[name];
}




//void Resources::loadFonts()
//{
//	ofLogNotice("Resources", "loading fonts");
//	
//	fontHeader = new ofxFontStash();
//	fontHeader->setup("font/Geogtq-Bd.ttf");
//	fontHeader->setKerning(true);
//	fontHeader->setCharacterSpacing(3);
//	
//	fontBody = new ofxFontStash();
//	fontBody->setup("font/Proxima Nova-Regular.ttf");
//	fontBody->setKerning(true);
//}

void Resources::loadTextures()
{
	loadTexture("dot", "spritesheets/dot.png");
	loadTexture("star", "spritesheets/star.png");
	loadTexture("star-small", "spritesheets/star-small.png");
	loadTexture("hollow-dot", "spritesheets/hollow-dot.png");
	loadTexture("square", "spritesheets/square.png");
	loadTexture("line", "spritesheets/line.png");
	loadTexture("inflating", "spritesheets/inflating.png");
	loadTexture("rotating", "spritesheets/rotating.png");
	loadTexture("x", "spritesheets/x.png");
	loadTexture("loading", "spritesheets/loading.png");

}



bool Resources::loadTexture(const string &name, const string& filename, bool doMipmaps)
{
	ofTexture* tex = new ofTexture();

	bool ok = ofLoadImage(*tex, filename);
	if (ok) {
		if (doMipmaps) {
			tex->bind();
			glGenerateMipmap(tex->getTextureData().textureTarget);
			tex->unbind();
			tex->setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		}

		tex->setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		textures[name] = tex;
	}
	else {
		ofLogError("Resources::loadTexture", "failed to load texture: %s", filename.c_str());
		delete tex;
	}

	return ok;
}
