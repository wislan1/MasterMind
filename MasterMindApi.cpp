#include "MasterMindApi.h"


MasterMindApi::MasterMindApi( )
{
    //init randomization process, just one time
    srand( (unsigned int)time( NULL ) );

    InitData( );
}

int MasterMindApi::putColorInCurrentRow( ColorCodes colorCode, int col )
{
    int ret = putColor( colorCode, m_currentRow, col );
    switch ( ret )
    {
    case -1:
        debug( "setting color out of range\n" );
        return -1;
    case -2:
        debug( "setting color position out of range\n" );
        return -2;
    default:
        break;
    }
    return 1;
}

int MasterMindApi::checkAndReturnState( int& newRow, int feedback[ ROW_SIZE ] )
{
    int my_ret = -1;
    int ret = evaluateCurrentState( );
    switch ( ret )
    {
    case -1:
        my_ret = -1;
        debug( "Have to fill in all the fields in the row: ", m_currentRow, "\n" );
        return my_ret;
    case 2:
        my_ret = 2;
        debug( "game is over, all code has been guessed\n" );
        break;
    case 1:
        my_ret = 1;
        debug( "code has been guessed partialy\n" );
    default:
        break;
    }

    //assign the pegs feedback return array
    for ( int i = 0; i < ROW_SIZE; i++ )
    {
        feedback[ i ] = m_FeedbackPegs[ m_currentRow ][ i ];
    }

    // protect against the play field array index overflow
    ++m_currentRow >= NUMBER_OF_ROWS ? m_currentRow = ( NUMBER_OF_ROWS - 1 ) : false;
    newRow = m_currentRow;

    if ( m_currentRow >= ( NUMBER_OF_ROWS - 1 ) )
    {
        debug( "game is over, the available rows finished\n" );
    }
    return my_ret;
}

void MasterMindApi::getHiddenCode( ColorCodes hidden_code[ ROW_SIZE ] ) const
{
    for ( int i = 0; i < ROW_SIZE; i++ )
    {
        hidden_code[ i ] = m_HiddenCode[ i ];
    }
}

int MasterMindApi::getCurrentRow( ) const
{
    return m_currentRow;
}

void MasterMindApi::RestartGame( )
{
    InitData( );
}

//----private methods
int MasterMindApi::putColor( ColorCodes colorCode, int row, int col )
{
    if ( colorCode < COLOR_FIRST || colorCode >= NUMBER_OF_COLORS )
        return -1;
    if ( row < 0 || row >= NUMBER_OF_ROWS || col < 0 || col >= ROW_SIZE )
        return -2;
    m_PlayGrate[ row ][ col ] = colorCode;
    return 1;
}

void MasterMindApi::InitData( )
{
    m_currentRow = 0;
    //make a new hidden code to be broken
    for ( int i = 0; i < ROW_SIZE; i++ )
    {
        m_HiddenCode[ i ] = (ColorCodes)( rand( ) % ( (int)(NUMBER_OF_COLORS)-1 ) );
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
