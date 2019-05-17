#include <wx/wx.h>
#include <wx/notebook.h>
struct Image;
class Frame;

class ImageTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesbox;
	wxScrolledWindow* imageContainer;
	wxStaticBitmap* image;
	wxButton* addButton;
	wxButton* removeButton;

public:
	ImageTab(Frame* parent, wxNotebook* guiParent);

	void onAddClicked(wxCommandEvent& event);
	void onRemoveClicked(wxCommandEvent& event);
	void onListBoxClicked(wxCommandEvent& event);

	void resizeContainer();
	Image* getImage(wxString name);

};
