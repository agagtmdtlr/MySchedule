#include "MyFrame.h"
#include <wx/grid.h>
#include <time.h>
#include "Date.h"
#include "MyDefs.h"




MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	//: wxFrame(nullptr, wxID_ANY, title, pos, size, wxNO_BORDER) // 
	: wxFrame(nullptr, wxID_Root, title, pos, size)

{
	menuFile = new wxMenu();
	menuFile->Append(wxID_Hello, "&Hello...\tCtrl+H", "Help string shown in status bar for this menu item");
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

	Bind(wxEVT_MENU, &MyFrame::OnHello, this, wxID_Hello);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	calendar = new Calendar(this, -1, wxPoint(0, 0), GetSize());
	
	boxSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(boxSizer);
	boxSizer->Add(calendar,1, wxEXPAND);
	Connect(wxEVT_SIZE, wxID_ANY, wxSizeEventHandler(MyFrame::OnSize) );
	boxSizer->Fit(this);


}

MyFrame::~MyFrame()
{
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

void MyFrame::OnSize(wxSizeEvent& event)
{
	boxSizer->Fit(this);
	
	wxSizerItem* item = boxSizer->GetItem(0);

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

