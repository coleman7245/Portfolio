#Author: Derek Coleman
#Project: Iterative Deepening vs Depth Limited Search
#Last Update: 3/6/19

#Import the random package for generate random numbers.
import random

#Method Summary: The main thread of execution.
def main(args):
	#Create the start state for the sliding block puzzle.
    startState_8p = [0, 1, 3, 2, 4, 5, 6, 7, 8]
    #Create the goal state for the sliding block puzzle.
    goalState_8p = [1, 3, 0, 2, 4, 5, 6, 7, 8]
    #Create the start state for the peg puzzle.
    startState_peg15 = [0, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P']
    #Create the goal state for the peg puzzle.
    goalState_peg15 = [0, 0, 0, 'P', 0, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P']
    
    #Print the title of the algorithm and the puzzle being used.
    print('Depth-Limited Search Solution with 8 blocks:\n')
    #Find the correct path for the sliding block puzzle using the depth-limited search.
    path_8p = depthLimitedSearch(startState_8p, goalState_8p, actionsF_8p, takeActionF_8p, 15)
    #Print the path of the solution
    printPath_8p(startState_8p, goalState_8p, path_8p)
    #Print the dividing line.
    print()
    #Print the title of the algorithm and the puzzle being used.
    print('Iterative-deepening Search Solution with 8 blocks:\n')
    #Find the correct path for the sliding block puzzle using the iterative-deepening search.
    path_8p = iterativeDeepeningSearch(startState_8p, goalState_8p, actionsF_8p, takeActionF_8p, 15)
    #Print the path of the solution
    printPath_8p(startState_8p, goalState_8p, path_8p)
    #Print the dividing line.
    print()
    #Print the title of the algorithm and the puzzle being used.
    print('Depth-Limited Search Solution with 15 Pegs:\n')
    #Find the correct path for the peg puzzle using depth-limited search.
    path_peg15 = depthLimitedSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 15)
    #Print the path of the solution.
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
    #Print the dividing line.
    print()
    #Print the title of the algorithm and the puzzle being used.
    print('\nIterative-deepening Search Solution with 15 Pegs:\n')
    #Find the correct path of the peg puzzle using iterative-deepening search.
    path_peg15 = iterativeDeepeningSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 15)
    #Print the path of the solution.
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
	#Print the dividing line.
    print()
	
	#Create a random goal state for the peg puzzle.
    goalState_peg15 = randomGoalState_peg15(startState_peg15, actionsF_peg15, takeActionF_peg15, 20)
    #Create a random goal state for the sliding block puzzle.
    startState_8p = randomStartState_8p(goalState_8p, actionsF_8p, takeActionF_8p, 10)
	
	#Find the correct path of the sliding block puzzle using the iterative-deepening search.
    path_8p = iterativeDeepeningSearch(startState_8p, goalState_8p, actionsF_8p, takeActionF_8p, 20)
    #Find the correct path of the peg puzzle using the iterative-deepening search.
    path_peg15 = iterativeDeepeningSearch(startState_peg15, goalState_peg15, actionsF_peg15, takeActionF_peg15, 20)
	
	#Print the title of the algorithm and the puzzle being used.
    print('Iterative Deepening Search Solution with 8 Pieces in Random States:')
    #Print the path of the solution.
    printPath_8p(startState_8p, goalState_8p, path_8p)
    #Print the dividing line.
    print()
    #Print the title of the algorithm and the puzzle being used.
    print('Iterative Deepening Search Solution with 15 Pieces in Random States:')
    #Print the path of the solution.
    printPath_peg15(startState_peg15, goalState_peg15, path_peg15)
	
	#Return 0, indicating success.
    return 0

#Method Summary: Find the blank space on the board.
def findBlank_8p(state):
	    #r: Row index.
        r = 0
        #c: Column index.
        c = 0
        #For every space on the board:
        for s in state:
			#If this space is the blank space:
            if s == 0:
				#Return the row and column indices as a tuple.
                return (r, c)
            #Otherwise, move onto the next space.
            else:
				#Increment the column idex.
                c += 1
                #If the column index is out of bounds:
                if c == 3:
					#Increment the row index.
                    r += 1
                    #Set the column index to 0.
                    c = 0
        #Return an error message if the blank space was never found.
        return 'Blank not found!'

