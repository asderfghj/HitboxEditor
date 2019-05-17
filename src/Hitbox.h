#include <nlohmann/json.hpp>

struct Image;

class hitbox
{
public:
	hitbox();//default contructor, assigns everything to zero
	hitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, wxString _ID);//better contructor, assigns all of the values for a hitbox
	wxRect getBox(float _currentOffsetX, float _currentOffsetY);//returns a rect that will be drawn in the hitbox tab, takes into account the scrolled position and offsets based on that
	wxString getID();
	bool getSelected();
	void setSelected(bool _selected);
	nlohmann::json getJSONInfo(Image* _currentImage, int _PPU);//returns all of the information in a JSON class for exportation 

private:
	float clientX, clientY, imageX, imageY, w, h, startOffsetX, startOffsetY;//client(x,y): the postion in the window, image(x,y): position on the image top left is origin, (w,h): width and height, startOffset(x,y): The scroll offset when the rect is created 
	wxString ID;//identifier for the hitbox
	bool isSelected;//if this value is set to true, the box will yellow rather than it's default color to indicate it has been selected.
	wxRealPoint convertPosition(Image* _currentImage, int _PPU);//converts position values from pixel space to unity unity space for exportation
	wxRealPoint convertSize(int _PPU);//converts size values from pixel space to unity unity space for exportation
};


