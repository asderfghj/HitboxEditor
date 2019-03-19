#ifndef IMAGESCONTAINER_H_
#define IMAGESCONTAINER_H_
#include "Headers.h"

class HitboxData;
class hitbox;

class ImagesContainer
{
	std::vector<std::shared_ptr<HitboxData>> files;

public:
	void addImage(std::shared_ptr<Image> _image);
	void removeImage(wxString _name);
	Image* getImage(wxString _name);
	std::shared_ptr<hitbox> getHitBox(wxString _imageName, int _HBIndex);
	std::shared_ptr<hitbox> getHitBox(wxString _imageName, wxString _ID);
	void AddHitbox(wxString _imageName, float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	void AddHitbox(wxString _imageName, nlohmann::json jsonData);
	void RemoveHitbox(wxString _imagename, wxString _HBID);
	int getNumberOfHitboxes(wxString _imagename);
	int getHitboxCounter(wxString _imageName);
	void setHitboxCounter(wxString _imageName, int _counter);

	std::shared_ptr<hitbox> getHurtBox(wxString _imageName, int _HBIndex);
	std::shared_ptr<hitbox> getHurtBox(wxString _imageName, wxString _ID);
	void AddHurtbox(wxString _imageName, float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);
	void AddHurtbox(wxString _imageName, nlohmann::json jsonData);
	void RemoveHurtbox(wxString _imagename, wxString _HBID);
	int getNumberOfHurtboxes(wxString _imagename);
	int getHurtboxCounter(wxString _imageName);
	void setHurtboxCounter(wxString _imageName, int _counter);
	bool checkForImage(wxString _path);
	void DeselectAll();

};





#endif // !IMAGESCONTAINER_H_