#Method Summary: Create a list of possible actions given the current state.        
def actionsF_8p(state):
    
    #Method Summary: Find the blank space on the board.
    def findBlank_8p(state):
	    #r: Row index.
        r = 0
        #c: Column index.
        c = 0
        #For every space on the board:
        for s in state:
			#If this space is the blank space:
            if s == 0:
				#Return the row and column indices as a tuple.
                return (r, c)
            #Otherwise, move onto the next space.
            else:
				#Increment the column idex.
                c += 1
                #If the column index is out of bounds:
                if c == 3:
					#Increment the row index.
                    r += 1
                    #Set the column index to 0.
                    c = 0
        #Return an error message if the blank space was never found.
        return 'Blank not found!'
    
    #Start an empty list of possible actions.
    actions = []
    #Find the row and column tuple of the blank space on the board.
    rowNColumn = findBlank_8p(state)
    #If the blank space is not at the leftmost edge:
    if rowNColumn[1] > 0:
		#Append the left action.
        actions.append('left')
    #If the blank space is not at the rightmost edge:
    if rowNColumn[1] < 2:
		#Append the right action.
        actions.append('right')
    #If the blank space is not at the uppermost edge:
    if rowNColumn[0] > 0:
		#Append the up action.
        actions.append('up')
    #If the blank space is not at the lowermost edge.
    if rowNColumn[0] < 2:
		#Append the down action.
        actions.append('down')
    #Return the list of possible actions.
    return actions

#Creates a list of possible actions on the peg puzzle.
def actionsF_peg15(state):
    
    #Method Summary: Find all blank spaces on the board.
    def findBlank_peg15(state):
		#r: The row index.
        r = 0
        #c: The column index.
        c = 0
        #Create an empty list of blanks.
        blanks = []
        #For every spot in the state:
        for s in state:
			#If the spot is blank:
            if s == 0:
				#Append the row and column tuple to the list of blanks.
                blanks.append((r, c))
            #Increment the column index.
            c += 1
            #If the column index is greater than the row index:
            if c > r:
				#Increment the row index.
                r += 1
                #Reset the column index.
                c = 0
        #Return the list of blank row and column tuples.
        return blanks
    
    #Find all pegs in the board.
    def findPeg_peg15(state):
		#r: The row index.
        r = 0
        #c: The column index.
        c = 0
        #Create an empty list of pegs.
        pegs = []
        #For every spot on the board:
        for s in state:
			#If the spot is a peg:
            if s == 'P':
				#Append the row and column tuple to the list.
                pegs.append((r, c))
            #Increment the column index.
            c += 1
            #If the column index is greater than the row index:
            if c > r:
				#Increment the row index.
                r += 1
                #Reset the column index to 0.
                c = 0
        #Return the list of peg row and column tuples.
        return pegs
    
    #Method Summary: Find all nearby pegs at the current spot.
    def findNearbyPegs_peg15(space, pegs):
		#Create an empty list of pegs.
        nearbyPegs = []
        #For every peg in the list of pegs:
        for p in pegs:
			#If the peg exits near the given spot:
            if p == (space[0] - 1, space[1] - 1) or p == (space[0] - 1, space[1]) or p == (space[0], space[1] + 1)or p == (space[0] + 1, space[1] + 1) or p == (space[0] + 1, space[1]) or p == (space[0], space[1] - 1):
				#Append the peg row and colun tuple to the list.
                nearbyPegs.append(p)
        #Return the list of row and column tuples.
        return nearbyPegs
    
    #Method Summary: Find all nearby blank spots on the board.
    def findNearbyBlanks_peg15(space, blanks):
		#Create a list of nearby blank row and column tuples.
        nearbyBlanks = []
        #For every blank in the list of blanks:
        for b in blanks:
			#If the blank exists near the given spot:
            if b == (space[0] - 1, space[1] - 1) or b == (space[0] - 1, space[1]) or b == (space[0], space[1] + 1) or b == (space[0] + 1, space[1] + 1) or b == (space[0] + 1, space[1]) or b == (space[0], space[1] - 1):
				#Append the blank row and column tuple to the list.
                nearbyBlanks.append(b)
        #Return the list of nearby blank row and column tuples.
        return nearbyBlanks
    
    #Method Summary: Find the list of possible moves given the current space.
    def findNearbyMoves_peg15(space):
		#Create an empty list of possible moves.
        nearbyMoves = []
        #If the space exists on the board:
        if space[0] - 2 >= 0:
			#Append the row and column tuple to the list.
            nearbyMoves.append((space[0] - 2, space[1]))
            #Append the row and column tuple to the list.
            if space[1] - 2 >= 0:
				#Append the row and column tuple to the list.
                nearbyMoves.append((space[0] - 2, space[1] - 2))
        #Append the row and column tuple to the list.
        if space[0] + 2 <= 4:
			#Append the row and column tuple to the list.
            nearbyMoves.append((space[0] + 2, space[1]))
            #Append the row and column tuple to the list.
            if space[1] + 2 <= space[0] + 2:
				#Append the row and column tuple to the list.
                nearbyMoves.append((space[0] + 2, space[1] + 2))
        #Append the row and column tuple to the list.
        if space[1] - 2 >= 0:
			#Append the row and column tuple to the list.
            nearbyMoves.append((space[0], space[1] - 2))
        #Append the row and column tuple to the list.
        if space[1] + 2 <= space[0]:
			#Append the row and column tuple to the list.
            nearbyMoves.append((space[0], space[1] + 2))
        #Return the nearby moves.
        return nearbyMoves
    
    #Create a list of all blanks on the board.
    blanks = findBlank_peg15(state)
    #Create a list of all pegs on the board.
    pegs = findPeg_peg15(state)
    #Create a list of possible actions.
    actions = []
    #For every peg in the list of pegs:
    for p in pegs:
		#Create a list of available moves.
        nearbyMoves = findNearbyMoves_peg15(p)
        #Create a list of nearby pegs.
        nearbyPegs = findNearbyPegs_peg15(p, pegs)
        #For every nearby peg:
        for np in nearbyPegs:
			#Create a list of nearby blanks.
            nearbyBlanks = findNearbyBlanks_peg15(np, blanks)
            #For every nearby blank:
            for nb in nearbyBlanks:
				#If the nearby blank is in the list of nearby moves:
                if nb in nearbyMoves:
					#Append the 3-length tuple of the starting peg, nearby peg, and the nearby blank to the list of possible actions.
                    actions.append((p, np, nb))
    #Return the list of possible actions.
    return actions

