/*
*  ofxSkinnedCurve.cpp
*  AxonSkin
*
*  Created by Cameron Browning on 9/14/10.
*  Copyright 2010 __MyCompanyName__. All rights reserved.
*
*/

#include "ofxSkinnedCurve.h"

ofxSkinnedCurve::ofxSkinnedCurve(){
	foot = NULL;
	red = green = blue = alpha = 255;
}

void ofxSkinnedCurve::setColor(int r, int g, int b, int a){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}
void ofxSkinnedCurve::setColor(int r, int g, int b){
	red = r;
	green = g;
	blue = b;
}

void ofxSkinnedCurve::addBase(ofImage * img_in){
	base.push_back(img_in);	
}
void ofxSkinnedCurve::addTail(ofImage * img_in){
	tail.push_back(img_in);
}
void ofxSkinnedCurve::addFoot(ofImage * foot_in){
	foot = foot_in;	
}

void ofxSkinnedCurve::setupSkin(ofImage * shaft_in, int steps_in){
	steps = steps_in;
	shaft = shaft_in;
}

ofxSkinnedCurve::~ofxSkinnedCurve(){
	// empty destructor
}

void ofxSkinnedCurve::updateAlpha(float a){
	alpha = (int)(255.0f*a);
}

void ofxSkinnedCurve::drawSkin(){

	ofPoint thisPoint;
	ofPoint prevPoint;
float prevRot = 0;
	int fireCount = (ofGetFrameNum())/5 % (steps+1);

	for(int i=0;i<=steps+1;i++){
		bool scaling = true;
		bool isTail = false;

		float pct = 1.0f/(float)steps*i;
		thisPoint = plot(pct);



		if(i>0){
			if(i<base.size()+1){
				skin = base[i-1];
				if(i==1){
					scaling = false;
				}
			} else if( i > ( steps - tail.size()+1 ) ){
				int j = steps-(i)+1;
				
				skin = tail[j];
				if(j==0){
						
					scaling = false;
					isTail = true;
				}
			} else {
				skin = shaft;
			}
			// scaling = true;

			float r = atan2(thisPoint.y-prevPoint.y,thisPoint.x-prevPoint.x);
			glPushMatrix();

			float skinlength = ofDist(prevPoint.x,prevPoint.y,thisPoint.x,thisPoint.y);
			float skinScale = skinlength/skin->getWidth();

			
			 ofSetColor(red,green,blue,alpha);	

			ofEnableAlphaBlending();
			if(!isTail){
			glTranslatef(prevPoint.x,prevPoint.y,0);
			} else {
glTranslatef(thisPoint.x,thisPoint.y,0);
			}
			if(!isTail){
			glRotatef(r*180/PI,0,0,1);
			} else {
glRotatef(prevRot*180/PI,0,0,1);

			}
			prevRot = r;
			if(scaling){

				skin->draw(-1*skin->getHeight()/2,-1*skin->getHeight()/2,skinlength+skin->getHeight(),skin->getHeight());
				//	ofNoFill();
				//	ofSetLineWidth(1);
				//	ofRect(-1*skin->height/2,-1*skin->height/2,skinlength+skin->height,skin->height);
			} else {
				// cout << skin->width << ", " << skin->height << endl;
				//				if(skin->width==105)
				
				 skin->draw(-1*skin->getHeight()/2,-1*skin->getHeight()/2);
				// ofDrawBitmapString(ofToString(pct),15,0);
				//	ofNoFill();
				//	ofSetLineWidth(1);
				//				ofRect(-1*skin->height/2,-1*skin->height/2,skinlength+skin->height,skin->height);
				//ofRect(-1*skin->height/2,-1*skin->height/2,skin->width,skin->height);
			}

			if(i>2){
				if(jointImg.isAllocated()) jointImg.draw(-jointImg.getWidth()/2,-jointImg.getHeight()/2);
			}
			glPopMatrix();

			if(i==steps && foot!=NULL){
				glPushMatrix();
				glTranslatef(thisPoint.x,thisPoint.y,0);
				glRotatef(r*180/PI,0,0,1);
				foot->draw(-foot->getWidth()/2,-foot->getHeight()/2);
				glPopMatrix();
			}
			ofDisableAlphaBlending();
		}
		
		prevPoint = thisPoint;
	}
}