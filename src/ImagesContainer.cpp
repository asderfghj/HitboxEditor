#include "ImagesContainer.h"
#include "HitboxData.h"
#include "Image.h"
#include "Hitbox.h"

void ImagesContainer::addImage(std::shared_ptr<Image> _image)
{
	files.push_back(std::make_shared<HitboxData>(_image));
}

void ImagesContainer::removeImage(wxString _name)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _name)
		{
			files.erase(files.begin() + i);
			break;
		}
	}
}

Image* ImagesContainer::getImage(wxString _name)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _name)
		{
			return files[i]->getImage();
		}
	}

	return NULL;
}

std::shared_ptr<hitbox> ImagesContainer::getHitBox(wxString _imageName, int _HBIndex)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			return files[i]->getHitbox(_HBIndex);
		}
	}
	return NULL;
}

std::shared_ptr<hitbox> ImagesContainer::getHitBox(wxString _imageName, wxString _ID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			for (int j = 0; j < files[i]->getHitboxCount(); j++)
			{
				if (files[i]->getHitbox(j)->getID() == _ID)
				{
					return files[i]->getHitbox(j);
				}
			}
		}
	}
	return NULL;
}

void ImagesContainer::AddHitbox(wxString _imageName, float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->addHitbox(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, _ID);
		}
	}
}

void ImagesContainer::AddHitbox(wxString _imageName, nlohmann::json jsonData)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			std::string ID = jsonData["ID"];
			files[i]->addHitbox(jsonData["cX"], jsonData["cY"], jsonData["iX"], jsonData["iY"], jsonData["iW"], jsonData["iH"], jsonData["oX"], jsonData["oY"], _(ID));
		}
	}
}

void ImagesContainer::RemoveHitbox(wxString _imageName, wxString _HBID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->removeHitbox(_HBID);
		}
	}
}

int ImagesContainer::getNumberOfHitboxes(wxString _imagename)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imagename)
		{
			return files[i]->getHitboxCount();
		}
	}
	return NULL;
}

int ImagesContainer::getHitboxCounter(wxString _imageName)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			return files[i]->getHitboxCounter();
		}
	}
	throw std::exception();
}

void ImagesContainer::setHitboxCounter(wxString _imageName, int _counter)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->setHitboxCounter(_counter);
		}
	}
	throw std::exception();
}


std::shared_ptr<hitbox> ImagesContainer::getHurtBox(wxString _imageName, int _HBIndex)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			return files[i]->getHurtbox(_HBIndex);
		}
	}
	return NULL;
}

std::shared_ptr<hitbox> ImagesContainer::getHurtBox(wxString _imageName, wxString _ID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			for (int j = 0; j < files[i]->getHurtboxCount(); j++)
			{
				if (files[i]->getHurtbox(j)->getID() == _ID)
				{
					return files[i]->getHurtbox(j);
				}
			}
		}
	}
	return NULL;
}

void ImagesContainer::AddHurtbox(wxString _imageName, float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->addHurtbox(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, _ID);
		}
	}
}

void ImagesContainer::AddHurtbox(wxString _imageName, nlohmann::json jsonData)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			std::string ID = jsonData["ID"];
			files[i]->addHurtbox(jsonData["cX"], jsonData["cY"], jsonData["iX"], jsonData["iY"], jsonData["iW"], jsonData["iH"], jsonData["oX"], jsonData["oY"], _(ID));
		}
	}
}

void ImagesContainer::RemoveHurtbox(wxString _imageName, wxString _HBID)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->removeHurtbox(_HBID);
		}
	}
}

int ImagesContainer::getNumberOfHurtboxes(wxString _imagename)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imagename)
		{
			return files[i]->getHurtboxCount();
		}
	}
	return NULL;
}

int ImagesContainer::getHurtboxCounter(wxString _imageName)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			return files[i]->getHurtboxCounter();
		}
	}

	throw std::exception();
}

void ImagesContainer::setHurtboxCounter(wxString _imageName, int _counter)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _imageName)
		{
			files[i]->setHurtboxCounter(_counter);
		}
	}
}


bool ImagesContainer::checkForImage(wxString _path)
{
	for (size_t i = 0; i < files.size(); i++)
	{
		if (files[i]->getImage()->name == _path)
		{
			return true;
		}
	}
	return false;
}

void ImagesContainer::DeselectAll()
{
	for (size_t i = 0; i < files.size(); i++)
	{
		files[i]->Deselect();
	}
}