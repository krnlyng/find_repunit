/*
 *  Copyright (C) 2015 Franz-Josef Anton Friedrich Haider
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#if USE_GMP
#include <gmpxx.h>
#endif

using namespace std;

#if USE_GMP
typedef mpz_class number;
#else
typedef unsigned long long int number;
#endif

number build_repunit(const number &index, const number &base)
{
    number ret = 1;
    number current_base = base;

    for(number i = 1;i < index;i++)
    {
        ret += current_base;
        current_base *= base;
    }

    return ret;
}

pair<number, number> find_repunit(const number &n)
{
    number index = 1;
    number base = 2;
    number step_base = base;
    number step_index = 1;
    number current_repunit;

    // diagonalisation method
    for(number step = 1;;step += 2)
    {
        step_base = 2;
        step_index = index;

        // down
        for(number d = 0;d < step;d++)
        {
            current_repunit = build_repunit(step_index, step_base);

            if(current_repunit == n)
            {
                return make_pair(step_index, step_base);
            }

            step_index--;
            step_base++;
        }

        // next diagonal
        base++;
        index++;

        step_base = base;
        step_index = 1;

        // right
        for(number d = 0;d < step+1;d++)
        {
            current_repunit = build_repunit(step_index, step_base);

            if(current_repunit == n)
            {
                return make_pair(step_index, step_base);
            }

            step_index++;
            step_base--;
        }

        // next diagonal
        base++;
        index++;
    }

    return std::make_pair(0, 0);
}

void usage(char *name)
{
    cout << "usage:" << endl;
    cout << name << " number" << endl;
    cout << "\tnumber\tIs the number for which its repunit representation is to be" << endl;
    cout << "\t\tsearched." << endl;
}

int main(int argc, char *argv[])
{
    number n;

    if(argc != 2)
    {
        usage(argv[0]);
        return -1;
    }

#if USE_GMP
    n = argv[1];
#else
    n = strtoull(argv[1], NULL, 10);
#endif

    pair<number, number> r = find_repunit(n);

    if(r.first == 0 && r.second == 0)
    {
        cout << "No repunit representation for this number exists." << endl;
    }
    else
    {
        cout << "The repunit representation of the given number is" << endl;
        cout << "I_{0," << r.first << "," << r.second << "}." << endl;
    }

    return 0;
}

