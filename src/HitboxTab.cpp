#include "Headers.h"

HitboxTab::HitboxTab(Frame* parent, wxNotebook* guiParent) : wxPanel(guiParent, wxID_ANY)
{
	wxBoxSizer* vboxImages = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));
	wxBoxSizer* vboxColBoxes = new wxStaticBoxSizer(wxVERTICAL, this, _("Collision Boxes"));
	wxBoxSizer* vboxPPU = new wxStaticBoxSizer(wxVERTICAL, this, _("PPU"));

	wxBoxSizer* vboxMaster = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hboxMaster = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hboxAdd = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hboxHRemove = new wxBoxSizer(wxHORIZONTAL);


	this->parent = parent;
	imagesBox = new wxListBox(this, wxID_ANY);
	imagesBox->SetMinSize(wxSize(200, 0));
	Connect(imagesBox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&HitboxTab::OnImageBoxClick);
	

	removeButton = new wxButton(this, wxID_ANY, _("Remove"));
	Connect(removeButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onRemoveClicked);
	removeButton->SetMaxSize(wxSize(1000, 25));

	exportButton = new wxButton(this, wxID_ANY, _("Export"));
	Connect(exportButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onExportClicked);
	exportButton->SetMaxSize(wxSize(1000, 25));

	importButton = new wxButton(this, wxID_ANY, _("Import"));
	Connect(importButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&HitboxTab::onImportClicked);
	importButton->SetMaxSize(wxSize(1000, 25));

	hitboxesBox = new wxListBox(this, wxID_ANY);
	hitboxesBox->SetMinSize(wxSize(200, 0));
	Connect(hitboxesBox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&HitboxTab::OnHitboxBoxClick);

	PPUValue = new wxSpinCtrl(this, wxID_ANY);
	PPUValue->SetValue(100);
	PPUValue->SetRange(1, 999);
	PPUValue->SetMaxSize(wxSize(200, 25));
	Connect(PPUValue->GetId(), wxEVT_SPINCTRL, (wxObjectEventFunction)&HitboxTab::onSpinValChanged);


	imageContainer = new Canvas(this, this);
	canvasView = new CanvasView(imageContainer, this);

	/*hboxAdd->Add(addHitboxButton, 1, wxEXPAND | wxRIGHT, 5);
	hboxAdd->Add(addHurtboxButton, 1, wxEXPAND | wxALL, 0);*/

	vboxImages->Add(imagesBox, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hitboxesBox, 1, wxEXPAND | wxALL, 0);
	vboxPPU->Add(PPUValue, 1, wxEXPAND | wxALL, 0);

	vboxMaster->Add(vboxImages, 1, wxEXPAND | wxALL, 0);
	vboxMaster->Add(vboxColBoxes, 1, wxEXPAND | wxALL, 0);
	vboxMaster->Add(removeButton, 1, wxEXPAND | wxTOP, 5);
	vboxMaster->Add(exportButton, 1, wxEXPAND | wxTOP, 5);
	vboxMaster->Add(importButton, 1, wxEXPAND | wxTOP, 5);
	vboxMaster->Add(vboxPPU, 1, wxEXPAND | wxTOP, 5);
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
	hitboxCounter = 0;
	hurtboxCounter = 0;
	PPU = 100;
}

void HitboxTab::ForceUpdate()
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		wxBitmap bmp = wxBitmap(getImage(imagesBox->GetStringSelection())->image);
		canvasView->OnUpdate(NULL);
		parent->getImagesContainer()->DeselectAll();
		hitboxesBox->Clear();
		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHitboxes(imagesBox->GetStringSelection()); i++)
		{
			hitboxesBox->Append(parent->getImagesContainer()->getHitBox(imagesBox->GetStringSelection(), i)->getID());
		}

		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHurtboxes(imagesBox->GetStringSelection()); i++)
		{
			hitboxesBox->Append(parent->getImagesContainer()->getHurtBox(imagesBox->GetStringSelection(), i)->getID());
		}
	}

	imageContainer->FixViewOffset();
}

void HitboxTab::AddEntry(wxString name)
{
	imagesBox->Append(name);
}

void HitboxTab::RemoveEntry(wxString name)
{
	for (unsigned int i = 0; i < imagesBox->GetCount(); i++)
	{
		imagesBox->Delete(i);
	}
}

