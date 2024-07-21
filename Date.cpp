#include "Date.h"
#include "MyDefs.h"

Calendar::Calendar(wxWindow* parent, wxWindowID id, const wxPoint& point, const wxSize& size, long style, const wxString& name)
	: wxGrid(parent, id, point, size, style, name)
{
	OnInit();

}

Calendar::~Calendar()
{
	if (timer != nullptr && timer->IsRunning() == true)
	{		
		timer->Stop();
	}
}

void Calendar::OnInit()
{

	SetDefaultCellFitMode(wxGridFitMode::Clip());


	timer = new wxTimer(this, wxID_ANY);
	Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(Calendar::OnTimer));
	timer->Start(0);
	
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

	selectedYear = wxDateTime::GetCurrentYear();
	selectedMonth = wxDateTime::GetCurrentMonth();

	wxDateTime::Tm firstDayOfMonth;

	firstDayOfMonth.year = selectedYear;
	firstDayOfMonth.mon = selectedMonth;
	firstDayOfMonth.mday = 1;

	firstDayOfMonth.AddDays(-1);
	

	dateTime.SetToLastMonthDay(selectedMonth, selectedYear);

	

	//int w, h;

	//GetSize(&w, &h);
	//GetClientSize(&w,&h);
	//GetParent()->GetClientSize(&w, &h);

	//int colSize = w/8;
	//int rowSize = h/6;

	//SetDefaultRowSize(rowSize, true);
	//SetDefaultColSize(colSize, true);

	CreateGrid(6, 8);

	SetCellValue(0, 3, "This is read-only");
	SetReadOnly(0, 3);

	SetCellValue(3, 3, "green on grey");
	SetCellTextColour(3, 3, *wxGREEN);
	SetCellBackgroundColour(3, 3, *wxLIGHT_GREY);

	SetColLabelValue(0, "Mon");
	SetColLabelValue(1, "Tue");
	SetColLabelValue(2, "Wed");
	SetColLabelValue(3, "Thu");
	SetColLabelValue(4, "Fri");
	SetColLabelValue(5, "Sat");
	SetColLabelValue(6, "Sun");

	SetCellFitMode(0,0,wxGridFitMode::Clip());
	SetCellValue(0, 0, "clip test clip test  clip test  clip test  clip test  clip test  clip test  clip test ");

	SelectBlock(wxGridCellCoords(1,1), wxGridCellCoords(1,1), false);

	HideRowLabels();
	HideColLabels();


}

void Calendar::OnTimer(wxTimerEvent& event)
{
	
}

time_t Calendar::MakeTime(int year, int month, int day)
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
