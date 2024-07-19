#include "Date.h"

Calendar::Calendar(wxWindow* parent, wxWindowID id, const wxPoint& point, const wxSize& size, long style, const wxString& name)
	: wxGrid(parent, id, point, size, style, name)
{
	OnInit();
}

Calendar::~Calendar()
{
}

void Calendar::OnInit()
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

	selectedYear = wxDateTime::GetCurrentYear();
	selectedMonth = wxDateTime::GetCurrentMonth();

	wxDateTime::Tm firstDayOfMonth;

	firstDayOfMonth.year = selectedYear;
	firstDayOfMonth.mon = selectedMonth;
	firstDayOfMonth.mday = 1;

	firstDayOfMonth.AddDays(-1);
	

	dateTime.SetToLastMonthDay(selectedMonth, selectedYear);
	

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
