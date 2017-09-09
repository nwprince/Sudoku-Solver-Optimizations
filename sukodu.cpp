//Noah Prince
//Final Project

#include "sudoku.h"
#include "timing.h"

int main()
{
  timestamp_t t0 = get_timestamp();
  Sudoku Game;
  Game.buildBoard();
  Game.initialSums();
  if(Game.solve())
    Game.printBoard();
  else
    cout<<"NO SOLUTION"<<endl;
  timestamp_t t1 = get_timestamp();
  double secs = (t1 - t0) / 1000000.0L;
  cout<<"Time(microseconds): "<<secs<<endl;
  return 0;
}
