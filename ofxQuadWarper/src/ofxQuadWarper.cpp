#include "ofxQuadWarper.h"

ofxQuadWarper::ofxQuadWarper(){
	setupFlag = false;
	pts = new DragPoint[4];
	origPts = new ofPoint[4];
	isActive = true;

	selectedPoint = NULL;
	snap = false;
	limit = true;
	xmlString = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<quad>\n";
	file = "dummy.xml";
	c = 0x000000;
}
void ofxQuadWarper::reset(){
	pts[0].loc.set(0,0);
	pts[1].loc.set(w,0);
	pts[2].loc.set(w,h);
	pts[3].loc.set(0,h);
}
void ofxQuadWarper::saveSettings(){
	settings.pushTag("quad");
	for(int i=0;i<4;i++){
		settings.setValue("point:x",(pts[i].loc.x)/w,i);
		settings.setValue("point:y",(pts[i].loc.y)/h,i);
	}
	settings.saveFile(file);
	settings.popTag();

}
void ofxQuadWarper::loadSettings(){
	cout << "TRYING TO LOAD THIS FILE: " << file << endl;
	settings.loadFile(file);
	string str;

	settings.pushTag("quad",0);

	//we see how many points we have stored in <point> tags
	int numPtTags = settings.getNumTags("point");

	if(numPtTags > 0){
		int totalToRead = MIN(numPtTags, 4);
		for(int i = 0; i < totalToRead; i++){
			float x = settings.getValue("point:x", 0.0f, i);
			float y = settings.getValue("point:y", 0.0f, i);
			pts[i].loc.set(x*(float)w,y*(float)h);
			cout << "QUAD POINT: " << x << ", " << y << endl;
		}
	}
	settings.popTag();
}

ofxQuadWarper::~ofxQuadWarper(){
	// this makes a rather ugly error...
	//delete pts;
	//delete origPts;
}

void ofxQuadWarper::setup(string file_in, int w_in,int h_in, bool snap_in, bool limit_in){

	file = file_in;

	w = w_in;
	h = h_in;

	snap = snap_in;
	limit = limit_in;

	reset();

	origPts[0] = pts[0].loc;
	origPts[1] = pts[1].loc;
	origPts[2] = pts[2].loc;
	origPts[3] = pts[3].loc;
	loadSettings();
	setupFlag = true;
}

bool ofxQuadWarper::isSetup(){
	if(w!=NULL){
		return true;
	} else {
		return false;
	}
}

void ofxQuadWarper::update(int x_in,int y_in){
	mx = x_in-x;
	my = y_in-y;
	int ex = x_in-x;
	int ey = y_in - y;

	if(isActive){
		if(ex>-7 && ex < w+7 && ey > -7 && ey<h+7 && limit || ex>pts[0].loc.x-7 && ex < pts[1].loc.x+7 && ey > pts[0].loc.y-7 && ey<pts[2].loc.y+7){
			c = 0xFFFFFF;
			// find nearest point
			float nearDist = 10;
			int nearID = -1;

			for (int i=0;i<4;i++){
				float d = ofDist(ex,ey,pts[i].loc.x*destW/w,pts[i].loc.y*destH/h);
				if(d<nearDist){
					nearDist = d;
					nearID = i;
				}
			}
			for(int i=0;i<4;i++){
				if(i==nearID){
					pts[nearID].isSelected = true;
					selectedPoint = &pts[nearID];
				} else {
					pts[i].isSelected = false;
				}
			}
			if(nearID<0){
				selectedPoint = NULL;
			}
			// cout << "selected point::: " << nearID << endl;
		} else {
			c = 0x00FF00;
			selectedPoint = NULL;

		}
	} else {
		if(limit){
			selectedPoint->loc.x = MAX(0,MIN((x_in-x)/destW*w,w));
			selectedPoint->loc.y = MAX(0,MIN((y_in-y)/destH*h,h));
		} else {
			selectedPoint->loc.x = (x_in-x)/destW*w;
			selectedPoint->loc.y = (y_in-y)/destH*h;
		}
		if(snap){

			int nearID;
			for(int i=0;i<4;i++){
				if(	pts[i].isSelected){
					nearID=i;
					break;
				}
			}
			cout << "SNAPSNAPSNAP" << nearID << endl;
			switch(nearID){
			case 0:
				pts[1].loc.y = selectedPoint->loc.y;
				pts[3].loc.x = selectedPoint->loc.x;
				break;
			case 1:
				pts[0].loc.y = selectedPoint->loc.y;
				pts[2].loc.x = selectedPoint->loc.x;
				break;
			case 2:
				pts[3].loc.y = selectedPoint->loc.y;
				pts[1].loc.x = selectedPoint->loc.x;
				break;
			case 3:
				pts[2].loc.y = selectedPoint->loc.y;
				pts[0].loc.x = selectedPoint->loc.x;
				break;
			}
		}
	}
	for(int i=0;i<4;i++){
		pts[i].update();
	} 
}

