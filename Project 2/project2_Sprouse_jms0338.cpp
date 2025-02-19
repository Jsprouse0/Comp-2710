// Jacob Sprouse
// Auburn ID: Jms0338
// project2_Sprouse_jms0338.cpp
// Version 1
// compilation instructions

# include <iostream>
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

// shooting method for determining hit or miss
bool shoot(double accuracy) {
  double target = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
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
  else if (Bob) {
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
  else if (Aaron) {
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
  else if (Aaron) {
    bool hit = shoot(charlie_accuracy);
    Aaron = hit ? false : Aaron;
    return 0;
  }
  return -1;
}

bool at_least_two_alive(bool Aaron, bool Bob, bool Charlie) {
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
  while (at_least_two_alive(Aaron, Bob, Charlie)) {
    if (Aaron && strategy_num == 1) {
      Aaron_shoots1(Bob, Charlie);
    }
    else{
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
   *
   */
  std::cout << "Unit Testing 1: Function - at_least_two_alive()\n";

  std::cout << "Case 1: Aaron alive, Bob alive, Charlie alive\n";
  assert(true == at_least_two_alive(true, true, true));
  std::cout << "Case Passed...\n";

  std::cout << "Case 2: Aaron dead, Bob alive, Charlie alive\n";
  assert(true == at_least_two_alive(false, true, true));
  std::cout << "Case Passed...\n";

  std::cout << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
  assert(true == at_least_two_alive(true, false, true));
  std::cout << "Case Passed...\n";

  std::cout << "Case 4: Aaron alive, Bob alive, Charlie dead\n";
  assert(true == at_least_two_alive(true, true, false));
  std::cout << "Case Passed...\n";

  std::cout << "Case 5: Aaron dead, Bob dead, Charlie alive\n";
  assert(false == at_least_two_alive(false, false, true));
  std::cout << "Case Passed...\n";

  std::cout << "Case 6: Aaron dead, Bob alive, Charlie dead\n";
  assert(false == at_least_two_alive(false, true, false));
  std::cout << "Case Passed...\n";

  std::cout << "Case 7: Aaron alive, Bob dead, Charlie dead\n";
  assert(false == at_least_two_alive(true, false, false));
  std::cout << "Case Passed...\n";

  std::cout << "Case 8: Aaron dead, Bob dead, Charlie alive\n";
  assert(false == at_least_two_alive(false, false, true));
  std::cout << "Case Passed...\n";

  continue_test();
}

void test_Aaron_shoots1(bool &Bob, bool &Charlie) {
  std::cout << "Unit Testing 2: Function - Aaron_shoots1(Bob, Charlie)\n";

  std::cout << "Case 1: Bob alive, Charlie alive\n";
  std::cout << "Aaron is shooting at Charlie\n";

  std::cout <<"Case 2: Bob dead, Charlie alive\n";
  std::cout << "Aaron is shooting at Charlie\n";

  std::cout <<"Case 3: Bob alive, Charlie dead\n";
  std::cout << "Aaron is shooting at Bob\n";

  continue_test();
}

void test_Bob_shoots(bool &Aaron, bool &Charlie) {
  std::cout << "Unit Testing 3: Function Bob_shoots(Aaron, Charlie)\n";

  std::cout << "Case 1: Aaron alive, Charlie alive\n";
  std::cout << "Bob is shooting at Charlie\n";

  std::cout << "Case 2: Aaron dead, Charlie alive\n";
  std::cout << "Bob is shooting at Charlie\n";

  std::cout << "Case 3: Aaron alive, Charlie dead\n";
  std::cout << "Bob is shooting at Aaron\n";

  continue_test();
}

void test_Charlie_shoots(bool &Aaron, bool &Bob) {
  std::cout << "Unit Testing 4: Function Charlie_shoots(Aaron, Bob)\n";
  std::cout << "Case 1: Aaron alive, Bob alive\n";
  std::cout << "Charlie is shooting at Bob\n";

  std::cout << "Case 2: Aaron dead, Bob alive\n";
  std::cout << "Charlie is shooting at Bob\n";

  std::cout << "Case 3: Aaron alive, Bob dead\n";
  std::cout << "Charlie is shooting at Aaron\n";

  continue_test();
}

void test_Aaron_shoots2(bool &Bob, bool &Charlie) {
  std::cout << "Unit Testing 5: Function Aaron_shoots2(Bob, Charlie)\n";
  std::cout << "Case 1: Bob alive, Charlie alive\n";
  std::cout << "Aaron intentionally misses his first shot \n"
            << "Both Bob and Charlie are alive.\n";

  std::cout << "Case 2: Bob dead, Charlie alive\n";
  std::cout << "Aaron is shooting at Charlie\n";

  std::cout << "Case 3: Bob alive, Charlie dead\n";
  std::cout << "Aaron is shooting at Bob\n";

  continue_test();
}

int test_Truel(int strategy_num, bool &Aaron, bool &Bob, bool &Charlie) {
  std::cout << "Ready to test strategy " << strategy_num << " (run " << test_amount << " times): \n";
  continue_test();

  int aaron_wins = 0;
  int bob_wins = 0;
  int charlie_wins = 0;
  for (int i = 0; i < test_amount; i++) {
    int truel_result = truel(strategy_num, Aaron, Bob, Charlie);
    switch (truel_result) {
      case 0:
        aaron_wins++;
        break;
      case 1:
        bob_wins++;
        break;
      case 2:
        charlie_wins++;
        break;
      default:
        std::cout << "Error in test strategy " << strategy_num;
        break;
    }
  }

  std::cout << "Aaron won: " << aaron_wins << "/" << test_amount << " duels or " << static_cast<double>(aaron_wins) / test_amount * 100 << "%\n";
  std::cout << "Bob won: " << bob_wins << "/" << test_amount << " duels or " << static_cast<double>(bob_wins) / test_amount * 100 << "%\n";
  std::cout << "Charlie won: " << charlie_wins << "/" << test_amount << " duels or " << static_cast<double>(charlie_wins) / test_amount * 100 << "%\n";

  return aaron_wins;
}

void best_strategy(int strategy_1, int strategy_2) {
  if (strategy_1 > strategy_2) {
    std::cout << "Strategy 1 is better than Strategy 2 \n";
  }
  else if (strategy_2 > strategy_1) {
    std::cout << "Strategy 2 is better than Strategy 1 \n";
  }
  else {
    std::cout << "Both strategies produce equal results for Aaron";
  }
}

int main(){
  // Initialize Random number generator
  srand(time(0));
  rand();

  std::cout.setf(std::ios::fixed);
  std::cout.setf(std::ios::showpoint);
  std::cout.precision(2);
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

  best_strategy(strategy_1, strategy_2);

  return 0;
}