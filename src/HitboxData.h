#ifndef HITBOXDATA_H_
#define HITBOXDATA_H_

#include <vector>
#include <memory>
#include <wx/wx.h>

class hitbox;
struct Image;

//class that contains an image and all of the hitbox and hurtbox data related to the image
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
	void addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);//creates a new hitbox, adds to the hitboxes vector
	void removeHitbox(wxString _ID);//searches for a hitbox based on the ID and deletes it if a hitbox matches the ID provided
	std::shared_ptr<hitbox> getHitbox(int _index);//returns a hitbox based on the index
	std::shared_ptr<hitbox> getHitbox(wxString _ID);//returns a hitbox based on the ID
	int getHitboxCount();//returns the number of hitboxes in the hitboxes vector
	int getHitboxCounter();//returns the hitbox counter. Used for generating hitbox IDs
	void setHitboxCounter(int _counter);
	void addHurtbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	void removeHurtbox(wxString _ID);
	std::shared_ptr<hitbox> getHurtbox(int _index);
	std::shared_ptr<hitbox> getHurtbox(wxString _ID);
	int getHurtboxCount();
	int getHurtboxCounter();
	void setHurtboxCounter(int _counter);
	void Deselect();//sets, isselected on all hit and hurt boxes to false.
};

#endif