#include "Headers.h"

HitboxTab::HitboxTab(Frame* parent, wxNotebook* guiParent) : wxPanel(guiParent, wxID_ANY)
{
	wxBoxSizer* vboxImages = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));
	wxBoxSizer* vboxColBoxes = new wxStaticBoxSizer(wxVERTICAL, this, _("Collision Boxes"));
	wxBoxSizer* vboxMaster = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hboxMaster = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hboxPosition = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Position"));
	wxBoxSizer* hboxSize = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Size"));
	wxBoxSizer* hboxAdd = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hboxHRemove = new wxBoxSizer(wxHORIZONTAL);

	this->parent = parent;
	imagesBox = new wxListBox(this, wxID_ANY);
	imagesBox->SetMinSize(wxSize(200, 0));
	Connect(imagesBox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&HitboxTab::OnImageBoxClick);

	addHitboxButton = new wxButton(this, wxID_ANY, _("Add Hitbox"));
	Connect(addHitboxButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onAddHitboxClicked);
	addHitboxButton->SetMaxSize(wxSize(100, 25));
	addHurtboxButton = new wxButton(this, wxID_ANY, _("Add Hurtbox"));
	Connect(addHurtboxButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onAddHurtboxClicked);
	addHurtboxButton->SetMaxSize(wxSize(100, 25));
	removeButton = new wxButton(this, wxID_ANY, _("Remove"));
	Connect(removeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onRemoveClicked);
	removeButton->SetMaxSize(wxSize(200, 25));

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



	imageContainer = new Canvas(this);
	canvasView = new CanvasView(imageContainer, this);

	hboxPosition->Add(posXDisplay, 1, wxEXPAND | wxALL, 0);
	hboxPosition->Add(posYDisplay, 1, wxEXPAND | wxALL, 0);

	hboxSize->Add(WidthDisplay, 1, wxEXPAND | wxALL, 0);
	hboxSize->Add(HeightDisplay, 1, wxEXPAND | wxALL, 0);

	hboxAdd->Add(addHitboxButton, 1, wxEXPAND | wxRIGHT, 5);
	hboxAdd->Add(addHurtboxButton, 1, wxEXPAND | wxALL, 0);

	vboxImages->Add(imagesBox, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hitboxesBox, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hboxPosition, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hboxSize, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hboxAdd, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(removeButton, 1, wxEXPAND | wxALL, 0);

	vboxMaster->Add(vboxImages, 1, wxEXPAND | wxALL, 0);
	vboxMaster->Add(vboxColBoxes, 1, wxEXPAND | wxALL, 0);
	hboxMaster->Add(vboxMaster, 0, wxEXPAND | wxALL, 5);
	hboxMaster->Add(imageContainer, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	wxBoxSizer* vboxDisplayImage = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hboxDisplayImage = new wxBoxSizer(wxHORIZONTAL);
	//displayImage = new wxStaticBitmap(imageContainer, wxID_ANY, wxBitmap(wxImage(100, 100, true)));
	//displayImage->Hide();

	/*hboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	hboxDisplayImage->Add(displayImage, 0, wxEXPAND | wxALL, 5);
	hboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);

	vboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	vboxDisplayImage->Add(hboxDisplayImage, 0, wxEXPAND | wxALL, 0);
	vboxDisplayImage->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	imageContainer->SetSizer(vboxDisplayImage);*/


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
	//displayImage->Hide();
}

void HitboxTab::resizeContainer()
{
	//imageContainer->SetVirtualSize(displayImage->GetSize().GetWidth(), displayImage->GetSize().GetHeight());
	//imageContainer->SetScrollRate(10, 10);
}

Image* HitboxTab::getImage(wxString name)
{
	Image* returnImage = NULL;

	returnImage = parent->getImagesContainer()->getImage(name);

	if (returnImage == NULL)
	{
		throw std::exception();
	}

	return returnImage;
}

void HitboxTab::OnImageBoxClick(wxCommandEvent& event)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		wxBitmap bmp = wxBitmap(getImage(imagesBox->GetStringSelection())->image);
		canvasView->OnUpdate(NULL);
	}

	resizeContainer();
}

void HitboxTab::onAddHitboxClicked(wxCommandEvent& event)
{

}

void HitboxTab::onAddHurtboxClicked(wxCommandEvent& event)
{

}

void HitboxTab::onRemoveClicked(wxCommandEvent& event)
{

}

Image* HitboxTab::getCurrentlySelectedImage()
{
	return getImage(imagesBox->GetStringSelection());
}