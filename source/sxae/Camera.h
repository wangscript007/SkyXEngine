#ifndef CAMERA_H
#define CAMERA_H

#include <common/SXMath.h>

class Camera
{
	SMMATRIX m_mResult;

	SMVECTOR m_vEye;
	SMVECTOR m_vAt;
	SMVECTOR m_vUp;

	float3_t m_vCamRef;
	float3_t m_vPosition;

	float fYaw;
	float fPitch;

	bool bMove[4];
public:
	enum CAMERA_MOVE
	{
		CAMERA_MOVE_FORWARD,
		CAMERA_MOVE_BACKWARD,
		CAMERA_MOVE_LEFT,
		CAMERA_MOVE_RIGHT
	};
	Camera();

	SMMATRIX GetMatrix();

	void RotateX(float fDelta);
	void RotateY(float fDelta);

	void Rotate(float fDeltaX, float fDeltaY);

	void UpdateMatrix();

	void Forward(float fDelta);
	void Strafe(float fDelta);

	void Move(CAMERA_MOVE m, bool state);
	void Advance();

	float3_t GetPos();

	float3_t GetViewDir();
};

#endif