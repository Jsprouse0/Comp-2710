// Jacob Sprouse
// Auburn ID: Jms0338
// project2_Sprouse_jms0338_v2.cpp
// Version 2
// Compiling instructions:
// g++ project2_Sprouse_jms0338_v2.cpp -o <output_file_name>

/* Running instructions:
 * ./<output_file_name>
 *
 * Merging instructions:
 * git init
 * git add <file_name>
 * git commit -m "<message>"
 * git branch <name of branch>
 * git checkout <name of branch>
 * git add <file_name>
 * git commit -m "<message>"
 * git checkout <name of main branch>
 * git merge <name of branch>
*/

# include <iostream>
# include <iomanip>
# include <stdlib.h>
# include <assert.h>
# include <ctime>

// Accuracy constant
constexpr double aaron_accuracy = 0.333;
constexpr double bob_accuracy = 0.5;
constexpr double charlie_accuracy = 1;

// Testing Constant
constexpr int test_amount = 10000;

void continue_test(){
  // Pause command for Linux Terminal
  std::cout << "Press Enter to continue...";
  std::cin.ignore().get();
}

bool shoot(double accuracy) {
  /* shooting method for determining hit or miss
   * Input: accuracy indicates the probability of hitting the target
   *
   * Return: true if the shot hits, false otherwise
   */
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

void test_at_least_two_alive() {
  /* This is a test driver for at_least_two_alive()
   * to determine if the function is working correctly
   */
  std::cout << "Unit Testing 1: Function - at_least_two_alive()\n";

  std::cout << std::setw(5) << "" << std::left << "Case 1: Aaron alive, Bob alive, Charlie alive\n";
  assert(true == at_least_two_alive(true, true, true));
  std::cout << std::setw(28) << std::right << "Case Passed...\n";

  std::cout << std::setw(5) << "" << std::left << "Case 2: Aaron dead, Bob alive, Charlie alive\n";
  assert(true == at_least_two_alive(false, true, true));
  std::cout << std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
  assert(true == at_least_two_alive(true, false, true));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 4: Aaron alive, Bob alive, Charlie dead\n";
  assert(true == at_least_two_alive(true, true, false));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 5: Aaron dead, Bob dead, Charlie alive\n";
  assert(false == at_least_two_alive(false, false, true));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 6: Aaron dead, Bob alive, Charlie dead\n";
  assert(false == at_least_two_alive(false, true, false));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 7: Aaron alive, Bob dead, Charlie dead\n";
  assert(false == at_least_two_alive(true, false, false));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  std::cout <<std::setw(5) << "" << std::left << "Case 8: Aaron dead, Bob dead, Charlie alive\n";
  assert(false == at_least_two_alive(false, false, true));
  std::cout <<std::setw(28) << std::right << "Case Passed...\n";

  continue_test();
}

void test_Aaron_shoots1(bool &Bob, bool &Charlie) {
  /* Unit Testing for Aaron_shoots1
   * Input: Bob indicates if Bob is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: Change Bob to false if Bob is killed.
   *         Change Charlie to false if Charlie is killed.
   */
  std::cout << "Unit Testing 2: Function - Aaron_shoots1(Bob, Charlie)\n";

  std::cout << std::setw(7) << "" << std::left << "Case 1: Bob alive, Charlie alive\n";
  assert(Aaron_shoots1(Bob=true, Charlie=true) == 2 || 1);
  std::cout << std::setw(15) << "" << std::left << "Aaron is shooting at Charlie\n";

  std::cout << std::setw(7) << "" << std::left <<"Case 2: Bob dead, Charlie alive\n";
  assert(Aaron_shoots1(Bob=false, Charlie=true) == 2);
  std::cout << std::setw(15) << "" << std::left << "Aaron is shooting at Charlie\n";

  std::cout << std::setw(7) << "" << std::left <<"Case 3: Bob alive, Charlie dead\n";
  assert(Aaron_shoots1(Bob=true, Charlie=false) == 1);
  std::cout << std::setw(15) << "" << std::left << "Aaron is shooting at Bob\n";

  continue_test();
}

void test_Bob_shoots(bool Aaron, bool Charlie) {
  /* Unit Testing for Bob_shoots
   * Input: Aaron indicates if Aaron is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: Change Aaron to false if Aaron is killed.
   *         Change Charlie to false if Charlie is killed.
   */
  std::cout << "Unit Testing 3: Function Bob_shoots(Aaron, Charlie)\n";

  std::cout <<std::setw(7) << "" << std::left << "Case 1: Aaron alive, Charlie alive\n";
  assert(Bob_shoots(Aaron=true, Charlie=true) == 0 || 2);
  std::cout <<std::setw(15) << "" << std::left << "Bob is shooting at Charlie\n";

  std::cout <<std::setw(7) << "" << std::left << "Case 2: Aaron dead, Charlie alive\n";
  assert(Bob_shoots(Aaron=false, Charlie=true) == 2);
  std::cout <<std::setw(15) << "" << std::left << "Bob is shooting at Charlie\n";

  std::cout <<std::setw(7) << "" << std::left << "Case 3: Aaron alive, Charlie dead\n";
  assert(Bob_shoots(Aaron=true, Charlie=false) == 0);
  std::cout <<std::setw(15) << "" << std::left << "Bob is shooting at Aaron\n";

  continue_test();
}

void test_Charlie_shoots(bool &Aaron, bool &Bob) {
  /* Unit Testing for Charlie_shoots
   * Input: Aaron indicates if Aaron is alive or dead
   *        Bob indicates if Bob is alive or dead
   *
   * Return: Change Aaron to false if Aaron is killed.
   *         Change Bob to false if Bob is killed.
   */
  std::cout << "Unit Testing 4: Function Charlie_shoots(Aaron, Bob)\n";
  std::cout <<std::setw(7) << "" << std::left << "Case 1: Aaron alive, Bob alive\n";
  assert(Charlie_shoots(Aaron=true, Bob=true) == 0 || 1);
  std::cout <<std::setw(15) << "" << std::left << "Charlie is shooting at Bob\n";

  std::cout <<std::setw(7) << "" << std::right << "Case 2: Aaron dead, Bob alive\n";
  assert(Charlie_shoots(Aaron=false, Bob=true) == 1);
  std::cout <<std::setw(15) << "" << std::left << "Charlie is shooting at Bob\n";

  std::cout <<std::setw(7) << "" << std::right << "Case 3: Aaron alive, Bob dead\n";
  assert(Charlie_shoots(Aaron=true, Bob=false) == 0);
  std::cout <<std::setw(15) << "" << std::left << "Charlie is shooting at Aaron\n";

  continue_test();
}

void test_Aaron_shoots2(bool &Bob, bool &Charlie) {
  /* Unit Testing for Aaron_shoots2
   * Input: Bob indicates if Bob is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: Change Bob to false if Bob is killed.
   *         Change Charlie to false if Charlie is killed.
   */
  std::cout << "Unit Testing 5: Function Aaron_shoots2(Bob, Charlie)\n";
  std::cout <<std::setw(7) << "" << std::left << "Case 1: Bob alive, Charlie alive\n";
  assert( -1 ? Aaron_shoots2(Bob=true, Charlie=true) : false);
  std::cout <<std::setw(15) << "" << std::left << "Aaron intentionally misses his first shot \n";
  std::cout <<std::setw(15) << "" << std::left << "Both Bob and Charlie are alive.\n";

  std::cout <<std::setw(7) << "" << std::left << "Case 2: Bob dead, Charlie alive\n";
  assert( 1 || 2 ? Aaron_shoots2(Bob=false, Charlie=true) : false);
  std::cout <<std::setw(15) << "" << std::left << "Aaron is shooting at Charlie\n";

  std::cout <<std::setw(7) << "" << std::left << "Case 3: Bob alive, Charlie dead\n";
  assert( 1 || 2 ? Aaron_shoots2(Bob=true, Charlie=false) : false);
  std::cout <<std::setw(15) << "" << std::left << "Aaron is shooting at Bob\n";

  continue_test();
}

int test_Truel(int strategy_num, bool &Aaron, bool &Bob, bool &Charlie) {
  /* Test the truel function
   * Input: strategy_num indicates which strategy to use
   *        Aaron indicates if Aaron is alive or dead
   *        Bob indicates if Bob is alive or dead
   *        Charlie indicates if Charlie is alive or dead
   *
   * Return: 0 if Aaron wins, 1 if Bob wins, 2 if Charlie wins
   */
  std::cout << "Ready to test strategy " << strategy_num << " (run " << test_amount << " times): \n";
  continue_test();

  int aaron_wins   = 0;
  int bob_wins     = 0;
  int charlie_wins = 0;

  // Run the Truel simulation for the constant number of times (10,000)
  for (int i = 0; i < test_amount; i++) {
    Aaron = true;  // Reset the states for each test
    Bob = true;
    Charlie = true;

    // Call the truel function with the current strategy to determine the winner
    int truel_result = truel(strategy_num, Aaron, Bob, Charlie);

    if (truel_result == 0) {
      aaron_wins++;
    }
    else if (truel_result == 1) {
      bob_wins++;
    }
    else {
      charlie_wins++;
    }
  }

  std::cout << "Aaron won: " << aaron_wins << "/" << test_amount << " duels or " << static_cast<double>(aaron_wins) / test_amount * 100 << "%\n";
  std::cout << "Bob won: " << bob_wins << "/" << test_amount << " duels or " << static_cast<double>(bob_wins) / test_amount * 100 << "%\n";
  std::cout << "Charlie won: " << charlie_wins << "/" << test_amount << " duels or " << static_cast<double>(charlie_wins) / test_amount * 100 << "%\n\n";

  return aaron_wins;  // Return the number of wins for Aaron to compare strategies 1 && 2
}

void best_strategy(int strategy_1, int strategy_2) {
  /* Compare the two strategies and print the best one
   * Input: strategy_1 indicates the number of wins for strategy 1
   *        strategy_2 indicates the number of wins for strategy 2
   *
   * Reasoning: Strategy 2 is better because Bob and Charlie are the better marksmen, thus they will target each
   * other first. Aaron will then be left to deal with the last marksmen on the second turn
   * increasing his chances of winning.
   *
   * Return: Print the best strategy
   */
  if (strategy_1 > strategy_2) {
    std::cout << "Strategy 1 is better than Strategy 2\n";
  }
  else if (strategy_2 > strategy_1) {
    std::cout << "Strategy 2 is better than Strategy 1\n";
  }
  else {
    std::cout << "Both strategies produce equal results for Aaron";
  }
}

int main(){
  srand(time(0)); // initialize the random number generator

  std::cout.setf(std::ios::fixed);      // set the output format to fixed
  std::cout.setf(std::ios::showpoint);  // show decimal point
  std::cout.precision(2);              // set the precision to 2 decimal places
  std::cout << "*** Welcome to Jacob's Truel of the Fates Simulator ***" << std::endl;

  bool Aaron, Bob, Charlie = true;  // sets Aaron, Bob and Charlie to Alive (true)

  // Unit Testing
  test_at_least_two_alive();
  test_Aaron_shoots1(Bob, Charlie);
  test_Bob_shoots(Bob, Charlie);
  test_Charlie_shoots(Bob, Charlie);
  test_Aaron_shoots2(Bob, Charlie);


  // Strategy testing and comparison
  int strategy_1 = test_Truel(1, Aaron, Bob, Charlie);
  int strategy_2 = test_Truel(2, Aaron, Bob, Charlie);

  // Compare the two strategies and print the best one
  best_strategy(strategy_1, strategy_2);

  return 0;
}