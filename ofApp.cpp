#include "ofApp.h"
#include "Emitter.h"
#include "Sprite.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	score = 0;

	// Record when the game starts - game will run for 10 sec
	//
	gameStartTime = ofGetElapsedTimeMillis();
	
	// Image set up
	string soundFile1 = ("sounds/pew.mp3");
	if (!radio.load(soundFile1)) {
		cout << "FATAL ERROR: can't load sound file" << soundFile1 << endl;
		ofExit();
	}
	radio.setSpeed(2.5f);

	string soundFile2 = ("sounds/explosion.mp3");
	if (!explosion.load(soundFile2)) {
		cout << "FATAL ERROR: can't load sound file" << soundFile2 << endl;
		ofExit();
	}
	explosion.setSpeed(3.0f);


	string imageFile2 = "images/airplane2.png";
	if (!myShip.image.load(imageFile2)) {
		cout << "FATAL ERROR: can't load image file" << imageFile2 << endl;
		ofExit();
	}

	string imageFile3 = "images/background.png";
	if (!space.image.load(imageFile3)) {
		cout << "FATAL ERROR: can't load image file" << imageFile3 << endl;
		ofExit();
	}

	string imageFile4 = "images/airplane1.png";
	if (!enemyShip1.image.load(imageFile4)) {
		cout << "FATAL ERROR: can't load image file" << imageFile4 << endl;
		ofExit();
	}
	if (!enemyShip2.image.load(imageFile4)) {
		cout << "FATAL ERROR: can't load image file" << imageFile4 << endl;
		ofExit();
	}
	if (!enemyShip3.image.load(imageFile4)) {
		cout << "FATAL ERROR: can't load image file" << imageFile4 << endl;
		ofExit();
	}
	if (!enemyShip4.image.load(imageFile4)) {
		cout << "FATAL ERROR: can't load image file" << imageFile4 << endl;
		ofExit();
	}

	if (bullet1.load("images/bullet.png")) {
		imageLoaded1 = true;
	}
	else {
		ofLogFatalError("can't load image: images/bullet.png");
		ofExit();
	}

	if (bullet2.load("images/enemyBullet1.png")) {
		imageLoaded2 = true;
	}
	else {
		ofLogFatalError("can't load image: images/enemyBullet1.png");
		ofExit();
	}

	space.rotation = 0.0;
	space.scale = glm::vec3(2.0, 2.0, 1.0);
	space.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);

	myShip.hp = 5;
	myShip.rotation = 0.0;
	myShip.pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 1);

	enemyShip1.pos = glm::vec3(ofGetWindowWidth() / 8.0, ofGetWindowHeight() / 8.0, 1);
	enemyShip1.rotation = 180;

	enemyShip2.pos = glm::vec3(ofGetWindowWidth() / 8.0, ofGetWindowHeight() - ofGetWindowHeight() / 3.0, 1);
	enemyShip2.rotation = 45.0;

	enemyShip3.pos = glm::vec3(ofGetWindowWidth() - ofGetWindowWidth() / 7.0, ofGetWindowHeight() / 2.0, 1);
	enemyShip3.rotation = 75.0;

	enemyShip4.pos = glm::vec3(ofGetWindowWidth() - ofGetWindowWidth() / 4.0, ofGetWindowHeight() - ofGetWindowHeight() / 8.0, 1);
	enemyShip4.rotation = 110.0;


	enemyShip1.bot = true;
	enemyShip1.scaleBot = 200;
	enemyShip1.speed = 6;
	enemyShip1.cycles = 4;

	enemyShip2.bot = true;
	enemyShip2.scaleBot = 400;
	enemyShip2.speed = 5;
	enemyShip2.cycles = 10;

	enemyShip3.bot = true;
	enemyShip3.scaleBot = 500;
	enemyShip3.speed = 5;
	enemyShip3.cycles = 7;

	enemyShip4.bot = true;
	enemyShip4.scaleBot = 300;
	enemyShip4.speed = 5;
	enemyShip4.cycles = 20;

	// Create and setup emitters  (you can play with parameters
	// I have another example program that creates a GUI for these
	// so with that you can get an idea of velocity/rate effects.
	//
	gun = new Emitter( new SpriteSystem() );
	explode = new ParticleEmitter(new ParticleSystem());
	invader1 = new Emitter(new SpriteSystem());
	invader2 = new Emitter(new SpriteSystem());
	invader3 = new Emitter(new SpriteSystem());
	invader4 = new Emitter(new SpriteSystem());

	// Set up some reasonable parameters for the gun/missile launcher
	// Remember that "Y" decreases as we move toward teh top of the 
	// window, so we set a negative velocity of -1000;
	// We also don't want the missiles to live forever, so we set
	// a lifespan of 500 ms.
	//

	gui.setup();

	gun->setPosition(myShip.pos);
	gun->setRate(3);
	gun->setLifespan(5000);
	gun->setChildImage(bullet1);

	
	invader1->setLifespan(5000);
	invader1->setRate(2);
	invader1->setChildSize(20, 20);
	invader1->setChildImage(bullet2);
	
	invader2->setLifespan(5000);
	invader2->setRate(2);
	invader2->setChildSize(20, 20);
	invader2->setChildImage(bullet2);

	invader3->setLifespan(5000);
	invader3->setRate(2);
	invader3->setChildSize(20, 20);
	invader3->setChildImage(bullet2);

	invader4->setLifespan(5000);
	invader4->setRate(2);
	invader4->setChildSize(20, 20);
	invader4->setChildImage(bullet2);

	// start them up
	//


	myShip.thrust = 800;
	myShip.damping = .977;


	invader1->start();
	invader2->start();
	invader3->start();
	invader4->start();
	gun->start();

	radialForce = new ImpulseRadialForce(1000.0);
	


	explode->sys->addForce(radialForce);
	explode->setVelocity(ofVec3f(0, 0, 0));
	explode->setOneShot(true);
	explode->setEmitterType(RadialEmitter);
	explode->setGroupSize(100);

	
	bHide = false;
}

