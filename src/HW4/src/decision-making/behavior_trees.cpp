#include "../../include/decision-making/behavior_trees.hpp"

Status Selector::run(DecisionContext context)
{
    for (const auto& child : m_children)
    {
        auto childStatus = child->run(context);
        if (childStatus == SUCCESS || childStatus == RUNNING)
        {
            return childStatus;
        }
    }
    return FAIL;
}

Status Sequence::run(DecisionContext context)
{
    for (const auto& child : m_children)
    {
        auto childStatus = child->run(context);
        if (childStatus == FAIL || childStatus == RUNNING)
        {
            return childStatus;
        }
    }
    return SUCCESS;

}

Status Inverter::run(DecisionContext context)
{
    switch(m_child->run(context)){
      case FAIL: return SUCCESS;
      case SUCCESS: return FAIL;
      default: return RUNNING;
    }
}

Status isPlayerClose::run(DecisionContext context)
{
    auto dist = context.gameState.getDistance();
    // return true if player closer than threshold
    if (m_threshold > dist)
        return SUCCESS;
    else
        return FAIL; // player far away
}

Status isEnemyOnValidNode::run(DecisionContext context)
{ 
    auto boidPos = context.boid.getPosition();
    auto boidNodeIndex = calcNodeIndex(boidPos);
    if (context.gameState.getGraph().getNodes(boidNodeIndex).size() >= 1)
        return SUCCESS;
    else
        return FAIL;
}