#include "Headers.h"

HitboxTab::HitboxTab(Frame* parent, wxNotebook* guiParent) : wxPanel(guiParent, wxID_ANY)
{
	wxBoxSizer* vboxImages = new wxStaticBoxSizer(wxVERTICAL, this, _("Images"));
	wxBoxSizer* vboxColBoxes = new wxStaticBoxSizer(wxVERTICAL, this, _("Collision Boxes"));
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

	hitboxesBox = new wxListBox(this, wxID_ANY);
	hitboxesBox->SetMinSize(wxSize(200, 0));
	Connect(hitboxesBox->GetId(), wxEVT_COMMAND_LISTBOX_SELECTED, (wxObjectEventFunction)&HitboxTab::OnHitboxBoxClick);



	imageContainer = new Canvas(this, this);
	canvasView = new CanvasView(imageContainer, this);

	/*hboxAdd->Add(addHitboxButton, 1, wxEXPAND | wxRIGHT, 5);
	hboxAdd->Add(addHurtboxButton, 1, wxEXPAND | wxALL, 0);*/

	vboxImages->Add(imagesBox, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hitboxesBox, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(hboxAdd, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(removeButton, 1, wxEXPAND | wxALL, 0);
	vboxColBoxes->Add(exportButton, 1, wxEXPAND | wxALL, 0);

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
	hitboxCounter = 0;
	hurtboxCounter = 0;
}

void HitboxTab::AddEntry(wxString name)
{
	imagesBox->Append(name);
}

void HitboxTab::RemoveEntry(wxString name)
{
	for (int i = 0; i < imagesBox->GetCount(); i++)
	{
		imagesBox->Delete(i);
	}
}

void HitboxTab::RemoveHitbox()
{
	if (hitboxesBox->GetSelection() != wxNOT_FOUND)
	{
		if (hitboxesBox->GetStringSelection().Find("hit") != wxNOT_FOUND)
		{
			for (size_t i = 0; i < hitboxes.size(); i++)
			{
				if (hitboxes.at(i)->getID() == hitboxesBox->GetStringSelection())
				{
					hitboxes.erase(hitboxes.begin() + i);
					hitboxesBox->Delete(hitboxesBox->GetSelection());
					break;
				}
			}
		}
		else if (hitboxesBox->GetStringSelection().Find("hurt") != wxNOT_FOUND)
		{
			for (size_t i = 0; i < hurtboxes.size(); i++)
			{
				if (hurtboxes.at(i)->getID() == hitboxesBox->GetStringSelection())
				{
					hurtboxes.erase(hurtboxes.begin() + i);
					hitboxesBox->Delete(hitboxesBox->GetSelection());
					break;
				}
			}
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

void HitboxTab::onAddHitboxClicked(wxCommandEvent& event)
{

}

void HitboxTab::onAddHurtboxClicked(wxCommandEvent& event)
{

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
		hitboxString = wxString::Format("hitbox_%i", hitboxCounter);
		hitboxes.push_back(std::make_shared<hitbox>(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, hitboxString));
		hitboxesBox->Append(hitboxString);
		hitboxCounter++;
	}
	else
	{
		hitboxString = wxString::Format("hurtbox_%i", hurtboxCounter);
		hurtboxes.push_back(std::make_shared<hitbox>(_cX, _cY, _iX, _iY, _w, _h, _oX, _oY, hitboxString));
		hitboxesBox->Append(hitboxString);
		hurtboxCounter++;
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
	return hitboxes.at(_index);
}

std::shared_ptr<hitbox> HitboxTab::getHitbox(wxString _ID)
{
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes.at(i)->getID() == _ID)
		{
			return hitboxes.at(i);
		}
	}

	return NULL;
}

int HitboxTab::getHitboxArraySize()
{
	return hitboxes.size();
}

std::shared_ptr<hitbox> HitboxTab::getHurtbox(int _index)
{
	return hurtboxes.at(_index);
}

std::shared_ptr<hitbox> HitboxTab::getHurtbox(wxString _ID)
{
	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		if (hurtboxes.at(i)->getID() == _ID)
		{
			return hurtboxes.at(i);
		}
	}
	return NULL;
}

int HitboxTab::getHurtboxArraySize()
{
	return hurtboxes.size();
}

void HitboxTab::deselectSelectedHitbox()
{
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		if (hitboxes.at(i)->getSelected())
		{
			hitboxes.at(i)->setSelected(false);
		}
	}

	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		if (hurtboxes.at(i)->getSelected())
		{
			hurtboxes.at(i)->setSelected(false);
		}
	}
}

nlohmann::json HitboxTab::generateJSON()
{
	nlohmann::json rtn;
	std::vector<nlohmann::json> hitboxJSONData;
	for (size_t i = 0; i < hitboxes.size(); i++)
	{
		hitboxJSONData.push_back(hitboxes.at(i)->getJSONInfo(getCurrentlySelectedImage(), 100));
	}
	std::vector<nlohmann::json> hurtboxJSONData;
	for (size_t i = 0; i < hurtboxes.size(); i++)
	{
		hurtboxJSONData.push_back(hurtboxes.at(i)->getJSONInfo(getCurrentlySelectedImage(), 100));
	}
	rtn["Hitboxes"] = hitboxJSONData;
	rtn["Hurtboxes"] = hurtboxJSONData;
	return rtn;

}

void HitboxTab::onExportClicked(wxCommandEvent& event)
{
	std::ofstream jsonfile;
	jsonfile.open("example.json");
	jsonfile << generateJSON();
	jsonfile.close();
}

