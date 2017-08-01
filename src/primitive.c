// Helper functions to support primitive types.

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "primitive.h"

/*******************************************************************************************/

// Global variables.

union primitive_value primitive_null = { .pointerValue = NULL };

/*******************************************************************************************/

// Constructors.

union primitive_value primitive_getBool(bool boolValue) {
    union primitive_value v = { .boolValue = boolValue };
    return v;
}

union primitive_value primitive_getByte(int8_t byteValue) {
    union primitive_value v = { .byteValue = byteValue };
    return v;
}

union primitive_value primitive_getShort(int16_t shortValue) {
    union primitive_value v = { .shortValue = shortValue };
    return v;
}

union primitive_value primitive_getInt(int32_t intValue) {
    union primitive_value v = { .intValue = intValue };
    return v;
}

union primitive_value primitive_getLong(int64_t longValue) {
    union primitive_value v = { .longValue = longValue };
    return v;
}

union primitive_value primitive_getUByte(uint8_t ubyteValue) {
    union primitive_value v = { .ubyteValue = ubyteValue };
    return v;
}

union primitive_value primitive_getUShort(uint16_t ushortValue) {
    union primitive_value v = { .ushortValue = ushortValue };
    return v;
}

union primitive_value primitive_getUInt(uint32_t uintValue) {
    union primitive_value v = { .uintValue = uintValue };
    return v;
}

union primitive_value primitive_getULong(uint64_t ulongValue) {
    union primitive_value v = { .ulongValue = ulongValue };
    return v;
}

union primitive_value primitive_getFloat(float floatValue) {
    union primitive_value v = { .floatValue = floatValue };
    return v;
}

union primitive_value primitive_getDouble(double doubleValue) {
    union primitive_value v = { .doubleValue = doubleValue };
    return v;
}

union primitive_value primitive_getPointer(void *pointerValue) {
    union primitive_value v = { .pointerValue = pointerValue };
    return v;
}

union primitive_value primitive_getChar(char charValue) {
    union primitive_value v = { .charValue = charValue };
    return v;
}

union primitive_value primitive_getWChar(wchar_t wcharValue) {
    union primitive_value v = { .wcharValue = wcharValue };
    return v;
}

union primitive_value primitive_getString(char *stringValue) {
    union primitive_value v = { .stringValue = stringValue };
    return v;
}

union primitive_value primitive_getWString(wchar_t *wstringValue) {
    union primitive_value v = { .wstringValue = wstringValue };
    return v;
}

/*******************************************************************************************/

// Free.

void primitive_free(union primitive_value value) {
    free(value.pointerValue);
}

/*******************************************************************************************/

// Compare values.

int32_t primitive_cmpBool(union primitive_value value1, union primitive_value value2) {
    return (value1.boolValue < value2.boolValue) ? -1 : (value1.boolValue == value2.boolValue) ? 0 : 1;
}

int32_t primitive_cmpByte(union primitive_value value1, union primitive_value value2) {
    return (value1.byteValue < value2.byteValue) ? -1 : (value1.byteValue == value2.byteValue) ? 0 : 1;
}

int32_t primitive_cmpShort(union primitive_value value1, union primitive_value value2) {
    return (value1.shortValue < value2.shortValue) ? -1 : (value1.shortValue == value2.shortValue) ? 0 : 1;
}

int32_t primitive_cmpInt(union primitive_value value1, union primitive_value value2) {
    return (value1.intValue < value2.intValue) ? -1 : (value1.intValue == value2.intValue) ? 0 : 1;
}

int32_t primitive_cmpLong(union primitive_value value1, union primitive_value value2) {
    return (value1.longValue < value2.longValue) ? -1 : (value1.longValue == value2.longValue) ? 0 : 1;
}

int32_t primitive_cmpUByte(union primitive_value value1, union primitive_value value2) {
    return (value1.ubyteValue < value2.ubyteValue) ? -1 : (value1.ubyteValue == value2.ubyteValue) ? 0 : 1;
}

int32_t primitive_cmpUShort(union primitive_value value1, union primitive_value value2) {
    return (value1.ushortValue < value2.ushortValue) ? -1 : (value1.ushortValue == value2.ushortValue) ? 0 : 1;
}

int32_t primitive_cmpUInt(union primitive_value value1, union primitive_value value2) {
    return (value1.uintValue < value2.uintValue) ? -1 : (value1.uintValue == value2.uintValue) ? 0 : 1;
}

int32_t primitive_cmpULong(union primitive_value value1, union primitive_value value2) {
    return (value1.ulongValue < value2.ulongValue) ? -1 : (value1.ulongValue == value2.ulongValue) ? 0 : 1;
}

