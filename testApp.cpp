#include "testApp.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void testApp::setup(){

	// we don't want to be running to fast
	ofSetVerticalSync(true);

	msgRx	= "";

	//are we connected to the server - if this fails we
	//will check every few seconds to see if the server exists
	weConnected = tcpClient.setup("127.0.0.1", 11999);

	connectTime = 0;
	deltaTime = 0;

	tcpClient.setVerbose(true);

}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(230, 230, 230);

	//we are connected - lets send our text and check what we get back
	if(weConnected){
        //if data has been sent lets update our text
		string str = tcpClient.receive();
		if( str.length() > 0 ){
			msgRx = str;
		}
	}else{
		//if we are not connected lets try and reconnect every 5 seconds
		deltaTime = ofGetElapsedTimeMillis() - connectTime;

		if( deltaTime > 5000 ){
			weConnected = tcpClient.setup("127.0.0.1", 11999);
			connectTime = ofGetElapsedTimeMillis();
		}

	}
}

//--------------------------------------------------------------
void testApp::draw(){


}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