void ofxQuadWarper::draw(int x_in,int y_in){
	draw(x_in,y_in,w,h);
}
void ofxQuadWarper::draw(int x_in,int y_in,float destW_in,float destH_in){

	destW = destW_in;
	destH = destH_in;
	ofSetLineWidth(1);
	x = x_in;
	y = y_in;
	glPushMatrix();
	glTranslatef(x_in,y_in,0);
	ofSetColor(c);
	ofNoFill();
	ofSetLineWidth(1);
	ofRect(0,0,destW,destH);
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString(file,0,-20);
	ofBeginShape();
	for(int i=0;i<4;i++){
		ofNoFill();
		ofSetHexColor(0xFFFFFF);
		ofVertex(pts[i].loc.x/w*destW,pts[i].loc.y/h*destH);

		pts[i].draw(w/destW,h/destH);
		if(isActive){
			ofSetHexColor(0x00FFFF);
		} else {
			ofSetHexColor(0x0000FF);
		}
		ofFill();
		ofRect(origPts[i].x/w*destW-2,origPts[i].y/h*destH-2,4,4);

		ofNoFill();
		ofLine(origPts[i].x/w*destW,origPts[i].y/h*destH,pts[i].loc.x/w*destW,pts[i].loc.y/h*destH);
	}
	ofEndShape(true);

	if(selectedPoint!=NULL){
		ofCircle(selectedPoint->loc.x/w*destW,selectedPoint->loc.y/h*destH,15);
		string msg = ofToString(selectedPoint->loc.x) + ","+ofToString(selectedPoint->loc.y);
		ofDrawBitmapString(msg,selectedPoint->loc.x/w*destW+15,selectedPoint->loc.y/h*destH-10);
	}

	ofSetColor(255,0,0);
	ofNoFill();
	ofLine(mx-5,my-5,mx+5,my+5);
	ofLine(mx+5,my-5,mx-5,my+5);

	glPopMatrix();



}
void ofxQuadWarper::mousedown(){
	if(selectedPoint!=NULL){
		// cout << "SELECTED POINT!=NULL";
		isActive = false;
		selectedPoint->isDragging = true;


	} else {
		// cout << "SELECTED POINT is NULL";
	}
	cout << endl;
}
void ofxQuadWarper::mouseup(){
	isActive = true;
	selectedPoint = NULL;
	for(int i=0;i<4;i++){
		pts[i].isDragging = false;
	}

}

ofPoint tempArray [4];

ofPoint* ofxQuadWarper::getWarp(float pct){
	// ick, that looks dangerous!
	//	ofPoint * returnArray = new ofPoint[4];
	// ofPoint returnArray [4];
	for(int i=0;i<4;i++){
		tempArray[i] = pts[i].loc;
		if(pct!=1.0f) tempArray[i]*=1/pct;
	}
	return tempArray; 
}

ofPoint* ofxQuadWarper::getWarpPct(){
	// this has got to be a leak... why would you do that!?!
	// ofPoint * returnArray = new ofPoint [4];
	// ofPoint returnArray [4];
	for(int i=0;i<4;i++){
		tempArray[i].set(pts[i].loc.x/w,pts[i].loc.y/h);
	}
	return tempArray;
}