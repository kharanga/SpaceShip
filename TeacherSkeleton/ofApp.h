#pragma once

#include "ofMain.h"


//  Shape base class
//
class Shape {
public:
	Shape() {}
	virtual void draw() {}
	virtual bool inside() { return false;  }

	glm::vec3 pos;
	float rotation = 0.0;
	glm::vec3 scale = glm::vec3(1.0, 1.0, 1.0);

	// get transformation matrix for object (based on it's current pos, rotation and scale channels)
	//
	glm::mat4 getMatrix() {
		glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);

		return (trans * rot * scale);
	}

	vector<glm::vec3> verts;
	bool bSelected = false;
};

class ImageShape: public Shape {
public:
	ImageShape(ofImage image) {
		this->image = image;
	}
	ImageShape() {}
	bool inside(glm::vec3 p) {
		return false;
	}

	void draw();

	ofImage image;
};

//  Example - we could define any type of shape we want
//
class LineDrawingShape : public Shape {
public:
	void draw() {};
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		glm::vec3 heading() {
			glm::vec3 initialHeading = glm::vec3(0, -1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(im.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}
		
		// initialize triangle - note: I changed vertices to match what I had in demo video
		//
		ImageShape im;
		glm::vec3 mouseLast;
};
