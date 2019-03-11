#include "Headers.h"

hitbox::hitbox()
{
	clientX = 0.0f;
	clientY = 0.0f;
	imageX = 0.0f;
	imageY = 0.0f;
	w = 0.0f;
	h = 0.0f;
	startOffsetX = 0.0f;
	startOffsetY = 0.0f;
	isSelected = false;
}

hitbox::hitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID)
{
	clientX = _cX;
	clientY = _cY;
	imageX = _iX;
	imageY = _iY;
	w = _w;
	h = _h;
	startOffsetX = _oX;
	startOffsetY = _oY;
	ID = _ID;
	isSelected = false;
}

wxRect hitbox::getBox(float _currentOffsetX, float _currentOffsetY)
{
	return wxRect(clientX + (_currentOffsetX - startOffsetX), clientY + (_currentOffsetY - startOffsetY), w, h);
}

wxString hitbox::getID()
{
	return ID;
}

bool hitbox::getSelected()
{
	return isSelected;
}

void hitbox::setSelected(bool _selected)
{
	isSelected = _selected;
}