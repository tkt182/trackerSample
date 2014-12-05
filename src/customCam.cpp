#include "customCam.h"


CustomCam::CustomCam(float distance){

	// �J�����ƒ����_�̋����y�уx�N�g���̏����� 
	_distance             = distance;
	_defaultVecFromTarget = ofVec3f(0.5, 0.5, 0.5);

	_pos = ofVec3f(0.0, 0.0, 0.0);

}


CustomCam::~CustomCam(){
}


/**
 * �J�����̊�{�ʒu������
 */
void CustomCam::setCamBasePos(const ofVec3f camBasePos){

	_pos = camBasePos;
}


/**
 * �J�����̒����_������
 */
void CustomCam::setTargetPos(const ofVec3f targetPos){

	_targetPos = targetPos;

}

/**
 * �J�����̈ʒu���A�����_������̋�����ۂĂ�ʒu�ɕύX����
 */
void CustomCam::keepADistance(){

	_vecFromTarget  = _defaultVecFromTarget.getScaled(_distance);
	_pos           += _vecFromTarget;

}


/**
 * �}�E�X����ɂ���]�̍��W�ϊ����J�����ݒ�(�J�����ʒu�A�����_�A�����)�ɓK�p����
 */
void CustomCam::execRotate(){

	float   angle;
	ofVec3f axis;


	_rotation.getRotate(angle, axis);
	
	_pos.rotate(angle, axis);

	// �J�����̏�����x�N�g���́A���[���h���W�n��Y���ɑ΂��Ẳ�]�ƂȂ�
	_upVec = ofVec3f(0.0, 1.0, 0.0);
	_upVec.rotate(angle, axis);

	_targetPos.rotate(angle, axis);


}

/**
 * ���_���W�n�̍��W�����v�Z����
 * �� �}�E�X����ɂ���]���v�Z����ۂɎg�p
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
 * �ŏI�I�ȃJ�����ʒu�����[���h���W�n�ɓK�p
 * �� ofCamera::setPostion()�̃��b�p�[
 */
void CustomCam::setPosition(){

	ofCamera::setPosition(_pos);

}


/**
 * �ŏI�I�Ȓ����_�����[���h���W�n�ɓK�p
 * �� ofCamera::lookAt()�̃��b�p�[
 */
void CustomCam::lookAt(){

	ofCamera::lookAt(_targetPos, _upVec);
}


/**
 * �J����-�����_�Ԃ̋�����ύX����
 */
void CustomCam::updateDistance(const float moveDistance){

	_distance += moveDistance;

}


/**
 * �}�E�X����ɂ���]���擾����
 */
void CustomCam::getRotation(float& angle, ofVec3f& axis){

	_rotation.getRotate(angle, axis);

}

/**
 * �}�E�X����ɂ���]��ݒ肷��
 */
void CustomCam::setRotation(const ofQuaternion& rotation){

	_rotation *= rotation;

}


/**
 * ���_���W�n��X�����擾����
 */
ofVec3f CustomCam::getCamXAxis(){

	return _xAxis; 

}

/**
 * ���_���W�n��Y�����擾����
 */
ofVec3f CustomCam::getCamYAxis(){

	return _yAxis;

}

/**
 * ���_���W�n��Z�����擾����
 */
ofVec3f CustomCam::getCamZAxis(){

	return _zAxis;

}