#include "testApp.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void testApp::setup(){

	// we don't want to be running to fast
	ofSetVerticalSync(true);

	//our send and recieve strings
	msgRx	= "";

	//are we connected to the server - if this fails we
	//will check every few seconds to see if the server exists
	weConnected = tcpClient.setup("127.0.0.1", 6667);


	connectTime = 0;
	deltaTime = 0;
	packet = 0;

	tcpClient.setVerbose(true);

	myPlayer.loadMovie("film720.mp4");
	myPlayer.play();

	w = myPlayer.width;
	h = myPlayer.height;

	myTexture.allocate(w, h, GL_RGB);

	ofHideCursor();



}

//--------------------------------------------------------------
void testApp::update(){
	myPlayer.idleMovie();
	ofBackground(0, 0, 0);

	unsigned char * pixels = myPlayer.getPixels();

	//we are connected - check what we get back
	if(weConnected){
		//if data has been sent lets update our text
		string str = tcpClient.receiveRaw();
		if( str.length() > 0 ){
			msgRx = str;
			packet = ofToFloat(msgRx);



			for(int i=0;i<w*h*4;i++) {
				pixels[i] = pixels[i] + packet;
			}


		}
	}else{
		//if we are not connected lets try and reconnect every 5 seconds
		deltaTime = ofGetElapsedTimeMillis() - connectTime;

		if( deltaTime > 5000 ){
			weConnected = tcpClient.setup("127.0.0.1", 6667);
			connectTime = ofGetElapsedTimeMillis();
		}

	}
	myTexture.loadData(pixels, w, h, GL_RGB);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xFFFFFF);
	myTexture.draw(0,0,w, h);
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
