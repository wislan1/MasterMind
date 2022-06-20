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
    //---possible values in a pegs feedback aray
    static const int EXACT_MATCH = 2;    //field matched exactly according to the color and positon
    static const int PARTIAL_MATCH = 1;  //field matched only according to the color but ot positon
    static const int NO_VALUE = -1;      //field value after initialisation
    //---possible values in a pegs feedback aray

public:
    //default constructor
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
 */
    void getHiddenCode( ColorCodes hidden_code[ ROW_SIZE ] ) const;
    inline int getCurrentRow( ) const;
    void RestartGame( );

private:
    /*
     * @brief Based on the m_PlayGrate[m_currentRow][...] choises and m_HiddenCode[...] values, the function files in the m_FeedbackPegs array
     *
     * @return "-1" - when some of the positions in m_PlayGrate[m_currentRow][i] is not yet choosen
     *         " 2" - when there is BINGO, whole hidden code has been guessed
     *         " 1" - when there is at least one not EXACT_MATCH, which may be either (PARTIAL_MATCH or NO_VALUE)
     */
    int evaluateCurrentState();
    int putColor( ColorCodes colorCode, int row, int col );
    void InitData();

private:
    static const ColorCodes NUMBER_OF_COLORS = ColorCodes::NO_COLOR;
    static const ColorCodes COLOR_FIRST = ColorCodes::COLOR_RED;      //make sure this is always first entry in the ColorCodes class
    ColorCodes m_HiddenCode[ ROW_SIZE ];
    ColorCodes m_PlayGrate[ NUMBER_OF_ROWS][ ROW_SIZE ];
    int m_FeedbackPegs[ NUMBER_OF_ROWS ][ ROW_SIZE ];
    int m_currentRow = 0;
};
