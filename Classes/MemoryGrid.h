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
		_map = NULL;
	}
	
	~MemoryGrid()
	{
		delete [] _data;
	}
	
	void create(const BaseMap * map)
	{
		_data = new TypeName[map->getMapSizeX() * map->getMapSizeY()];
		_map = map;
	}
	
	void clear(int defaultValue = 0)
	{
		memset(_data,
			   defaultValue,
			   (size_t)(_map->getMapSizeX() * _map->getMapSizeY() * sizeof(TypeName)));
	}
	
	inline void set(int memId, TypeName& val)
	{
		_data[memId] = val;
	}
	
	inline TypeName * getData()
	{
		return _data;
	}
	
	TypeName& operator[](const int memId)
	{
		return _data[memId];
	}
	
	/*inline TypeName& getDataByID(int memId)
	{
		return _data[memId];
	}*/
	
private:
	
	TypeName * _data;
	const BaseMap * _map;
	
};

#endif /* defined(__Game3__MemoryGrid__) */
