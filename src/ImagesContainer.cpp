#include "Headers.h"

void ImagesContainer::addImage(std::shared_ptr<Image> _image)
{
	images.push_back(_image);
}

void ImagesContainer::removeImage(wxString _name)
{
	for (size_t i = 0; i < images.size(); i++)
	{
		if (images[i]->name == _name)
		{
			images.erase(images.begin() + i);
			break;
		}
	}
}

Image* ImagesContainer::getImage(wxString _name)
{
	for (size_t i = 0; i < images.size(); i++)
	{
		if (images[i]->name == _name)
		{
			return images[i].get();
		}
	}

	return NULL;
}

bool ImagesContainer::checkForImage(wxString _path)
{
	for (size_t i = 0; i < images.size(); i++)
	{
		if (images[i]->path == _path)
		{
			return true;
		}
	}

	return false;
}