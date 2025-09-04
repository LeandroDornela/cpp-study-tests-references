#pragma once

template<typename CellType>
class Grid
{
private:
	CellType* _cells = nullptr;
	unsigned int _width = 0;
	unsigned int _height = 0;
	unsigned int _totalCells = 0;

	bool _debug = true;


public:
	Grid() = delete;

	Grid(const unsigned int& width, const unsigned int& height, const CellType& defaultCellValue) :
		_width(width),
		_height(height),
		_totalCells(width* height)
	{
		_cells = new CellType[_totalCells];

		for (unsigned int i = 0; i < _totalCells; i++)
		{
			_cells[i] = defaultCellValue;
		}

		if(_debug) std::cout << typeid(CellType).name() << " grid created with " << _totalCells << " total cells." << std::endl;
	}

	void ForEachCell(void(*function)(const CellType&))
	{
		for (unsigned int i = 0; i < _totalCells; i++)
		{
			function(_cells[i]);
		}
	}

	inline void TEMP_ForEachCell(void(*function)(CellType&))
	{
		for (unsigned int i = 0; i < _totalCells; i++)
		{
			function(_cells[i]);
		}
	}

	void TEST_ForEachSetDef(const CellType& defaultCellValue)
	{
		for (unsigned int i = 0; i < _totalCells; i++)
		{
			_cells[i] = defaultCellValue;
		}
	}

	const CellType* GetCell(int i, int j)
	{
		return &_cells[0];
	}
	
	~Grid()
	{
		delete[] _cells;
		if (_debug) std::cout << typeid(CellType).name() << " cell destroyed." << std::endl;
	}
};