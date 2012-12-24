#include "ProjectEuler.h"

#include "BigAdder.h" // BigAdder class
#include "Primes.h"   // IsPrime
#include "Text.h"     // IsPalindrome
#include "Timing.h"   // QueryCounter, QueryFrequency

#include <climits>    // INT_MAX
#include <iostream>   // cin, cout
#include <map>        // map
#include <numeric>    // accumulate
#include <ostream>    // endl
#include <regex>      // regex, smatch, sregex_iterator
#include <string>     // string
#include <vector>     // vector
using namespace std;

#define DISCARDS          5
#define TRIALS            5

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

void ProjectEuler::RunMenuLoop() const {
  while(true) {
    cout << "Enter the number of the problem to execute:" << endl;
    cout << "  1. Sum of natural numbers that are multiples of 3 and 5." << endl;
    cout << "  2. Sum of even-valued Fibonacci terms." << endl;
    cout << "  3. Largest prime factor." << endl;
    cout << "  4. Find largest palindrome product." << endl;
    cout << "  5. Find smallest number with consecutive divisors." << endl;
    cout << "  6. Difference between sum of squares and square sum." << endl;
    cout << "  7. Find nth prime number." << endl;
    cout << "  8. Largest product of consecutive digits." << endl;
    cout << "  9. Special Pythagorean triplet." << endl;
    cout << " 10. Summation of primes." << endl;
    cout << " 11. Largest product in a grid." << endl;
    cout << " 12. Highly divisible triangular number." << endl;
    cout << " 13. Large sum." << endl;
    cout << " 14. Longest Collatz sequence." << endl;
    cout << "> ";

    unsigned short problem;
    cin >> problem;
    cout << endl;

    switch (problem) {
    case 1:
      RunAndTimeMethod(&ProjectEuler::Problem1);
      break;
    case 2:
      RunAndTimeMethod(&ProjectEuler::Problem2);
      break;
    case 3:
      RunAndTimeMethod(&ProjectEuler::Problem3);
      break;
    case 4:
      RunAndTimeMethod(&ProjectEuler::Problem4);
      break;
    case 5:
      RunAndTimeMethod(&ProjectEuler::Problem5);
      break;
    case 6:
      RunAndTimeMethod(&ProjectEuler::Problem6);
      break;
    case 7:
      RunAndTimeMethod(&ProjectEuler::Problem7);
      break;
    case 8:
      RunAndTimeMethod(&ProjectEuler::Problem8);
      break;
    case 9:
      RunAndTimeMethod(&ProjectEuler::Problem9);
      break;
    case 10:
      RunAndTimeMethod(&ProjectEuler::Problem10);
      break;
    case 11:
      RunAndTimeMethod(&ProjectEuler::Problem11);
      break;
    case 12:
      RunAndTimeMethod(&ProjectEuler::Problem12);
      break;
    case 13:
      RunAndTimeMethod(&ProjectEuler::Problem13);
      break;
    case 14:
      RunAndTimeMethod(&ProjectEuler::Problem14);
      break;
    default:
      cout << "Please enter a valid problem number from the menu." << endl;
      break;
    }
  }
}

void ProjectEuler::RunAndTimeMethod(ProjectEulerMemFn problem) const {
  static const auto frequency = QueryFrequency();
  std::vector<double> times(TRIALS);
  for (auto i = 0; i < TRIALS + DISCARDS; ++i) {
    const auto start = QueryCounter();
    unsigned long long result = CALL_MEMBER_FN(*this, problem)();
    const auto finish = QueryCounter();
    if (i == 0) {
      std::cout << "Result: " << result << std::endl;
    }
    if (i >= DISCARDS) {
      auto time_taken = (finish - start) * 1000.0 / frequency;
      times.push_back(time_taken);
      std::cout << "\t@ " << time_taken << std::endl;
    }
  }
  auto total_time = std::accumulate(times.begin(), times.end(), 0.0);
  std::cout << "Average time taken: " << total_time / TRIALS << "ms" << std::endl;
  std::cout << std::endl;
}

unsigned long long ProjectEuler::Problem1() const {
  auto result = 0;
  for (auto i = 1; i < 1000; ++i) {
    if (i % 3 == 0 || i % 5 == 0) {
      result += i;
    }
  }
  return result;  // 233168
}

