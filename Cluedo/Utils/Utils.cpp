#include "Utils.h"
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

namespace Utils
{
    int generateRandomNumber(int p_minNumber, int p_maxNumber)
    {
        /* generate random number between 1 and 10: */
        int randomNumber = 0;
        if (p_maxNumber > 0)
        {
            randomNumber = rand() % p_maxNumber + p_minNumber;
        }

        return randomNumber;
    }
}