#include <wx/wx.h>
#include <wx/filename.h>
#include "Image.h"

Image::Image(wxString path)
{
	this->path = path;
	//wxLogMessage(this->path);
	this->image = wxImage(path);

	if (!this->image.IsOk())
	{
		throw std::exception();
	}

	this->name = wxFileName::FileName(path).GetFullName();
	//wxLogMessage(this->name);
}