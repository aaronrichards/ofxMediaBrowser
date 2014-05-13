//
//  ofxMediaBrowser.cpp
//
//  Created by Aaron Richards on 24/04/2014.
//
//

#include "ofxMediaBrowser.h"


//--------------------------------------------------------------
// Setup
//--------------------------------------------------------------
void ofxMediaBrowser::setup()
{
    setup(10, 10, 400, 600);
}

//--------------------------------------------------------------
void ofxMediaBrowser::setup(int x, int y)
{
    setup(x, y, 400, 600);
}

//--------------------------------------------------------------
void ofxMediaBrowser::setup(int x, int y, int width, int height)
{

    allowedImageExt.push_back("png");
    allowedImageExt.push_back("jpg");
    allowedVideoExt.push_back("mp4");
    allowedVideoExt.push_back("mov");
    
    mediaUI = new ofxUICanvas(x, y, width, height);
    mediaUI->addLabel("MEDIA", OFX_UI_FONT_LARGE);
    mediaUI->addSpacer();
    
    ddEvent = new ofxMediaBrowserEvent();
    ofAddListener(mediaUI->newGUIEvent, this, &ofxMediaBrowser::guiEvent);
    ofAddListener(ofEvents().exit, this, &ofxMediaBrowser::exit);
    ofAddListener(ofEvents().fileDragEvent, this, &ofxMediaBrowser::dragEvent);
    
}

//--------------------------------------------------------------
// Exit
//--------------------------------------------------------------
void ofxMediaBrowser::exit(ofEventArgs &e)
{
    
    if(ddEvent != NULL)
        delete ddEvent;
    
    if(mediaUI != NULL)
        delete mediaUI;
    
    ofRemoveListener(ofEvents().fileDragEvent, this, &ofxMediaBrowser::dragEvent);
    ofRemoveListener(ofEvents().exit, this, &ofxMediaBrowser::exit);
    
}




//--------------------------------------------------------------
// Events
//--------------------------------------------------------------
void ofxMediaBrowser::guiEvent(ofxUIEventArgs &e)
{
    
	string name = e.widget->getName();

    for (int i = 0; i < mediaElements.size(); i++)
    {
        if(mediaElements[i].filename == name)
        {
            ofxUIToggle *s = (ofxUIToggle *) e.widget;
            
            ddEvent->status = s->getValue();
            ddEvent->kind = mediaElements[i].kind;
            ddEvent->filename = mediaElements[i].filename;
            ddEvent->path = mediaElements[i].path;
            ofNotifyEvent(uiEvent, *ddEvent, this);
            
            break;
        }
    }

}

//--------------------------------------------------------------
void ofxMediaBrowser::dragEvent(ofDragInfo &dragInfo)
{
    
    if (insideDropArea(dragInfo.position))
    {
        if( dragInfo.files.size() > 0 )
        {
            processDroppedFiles(dragInfo.files);
        }
    }
    
}

//--------------------------------------------------------------
// Visibility
//--------------------------------------------------------------
void ofxMediaBrowser::show()
{
    mediaUI->setVisible(true);
}

//--------------------------------------------------------------
void ofxMediaBrowser::hide()
{
    mediaUI->setVisible(false);
}

//--------------------------------------------------------------
void ofxMediaBrowser::toggle()
{
    mediaUI->toggleVisible();
}

//--------------------------------------------------------------
// Helpers
//--------------------------------------------------------------
void ofxMediaBrowser::processDroppedFiles(vector<string> files)
{
    for(unsigned int k = 0; k < files.size(); k++)
    {
        
        ofFile file(files[k]);
        string ext = file.getExtension();
        
        if (!doesFileExist(file.path(), mediaElements))
        {
            if (isImageFile(ext))
            {
                
                MediaElement me;
                me.kind = IMAGE;
                me.path = file.path();
                me.filename = file.getFileName();
                
                mediaElements.push_back(me);
                mediaUI->addToggle(me.filename, false);
                ofLogNotice() << "Added file: " << file.getFileName();
                
            }
            else if (isVideoFile(ext))
            {
                
                MediaElement me;
                me.kind = VIDEO;
                me.path = file.path();
                me.filename = file.getFileName();
                
                mediaElements.push_back(me);
                mediaUI->addToggle(me.filename, false);
                ofLogNotice() << "Added file: " << file.getFileName();
                
            }
            else
            {
                ofLogNotice() << "Cannot process file: " << file.getFileName();
            }
            
        }
        
    }
    
}

//--------------------------------------------------------------
bool ofxMediaBrowser::doesFileExist(string file, vector<MediaElement> &haystack)
{
    for (int i = 0; i < haystack.size(); i++)
    {
        if (haystack[i].path == file)
        {
            ofLogNotice() << "File already exists: " << file;
            return true;
            
        }
    }
    return false;
}

//--------------------------------------------------------------
bool ofxMediaBrowser::isImageFile(string _ext)
{
    
    for (int i = 0; i < allowedImageExt.size(); i++)
    {
        if (_ext == allowedImageExt[i])
        {
            return true;
        }
    }
    
    return false;
    
}

//--------------------------------------------------------------
bool ofxMediaBrowser::isVideoFile(string _ext)
{
    
    for (int i = 0; i < allowedVideoExt.size(); i++)
    {
        if (_ext == allowedVideoExt[i])
        {
            return true;
        }
    }
    
    return false;
    
}



//--------------------------------------------------------------
bool ofxMediaBrowser::insideDropArea(ofPoint pos)
{
    
    if (pos.x >= mediaUI->getRect()->x && pos.x <= (mediaUI->getRect()->x + mediaUI->getRect()->width) && pos.y >= mediaUI->getRect()->y && pos.y <= (mediaUI->getRect()->y + mediaUI->getRect()->height))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}







