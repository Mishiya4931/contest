#include "Camera.h" 
#include "Input.h" 
class CameraDebug : public Camera 
{
public:
	CameraDebug();
	~CameraDebug();
	void Update()final;
private:
	float m_radXZ;
	float m_radY;
	float m_radius; //  
};