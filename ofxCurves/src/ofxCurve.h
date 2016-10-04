#ifndef _OFXCURVE
#define _OFXCURVE
/*
 *  ofxCurve.h
 *  NeuronConnections
 *
 *  Created by Cameron Browning on 8/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class ofxCurve{

public:
	ofxCurve();
    ofxCurve(float x1,float y1,float x2,float y2,float x3,float y3, float x4, float y4);
    
    ofxCurve(ofVec3f a,
             ofVec3f b,
             ofVec3f c,
             ofVec3f d);
    
	~ofxCurve();
	
	ofPoint start;
	ofPoint startControl;
	ofPoint end;
	ofPoint endControl;
	
	ofPoint startDest;
	ofPoint startControlDest;
	ofPoint endDest;
	ofPoint endControlDest;
	
	ofPoint startOrig;
	ofPoint startControlOrig;
	ofPoint endControlOrig;
	ofPoint endOrig;
	
	bool isAnimated;
	int tweenVal;
	bool setOrig;
	
	ofPoint plot(float pct_in);
    ofPoint plot3d(float pct_in);
    
    
    ofPoint getDirection(float pct_in);
    float getSlope(float pct_in);
    
    ofPoint getNormal(float pct_in){ ofLog(OF_LOG_WARNING) << "getNormal is Deprecated. Use GetDirection"; return getDirection(pct_in); };
    
    int setCtrl(ofPoint ctrlPt_in, int whichCtrlPt);
	
	void update();
	void set(ofPoint start_in, ofPoint startControl_in, ofPoint endControl_in,ofPoint end_in);
	void set(float x1,float y1,float x2,float y2,float x3,float y3, float x4, float y4);
	void setEnd(ofPoint end_in);
	void draw(bool bDrawControlPoints = false);
};

#endif