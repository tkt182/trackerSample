#include "ofMain.h"

class CustomCam : public ofCamera{


public:


	CustomCam(float distance = 100.0);
	~CustomCam();


	// カメラの基本位置を決定
	void setCamBasePos(const ofVec3f camBasePos);
	
	// カメラの注視点を決定
	void setTargetPos(const ofVec3f targetPos);
	
	// カメラの位置を、注視点から一定の距離を保てる位置に変更する
	void keepADistance();


	// マウス操作による回転の座標変換をカメラ関連の設定
	// (カメラ位置、注視点、上方向)に適用する
	void execRotate();


	// 視点座標系の座標軸を計算
	void calcCamAxis();


	// 最終的なカメラの位置及び注視点の位置をワールド座標系に適用
	// ※ ofCamera::setPostion及びofCamera::lookAtのラッパー
	void setPosition();
	void lookAt();


	// カメラ-注視点間の距離を変更する
	void updateDistance(const float moveDistance);


	// マウス操作による回転を取得する
	void getRotation(float& angle, ofVec3f& axis);

	// マウス操作による回転を設定する 
	void setRotation(const ofQuaternion& rotation);


	// 視点座標系の座標軸を取得する
	ofVec3f getCamXAxis();
	ofVec3f getCamYAxis();
	ofVec3f getCamZAxis();



private:

	ofVec3f _pos;                   // カメラ位置
	ofVec3f _targetPos;             // 注視点
	ofVec3f _upVec;                 // カメラの上方向ベクトル
	ofVec3f _defaultVecFromTarget;  // 注視点から離れるべき方向(初期値)
	ofVec3f _vecFromTarget;         // 注視点から離れるべき方向
	float   _distance;              // カメラと注視点の距離



	ofQuaternion _rotation;         // カメラの回転クォータニオン
	ofVec3f _xAxis;                 // 視点座標系のX軸
	ofVec3f _yAxis;                 // 視点座用系のY軸
	ofVec3f _zAxis;                 // 視点座標系のZ軸
	


};