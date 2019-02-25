#include "Headers.h"

Image::Image(wxString path)
{
	this->path = path;
	//wxLogMessage(this->path);
	this->image = wxImage(path);

	if (!this->image.IsOk())
	{
		throw std::exception();
	}

	this->bitmap = wxBitmap(this->bitmap);
	this->name = wxFileName::FileName(path).GetFullName();
	//wxLogMessage(this->name);
}