#pragma once
#include "RayCaster.h"
class RayCasterFixed : public RayCaster
{
protected:
	uint16_t _px;
	uint16_t _py;
	int16_t	 _pa;
	uint8_t	 _qtr;
	uint8_t	 _qa;

	void Distance(uint16_t _sx, uint16_t _sy, uint16_t ra, int16_t* dx, int16_t* dy, uint8_t* textureNo, uint8_t* tX);
	bool IsWall(uint8_t bx, uint8_t by, uint8_t sx, uint8_t sy);

	int16_t	 MulTan(uint8_t v, uint8_t i, uint8_t qtr, uint8_t a, const uint16_t* fun);
	int16_t	 AbsTan(uint8_t qtr, uint8_t a, const uint16_t* fun);
	uint16_t Mul(uint8_t v, uint16_t f);
	int16_t	 MulS(uint8_t v, int16_t f);
	void	 Height(uint16_t d, uint8_t* h, uint16_t* ts);

public:
	void Start(uint16_t playerX, uint16_t playerY, int16_t playerA);

	void Trace(uint16_t	 screenX,
			   uint8_t*	 screenY,
			   uint8_t*	 textureNo,
			   uint8_t*	 textureX,
			   uint16_t* textureY,
			   uint16_t* textureStep);

	RayCasterFixed();
	~RayCasterFixed();
};
