#include "Headers.h"

ImageTab::ImageTab(Frame* parent, wxNotebook* guiParent) : wxPanel(guiParent, wxID_ANY)
{
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vbox = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));

	this->parent = parent;
	imagesbox = new wxListBox(this, wxID_ANY);
	imagesbox->SetMinSize(wxSize(200, 0));
	Connect(imagesbox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&ImageTab::onListBoxClicked);
	imageContainer = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);

	/*wxArrayString testArray;
	testArray.Add("test");

	imagesbox->InsertItems(testArray, 0);*/

	addButton = new wxButton(this, wxID_ANY, _("Add"));
	Connect(addButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&ImageTab::onAddClicked);
	removeButton = new wxButton(this, wxID_ANY, _("Remove"));
	Connect(removeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&ImageTab::onRemoveClicked);

	vbox->Add(imagesbox, 1, wxEXPAND | wxALL, 0);
	vbox->Add(addButton, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
	vbox->Add(removeButton, 0, wxEXPAND | wxALL, 0);
	hbox->Add(vbox, 0, wxEXPAND | wxALL, 5);
	hbox->Add(imageContainer, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);

	wxBoxSizer* vbox2 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	image = new wxStaticBitmap(imageContainer, wxID_ANY, wxBitmap(wxImage(100, 100, true)));
	image->Hide();

	hbox2->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	hbox2->Add(image, 0, wxEXPAND | wxALL, 5);
	hbox2->Add(0, 0, 1, wxEXPAND | wxALL, 0);

	vbox2->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	vbox2->Add(hbox2, 0, wxEXPAND | wxALL, 0);
	vbox2->Add(0, 0, 1, wxEXPAND | wxALL, 0);
	imageContainer->SetSizer(vbox2);



	SetSizerAndFit(hbox);
}

void ImageTab::resizeContainer()
{
	imageContainer->SetVirtualSize(image->GetSize().GetWidth(), image->GetSize().GetHeight());
	imageContainer->SetScrollRate(10, 10);
}

void ImageTab::onRemoveClicked(wxCommandEvent& event)
{

	for (int i = 0; i < images.size(); i++)
	{
		if (images[i]->name == imagesbox->GetStringSelection())
		{
			images.erase(images.begin() + i);
			imagesbox->Delete(imagesbox->GetSelection());
			break;
		}
	}

}

void ImageTab::onAddClicked(wxCommandEvent& event)
{
	Image* imageInfo = NULL;
	wxString path;
	wxFileDialog* openDialog = NULL;

	openDialog = new wxFileDialog(this, _("Choose an image to open"), wxEmptyString, wxEmptyString, _("Image files (*.png, *.jpg)|*.png;*.jpg"), wxFD_OPEN, wxDefaultPosition);

	
	


	if (openDialog->ShowModal() == wxID_OK)
	{
		path = openDialog->GetPath();
	}

	openDialog->Destroy();

	if (path == _(""))
	{
		return;
	}
	
	for (int i = 0; i < images.size(); i++)
	{
		if (images[i]->path == path)
		{
			return;
		}
	}


	imageInfo = new Image(path);
	images.push_back(std::shared_ptr<Image>(imageInfo));
	wxArrayString infoToPush;
	infoToPush.Add(imageInfo->name);
	imagesbox->InsertItems(infoToPush, images.size() - 1);
}

Image* ImageTab::tryGetImage(wxString name)
{
	for (int i = 0; i < images.size(); i++)
	{
		if (images[i]->name == name)
		{
			return images[i].get();
		}
	}

	return NULL;
}

Image* ImageTab::getImage(wxString name)
{
	Image* returnImage = NULL;

	returnImage = tryGetImage(name);

	if (returnImage == NULL)
	{
		throw std::exception();
	}

	return returnImage;
}

void ImageTab::onListBoxClicked(wxCommandEvent& event)
{
	if (imagesbox->GetSelection() != wxNOT_FOUND)
	{
		wxBitmap bmp = wxBitmap(getImage(imagesbox->GetStringSelection())->image);

		image->SetBitmap(bmp);
		image->Show();
	}

	resizeContainer();
}

