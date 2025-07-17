#include "CContainerKit/CVariant.h"

const char* _getTypeName(dataType d_type) {
    switch (d_type) {
        case TYPE_BOOL:
            return "bool";
        case TYPE_INT8:
            return "signed char (int8)";
        case TYPE_UINT8:
            return "unsigned char (uint8)";
        case TYPE_INT16:
            return "short (int16)";
        case TYPE_UINT16:
            return "unsigned short (uint16)";
        case TYPE_INT32:
            return "int (int32)";
        case TYPE_UINT32:
            return "unsigned int (uint32)";
        case TYPE_INT64:
            return "long long int (int64)";
        case TYPE_UINT64:
            return "unsigned long long int (uint64)";
        case TYPE_FLOAT:
            return "float";
        case TYPE_DOUBLE:
            return "double";
        case TYPE_LONG_DOUBLE:
            return "long double";
        case TYPE_POINTER:
            return "void* (pointer)";
        case TYPE_STRING:
            return "string (const char *)";
        case TYPE_STRUCT:
            return "struct";
        case TYPE_ENUM:
            return "enum";
        case TYPE_FUNCTION:
            return "function";
        case TYPE_CUSTOM:
            return "custom";
        default:
            return "undefined";
    }
}

const char* _varTypeName(CVariant* variant) {
    if (variant->data_type == TYPE_STRUCT) {
        return ((VStruct *)(variant->value))->type_name;
    } else if (variant->data_type == TYPE_ENUM) {
        return ((VEnum *)(variant->value))->type_name;
    } else if (variant->data_type == TYPE_CUSTOM) {
        return ((VCustom *)(variant->value))->type_name;
    } else {
        return _getTypeName(variant->data_type);
    }
}

CVariant _varEmpty(void) {
    CVariant new_variant;
    new_variant.data_type = TYPE_NULL;
    new_variant.value = (void*)0;
    return new_variant;
}

CVariant _varBool(bool value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_BOOL;
    new_variant.value = (void*)value;
    return new_variant;
}

CVariant _varInt8(int8_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_INT8;
    new_variant.value = (void*)(int64_t)value;
    return new_variant;
}

CVariant _varUInt8(uint8_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_UINT8;
    new_variant.value = (void*)(int64_t)value;
    return new_variant;
}

CVariant _varInt16(int16_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_INT16;
    new_variant.value = (void*)(int64_t)value;
    return new_variant;
}

CVariant _varUInt16(uint16_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_UINT16;
    new_variant.value = (void*)(uint64_t)value;
    return new_variant;
}

CVariant _varInt32(int32_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_INT32;
    new_variant.value = (void*)(int64_t)value;
    return new_variant;
}

CVariant _varUInt32(uint32_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_UINT32;
    new_variant.value = (void*)(uint64_t)value;
    return new_variant;
}

CVariant _varInt64(int64_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_INT64;
    new_variant.value = (void*)(int64_t)value;
    return new_variant;
}

CVariant _varUInt64(uint64_t value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_UINT64;
    new_variant.value = (void*)(uint64_t)value;
    return new_variant;
}

CVariant _varFloat(float* value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_FLOAT;
    new_variant.value = (void*)value;
    return new_variant;
}

CVariant _varDouble(double* value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_DOUBLE;
    new_variant.value = (void*)value;
    return new_variant;
}

CVariant _varLongDouble(long double* value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_LONG_DOUBLE;
    new_variant.value = (void*)value;
    return new_variant;
}

CVariant _varPointer(void* value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_POINTER;
    new_variant.value = value;
    return new_variant;
}

CVariant _varString(const char* value) {
    CVariant new_variant;
    new_variant.data_type = TYPE_STRING;
    new_variant.value = (void*)value;
    return new_variant;
}

CVariant _varStruct(void *value, const char *type_name) {
    CVariant new_variant;
    new_variant.data_type = TYPE_STRUCT;
    VStruct* new_struct = malloc(sizeof(VStruct));
    new_struct->data = (void*)value;
    new_struct->type_name = type_name;
    new_variant.value = (void*)new_struct;
    return new_variant;
}

CVariant _varEnum(int8_t value, const char *type_name) {
    CVariant new_variant;
    new_variant.data_type = TYPE_ENUM;
    VEnum* new_enum = malloc(sizeof(VEnum));
    new_enum->value = value;
    new_enum->type_name = type_name;
    new_variant.value = (void*)new_enum;
    return new_variant;
}

CVariant _varFunction(void (*value)(void*)) {
    CVariant new_variant;
    new_variant.data_type = TYPE_ENUM;
    new_variant.value = (void *) value;
    return new_variant;
}

CVariant _varCustom(void *value, const char *type_name, void (*destructor)(void *)) {
    CVariant new_variant;
    new_variant.data_type = TYPE_CUSTOM;
    VCustom* new_custom = malloc(sizeof(VCustom));
    new_custom->data = value;
    new_custom->type_name = type_name;
    new_custom->destructor = destructor;
    return new_variant;
}

void _varBoolModifyValue(CVariant* variant, bool new_value) {
    if (variant->data_type == TYPE_BOOL) {
        variant->value = (void*)new_value;
    }
}

void _varIntModifyValue(CVariant* variant, int64_t new_value) {
    if (variant->data_type >= TYPE_INT8 && variant->data_type <= TYPE_INT64) {
        variant->value = (void*)new_value;
    }
}

void _varUIntModifyValue(CVariant* variant, uint64_t new_value) {
    if (variant->data_type >= TYPE_UINT8 && variant->data_type <= TYPE_UINT64) {
        variant->value = (void*)new_value;
    }
}

