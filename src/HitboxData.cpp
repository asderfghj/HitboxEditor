#include "HitboxData.h"
#include "Image.h"
#include "Hitbox.h"

HitboxData::HitboxData(std::shared_ptr<Image> _img)
{
	attachedImage = _img;
	hitboxCounter = 0;
	hurtboxCounter = 0;
}

wxString HitboxData::getImageName()
{
	return attachedImage->name;
}

Image* HitboxData::getImage()
{
	return attachedImage.get();
}

void HitboxData::addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID)
{
	hitboxes.push_back(std::make_shared<hitbox>(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, _ID));
	hitboxCounter++;
}

void HitboxData::removeHitbox(wxString _ID)
{
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes[i]->getID() == _ID)
		{
			hitboxes.erase(hitboxes.begin() + i);
		}
	}
}

std::shared_ptr<hitbox> HitboxData::getHitbox(int _index)
{
	return hitboxes.at(_index);
}

std::shared_ptr<hitbox> HitboxData::getHitbox(wxString _ID)
{
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes.at(i)->getID() == _ID)
		{
			return hitboxes.at(i);
		}
	}
	return NULL;
}

int HitboxData::getHitboxCount()
{
	return hitboxes.size();
}

int HitboxData::getHitboxCounter()
{
	return hitboxCounter;
}

void HitboxData::setHitboxCounter(int _counter)
{
	hitboxCounter = _counter;
}

void HitboxData::addHurtbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID)
{
	hurtboxes.push_back(std::make_shared<hitbox>(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, _ID));
	hurtboxCounter++;
}

void HitboxData::removeHurtbox(wxString _ID)
{
	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		if (hurtboxes[i]->getID() == _ID)
		{
			hurtboxes.erase(hurtboxes.begin() + i);
		}
	}
}

std::shared_ptr<hitbox> HitboxData::getHurtbox(int _index)
{
	return hurtboxes.at(_index);
}

std::shared_ptr<hitbox> HitboxData::getHurtbox(wxString _ID)
{
	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		if (hurtboxes.at(i)->getID() == _ID)
		{
			return hurtboxes.at(i);
		}
	}
	return NULL;
}

int HitboxData::getHurtboxCount()
{
	return hurtboxes.size();
}

int HitboxData::getHurtboxCounter()
{
	return hurtboxCounter;
}

void HitboxData::setHurtboxCounter(int _counter)
{
	hurtboxCounter = _counter;
}

void HitboxData::Deselect()
{
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes.at(i)->getSelected())
		{
			hitboxes.at(i)->setSelected(false);
		}
	}

	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		if (hurtboxes.at(i)->getSelected())
		{
			hurtboxes.at(i)->setSelected(false);
		}
	}
}