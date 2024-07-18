#include <wx/wx.h>
#include <memory>
#include <wx/grid.h>

#include "MyFrame.h"

class MyFrame;

class MyApp : public wxApp
{
public:
	virtual bool OnInit() override;
private:
	MyFrame* frame;
};

wxIMPLEMENT_APP(MyApp); 

bool MyApp::OnInit()
{
	frame = new MyFrame("Schedule", wxPoint(512,200), wxSize(1024, 512));
	frame->Show(true);
	return true;
}

