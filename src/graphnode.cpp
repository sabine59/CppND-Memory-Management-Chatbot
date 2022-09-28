#include "graphedge.h"
#include "graphnode.h"

#include<iostream> // SCS debug

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

   std::cout << "GraphNode destructor is called " <<std::endl; // SCS debug
   if (_chatBot != nullptr) {  // SCS 22.09.
         //std::cout << "GraphNode destructor is called: " << _chatBot<< " " << std::endl; // SCS debug


     delete _chatBot; 
     _chatBot = nullptr;
    } else {

         //std::cout << "GraphNode destructor is called: _chatBot = nullptr " << std::endl; // SCS debug
    }

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(std::shared_ptr<GraphEdge *>edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::shared_ptr<GraphEdge *>edge)
{
    GraphEdge *childRawPointer = *edge.get();
    _childEdges.push_back(std::make_unique <GraphEdge*> (childRawPointer));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot * chatbot)
{
    this->_chatBot = chatbot;

         std::cout << "MoveChatBotHere: " << _chatBot<< " " << std::endl; // SCS debug
    this->_chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{

         std::cout << "MoveChatBotToNewNode: " << newNode->_chatBot << " " << std::endl; // SCS debug
    newNode->MoveChatbotHere(_chatBot);

    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    
	GraphEdge * returnValue = *_childEdges[index].get();
    return returnValue;

    ////
    //// EOF STUDENT CODE
}