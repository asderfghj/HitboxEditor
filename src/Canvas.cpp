#include "Headers.h"

wxSize Canvas::ScrollingIncrement = wxSize(10, 10);

Canvas::Canvas()
{
	Init();
}

Canvas::Canvas(wxWindow *Parent, HitboxTab *tabParent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
	Init();
	this->tabParent = tabParent;
	Create(Parent, id, pos, size, style, name);
}

bool Canvas::Create(wxWindow *Parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
	bool res = wxWindow::Create(Parent, id, pos, size);
	if (res)
	{

	}
	return res;
}

void Canvas::Init()
{
	m_View = NULL;
	m_leftMouseDown = false;
	m_rightMouseDown = false;
	Connect(this->GetId(), wxEVT_SCROLLWIN_LINEUP, (wxObjectEventFunction)&Canvas::OnScrollLineUp);
	Connect(this->GetId(), wxEVT_SCROLLWIN_LINEDOWN, (wxObjectEventFunction)&Canvas::OnScrollLineDown);
	Connect(this->GetId(), wxEVT_SCROLLWIN_PAGEUP, (wxObjectEventFunction)&Canvas::OnScrollPageUp);
	Connect(this->GetId(), wxEVT_SCROLLWIN_PAGEDOWN, (wxObjectEventFunction)&Canvas::OnScrollPageDown);
	Connect(this->GetId(), wxEVT_SCROLLWIN_THUMBTRACK, (wxObjectEventFunction)&Canvas::OnScrollThumbTrack);
	Connect(this->GetId(), wxEVT_SCROLLWIN_THUMBRELEASE, (wxObjectEventFunction)&Canvas::OnScrollThumbTrack);
	Connect(this->GetId(), wxEVT_PAINT, (wxObjectEventFunction)&Canvas::OnPaint);
	Connect(this->GetId(), wxEVT_IDLE, (wxObjectEventFunction)&Canvas::OnIdle);
	Connect(this->GetId(), wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Canvas::OnLeftDown);
	Connect(this->GetId(), wxEVT_LEFT_UP, (wxObjectEventFunction)&Canvas::OnLeftUp);
	Connect(this->GetId(), wxEVT_RIGHT_DOWN, (wxObjectEventFunction)&Canvas::OnRightDown);
	Connect(this->GetId(), wxEVT_RIGHT_UP, (wxObjectEventFunction)&Canvas::OnRightUp);
	Connect(this->GetId(), wxEVT_MOTION, (wxObjectEventFunction)&Canvas::OnMotion);
	Connect(this->GetId(), wxEVT_ERASE_BACKGROUND, (wxObjectEventFunction)&Canvas::OnEraseBackground);
	//Connect(this->GetId(), wxEVT_SIZE, (wxObjectEventFunction)&Canvas::FixViewOffset);
}


CanvasView* Canvas::GetView()
{
	return m_View;
}

void Canvas::SetView(CanvasView* value)
{
	m_View = value;
}

const wxRect& Canvas::GetSelection()
{
	return m_selection;
}

