//
//  ofxMediaBrowserEvent.h
//
//  Created by Aaron Richards on 13/05/2014.
//
//

#ifndef ContentScaleDrag_DragDropEvent_h
#define ContentScaleDrag_DragDropEvent_h

#include "ofMain.h"

class ofxMediaBrowserEvent : public ofEventArgs
{
    
    public:
        
        int status;
        int kind;
        string path;
        string filename;
        
        static ofEvent <ofxMediaBrowserEvent> events;
    
};

#endif
