#Author: coleman7245
#Project: A* Search Experiment
#Last Edit: 3/1/19

#include the random class
import random

#Global variable to track nodes. 
numOfNodes = 0

#Method Summary: Main thread of execution.
def main(args):
	#Run the experiment
    runExperiment([1, 2, 3, 4, 0, 5, 6, 7, 8], [1, 2, 3, 4, 5, 8, 6, 0, 7], [1, 0, 3, 4, 5, 8, 2, 6, 7], [h1_8p, h2_8p, h3_8p])
	
    return 0

#Method Summary: First heuristic function that returns a null guess.
def h1_8p(state, goal):
		#Return 0
        return 0

#Method Summary: Second heuristic function that returns the cost of the distance between the current state and goal.
def h2_8p(state, goal):
	
	#Method Summary: Find the blank space in the board.	
    def findBlank_8p(state):
		#Row index.
        r = 0
        #Column index.
        c = 0
        # For every state in the board:
        for s in state:
			#If the state is a space:
            if s == 0:
				#Return the row and column index.
                return (r, c)
            #Otherwise:
            else:
				#Increment the column index.
                c += 1
                #If the column index is out of bounds:
                if c == 3:
					#Increment the row index.
                    r += 1
                    #Reset the column index to 0.
                    c = 0
        #Return an error message.
        return 'Blank not found!'
	
	#Beginning position on the board.
    beginning = findBlank_8p(state)
    #Ending position on the board.
    end = findBlank_8p(goal)
    #Compute the distance between the beginning and end positions. 
    totalCost = abs(beginning[0] - end[0]) + abs(beginning[1] - end[1])
    #Return the total cost.
    return totalCost

#Third heuristic function that finds the total sum of costs of all squares in the board between the current state and goal.
def h3_8p(state, goal):
		
    #Method Summary: Find the blank space in the board.	
    def findSpace_8p(state, space):
		#Row index.
        r = 0
        #Column index.
        c = 0
        # For every state in the board:
        for s in state:
			#If the state is a space:
            if s == space:
				#Return the row and column index.
                return (r, c)
            #Otherwise:
            else:
				#Increment the column index.
                c += 1
                #If the column index is out of bounds:
                if c == 3:
					#Increment the row index.
                    r += 1
                    #Reset the column index to 0.
                    c = 0
        #Return an error message.
        return 'Blank not found!'
	
	#The total cost of moves.
    totalCost = 0
    #For every state on the board:
    for i in range(9):
		#Find the space between the current state and the intermediate state.
        beginning = findSpace_8p(state, i)
        #Find the space betwwen the goal and the intermediate state.
        end = findSpace_8p(goal, i)
        #Add the sum of distances to the total cost.
        totalCost += abs(beginning[0] - end[0]) + abs(beginning[1] - end[1])
    #Return the total cost.
    return totalCost

