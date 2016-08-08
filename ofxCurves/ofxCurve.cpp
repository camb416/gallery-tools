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
	tweenVal = 16 ;
	setOrig = true;
}

ofxCurve::ofxCurve(float x1,float y1,float x2,float y2,float x3,float y3, float x4, float y4){
    isAnimated = true;
    tweenVal = 16 ;
    setOrig = true;
    set(x1,y1,x2,y2,x3,y3,x4,y4);
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
void ofxCurve::draw(){
	ofDrawBezier(start.x,start.y,startControl.x,startControl.y,endControl.x,endControl.y,end.x,end.y);
}
