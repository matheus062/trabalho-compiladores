#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_VAR = 2,
    t_ID = 3,
    t_FILE_START = 4,
    t_FILE_END = 5,
    t_BOOLEAN_VALUE = 6,
    t_USING = 7,
    t_CONST = 8,
    t_BREAK = 9,
    t_RETURN = 10,
    t_COUT = 11,
    t_CIN = 12,
    t_DEFAULT = 13,
    t_CONTINUE = 14,
    t_PRINTF = 15,
    t_SCANF = 16,
    t_FUNCTION = 17,
    t_IMPORT = 18,
    t_INT = 19,
    t_FLOAT = 20,
    t_CHAR = 21,
    t_STRING = 22,
    t_BOOL = 23,
    t_DOUBLE = 24,
    t_VOID = 25,
    t_MAIN = 26,
    t_IF = 27,
    t_ELSE = 28,
    t_SWITCH = 29,
    t_CASE = 30,
    t_FOR = 31,
    t_WHILE = 32,
    t_DO = 33,
    t_OR = 34,
    t_AND = 35,
    t_MAIOR = 36,
    t_MENOR = 37,
    t_MENOR_IGUAL = 38,
    t_MAIOR_IGUAL = 39,
    t_MAIS = 40,
    t_MENOS = 41,
    t_DIVISAO = 42,
    t_MOD = 43,
    t_MULTIPLICACAO = 44,
    t_ATRIBUICAO = 45,
    t_IGUAL = 46,
    t_INVERTER = 47,
    t_DIFERENTE = 48,
    t_RIGHTSHIFT = 49,
    t_LEFTSHIFT = 50,
    t_BITWISE_AND = 51,
    t_BITWISE_OR = 52,
    t_BITWISE_NOT = 53,
    t_BITWISE_XOR = 54,
    t_PONTO = 55,
    t_VIRGULA = 56,
    t_DOIS_PONTOS = 57,
    t_PONTO_E_VIRGULA = 58,
    t_ABRIR_COLCHETES = 59,
    t_FECHAR_COLCHETES = 60,
    t_ABRIR_PARENTESES = 61,
    t_FECHAR_PARENTESES = 62,
    t_ABRIR_CHAVES = 63,
    t_FECHAR_CHAVES = 64,
    t_CONTRABARRA = 65,
    t_INTERROGACAO = 66,
    t_INT_VALUE = 67,
    t_FLOAT_VALUE = 68,
    t_DOUBLE_VALUE = 69,
    t_BIN_VALUE = 70,
    t_HEX_VALUE = 71,
    t_STRING_VALUE = 72,
    t_CHAR_VALUE = 73
};

const int STATES_COUNT = 69;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern int SPECIAL_CASES_INDEXES[75];

extern const char *SPECIAL_CASES_KEYS[27];

extern int SPECIAL_CASES_VALUES[27];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 147;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[413][220][2];

extern const int PRODUCTIONS[159][2];

extern const char *PARSER_ERROR[413];

#endif