#Method Summary: Take a state-altering action given the state and a list of possible actions.
def takeActionF_8p(state, action):
	#temp: Temporary variable for swapping.
    temp = 0
    #Create a new state from all values of the old state.
    newState = [s for s in state]
    #If the action is downward:
    if action == 'down':
		#For every space in the new state:
        for i in range(len(newState)):
			#If the spot is a blank:
            if newState[i] == 0:
				#Swap the space directly below with the blank.
                temp = newState[i]
                newState[i] = newState[i + 3]
                newState[i + 3] = temp
                #Break out of the loop.
                break
    #If the action is upward:
    elif action == 'up':
		#For every space in the new state:
        for i in range(len(newState)):
			#If the spot is a blank:
            if newState[i] == 0:
				#Swap the space directly below with the blank.
                temp = newState[i]
                newState[i] = newState[i - 3]
                newState[i - 3] = temp
                #Break out of the loop.
                break
    #If the action is rightward:
    elif action == 'right':
		#For every space in the new state:
        for i in range(len(newState)):
			#If the spot is a blank:
            if newState[i] == 0:
				#Swap the space directly below with the blank.
                temp = newState[i]
                newState[i] = newState[i + 1]
                newState[i + 1] = temp
                #Break out of the loop.
                break
    #If the action is leftward:
    else:
		#For every space in the new state:
        for i in range(len(newState)):
			#If the spot is a blank:
            if newState[i] == 0:
				#Swap the space directly below with the blank.
                temp = newState[i]
                newState[i] = newState[i - 1]
                newState[i - 1] = temp
                #Break out of the loop.
                break
    #Return the new state.
    return newState

#Method Summary: Converts the row and column tuple to an integer position.
def convertRCToInt(t):
	    #row: The row index.
        row = int(t[0])
        #col: The column index.
        col = int(t[1])
        #The integer position.
        num = 0
        #For every row up to the row index.
        for i in range(row+1):
			#Increment the integer position.
            num += (i + 1)
        #Subtract the sum of the row and column indices from the integer position.
        num -= (row + 1 - col)
        #Return the integer position.
        return num