//--------------------------------------------------------------
//  ofApp::update() is called every frame by the OF mainloop. 
//  If the frame rate is 60 fps (frames per second) it gets called 
//  every 1/60 sec
//
void ofApp::update() {

	enemyShip1.update();
	enemyShip2.update();
	enemyShip3.update();
	enemyShip4.update();
	myShip.update();
	//  call the emitter's update function to create new sprites
	//  as needed
	//
	gun->setPosition(myShip.pos);
	gun->setVelocity(ofVec3f(1000* glm::sin(glm::radians(myShip.rotation)), (-1000 * glm::cos(glm::radians(myShip.rotation))), 0));

	invader1->setPosition(enemyShip1.pos);
	invader2->setPosition(enemyShip2.pos);
	invader3->setPosition(enemyShip3.pos);
	invader4->setPosition(enemyShip4.pos);

	gun->update();
	invader1->update();
	invader2->update();
	invader3->update();
	invader4->update();


	explode->setLifespan(3);
	explode->setRate(10);
	explode->setParticleRadius(1.5);
	explode->update();
	
	checkCollisions();

	
	invader1->setVelocity(ofVec3f(1000, 1000, 0));
	invader1->setVelocity(ofVec3f(invader1->velocity.x*glm::sin(glm::radians(enemyShip1.rotation)), invader1->velocity.y*-glm::cos(glm::radians(enemyShip1.rotation)), 0));

	invader2->setVelocity(ofVec3f(1000, 1000, 0));
	invader2->setVelocity(ofVec3f(invader2->velocity.x*glm::sin(glm::radians(enemyShip2.rotation)), invader2->velocity.y*-glm::cos(glm::radians(enemyShip2.rotation)), 0));

	invader3->setVelocity(ofVec3f(1000, 1000, 0));
	invader3->setVelocity(ofVec3f(invader3->velocity.x*glm::sin(glm::radians(enemyShip3.rotation)), invader3->velocity.y*-glm::cos(glm::radians(enemyShip3.rotation)), 0));

	invader4->setVelocity(ofVec3f(1000, 1000, 0));
	invader4->setVelocity(ofVec3f(invader4->velocity.x*glm::sin(glm::radians(enemyShip4.rotation)), invader4->velocity.y*-glm::cos(glm::radians(enemyShip4.rotation)), 0));
	

	float t = ofGetElapsedTimeMillis();
	if ((t - gameStartTime > (200 * 1000))) {
		gameOver = true;
		gun->stop();
		invader1->stop();
		invader2->stop();
		invader3->stop();
		invader4->stop();
	}
	if (!gameOver)
		if (!radio.isPlaying()) 
			radio.play();

}


