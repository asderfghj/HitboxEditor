#ifndef HITBOXDATA_H_
#define HITBOXDATA_H_
#include "Headers.h"

class HitboxData
{
	std::vector<std::shared_ptr<hitbox>> hitboxes;
	std::vector<std::shared_ptr<hitbox>> hurtboxes;
	std::shared_ptr<Image> attachedImage;
	int hitboxCounter, hurtboxCounter;

public:
	HitboxData(std::shared_ptr<Image> _img);
	wxString getImageName();
	Image* getImage();
	void addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	void removeHitbox(wxString _ID);
	std::shared_ptr<hitbox> getHitbox(int _index);
	std::shared_ptr<hitbox> getHitbox(wxString _ID);
	int getHitboxCount();
	int getHitboxCounter();
	void setHitboxCounter(int _counter);
	void addHurtbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	void removeHurtbox(wxString _ID);
	std::shared_ptr<hitbox> getHurtbox(int _index);
	std::shared_ptr<hitbox> getHurtbox(wxString _ID);
	int getHurtboxCount();
	int getHurtboxCounter();
	void setHurtboxCounter(int _counter);
	void Deselect();
};



#endif // !HITBOXDATA