#Method Summary: Take a state-altering action given the current state and possible action.
def takeActionF_peg15(state, action):
    
    def convertRCToInt(t):
	    #row: The row index.
        row = int(t[0])
        #col: The column index.
        col = int(t[1])
        #The integer position.
        num = 0
        #For every row up to the row index.
        for i in range(row+1):
			#Increment the integer position.
            num += (i + 1)
        #Subtract the sum of the row and column indices from the integer position.
        num -= (row + 1 - col)
        #Return the integer position.
        return num
    
    #Create the new state using the values and positions of the old state.
    newState = [s for s in state]
    #Create the appropriate integer values out of the row and column tuples.
    startPeg = int(convertRCToInt(action[0]))
    middlePeg = int(convertRCToInt(action[1]))
    endPeg = int(convertRCToInt(action[2]))
    
    #Create the appropriate values when one peg hops over another into a blank spot. 
    newState[startPeg] = 0
    newState[middlePeg] = 0
    newState[endPeg] = 'P'
    
    #Return the new state.
    return newState

#Print the state of the sliding block puzzle.    
def printState_8p(state):
	#For every value in the state:
    for i in range(len(state)):
		#Print only 3 blocks at a time to display a 3 x 3 board.
        if i % 3 == 0:
            print(state[i], state[i+1], state[i+2])

