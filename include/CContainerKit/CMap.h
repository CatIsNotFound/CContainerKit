
#pragma once
#ifndef CCONTAINERKIT_CMAP_H
#define CCONTAINERKIT_CMAP_H
#include "CArray.h"
#include "CPair.h"


typedef struct Map {
    CPair* pairs;
    uint64_t size;
    uint64_t capacity;
    KeyType key_type;
} CMap;

CMap mapInit(KeyType key_type, uint64_t size);
CMap mapList(CArray* keys, CArray* values, bool destroy_arrays);
void _destroyMap(CMap* map);

bool _insertToMap(CMap* map, void* key_name, CVariant value);
bool _removeFromMap(CMap* map, void* key_name);
bool _swapValuesFromMap(CMap* map, void* key_name1, void* key_name2);
bool _renameKeyFromMap(CMap* map, void* old_key_name, void* new_key_name);
bool _modifyValueFromMap(CMap* map, void* key_name, CVariant new_value);
bool _isKeyContainsFromMap(CMap* map, void* key_name);
CVariant* _getValueFromMap(CMap* map, void* key_name);
uint64_t _getSizeFromMap(CMap* map);
uint64_t _getCapacityFromMap(CMap* map);
CArray _getAllKeysFromMap(CMap* map);
CArray _getAllValuesFromMap(CMap* map);

bool _isEqualFromMap(CMap* map1, CMap* map2, bool (*compare_with_value)(CVariant, CVariant));
bool _mergeToMap(CMap* dest, CMap* src, bool destroy_src_map);

void _clearMap(CMap* map);
void _reverseMap(CMap* map, uint64_t new_capacity);
void _shrinkToFitMap(CMap* map, uint64_t new_capacity);

#define destroyMap(map)                             _destroyMap(&map)
#define insertToMap(map, key, value)                _insertToMap(&map, (void*)key, value)
#define removeFromMap(map, key)                     _removeFromMap(&map, (void*)key)
#define swapValuesFromMap(map, key1, key2)          _swapValuesFromMap(&map, (void*)key1, (void*)key2)
#define renameKeyFromMap(map, key, key_name)        _renameKeyFromMap(&map, (void*)key, (void*)key_name)
#define modifyValueFromMap(map, key, value)         _modifyValueFromMap(&map, (void*)key, value)
#define isKeyContainsFromMap(map, key)              _isKeyContainsFromMap(&map, (void*)key)
#define getValueFromMap(map, key)                   _getValueFromMap(&map, (void*)key)
#define getSizeFromMap(map)                         _getSizeFromMap(&map)
#define getCapacityFromMap(map)                     _getCapacityFromMap(&map)
#define getAllKeysFromMap(map)                      _getAllKeysFromMap(&map)
#define getAllValuesFromMap(map)                    _getAllValuesFromMap(&map)
#define isEuqalFromMap(map1, map2, cmp_with_value)  _isEqualFromMap(&map1, &map2, cmp_with_value)
#define mergeToMap(dest, src, destroy_src_map)      _mergeToMap(&dest, &src, destroy_src_map)
#define clearMap(map)                               _clearMap(&map)
#define reverseMap(map, new_capacity)               _reverseMap(&map, new_capacity)
#define shrinkToFitMap(map, new_capacity)           _shrinkToFitMap(&map, new_capacity)



#endif //CCONTAINERKIT_CMAP_H
