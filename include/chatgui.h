#ifndef CHATGUI_H_
#define CHATGUI_H_

#include <wx/wx.h>
#include<memory>
#include<mutex>
#include<string>
#include "socketserver.h"
#include "socketclient.h"




class ChatLogic; // forward declaration
class socketServer; // forward declaration
class socketClient; // forward declaration

// middle part of the window containing the dialog between user and NetworkChat
class NetworkChatPanelDialog : public wxScrolledWindow
{
private:
    // control elements
    wxBoxSizer *_dialogSizer;
    wxBitmap _image;

public:
    // constructor / destructor
    NetworkChatPanelDialog(wxWindow *parent, wxWindowID id);
    ~NetworkChatPanelDialog();

    
    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    // proprietary functions
    void AddDialogItem(wxString text, bool isFromUser = true,bool isInformation=false);
    void PrintNetworkChatResponse(std::string response);

    DECLARE_EVENT_TABLE()
};

// dialog item shown in NetworkChatPanelDialog
class NetworkChatPanelDialogItem : public wxPanel
{
private:
    // control elements
    wxStaticBitmap *_NetworkChatImg;
    wxStaticText *_NetworkChatTxt;

public:
    // constructor / destructor
    NetworkChatPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser,bool isInformation);
};

// frame containing all control elements
class NetworkChatFrame : public wxFrame
{
private:
    // control elements
    
    wxTextCtrl *_userTextCtrl;
    wxMenuBar *m_pMenuBar;
    wxMenu *m_pFileMenu;
    std::shared_ptr<socketServer> socket;
    std::shared_ptr<socketClient> socketclient;
    
    void OnQuit(wxCommandEvent& WXUNUSED(event));
    void OnConnect(wxCommandEvent& WXUNUSED(event));
    void OnListen(wxCommandEvent& WXUNUSED(event));
    // events
    void OnEnter(wxCommandEvent &WXUNUSED(event));
    void startServer();
    

    //flags for sockets
    bool isListening;
    bool isConected;

public:
    std::mutex _mutex;

    void startClient();
    std::string ipserver;
    NetworkChatPanelDialog *_panelDialog;
    // constructor / desctructor
    
    NetworkChatFrame(const wxString &title);
};

// control panel for background image display
class NetworkChatFrameImagePanel : public wxPanel
{
    // control elements
    wxBitmap _image;

public:
    // constructor / desctructor
    NetworkChatFrameImagePanel(wxFrame *parent);

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    DECLARE_EVENT_TABLE()
};
class ipbox : public wxDialog
{
wxTextCtrl *tc;
wxButton *okButton;
std::string ip;
NetworkChatFrame* _networkChatFrame;

public:
  ipbox(const wxString& title,NetworkChatFrame* networkChatFrame);
  void buttoncliked(wxCommandEvent& WXUNUSED(event));

};


// wxWidgets app that hides main()
class NetworkChatApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};

#endif /* CHATGUI_H_ */
