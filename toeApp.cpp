#include "toeApp.h"

wxIMPLEMENT_APP(toeApp);

bool toeApp::OnInit()
{
	m_frame = new toeFrame();

	m_frame->Show();

	return true;
}