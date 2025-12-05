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

Status CheckPlayerProximity::run(DecisionContext context)
{
    auto dist = context.gameState.getDistance();
    // return true if player closer than threshold
    if (m_threshold > dist)
        return SUCCESS;
    else
        return FAIL; // player far away
}

Status IsEnemyOnValidNode::run(DecisionContext context)
{ 
    auto boidPos = context.boid.getPosition();
    auto boidNodeIndex = calcNodeIndex(boidPos);
    if (context.gameState.getGraph().getNodes(boidNodeIndex).size() >= 1)
        return SUCCESS;
    else
        return FAIL;
}

Status PathfindPlayer::run(DecisionContext context)
{
    auto enemyPos = context.boid.getPosition();
    auto playerPos = context.gameState.getPlayerPos();

    // If there is a current path being followed
    if (!m_path.empty())
    {
        // check if the current path destination is the same as the current players location 
        if (m_path.front().getToNode() != calcNodeIndex(playerPos))
        {
            // current path destination is not the same so clear current plan and return FAIL
            m_path = std::vector<Connection>{};
            return FAIL; 
        } 
        // check if the current path start location is different than the current boid position
        else if (m_path.back().getFromNode() != calcNodeIndex(enemyPos))
        {
            // current path start location is different the current boid position so clear current plan and return FAIL
            m_path = std::vector<Connection>{};
            return FAIL; 
        } 
        // check if the current player position is on a valid node 
        else if (context.gameState.getGraph().getNodes(calcNodeIndex(playerPos)).size() >= 1)
        {
            // current path destination location is not a valid node so clear current plan and return FAIL
            m_path = std::vector<Connection>{};
            return FAIL;    
        }
    }

    // check if path is empty so new path must be planned
    if (m_path.empty()) 
    {
        m_path = context.gameState.getPath(enemyPos,playerPos);
        if (!m_path.empty())
            context.gameState.followPath(m_path, context.boid);
            return SUCCESS;
    } else // continue following existing path
        context.gameState.followPath(m_path, context.boid);
        return RUNNING;

}

Status PathfindRandomNode::run(DecisionContext context)
{
    auto enemyPos = context.gameState.getEnemyCatPos();
    auto random_position = sf::Vector2f(m_rng.getRandomInt(), m_rng.getRandomInt());
    // If there is a current path being followed
    if (!m_path.empty())
    {
        // check if the current path start location is different than the current boid position
        if (m_path.back().getFromNode() != calcNodeIndex(enemyPos))
        {
            // current path start location is different the current boid position so clear current plan and return FAIL
            return FAIL; 
        } 
        // check if the current random position is on a valid node 
        else if (context.gameState.getGraph().getNodes(calcNodeIndex(random_position)).size() >= 1)
        {
            // current path destination location is not a valid node so clear current plan and return FAIL
            m_path = std::vector<Connection>{};
            return FAIL;
        }
    }

    std::cout << m_path.size() << std::endl;
    // check if path is empty so new path must be planned
    if (m_path.empty()) 
    {
        m_path = context.gameState.getPath(enemyPos,random_position);
        if (!m_path.empty())
            context.gameState.followPath(m_path, context.boid);
            return SUCCESS;
    } else // continue following existing path
        context.gameState.followPath(m_path, context.boid);
        return RUNNING;
}

Status SeekPlayer::run(DecisionContext context)
{
    auto seekBehavior = std::make_unique<KinematicSeek>();
    if (!(context.boid.controller == seekBehavior))
    {
        context.boid.controller = std::move(seekBehavior);
    }
    
    context.boid.setTarget(context.gameState.getPlayer()); 
    return SUCCESS;
}