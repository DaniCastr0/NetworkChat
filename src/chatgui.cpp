#include <wx/filename.h>
#include <wx/colour.h>
#include <wx/image.h>
#include <string>
#include<iostream>
#include<thread>

using namespace std;

#include "chatgui.h"


// size of NetworkChat window
const int width = 414;
const int height = 736;

// wxWidgets APP
IMPLEMENT_APP(NetworkChatApp);


std::string imgBasePath = "../images/";

bool NetworkChatApp::OnInit()
{
    // create window with name and show it
    NetworkChatFrame *networkChatFrame = new NetworkChatFrame(wxT("NetworkChat C++"));
    networkChatFrame->Show(true);

    return true;
}

// wxWidgets FRAME
NetworkChatFrame::NetworkChatFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    socket=std::make_shared<socketServer>();
    socketclient=std::make_shared<socketClient>();
    isConected=false;
    
    // create panel with background image
    NetworkChatFrameImagePanel *ctrlPanel = new NetworkChatFrameImagePanel(this);

    ipserver="";

    // create controls and assign them to control panel
    _panelDialog = new NetworkChatPanelDialog(ctrlPanel, wxID_ANY);

    // create text control for user input
    int idTextXtrl = 1;
    _userTextCtrl = new wxTextCtrl(ctrlPanel, idTextXtrl, "", wxDefaultPosition, wxSize(width, 50), wxTE_PROCESS_ENTER, wxDefaultValidator, wxTextCtrlNameStr);
    Connect(idTextXtrl, wxEVT_TEXT_ENTER, wxCommandEventHandler(NetworkChatFrame::OnEnter));

    // create vertical sizer for panel alignment and add panels
    wxBoxSizer *vertBoxSizer = new wxBoxSizer(wxVERTICAL);
    vertBoxSizer->AddSpacer(90);
    vertBoxSizer->Add(_panelDialog, 6, wxEXPAND | wxALL, 0);
    vertBoxSizer->Add(_userTextCtrl, 1, wxEXPAND | wxALL, 5);
    ctrlPanel->SetSizer(vertBoxSizer);

    m_pMenuBar = new wxMenuBar();
    // File Menu
    m_pFileMenu = new wxMenu();
    m_pFileMenu->Append(wxID_EXECUTE, _T("&Listen"));
    m_pFileMenu->Append(wxID_ADD, _T("&Connect"));
    m_pFileMenu->Append(wxID_EXIT, _T("&Quit "));
    m_pMenuBar->Append(m_pFileMenu, _T("&File"));
    // About menu
    
    SetMenuBar(m_pMenuBar);

    Connect(wxID_EXECUTE, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(NetworkChatFrame::OnListen));
    Connect(wxID_ADD, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(NetworkChatFrame::OnConnect));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
      wxCommandEventHandler(NetworkChatFrame::OnQuit));

    isListening=false;

    // position window in screen center
    this->Centre();
}

void NetworkChatFrame::OnEnter(wxCommandEvent &WXUNUSED(event))
{
    // retrieve text from text control
    wxString userText = _userTextCtrl->GetLineText(0);

    char msg[1024];
    strncpy(msg, (const char*)userText.mb_str(wxConvUTF8), 1023);
    // add new user text to dialog
    
    _mutex.lock();
    _panelDialog->AddDialogItem(userText, true,false);
    _mutex.unlock();

    if (isConected==true){
        socketclient->sending(msg);
    }
    if (isListening==true){
        socket->sending(msg);
    }

    // delete text in text control
    _userTextCtrl->Clear();

   
}

BEGIN_EVENT_TABLE(NetworkChatFrameImagePanel, wxPanel)
EVT_PAINT(NetworkChatFrameImagePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

NetworkChatFrameImagePanel::NetworkChatFrameImagePanel(wxFrame *parent) : wxPanel(parent)
{
}

void NetworkChatFrameImagePanel::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void NetworkChatFrameImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void NetworkChatFrameImagePanel::render(wxDC &dc)
{
    // load backgroud image from file
    wxString imgFile = imgBasePath + "gijon.jpg";
    wxImage image;
    image.LoadFile(imgFile);

    // rescale image to fit window dimensions
    wxSize sz = this->GetSize();
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);
    _image = wxBitmap(imgSmall);
    
    dc.DrawBitmap(_image, 0, 0, false);
}

BEGIN_EVENT_TABLE(NetworkChatPanelDialog, wxPanel)
EVT_PAINT(NetworkChatPanelDialog::paintEvent) // catch paint events
END_EVENT_TABLE()

NetworkChatPanelDialog::NetworkChatPanelDialog(wxWindow *parent, wxWindowID id)
    : wxScrolledWindow(parent, id)
{
    // sizer will take care of determining the needed scroll size
    _dialogSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(_dialogSizer);

    // allow for PNG images to be handled
    wxInitAllImageHandlers();

}