unsigned long long ProjectEuler::Problem2() const {
  int acc = 2;
  int last2 = 1, last1 = 2;
  int next ;
  while ((next = last2 + last1) < 4000000) {
    if (next % 2 == 0) {
      acc += next;
    }
    last2 = last1;
    last1 = next;
  }
  return acc;   // 4613732
}

unsigned long long ProjectEuler::Problem3() const {
  auto n = 600851475143;
  auto i = 2;
  while (n > 1) {
    if (n % i == 0) {
      n /= i;
    }
    ++i;
  }
  return i - 1; // 6857
}

unsigned long long ProjectEuler::Problem4() const {
  unsigned largest_palindrome = 0;

  for (unsigned first = 999; first >= 100; --first) {
    for(unsigned second = 999; second >= 100; --second) {
      unsigned product = first * second;
      if (IsPalindrome(product) && product > largest_palindrome) {
        largest_palindrome = product;
      }
    }
  }

  return largest_palindrome;  // 906609
}

unsigned long long ProjectEuler::Problem5() const {
  const unsigned short MIN_DIVISOR = 1;
  const unsigned short MAX_DIVISOR = 20;

  for (unsigned n = 1; ; ++n) {
    bool success = true;
    for (unsigned short d = MIN_DIVISOR; d <= MAX_DIVISOR; ++d) {
      if (n % d) {
        success = false;
        break;
      }
    }
    if (success) {
      return n; // 232792560
    }
  }
}

unsigned long long ProjectEuler::Problem6() const {
  // use well-known formula for calculating triangular numbers
  unsigned sum = (100 * 101) / 2;
  int squared_sum = sum * sum;

  unsigned sum_squares = 0;
  for (unsigned short n = 1; n <= 100; ++n) {
    sum_squares += n * n;
  }

  return squared_sum - sum_squares; // 25164150
}

unsigned long long ProjectEuler::Problem7() const {
  unsigned ordinal = 0;
  unsigned candidate = 1;
  while (ordinal < 10001) {
    if (IsPrime(++candidate)) {
      ++ordinal;
    }
  }
  return candidate; // 104743
}

unsigned long long ProjectEuler::Problem8() const {
  const string digits(
    "73167176531330624919225119674426574742355349194934"
    "96983520312774506326239578318016984801869478851843"
    "85861560789112949495459501737958331952853208805511"
    "12540698747158523863050715693290963295227443043557"
    "66896648950445244523161731856403098711121722383113"
    "62229893423380308135336276614282806444486645238749"
    "30358907296290491560440772390713810515859307960866"
    "70172427121883998797908792274921901699720888093776"
    "65727333001053367881220235421809751254540594752243"
    "52584907711670556013604839586446706324415722155397"
    "53697817977846174064955149290862569321978468622482"
    "83972241375657056057490261407972968652414535100474"
    "82166370484403199890008895243450658541227588666881"
    "16427171479924442928230863465674813919123162824586"
    "17866458359124566529476545682848912883142607690042"
    "24219022671055626321111109370544217506941658960408"
    "07198403850962455444362981230987879927244284909188"
    "84580156166097919133875499200524063689912560717606"
    "05886116467109405077541002256983155200055935729725"
    "71636269561882670428252483600823257530420752963450");
  unsigned max_product = 0;

  for (auto b = digits.begin(), e = b + 5; e != digits.end(); ++b, ++e) {
    unsigned product = std::accumulate(b, e, 1, [](unsigned acc, char next) {
      return acc * (next - '0');
    });
    if (product > max_product) {
      max_product = product;
    }
  }

  return max_product; // 40824
}

unsigned long long ProjectEuler::Problem9() const {
  for (unsigned short a = 1; a < 1000; ++a) {
    for (unsigned short b = a + 1; b < 1000; ++b) {
      unsigned short c = 1000 - a - b;

      if (a * a + b * b == c * c) {
        return a * b * c; // 31875000
      }
    }
  }
  return -1;
}

unsigned long long ProjectEuler::Problem10() const {
  unsigned long long sum = 0;
  for (unsigned n = 2; n < 2000000; ++n) {
    if (IsPrime(n)) {
      sum += n;
    }
  }
  return sum; // 142913828922
}

