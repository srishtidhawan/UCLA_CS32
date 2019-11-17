//
//  Before.h
//  Project_One
//
//  Created by Srishti Dhawan on 7/5/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#ifndef Before_h
#define Before_h

#include "globals.h"

class Before
{
public:
    Before(int nRows, int nCols);
    bool keepTrack(int r, int c);
    void printWhatWasBefore() const;
private:
    int m_rows;
    int m_cols;
    char m_Before[MAXROWS][MAXCOLS];
    
};


#endif /* Before_h */
