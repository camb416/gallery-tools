#ifndef _DRAGPOINT
#define _DRAGPOINT

#include "ofMain.h"

class DragPoint{
    
public:
    
    ofPoint loc;
    int c;
    bool isDragging;
    bool isSelected;
    
    DragPoint();
    ~DragPoint();
    void draw(float destW,float destH);
    void update();
    void setup(int w_in,int h_in); // takes in the constraints
    
};


#endif