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

// middle part of the window containing the dialog between user and chatbot
class ChatBotPanelDialog : public wxScrolledWindow
{
private:
    // control elements
    wxBoxSizer *_dialogSizer;
    wxBitmap _image;

public:
    // constructor / destructor
    ChatBotPanelDialog(wxWindow *parent, wxWindowID id);
    ~ChatBotPanelDialog();

    
    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    // proprietary functions
    void AddDialogItem(wxString text, bool isFromUser = true,bool isInformation=false);
    void PrintChatbotResponse(std::string response);

    DECLARE_EVENT_TABLE()
};

// dialog item shown in ChatBotPanelDialog
class ChatBotPanelDialogItem : public wxPanel
{
private:
    // control elements
    wxStaticBitmap *_chatBotImg;
    wxStaticText *_chatBotTxt;

public:
    // constructor / destructor
    ChatBotPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser,bool isInformation);
};

// frame containing all control elements
class ChatBotFrame : public wxFrame
{
private:
    // control elements
    
    wxTextCtrl *_userTextCtrl;
    wxMenuBar *m_pMenuBar;
    wxMenu *m_pFileMenu;
    socketServer *socket;
    socketClient *socketclient;
    bool isConected;
    void OnQuit(wxCommandEvent& WXUNUSED(event));
    void OnConnect(wxCommandEvent& WXUNUSED(event));
    void OnListen(wxCommandEvent& WXUNUSED(event));
    // events
    void OnEnter(wxCommandEvent &WXUNUSED(event));
    void startServer();
    
    std::mutex t;
    //sockets
    bool isListening;

public:
    void startClient();
    std::string ipserver;
    ChatBotPanelDialog *_panelDialog;
    // constructor / desctructor
    
    ChatBotFrame(const wxString &title);
};

// control panel for background image display
class ChatBotFrameImagePanel : public wxPanel
{
    // control elements
    wxBitmap _image;

public:
    // constructor / desctructor
    ChatBotFrameImagePanel(wxFrame *parent);

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
ChatBotFrame* _chatBotFrame;

public:
  ipbox(const wxString& title,ChatBotFrame* chatBotFrame);
  void buttoncliked(wxCommandEvent& WXUNUSED(event));

};


// wxWidgets app that hides main()
class ChatBotApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};

#endif /* CHATGUI_H_ */
