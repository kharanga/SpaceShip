#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "Shape.h"
#include "ParticleEmitter.h"
#include "TransformObject.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;



class Emitter;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void checkCollisions();
		void reset();
		void spawnExplosion(ofVec3f);

		void keyPressed(int key);
		void keyReleased(int key) {}
		void mouseMoved(int x, int y) {}
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y) {}
		void mouseExited(int x, int y) {}
		void windowResized(int w, int h) {}
		void dragEvent(ofDragInfo dragInfo) {}
		void gotMessage(ofMessage msg) {}
		
		Emitter *invader1, *invader2, *invader3, *invader4, *gun;
		int score;

		float gameStartTime, level = 0;
		bool gameOver = false;
		ofVec3f mouseLast;
		ImageShape waitingScreen;
		ImageShape myShip;
		ImageShape space;
		ImageShape enemyShip1, enemyShip2, enemyShip3, enemyShip4;
		ParticleEmitter *explode;
		ImpulseRadialForce *radialForce;
		ofImage bullet1;
		ofImage bullet2;
		bool imageLoaded1;
		bool imageLoaded2;
		ofSoundPlayer radio;
		ofSoundPlayer explosion;

		glm::vec3 heading() {
			glm::vec3 initialHeading = glm::vec3(0, -1, 0);    // heading at start
			glm::mat4 Mrot = glm::rotate(glm::mat4(1.0), glm::radians(myShip.rotation), glm::vec3(0, 0, 1));
			glm::vec3 h = Mrot * glm::vec4(initialHeading, 1);
			return glm::normalize(h);
		}

		bool bHide;
		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxFloatSlider hp;

		ofxFloatSlider rateEnemy;
		ofxFloatSlider lifeEnemy;
		ofxVec3Slider velocityEnemy;
		ofxFloatSlider hpEnemy;

		ofxPanel gui;
};
