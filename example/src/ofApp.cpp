#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    
    ofSetBackgroundColor(200);
    fileDropArea.setup();
    ofAddListener(fileDropArea.uiEvent, this, &ofApp::guiEvent);
    
}

//--------------------------------------------------------------
void ofApp::exit()
{
    ofRemoveListener(fileDropArea.uiEvent, this, &ofApp::guiEvent);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{

}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxMediaBrowserEvent &e)
{
    ofLogNotice() << "State:" << e.status << " Kind:" << e.kind << " Filename:" << e.filename << " Path:" << e.path;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    
    switch (key) {
        case ' ':
            fileDropArea.toggle();
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
