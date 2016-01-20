#ifndef _OFXSKINNEDCURVE
#define _OFXSKINNEDCURVE
/*
*  ofxSkinnedCurve.h
*  AxonSkin
*
*  Created by Cameron Browning on 9/14/10.
*  Copyright 2010 __MyCompanyName__. All rights reserved.
*
*/

#include "ofxCurve.h"
#include "ofMain.h"

class ofxSkinnedCurve : public ofxCurve{
public:

	ofxCurve curve;

	ofImage * skin;
	ofImage * shaft;

	ofImage axonImg;

	ofImage synapseImg;

	ofImage hillockImg1;
	ofImage hillockImg2;
	ofImage somaImg;
	ofImage jointImg;

	vector <ofImage*> base;
	vector <ofImage*> tail;
	ofImage * foot;

	int steps;

	ofxSkinnedCurve();
	~ofxSkinnedCurve();

	void drawSkin();
	void setupSkin(ofImage * shaft_in,int steps_in  = 10);
	void addBase(ofImage * img_in);
	void addTail(ofImage * img_in);
	void addFoot(ofImage * foot_in);

	int red,green,blue,alpha;
	void setColor(int r,int g, int b, int a);
	void setColor(int r,int g, int b);
	void updateAlpha(float a);
};

#endif
