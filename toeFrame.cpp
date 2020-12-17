#include "toeFrame.h"

toeFrame::toeFrame() : wxFrame(nullptr, wxID_ANY, "Tic-Tac-Toe", wxDefaultPosition, wxSize(m_nWindow_size, m_nWindow_size))
{
	this->SetMinSize(wxSize(m_nWindow_size, m_nWindow_size));
	this->SetMaxSize(wxSize(m_nWindow_size, m_nWindow_size));

	m_nField_value = new int[m_nSize * m_nSize];

	btn = new wxButton * [m_nSize * m_nSize];

	wxGridSizer* grid = new wxGridSizer(m_nSize, m_nSize, 0, 0);

	wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	for (int x = 0; x < m_nSize; x++)
	{
		for (int y = 0; y < m_nSize; y++)
		{
			btn[y * m_nSize + x] = new wxButton(this, 10 + (y * m_nSize + x));
			grid->Add(btn[y * m_nSize + x], 1, wxEXPAND | wxALL);
			btn[y * m_nSize + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &toeFrame::OnButtonClicked, this);

			btn[y * m_nSize + x]->SetFont(font);
			m_nField_value[y * m_nSize + x] = 0;

		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

toeFrame::~toeFrame()
{
	delete[]btn;
	delete[]m_nField_value;
}

void toeFrame::OnButtonClicked(wxCommandEvent& event)
{

	// getting x and y coordinates of clicked button
	int x = (event.GetId() - 10) % m_nSize;
	int y = (event.GetId() - 10) / m_nSize;

	btn[y * m_nSize + x]->Enable(false);

	m_nTotal_clicked++;

	if (m_bPlayer2_turn)
	{
		m_nField_value[y * m_nSize + x] = 2;
		btn[y * m_nSize + x]->SetLabel("X");
		m_bPlayer2_turn = false;
	}
	else
	{
		m_nField_value[y * m_nSize + x] = 1;
		btn[y * m_nSize + x]->SetLabel("O");
		m_bPlayer2_turn = true;
	}

	//check if someone wins
	if (m_nTotal_clicked >= 5)
	{

		switch (didLineCross())
		{
		case 1:
			// player 1 won
			wxMessageBox("Player 'O' Won!");
			reset();
			break;
		case 2:
			// player 2 won
			wxMessageBox("Player 'X' Won!");
			reset();
			break;
		}
	}

	if (m_nTotal_clicked == 9)
	{
		wxMessageBox("Draw!");
		reset();
	}

	event.Skip();
}

int toeFrame::didLineCross()
{

	/*
	{x,y}
	---------------------
	{0,0}, {0,1}, {0,2},
	{1,0}, {1,1}, {1,2},
	{2,0}, {2,1}, {2,2}
	---------------------
	{0},{3},{6},
	{1},{4},{7},
	{2},{5},{8}
	*/


	// for each row
	for (int x = 0; x < 3; x++)
	{

		if (m_nField_value[x] != 0
			&& m_nField_value[x] == m_nField_value[x + 3] && m_nField_value[x] == m_nField_value[x + 6])
			return m_nField_value[x];
	}

	// for each column
	for (int y = 0; y <= 6; y += 3)
	{
		if (m_nField_value[y] != 0
			&& m_nField_value[y] == m_nField_value[y + 1] && m_nField_value[y] == m_nField_value[y + 2])
			return m_nField_value[y];
	}

	// diagonal 1
	if (m_nField_value[0] != 0
		&& m_nField_value[0] == m_nField_value[4] && m_nField_value[4] == m_nField_value[8])
		return m_nField_value[0];

	// diagonal 2
	if (m_nField_value[2] != 0
		&& m_nField_value[2] == m_nField_value[4] && m_nField_value[4] == m_nField_value[6])
		return m_nField_value[2];

	return 0;
}

void toeFrame::reset()
{
	for (int x = 0; x < m_nSize; x++)
	{
		for (int y = 0; y < m_nSize; y++)
		{
			m_nField_value[y * m_nSize + x] = 0;
			btn[y * m_nSize + x]->SetLabel("");
			btn[y * m_nSize + x]->Enable(true);
		}
	}

	m_bPlayer2_turn = false;
	m_nTotal_clicked = 0;
}