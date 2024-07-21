#pragma once

#include <time.h>
#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <wx/datetime.h>

class wxTimer;

class Calendar : public wxGrid
{
public: 
	Calendar(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxWANTS_CHARS,
        const wxString& name = wxASCII_STR(wxGridNameStr));

	virtual ~Calendar() override; 

	void OnInit();
    void OnTimer(wxTimerEvent& event);

    time_t MakeTime(int year, int month, int day);


private:
	wxTimer* timer;
    // selected info
    int selectedYear;
    wxDateTime::Month selectedMonth;
    int selectedDay;
    wxDateTime dateTime;

    
};