#ifndef CONSTANTS_H
#define CONSTANTS_H

enum TokenId 
{
    EPSILON  = 0,
    DOLLAR   = 1,
    t_ID = 2,
    t_FILE_START = 3,
    t_FILE_END = 4,
    t_BOOLEAN_VALUE = 5,
    t_USING = 6,
    t_CONST = 7,
    t_BREAK = 8,
    t_RETURN = 9,
    t_COUT = 10,
    t_CIN = 11,
    t_DEFAULT = 12,
    t_CONTINUE = 13,
    t_PRINTF = 14,
    t_SCANF = 15,
    t_FUNCTION = 16,
    t_IMPORT = 17,
    t_INT = 18,
    t_FLOAT = 19,
    t_CHAR = 20,
    t_STRING = 21,
    t_BOOL = 22,
    t_DOUBLE = 23,
    t_VOID = 24,
    t_MAIN = 25,
    t_IF = 26,
    t_ELSE = 27,
    t_SWITCH = 28,
    t_CASE = 29,
    t_FOR = 30,
    t_WHILE = 31,
    t_DO = 32,
    t_OR = 33,
    t_AND = 34,
    t_MAIOR = 35,
    t_MENOR = 36,
    t_MENOR_IGUAL = 37,
    t_MAIOR_IGUAL = 38,
    t_MAIS = 39,
    t_MENOS = 40,
    t_DIVISAO = 41,
    t_MOD = 42,
    t_MULTIPLICACAO = 43,
    t_ATRIBUICAO = 44,
    t_IGUAL = 45,
    t_INVERTER = 46,
    t_DIFERENTE = 47,
    t_RIGHTSHIFT = 48,
    t_LEFTSHIFT = 49,
    t_BITWISE_AND = 50,
    t_BITWISE_OR = 51,
    t_BITWISE_NOT = 52,
    t_BITWISE_XOR = 53,
    t_PONTO = 54,
    t_VIRGULA = 55,
    t_DOIS_PONTOS = 56,
    t_PONTO_E_VIRGULA = 57,
    t_ABRIR_COLCHETES = 58,
    t_FECHAR_COLCHETES = 59,
    t_ABRIR_PARENTESES = 60,
    t_FECHAR_PARENTESES = 61,
    t_ABRIR_CHAVES = 62,
    t_FECHAR_CHAVES = 63,
    t_CONTRABARRA = 64,
    t_INTERROGACAO = 65,
    t_INT_VALUE = 66,
    t_FLOAT_VALUE = 67,
    t_DOUBLE_VALUE = 68,
    t_BIN_VALUE = 69,
    t_HEX_VALUE = 70,
    t_STRING_VALUE = 71,
    t_CHAR_VALUE = 72
};

const int STATES_COUNT = 67;

extern int SCANNER_TABLE[STATES_COUNT][256];

extern int TOKEN_STATE[STATES_COUNT];

extern int SPECIAL_CASES_INDEXES[74];

extern const char *SPECIAL_CASES_KEYS[27];

extern int SPECIAL_CASES_VALUES[27];

extern const char *SCANNER_ERROR[STATES_COUNT];

const int FIRST_SEMANTIC_ACTION = 146;

const int SHIFT  = 0;
const int REDUCE = 1;
const int ACTION = 2;
const int ACCEPT = 3;
const int GO_TO  = 4;
const int ERROR  = 5;

extern const int PARSER_TABLE[414][219][2];

extern const int PRODUCTIONS[159][2];

extern const char *PARSER_ERROR[414];

#endif
