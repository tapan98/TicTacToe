#pragma once

#include "wx/wx.h"

class toeFrame : public wxFrame
{
public:

	toeFrame();
	~toeFrame();

	wxButton** btn;



private:
	const int m_nSize = 3;
	const int m_nWindow_size = 300;

	int* m_nField_value = nullptr;
	bool m_bPlayer2_turn = false;
	int m_nTotal_clicked = 0;
	void reset();


	int didLineCross();
	void OnButtonClicked(wxCommandEvent& event);

};

