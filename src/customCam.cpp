#include "customCam.h"


CustomCam::CustomCam(float distance){

	// カメラと注視点の距離及びベクトルの初期化 
	_distance             = distance;
	_defaultVecFromTarget = ofVec3f(0.5, 0.5, 0.5);

	_pos = ofVec3f(0.0, 0.0, 0.0);

}


CustomCam::~CustomCam(){
}


/**
 * カメラの基本位置を決定
 */
void CustomCam::setCamBasePos(const ofVec3f camBasePos){

	_pos = camBasePos;
}


/**
 * カメラの注視点を決定
 */
void CustomCam::setTargetPos(const ofVec3f targetPos){

	_targetPos = targetPos;

}

/**
 * カメラの位置を、注視点から一定の距離を保てる位置に変更する
 */
void CustomCam::keepADistance(){

	_vecFromTarget  = _defaultVecFromTarget.getScaled(_distance);
	_pos           += _vecFromTarget;

}


/**
 * マウス操作による回転の座標変換をカメラ設定(カメラ位置、注視点、上方向)に適用する
 */
void CustomCam::execRotate(){

	float   angle;
	ofVec3f axis;


	_rotation.getRotate(angle, axis);
	
	_pos.rotate(angle, axis);

	// カメラの上方向ベクトルは、ワールド座標系のY軸に対しての回転となる
	_upVec = ofVec3f(0.0, 1.0, 0.0);
	_upVec.rotate(angle, axis);

	_targetPos.rotate(angle, axis);


}

/**
 * 視点座標系の座標軸を計算する
 * ※ マウス操作による回転を計算する際に使用
 */
void CustomCam::calcCamAxis(){

	_zAxis = _pos - _targetPos;
	_zAxis.normalize();

	_xAxis = _upVec.getCrossed(_zAxis);
	_xAxis.normalize();
	
	_yAxis = _zAxis.getCrossed(_xAxis);
	_yAxis.normalize();

}


/**
 * 最終的なカメラ位置をワールド座標系に適用
 * ※ ofCamera::setPostion()のラッパー
 */
void CustomCam::setPosition(){

	ofCamera::setPosition(_pos);

}


/**
 * 最終的な注視点をワールド座標系に適用
 * ※ ofCamera::lookAt()のラッパー
 */
void CustomCam::lookAt(){

	ofCamera::lookAt(_targetPos, _upVec);
}


/**
 * カメラ-注視点間の距離を変更する
 */
void CustomCam::updateDistance(const float moveDistance){

	_distance += moveDistance;

}


/**
 * マウス操作による回転を取得する
 */
void CustomCam::getRotation(float& angle, ofVec3f& axis){

	_rotation.getRotate(angle, axis);

}

/**
 * マウス操作による回転を設定する
 */
void CustomCam::setRotation(const ofQuaternion& rotation){

	_rotation *= rotation;

}


/**
 * 視点座標系のX軸を取得する
 */
ofVec3f CustomCam::getCamXAxis(){

	return _xAxis; 

}

/**
 * 視点座標系のY軸を取得する
 */
ofVec3f CustomCam::getCamYAxis(){

	return _yAxis;

}

/**
 * 視点座標系のZ軸を取得する
 */
ofVec3f CustomCam::getCamZAxis(){

	return _zAxis;

}