#pragma once

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

//--- logging stuff ---
#define PRINTOUT_YES 1

using namespace std;

template <typename T>
void debug( T t )
{
#if PRINTOUT_YES == 1
    cerr << t; //<< std::endl;
#endif
}

template<typename T, typename... Args>
void debug( T t, Args... args )
{
#if PRINTOUT_YES == 1
    cerr << t;
    debug( args... );
#endif
}
//--- logging stuff ---

//--- color codes
enum class ColorCodes
{
    COLOR_RED = 0,  // first color
    COLOR_GREEN = 1,
    COLOR_BLUE = 2,
    COLOR_CYAN = 3,
    COLOR_MAGENTA = 4,
    COLOR_YELLOW = 5,
    NO_COLOR        // make sure it is always last element
};


class MasterMindApi
{
public:
    //---sizes of play field
    static const int ROW_SIZE = 4;
    static const int NUMBER_OF_ROWS = 10;
    //---sizes of play field
    //---value in a pegs feedback aray
    static const int EXACT_MATCH = 2;    //field matched exactly according to the color and positon
    static const int PARTIAL_MATCH = 1;  //field matched only according to the color but ot positon
    static const int NO_VALUE = -1;      //field value after initialisation
    //---value in a pegs feedback aray

public:
    //constructor
    MasterMindApi( );

    int putColorInCurrentRow( ColorCodes colorCode, int col );
/*
 * @brief Function checks mating level with call to the checkAndReturnState(...)
 *        Increments m_currentRow var.
 * @param out "newRow" - new row on play field
 * @param out "feedback" - array of ROW_SIZE size that contains pegs feedback after current quess
 * 
 * @return -1 - when not all field yet have been selected color
 *          2 - when all code as been guessed
 *          1 - when not all code has been guessed
 */
    int checkAndReturnState( int& newRow, int feedback[ ROW_SIZE ] );

/*
 * @brief gets array with hidden code
 * 
 * @param out "hidden_code" - array of ROW_SIZE size that contains the numbers of color code to be guessed
 *
 */
    void getHiddenCode( ColorCodes hidden_code[ ROW_SIZE ] ); const

    int getCurrentRow( ) const
    {
        return m_currentRow;
    }

    void RestartGame( );

private:
    int evaluateCurrentState( )
    {
        //reset the pegs feedback array
        for ( int i = 0; i < ROW_SIZE; i++ )
        {
            m_FeedbackPegs[ m_currentRow ][ i ] = NO_VALUE;
        }

        int number_of_exact_matches = 0;
        for ( int i = 0; i < ROW_SIZE; i++ )
        {
            if ( m_PlayGrate[ m_currentRow ][ i ] == ColorCodes::NO_COLOR )
            {
                debug( "pos: ", i, ", in row: ", m_currentRow, " is not filled in\n" );
                return -1;
            }
            if ( m_PlayGrate[ m_currentRow ][ i ] == m_HiddenCode[ i ] )
            {
                m_FeedbackPegs[ m_currentRow ][ i ] = EXACT_MATCH;
                number_of_exact_matches++;
            }
        }
        //all colors matched excactly
        if ( number_of_exact_matches == ROW_SIZE )
            return 2;

        //find remaining, not exact matches
        for ( int i = 0; i < ROW_SIZE; i++ )
        {
            if ( m_FeedbackPegs[ m_currentRow ][ i ] == EXACT_MATCH )
                continue;

            for ( int j = 0; j < ROW_SIZE; j++ )
            {
                if ( i == j || m_FeedbackPegs[ m_currentRow ][ j ] == EXACT_MATCH )
                    continue;

                if ( m_PlayGrate[ m_currentRow ][ i ] == m_HiddenCode[ j ] )
                {
                    m_FeedbackPegs[ m_currentRow ][ i ] = PARTIAL_MATCH;
                }
            }
        }
        return 1;
    }

    int putColor( ColorCodes colorCode, int row, int col )
    {
        if ( colorCode < COLOR_FIRST || colorCode >= NUMBER_OF_COLORS )
            return -1;
        if ( row < 0 || row >= NUMBER_OF_ROWS || col < 0 || col >= ROW_SIZE )
            return -2;
        m_PlayGrate[ row ][ col ] = colorCode;
        return 1;
    }

    void InitData( )
    {
        m_currentRow = 0;
        //make a new hidden code to be broken
        for (int i=0; i<ROW_SIZE; i++ )
        {
            m_HiddenCode[ i ] = (ColorCodes)(rand( ) % ((int)(NUMBER_OF_COLORS)-1));
        }

        for ( int i = 0; i < NUMBER_OF_ROWS; i++ )
        {
            for ( int j = 0; j < ROW_SIZE; j++ )
            {
                m_PlayGrate[ i ][ j ] = ColorCodes::NO_COLOR;
                m_FeedbackPegs[ i ][ j ] = NO_VALUE;
            }
        }
    }

private:
    static const ColorCodes NUMBER_OF_COLORS = ColorCodes::NO_COLOR;
    static const ColorCodes COLOR_FIRST = ColorCodes::COLOR_RED;      //make sure this is alwais first entry from the ColorCodes class
    ColorCodes m_HiddenCode[ ROW_SIZE ];
    ColorCodes m_PlayGrate[ NUMBER_OF_ROWS][ ROW_SIZE ];
    int m_FeedbackPegs[ NUMBER_OF_ROWS ][ ROW_SIZE ];
    int m_currentRow = 0;
};