#Method Summary: Runs an experiment with multiple goal states and heuristic functions to see which grouping is the best.
def runExperiment(goalState1, goalState2, goalState3, hFunctions):
    
	#The current heuristic function.
    numOfH = 1
    #The depth or length of the algorithm in terms of states or moves.
    depths = []
    #The number of nodes for each experiment.
    numOfN = []
    #Names of the experiments.
    experimentNames = []
    #Effective branching factors.
    ebfs = []
    
    #Method Summary: Compares the state and goal to see if they're one in the same.
    def goalTestF_8p(state, goalState):
		#Boolean return value to be determined later.
        goalOrNot = True
        #For every value in state:
        for i in range(len(state)):
			#If the state value does equal the goal value:
            if state[i] != goalState[i]:
				#Set the return value to false.
                goalOrNot = False
        #Return the boolean value.
        return goalOrNot
        
    #Method Summary: Returns the actions available given the current state.
    def actionsF_8p(state):
    
        #Method Summary: Find the blank space in the board.	
        def findBlank_8p(state):
		    #Row index.
            r = 0
            #Column index.
            c = 0
            # For every state in the board:
            for s in state:
			    #If the state is a space:
                if s == 0:
				    #Return the row and column index.
                    return (r, c)
                #Otherwise:
                else:
				    #Increment the column index.
                    c += 1
                    #If the column index is out of bounds:
                    if c == 3:
					    #Increment the row index.
                        r += 1
                        #Reset the column index to 0.
                        c = 0
            #Return an error message.
            return 'Blank not found!'

        #The actions to be returned.
        actions = []
        #The row and column tuple formed from the current state's blank space.
        rowNColumn = findBlank_8p(state)
        #If the column is not on the leftmost edge:
        if rowNColumn[1] > 0:
			#Append the left action to the list possible actions.
            actions.append(('left', 1))
        #If the column is not at the rightmost edge:
        if rowNColumn[1] < 2:
			#Append the right action to the list of possible actions.
            actions.append(('right', 1))
        #If the row is not at the uppermost edge:
        if rowNColumn[0] > 0:
			#Append the up action to the list of possible actions.
            actions.append(('up', 1))
        #If the row is not at the lowermost edge:
        if rowNColumn[0] < 2:
			#Append the down action to the list of possible actions.
            actions.append(('down', 1))
        #Return the list of possible actions.
        return actions
    
    #Method Summary: Takes an action depending on the possible actions available. This action permanently alters the state.
    def takeActionF_8p(state, action):
		#Temporary variable for swapping.
        temp = 0
        #The new state created from values of the current state at their original positions.
        newState = [s for s in state]
        #The cost of the action currently being explored.
        cost = action[1]
        #If the action is directed downward:
        if action[0] == 'down':
			#For every space in the new state:
            for i in range(len(newState)):
				#If this space in the new state is the blank space:
                if newState[i] == 0:
					#Swap this space with the one directly below it.
                    temp = newState[i]
                    newState[i] = newState[i + 3]
                    newState[i + 3] = temp
                    #Break out of the loop.
                    break
        #If the action is directed upward:
        elif action[0] == 'up':
			#For every space in the new state:
            for i in range(len(newState)):
				#If this space in the new state is the blank space:
                if newState[i] == 0:
					#Swap this space with the one directly above it.
                    temp = newState[i]
                    newState[i] = newState[i - 3]
                    newState[i - 3] = temp
                    #Break out of the loop.
                    break
        #If the action is directed rightward:
        elif action[0] == 'right':
			#For every space in the new state:
            for i in range(len(newState)):
				#If this space in the new state is the blank space:
                if newState[i] == 0:
					#Swap the space with the one directly to the right of it.
                    temp = newState[i]
                    newState[i] = newState[i + 1]
                    newState[i + 1] = temp
                    #Break out of the loop.
                    break
        #The only other action left is to the left:
        else:
			#For every space in the new state:
            for i in range(len(newState)):
				#If this space in the new state is the blank space:
                if newState[i] == 0:
					#Swap this space with the one directly to left of it.
                    temp = newState[i]
                    newState[i] = newState[i - 1]
                    newState[i - 1] = temp
                    #Break out of the loop.
                    break
        #Return the new stae and its cost as a tuple.
        return (newState, cost)
    
    #Calculates the effective branching factor of the algorithm.
    def ebf(nNodes, depth, precision=0.01):
		#If the depth is less than or equal to 0:
        if depth <= 0:
			#Return the number of nodes.
            return nNodes
        #If the number of nodes is less than or equal to 0:
        elif nNodes <= 0:
			#Return 0.
            return 0
        #All parameters are ligitimate, so calculate the effective branching factor using the binary search.
        else:
			#Increment used to increase the hi end of the range.
            increment = 1
            #The original hi starts at 1.
            originalHi = 1
            #Set hi to be evaluated and returned with the original hi.
            hi = originalHi
            #Set the lo end of the range as 0.
            lo = 0
            #Formula as a function of hi, lo, middle, and depth.
            formula = 0
            #Continue the loop until a value is returned.
            while True:
				#If hi does NOT equal 1:
                if (hi != 1):
					#Compute the formula using the hi.
                    formula = ((1 - (hi ** (depth + 1))) / (1 - hi))
                #If the distance between the formula's output and the numer of nodes is less than or equal to the percision:
                if abs(formula - nNodes) <= precision:
					#Return the hi.
                    return hi
                #If the lo does NOT equal 1:
                if (lo != 1):
					#Calculate the forumula using the lo.
                    formula = ((1 - (lo ** (depth + 1))) / (1 - lo))
                #If the distance between the formula's output and the numer of nodes is less than or equal to the percision:
                if abs(formula - nNodes) <= precision:
					#Return the lo.
                    return lo
                #Calculate the middle position.
                middle = (lo + hi) / 2
                #If the middle does NOT equal 1:
                if (middle != 1):
					#Calculate the formula using the middle.
                    formula = ((1 - (middle ** (depth + 1))) / (1 - middle))
                #If the distance between the formula's output and the number of nodes is less than or equal to the precision:
                if abs(formula - nNodes) <= precision:
					#Return the middle.
                    return middle
                #If the distance between the hi and lo is less than or equal to the precision:
                if abs(hi - lo) <= precision:
					#Increment the original hi by a decreasing increment.
                    originalHi += increment
                    #Set the hi to the original hi
                    hi = originalHi
                    #Reset the lo to 0.
                    lo = 0
                #If the lo is greater than the number of nodes:
                elif lo > nNodes:
					#Scal the increment by a factor of .1.
                    increment *= .1
                    #Set the original hi to 1
                    originalHi = 1
                    #Set hi to the original hi.
                    hi = originalHi
                    #Set the lop to 0.
                    lo = 0
                #If all else fails:
                else:
					#If the formula's output is greater than the number of nodes:
                    if formula > nNodes:
						#Advance the hi with the middle.
                        hi = (hi + middle) / 2
                    #Only one option remains:
                    else:
						#Advance the lo using the middle.
                        lo = (lo + middle) / 2
    
    #Method Summary: Creates a board in a random state.
    def randomStartState_8p(goalState, actionsF, takeActionF, nSteps):
		#The initial state resembles the goal state.
        state = goalState
        #For every value in the number of steps:
        for i in range(nSteps):
			#Alter the state using the first random action taken.
            state = takeActionF(state, random.choice(actionsF(state)))[0]
        #Return the altered state
        return state
    
    #Method Summary: Finds the correct path using a limited depth-first search approach.
    def iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth):
		#Global variable.
        global numOfNodes
        #Initialize the global counter to 0.
        numOfNodes = 0
        #For every value in the range of the maximum depth:
        for d in range(maxDepth):
			#Store the result of the depthLimitedSearch using the given depth.
            result = depthLimitedSearch(startState, goalState, actionsF, takeActionF, d)
            #If the algorithm failed:
            if result == 'failure':
				#Return a failure message.
                return 'failure'
            #If the algorithm failed to find a solution with the given depth:
            elif result != 'cutoff':
				#Insert the startState at the beginning of the result list.
                result.insert(0, startState)
                #Return the result.
                return result
        #Return a cutoff message if the maximum depth has been reached.
        return 'cutoff'
    
    #Method Summary: Find the correct path using a depth-first search approach with a limited depth.
    def depthLimitedSearch(startState, goalState, actionsF, takeActionF, depthLimit):

        #Method Summary: Tests in the goal state has been reached.
        def goalTestF(state, goalState):
			#Boolean return value initialized to true.
            goalOrNot = True
            #For every space in the state:
            for i in range(len(state)):
				#If the space in state does have an equal in the goal state:
                if state[i] != goalState[i]:
					#Set the return value to false.
                    goalOrNot = False
            #Return the boolean value.
            return goalOrNot

        #Method Summary: Recursive variation of the depth-limited search.
        def recursiveDLS(currentState, actionsF, takeActionF, goalState, goalTestF, depthLimit):
			#If the goal state has been reached:
            if goalTestF(currentState, goalState):
				#Return an empty list.
                return []
            #If the depth limit has been reached:
            elif depthLimit <= 0:
				#Return the cutoff message.
                return 'cutoff'
            #Proceed with the algorithm otherwise:
            else:
				#Set the cutoff to false.
                cutOff = False
                #Find the list of possible actions.
                actions = actionsF(currentState)
                #For every possible action in the list:
                for a in actions:
					#Create the next state with the taken action.
                    nextState, _ = takeActionF(currentState, a)
                    #Refer to the global variable.
                    global numOfNodes
                    #Increment the number of nodes.
                    numOfNodes += 1
                    #Store the result of the recursive call.
                    result = recursiveDLS(nextState, actionsF, takeActionF, goalState, goalTestF, depthLimit - 1)
                    #If the result was cutoff: 
                    if result == 'cutoff':
						#Set the cutoff to true.
                        cutOff = True
                    #If the result did NOT result in failure.
                    elif result != 'failure':
						#Insert the next state at the beginning of the list.
                        result.insert(0, nextState)
                        #Return the result.
                        return result
                #If the cutoff is true:
                if cutOff:
					#Return the cutoff message.
                    return 'cutoff'
                #Failure is the last option.
                else:
					#Return the failure message.
                    return 'failure'
                    
		#Return the call to the recursive depth-limited search algorithm.
        return recursiveDLS(startState, actionsF, takeActionF, goalState, goalTestF, depthLimit)
    
    #Node class written by Chuck Anderson.
    class Node:
        def __init__(self, state, f=0, g=0 ,h=0):
            self.state = state
            self.f = f
            self.g = g
            self.h = h
        def __repr__(self):
            return "Node(" + repr(self.state) + ", f=" + repr(self.f) + \
                   ", g=" + repr(self.g) + ", h=" + repr(self.h) + ")"

    #Method Summary: Starts the A* aearch algorithm.
    def aStarSearch(startState, actionsF, takeActionF, goalTestF, hF):
		#Refer to the global counter for nodes.
        global numOfNodes
        #Initialize the number of nodes to 0.
        numOfNodes = 0
        #Use the heristic function with the start state.
        h = hF(startState)
        #Create the starting node with the start state and the heuristic function.
        startNode = Node(state=startState, f=0+h, g=0, h=h)
        #Return the call to the main A* search algorithm.
        return aStarSearchHelper(startNode, actionsF, takeActionF, goalTestF, hF, float('inf'))

    #Method Summary: A* search algorithm.
    def aStarSearchHelper(parentNode, actionsF, takeActionF, goalTestF, hF, fmax):
		#If the goal state has been reached:
        if goalTestF(parentNode.state):
			#Return a tuple of the parent state and the g cost.
            return ([parentNode.state], parentNode.g)
        #Create the list of possible actions.
        actions = actionsF(parentNode.state)
        #If the list of possible actions is empty:
        if not actions:
			#Return a failure node.
            return ("failure", float('inf'))
        #Create the list of child nodes.
        children = []
        #For every possible action in the list:
        for action in actions:
			#Create a state/cost tuple from the given action and parent state.
            (childState,stepCost) = takeActionF(parentNode.state, action)
            #Refer to the global counter for the number of nodes.
            global numOfNodes
            #Increment the number of nodes.
            numOfNodes += 1
            #Calculate the h cost of the child state.
            h = hF(childState)
            #Calculate the g cost as the sum of the parent's g cost and the step cost.
            g = parentNode.g + stepCost
            #Calculate the f cost as the maximum value betweeen the sum of the h ad g costs and the parent node's f cost.
            f = max(h+g, parentNode.f)
            # Create the child node with the calculate costs.
            childNode = Node(state=childState, f=f, g=g, h=h)
            #Append the current child node to the list of child nodes.
            children.append(childNode)
        #Continue the loop until the break instruction is reached.
        while True:
            #Sort the list of child nodes using the f cost as the lambda.
            children.sort(key = lambda n: n.f)
            #Pick the first child node as the prime choice.
            bestChild = children[0]
            #If the best node's f cost is greater than the maximum f cost:
            if bestChild.f > fmax:
				#Return the failure node.
                return ("failure",bestChild.f)
            # Calculate the next best f cost.
            alternativef = children[1].f if len(children) > 1 else float('inf')
            # Expand the best child, set its f value to be returned value from the recursive call.
            result,bestChild.f = aStarSearchHelper(bestChild, actionsF, takeActionF, goalTestF,
                                                hF, min(fmax,alternativef))
            #If the result is not a failure node:
            if result is not "failure":
				#Insert the parent state at the beginning of the result list.              
                result.insert(0,parentNode.state)
                #Return the result list and the best node's f cost as a tuple.     
                return (result, bestChild.f)       
    
    #Method Summary: Print the header of the experiment.
    def printHeader(goalState1, goalState2, goalState3):
        print('         ', goalState1, '   ', goalState2, '   ', goalState3)
        print('Algorithm     Depth   Nodes   EBF             Depth   Nodes   EBF               Depth   Nodes   EBF')
        return
    
    #Method Summary: Print the results of the experiment.
    def printExperiment(algorithm, depth, nNodes, ebf):
        print(algorithm, '         ', depth[0], '     ', nNodes[0], '   ', "{0:.4f}".format(ebf[0]), '      ', depth[1], ' ', nNodes[1], ' ', "{0:.4f}".format(ebf[1]), '           ', depth[2], ' ', nNodes[2], ' ', "{0:.4f}".format(ebf[2]))
        return
    
    #Initialize the start states with a random state.
    startState1 = randomStartState_8p(goalState1, actionsF_8p, takeActionF_8p, 20)
    startState2 = randomStartState_8p(goalState2, actionsF_8p, takeActionF_8p, 20)
    startState3 = randomStartState_8p(goalState3, actionsF_8p, takeActionF_8p, 20)
    
    #Print the header.
    printHeader(goalState1, goalState2, goalState3)
    
    #Run the experiment with the iterative deepening search algorithm.
    #Append the experiment name to the list.
    experimentNames.append('IDS')
    #Try the IDS algorithm with goal state 1.
    result = iterativeDeepeningSearch(startState1, goalState1, actionsF_8p, takeActionF_8p, 20)
    #Append the depth from the result.
    depths.append(len(result) - 1)
    #Append the number of nodes from the result to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the IDS algorithm with goal state 2.
    result = iterativeDeepeningSearch(startState2, goalState2, actionsF_8p, takeActionF_8p, 20)
    #Append the depth from the result.
    depths.append(len(result) - 1)
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the IDS algorithm with goal state 3.
    result = iterativeDeepeningSearch(startState3, goalState3, actionsF_8p, takeActionF_8p, 20)
    #Append the depth from the result.
    depths.append(len(result) - 1)
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Print the experiment results from the IDS algorithm.
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    #Reset the depth to an empty list.
    depths = []
    #Reset the number of nodes to an empty list.
    numOfN = []
    #Reset the ebf to an empty list.
    ebfs = []
    
    #Run the experiment with the A* search algorithm and the first heuristic function.
    #Append the experiment name to the list.
    experimentNames.append('A*h1')
    #Try the A* search algorithm with goal state 1 and the first heuristic function.
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[0](s, goalState1))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 2 and the first heuristic function.
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[0](s, goalState2))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 3 and the first heuristic function.
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[0](s, goalState3))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Print the results from the A* search algorithm and the first heuristic function.
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    #Reset the depth to an empty list.
    depths = []
    #Reset the number of nodes to an empty list.
    numOfN = []
    #Reset the ebf to an empty list.
    ebfs = []
    
    #Run the experiment using the A* search algorithm and the second heuristic function.
    #Append the experiment name to the list.
    experimentNames.append('A*h2')
    #Try the A* search algorithm with goal state 1 and the second heuristic function.
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[1](s, goalState1))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 2 and the second heuristic function.
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[1](s, goalState2))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 3 and the second heuristic function.
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[1](s, goalState3))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Print the results from the A* search algorithm and the second heuristic function.
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
    
    #Reset the depth to an empty list.
    depths = []
    #Reset the number of nodes to an empty list.
    numOfN = []
    #Reset the ebf to an empty list.
    ebfs = []
    
    #Run the experiment using the A* search algorithm and the thirs heuristic function.
    #Append the experiment name to the list.
    experimentNames.append('A*h3')
    #Try the A* search algorithm with goal state 1 and the third heuristic function.
    result = aStarSearch(startState1, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState1), lambda s : hFunctions[2](s, goalState1))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 2 and the third heuristic function.
    result = aStarSearch(startState2, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState2), lambda s : hFunctions[2](s, goalState2))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Try the A* search algorithm with goal state 3 and the third heuristic function.
    result = aStarSearch(startState3, actionsF_8p, takeActionF_8p, lambda s : goalTestF_8p(s, goalState3), lambda s : hFunctions[2](s, goalState3))
    #Append the depth from the result.
    depths.append(result[1])
    #Append the number of nodes to the list.
    numOfN.append(numOfNodes)
    #Append the ebf from the result to the list.
    ebfs.append(ebf(numOfN[len(numOfN) - 1], depths[len(depths) - 1]))
    #Print the results from the A* search algorithm and the third heuristic function.
    printExperiment(experimentNames[len(experimentNames) - 1], depths, numOfN, ebfs)
         
#If the function name is main:
if __name__ == '__main__':
	#Import the sys package.
    import sys
    #Run the main method.
    sys.exit(main(sys.argv))
