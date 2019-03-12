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

nlohmann::json hitbox::getJSONInfo(Image* _currentImage, int _PPU)
{
	wxRealPoint convertedPosition = convertPosition(_currentImage, _PPU);
	wxRealPoint convertedSize = convertSize(_PPU);
	nlohmann::json rtn;
	rtn["x"] = convertedPosition.x;
	rtn["y"] = convertedPosition.y;
	rtn["w"] = convertedSize.x;
	rtn["h"] = convertedSize.y;
	return rtn;
}

wxRealPoint hitbox::convertPosition(Image* _currentImage, int _PPU)
{
	float x = ((imageX - (_currentImage->image.GetWidth() / 2)) + (w / 2)) / _PPU;
	float y = ((((imageY - (_currentImage->image.GetHeight() / 2)) + (h / 2)) / _PPU) * -1);
	return wxRealPoint(x, y);
}

wxRealPoint hitbox::convertSize(int _PPU)
{
	float width = (w / _PPU);
	float height = (h / _PPU);
	return wxRealPoint(width, height);
}