NetworkChatPanelDialog::~NetworkChatPanelDialog()
{
    
}
void NetworkChatPanelDialog::AddDialogItem(wxString text, bool isFromUser,bool isInformation)
{
    // add a single dialog element to the sizer
    NetworkChatPanelDialogItem *item = new NetworkChatPanelDialogItem(this, text, isFromUser,isInformation);
    if (isInformation==false)
    {
        if (isFromUser==true)
        {
            _dialogSizer->Add(item, 0, wxALL | wxALIGN_LEFT , 8);
        }
        else
        {
            _dialogSizer->Add(item, 0, wxALL | wxALIGN_RIGHT, 8);
        }
        
    }
    else
    {
        _dialogSizer->Add(item, 0, wxALL | wxALIGN_CENTER, 8);
        
    }
    _dialogSizer->Layout();
    // make scrollbar show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
    this->Layout();

    // scroll to bottom to show newest element
    int dx, dy;
    this->GetScrollPixelsPerUnit(&dx, &dy);
    int sy = dy * this->GetScrollLines(wxVERTICAL);
    this->DoScroll(0, sy);
}

void NetworkChatPanelDialog::PrintNetworkChatResponse(std::string response)
{
    // convert string into wxString and add dialog element
    
}

void NetworkChatPanelDialog::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void NetworkChatPanelDialog::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void NetworkChatPanelDialog::render(wxDC &dc)
{
    wxImage image;
    image.LoadFile(imgBasePath + "gijonin.jpg");

    wxSize sz = this->GetSize();
    wxImage imgSmall = image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);

    _image = wxBitmap(imgSmall);
    dc.DrawBitmap(_image, 0, 0, false);
}

NetworkChatPanelDialogItem::NetworkChatPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser,bool isInformation)
    : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_NONE)
{
    // retrieve image from NetworkChat
    wxBitmap *bitmap = nullptr; 

    // create image and text
    if(isInformation==false)
    {
        _NetworkChatImg = new wxStaticBitmap(this, wxID_ANY, (isFromUser ? wxBitmap(imgBasePath + "user.png", wxBITMAP_TYPE_PNG) : wxBitmap(imgBasePath + "user.png", wxBITMAP_TYPE_PNG)), wxPoint(-1, -1), wxSize(-1, -1));
        _NetworkChatTxt = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(150, -1), wxALIGN_CENTRE | wxBORDER_NONE);
        _NetworkChatTxt->SetForegroundColour(isFromUser == true ? wxColor(*wxBLACK) : wxColor(*wxWHITE));
    }
    else
    {
        _NetworkChatTxt = new wxStaticText(this, wxID_ANY, text, wxPoint(-1, -1), wxSize(150, -1), wxALIGN_CENTRE | wxBORDER_NONE);
        _NetworkChatTxt->SetForegroundColour(wxColor(*wxBLACK));
    }
    
    // create sizer and add elements
    wxBoxSizer *horzBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    horzBoxSizer->Add(_NetworkChatTxt, 8, wxEXPAND | wxALL, 1);
    if (isInformation==false){
        horzBoxSizer->Add(_NetworkChatImg, 2, wxEXPAND | wxALL, 1);
    }
    this->SetSizer(horzBoxSizer);

    // wrap text after 150 pixels
    _NetworkChatTxt->Wrap(150);

    // set background color
    if(isInformation==false)
    {
        this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
    }
    else
    {
        this->SetBackgroundColour(wxT("WHITE")); 
    }
    
}
ipbox::ipbox(const wxString & title,NetworkChatFrame* networkChatFrame)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(300, 130))
{

  _networkChatFrame=networkChatFrame;
  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  

  
  tc = new wxTextCtrl(panel, -1, wxT("insert server IP"), 
      wxPoint(30, 20),wxSize(220, 30));

  okButton = new wxButton(this, -1, wxT("Ok"), 
      wxDefaultPosition, wxSize(70, 30));
  
  okButton->Bind(wxEVT_BUTTON,&ipbox::buttoncliked,this);

  hbox->Add(okButton, 1);
  

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  SetSizer(vbox);

  Centre();
  ShowModal();

  Destroy(); 
}

void NetworkChatFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}
void NetworkChatFrame::OnListen(wxCommandEvent& WXUNUSED(event))
{
  startServer();
  
}
  

void NetworkChatFrame::OnConnect(wxCommandEvent& WXUNUSED(event))
{
  ipbox *box = new ipbox(wxT("Server Ip"),this);
  box->Show(true);

    
}
void NetworkChatFrame::startServer()
{
    
    if (isListening==false)
    {
        
        socket->attachPort();
        socket->receiving();
        std::thread t=std::thread(&socketServer::accepting,socket,this);
        t.detach();
        isListening=true;
    }
    else
    {
         string a="The chat is already listening petitions";
         wxString botText(a.c_str(), wxConvUTF8);
        _panelDialog->AddDialogItem(botText, false,true);
    }
}
void NetworkChatFrame::startClient()
{
    socketclient->ipbin(this->ipserver);
    socketclient->connecting();
    isConected=true;
    std::thread t=std::thread(&socketClient::receiving,socketclient,this);
    t.detach();
    
    
}
void ipbox::buttoncliked(wxCommandEvent& WXUNUSED(event))
{
    ip=tc->GetLineText(0);
    _networkChatFrame->ipserver=ip;
    _networkChatFrame->startClient();
    Close(true);
}
