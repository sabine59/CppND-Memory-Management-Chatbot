#include "graphedge.h"
#include "graphnode.h"

#include<iostream> // SCS debug

GraphNode::GraphNode(int id) { _id = id; }

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////
   

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
   _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(std::unique_ptr <GraphEdge *> edge)
{
   std::shared_ptr <GraphEdge *> parentNodeEdge = std::move(edge);
   _parentEdges.push_back(parentNodeEdge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr <GraphEdge *> edge)
{
   _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(std::shared_ptr <ChatBot *>  chatbot)
{
   
    this->_chatBot = chatbot;
    (*chatbot)->SetCurrentNode(this);  
    

}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{

    newNode->MoveChatbotHere(_chatBot);

    _chatBot = std::move(nullptr); // call move assignement operator to invalidate _chatbot after movement
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