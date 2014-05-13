//
//  ofxMediaBrowser.h
//
//  Created by Aaron Richards on 24/04/2014.
//
//

#ifndef __ofxMediaBrowser__
#define __ofxMediaBrowser__

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxMediaBrowserEvent.h"

class ofxMediaBrowser
{
    
    public:
        
        enum FileKind
        {
            IMAGE,
            VIDEO
        };
        
        struct MediaElement
        {
            FileKind kind;
            string path;
            string filename;
        };
        
        void setup();
        void setup(int x, int y);
        void setup(int x, int y, int width, int height);
        void exit(ofEventArgs &e);
        
        void dragEvent(ofDragInfo &dragInfo);
        void guiEvent(ofxUIEventArgs &e);
        
        ofxUICanvas *mediaUI;
        ofEvent<ofxMediaBrowserEvent> uiEvent;
        
    private:
        
        ofxMediaBrowserEvent *ddEvent;
        
        vector<MediaElement> mediaElements;
        vector<string> allowedImageExt;
        vector<string> allowedVideoExt;
        
        bool isImageFile(string _ext);
        bool isVideoFile(string _ext);
        
        void processDroppedFiles(vector<string> files);
        bool doesFileExist(string file, vector<MediaElement> &haystack);
        bool insideDropArea(ofPoint pos);
    
};


#endif /* defined(ofxMediaBrowser) */
