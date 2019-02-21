#ifndef IMAGE_H_
#define IMAGE_H_
#include "Headers.h"

struct Image
{
	wxString path;
	wxString name;
	wxImage image;
	wxBitmap bitmap;

	Image(wxString path);
};

#endif // !IMAGE_H_