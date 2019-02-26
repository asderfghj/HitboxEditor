#include "Headers.h"

HitboxTab::HitboxTab(Frame* parent, wxNotebook* guiParent) : wxPanel(guiParent, wxID_ANY)
{
	wxBoxSizer* vboxImages = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));
	wxBoxSizer* vboxHitboxes = new wxStaticBoxSizer(wxVERTICAL, this, _("Hitboxes"));
	wxBoxSizer* vboxMaster = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hboxMaster = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hboxPosition = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Position"));
	wxBoxSizer* hboxSize = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Size"));

	this->parent = parent;
	imagesBox = new wxListBox(this, wxID_ANY);
	imagesBox->SetMinSize(wxSize(200, 0));
	hitboxesBox = new wxListBox(this, wxID_ANY);
	hitboxesBox->SetMinSize(wxSize(200, 0));

	posXDisplay = new wxSpinCtrlDouble(this, wxID_ANY);
	posXDisplay->SetMaxSize(wxSize(200, 25));
	posYDisplay = new wxSpinCtrlDouble(this, wxID_ANY);
	posYDisplay->SetMaxSize(wxSize(200, 25));
	WidthDisplay = new wxSpinCtrlDouble(this, wxID_ANY);
	WidthDisplay->SetMaxSize(wxSize(200, 25));
	HeightDisplay = new wxSpinCtrlDouble(this, wxID_ANY);
	HeightDisplay->SetMaxSize(wxSize(200, 25));



	imageContainer = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);

	hboxPosition->Add(posXDisplay, 1, wxEXPAND | wxALL, 0);
	hboxPosition->Add(posYDisplay, 1, wxEXPAND | wxALL, 0);

	hboxSize->Add(WidthDisplay, 1, wxEXPAND | wxALL, 0);
	hboxSize->Add(HeightDisplay, 1, wxEXPAND | wxALL, 0);

	vboxImages->Add(imagesBox, 1, wxEXPAND | wxALL, 0);
	vboxHitboxes->Add(hitboxesBox, 1, wxEXPAND | wxALL, 0);
	vboxHitboxes->Add(hboxPosition, 1, wxEXPAND | wxALL, 0);
	vboxHitboxes->Add(hboxSize, 1, wxEXPAND | wxALL, 0);
	vboxMaster->Add(vboxImages, 1, wxEXPAND | wxALL, 0);
	vboxMaster->Add(vboxHitboxes, 1, wxEXPAND | wxALL, 0);
	hboxMaster->Add(vboxMaster, 0, wxEXPAND | wxALL, 5);
	hboxMaster->Add(imageContainer, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	wxBoxSizer* vboxDisplayImage = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hboxDisplayImage = new wxBoxSizer(wxHORIZONTAL);
	displayImage = new wxStaticBitmap(imageContainer, wxID_ANY, wxBitmap(wxImage(100, 100, true)));
	displayImage->Hide();

	hboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	hboxDisplayImage->Add(displayImage, 0, wxEXPAND | wxALL, 5);
	hboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);

	vboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	vboxDisplayImage->Add(hboxDisplayImage, 0, wxEXPAND | wxALL, 0);
	vboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	imageContainer->SetSizer(vboxDisplayImage);

	SetSizerAndFit(hboxMaster);

}

void HitboxTab::AddEntry(wxString _imageName)
{
	imagesBox->Append(_imageName);
}

void HitboxTab::RemoveEntry(wxString _imageName)
{
	for (size_t i = 0; i < imagesBox->GetCount(); i++)
	{
		if (imagesBox->GetString(i) == _imageName)
		{
			imagesBox->Delete(i);
			break;
		}
	}
}