//--------------------------------------------------------------
//  ofApp::draw() this is where everything gets drawn
//  you should only put draw code in this method. 
//
//
void ofApp::draw(){

	// if game is over, just draw a label in middle of screen
	//
	if (gameOver) {
		if (level == 0)
			ofDrawBitmapString("GAME OVER", ofPoint(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2));
		else {
			ofDrawBitmapString("Level: " + ofToString(level), ofPoint(ofGetWindowWidth() / 2 - 60, ofGetWindowHeight() / 2) + 60);
			ofDrawBitmapString("Score: " + ofToString(score), ofPoint(ofGetWindowWidth() / 2 - 30, ofGetWindowHeight() / 2) + 30);
		}
	}
	else {
		space.draw();
		if(myShip.toDraw())
			myShip.draw();
		else {
			gameOver = true;
			level = 0;
			score = 0;
		}
		if (enemyShip1.toDraw())
			enemyShip1.draw();
		if (enemyShip2.toDraw())
			enemyShip2.draw();
		if (enemyShip3.toDraw())
			enemyShip3.draw();
		if (enemyShip4.toDraw())
			enemyShip4.draw();
		if (!(enemyShip1.toDraw() || enemyShip2.toDraw() || enemyShip3.toDraw() || enemyShip4.toDraw())) {
			gameOver = true;
			level++;
		}
		explode->draw();
		gun->draw();
		invader1->draw();
		invader2->draw();
		invader3->draw();
		invader4->draw();
		if (!bHide) {
			gui.draw();
		}
	}

	// draw current score
	//
	string scoreText;
	scoreText += "Score: " + std::to_string(score);
	ofDrawBitmapString(scoreText, ofPoint(10, 20));
}



