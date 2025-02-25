// Jacob Sprouse
// Auburn ID: Jms0338
// project2_Sprouse_jms0338_v1.cpp
// Version 1
// compilation instructions:
// g++ project2_Sprouse_jms0338_v1.cpp -o <output_file_name>
/* Running instructions:
 * ./<output_file_name>
 * BE SURE TO HAVE MERGED THE TWO FILES IF YOU ARE RUNNING THIS ONE
 * I RECOMMEND JUST RUNNING THE V2 FILE TO TEST THE FINAL PRODUCT
 * CHECK V2 FOR MERGING INSTRUCTIONS
*/

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>

// Accuracy constant
constexpr double aaron_accuracy = 0.333;
constexpr double bob_accuracy = 0.5;
constexpr double charlie_accuracy = 1;

void continue_test(){
  // Pause command for Linux Terminal
  std::cout << "Press Enter to continue...";
  std::cin.ignore().get();
}

// shooting method for determining hit or miss
bool shoot(double accuracy) {
  double target = static_cast<double>(rand()) / ((RAND_MAX));
  return target <= accuracy;
}


int Aaron_shoots1(bool& Bob, bool& Charlie) {
  /* Strategy 1: Use call by reference
   * Input: Bob indicates if bob is alive or dead
   *        Charlie indicates if charlie is alive or dead
   *
   * Return: Change Bob into false if bob is killed.
   *         Change Charlie into false if Charlie is killed.
   */
  if (Charlie) {
    bool hit = shoot(aaron_accuracy);
    Charlie = hit ? false : Charlie;
    return 2; // Charlie is the third to go so return 2 to signify Charlie
  }
  if (Bob) {
    bool hit = shoot(aaron_accuracy);
    Bob = hit ? false : Bob;
    return 1; // Bob is the second to go so return 1 to signify Bob
  }
  return -1; // If Neither are alive return -1
}

int Aaron_shoots2(bool& Bob, bool& Charlie) {
  /*Strategy 2: Use call by reference
   *Input: Bob indicates whether Bob is alive or dead
   *       Charlie indicates whether Charlie is alive or dead
   *
   * Return: Change Bob to false if Bob is killed.
   *         Change Charlie to false if Charlie is killed.
   */
  if (Bob && Charlie) {
    return -1;
  }
  return Aaron_shoots1(Bob, Charlie);
}

int Bob_shoots(bool& Aaron, bool& Charlie) {
  /* Call by reference
   * Input: Aaron determines if Aaron is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: Change Aaron to false if Aaron is killed.
   *         Change Charlie to false if Charlie is killed
   */
  if (Charlie) {
    bool hit = shoot(bob_accuracy);
    Charlie = hit ? false : Charlie;
    return 2;
  }
  if (Aaron) {
    bool hit = shoot (bob_accuracy);
    Aaron = hit ? false : Aaron;
    return 0; // Aaron is the first in turn so 0 signifies Aaron
  }
  return -1;
}

int Charlie_shoots(bool& Aaron, bool& Bob) {
  /* Call by reference
   * Input: Aaron determines if Aaron is alive or dead
   *        Bob determines if Bob is dead or alive
   *
   * Return: Change Aaron into false if Aaron is killed.
   *         Change Bob into false if Bob is killed.
   */
  if (Bob) {
    bool hit = shoot(charlie_accuracy);
    Bob = hit ? false : Bob;
    return 1;
  }
  if (Aaron) {
    bool hit = shoot(charlie_accuracy);
    Aaron = hit ? false : Aaron;
    return 0;
  }
  return -1;
}

bool at_least_two_alive(bool Aaron, bool Bob, bool Charlie) {
  /* at_least_two_alive function
   * Input: Aaron indicates if Aaron is alive or dead
   *        Bob indicates if Bob is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: true if at least two are alive, false otherwise
   */
  int alive = 0;
  if (Aaron) {
    alive += 1;
  }
  if (Bob) {
    alive += 1;
  }
  if (Charlie) {
    alive += 1;
  }
  return alive >= 2;
}

int truel(int strategy_num, bool &Aaron, bool &Bob, bool &Charlie) {
  /* Truel function
   * Input: strategy_num indicates which strategy to use
   *        Aaron indicates if Aaron is alive or dead
   *        Bob indicates if Bob is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: 0 if Aaron wins, 1 if Bob wins, 2 if Charlie wins
   */
  while (at_least_two_alive(Aaron, Bob, Charlie)) {
    if (Aaron && strategy_num == 1) {
      Aaron_shoots1(Bob, Charlie);
    }
    else if (Aaron) {
      Aaron_shoots2(Bob, Charlie);
    }

    if (Bob) {
      Bob_shoots(Aaron, Charlie);
    }
    if (Charlie) {
      Charlie_shoots(Aaron, Bob);
    }
  }
  return Aaron ? 0 : Bob ? 1 : Charlie ? 2: -1;
}


int main(){
  srand(time(0));
  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(2);
  std::cout << "*** Welcome to Jacob's Truel of the Fates Simulator ***" << std::endl;
  bool Aaron = true;
  bool Bob = true;
  bool Charlie = true;  // sets Aaron, Bob and Charlie to Alive (true)

  // Single test
  if (truel(1, Aaron, Bob, Charlie) == 0) {
    std::cout << "Aaron won the duel\n";
  }
  else if (truel(1, Aaron, Bob, Charlie) == 1) {
    std::cout << "Bob won the duel\n";
  }
  else {
    std::cout << "Charlie won the duel\n";
  }

  return 0;
}
