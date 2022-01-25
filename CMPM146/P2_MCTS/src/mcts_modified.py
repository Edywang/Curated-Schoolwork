from mcts_node import MCTSNode
from random import choice
from math import sqrt, log

from p2_t3 import Board
num_nodes = 100
explore_faction = 2

RED = 1
BLUE = 2
BOT = 0
OP = 1
MAX_ACTIONS = 5
ROLLOUTS = 5
MAX_DEPTH = 3
# MAX_DEPTH = 9223372036854775807

# Define a helper function to calculate the difference between the bot's score and the opponent's.
def outcome(owned_boxes, game_points, board, state):
    if game_points is not None:
        # Try to normalize it up?  Not so sure about this code anyhow.
        red_score = game_points[1]*9
        blue_score = game_points[2]*9
    else:
        red_score = len([v for v in owned_boxes.values() if v == 1])
        blue_score = len([v for v in owned_boxes.values() if v == 2])
    return red_score - blue_score if board.current_player(state) == RED else blue_score - red_score

# board.owned_boxes returns the owners of boards
def best_legal_action(board, state):
    id = board.current_player(state)
    best_action = board.legal_actions(state)[0]
    best_action_val = float('-inf')
    for action in board.legal_actions(state):
        red_val = 0
        blue_val = 0
        for box_owner in list(board.owned_boxes(board.next_state(state, action)).values()):
            if box_owner == RED:
                red_val += 1
            elif box_owner == BLUE:
                blue_val += 1
        if id == RED:
            action_val = red_val - blue_val
        else:
            action_val = blue_val - red_val
        if action_val > best_action_val:
            best_action = action
            best_action_val = action_val
    return best_action



def UCT(node, identity):
    winrate = node.wins/node.visits
    if identity == OP:
        winrate = 1 - winrate
    return winrate + (explore_faction*sqrt(log(node.parent.visits)/node.visits))

def best_child(root_node):
    best_wr = -1
    for node in root_node.child_nodes.values():
        if node.wins/node.visits > best_wr:
            best_wr = node.wins/node.visits
            best_action = node.parent_action
    return best_action


def traverse_nodes(node, board, state, identity):
    """ Traverses the tree until the end criterion are met.

    Args:
        node:       A tree node from which the search is traversing.
        board:      The game setup.
        state:      The state of the game.
        identity:   The bot's identity, either 'red' or 'blue'.

    Returns:        A node from which the next stage of the search can proceed.

    """
    curr_node = node
    curr_id = BOT
    if identity is None:
        print("No identity!")
    # while not at leaf(ie nodes with unfinished actions and not terminal)
    while curr_node.child_nodes and len(curr_node.untried_actions) == 0:
        curr_node.visits += 1
        best_node_val = float('-inf')
        # chooses best node in child nodes
        for elem in curr_node.child_nodes.values():
            elem_val = UCT(elem, curr_id)
            if elem_val > best_node_val:
                best_node = elem
                best_node_val = elem_val
        # switch the identity for next iteration
        if curr_id == BOT:
            curr_id = OP
        else:
            curr_id = BOT
        curr_node = best_node
    # returns the best leaf node
    curr_node.visits += 1
    return curr_node

    # Hint: return leaf_node


def expand_leaf(node, board, state):
    """ Adds a new leaf to the tree by creating a new child node for the given node.

    Args:
        node:   The node for which a child will be added.
        board:  The game setup.
        state:  The state of the game.

    Returns:    The added child node.

    """
    action = choice(node.untried_actions)
    node.untried_actions.remove(action)
    new_node = MCTSNode(node, action, board.legal_actions(board.next_state(state, action)))
    node.child_nodes[action] = new_node
    new_node.visits += 1
    return new_node
    # Hint: return new_node


def rollout(board, state):
    """ Given the state of the game, the rollout plays out the remainder randomly.

    Args:
        board:  The game setup.
        state:  The state of the game.

    """
    curr_state = state
    curr_action = 0

    while not board.is_ended(curr_state) and curr_action < MAX_ACTIONS:
        curr_action += 1
        best_expectation = float('-inf')
        best_move = None
        for move in board.legal_actions(curr_state):
            total_score = 0.0

            # Sample a set number of games where the target move is immediately applied.
            for r in range(ROLLOUTS):
                rollout_state = board.next_state(curr_state, move)

                # Only play to the specified depth.
                # for i in range(MAX_DEPTH):
                #     if board.is_ended(rollout_state):
                #         break
                #     rollout_move = choice(board.legal_actions(rollout_state))
                #     rollout_state = board.next_state(rollout_state, rollout_move)
                curr_depth = 0
                while not board.is_ended(rollout_state) and curr_depth < MAX_DEPTH:
                    rollout_move = choice(board.legal_actions(rollout_state))
                    rollout_state = board.next_state(rollout_state, rollout_move)
                    curr_depth += 1

                total_score += outcome(board.owned_boxes(rollout_state),
                                    board.points_values(rollout_state), board, curr_state)

            # expectation = float(total_score) / ROLLOUTS
            # expectation = float(total_score)

            # If the current move has a better average score, replace best_move and best_expectation
            # if expectation > best_expectation:
            if total_score > best_expectation:
                best_expectation = total_score
                # best_expectation = expectation
                best_move = move
                # if expectation == 1:
                #     break
        curr_state = board.next_state(curr_state, best_move)
        # print(curr_state)
    while not board.is_ended(curr_state):
        curr_state = board.next_state(curr_state, choice(board.legal_actions(curr_state)))

    # print("Returning curr_state!", curr_state)
    return curr_state
    # curr_state = state
    # while not board.is_ended(curr_state):
    #     curr_state = board.next_state(curr_state, best_legal_action(board, curr_state))
    # return curr_state


def backpropagate(node, won):
    """ Navigates the tree from a leaf node to the root, updating the win and visit count of each node along the path.

    Args:
        node:   A leaf node.
        won:    An indicator of whether the bot won or lost the game.

    """
    curr_node = node
    while curr_node:
        curr_node.wins += won
        curr_node = curr_node.parent


def think(board, state):
    """ Performs MCTS by sampling games and calling the appropriate functions to construct the game tree.

    Args:
        board:  The game setup.
        state:  The state of the game.

    Returns:    The action to be taken.

    """
    identity_of_bot = board.current_player(state)
    root_node = MCTSNode(parent=None, parent_action=None, action_list=board.legal_actions(state))

    for step in range(num_nodes):
        # Copy the game for sampling a playthrough
        sampled_game = state

        # Start at root
        node = root_node

        # Do MCTS - This is all you!
        node = traverse_nodes(node, board, sampled_game, identity_of_bot)

        # updates sampled_game to the state of the node
        curr_node = node
        action_queue = []
        while curr_node.parent_action:
            action_queue.insert(0, curr_node.parent_action)
            curr_node = curr_node.parent
        for action in action_queue:
            sampled_game = board.next_state(sampled_game, action)

        # checks if node is not a terminal state
        if not board.is_ended(sampled_game):
            node = expand_leaf(node, board, sampled_game)
            sampled_game = board.next_state(sampled_game, node.parent_action)
            sampled_game = rollout(board, sampled_game)

        won = board.points_values(sampled_game)[identity_of_bot] > 0
        
        backpropagate(node, won)

    # Return an action, typically the most frequently used action (from the root) or the action with the best
    # estimated win rate.
    return best_child(root_node)