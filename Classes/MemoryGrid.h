//
//  MemoryGrid.h
//  Game3
//
//  Created by Stepanov Ilia on 01/06/15.
//
//

#ifndef __Game3__MemoryGrid__
#define __Game3__MemoryGrid__

#include "CommonMap.h"

template <typename TypeName>
class MemoryGrid
{
public:
	
	MemoryGrid()
	{
		_data = NULL;
	}
	
	~MemoryGrid()
	{
		delete [] _data;
	}
	
	void create(const BaseMap * map)
	{
		_size = map->getMapSizeX() * map->getMapSizeY();
		_data = new TypeName[_size];
	}
	
	void clear(int defaultValue = 0)
	{
		memset(_data,
			   defaultValue,
			   (size_t)(_size * sizeof(TypeName)));
	}
	
	inline void set(int memId, TypeName& val)
	{
		_data[memId] = val;
	}
	
	inline TypeName * getData()
	{
		return _data;
	}
	
	const TypeName& operator[](const int memId) const
	{
		return _data[memId];
	}
	
	TypeName& operator[](const int memId)
	{
		return _data[memId];
	}
	
private:
	
	TypeName * _data;
	int _size;
	
};

#endif /* defined(__Game3__MemoryGrid__) */
