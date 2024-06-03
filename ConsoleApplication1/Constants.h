#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_FILE_START = 2,
    t_FILE_END = 3,
    t_INT = 4,
    t_FLOAT = 5,
    t_BOOLEAN = 6,
    t_STRING = 7,
    t_ARRAY = 8,
    t_DOT = 9,
    t_COMMA = 10,
    t_SEMI_COLON = 11,
    t_DOUBLE_COLON = 12,
    t_PARENTHESES_OPEN = 13,
    t_PARENTHESES_CLOSE = 14,
    t_BRACKETS_OPEN = 15,
    t_BRACKETS_CLOSE = 16,
    t_CURLY_OPEN = 17,
    t_CURLY_CLOSE = 18,
    t_BACKSLASH = 19,
    t_COMMENT = 20,
    t_COMMENT_MULTILINE = 21,
    t_DECIMAL = 22,
    t_BINARY = 23,
    t_HEX = 24,
    t_FLOAT_VAL = 25,
    t_CHAR = 26,
    t_STRING_VAL = 27,
    t_CONCAT = 28,
    t_CONCAT_EQUAL = 29,
    t_BOOLEAN_VAL = 30,
    t_NULL = 31,
    t_PLUS = 32,
    t_MINUS = 33,
    t_MULTIPLY = 34,
    t_DIVIDE = 35,
    t_MODULE = 36,
    t_INCREMENT = 37,
    t_DECREMENT = 38,
    t_DIV_EQUAL = 39,
    t_PLUS_EQUAL = 40,
    t_POW = 41,
    t_POW_EQUAL = 42,
    t_IS_GREATER = 43,
    t_IS_SMALLER = 44,
    t_IS_GREATER_EQUAL = 45,
    t_IS_SMALLER_EQUAL = 46,
    t_IS_EQUAL = 47,
    t_NOT_EQUAL = 48,
    t_EQUAL = 49,
    t_AND = 50,
    t_OR = 51,
    t_XOR = 52,
    t_NOT = 53,
    t_COALESCE = 54,
    t_SPACESHIP = 55,
    t_BITWISE_LEFT = 56,
    t_BITWISE_RIGHT = 57,
    t_BITWISE_AND = 58,
    t_BITWISE_OR = 59,
    t_BITWISE_TILDE = 60,
    t_BITWISE_CIRCU = 61,
    t_VAR = 62,
    t_ID = 63,
    t_ABSTRACT = 64,
    t_BREAK = 65,
    t_CASE = 66,
    t_CLASS = 67,
    t_CONST = 68,
    t_CONTINUE = 69,
    t_DECLARE = 70,
    t_DIE = 71,
    t_DO = 72,
    t_ECHO = 73,
    t_ELSE = 74,
    t_ELSEIF = 75,
    t_EXTENDS = 76,
    t_FINALLY = 77,
    t_FOR = 78,
    t_FOREACH = 79,
    t_FUNCTION = 80,
    t_GLOBAL = 81,
    t_IF = 82,
    t_INCLUDE = 83,
    t_INCLUDE_ONCE = 84,
    t_NAMESPACE = 85,
    t_NEW = 86,
    t_PRIVATE = 87,
    t_PROTECTED = 88,
    t_PUBLIC = 89,
    t_REQUIRE = 90,
    t_REQUIRE_ONCE = 91,
    t_RETURN = 92,
    t_STATIC = 93,
    t_VOID = 94,
    t_SWITCH = 95,
    t_THROW = 96,
    t_TRY = 97,
    t_UNSET = 98,
    t_USE = 99,
    t_WHILE = 100,
    t_PHP_IN = 101,
    t_PHP_OUT = 102
};

const int STATES_COUNT = 121;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern int SPECIAL_CASES_INDEXES[104];

extern const char *SPECIAL_CASES_KEYS[39];

extern int SPECIAL_CASES_VALUES[39];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 154;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[253][168][2];

extern const int PRODUCTIONS[119][2];

extern const char *PARSER_ERROR[253];

#endif
