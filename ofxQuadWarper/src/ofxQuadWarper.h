#ifndef _OFXQUADWARPER
#define _OFXQUADWARPER

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "DragPoint.h"

class ofxQuadWarper{
public:
	int x,y,w,h;
	DragPoint* pts;
	ofPoint * origPts;
	bool isActive;

	bool isSetup();

	string xmlString;

	int c;
	float destW,destH;

	bool snap;
	bool limit;

	ofxQuadWarper();
	~ofxQuadWarper();
	void setup(string file_in, int w_in,int h_in, bool snap_in = false, bool limit_in=true);
	void update(int x_in, int y_in); // accepts mousex and mousey
	void draw(int x_in, int y_in,float destW_in,float destH_in);
	void draw(int x_in,int y_in);
	void mousedown();
	void mouseup();
	void reset();
	ofPoint* getWarp(float pct=1.0f);
	ofPoint* getWarpPct();

	string file;


	DragPoint* selectedPoint;

	void saveSettings();

private:

	ofxXmlSettings settings;
	void loadSettings();
	bool setupFlag;

	// for debugging UI
	int mx,my;



};
#endif