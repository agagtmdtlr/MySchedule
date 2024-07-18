#include "MyFrame.h"
#include <wx/grid.h>
#include <time.h>

enum
{
	ID_Hello = 1
};


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	//: wxFrame(nullptr, wxID_ANY, title, pos, size, wxNO_BORDER) // 
	: wxFrame(nullptr, wxID_ANY, title, pos, size)

{
	menuFile = new wxMenu();
	menuFile->Append(ID_Hello, "&Hello...\tCtrl+H", "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	menuHelp = new wxMenu();
	menuHelp->Append(wxID_ABOUT);

	menuBar = new wxMenuBar();
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets!");

	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	grid = new wxGrid(this, -1, wxPoint(0, 0), wxSize(400, 300));

	grid->SetDefaultRowSize(60, true);
	grid->SetDefaultColSize(120, true);
	grid->CreateGrid(5, 7);

	grid->SetCellValue(0, 3, "This is read-only");
	grid->SetReadOnly(0, 3);

	grid->SetCellValue(3, 3, "green on grey");
	grid->SetCellTextColour(3, 3, *wxGREEN);
	grid->SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);

	grid->SetColLabelValue(0, "Mon");
	grid->SetColLabelValue(1, "Tue");
	grid->SetColLabelValue(2, "Wed");
	grid->SetColLabelValue(3, "Thu");
	grid->SetColLabelValue(4, "Fri");
	grid->SetColLabelValue(5, "Sat");
	grid->SetColLabelValue(6, "Sun");

	// individual set size
	//grid->SetRowSize(0,60);
	//grid->SetColSize(0,120);

	time_t rawTime;
	rawTime = time(nullptr);
	tm* pTimeInfo;
	pTimeInfo = localtime(&rawTime);

	int year = pTimeInfo->tm_year +1900;
	int month = pTimeInfo->tm_mon + 1;
	int day = pTimeInfo->tm_mday;
	int hour = pTimeInfo->tm_hour;
	int min = pTimeInfo->tm_min;
	int sec = pTimeInfo->tm_sec;

	wxString currentTime = wxString::Format("%d년 %d월 %d일 %d시 %d분 %d초\n", year, month, day, hour, min, sec);

	grid->SetCellValue(0, 0, currentTime);
	

	timer = new wxTimer(this, wxID_ANY);
	Connect(wxID_ANY,wxEVT_TIMER, wxTimerEventHandler(MyFrame::OnTimer));
	timer->Start(0);

	
}

void MyFrame::OnTimer(wxTimerEvent& event)
{
	time_t rawTime;
	rawTime = time(nullptr);
	tm* pTimeInfo;
	pTimeInfo = localtime(&rawTime);

	int year = pTimeInfo->tm_year + 1900;
	int month = pTimeInfo->tm_mon + 1;
	int day = pTimeInfo->tm_mday;
	int hour = pTimeInfo->tm_hour;
	int min = pTimeInfo->tm_min;
	int sec = pTimeInfo->tm_sec;

	wxString currentTime = wxString::Format("%d년 %d월 %d일 %d시 %d분 %d초\n", year, month, day, hour, min, sec);

	grid->SetCellValue(0, 0, currentTime);

	grid->UpdateGridWindows();
}


void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello World from wxWidgets!");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidgets HelloWorld example", "About Hellow World", wxOK | wxICON_INFORMATION);
}

void MyFrame::Refresh(bool eraseBackground /*= true*/, const wxRect* rect /*= (const wxRect*)NULL*/)
{
	
}

void MyFrame::Update()
{
	


}

