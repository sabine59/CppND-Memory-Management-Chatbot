#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);
    
    ChatBot(const ChatBot &source);     // SCS 24.09. rule of five -  copy constructor, no copy allowed, because _chatLogic will be constructed recursively
    ChatBot &operator=(const ChatBot &source) ;   // SCS 24.09. rule of five -  copy assignment operator, no copy allowed,  because _chatLogic will be constructed recursively

   

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();                    // destructor
    

    //// STUDENT CODE
    ////
   ChatBot(ChatBot &&source);      // SCS 24.09. rule of five -  move constructor
   ChatBot &operator=(ChatBot &&source) { // SCS 24.09. rule of five -  move assignement operator
  
       std::cout << "ChatBot move assignement operator - ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
     
      if (_image != NULL)
       	delete _image;
      _image = std::move(source._image);
      source._image = NULL;
     
      _chatLogic = std::move(source._chatLogic);
      source._chatLogic = nullptr;
  
      _rootNode = std::move(source._rootNode);
      source._rootNode = nullptr;
      return *this;
    }


    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */
