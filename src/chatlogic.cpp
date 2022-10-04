#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <tuple>
#include <algorithm>

#include "graphedge.h"
#include "graphnode.h"
#include "chatbot.h"
#include "chatlogic.h"

ChatLogic::ChatLogic()
{
    //// STUDENT CODE
    ////

    // create instance of chatbot
   

  
/*  ChatBot * tripleBot;
  tripleBot =std::move(_chatBot);
  
    std::cout << "count: " << tripleBot->_count << std::endl`*/
    // add pointer to chatlogic so that chatbot answers can be passed on to the GUI
   std::cout << "ChatBot still alive 0?  " << std::endl;
    ////
   _chatBot.SetChatLogicHandle(this);

    //// EOF STUDENT CODE
}

ChatLogic::~ChatLogic()
{
    //// STUDENT CODE
    ////

    // the owned smartpointers are deleted automatically,
    // the other pointers are not owned

    ////
    //// EOF STUDENT CODE
}

template <typename T>
void ChatLogic::AddAllTokensToElement(std::string tokenID, tokenlist &tokens, T &element)
{

    // find all occurences for current node
    auto token = tokens.begin();
    while (true)
    {
        token = std::find_if(token, tokens.end(), [&tokenID](const std::pair<std::string, std::string> &pair)
                             { return pair.first == tokenID;; });
        if (token != tokens.end())
        {
            element.AddToken(token->second); // add new keyword to edge
            token++;                         // increment iterator to next element
        }
        else
        {
            break; // quit infinite while-loop
        }
    }
}

void ChatLogic::LoadAnswerGraphFromFile(std::string filename)
{
std::cout << "LoadAnswerGraphFromFile : _chatbot at " << &this->_chatBot << std::endl;
    // load file with answer graph elements
    std::ifstream file(filename);

    // check for file availability and process it line by line
    if (file)
    {
        // loop over all lines in the file
        std::string lineStr;
        while (getline(file, lineStr))
        {
            // extract all tokens from current line
            tokenlist tokens;
            while (lineStr.size() > 0)
            {
                // extract next token
                int posTokenFront = lineStr.find("<");
                int posTokenBack = lineStr.find(">");
                if (posTokenFront < 0 || posTokenBack < 0)
                    break; // quit loop if no complete token has been found
                std::string tokenStr = lineStr.substr(posTokenFront + 1, posTokenBack - 1);

                // extract token type and info
                int posTokenInfo = tokenStr.find(":");
                if (posTokenInfo != std::string::npos)
                {
                    std::string tokenType = tokenStr.substr(0, posTokenInfo);
                    std::string tokenInfo = tokenStr.substr(posTokenInfo + 1, tokenStr.size() - 1);

                    // add token to vector
                    tokens.push_back(std::make_pair(tokenType, tokenInfo));
                }

                // remove token from current line
                lineStr = lineStr.substr(posTokenBack + 1, lineStr.size());
            }

            // process tokens for current line
            auto type = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair)
                                     { return pair.first == "TYPE"; });
            if (type != tokens.end())
            {
                // check for id
                auto idToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair)
                                            { return pair.first == "ID"; });
                if (idToken != tokens.end())
                {

                    // extract id from token
                    int id = std::stoi(idToken->second);
                    std::vector<GraphNode *> _rawNodes{}; // SCS 26.09 task 3: exclusive ownership
                    for (int k = 0; k < _nodes.size(); k++)
                    { // SCS 26.09 task 3: exclusive ownership
                        GraphNode *actualNode = *_nodes[k].get();
                        _rawNodes.emplace_back(actualNode); // SCS 26.09 task 3: exclusive ownership
                    }

                    // node-based processing
                    if (type->second == "NODE")
                    {
                        //// STUDENT CODE
                        ////
                        // SCS 26.09 task 3: exclusive ownership
                        // check if node with this ID exists already
                        auto newNode = std::find_if(_rawNodes.begin(), _rawNodes.end(), [&id](GraphNode *node)
                                                    { return node->GetID() == id; }); // SCS 26.09 task 3: exclusive ownership

                        if (newNode == _rawNodes.end())
                            // create new element if ID does not yet exist
                            if (newNode == _rawNodes.end()) // SCS 26.09 task 3: exclusive ownership
                            {

                                _nodes.emplace_back(std::make_unique<GraphNode *>(new GraphNode(id))); // SCS 26.09 task 3: exclusive ownership
                                auto newNodeRawPtr = *(_nodes.end() - 1)->get();                       // SCS 26.09 task 3: exclusive ownership // get iterator from last element

                                // add all answers to current node
                                AddAllTokensToElement("ANSWER", tokens, *newNodeRawPtr); // SCS 26.09 task 3: exclusive ownership
                            }

                        ////
                        //// EOF STUDENT CODE
                    }

                    // edge-based processing
                    if (type->second == "EDGE")
                    {
                        //// STUDENT CODE
                        ////

                        // find tokens for incoming (parent) and outgoing (child) node
                        auto parentToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair)
                                                        { return pair.first == "PARENT"; });
                        auto childToken = std::find_if(tokens.begin(), tokens.end(), [](const std::pair<std::string, std::string> &pair)
                                                       { return pair.first == "CHILD"; });

                        if (parentToken != tokens.end() && childToken != tokens.end())
                        {
                            // get iterator on incoming and outgoing node via ID search
                            auto parentNode = std::find_if(_rawNodes.begin(), _rawNodes.end(), [&parentToken](auto node)
                                                           { return node->GetID() == std::stoi(parentToken->second); }); // SCS 26.09 task 3: exclusive ownership
                            auto childNode = std::find_if(_rawNodes.begin(), _rawNodes.end(), [&childToken](auto node)
                                                          { return node->GetID() == std::stoi(childToken->second); }); // SCS 26.09 task 3: exclusive ownership

                            // create new edge
                            GraphEdge *edge = new GraphEdge(id);
                            edge->SetChildNode(*childNode);
                            edge->SetParentNode(*parentNode);

                            // find all keywords for current node
                            AddAllTokensToElement("KEYWORD", tokens, *edge);
                            std::unique_ptr<GraphEdge *> edge_unique = std::make_unique<GraphEdge *>(edge);
                            std::unique_ptr<GraphEdge *> childNodeEdge_unique = std::make_unique<GraphEdge *>(edge);
                            std::unique_ptr<GraphEdge *> parentNodeEdge_unique = std::make_unique<GraphEdge *>(edge);

                            _edges.push_back(std::move(edge_unique));
                            int s = _edges.size();
 // std::cout << "_edges_push_back s " << s << std::endl;
                            // store reference in child node and parent node
                            (*childNode)->AddEdgeToParentNode(std::move(parentNodeEdge_unique));
                          // std::cout << "child node id: " <<  (*childNode)->GetID() << std::endl;
                            (*parentNode)->AddEdgeToChildNode(std::move(childNodeEdge_unique));
                          //  std::cout << "parent node id: " <<  (*parentNode)->GetID()<< std::endl;
                        }

                        ////
                        //// EOF STUDENT CODE
                    }
                }
                else
                {
                    std::cout << "Error: ID missing. Line is ignored!" << std::endl;
                }
            }
        } // eof loop over all lines in the file

        file.close();

    } // eof check for file availability
    else
    {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }

    //// STUDENT CODE
    ////

    // identify root node
    GraphNode *rootNode = nullptr;
    for (auto it = std::begin(_nodes); it != std::end(_nodes); ++it)
    {
        // search for nodes which have no incoming edges
        GraphNode *myTest = *it->get();
        if (myTest->GetNumberOfParents() == 0)
        {

            if (rootNode == nullptr)
            {
                rootNode = *it->get(); // SCS 26.09 task 3: exclusive ownership // assign current node to root
            }
            else
            {
                std::cout << "ERROR : Multiple root nodes detected" << std::endl;
            }
        }
    }

    // add chatbot to graph root node
    _chatBot.SetRootNode(rootNode);
    std::cout << "rootNode node id: " <<  rootNode->GetID()<< std::endl;
    // ChatBot* hChatbot (std::move(_chatBot));
    //std::shared_ptr<ChatBot > hikingChatbot = std::make_shared<ChatBot >(std::move(doubleBot)); // Call of the ChatBot move constructor
   rootNode->MoveChatbotHere(std::move(_chatBot));
   _currentNode = rootNode;
   std::cout << "MoveChatBotHere rootNode->_chatBot._currentNode._id: " << rootNode->GetChatBotCurrentNode() << std::endl;

    ////
    //// EOF STUDENT CODE
}

void ChatLogic::SetPanelDialogHandle(ChatBotPanelDialog *panelDialog)
{
    _panelDialog = panelDialog;
}

void ChatLogic::SetChatbotHandle(ChatBot chatbot)
{
  std::cout << "Set Chatbot Handle" << std::endl;
   _chatBot = chatbot;
}

void ChatLogic::SendMessageToChatbot(std::string message)
{
   std::cout << "Send Message To ChatBot, message: " << message << std::endl;
  //std::cout << "Send Message To ChatBot, chatBotHanlde: " <<  _currentNode->GetNodesChatBotHandle() << std::endl;
   _currentNode->GetNodesChatBotHandle().ReceiveMessageFromUser(message);
}

void ChatLogic::SendMessageToUser(std::string message)
{
  std::cout << "Send Message To User" << std::endl;
    _panelDialog->PrintChatbotResponse(message);
}

wxBitmap *ChatLogic::GetImageFromChatbot()
{
    std::cout << "Get Image Handle" << std::endl;
   return _chatBot.GetImageHandle();
 
}
