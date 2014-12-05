#include "ofMain.h"

class CustomCam : public ofCamera{


public:


	CustomCam(float distance = 100.0);
	~CustomCam();


	// �J�����̊�{�ʒu������
	void setCamBasePos(const ofVec3f camBasePos);
	
	// �J�����̒����_������
	void setTargetPos(const ofVec3f targetPos);
	
	// �J�����̈ʒu���A�����_������̋�����ۂĂ�ʒu�ɕύX����
	void keepADistance();


	// �}�E�X����ɂ���]�̍��W�ϊ����J�����֘A�̐ݒ�
	// (�J�����ʒu�A�����_�A�����)�ɓK�p����
	void execRotate();


	// ���_���W�n�̍��W�����v�Z
	void calcCamAxis();


	// �ŏI�I�ȃJ�����̈ʒu�y�ђ����_�̈ʒu�����[���h���W�n�ɓK�p
	// �� ofCamera::setPostion�y��ofCamera::lookAt�̃��b�p�[
	void setPosition();
	void lookAt();


	// �J����-�����_�Ԃ̋�����ύX����
	void updateDistance(const float moveDistance);


	// �}�E�X����ɂ���]���擾����
	void getRotation(float& angle, ofVec3f& axis);

	// �}�E�X����ɂ���]��ݒ肷�� 
	void setRotation(const ofQuaternion& rotation);


	// ���_���W�n�̍��W�����擾����
	ofVec3f getCamXAxis();
	ofVec3f getCamYAxis();
	ofVec3f getCamZAxis();



private:

	ofVec3f _pos;                   // �J�����ʒu
	ofVec3f _targetPos;             // �����_
	ofVec3f _upVec;                 // �J�����̏�����x�N�g��
	ofVec3f _defaultVecFromTarget;  // �����_���痣���ׂ�����(�����l)
	ofVec3f _vecFromTarget;         // �����_���痣���ׂ�����
	float   _distance;              // �J�����ƒ����_�̋���



	ofQuaternion _rotation;         // �J�����̉�]�N�H�[�^�j�I��
	ofVec3f _xAxis;                 // ���_���W�n��X��
	ofVec3f _yAxis;                 // ���_���p�n��Y��
	ofVec3f _zAxis;                 // ���_���W�n��Z��
	


};