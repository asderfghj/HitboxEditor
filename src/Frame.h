#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>

class ImageTab;
class HitboxTab;
class ImagesContainer;

class Frame : public wxFrame
{
	wxNotebook* notebook;//used for the tabbing system, currently has two tabs, hitbox and image
	ImageTab* imageTab;//See image tab
	HitboxTab* hitboxTab;//See hitbox tab
	
	//Debugging stuff
	wxTextCtrl* log_textctrl;
	wxLogTextCtrl* logger;

	ImagesContainer* imagesContainer;//Used to store images and hitboxes, see images container

	public:
		Frame();//initialises the frame, intialises notebook and the two tabs, assigns the tabs to the notebook so that they can be displayed on the tabbing system 

		ImagesContainer* getImagesContainer();
		void ImageAdded(wxString _imageName);//Informs the hitbox tab that an image has been added to the image tab so that the tab can update image list box to include the new image
		void ImageRemoved(wxString _imageName);//Informs the hitbox tab that an image has been deleted from the image tab so that the tab can remove it from the list box andhide the image if it was displayed
};
