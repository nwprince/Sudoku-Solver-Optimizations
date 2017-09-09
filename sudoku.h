//Noah Prince
//Final Project
#include <iostream>
using namespace std;

class Sudoku
{
private:
  int board[9][9];
  int columns[9];
  int rows[9];
  int numCalls;
  int numRowChecks;
  int numColChecks;
  int numRowChecksSkipped;
  int numColChecksSkipped;
public:
  Sudoku();
  void printBoard();
  void buildBoard();
  void initialSums();
  bool checkConflict(int testNum, int rowNum, int colNum);
  bool solve();
};

Sudoku::Sudoku()
{
  for (int i = 0; i < 9; i++) {
    columns[i] = 0;
    rows[i] = 0;
    for (int j = 0; j < 9; j++) {
      board[i][j] = 0;
    }
  }
  numCalls = 0;
  numRowChecks = 0;
  numColChecks = 0;
  numRowChecksSkipped =0;
  numColChecksSkipped =0;
}

void Sudoku::buildBoard() {

  for (int i = 0; i < 9; i++) {
    cout<<"Enter the numbers in row "<< i+1<<" separted by spaces. Define blank spaces with 0 :"<<endl;
    for (int j = 0; j < 9; j++) {
      cin>>board[i][j];
    }
  }
}

void Sudoku::printBoard()
{
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      cout << board[i][j] << " ";
      if((j+1)%3 == 0) cout << "| ";
    }
    cout << endl;
    if((i+1)%3 == 0) cout << "------+-------+---------" << endl;
  }
  cout<<"This puzzle was solved with "<< numCalls << " recursive calls."<<endl;
  cout<<"Number of times Row check avoided looping : "<<numRowChecksSkipped
  <<" --------- Number of Column checks avoided looping: "
  <<numColChecksSkipped<<endl;
}

void Sudoku::initialSums()
{
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      rows[i] += board[i][j];
      columns[i] += board[j][i];
    }
  }
}

bool Sudoku::checkConflict(int testNum, int rowNum, int colNum)
{
  int tempRows=rowNum-rowNum%3;
  int tempCols=colNum-colNum%3;
  if(rows[rowNum] + testNum >45) {
    numRowChecksSkipped++;
    return false;
  }
  else if(columns[colNum] + testNum > 45) {
    numColChecksSkipped++;
    return false;
  }
  else {
    for (int k = 0; k < 9; k++) {
      if(board[rowNum][k] == testNum || board[k][colNum] == testNum)
        return false;
    }
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if(board[tempRows+i][tempCols+j]==testNum)
          return false;
      }
    }
  }
  return true;
}

bool Sudoku::solve()
{
  numCalls++;
  bool flag=false;
  int i,j=0;
  for(i=0;i<9;i++) {
    for(j=0;j<9;j++) {
      if(board[i][j]==0)
      {
        flag=true;
        break;
      }
    }
    if(flag)
      break;
  }
  if(!flag)
    return true;
  else {
    for(int testNum = 1; testNum <=9; testNum++) {
      if(checkConflict(testNum,i,j)) {
        board[i][j] = testNum;
        rows[i] +=testNum;
        columns[j]+=testNum;
        if(solve())
          return true;
        board[i][j] = 0;
        rows[i] -= testNum;
        columns[j] -=testNum;
      }
    }
  }
  return false;
}
