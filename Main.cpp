#include <wx/wx.h>
#include <memory>
#include <wx/grid.h>

class MyFrame;

class MyApp : public wxApp
{
public:
	virtual bool OnInit() override;

private:
	MyFrame* frame;
};

wxIMPLEMENT_APP(MyApp); 

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello( wxCommandEvent& event);
	void OnExit( wxCommandEvent& event);
	void OnAbout( wxCommandEvent& event);

private:
	wxMenu* menuFile;
	wxMenu* menuHelp;
	wxMenuBar* menuBar;

};

enum
{
	ID_Hello =1
};



bool MyApp::OnInit()
{
	frame = new MyFrame("Schedule", wxPoint(512,200), wxSize(1024, 512));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(nullptr, wxID_ANY, title, pos, size, wxNO_BORDER)
{
	menuFile= new wxMenu();
	menuFile->Append(ID_Hello, "&Hello...\tCtrl+H","Help string shown in status bar for this menu item");
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

	Bind( wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
	Bind( wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
	Bind( wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	
	wxGrid* grid = new wxGrid(this,-1,wxPoint(0,0),wxSize(400,300));

	



	grid->SetDefaultRowSize(60, true);
	grid->SetDefaultColSize(120, true);
	grid->CreateGrid(5,7);

	grid->SetCellValue(0,3,"This is read-only");
	grid->SetReadOnly(0,3);

	grid->SetCellValue(3,3, "green on grey");
	grid->SetCellTextColour(3,3,*wxGREEN);
	grid->SetCellBackgroundColour(3,3,*wxLIGHT_GREY);

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

	//Bind( wxEVT_MENU, [=](wxCommandEvent&) {wxLogMessage("Hellow World from lambda!");}, ID_Hello);
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
