#include "Shape.h"
void ImageShape::draw() {
	if (toDraw()) {
		ofPushMatrix();
		ofMultMatrix(getMatrix());  // get the current transform for the object
		image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
		ofPopMatrix();
	}
}
bool ImageShape::inside(int x, int y) {
	if (x >= pos.x - image.getWidth() / 2.0 && x <= pos.x + image.getWidth() / 2.0) {
		if (y >= pos.y - image.getHeight() / 2.0 && y <= pos.y + image.getHeight() / 2.0) {
			return true;
		}
	}
	return false;
}

bool ImageShape::toDraw() {
	if (hp > 0) {
		return true;
	}
	return false;
}

void ImageShape::update() {
	if (bot) {

		// speed in UI is in pixels/sec; covert to pixels/frame
		//

		// wrap position of sprite if we reach the end
		//
		if (pos.x > (ofGetWidth() - 1))
			pos = curveEval(0, scaleBot, cycles);

		// get new heading (estimate); based on looking ahead along
		// the curve by some distance; we will use the speed.
		//
		heading = glm::normalize(curveEval(pos.x + speed, scaleBot , cycles) - pos);

		// adjust position while trying to keep speed constant 
		//   there are different possible solutions. One "heuristic" would be
		//   to travel along the estimated heading vector by distance t, which 
		//   would be the amount of distance traveled in one frame (based 
		//   on what the speed is)
		//   once we have have this new point, we can evaluate 
		//   the actual point on the curve using this and 
		//   recompute the actual heading once we have the point on curve;
		//
		glm::vec3 p = pos + (heading * speed);
		glm::vec3 newPos = curveEval(p.x, scaleBot, cycles);
		heading = glm::normalize(newPos - pos);   // save heading because we will draw it later
		pos = newPos;


		rotation = -glm::degrees(glm::orientedAngle(heading, glm::vec3(0, -1, 0), glm::vec3(0, 0, 1)));
	}
	else {
		if (pos.x - image.getWidth() / 2.0 < 0) {
			pos = glm::vec3(image.getWidth() / 2.0, pos.y, 1);
		}
		if (pos.x + image.getWidth() / 2.0 > 1280) {
			pos = glm::vec3(1280 - image.getWidth() / 2.0, pos.y, 1);
		}
		if (pos.y - image.getHeight() / 2.0 < 0) {
			pos = glm::vec3(pos.x, image.getHeight() / 2.0, 1);
		}
		if (pos.y + image.getHeight() / 2.0 > 1024) {
			pos = glm::vec3(pos.x, 1024 - image.getHeight() / 2.0, 1);
		}
		integrate();
	}
	
}



void ImageShape::integrate() {


	pos += (velocity * 1.0 / ofGetFrameRate());


	ofVec3f accel = acceleration;

	accel += (forces * (1.0 / mass));
	velocity += (accel * 1.0 / ofGetFrameRate());

	velocity *= damping;

	forces.set(0, 0, 0);
	//------------------------------------------------------------
	rotation += (rotVel * 1.0 / 60);
	float rotAccel = rotAcc;

	rotAccel += (rotForces * (1.0 / mass));
	rotVel += (rotAccel * 1.0 / 60);

	rotVel *= damping;

	rotForces = 0;
}

glm::vec3 ImageShape::curveEval(float x, float scale, float cycles)
{
	// x is in screen coordinates and his in [0, WindowWidth]
	float u = (cycles * x * PI) / ofGetWidth();
	return (glm::vec3(x, -scale * sin(u) + (ofGetHeight() / 2), 0));
}

