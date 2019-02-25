#ifndef IMAGESCONTAINER_H_
#define IMAGESCONTAINER_H_
#include "Headers.h"

class ImagesContainer
{
	std::vector<std::shared_ptr<Image>> images;

public:
	void addImage(std::shared_ptr<Image> _image);
	void removeImage(wxString _name);
	Image* getImage(wxString _name);
	bool checkForImage(wxString _path);

};





#endif // !IMAGESCONTAINER_H_
