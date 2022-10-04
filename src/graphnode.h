#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>   //SCS 28.09. task 4
#include "chatbot.h"


// forward declarations
class GraphEdge;

class GraphNode
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    std::vector<std::unique_ptr <GraphEdge *>> _childEdges;  // SCS 28.09. Task 4: moving smartpinters - edges to subsequent nodes

    // data handles (not owned)
    std::vector<std::shared_ptr <GraphEdge *>> _parentEdges; // SCS 28.09. Task 4: moving smartpinters - edges to preceding nodes 
    ChatBot  _chatBot; // SCS 28.09. Task 5 

    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    std::vector<std::string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return _id; }
    int GetNumberOfChildEdges() { return _childEdges.size(); }
    GraphEdge *GetChildEdgeAtIndex(int index);
    std::vector<std::string> GetAnswers() { return _answers; }
    int GetNumberOfParents() { return _parentEdges.size(); }
    int GetChatBotCurrentNode() { return _chatBot.GetCurrentNode()->GetID(); } // SCS - only for debugging
    ChatBot& GetNodesChatBotHandle() { return _chatBot; } 

    // proprietary functions
    void AddToken(std::string token); // add answers to list
    void AddEdgeToParentNode(std::unique_ptr <GraphEdge *> edge);
    void AddEdgeToChildNode(std::unique_ptr <GraphEdge *> edge);

    //// STUDENT CODE
    ////

    void MoveChatbotHere(ChatBot chatbot);

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(GraphNode *newNode);
};

#endif /* GRAPHNODE_H_ */