//--------------------------------------------------------------
//
void ofApp::keyPressed(int key) {
	switch (key) {
	case OF_KEY_LEFT:   // turn left
		myShip.rotForces = -myShip.thrust;
		break;
	case OF_KEY_RIGHT:  // turn right
		myShip.rotForces = myShip.thrust;
		break;
	case OF_KEY_UP:     // go forward
		myShip.forces.set(myShip.thrust*heading());
		break;
	case OF_KEY_DOWN:   // go backward
		myShip.forces.set(-myShip.thrust*heading());
		break;
	case ' ':
		reset();
		gameOver = false;
		break;
	default:
		break;
	}

}
void ofApp::reset() {
	myShip.hp = 5;
	gun->rate = 3;
	enemyShip1.hp = 1 + level;
	invader1->rate = 1 + level;
	enemyShip2.hp = 1 + level;
	invader2->rate = 1 + level;
	enemyShip3.hp = 1 + level;
	invader3->rate = 1 + level;
	enemyShip4.hp = 1 + level;
	invader4->rate = 1 + level;
}
//  This is a simple O(M x N) collision check
//  For each missle check to see which invaders you hit and remove them
//
void ofApp::checkCollisions() {
	int tempScore = 0;
	// find the distance at which the two sprites (missles and invaders) will collide
	// detect a collision when we are within that distance.
	//
	float collisionDist = gun->childHeight / 2 + invader1->childHeight / 2;
	//float collisionDistShip = myShip.image.getHeight/2 + invader1->childHeight / 2;

	// Loop through all the missiles, then remove any invaders that are within
	// "collisionDist" of the missiles.  the removeNear() function returns the
	// number of missiles removed.
	//
	for (int i = 0; i < gun->sys->sprites.size(); i++) {
		if (enemyShip1.inside(gun->sys->sprites[i].trans.x, gun->sys->sprites[i].trans.y)) {
			enemyShip1.hp -= 1;
			gun->sys->remove(i);
			if (enemyShip1.hp == 0) {
				invader1->setRate(0);
				score++;
				if (!explosion.isPlaying())
					explosion.play();
				spawnExplosion(enemyShip1.pos);
			}
		}
		else if (enemyShip2.inside(gun->sys->sprites[i].trans.x, gun->sys->sprites[i].trans.y)) {
			enemyShip2.hp -= 1;
			gun->sys->remove(i);
			if (enemyShip2.hp == 0) {
				invader2->setRate(0);
				score++;
				if (!explosion.isPlaying())
					explosion.play();
				spawnExplosion(enemyShip2.pos);
			}
		}
		else if (enemyShip3.inside(gun->sys->sprites[i].trans.x, gun->sys->sprites[i].trans.y)) {
			enemyShip3.hp -= 1;
			gun->sys->remove(i);
			if (enemyShip3.hp == 0) {
				invader3->setRate(0);
				score++;
				if (!explosion.isPlaying())
					explosion.play();
				spawnExplosion(enemyShip3.pos);
			}
		}
		else if (enemyShip4.inside(gun->sys->sprites[i].trans.x, gun->sys->sprites[i].trans.y)) {
			enemyShip4.hp -= 1;
			gun->sys->remove(i);
			if (enemyShip4.hp == 0) {
				invader4->setRate(0);
				score++;
				if (!explosion.isPlaying())
					explosion.play();
				spawnExplosion(enemyShip4.pos);
			}
		}
	}
	for (int i = 0; i < invader1->sys->sprites.size(); i++) {
		if (myShip.inside(invader1->sys->sprites[i].trans.x, invader1->sys->sprites[i].trans.y)) {
			myShip.hp -= 1;
			invader1->sys->remove(i);
			if (myShip.hp == 0) {
				gun->setRate(0);
				if (!explosion.isPlaying())
					explosion.play();
			}
		}
	}
	for (int i = 0; i < invader2->sys->sprites.size(); i++) {
		if (myShip.inside(invader2->sys->sprites[i].trans.x, invader2->sys->sprites[i].trans.y)) {
			myShip.hp -= 1;
			invader2->sys->remove(i);
			if (myShip.hp == 0) {
				gun->setRate(0);
				if (!explosion.isPlaying())
					explosion.play();
			}
		}
	}
	for (int i = 0; i < invader3->sys->sprites.size(); i++) {
		if (myShip.inside(invader3->sys->sprites[i].trans.x, invader3->sys->sprites[i].trans.y)) {
			myShip.hp -= 1;
			invader3->sys->remove(i);
			if (myShip.hp == 0) {
				gun->setRate(0);
				if (!explosion.isPlaying())
					explosion.play();
			}
		}
	}
	for (int i = 0; i < invader4->sys->sprites.size(); i++) {
		if (myShip.inside(invader4->sys->sprites[i].trans.x, invader4->sys->sprites[i].trans.y)) {
			myShip.hp -= 1;
			invader4->sys->remove(i);
			if (myShip.hp == 0) {
				gun->setRate(0);
				if (!explosion.isPlaying())
					explosion.play();
			}
		}
	}
}

void ofApp::spawnExplosion(ofVec3f vec) {
	explode->setPosition(vec);
	explode->sys->reset();
	explode->start();
}

//  support dragging of gun with mouse
//
void ofApp::mouseDragged(int x, int y, int button){
	glm::vec3 mouse = glm::vec3(x, y, 1);
	if (!myShip.bSelected) return;
	glm::vec3 delta = mouse - mouseLast;
	myShip.pos += delta;
	mouseLast = mouse;
}


//--------------------------------------------------------------
// Start game if not running; otherwise track mouse last coord
// 
void ofApp::mousePressed(int x, int y, int button){
	if (!gun->started) {
		gameStartTime = ofGetElapsedTimeMillis();
		gameOver = false;
		gun->start();
		invader1->start();
		invader2->start();
		invader3->start();
		invader4->start();
		score = 0;
	}
	glm::vec3 mouse = glm::vec3(x, y, 1);
	if (myShip.inside(x, y)) {
		myShip.bSelected = true;
		mouseLast = mouse;   // store initial position of mouse
	}
	mouseLast = ofPoint(x, y);
}

//--------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	myShip.bSelected = false;
}
