#ifndef HITBOX_H_
#define HITBOX_H_

#include "Headers.h"

class hitbox
{
public:
	hitbox();
	hitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	wxRect getBox(float _currentOffsetX, float _currentOffsetY);
	wxString getID();
	bool getSelected();
	void setSelected(bool _selected);

private:
	float clientX, clientY, imageX, imageY, w, h, startOffsetX, startOffsetY;
	wxString ID;
	bool isSelected;
};



#endif // !HITBOX_H_