// Largest product in a grid
// Problem 11
// 22 February 2002
//
// In the 20x20 grid below, four numbers along a diagonal line have been marked
// in red.
//  08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
//  49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
//  81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
//  52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
//  22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
//  24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
//  32 98 81 28 64 23 67 10*26 38 40 67 59 54 70 66 18 38 64 70
//  67 26 20 68 02 62 12 20 95*63 94 39 63 08 40 91 66 49 94 21
//  24 55 58 05 66 73 99 26 97 17*78 78 96 83 14 88 34 89 63 72
//  21 36 23 09 75 00 76 44 20 45 35*14 00 61 33 97 34 31 33 95
//  78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
//  16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
//  86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
//  19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
//  04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
//  88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
//  04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
//  20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
//  20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
//  01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
// The product of these numbers is 26 * 63 * 78 * 14 = 1788696.
//
// What is the greatest product of four adjacent numbers in any
// direction (up, down, left, right, or diagonally) in the 20x20 grid?
unsigned long long ProjectEuler::Problem11() const {
  const string data(
    "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08\n"
    "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00\n"
    "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65\n"
    "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91\n"
    "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80\n"
    "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50\n"
    "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70\n"
    "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21\n"
    "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72\n"
    "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95\n"
    "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92\n"
    "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57\n"
    "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58\n"
    "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40\n"
    "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66\n"
    "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69\n"
    "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36\n"
    "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16\n"
    "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54\n"
    "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48\n");

  vector<vector<unsigned char>> grid;

  {
    vector<unsigned char> row;

    const regex r("(\\d{2})|(\\n)|( )");
    for (sregex_iterator i(data.begin(), data.end(), r), end; i != end; ++i) {
      const smatch &m = *i;
      if (m[1].matched) {
        row.push_back(stoi(m[1]));
      } else if (m[2].matched) {
        grid.push_back(row);
        row.clear();
      } else if (m[3].matched) {
        // do nothing
      } else {
        throw new runtime_error("RUNTIME ERROR: grid must contain only digits, "
          "newlines, and spaces.");
      }
    }

    _ASSERT(grid.size() == 20);
    _ASSERT(grid[0].size() == 20);
  }

  unsigned long long max_product = 0;

  // Check right
  for (unsigned char row = 0; row < 16; ++row) {
    for (unsigned char col = 0; col < 20; ++col) {
      unsigned long long product =
        grid[col][row]     * grid[col][row + 1] *
        grid[col][row + 2] * grid[col][row + 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check down
  for (unsigned char row = 0; row < 20; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]     * grid[col + 1][row] *
        grid[col + 2][row] * grid[col + 3][row];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check diagonal (-ve)
  for (unsigned char row = 0; row < 16; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]         * grid[col + 1][row + 1] *
        grid[col + 2][row + 2] * grid[col + 3][row + 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }
  // Check diagonal (+ve)
  for (unsigned char row = 4; row < 20; ++row) {
    for (unsigned char col = 0; col < 16; ++col) {
      unsigned long long product =
        grid[col][row]         * grid[col + 1][row - 1] *
        grid[col + 2][row - 2] * grid[col + 3][row - 3];
      if (product > max_product) {
        max_product = product;
      }
    }
  }

  return max_product; // 70600674
}

// Highly divisible triangular number
// Problem 12
// 08 March 2002
//
// The sequence of triangle numbers is generated by adding the natural numbers.
// So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The
// first ten terms would be: 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// Let us list the factors of the first seven triangle numbers:
//  1: 1
//  3: 1,3
//  6: 1,2,3,6
// 10: 1,2,5,10
// 15: 1,3,5,15
// 21: 1,3,7,21
// 28: 1,2,4,7,14,28
// We can see that 28 is the first triangle number to have over five divisors.
//
// What is the value of the first triangle number to have over five hundred
// divisors?
unsigned long long ProjectEuler::Problem12() const {
  for (unsigned long long candidate = 1, num = 1; ; candidate += ++num) {
    unsigned short total_divisors = 2;  // 1 and itself, which we won't test
    // NB: this fails for candidate == 1
    unsigned long long max_divisor =
      static_cast<unsigned long long>(sqrt(candidate));
    for (unsigned long long divisor = 2; divisor <= max_divisor; ++divisor) {
      if (candidate % divisor == 0) {
        // Here to be precise, but could be removed in this problem instance.
        if (divisor * divisor == candidate) {
          ++total_divisors;
        } else {
          total_divisors += 2;
        }
      }
    }
    if (total_divisors > 500) {
      return candidate;
    }
  }
}


// Large sum
// Problem 13
// 22 March 2002
//
// Work out the first ten digits of the sum of the following one-hundred
// 50-digit numbers. (see code)
unsigned long long ProjectEuler::Problem13() const {
  BigAdder total = 0U;
  total += "37107287533902102798797998220837590246510135740250";
  total += "46376937677490009712648124896970078050417018260538";
  total += "74324986199524741059474233309513058123726617309629";
  total += "91942213363574161572522430563301811072406154908250";
  total += "23067588207539346171171980310421047513778063246676";
  total += "89261670696623633820136378418383684178734361726757";
  total += "28112879812849979408065481931592621691275889832738";
  total += "44274228917432520321923589422876796487670272189318";
  total += "47451445736001306439091167216856844588711603153276";
  total += "70386486105843025439939619828917593665686757934951";
  total += "62176457141856560629502157223196586755079324193331";
  total += "64906352462741904929101432445813822663347944758178";
  total += "92575867718337217661963751590579239728245598838407";
  total += "58203565325359399008402633568948830189458628227828";
  total += "80181199384826282014278194139940567587151170094390";
  total += "35398664372827112653829987240784473053190104293586";
  total += "86515506006295864861532075273371959191420517255829";
  total += "71693888707715466499115593487603532921714970056938";
  total += "54370070576826684624621495650076471787294438377604";
  total += "53282654108756828443191190634694037855217779295145";
  total += "36123272525000296071075082563815656710885258350721";
  total += "45876576172410976447339110607218265236877223636045";
  total += "17423706905851860660448207621209813287860733969412";
  total += "81142660418086830619328460811191061556940512689692";
  total += "51934325451728388641918047049293215058642563049483";
  total += "62467221648435076201727918039944693004732956340691";
  total += "15732444386908125794514089057706229429197107928209";
  total += "55037687525678773091862540744969844508330393682126";
  total += "18336384825330154686196124348767681297534375946515";
  total += "80386287592878490201521685554828717201219257766954";
  total += "78182833757993103614740356856449095527097864797581";
  total += "16726320100436897842553539920931837441497806860984";
  total += "48403098129077791799088218795327364475675590848030";
  total += "87086987551392711854517078544161852424320693150332";
  total += "59959406895756536782107074926966537676326235447210";
  total += "69793950679652694742597709739166693763042633987085";
  total += "41052684708299085211399427365734116182760315001271";
  total += "65378607361501080857009149939512557028198746004375";
  total += "35829035317434717326932123578154982629742552737307";
  total += "94953759765105305946966067683156574377167401875275";
  total += "88902802571733229619176668713819931811048770190271";
  total += "25267680276078003013678680992525463401061632866526";
  total += "36270218540497705585629946580636237993140746255962";
  total += "24074486908231174977792365466257246923322810917141";
  total += "91430288197103288597806669760892938638285025333403";
  total += "34413065578016127815921815005561868836468420090470";
  total += "23053081172816430487623791969842487255036638784583";
  total += "11487696932154902810424020138335124462181441773470";
  total += "63783299490636259666498587618221225225512486764533";
  total += "67720186971698544312419572409913959008952310058822";
  total += "95548255300263520781532296796249481641953868218774";
  total += "76085327132285723110424803456124867697064507995236";
  total += "37774242535411291684276865538926205024910326572967";
  total += "23701913275725675285653248258265463092207058596522";
  total += "29798860272258331913126375147341994889534765745501";
  total += "18495701454879288984856827726077713721403798879715";
  total += "38298203783031473527721580348144513491373226651381";
  total += "34829543829199918180278916522431027392251122869539";
  total += "40957953066405232632538044100059654939159879593635";
  total += "29746152185502371307642255121183693803580388584903";
  total += "41698116222072977186158236678424689157993532961922";
  total += "62467957194401269043877107275048102390895523597457";
  total += "23189706772547915061505504953922979530901129967519";
  total += "86188088225875314529584099251203829009407770775672";
  total += "11306739708304724483816533873502340845647058077308";
  total += "82959174767140363198008187129011875491310547126581";
  total += "97623331044818386269515456334926366572897563400500";
  total += "42846280183517070527831839425882145521227251250327";
  total += "55121603546981200581762165212827652751691296897789";
  total += "32238195734329339946437501907836945765883352399886";
  total += "75506164965184775180738168837861091527357929701337";
  total += "62177842752192623401942399639168044983993173312731";
  total += "32924185707147349566916674687634660915035914677504";
  total += "99518671430235219628894890102423325116913619626622";
  total += "73267460800591547471830798392868535206946944540724";
  total += "76841822524674417161514036427982273348055556214818";
  total += "97142617910342598647204516893989422179826088076852";
  total += "87783646182799346313767754307809363333018982642090";
  total += "10848802521674670883215120185883543223812876952786";
  total += "71329612474782464538636993009049310363619763878039";
  total += "62184073572399794223406235393808339651327408011116";
  total += "66627891981488087797941876876144230030984490851411";
  total += "60661826293682836764744779239180335110989069790714";
  total += "85786944089552990653640447425576083659976645795096";
  total += "66024396409905389607120198219976047599490197230297";
  total += "64913982680032973156037120041377903785566085089252";
  total += "16730939319872750275468906903707539413042652315011";
  total += "94809377245048795150954100921645863754710598436791";
  total += "78639167021187492431995700641917969777599028300699";
  total += "15368713711936614952811305876380278410754449733078";
  total += "40789923115535562561142322423255033685442488917353";
  total += "44889911501440648020369068063960672322193204149535";
  total += "41503128880339536053299340368006977710650566631954";
  total += "81234880673210146739058568557934581403627822703280";
  total += "82616570773948327592232845941706525094512325230608";
  total += "22918802058777319719839450180888072429661980811197";
  total += "77158542502016545090413245809786882778948721859617";
  total += "72107838435069186155435662884062257473692284509516";
  total += "20849603980134001723930671666823555245252804609722";
  total += "53503534226472524250874054075591789781264330331690";
  std::string total_string = static_cast<std::string>(total);
  std::string answer = total_string.substr(0, 10);
  return stoull(answer);  // 5537376230
}

// Longest Collatz sequence
// Problem 14
// 05 April 2002
//
// The following iterative sequence is defined for the set of positive
// integers:
//  n -> n/2 (n is even)
//  n -> 3n + 1 (n is odd)
// Using the rule above and starting with 13, we generate the following
// sequence:
//  13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
// It can be seen that this sequence (starting at 13 and finishing at 1
// contains 10 terms. Although it has not been proved yet (Collatz Problem), it
// is thought that all starting numbers finish at 1.
// Which starting number, under one million, produces the longest chain?
// 
// NOTE: Once the chain starts the terms are allowed to go above one million.
unsigned long long ProjectEuler::Problem14() const {
  map<unsigned, unsigned> cache;
  // Pre-stage terminating value.
  cache[1] = 1;

  unsigned max_starting = 1U;
  unsigned max_length = 1U;

  for (unsigned n = 1U; n < 1000000U; ++n) {
    // Has this been processed already?
    {
      auto cached_value = cache.find(n);
      if (cached_value != cache.end()) {
        continue;
      }
    }

    unsigned cur = n;
    unsigned length = 1U;
    while (cur != 1) {
      // Apply Collatz rule.
      if (cur % 2 == 0) {
        cur /= 2;
      } else {
        cur *= 3;
        ++cur;
      }
      ++length;

      auto cached_value = cache.find(cur);
      if (cached_value != cache.end()) {
        unsigned new_length = length + (*cached_value).second - 1;
        cache[n] = new_length;
        if (new_length > max_length) {
          max_starting = n;
          max_length = new_length;
        }
        // Trick the while loop to complete.
        cur = 1;
      }
    }
  }

  return max_starting;  // 837799
}