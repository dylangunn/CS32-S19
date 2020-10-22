//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#include "History.h"
#include "globals.h"


History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int i = 1; i <= nRows; i++)
	{
		for (int j = 1; j <= nCols; j++)
		{
			m_arena[i][j] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r < 1 || c < 1 || r > m_rows || c > m_cols)
	{
		return false;
	}

	if (m_arena[r][c] == '.')
	{
		m_arena[r][c] = 'A';
	}
	else if (m_arena[r][c] == 'Z')
	{
		return true;
	}
	else
	{
		m_arena[r][c]++;
	}
	return true;
	
}

void History::display() const
{
	clearScreen();
	for (int i = 1; i <= m_rows; i++)
	{
		for (int j = 1; j <= m_cols; j++)
		{
			cout << m_arena[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
