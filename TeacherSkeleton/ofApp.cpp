#include "ofApp.h"

void ImageShape::draw() {


	ofPushMatrix();
	ofMultMatrix(getMatrix());  // get the current transform for the object


	image.draw(-image.getWidth()/2.0, -image.getHeight()/2.0);
	
	ofPopMatrix();

}
//--------------------------------------------------------------
void ofApp::setup() {
	
	string imageFile = "images/ship.png";
	if (!im.image.load(imageFile)) {
		cout << "FATAL ERROR: can't load image file" << imageFile << endl;
		ofExit();
	}

	im.rotation = 0.0;
	im.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);

}


//--------------------------------------------------------------
void ofApp::update(){
   // test -  move object along heading 
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(ofColor::white);
	im.draw();

	ofSetColor(ofColor::white);
	ofDrawLine(im.pos, im.pos + 150 * heading());
}

//--------------------------------------------------------------
//
void ofApp::keyPressed(int key){

	switch (key) {
	case OF_KEY_LEFT:
		// do something if left arrow key pressed
		im.rotation -= 2.0;
		break;
	case OF_KEY_RIGHT:
		im.rotation += 2.0;
		break;
	case OF_KEY_UP:
		im.pos += 2.0*heading();
		break;
	case OF_KEY_DOWN:
		im.pos -= 2.0*heading();
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
	glm::vec3 mouse = glm::vec3(x, y, 1);

	if (!im.bSelected) return;

	// calculate a difference vector between the current mouse and the last mouse
	//
	glm::vec3 delta = mouse - mouseLast;

	// add the difference to the mouse's current position
	//
	im.pos += delta;

	// store last mouse position for next time
	mouseLast = mouse;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	glm::vec3 mouse = glm::vec3(x, y, 1);

	if (im.inside(glm::inverse(im.getMatrix()) * glm::vec4(mouse, 1))) {
		im.bSelected = true;
		mouseLast = mouse;   // store initial position of mouse
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	im.bSelected = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