int32_t primitive_cmpFloat(union primitive_value value1, union primitive_value value2) {
    return (value1.floatValue < value2.floatValue) ? -1 : (value1.floatValue == value2.floatValue) ? 0 : 1;
}

int32_t primitive_cmpDouble(union primitive_value value1, union primitive_value value2) {
    return (value1.doubleValue < value2.doubleValue) ? -1 : (value1.doubleValue == value2.doubleValue) ? 0 : 1;
}

int32_t primitive_cmpPointer(union primitive_value value1, union primitive_value value2) {
    return (value1.pointerValue < value2.pointerValue) ? -1 : (value1.pointerValue == value2.pointerValue) ? 0 : 1;
}

int32_t primitive_cmpChar(union primitive_value value1, union primitive_value value2) {
    return (value1.charValue < value2.charValue) ? -1 : (value1.charValue == value2.charValue) ? 0 : 1;
}

int32_t primitive_cmpWChar(union primitive_value value1, union primitive_value value2) {
    return (value1.wcharValue < value2.wcharValue) ? -1 : (value1.wcharValue == value2.wcharValue) ? 0 : 1;
}

int32_t primitive_cmpString(union primitive_value value1, union primitive_value value2) {
    if (value1.stringValue == NULL && value2.stringValue == NULL) {
        return 0;
    }
    if (value1.stringValue == NULL) {
        return -1;
    }
    if (value2.stringValue == NULL) {
        return 1;
    }
    return strcmp(value1.stringValue, value2.stringValue);
}

int32_t primitive_cmpWString(union primitive_value value1, union primitive_value value2) {
    if (value1.wstringValue == NULL && value2.wstringValue == NULL) {
        return 0;
    }
    if (value1.wstringValue == NULL) {
        return -1;
    }
    if (value2.wstringValue == NULL) {
        return 1;
    }
    return wcscmp(value1.wstringValue, value2.wstringValue);
}

/*******************************************************************************************/

// Calculate hash code.

uint32_t primitive_hashRawUInt(uint32_t u) {
    return (u | 64) ^ ((u >> 15) | (u << 17));
}

uint32_t primitive_hashRawULong(uint64_t u) {
    return primitive_hashRawUInt(((uint32_t) u) ^ ((uint32_t) (u >> 32)));
}

uint32_t primitive_hashRawDouble(double d) {
    return primitive_hashRawUInt((((uint32_t) d) + 5381) ^ ((uint32_t) (d * 72865789.0)));
}

uint32_t primitive_hashRawString(char *string) {
    uint32_t hash = 5381;

    if (string != NULL) {
        for (uint32_t c, i = 0; (c = (uint32_t) string[i]) != 0; i++) {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
    }

    return hash;
}

uint32_t primitive_hashRawWString(wchar_t *wstring) {
    uint32_t hash = 5381;

    if (wstring != NULL) {
        for (uint32_t c, i = 0; (c = (uint32_t) wstring[i]) != 0; i++) {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
    }

    return hash;
}

uint32_t primitive_hashBool(union primitive_value value) {
    return (uint32_t) value.boolValue;
}

uint32_t primitive_hashByte(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.byteValue);
}

uint32_t primitive_hashShort(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.shortValue);
}

uint32_t primitive_hashInt(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.intValue);
}

uint32_t primitive_hashLong(union primitive_value value) {
    return primitive_hashRawULong((uint64_t) value.longValue);
}

uint32_t primitive_hashUByte(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.ubyteValue);
}

uint32_t primitive_hashUShort(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.ushortValue);
}

uint32_t primitive_hashUInt(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.uintValue);
}

uint32_t primitive_hashULong(union primitive_value value) {
    return primitive_hashRawULong((uint64_t) value.ulongValue);
}

uint32_t primitive_hashFloat(union primitive_value value) {
    return primitive_hashRawDouble((double) value.floatValue);
}

uint32_t primitive_hashDouble(union primitive_value value) {
    return primitive_hashRawDouble(value.doubleValue);
}

uint32_t primitive_hashPointer(union primitive_value value) {
    return primitive_hashRawULong((uint64_t) value.pointerValue);
}

uint32_t primitive_hashChar(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.charValue);
}

uint32_t primitive_hashWChar(union primitive_value value) {
    return primitive_hashRawUInt((uint32_t) value.wcharValue);
}

uint32_t primitive_hashString(union primitive_value value) {
    return primitive_hashRawString(value.stringValue);
}

uint32_t primitive_hashWString(union primitive_value value) {
    return primitive_hashRawWString(value.wstringValue);
}

/*******************************************************************************************/