void HitboxTab::RemoveHitbox()
{
	if (hitboxesBox->GetSelection() != wxNOT_FOUND && imagesBox->GetSelection() != wxNOT_FOUND)
	{
		if (hitboxesBox->GetStringSelection().Find("hit") != wxNOT_FOUND)
		{
			parent->getImagesContainer()->RemoveHitbox(imagesBox->GetStringSelection(), hitboxesBox->GetStringSelection());
			hitboxesBox->Delete(hitboxesBox->GetSelection());
		}
		else if (hitboxesBox->GetStringSelection().Find("hurt") != wxNOT_FOUND)
		{
			parent->getImagesContainer()->RemoveHurtbox(imagesBox->GetStringSelection(), hitboxesBox->GetStringSelection());
			hitboxesBox->Delete(hitboxesBox->GetSelection());
		}
		currentlySelectedHitbox = NULL;
		imageContainer->Refresh();
	}
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
		parent->getImagesContainer()->DeselectAll();
		hitboxesBox->Clear();
		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHitboxes(imagesBox->GetStringSelection()); i++)
		{
			hitboxesBox->Append(parent->getImagesContainer()->getHitBox(imagesBox->GetStringSelection(), i)->getID());
		}

		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHurtboxes(imagesBox->GetStringSelection()); i++)
		{
			hitboxesBox->Append(parent->getImagesContainer()->getHurtBox(imagesBox->GetStringSelection(), i)->getID());
		}
	}

	imageContainer->FixViewOffset();
}

void HitboxTab::OnHitboxBoxClick(wxCommandEvent& event)
{
	if (hitboxesBox->GetSelection() != wxNOT_FOUND)
	{
		deselectSelectedHitbox();
		if (hitboxesBox->GetStringSelection().Find(_("hit")) != wxNOT_FOUND)
		{
			getHitbox(hitboxesBox->GetStringSelection())->setSelected(true);
			currentlySelectedHitbox = getHitbox(hitboxesBox->GetStringSelection());
		}
		else
		{
			getHurtbox(hitboxesBox->GetStringSelection())->setSelected(true);
			currentlySelectedHitbox = getHurtbox(hitboxesBox->GetStringSelection());
		}
		imageContainer->Refresh();
	}

}

void HitboxTab::onRemoveClicked(wxCommandEvent& event)
{
	RemoveHitbox();
}

Image* HitboxTab::getCurrentlySelectedImage()
{
	return getImage(imagesBox->GetStringSelection());
}

void HitboxTab::addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, bool _isHurtbox)
{
	wxString hitboxString;
	if (!_isHurtbox)
	{
		if (imagesBox->GetSelection() != wxNOT_FOUND)
		{
			hitboxString = wxString::Format("hitbox_%i", parent->getImagesContainer()->getHitboxCounter(imagesBox->GetStringSelection()));
			parent->getImagesContainer()->AddHitbox(imagesBox->GetStringSelection(), _cX, _cY, _iX, _iY, _w, _h, _oX, _oY, hitboxString);
			hitboxesBox->Append(hitboxString);
		}
	}
	else
	{
		if (imagesBox->GetSelection() != wxNOT_FOUND)
		{
			hitboxString = wxString::Format("hurtbox_%i", parent->getImagesContainer()->getHurtboxCounter(imagesBox->GetStringSelection()));
			parent->getImagesContainer()->AddHurtbox(imagesBox->GetStringSelection(), _cX, _cY, _iX, _iY, _w, _h, _oX, _oY, hitboxString);
			hitboxesBox->Append(hitboxString);
		}
	}
}

/*void HitboxTab::addHurtbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY)
{
	wxString hurtboxString = wxString::Format("hurtbox_%i", hurtboxCounter);
	hurtboxes.push_back(std::make_shared<hitbox>(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, hurtboxString));
	hitboxesBox->Append(hurtboxString);
	hurtboxCounter++;
}*/

std::shared_ptr<hitbox> HitboxTab::getHitbox(int _index)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getHitBox(imagesBox->GetStringSelection(), _index);
	}

	return NULL;
}

std::shared_ptr<hitbox> HitboxTab::getHitbox(wxString _ID)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getHitBox(imagesBox->GetStringSelection(), _ID);
	}

	return NULL;
}

int HitboxTab::getHitboxArraySize()
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getNumberOfHitboxes(imagesBox->GetStringSelection());
	}

	return NULL;
}

std::shared_ptr<hitbox> HitboxTab::getHurtbox(int _index)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getHurtBox(imagesBox->GetStringSelection(), _index);
	}

	return NULL;
}

std::shared_ptr<hitbox> HitboxTab::getHurtbox(wxString _ID)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getHurtBox(imagesBox->GetStringSelection(), _ID);
	}

	return NULL;
}

int HitboxTab::getHurtboxArraySize()
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		return parent->getImagesContainer()->getNumberOfHurtboxes(imagesBox->GetStringSelection());
	}

	return NULL;
}

void HitboxTab::deselectSelectedHitbox()
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		parent->getImagesContainer()->DeselectAll();
	}
}

