#Author: Derek Coleman
#Project: Depth-First Search vs. Breadth-First Search
#Last Update: 3/6/19

#For copying the successors
import copy

def main(args):
	
	#Character dictionary
	successors = {'a':  ['b', 'c', 'd'],
              'b':  ['e', 'f', 'g'],
              'c':  ['a', 'h', 'i'],
              'd':  ['j', 'z'],
              'e':  ['k', 'l'],
              'g':  ['m'],
              'k':  ['z']}
              
    #Grid list
	gridSuccessors = []
    
    #Print the Breadth-First Search algorithm three times for the following paths: a to a, a to m, and a to z
	print('Breadth-first')
	print('path from a to a is', uniformSearch('a', 'a', successors, successorsf, True))
	print('path from a to m is', uniformSearch('a', 'm', successors, successorsf, True))
	print('path from a to z is', uniformSearch('a', 'z', successors, successorsf, True))
	
	#New line for separating space
	print('\n')
	
	#Print the Depth-First Search algorithm three times for same paths as before
	print('Depth-first')
	print('path from a to a is', uniformSearch('a', 'a', successors, successorsf, False))
	print('path from a to m is', uniformSearch('a', 'm', successors, successorsf, False))
	print('path from a to z is', uniformSearch('a', 'z', successors, successorsf, False))
	
	#New line for separating space
	print('\n')
	
	#Print the Breadth-First Search algorithm three times for the path from (0, 0) to (0, 9)
	print('Breadth-first')
	print('path from (0, 0) to (9, 9) is', uniformSearch((0, 0), (9, 9), gridSuccessors, gridSuccessorsf, True))
	
	#New line for separating space
	print('\n')
	
	#Print the Depth-First Search algorithm three times for the path from (0, 0) to (0, 9)
	print('Depth-first')
	print('path from (0, 0) to (9, 9) is', uniformSearch((0, 0), (9, 9), gridSuccessors, gridSuccessorsf, False))
	
	#Return 0, indicating success
	return 0

#Successor function that returns the successors of a state in the character successor dictionary
def successorsf(state, successors):
    return copy.copy(successors.get(state, []))

#Successor function that returns the successors of a state in the grid successor list
def gridSuccessorsf(state, successors):
	#Set the row and column indices from the cooresponding values in the state 
    row, col = state
    #Declare the successor list as an empty list
    successors = []
    #For every adjacent row and column
    for r in [-1, 0, 1]:
        for c in [-1, 0, 1]:
			#Create the next adjacent row and colum values for the new tuple
            newr = row + r
            newc = col + c
            #Check if the values are within the appropriate range of 0-9
            if 0 <= newr <= 9 and 0 <= newc <= 9:
				#Append the valid values to the list of successors as a tuple
                successors.append( (newr, newc) )
    #Return the successors list
    return successors

#Searches a graph or dictionary using a given methodology (breadth-first or depth-first) for a path between the start and goal states
#States are defined as the tuple (current state, parent)
def uniformSearch(startState, goalState, successors, successorsf, breadthFirst):
	#Declare expand as an empty dictionary
    expanded = {}
    #Declare unexpanded as a list initialized with the starting state as key with no parent
    unexpanded = [(startState, None)]
    #Check if the start state is the goal state
    if startState == goalState:
		#Return the first unexpanded state
        return [unexpanded[0][0]]
    #Continue until there are no states left to explore
    while len(unexpanded) != 0:
		#Pop an unexplored state and set it as the current state
        currentStateTuple = unexpanded.pop()
        #Set the state and parent to the approriate values
        currentState = currentStateTuple[0]
        parent = currentStateTuple[1]
        #Add the parent to the expanded dictionary using the state as the key
        expanded[currentState] = parent
        #Find the successors to the current state
        children = successorsf(currentState, successors)
        #Exlcude the children that are in the unexpanded list as the the current state or in the expanded dictionay
        children[:] = [state for state in children if not state in [tuple[0] for tuple in unexpanded] and not state in expanded]
        
        #Check to see if the goal state is amongst the children
        if goalState in children:
			#Declare the solution as a list initialized with the current state and the goal state
            solution = [currentState, goalState]
            #Continue if the parent value is valid
            while parent:
				#Insert the parent into the solution list
                solution.insert(0, parent)
                #Revert to the parent of the current state
                parent = expanded[parent]
            #Return the solution list
            return solution
        
        #Reverse and sort the list of children
        children.sort(reverse=True)
        #Cycle through the list of children
        for i in range(len(children)):
			#Remake the children list as a list of tuples in the form (current state, parent)
            children[i] = (children[i], currentState)
            #Append the children list to the front of the unexpanded list if the search is Breadth-First, or to the end if it is Depth-First
        unexpanded = children + unexpanded if breadthFirst else unexpanded + children
        
    #Return a message saying there is no valid path
    return 'Valid path not found.'
        


if __name__ == '__main__':
	import sys
	sys.exit(main(sys.argv))
