#pragma once

#include "wx/wx.h"
#include "toeFrame.h"

class toeApp : public wxApp
{

private:
	toeFrame* m_frame = nullptr;


public:
	virtual bool OnInit();

};

