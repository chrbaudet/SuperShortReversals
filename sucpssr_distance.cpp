/******************************************************************************/
/*                                                                            */
/*   This file is part of SuperShortReversals.                                */
/*                                                                            */
/*   SuperShortReversals is free software: you can redistribute it and/or     */
/*   modify it under the terms of the GNU General Public License as published */
/*   by the Free Software Foundation, either version 2 of the License, or     */
/*   any later version.                                                       */
/*                                                                            */
/*   SuperShortReversals is distributed in the hope that it will be useful,   */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*   GNU General Public License for more details.                             */
/*                                                                            */
/*   You should have received a copy of the GNU General Public License        */
/*   along with SuperShortReversals.                                          */
/*   If not, see <http://www.gnu.org/licenses/>.                              */
/*                                                                            */
/******************************************************************************/

/* ************************************************************************** */
/* Sorting unsigned permutations by super short reversals problem - Distance  */
/* ************************************************************************** */

#include <set>
#include <vector>
#include <climits>

#include <fstream>
#include <iomanip>
#include <iostream>

/* ************************************************************************** */
// Struct to receive the command line parameters
struct Parameters {
  // Permutation pi (input permutation)
  std::vector<int> pi;
};
/* ************************************************************************** */


/* ************************************************************************** */
// Prints program usage
void printUsage(char* name) {
  std::cerr << std::endl << "Usage: " << name << " <permutation>" << std::endl << std::endl;
  std::cerr << " -----------------------------------------------------------------------" << std::endl;
  std::cerr << " |This program returns the distance between the given permutation and  |" << std::endl;
  std::cerr << " |the identity permutation considering the problem SUCPSSR:            |" << std::endl;
  std::cerr << " |Sorting Unsigned Circular Permutations by Super Short Reversals      |" << std::endl;
  std::cerr << " -----------------------------------------------------------------------" << std::endl << std::endl;
  exit(EXIT_FAILURE);
}
/* ************************************************************************** */


/* ************************************************************************** */
// Verifies the list of arguments
Parameters processArguments(int argc, char* argv[]) {

  if (argc != 2) printUsage(argv[0]);

  bool error = false;

  Parameters toReturn;

  std::set<int> elements;

  std::string aux = std::string(argv[1]);
  size_t index    = 0;
  size_t length   = aux.length();
  size_t comma    = aux.find_first_of(",");
  try {
    if (comma != std::string::npos) {
      while (index < length) {
	int element = std::stoi(aux.substr(index, (comma - index)));
	if (element > 0) {
	  elements.insert(element);
	  toReturn.pi.push_back(element);
	  index = comma + 1;
	  comma = aux.find_first_of(",", index);
	  if (comma == std::string::npos) comma = length;
	} else {
	  error = true;
	  break;
	}
      }
    } else {
      int element = std::stoi(aux);
      if (element > 0) {
	elements.insert(element);
	toReturn.pi.push_back(element);
      } else {
	error = true;
      }
    }
  } catch (const std::exception& ia) {
    error = true;
  }

  int nElements = toReturn.pi.size();
  if (nElements < 1) {
    error = true;
  } else {
    for (int i = 1; i <= nElements; ++i) {
      if (elements.find(i) == elements.end()) {
	error = true;
	break;
      }
    }
  }

  if (error) {
    std::cerr << std::endl << "ERROR!!! Invalid unsigned circular permutation: " << argv[1] << std::endl;
    printUsage(argv[0]);
  }

  return toReturn;
}
/* ************************************************************************** */


/* ************************************************************************** */
// Returns the index of the element that has the maximum absolute value. The
// parameter x is the displacement vector.
int indexMaximumValue(const std::vector<int> &x) {
  int k   = -1;
  int max = -1;
  for(int i = 0; i < x.size(); ++i) {
    if(max < x[i]) {
      max = x[i];
      k = i;
    }
  }
  return k;
}
/* ************************************************************************** */


/* ************************************************************************** */
// Returns the index of the element that has the minimum absolute value. The
// parameter x is the displacement vector.
int indexMinimumValue(const std::vector<int> &x) {
  int k   = -1;
  int min = x.size();
  for(int i = 0; i < x.size(); ++i) {
    if(min > x[i]) {
      min = x[i];
      k = i;
    }
  }
  return k;
}
/* ************************************************************************** */


/* ************************************************************************** */
// Returns the crossing number of the displacement vector.
int crossingNumber(const std::vector<int> &x) {
  int cn = 0;
  int n  = x.size();

  for (int i = 0; i < n; ++i) {

    for (int j = i + 1; j < n; ++j) {

      int r = i - j;
      int s = (i + x[i]) - (j + x[j]);

      for (int k = std::min(r, s); k <= std::max(r, s); ++k)
	if (k % n == 0) ++cn;

    } // for (int j = i + 1; j < n; ++j) {...}

  } // for (int i = 0; i < n; ++i) {...}

  return cn;
}
/* ************************************************************************** */

/* ************************************************************************** */
int getDistance(const std::vector<int> &pi) {

  int i, j;
  int n = pi.size();

  std::vector<int> x = std::vector<int>(n);
  for(int i = 1; i <= n; ++i) {
    x[i - 1] = pi[i - 1] - i;
  }

  i = indexMaximumValue(x);
  j = indexMinimumValue(x);
  while(x[i] - x[j] > n) {
    x[i] -= n;
    x[j] += n;
    i = indexMaximumValue(x);
    j = indexMinimumValue(x);
  }

  return crossingNumber(x);

}
/* ************************************************************************** */


/* ************************************************************************** */
// Rotates the permutation starting from the base index.
std::vector<int> rotate(const std::vector<int> &pi, int baseIndex) {
  int n = pi.size();
  std::vector<int> toReturn = std::vector<int>(n);
  for (int i = 0; i < n; ++i)
    toReturn[i] = pi[(baseIndex + i) % n];
  return toReturn;
}
/* ************************************************************************** */

/* ************************************************************************** */
std::vector<int> revert(const std::vector<int> &pi) {
  int n = pi.size();
  std::vector<int> toReturn = std::vector<int>(n);
  for (int i = 0; i < n; ++i)
    toReturn[i] = pi[n - i - 1];
  return toReturn;
}
/* ************************************************************************** */


/* ************************************************************************** */
// Do the real job
void process(const Parameters parameters) {

  int distance = 0;
  int minimumDistance = INT_MAX;
  int n = parameters.pi.size();

  std::vector<int> pi1;
  std::vector<int> pi2;

  std::cout << "Input permutation: " << parameters.pi[0];
  for (int i = 1; i < n; ++i) {
    std::cout << "," << parameters.pi[i];
  }
  std::cout << std::endl;

  for (int i = 0; i < n; ++i) {
    pi1 = rotate(parameters.pi, i);
    distance = getDistance(pi1);
    if (minimumDistance > distance)
      minimumDistance = distance;

    pi2 = revert(pi1);
    distance = getDistance(pi2);
    if (minimumDistance > distance)
      minimumDistance = distance;
  }

  std::cout << "Distance: " << minimumDistance << std::endl;
}
/* ************************************************************************** */


/* ************************************************************************** */
// Main program
int main (int argc, char* argv[]) {
  process(processArguments(argc, argv));
  return 0;
}
/* ************************************************************************** */
