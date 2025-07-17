
#pragma once
#ifndef CVECTORSUITE_CVARIANT_H
#define CVECTORSUITE_CVARIANT_H
#define _CRT_SECURE_NO_WARNINGS 1

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>

typedef enum Types {
    TYPE_NULL,           
    TYPE_BOOL,           
    TYPE_INT8,           
    TYPE_INT16,          
    TYPE_INT32,          
    TYPE_INT64,          
    TYPE_UINT8,          
    TYPE_UINT16,         
    TYPE_UINT32,         
    TYPE_UINT64,         
    TYPE_FLOAT,          
    TYPE_DOUBLE,         
    TYPE_LONG_DOUBLE,    
    TYPE_POINTER,        
    TYPE_STRING,         
    TYPE_STRUCT,         
    TYPE_ENUM,           
    TYPE_FUNCTION,       
    TYPE_CUSTOM          
} dataType;

typedef struct Variant CVariant;

typedef struct VStruct {
    void* data;
    const char* type_name;
} VStruct;

typedef struct VEnum {
    int8_t value;
    const char* type_name;
} VEnum;

typedef void (*destructorFunc)(void *);

typedef struct VCustom {
    void* data;
    const char* type_name;
    destructorFunc destructor;
} VCustom;

struct Variant {
    void*    value;     
    uint8_t  data_type; 
};

#include "CDebug.h"

const char* _getTypeName(dataType d_type);
const char* _varTypeName(CVariant* variant);
#define varTypeName(variant)    _varTypeName(&variant)

CVariant _varEmpty(void);
CVariant _varBool(bool value);
CVariant _varInt8(int8_t value);
CVariant _varUInt8(uint8_t value);
CVariant _varInt16(int16_t value);
CVariant _varUInt16(uint16_t value);
CVariant _varInt32(int32_t value);
CVariant _varUInt32(uint32_t value);
CVariant _varInt64(int64_t value);
CVariant _varUInt64(uint64_t value);
CVariant _varFloat(float* value);
CVariant _varDouble(double* value);
CVariant _varLongDouble(long double* value);
CVariant _varPointer(void* value);
CVariant _varString(const char* value);
CVariant _varStruct(void *value, const char *type_name);
CVariant _varEnum(int8_t value, const char *type_name);
CVariant _varFunction(void (*value)(void*));
CVariant _varCustom(void *value, const char *type_name, void (*destructor)(void *));

#define varBool(value)      _varBool(value)
#define varChar(value)      _varInt8(value)
#define varUChar(value)     _varUInt8(value)
#define varShort(value)     _varInt16(value)
#define varUShort(value)    _varUInt16(value)
#define varInt(value)       _varInt32(value)
#define varUInt(value)      _varUInt32(value)
#define varLongLong(value)  _varInt64(value)
#define varULongLong(value) _varUInt64(value)
#define varFloat(value)     _varFloat(&value)
#define varDouble(value)    _varDouble(&value)
#define varLongDouble(value) _varLongDouble(&value)
#define varPointer(value)   _varPointer((void*)value)
#define varString(value)    _varString(value)
#define varStruct(value, type_name)  _varStruct((void*)&value, type_name)
#define varEnum(value, type_name)    _varEnum((int8_t)value, type_name)
#define varFunction(function)        _varFunction(function)
#define varCustom(value, type_name, destructor)   _varCustom(value, type_name, destructor)

void _varBoolModifyValue(CVariant* variant, bool new_value);
void _varIntModifyValue(CVariant* variant, int64_t new_value);
void _varUIntModifyValue(CVariant* variant, uint64_t new_value);

#define varBoolModifyData(variant, new_value) _varIntModifyValue(&variant, new_value)
#define varIntModifyData(variant, new_value)  _varIntModifyValue(&variant, new_value)
#define varUIntModifyData(variant, new_value) _varUIntModifyValue(&variant, new_value)

void _varDestroy(CVariant* variant);
void _varDestroyString(CVariant* variant);
void _varDestroyPointer(CVariant* variant);
void _varDestroyStruct(CVariant* variant);
void _varDestroyEnum(CVariant* variant);
void _varDestroyCustom(CVariant* variant);

#define varDestroy(variant)         _varDestroy(&variant)

bool _varBoolValue(CVariant* variant);
int8_t _varInt8Value(CVariant* variant);
uint8_t _varUInt8Value(CVariant* variant);
int16_t _varInt16Value(CVariant* variant);
uint16_t _varUInt16Value(CVariant* variant);
int32_t _varInt32Value(CVariant* variant);
uint32_t _varUInt32Value(CVariant* variant);
int64_t _varInt64Value(CVariant* variant);
uint64_t _varUInt64Value(CVariant* variant);
float* _varFloatPtr(CVariant* variant);
double* _varDoublePtr(CVariant* variant);
long double* _varLongDoublePtr(CVariant* variant);
void* _varPtr(CVariant* variant);
const char* _varStringData(CVariant* variant);
void* _varStructPtr(CVariant* variant);

#define varBoolData(variant)       _varBoolValue(&variant)
#define varCharData(variant)       _varInt8Value(&variant)
#define varUCharData(variant)      _varUInt8Value(&variant)
#define varShortData(variant)      _varInt16Value(&variant)
#define varUShortData(variant)     _varUInt16Value(&variant)
#define varIntData(variant)        _varInt32Value(&variant)
#define varUIntData(variant)       _varUInt32Value(&variant)
#define varLongLongData(variant)   _varInt64Value(&variant)
#define varULongLongData(variant)  _varUInt64Value(&variant)
#define varFloatData(variant)      *(_varFloatPtr(&variant))
#define varDoubleData(variant)     *(_varDoublePtr(&variant))
#define varLongDoubleData(variant) *(_varLongDoublePtr(&variant))
#define varStringData(variant)     _varStringData(&variant)
#define varPointerData(variant, ptr_type)    (ptr_type *)_varPtr(&variant)
#define varStructPtr(variant, struct_type)   (struct_type *)_varStructPtr(&variant)
#define varStructData(variant, struct_type)  *(varStructPtr(variant, struct_type))

void _printVarData(CVariant* variant);
#define printVarData(variant)      _printVarData(&variant)

#define N_POS SIZE_MAX

#endif //CVECTORSUITE_CVARIANT_H
