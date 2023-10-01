#include "Sort.h"

void ShellSort(std::vector<int*> vect)
{
  	for (size_t gap = vect.size() / 2; gap > 0; gap /= 2) {
		for (size_t f = gap; f < vect.size(); f++) {
			for (size_t s = f; s >= gap; s -= gap) {
				if (vect[s] < vect[s - gap])
				{
					std::swap(vect[s], vect[s - gap]);
				}
				else { break; };
			}
		}
	}
}
