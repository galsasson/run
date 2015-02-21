#include "ofMain.h"
#include "ofAppiOSWindow.h"
#include "ofApp.h"

int main() {

	ofiOSWindowSettings settings;
	settings.enableRetina = true;
	settings.enableDepth = false;
	settings.enableAntiAliasing = true;
	settings.numOfAntiAliasingSamples = 4;
	settings.enableHardwareOrientation = true;
	settings.enableHardwareOrientationAnimation = true;
	settings.glesVersion = OFXIOS_RENDERER_ES1;
	settings.windowMode = OF_FULLSCREEN;

	ofCreateWindow(settings);
    
	ofRunApp(new ofApp);
}
