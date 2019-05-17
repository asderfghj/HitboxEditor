#include "Frame.h"
#include "ImageTab.h"
#include "HitboxTab.h"
#include "ImagesContainer.h"

Frame::Frame() : wxFrame(NULL, wxID_ANY, _("Hitbox Editor"), wxDefaultPosition, wxSize(1600, 1200))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	/*log_textctrl = new wxTextCtrl(this, -1, wxEmptyString, wxPoint(0, 250), wxSize(700, 100), wxTE_MULTILINE);

	logger = new wxLogTextCtrl(log_textctrl);
	logger->SetActiveTarget(logger);*/

	notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
	imageTab = new ImageTab(this, notebook);
	hitboxTab = new HitboxTab(this, notebook);
	notebook->AddPage(imageTab, _("Images"));
	notebook->AddPage(hitboxTab, _("Hitboxes"));


	imagesContainer = new ImagesContainer();

	sizer->Add(notebook, 1, wxEXPAND | wxALL, 0);
	SetSizerAndFit(sizer);
}


ImagesContainer* Frame::getImagesContainer()
{
	return imagesContainer;
}

void Frame::ImageAdded(wxString _imageName)
{
	hitboxTab->AddEntry(_imageName);
}

void Frame::ImageRemoved(wxString _imageName)
{
	hitboxTab->RemoveEntry(_imageName);
}