void _varDestroy(CVariant* variant) {
    if (variant) {
        _varDestroyString(variant);
        _varDestroyPointer(variant);
        _varDestroyStruct(variant);
        _varDestroyEnum(variant);
        _varDestroyCustom(variant);
    }
}

void _varDestroyString(CVariant* variant) {
    if (variant->data_type == TYPE_STRING) {
        char* del_str = (char*) variant->value;
        free(del_str);
    }
}

void _varDestroyPointer(CVariant* variant) {
    if (variant->data_type == TYPE_POINTER) {
        free(variant->value);
    }
}

void _varDestroyStruct(CVariant* variant) {
    if (variant->data_type == TYPE_STRUCT) {
        if (variant->value) {
            VStruct* v_struct = (VStruct*)(variant->value);
            free(v_struct);
        }
    }
}

void _varDestroyEnum(CVariant* variant) {
    if (variant->data_type == TYPE_ENUM) {
        if (variant->value) {
            VEnum* v_enum = (VEnum*)(variant->value);
            free(v_enum);
        }
    }
}

void _varDestroyCustom(CVariant* variant) {
    if (variant->data_type == TYPE_CUSTOM) {
        if (variant->value) {
            VCustom *custom = (VCustom *) (variant->value);
            custom->destructor(variant->value);
            free(custom);
        }
    }
}

bool _varBoolValue(CVariant* variant) {
    if (variant && variant->data_type == TYPE_BOOL) {
        return (bool)variant->value;
    }
    return false;
}

int8_t _varInt8Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_INT8) {
        return (int8_t)(int64_t)variant->value;
    }
    return 0;
}

uint8_t _varUInt8Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_UINT8) {
        return (uint64_t)variant->value;
    }
    return 0;
}

int16_t _varInt16Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_INT16) {
        return (int16_t)(int64_t)variant->value;
    }
    return 0;
}

uint16_t _varUInt16Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_UINT16) {
        return (uint16_t)(uint64_t)variant->value;
    }
    return 0;
}

int32_t _varInt32Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_INT32) {
        return (int32_t)(int64_t)variant->value;
    }
    return 0;
}

uint32_t _varUInt32Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_UINT32) {
        return (uint32_t)(uint64_t)variant->value;
    }
    return 0;
}

int64_t _varInt64Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_INT64) {
        return (int64_t)variant->value;
    }
    return 0;
}

uint64_t _varUInt64Value(CVariant* variant) {
    if (variant && variant->data_type == TYPE_UINT64) {
        return (uint64_t)variant->value;
    }
    return 0;
}

float* _varFloatPtr(CVariant* variant) {
    if (variant && variant->data_type == TYPE_FLOAT) {
        return (float*)variant->value;
    }
    return NULL;
}

double* _varDoublePtr(CVariant* variant) {
    if (variant && variant->data_type == TYPE_DOUBLE) {
        return (double*)variant->value;
    }
    return NULL;
}

long double* _varLongDoublePtr(CVariant* variant) {
    if (variant && variant->data_type == TYPE_LONG_DOUBLE) {
        return (long double*)variant->value;
    }
    return NULL;
}

void* _varPtr(CVariant* variant) {
    if (variant) {
        return variant->value;
    }
    return NULL;
}

const char* _varStringData(CVariant* variant) {
    if (variant && variant->data_type == TYPE_STRING) {
        return (const char*)variant->value;
    }
    return NULL;
}

void* _varStructPtr(CVariant* variant) {
    if (variant && variant->data_type == TYPE_STRUCT) {
        VStruct* v_struct = (VStruct*)variant->value;
        return v_struct->data;
    }
    return NULL;
}

void _printVarData(CVariant* variant) {
    switch (variant->data_type) {
        case TYPE_BOOL:
            printf("%s", (_varBoolValue(variant) ? "true" : "false")); break;
        case TYPE_INT8:
            printf("%d", _varInt8Value(variant)); break;
        case TYPE_UINT8:
            printf("%d", _varUInt8Value(variant)); break;
        case TYPE_INT16:
            printf("%d", _varInt16Value(variant)); break;
        case TYPE_UINT16:
            printf("%d", _varUInt16Value(variant)); break;
        case TYPE_INT32:
            printf("%d", _varInt32Value(variant)); break;
        case TYPE_UINT32:
            printf("%d", _varUInt32Value(variant)); break;
        case TYPE_INT64:
            printf("%ld", _varInt64Value(variant)); break;
        case TYPE_UINT64:
            printf("%ld", _varUInt64Value(variant)); break;
        case TYPE_FLOAT:
            if (_varFloatPtr(variant)) printf("%f", *_varFloatPtr(variant));
            else printf("(NULL)");
            break;
        case TYPE_DOUBLE:
            if (_varDoublePtr(variant)) printf("%lf", *_varDoublePtr(variant));
            else printf("(NULL)");
            break;
        case TYPE_LONG_DOUBLE:
            if (_varLongDoublePtr(variant)) printf("%Lf", *_varLongDoublePtr(variant));
            else printf("(NULL)");
            break;
        case TYPE_POINTER:
            printf("%#x (pointer)", (uint32_t)(uint64_t)_varPtr(variant)); break;
        case TYPE_STRING:
            printf("%s", _varStringData(variant)); break;
        case TYPE_STRUCT:
            printf("%#x (struct)", (uint32_t)(uint64_t)_varPtr(variant)); break;
        case TYPE_ENUM:
            printf("%d (enum)", _varUInt8Value(variant)); break;
        case TYPE_FUNCTION:
            printf("%#x (function)", (uint32_t)(uint64_t)_varPtr(variant)); break;
        case TYPE_CUSTOM:
            printf("%#x (custom)", (uint32_t)(uint64_t)_varPtr(variant)); break;
        default:
            printf("(NULL)"); break;
    }
}
