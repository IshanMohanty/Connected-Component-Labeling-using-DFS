//@author: Ishan Mohanty

/*Dependencies*/
#include <vector>
#include <stack>
#include <gtest/gtest.h>

using std::vector;
using std::stack;

/* Structure Pos: 
 * Data Structure for Defining Location/Position of Pixel
 */
struct pos{
	int row;
	int col;
};

/*
 * LabelNeighbours Function: Performs an Iterative Depth First Search(DFS) Algorithm for Labeling
 * Neighbourhood Pixels, One Component at a time. 
 * @param board: 2D Binary Image/Matrix 
 * @param i: row location of pixel in the Image/Matrix
 * @param j: column location of pixel in the Image/Matrix
 * @label: Current Label
 */
void LabelNeighbours(vector<vector<int>> &board, int i, int j, int label){
        
	//Define Neighbourhood Coordinates According to North(-1,0), South(1,0), East(0,1), West(0,-1)
        vector <pos> coordinates = { {-1,0}, {1,0}, {0,1}, {0,-1} };

        stack <pos> dfs_stack; //Define Stack for DFS

        dfs_stack.push({i,j}); //Push ForeGround(1) Component into Stack

	/* Iterate Till Stack is Empty Signifying all Connected Components for the specific Pixel are Labeled*/
        while( !dfs_stack.empty() ){
        
		pos pixel_pos = dfs_stack.top(); //Get Location of ForeGround Pixel
        
		dfs_stack.pop(); //Remove the Element(Location) from the Stack
	
		/*Find 4-Connected Neighbours of the specific pixel and Assign Label if Unlabeled*/
                for(int k=0; k < coordinates.size() ; k++){
	
			/*Check For Boundary Conditions: Location of pixels should be in-range of (0,board.row-1) and (0,board.col-1)*/
                        if( (  (coordinates[k].row + pixel_pos.row  >= 0) && (coordinates[k].row + pixel_pos.row <= board.size()-1 ) )
                                 &&  ( (coordinates[k].col + pixel_pos.col) >= 0 && (coordinates[k].col + pixel_pos.col) <= board[i].size()-1 )  ){
	
				/* Check if Neighbour Pixel is equal to ForeGround(1) and is also Unlabelled(1)*/  
                                if( board[coordinates[k].row + pixel_pos.row][coordinates[k].col + pixel_pos.col] == 1 ){
                                        
					board[coordinates[k].row + pixel_pos.row][coordinates[k].col + pixel_pos.col] = label;	//Assign Current Label to Pixel
					/*Push the Location of Neighbourhood Pixel into Stack and Repeat the Process for Other Connected Components*/
                                        dfs_stack.push({coordinates[k].row + pixel_pos.row,coordinates[k].col + pixel_pos.col}); 

                                }
                        }
                }
        }

}

/* 
 * ConnectedComponents Function: Performs Connected Component Labeling for the Binary Image/Matrix Inplace.
 * labels all the 1's connected according to the 4-Connected Neighbourhood rule (N,S,E,W) starting with label 2.
 * @param board: 2D Binary Image/Matrix
 * PRE CONDITION: board must be 2D and Binary Thresholded
 */
void ConnectedComponents(vector<vector<int>> &board){

	int curr_label = 1; //Initialize Current Label to 1
	/* Iterate through 2D Matrix */
	for(int i=0; i<board.size() ; i++){
		for( int j=0; j<board[i].size() ; j++){
			//If Pixel is ForeGround (1)
			if( board[i][j] == 1 ){
				curr_label+=1; //Increment Label
				board[i][j] = curr_label; //Assign Current Label to ForeGround
				LabelNeighbours(board,i,j,curr_label); //Perform DFS to Label Connected Neighbourhood Pixels
			}
		}
	}

}

// Test Cases 

TEST(Challenge, ConnectedComponents) {
    vector<vector<int>> v{
            {1, 0, 0, 1, 1},
            {0, 1, 1, 0, 0},
            {1, 0, 1, 1, 1},
            {1, 1, 0, 1, 0}
    };

    vector<vector<int>> answer{
            {2, 0, 0, 3, 3},
            {0, 4, 4, 0, 0},
            {5, 0, 4, 4, 4},
            {5, 5, 0, 4, 0}
    };

    ConnectedComponents(v);

    ASSERT_EQ(v, answer);
}

/*
 *Custom Test for a Small 3x3 Matrix
 */
TEST(Challenge_2, ConnectedComponents) {
	
	vector<vector<int>> v_cust{
            		{1, 0, 1},
			{0, 0, 1},
			{1, 0, 1}
	};

	vector<vector<int>> answer_cust{
	        	{2, 0, 3},
			{0, 0, 3},
			{4, 0, 3}
	};

	ConnectedComponents(v_cust);

	ASSERT_EQ(v_cust, answer_cust);
}

