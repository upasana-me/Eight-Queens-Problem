#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

void pboard( char board[ 8 ][ 8 ] );
void array( char board[ 8 ][ 8 ], int row, int col );
void process( char board[ 8 ][ 8 ], char board1[ 8 ][ 8 ] );

char board[ 8 ][ 8 ];
int t = 1;
int bcount = 0;

int main()
{
    int introw = 0, intcol = 0,row, col, ttrow, ttcol, trow, tcol, count = 0, n = 0;
    char move[ 8 ][ 8 ] = {
        "????????",
        "????????",
        "????????",
        "????????",
        "????????",
        "????????",
        "????????",
        "????????"
    };
    char board1[ 8 ][ 8 ];

    while( introw < 8 )
    {
        while( intcol < 8 )
        {
            memcpy( board, move, sizeof( move ) );
            row = introw;
            col = intcol;
           
            while( row < 8 )
            {
                while( col < 8 )
                {
                    trow = row;
                    tcol = col;
                    if( board[ trow ][ tcol ] == '?' )
                    {
                        array( board, trow, tcol );
                        count++;
                    }
                    col++;
                }
                row++;
                col = 0;
            }
           
            ttrow = 0;
            ttcol = 0;
            while( ttrow < 8 )
            {
                while( ttcol < 8 )
                {
                    if( board[ ttrow ][ ttcol ] == '?' )
                    {
                        array( board, ttrow, ttcol );
                        count++;
                    }
                    ttcol++;
                }
                ttrow++;
                ttcol = 0;
            }

            if( count >= 8 )
            {
                pboard( board );
                memcpy( board1, board, sizeof( board ) );
                process( board, board1 );
            }
            intcol++;
            count = 0;
        }

        if( count >= 8 )
        {
            pboard( board );
            memcpy( board1, board, sizeof( board ) );
            return 0;
            process( board, board1 );
        }
        introw++;
        intcol = 0;
        count = 0;
    }
   
    return 0;
}

void pboard( char board[ 8 ][ 8 ] )
{
    int trow = 0;
    int tcol = 0;

    bcount++;
    printf("%d. Required pattern is:\n",bcount);
    while( trow < 8 )
    {
        while( tcol < 8 )
        {
            printf("%c ",board[ trow ][ tcol ]);
            tcol++;
        }
        printf("\n");
        trow++;
        tcol = 0;
    }
    printf("\n");
}

void array( char board[ 8 ][ 8 ], int row, int col )
{
    int trow, tcol;

    trow = row;
    tcol = col;
    board[ trow ][ tcol ] = 'q';
    trow++;
    tcol++;
    while( ( trow < 8 ) && ( tcol < 8 ) )
    {
        board[ trow ][ tcol ] = '*';
        trow++;
        tcol++;
    }

    trow = row - 1;
    tcol = col - 1;
    while( ( trow >= 0 ) && ( tcol >= 0 ) )
    {
        board[ trow ][ tcol ] = '*';
        trow--;
        tcol--;
    }

    trow = row - 1;
    tcol = col + 1;
    while( ( trow >= 0 ) && ( tcol < 8 ) )
    {
        board[ trow ][ tcol ] = '*';
        trow--;
        tcol++;
    }

    trow = row + 1;
    tcol = col - 1;
    while( ( trow < 8 ) && ( tcol >= 0 ) )
    {
        board[ trow][ tcol ] = '*';
        trow++;
        tcol--;
    }

    trow = row - 1;
    tcol = col;
    while( trow >= 0 )
    {
        board[ trow ][ tcol ] = '*';
        trow--;
    }

    trow = row + 1;
    while( trow < 8 )
    {
        board[ trow ][ tcol ] = '*';
        trow++;
    }

    trow = row;
    tcol = col - 1;
    while( tcol >= 0 )
    {
        board[ trow ][ tcol ] = '*';
        tcol--;
    }

    tcol = col + 1;
    while( tcol < 8 )
    {
        board[ trow ][ tcol ] = '*';
        tcol++;
    }
}

void process( char board[ 8 ][ 8 ], char board1[ 8 ][ 8 ] )
{
    int trow = 0;
    int tcol = 0;
    int *array;
    int n = 0, i;

    array = (int *)malloc( 16*(sizeof( n ) ) );
   
    while( trow < 8 )
    {
        i = 0;
        while( i < 16 )
        {
            *( array + i ) = 8;
            i++;
        }

        while( tcol < 8 )
        {
            if( board[ trow ][ tcol ] == 'q' )
            {
                i = 0;
                while( i < 16 )
                {
                    if( ( *(array+i) == ( 7 - tcol ) ) || ( *(array+i) == tcol ) )
                        break;
                    i++;
                }
                if( i == 16 )
                    i--;
                if( ( *(array+i) != tcol ) && ( *(array+i) != ( 7 - tcol )  ) )
                {
                    board[ trow ][ 7 - tcol ] = 'q';
                    *(array+n) = 7 - tcol;
                    board[ trow ][ tcol ] = '*';
                    n++;
                    *(array+n) = tcol;
                    n++;
                }   
            }
            tcol++;
        }
        trow++;
        tcol = 0;
        n = 0;
    }

    pboard( board );

    if( t == 0 )
    {
        t = 1;
        return;
    }

    trow = 0;
    tcol = 0;
    n = 0;

    while(  tcol < 8 )
    {
        i = 0;
        while( i < 16 )
        {
            *( array + i ) = 8;
            i++;
        }

        while( trow < 8 )
        {
            if( board1[ trow ][ tcol ] == 'q' )
            {
                i = 0;
                while( i < 16 )
                {
                    if( ( *(array+i) == trow ) || ( *(array+i) == ( 7 - trow ) ) )
                        break;
                    i++;
                }
                if( i == 16 )
                    i--;
                if( ( *(array+i) != trow ) && ( *(array+i) != ( 7 -trow ) ) )
                {
                    board1[ 7 - trow ][ tcol ] = 'q';
                    board1[ trow ][ tcol ] = '*';
                    *(array+n) = trow;
                    n++;
                    *(array+n) = (7 - trow);
                    n++;
                }
            }
            trow++;
        }
        tcol++;
        trow = 0;
        n = 0;
    }
    pboard( board1 );

    t--;
    if( t == 0 )
    {
        process( board1, board );
    }
    t = 1;
}
