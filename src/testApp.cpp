#include "testApp.h"

/*
	rotateToNormal will rotate everything using ofRotate. the rotation amount
	and axis are generated using an ofQuaternion. the trick is to use ofQuaternion
	to determine the rotation that is required from a standard axis (0,0,1) to the
	desired normal vector, then apply that rotation. 
*/
//--------------------------------------------------------------
void rotateToNormal(ofVec3f normal) {
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
}

//--------------------------------------------------------------
void testApp::setup(){


	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);

	_cTargetPos = ofVec3f(0.0, 0.0, 0.0);

	_dampen     = 0.4;

}

//--------------------------------------------------------------
void testApp::update(){

	_pTargetPos = _cTargetPos;
	
	// generate a noisy 3d position over time 
	float t = (2 + ofGetElapsedTimef()) * .1;
	_cTargetPos.x = ofSignedNoise(t, 0, 0);
	_cTargetPos.y = ofSignedNoise(0, t, 0);
	_cTargetPos.z = ofSignedNoise(0, 0, t);
	_cTargetPos *= 400; // scale from -1,+1 range to -400,+400
	


}

//--------------------------------------------------------------
void testApp::draw(){
	ofColor cyan = ofColor::fromHex(0x00abec);
	ofColor magenta = ofColor::fromHex(0xec008c);
	ofColor yellow = ofColor::fromHex(0xffee00);
	
	ofNoFill();
	
	_ccam.begin();

	/////// カメラ関連の設定 ///////

	// カメラの基本位置と注視点を決定
	_ccam.setCamBasePos(_cTargetPos);
	_ccam.setTargetPos(_cTargetPos);

	// マウス操作による回転の座標変換をカメラに加える
	_ccam.execRotate();

	// 座標変換されたカメラの位置を、オブジェクトから一定の距離を保てる位置に変更する
	_ccam.keepADistance();



	// 最終的なカメラの位置と注視点の座標を適用する
	_ccam.setPosition();
	_ccam.lookAt();


	/////// オブジェクトの設定・描画 ///////

	// マウス操作による回転の座標変換を適用
	float angle;
	ofVec3f axis;
	_ccam.getRotation(angle, axis);

	ofRotate(angle, axis.x, axis.y, axis.z);

	ofPushMatrix();
	{

		ofSetColor(0);
		ofDrawGrid(500, 10, false, false, true, false);
	
		ofPushMatrix();
		{

			ofTranslate(_cTargetPos.x, _cTargetPos.y, _cTargetPos.z);
			
			rotateToNormal(_cTargetPos - _pTargetPos);
			ofSetLineWidth(2);
			ofSetColor(255);
			ofDrawBox(32);
			ofDrawAxis(32);

		}
		ofPopMatrix();
	
	}
	ofPopMatrix();


	_ccam.end();

	
	// 更新された視点座標系の座標軸を計算する
	_ccam.calcCamAxis();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	// ↑キー
	if(key == 357){
		_ccam.updateDistance(-20.0);
	}	

	// ↓キー
	if(key == 359){
		_ccam.updateDistance(20.0);
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	ofVec2f mouse(x,y);  

	ofVec3f xAxis = _ccam.getCamXAxis();
	ofVec3f yAxis = _ccam.getCamYAxis();

	ofQuaternion yRot((x-_lastMouse.x)*_dampen, yAxis);  
    ofQuaternion xRot((y-_lastMouse.y)*_dampen, xAxis);


	_ccam.setRotation(yRot*xRot);
	_lastMouse = mouse;

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	_lastMouse = ofVec2f(x,y);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
