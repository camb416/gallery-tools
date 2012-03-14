#include "DragPoint.h"

DragPoint::DragPoint(){
c = 0xFFFFFF;
isSelected = false;
isDragging = false;

}
void DragPoint::setup(int w_in,int h_in){

}
DragPoint::~DragPoint(){
// nothin
}
void DragPoint::update(){
	if(isDragging){
		c = 0xFF0000;

	} else if(isSelected){
		
	c = 0xFFFF00;
	} else {
	c = 0xFFFFFF;
	}
}
void DragPoint::draw(float xs_in,float ys_in){
	ofSetColor(c);
ofRect(loc.x/xs_in-2,loc.y/ys_in-2,4,4);
}
