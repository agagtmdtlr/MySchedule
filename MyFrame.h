#pragma once
#include <wx/wx.h>

class wxGrid;
class wxGauge;
class wxTimer;

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnTimer(wxTimerEvent& event);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);


	virtual void Refresh(bool eraseBackground = true, const wxRect* rect = (const wxRect*)NULL) override;

	virtual void Update() override;


	time_t MakeTime(int year, int month, int day);

private:
	wxMenu* menuFile;
	wxMenu* menuHelp;
	wxMenuBar* menuBar;

	wxGrid* grid;

	wxTimer* timer;


};