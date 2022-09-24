#ifndef CHATGUI_H_
#define CHATGUI_H_

#include <wx/wx.h>
#include <memory>  // SCS 24.09 - implementing unique_ptr

class ChatLogic; // forward declaration

// middle part of the window containing the dialog between user and chatbot
class ChatBotPanelDialog : public wxScrolledWindow
{
private:
    // control elements
    wxBoxSizer *_dialogSizer;
    wxBitmap _image;

    //// STUDENT CODE
    ////

    std::unique_ptr<ChatLogic> _chatLogic;  // SCS 24.09. - implementing unique_ptr

    ////
    //// EOF STUDENT CODE

public:
    // constructor / destructor
    ChatBotPanelDialog(wxWindow *parent, wxWindowID id);
    ~ChatBotPanelDialog();

    // getter / setter
    ChatLogic *GetChatLogicHandle() { 
    
       std::cout << "ChatBotPanelDialog: GetChatLogicHandle: " << _chatLogic.get() << std::endl; // SCS debug
       return _chatLogic.get(); } // SCS 24.09. - implementing unique_ptr

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    // proprietary functions
    void AddDialogItem(wxString text, bool isFromUser = true);
    void PrintChatbotResponse(std::string response);

    DECLARE_EVENT_TABLE()
};

// dialog item shown in ChatBotPanelDialog
class ChatBotPanelDialogItem : public wxPanel
{
private:
    // control elements
    wxStaticBitmap *_chatBotImg = NULL; // SCS 22.09. - initialized with NULL
    wxStaticText *_chatBotTxt = NULL; // SCS 22.09.

public:
    // constructor / destructor
    ChatBotPanelDialogItem(wxPanel *parent, wxString text, bool isFromUser);
    ~ChatBotPanelDialogItem(); // SCS 22.09.
};

// frame containing all control elements
class ChatBotFrame : public wxFrame
{
private:
    // control elements
    ChatBotPanelDialog *_panelDialog;
    wxTextCtrl *_userTextCtrl;

    // events
    void OnEnter(wxCommandEvent &WXUNUSED(event));

public:
    // constructor / desctructor
    ChatBotFrame(const wxString &title);
    ~ChatBotFrame(); // SCS 22.09.
};

// control panel for background image display
class ChatBotFrameImagePanel : public wxPanel
{
    // control elements
    wxBitmap _image; // SCS 22.09.

public:
    // constructor / desctructor
    ChatBotFrameImagePanel(wxFrame *parent);
    ~ChatBotFrameImagePanel(); // SCS 22.09.

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    DECLARE_EVENT_TABLE()
};

// wxWidgets app that hides main()
class ChatBotApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};

#endif /* CHATGUI_H_ */