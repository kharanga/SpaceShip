#include "ofMain.h"

class Shape {
public:
	Shape() {}
	virtual void draw() {}
	virtual bool inside() { return false; }

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

class ImageShape : public Shape {
public:
	int hp = 1;

	ImageShape(ofImage image) {
		this->image = image;
	}
	ImageShape() {}
	bool inside(int x, int y);

	bool toDraw();

	void update();

	void draw();

	void integrate();

	ofImage image;

	ofVec3f velocity;
	ofVec3f acceleration = ofVec3f(0, 0, 0);
	ofVec3f forces = ofVec3f(0, 0, 0);
	int thrust;
	float	damping = .99;
	float   mass = 1;
	float rotVel;
	float rotAcc = 0;
	float rotForces = 0;
	float scaleBot;
	float cycles;
	float speed;
	glm::vec3 heading;
	glm::vec3 curveEval(float x, float scale, float cycles);
	bool bot = false;
};