nlohmann::json HitboxTab::generateJSON()
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		nlohmann::json rtn;
		std::vector<nlohmann::json> hitboxJSONData;
		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHitboxes(imagesBox->GetStringSelection()); i++)
		{
			hitboxJSONData.push_back(parent->getImagesContainer()->getHitBox(imagesBox->GetStringSelection(), i)->getJSONInfo(getCurrentlySelectedImage(), PPU));
		}
		std::vector<nlohmann::json> hurtboxJSONData;
		for (int i = 0; i < parent->getImagesContainer()->getNumberOfHurtboxes(imagesBox->GetStringSelection()); i++)
		{
			hurtboxJSONData.push_back(parent->getImagesContainer()->getHurtBox(imagesBox->GetStringSelection(), i)->getJSONInfo(getCurrentlySelectedImage(), PPU));
		}
		rtn["Hitboxes"] = hitboxJSONData;
		rtn["Hurtboxes"] = hurtboxJSONData;
		rtn["HitboxCounter"] = parent->getImagesContainer()->getHitboxCounter(imagesBox->GetStringSelection());
		rtn["HurtboxCounter"] = parent->getImagesContainer()->getHurtboxCounter(imagesBox->GetStringSelection());
		return rtn;
	}
	return NULL;

}

void HitboxTab::onExportClicked(wxCommandEvent& event)
{
	/*std::ofstream jsonfile;
	jsonfile.open("example.json");
	jsonfile << generateJSON();
	jsonfile.close();*/
	wxFileDialog* saveDialog = NULL;
	saveDialog = new wxFileDialog(this, _("Choose a location to save the hitbox data"), wxEmptyString, wxEmptyString, _("JSON Files (*.json) | *.json"), wxFD_SAVE);
	wxString path;
	wxTextFile* savefile = new wxTextFile();

	if (saveDialog->ShowModal() == wxID_OK)
	{
		path = saveDialog->GetPath();
	}

	saveDialog->Destroy();

	if (path == _(""))
	{
		return;
	}

	if (savefile->Create(path))
	{
		savefile->AddLine(_(generateJSON().dump()));
		savefile->Write();
		savefile->Close();
	}
	else
	{
		wxMessageDialog* warningDialog = NULL;
		warningDialog = new wxMessageDialog(this, _("File already exists! Overwrite?"), _("Warning!"), wxOK | wxCANCEL | wxCENTER);

		if (warningDialog->ShowModal() == wxID_OK)
		{
			warningDialog->Destroy();
			if (savefile->Open(path))
			{
				savefile->Clear();
				savefile->AddLine(_(generateJSON().dump()));
				savefile->Write();
				savefile->Close();
			}
			else
			{
				wxLogMessage("Could not open file, ERROR!");
			}
		}
		else if (warningDialog->ShowModal() == wxID_CANCEL)
		{
			warningDialog->Destroy();
		}

	}
}

void HitboxTab::onImportClicked(wxCommandEvent& event)
{
	if (imagesBox->GetSelection() != wxNOT_FOUND)
	{
		wxFileDialog* openDialogue = NULL;
		openDialogue = new wxFileDialog(this, _("Choose Hitbox data to import"), wxEmptyString, wxEmptyString, _("JSON Files (*.json) | *.json"), wxFD_OPEN);
		wxString path, jsonString;
		wxTextFile* openFile = new wxTextFile();
		nlohmann::json deserialisedJSON;

		if (openDialogue->ShowModal() == wxID_OK)
		{
			path = openDialogue->GetPath();
		}

		openDialogue->Destroy();

		if (path == _(""))
		{
			return;
		}

		if (openFile->Open(path))
		{
			jsonString = openFile->GetFirstLine();
		}
		else
		{
			return;
		}

		deserialisedJSON = nlohmann::json::parse(jsonString.ToStdString());

		for (int i = 0; i < deserialisedJSON["Hitboxes"].size(); i++)
		{
			parent->getImagesContainer()->AddHitbox(imagesBox->GetStringSelection(), deserialisedJSON["Hitboxes"][i]);
		}

		for (int i = 0; i < deserialisedJSON["Hurtboxes"].size(); i++)
		{
			parent->getImagesContainer()->AddHurtbox(imagesBox->GetStringSelection(), deserialisedJSON["Hurtboxes"][i]);
		}

		parent->getImagesContainer()->setHitboxCounter(imagesBox->GetStringSelection(), deserialisedJSON["HitboxCounter"]);
		parent->getImagesContainer()->setHurtboxCounter(imagesBox->GetStringSelection(), deserialisedJSON["HurtboxCounter"]);

	}
	ForceUpdate();
}

void HitboxTab::onSpinValChanged(wxSpinEvent& event)
{
	PPU = PPUValue->GetValue();
}
