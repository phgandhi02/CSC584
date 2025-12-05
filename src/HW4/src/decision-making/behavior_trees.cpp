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

