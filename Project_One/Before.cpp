//
//  Before.cpp
//  Project_One
//
//  Created by Srishti Dhawan on 7/5/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Before.h"

using namespace std;

Before::Before(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_Before[i][j] = '.';
        }
    }
}

bool Before::keepTrack(int r, int c)
{
    if ((r > 0 && r <= m_rows) && (c > 0 && c <= m_cols)) {
        if(m_Before[r-1][c-1] >= 'A' && m_Before[r-1][c-1] < 'Z') {
            m_Before[r-1][c-1] += 1;
        }
        if (m_Before[r-1][c-1] == '.') {
            m_Before[r-1][c-1] = 'A';
        }
        return true;
    }
    else
        return false;
}

void Before::printWhatWasBefore() const
{
    clearScreen();
    
    for(int i=0; i<m_rows; i++) {
        for (int j=0; j<m_cols; j++) {
            cout << m_Before[i][j];
        }
        cout <<endl;
    }
    cout <<endl;
}

