/*
*  ofxCurve.cpp
*  NeuronConnections
*
*  Created by Cameron Browning on 8/26/10.
*  Copyright 2010 __MyCompanyName__. All rights reserved.
*
*/

#include "ofxCurve.h"

// constructor
ofxCurve::ofxCurve(){
	isAnimated = true;
	tweenVal = 4 ;
	setOrig = true;
}

ofxCurve::ofxCurve(float x1,float y1,float x2,float y2,float x3,float y3, float x4, float y4){
    isAnimated = true;
    tweenVal = 4 ;
    setOrig = true;
    set(x1,y1,x2,y2,x3,y3,x4,y4);
}

ofxCurve::ofxCurve(ofVec3f a,
                   ofVec3f b,
                   ofVec3f c,
                   ofVec3f d){
    isAnimated = true;
    tweenVal = 4;
    setOrig = true;
    set(a,b,c,d);
    
}




ofxCurve::~ofxCurve(){
	// empty destructor
}

// plot a point along the curve
ofPoint ofxCurve::plot(float pct_in){
	float pct = MAX(0.0f,MIN(pct_in,1.0f));
	float cX = 3*(startControl.x-start.x);
	float bX = 3*(endControl.x-startControl.x)-cX;
	float aX = end.x-start.x-cX-bX;
	float cY = 3*(startControl.y-start.y);
	float bY = 3*(endControl.y-startControl.y)-cY;
	float aY = end.y-start.y-cY-bY; //  +ofRandom(-10,10);

	ofPoint returnVal;
	returnVal.x = aX*pct*pct*pct + bX*pct*pct + cX*pct + start.x; //+ofRandom(-5,5);
	returnVal.y = aY*pct*pct*pct + bY*pct*pct + cY*pct + start.y;
	return returnVal;
}

ofPoint ofxCurve::plot3d(float pct_in){
    float pct = MAX(0.0f,MIN(pct_in,1.0f));
    float cX = 3*(startControl.x-start.x);
    float bX = 3*(endControl.x-startControl.x)-cX;
    float aX = end.x-start.x-cX-bX;
    float cY = 3*(startControl.y-start.y);
    float bY = 3*(endControl.y-startControl.y)-cY;
    float aY = end.y-start.y-cY-bY; //  +ofRandom(-10,10);
    
    float cZ = 3*(startControl.z-start.z);
    float bZ = 3*(endControl.z-startControl.z)-cZ;
    float aZ = end.z-start.z-cZ-bZ;
    
    ofPoint returnVal;
    returnVal.x = aX*pct*pct*pct + bX*pct*pct + cX*pct + start.x; //+ofRandom(-5,5);
    returnVal.y = aY*pct*pct*pct + bY*pct*pct + cY*pct + start.y;
    returnVal.z = aZ*pct*pct*pct + bZ*pct*pct + cZ*pct + start.z;
    return returnVal;
}


float ofxCurve::getSlope(float pct_in){
    ofPoint normal = getDirection(pct_in);
    
    float angle = atan2(normal.y,normal.x);
    return angle;
    
}

int ofxCurve::setCtrl(ofPoint ctrlPt_in, int whichCtrlPt){
    if(whichCtrlPt ==0){
        startControlDest = ctrlPt_in;
    } else if(whichCtrlPt==1){
        endControlDest = ctrlPt_in;
    } else {
        // error
        return 1;
    }
    return 0;
}

ofPoint ofxCurve::getDirection(float pct_in){
    float t = MAX(0.0f,MIN(pct_in,1.0f)); // from plot
    
    // getting the slope of a cubic bezier at a given point
    // http://stackoverflow.com/questions/15397596/find-all-the-points-of-a-cubic-bezier-curve-in-javascript
    // http://stackoverflow.com/questions/4089443/find-the-tangent-of-a-point-on-a-cubic-bezier-curve-on-an-iphone/4091430#4091430
    float B0_dt = -3 * (1-t) * (1-t);
    float B1_dt = 3*(1-t) * (1-t) -6 * t * (1-t);
    float B2_dt = - 3 * t * t + 6 * t * (1-t);
    float B3_dt = 3 * t * t;
    
    // rate of change (derivative)
    float px_dt = (B0_dt * start.x) + (B1_dt * startControl.x) + (B2_dt * endControl.x) + (B3_dt * end.x);
    float py_dt = (B0_dt * start.y) + (B1_dt * startControl.y) + (B2_dt * endControl.y) + (B3_dt * end.y);
    float pz_dt = (B0_dt * start.z) + (B1_dt * startControl.z) + (B2_dt * endControl.z) + (B3_dt * end.z);
    
    ofPoint dir;
    dir.set(px_dt,py_dt, pz_dt);
    dir.normalize();
    return dir;
    
}

// animate the curve
void ofxCurve::update(){
	if(isAnimated){
		start += (startDest-start)/tweenVal;
		startControl += (startControlDest-startControl)/tweenVal;
		endControl += (endControlDest-endControl)/tweenVal;
		end += (endDest-end)/tweenVal;
	}
}

// set the curve (from points)
void ofxCurve::set(ofPoint start_in, ofPoint startControl_in, ofPoint endControl_in,ofPoint end_in){

	startDest = start_in;
	startControlDest = startControl_in;
	endControlDest = endControl_in;
	endDest = end_in;

	if(setOrig){
		startOrig = startDest;
		startControlOrig = startControlDest;
		endControlOrig = endControlDest;
		endOrig = endDest;
		setOrig = false;
	}


	if(!isAnimated){
		start = start_in;
		startControl = startControl_in;
		endControl = endControl_in;
		end = end_in;
	}
}

// set curve (from coords)
void ofxCurve::set(float x1,float y1,float x2,float y2,float x3,float y3, float x4, float y4){

	startDest.set(x1,y1);
	startControlDest.set(x2,y2);
	endControlDest.set(x3,y3);
	endDest.set(x4,y4);

	if(setOrig){
		startOrig = startDest;
		startControlOrig = startControlDest;
		endControlOrig = endControlDest;
		endOrig = endDest;
		setOrig = false;
	}

	if(!isAnimated){
		start.set(x1,y1);
		startControl.set(x2,y2);
		endControl.set(x3,y3);
		end.set(x4,y4);
	}
}

// set new end point
void ofxCurve::setEnd(ofPoint end_in){
	endDest = end_in;	
}

// draw (no style info)
void ofxCurve::draw(bool bDrawControlPoints){
    if(bDrawControlPoints){
        ofDrawLine(start,startControl);
        ofDrawLine(end,endControl);
        ofDrawEllipse(startControl,5,5);
        ofDrawEllipse(endControl,5,5);
    }
	ofDrawBezier(start.x,start.y, start.z,startControl.x,startControl.y, startControl.z,endControl.x,endControl.y,endControl.z,end.x,end.y,end.z);
}
