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
	tm* localTimeInfo;
	localTimeInfo = localtime(&rawTime);

	int year = localTimeInfo->tm_year +1900;
	int month = localTimeInfo->tm_mon + 1;
	int day = localTimeInfo->tm_mday;
	int hour = localTimeInfo->tm_hour;
	int min = localTimeInfo->tm_min;
	int sec = localTimeInfo->tm_sec;

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
	tm* localTimeInfo;
	localTimeInfo = localtime(&rawTime);

	int year = localTimeInfo->tm_year + 1900;
	int month = localTimeInfo->tm_mon + 1;
	int day = localTimeInfo->tm_mday;
	int hour = localTimeInfo->tm_hour;
	int min = localTimeInfo->tm_min;
	int sec = localTimeInfo->tm_sec;



	wxString currentTime(asctime(localTimeInfo));

	//wxString currentTime = wxString::Format("%d년 %d월 %d일 %d시 %d분 %d초\n", year, month, day, hour, min, sec);

	grid->SetCellValue(0, 0, currentTime);


	time_t testTime = MakeTime(2024,7,1);
	tm* testLocal;
	testLocal = localtime(&testTime);

	wxString testString = asctime(testLocal);
	grid->SetCellValue(0, 1, testString);
	time_t testTime2 = MakeTime(2024,7,0);
	testLocal = localtime(&testTime2);

	testString  = asctime(testLocal);
	grid->SetCellValue(0, 2, testString);

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

time_t MyFrame::MakeTime(int year, int month, int day)
{
	tm NewTime;
	NewTime.tm_year = year - 1900;
	NewTime.tm_mon = month - 1;
	NewTime.tm_mday = day;
	NewTime.tm_hour = 0;
	NewTime.tm_min = 0;
	NewTime.tm_sec = 0;
	NewTime.tm_isdst = 0;

	time_t rawTime = mktime(&NewTime);
	

	return rawTime;
}

