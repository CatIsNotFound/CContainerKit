
#include "CContainerKit/CMap.h"

void _expandCapacity(CMap* map) {
    uint64_t space = (map->capacity == 0 ? 1 : map->capacity);
    _reverseMap(map, space);
}

CMap mapInit(KeyType key_type, uint64_t size) {
    CMap new_map;
    new_map.key_type = key_type;
    new_map.size = size;
    new_map.capacity = size * 2;
    new_map.pairs = (CPair*) calloc(new_map.capacity + 1, sizeof(CPair));
    return new_map;
}

CMap mapList(CArray* keys, CArray* values, bool destroy_arrays) {
    if (!keys || !values) return mapInit(KEY_INT, 0);
    if (keys->length != values->length) return mapInit(KEY_INT, 0);
    CMap new_map;
    new_map.size = keys->length;
    new_map.capacity = new_map.size * 2;
    dataType origin_datatype = keys->elements->data_type;
    size_t _idx = 1;
    for (; _idx < keys->length; ++_idx) {
        if (keys->elements[_idx].data_type != origin_datatype) break;
    }
    if (_idx < keys->length) return mapInit(KEY_INT, 0);
    new_map.pairs = (CPair*) calloc(new_map.capacity + 1, sizeof(CPair));
    for (_idx = 0; _idx < keys->length; ++_idx) {
        new_map.pairs[_idx].key = keys->elements[0].value;
        new_map.pairs[_idx].value = values->elements[0];
    }
    if (destroy_arrays) {
        _destroyArray(keys);
        _destroyArray(values);
    }
    return new_map;
}

void _destroyMap(CMap* map) {
    if (map->pairs) {
        for (uint64_t _idx = 0; _idx < map->size; ++_idx) {
            if (map->key_type >= KEY_POINTER) {
                free(map->pairs[_idx].key);
            }
            varDestroy(map->pairs[_idx].value);
        }
    }
    map->key_type = 0;
    map->size = 0;
    map->capacity = 0;
}

bool _insertToMap(CMap* map, void* key_name, CVariant value) {

}

bool _removeFromMap(CMap* map, void* key_name) {

}

bool _swapValuesFromMap(CMap* map, void* key_name1, void* key_name2) {

}

bool _renameKeyFromMap(CMap* map, void* old_key_name, void* new_key_name) {

}

bool _modifyValueFromMap(CMap* map, void* key_name, CVariant new_value) {

}

bool _isKeyContainsFromMap(CMap* map, void* key_name) {

}

CVariant* _getValueFromMap(CMap* map, void* key_name) {

}

uint64_t _getSizeFromMap(CMap* map) {

}

uint64_t _getCapacityFromMap(CMap* map) {

}

CArray _getAllKeysFromMap(CMap* map) {

}

CArray _getAllValuesFromMap(CMap* map) {

}

bool _isEqualFromMap(CMap* map1, CMap* map2, bool (*compare_with_value)(CVariant, CVariant)) {

}

bool _mergeToMap(CMap* dest, CMap* src, bool destroy_src_map) {

}

void _clearMap(CMap* map) {

}

void _reverseMap(CMap* map, uint64_t new_capacity) {
    if (map->capacity < new_capacity) return;
    CPair* new_space = (CPair*) calloc(new_capacity, sizeof(CPair));
    for (uint64_t i = 0; i < map->size; ++i) {
        new_space[i] = map->pairs[i];
    }
    free(map->pairs);
    map->pairs = new_space;
    map->capacity = new_capacity;
}

void _shrinkToFitMap(CMap* map, uint64_t new_capacity) {
    CPair* new_space = (CPair*) calloc(new_capacity, sizeof(CPair));
    uint64_t real_capacity = (map->capacity > new_capacity ? new_capacity : map->capacity);
    for (uint64_t i = 0; i < real_capacity; ++i) {
        new_space[i] = map->pairs[i];
    }
    free(map->pairs);
    map->pairs = new_space;
    map->capacity = new_capacity;
}