#Print the state of a 15 peg puzzle board.            
def printState_peg15(state):
	
	#For every value in the state:
    for i in range(len(state)):
		#Print the board as a triangle, with the base increasing with decreasing height.
        if i == 0:
            print(' ', ' ', ' ', ' ', state[i], ' ', ' ', ' ', ' ')
        elif i == 1:
            print(' ', ' ', ' ', state[i], ' ', state[i+1], ' ', ' ', ' ')
        elif i == 3:
            print(' ', ' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', ' ')
        elif i == 6:
            print(' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ')
        elif i == 10:
            print(state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ', state[i+4])

#Print the path of a sliding block puzzle.            
def printPath_8p(startState, goalState, path):
    
    #Print the state of the sliding block puzzle. 
    def printState_8p(state):
		#For every value in the state:
        for i in range(len(state)):
			#Print only 3 blocks at a time to display a 3 x 3 board.
            if i % 3 == 0:
                print(state[i], state[i+1], state[i+2])
    
    #Print the start state title.
    print('Start State:\n')
    #Print this state of the sliding block puzzle.
    printState_8p(startState)
    #Print the path title.
    print('\nPath:\n')
    #For every state in tbe path:
    for p in path:
		#Print the state of the sliding block puzzle.
        printState_8p(p)
        #Print a dividing line.
        print()
    #Print the title of the goal state.
    print('Goal State:\n')
    #Print the goal state of the sliding block puzzle.
    printState_8p(goalState)
    
def printPath_peg15(startState, goalState, path):
    
    #Print the state of a 15 peg puzzle board.            
    def printState_peg15(state):
	
	    #For every value in the state:
        for i in range(len(state)):
		    #Print the board as a triangle, with the base increasing with decreasing height.
            if i == 0:
                print(' ', ' ', ' ', ' ', state[i], ' ', ' ', ' ', ' ')
            elif i == 1:
                print(' ', ' ', ' ', state[i], ' ', state[i+1], ' ', ' ', ' ')
            elif i == 3:
                print(' ', ' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', ' ')
            elif i == 6:
                print(' ', state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ')
            elif i == 10:
                print(state[i], ' ', state[i+1], ' ', state[i+2], ' ', state[i+3], ' ', state[i+4])
    
    #Print the start state title.
    print('Start State:\n')
    #Print the start state of the 15 peg puzzle.
    printState_peg15(startState)
    #Print the path title.
    print('\nPath:\n')
    #For every state in the path:
    for p in path:
		#Print the state of the 15 peg puzzle.
        printState_peg15(p)
        #Print a dividing line.
        print()
    #Print the goal state title.
    print('Goal State:\n')
    #Print the goal state of the 15 peg puzzle.
    printState_peg15(goalState)

#Method Summary: Create a random state for the 8 piece sliding block puzzle.    
def randomStartState_8p(goalState, actionsF, takeActionF, nSteps):
	#Start with the goal state, then work backwards.
    state = goalState
    #For every step:
    for i in range(nSteps):
		#Take a state-altering action and replace the current state.
        state = takeActionF(state, random.choice(actionsF(state)))
    #Return the altered state.
    return state

#Method Summary: Create a random state for the 15 peg puzzle board.
def randomGoalState_peg15(startState, actionsF, takeActionF, nSteps):
    
    #Find all pegs in the board.
    def findPeg_peg15(state):
		#r: The row index.
        r = 0
        #c: The column index.
        c = 0
        #Create an empty list of pegs.
        pegs = []
        #For every spot on the board:
        for s in state:
			#If the spot is a peg:
            if s == 'P':
				#Append the row and column tuple to the list.
                pegs.append((r, c))
            #Increment the column index.
            c += 1
            #If the column index is greater than the row index:
            if c > r:
				#Increment the row index.
                r += 1
                #Reset the column index to 0.
                c = 0
        #Return the list of peg row and column tuples.
        return pegs
	
	#Start with the start state.
    state = startState
    #For every step:
    for i in range(nSteps):
		#Find all the pegs on the board.
        pegs = findPeg_peg15(state)
        #If there is only one peg or less on the board:
        if len(pegs) <= 1:
			#The game is over, so return the state.
            return state
        #Find the list of possible actions depending on the current state.
        actions = actionsF(state)
        #If the list of actions is an empty list:
        if actions == []:
			#No valid moves exist, so return the state.
            return state
        #Take an action with a random action.
        state = takeActionF(state, random.choice(actions))
    #Return the randomized state.
    return state

#Method Summary: The iterative-deepening search algorithm.
def iterativeDeepeningSearch(startState, goalState, actionsF, takeActionF, maxDepth):
	#For every value until the maximum depth:
    for d in range(maxDepth + 1):
		#Run the depth limited search algorithm.
        result = depthLimitedSearch(startState, goalState, actionsF, takeActionF, d)
        #If the path resulted in failure:
        if result == 'failure':
			#Return a failure message.
            return 'failure'
        #If the algorithm ended before a solution was found:
        elif result != 'cutoff':
			#Insert the startState to the beginning of the path.
            result.insert(0, startState)
            #Return the path.
            return result
    #Return the cutoff message.
    return 'cutoff'

#Method Summary: The depth-limited search algorithm.
def depthLimitedSearch(startState, goalState, actionsF, takeActionF, depthLimit):
    
    #Method Summary: Check if the goal state and the current state are one in the same.
    def goalTestF(state, goalState):
		#goalOrNot: The boolean value to be returned, which is initialized to true.
        goalOrNot = True
        #For every value in the state:
        for i in range(len(state)):
			#If the values are NOT one in the same:
            if state[i] != goalState[i]:
				#Set the boolean variable to false.
                goalOrNot = False
        #Return the boolean variable.
        return goalOrNot
    
    #Method Summary: The recursive depth-limited search algorithm that is part of the depth-limited search algorithm. 
    def recursiveDLS(currentState, actionsF, takeActionF, goalState, goalTestF, depthLimit):
		#If the current state and the goal state are one in the same:
        if goalTestF(currentState, goalState):
			#Return an empty list.
            return []
        #If the depth limit is 0 or less:
        elif depthLimit <= 0:
			#Return the cutoff message.
            return 'cutoff'
        #Proceed with the algorithm.
        else:
			#Set the cutoff check to false.
            cutOff = False
            #Create a list of possible actions given the current state.
            actions = actionsF(currentState)
            #For every action in the list:
            for a in actions:
				#Take an action that changes the state of the board.
                nextState = takeActionF(currentState, a)
                #Create the solution path with the recursive call.
                result = recursiveDLS(nextState, actionsF, takeActionF, goalState, goalTestF, depthLimit - 1)
                #If the solution path was cutoff: 
                if result == 'cutoff':
					#Set the cutoff check to true.
                    cutOff = True
                #If the solution path was a failure:
                elif result != 'failure':
					#Insert the next state at the beginning of the solution path.
                    result.insert(0, nextState)
                    #Return the solution path.
                    return result
            #If the cutoff was reached:
            if cutOff:
				#Return the cutoff message.
                return 'cutoff'
            #The algorithm failed to find the solution path.
            else:
				#Return the failure message.
                return 'failure'
                
    #Return the solution path.
    return recursiveDLS(startState, actionsF, takeActionF, goalState, goalTestF, depthLimit)

#If the main method was invoked:
if __name__ == '__main__':
	#Import the system package.
    import sys
    #Run the main method.
    sys.exit(main(sys.argv))