wxPoint Canvas::GetScrollPosition()
{
	return wxPoint(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void Canvas::Scroll(wxPoint pt)
{
	if (pt.x >= 0)
	{
		SetScrollPos(wxHORIZONTAL, pt.x);
	}
	if (pt.y >= 0)
	{
		SetScrollPos(wxVERTICAL, pt.y);
	}
	Refresh();
}

void Canvas::Scroll(int x, int y)
{
	Scroll(wxPoint(x, y));
}

wxSize Canvas::GetCurrentSize()
{
	if (!m_View)
	{
		return wxSize(0, 0);
	}
	return wxSize(m_View->GetScaledBitmap().GetWidth(), m_View->GetScaledBitmap().GetHeight());
}

void Canvas::AdjustScrollBars()
{
	wxSize imageSize = GetCurrentSize();

	wxPoint pt = GetScrollPosition();
	SetScrollbar(wxHORIZONTAL, 0, GetClientSize().x, imageSize.x);
	SetScrollbar(wxVERTICAL, 0, GetClientSize().y, imageSize.y);
	Scroll(pt.x, pt.y);
}

void Canvas::FixViewOffset()
{
	if (m_View)
	{
		wxPoint pt = GetScrollPosition();
		wxRect displayRect = GetImageDisplayRect(pt);
		wxSize offset(displayRect.GetPosition().x, displayRect.GetPosition().y);
		m_View->SetViewOffset(offset);
		//wxLogMessage((wxString::Format("View offset: (%i , %i)", offset.GetWidth(), offset.GetHeight())));
	}
}

wxRect Canvas::GetImageDisplayRect(const wxPoint& scrollPos)
{
	wxSize currentSize = GetCurrentSize();
	wxPoint ptTest((GetClientSize().x - currentSize.GetWidth()) <= 0 ? -scrollPos.x : ((GetClientSize().GetWidth() - currentSize.GetWidth()) * 0.5f), (GetClientSize().y - currentSize.GetHeight()) <= 0 ? -scrollPos.y : ((GetClientSize().GetHeight() - currentSize.GetHeight()) * 0.5f));
	return wxRect(ptTest, currentSize);
}

void Canvas::OnIdle(wxIdleEvent &event)
{
	do
	{
		if (!HasCapture())
		{
			break;
		}

		wxPoint scrollPos = GetScrollPosition();

		wxPoint currentPos = ScreenToClient(wxGetMousePosition());

		if (AutoScroll(currentPos, scrollPos))
		{
			event.RequestMore();
		}
		FixViewOffset();
	} while (false);
}

void Canvas::OnLeftDown(wxMouseEvent& event)
{
	if (!m_rightMouseDown)
	{
		m_leftMouseDown = true;
		SetFocus();
		wxRect imageRect = GetImageDisplayRect(GetScrollPosition());
		do
		{
			if (!m_View)
			{
				break;
			}

			wxPoint cursorPosOnImage = ClientToImage(event.GetPosition());

			if (!imageRect.Contains(event.GetPosition()))
			{
				break;
			}

			CaptureMouse();
			Refresh();
			m_TR = m_BL = event.GetPosition();
			m_selection.SetPosition(event.GetPosition());
			m_selection.SetSize(wxSize(0, 0));
		} while (false);
	}
}

void Canvas::OnLeftUp(wxMouseEvent& event)
{
	if (!m_rightMouseDown)
	{
		if (HasCapture())
		{
			ReleaseMouse();
			Refresh();

			tabParent->addHitbox(m_selection.GetLeft(), m_selection.GetTop(), ClientToImage(m_selection.GetTopLeft()).x, ClientToImage(m_selection.GetTopLeft()).y, m_selection.GetWidth(), m_selection.GetHeight(), m_View->GetViewOffset().x, m_View->GetViewOffset().y, false);
			m_TR = m_BL = wxPoint(0, 0);
			m_selection.SetPosition(m_TR);
			m_selection.SetSize(wxSize(0, 0));
			m_leftMouseDown = false;
		}
	}
}

void Canvas::OnRightDown(wxMouseEvent& event)
{
	if (!m_leftMouseDown)
	{
		m_rightMouseDown = true;
		SetFocus();
		wxRect imageRect = GetImageDisplayRect(GetScrollPosition());
		do
		{
			if (!m_View)
			{
				break;
			}

			wxPoint cursorPosOnImage = ClientToImage(event.GetPosition());

			if (!imageRect.Contains(event.GetPosition()))
			{
				break;
			}

			CaptureMouse();
			Refresh();
			m_TR = m_BL = event.GetPosition();
			m_selection.SetPosition(event.GetPosition());
			m_selection.SetSize(wxSize(0, 0));
		} while (false);
	}
}

void Canvas::OnRightUp(wxMouseEvent& event)
{
	if (!m_leftMouseDown)
	{
		if (HasCapture())
		{
			ReleaseMouse();
			Refresh();
			
			tabParent->addHitbox(m_selection.GetLeft(), m_selection.GetTop(), ClientToImage(m_selection.GetTopLeft()).x, ClientToImage(m_selection.GetTopLeft()).y, m_selection.GetWidth(), m_selection.GetHeight(), m_View->GetViewOffset().x, m_View->GetViewOffset().y, true);
			m_TR = m_BL = wxPoint(0, 0);
			m_selection.SetPosition(m_TR);
			m_selection.SetSize(wxSize(0, 0));
			m_rightMouseDown = false;
		}
	}
}

void Canvas::OnMotion(wxMouseEvent& event)
{
	if (HasCapture())
	{
		wxPoint currentPos = event.GetPosition();
		wxPoint scrollPos = GetScrollPosition();
		AutoScroll(currentPos, scrollPos);
		FixViewOffset();
		Refresh();
	}
}

bool Canvas::AutoScroll(wxPoint currentPos, wxPoint scrollPos)
{
	bool res = false;

	wxRect displayRect = GetImageDisplayRect(scrollPos);

	wxSize oldSelection(m_TR.x - m_BL.x, m_TR.y - m_BL.y);

	m_TR.x = wxMin(wxMax(currentPos.x, displayRect.GetLeft()), displayRect.GetRight());
	m_TR.y = wxMin(wxMax(currentPos.y, displayRect.GetTop()), displayRect.GetBottom());

	if (currentPos.x <= 0)
	{
		Scroll(wxMax(scrollPos.x - Canvas::ScrollingIncrement.GetWidth(), 0), -1);
		m_BL.x += (scrollPos.x - GetScrollPosition().x);
		res = true;
	}
	if (currentPos.y <= 0)
	{
		Scroll(-1, wxMax(scrollPos.y - Canvas::ScrollingIncrement.GetHeight(), 0));
		m_BL.y += (scrollPos.y - GetScrollPosition().y);
		res = true;
	}
	if (currentPos.x >= GetClientSize().GetWidth())
	{
		Scroll(scrollPos.x + Canvas::ScrollingIncrement.GetWidth(), -1);
		m_BL.x -= (GetScrollPosition().x - scrollPos.x);
		res = true;
	}
	if (currentPos.y >= GetClientSize().y)
	{
		Scroll(-1, scrollPos.y + Canvas::ScrollingIncrement.GetHeight());
		m_BL.y -= (GetScrollPosition().y - scrollPos.y);
		res = true;
	}

	m_selection = wxRect(wxMin(m_TR.x, m_BL.x), wxMin(m_TR.y, m_BL.y), abs(m_TR.x - m_BL.x), abs(m_TR.y - m_BL.y));
	return res;
}

void Canvas::OnScrollLineUp(wxScrollWinEvent& event)
{
	int increment = (event.GetOrientation() == wxHORIZONTAL ? Canvas::ScrollingIncrement.GetWidth() : Canvas::ScrollingIncrement.GetHeight());
	SetScrollPos(event.GetOrientation(), GetScrollPos(event.GetOrientation()) - increment);
	FixViewOffset();
	// wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnScrollLineDown(wxScrollWinEvent& event)
{
	int increment = (event.GetOrientation() == wxHORIZONTAL ? Canvas::ScrollingIncrement.GetWidth() : Canvas::ScrollingIncrement.GetHeight());
	SetScrollPos(event.GetOrientation(), GetScrollPos(event.GetOrientation()) + increment);
	FixViewOffset();
	//wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnScrollPageUp(wxScrollWinEvent& event)
{
	SetScrollPos(event.GetOrientation(), GetScrollPos(event.GetOrientation()) - GetScrollThumb(event.GetOrientation()));
	FixViewOffset();
	//wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnScrollPageDown(wxScrollWinEvent& event)
{
	SetScrollPos(event.GetOrientation(), GetScrollPos(event.GetOrientation()) + GetScrollThumb(event.GetOrientation()));
	FixViewOffset();
	//wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnScrollThumbTrack(wxScrollWinEvent& event)
{
	SetScrollPos(event.GetOrientation(), event.GetPosition());
	FixViewOffset();
	//wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	FixViewOffset();
	//wxScrolledWindow::HandleOnScroll(event);
	Refresh();
}

void Canvas::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);
	dc.SetBackground(wxBrush(GetBackgroundColour()));
	dc.Clear();
	if (m_View)
	{
		m_View->OnDraw(&dc);
		if (HasCapture() && !m_selection.IsEmpty())
		{
			dc.SetBrush(*wxTRANSPARENT_BRUSH);
			dc.SetLogicalFunction(wxXOR);
			dc.SetPen(wxPen(*wxWHITE, 3));
			dc.DrawRoundedRectangle(m_selection.GetPosition(), m_selection.GetSize(), 1.0f);
		}
	}
	DrawHitboxes(&dc);
}

wxPoint Canvas::ClientToImage(const wxPoint &pos)
{
	wxPoint scrollPos = GetScrollPosition();
	wxRect imageRect = GetImageDisplayRect(scrollPos);
	return wxPoint(pos.x - imageRect.GetLeft(), pos.y - imageRect.GetTop());
}

void Canvas::OnEraseBackground(wxEraseEvent &event)
{

}

void Canvas::DrawHitboxes(wxBufferedPaintDC* dc)
{

	for (int i = 0; i < tabParent->getHitboxArraySize(); i++)
	{
		dc->SetBrush(*wxTRANSPARENT_BRUSH);
		dc->SetLogicalFunction(wxCOPY);
		if (!tabParent->getHitbox(i)->getSelected())
		{
			dc->SetPen(wxPen(*wxRED, 3));
		}
		else
		{
			dc->SetPen(wxPen(*wxYELLOW, 3));
		}

		dc->DrawRectangle(tabParent->getHitbox(i)->getBox(m_View->GetViewOffset().x, m_View->GetViewOffset().y));
	}

	for (int i = 0; i < tabParent->getHurtboxArraySize(); i++)
	{
		dc->SetBrush(*wxTRANSPARENT_BRUSH);
		dc->SetLogicalFunction(wxCOPY);
		if (!tabParent->getHurtbox(i)->getSelected())
		{
			dc->SetPen(wxPen(*wxBLUE, 3));
		}
		else
		{
			dc->SetPen(wxPen(*wxYELLOW, 3));
		}

		dc->DrawRectangle(tabParent->getHurtbox(i)->getBox(m_View->GetViewOffset().x, m_View->GetViewOffset().y));
	}

}
