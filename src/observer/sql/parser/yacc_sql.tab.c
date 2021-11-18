/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t data_num;
  size_t index_length;
  Value values[MAX_NUM * MAX_NUM];
  int data_list_r[MAX_NUM];
  Condition conditions[MAX_NUM];
  char *index_list[MAX_NUM];
  CompOp comp;
  AggregationOp aggop;

  size_t sub_condition_length;
  Condition sub_conditions[MAX_NUM];
  CompOp sub_comp;
  AggregationOp sub_aggop;

  size_t sub_sub_condition_length;
  Condition sub_sub_conditions[MAX_NUM];
  CompOp sub_sub_comp;
  AggregationOp sub_sub_aggop;

  size_t sub2_condition_length;
  Condition sub2_conditions[MAX_NUM];
  CompOp sub2_comp;
  AggregationOp sub2_aggop;

	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

char *int_to_char_array(int x) {
	int n = 0, y = x;
	while(y) ++n, y /= 10;
	char *s = malloc(sizeof(char) * (n + 1));
	for(int i = n - 1; i >= 0; --i) {
		s[i] = x % 10 + '0';
		x /= 10;
	}
  s[n]=0;
	return s;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->index_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->sub_condition_length = 0;
  context->sub_sub_condition_length = 0;
  context->sub2_condition_length = 0;
  printf("parse sql failed. error=%s", str);
}

CompOp Exchange_CompOp(CompOp comp) {
  switch (comp) {
    case LESS_EQUAL: 
      return GREAT_EQUAL;
    case LESS_THAN:
      return GREAT_THAN;
    case GREAT_EQUAL:
      return LESS_EQUAL;
    case GREAT_THAN:
      return LESS_THAN;
    default:
    break;
  }
  return comp;
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 181 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_ASC = 11,                       /* ASC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_DATE_T = 24,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 25,                    /* TEXT_T  */
  YYSYMBOL_STRING_T = 26,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 27,                   /* FLOAT_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_SET = 36,                       /* SET  */
  YYSYMBOL_ON = 37,                        /* ON  */
  YYSYMBOL_IN = 38,                        /* IN  */
  YYSYMBOL_LOAD = 39,                      /* LOAD  */
  YYSYMBOL_DATA = 40,                      /* DATA  */
  YYSYMBOL_INFILE = 41,                    /* INFILE  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_GT = 44,                        /* GT  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GE = 46,                        /* GE  */
  YYSYMBOL_NE = 47,                        /* NE  */
  YYSYMBOL_AGG_COUNT = 48,                 /* AGG_COUNT  */
  YYSYMBOL_AGG_MAX = 49,                   /* AGG_MAX  */
  YYSYMBOL_AGG_MIN = 50,                   /* AGG_MIN  */
  YYSYMBOL_AGG_AVG = 51,                   /* AGG_AVG  */
  YYSYMBOL_ORDER = 52,                     /* ORDER  */
  YYSYMBOL_GROUP = 53,                     /* GROUP  */
  YYSYMBOL_BY = 54,                        /* BY  */
  YYSYMBOL_INNER = 55,                     /* INNER  */
  YYSYMBOL_JOIN = 56,                      /* JOIN  */
  YYSYMBOL_IS = 57,                        /* IS  */
  YYSYMBOL_NOT = 58,                       /* NOT  */
  YYSYMBOL_NULLL = 59,                     /* NULLL  */
  YYSYMBOL_NULLABLE = 60,                  /* NULLABLE  */
  YYSYMBOL_UNIQUE = 61,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_DATEE = 64,                     /* DATEE  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_commands = 71,                  /* commands  */
  YYSYMBOL_command = 72,                   /* command  */
  YYSYMBOL_exit = 73,                      /* exit  */
  YYSYMBOL_help = 74,                      /* help  */
  YYSYMBOL_sync = 75,                      /* sync  */
  YYSYMBOL_begin = 76,                     /* begin  */
  YYSYMBOL_commit = 77,                    /* commit  */
  YYSYMBOL_rollback = 78,                  /* rollback  */
  YYSYMBOL_drop_table = 79,                /* drop_table  */
  YYSYMBOL_show_tables = 80,               /* show_tables  */
  YYSYMBOL_desc_table = 81,                /* desc_table  */
  YYSYMBOL_create_index = 82,              /* create_index  */
  YYSYMBOL_create_index_attr_list = 83,    /* create_index_attr_list  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_create_table = 85,              /* create_table  */
  YYSYMBOL_attr_def_list = 86,             /* attr_def_list  */
  YYSYMBOL_attr_def = 87,                  /* attr_def  */
  YYSYMBOL_number = 88,                    /* number  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_ID_get = 90,                    /* ID_get  */
  YYSYMBOL_insert = 91,                    /* insert  */
  YYSYMBOL_data = 92,                      /* data  */
  YYSYMBOL_data_list = 93,                 /* data_list  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update = 97,                    /* update  */
  YYSYMBOL_select = 98,                    /* select  */
  YYSYMBOL_sub_select = 99,                /* sub_select  */
  YYSYMBOL_sub2_select = 100,              /* sub2_select  */
  YYSYMBOL_sub_sub_select = 101,           /* sub_sub_select  */
  YYSYMBOL_order_by = 102,                 /* order_by  */
  YYSYMBOL_select_order_list = 103,        /* select_order_list  */
  YYSYMBOL_select_order = 104,             /* select_order  */
  YYSYMBOL_group_by = 105,                 /* group_by  */
  YYSYMBOL_select_group_list = 106,        /* select_group_list  */
  YYSYMBOL_select_group = 107,             /* select_group  */
  YYSYMBOL_sub_select_attribute = 108,     /* sub_select_attribute  */
  YYSYMBOL_sub2_select_attribute = 109,    /* sub2_select_attribute  */
  YYSYMBOL_sub_sub_select_attribute = 110, /* sub_sub_select_attribute  */
  YYSYMBOL_select_attr = 111,              /* select_attr  */
  YYSYMBOL_select_attribute = 112,         /* select_attribute  */
  YYSYMBOL_attr_list = 113,                /* attr_list  */
  YYSYMBOL_aggr_select_attr = 114,         /* aggr_select_attr  */
  YYSYMBOL_aggr_attr_list = 115,           /* aggr_attr_list  */
  YYSYMBOL_rel_list = 116,                 /* rel_list  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_inner_join_on = 118,            /* inner_join_on  */
  YYSYMBOL_condition_list = 119,           /* condition_list  */
  YYSYMBOL_condition = 120,                /* condition  */
  YYSYMBOL_bcondition = 121,               /* bcondition  */
  YYSYMBOL_sub_where = 122,                /* sub_where  */
  YYSYMBOL_sub_condition_list = 123,       /* sub_condition_list  */
  YYSYMBOL_sub_condition = 124,            /* sub_condition  */
  YYSYMBOL_sub2_where = 125,               /* sub2_where  */
  YYSYMBOL_sub2_condition_list = 126,      /* sub2_condition_list  */
  YYSYMBOL_sub2_condition = 127,           /* sub2_condition  */
  YYSYMBOL_sub_sub_where = 128,            /* sub_sub_where  */
  YYSYMBOL_sub_sub_condition_list = 129,   /* sub_sub_condition_list  */
  YYSYMBOL_sub_sub_condition = 130,        /* sub_sub_condition  */
  YYSYMBOL_comOp = 131,                    /* comOp  */
  YYSYMBOL_sub_comOp = 132,                /* sub_comOp  */
  YYSYMBOL_sub2_comOp = 133,               /* sub2_comOp  */
  YYSYMBOL_sub_sub_comOp = 134,            /* sub_sub_comOp  */
  YYSYMBOL_aggOp = 135,                    /* aggOp  */
  YYSYMBOL_sub_aggOp = 136,                /* sub_aggOp  */
  YYSYMBOL_sub2_aggOp = 137,               /* sub2_aggOp  */
  YYSYMBOL_sub_sub_aggOp = 138,            /* sub_sub_aggOp  */
  YYSYMBOL_load_data = 139                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   593

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  70
/* YYNRULES -- Number of rules.  */
#define YYNRULES  255
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  497

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   205,   205,   207,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   231,   236,   241,   247,   253,   259,   265,   271,   277,
     284,   291,   299,   301,   307,   314,   323,   325,   329,   340,
     351,   362,   373,   384,   397,   400,   401,   402,   403,   404,
     407,   416,   433,   437,   439,   444,   446,   451,   454,   457,
     461,   465,   471,   481,   491,   509,   524,   539,   553,   555,
     559,   561,   566,   571,   576,   581,   586,   591,   597,   599,
     603,   605,   610,   615,   622,   627,   632,   637,   642,   647,
     652,   657,   662,   669,   674,   679,   684,   689,   694,   699,
     704,   709,   716,   721,   726,   731,   736,   741,   746,   751,
     756,   763,   768,   773,   778,   783,   788,   793,   798,   803,
     808,   814,   816,   821,   824,   827,   831,   833,   836,   839,
     845,   847,   851,   855,   857,   861,   863,   867,   869,   874,
     895,   915,   935,   957,   978,   999,  1018,  1035,  1053,  1070,
    1088,  1106,  1127,  1147,  1167,  1189,  1210,  1231,  1250,  1267,
    1285,  1302,  1321,  1323,  1327,  1329,  1334,  1355,  1375,  1395,
    1417,  1438,  1459,  1478,  1495,  1513,  1530,  1549,  1551,  1555,
    1557,  1562,  1583,  1603,  1623,  1645,  1666,  1687,  1707,  1709,
    1713,  1715,  1720,  1741,  1761,  1781,  1803,  1824,  1845,  1867,
    1868,  1869,  1870,  1871,  1872,  1873,  1874,  1875,  1876,  1879,
    1880,  1881,  1882,  1883,  1884,  1885,  1886,  1887,  1888,  1891,
    1892,  1893,  1894,  1895,  1896,  1897,  1898,  1899,  1900,  1903,
    1904,  1905,  1906,  1907,  1908,  1909,  1910,  1911,  1912,  1916,
    1917,  1918,  1919,  1922,  1923,  1924,  1925,  1927,  1928,  1929,
    1930,  1933,  1934,  1935,  1936,  1940
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "ASC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "TEXT_T",
  "STRING_T", "FLOAT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "IN", "LOAD", "DATA", "INFILE", "EQ", "LT",
  "GT", "LE", "GE", "NE", "AGG_COUNT", "AGG_MAX", "AGG_MIN", "AGG_AVG",
  "ORDER", "GROUP", "BY", "INNER", "JOIN", "IS", "NOT", "NULLL",
  "NULLABLE", "UNIQUE", "NUMBER", "FLOAT", "DATEE", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "create_index_attr_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "data", "data_list", "value_list", "value", "delete", "update",
  "select", "sub_select", "sub2_select", "sub_sub_select", "order_by",
  "select_order_list", "select_order", "group_by", "select_group_list",
  "select_group", "sub_select_attribute", "sub2_select_attribute",
  "sub_sub_select_attribute", "select_attr", "select_attribute",
  "attr_list", "aggr_select_attr", "aggr_attr_list", "rel_list", "where",
  "inner_join_on", "condition_list", "condition", "bcondition",
  "sub_where", "sub_condition_list", "sub_condition", "sub2_where",
  "sub2_condition_list", "sub2_condition", "sub_sub_where",
  "sub_sub_condition_list", "sub_sub_condition", "comOp", "sub_comOp",
  "sub2_comOp", "sub_sub_comOp", "aggOp", "sub_aggOp", "sub2_aggOp",
  "sub_sub_aggOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-435)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -435,   196,  -435,     9,   183,   -24,   -45,    14,    49,     3,
      48,    21,   105,   112,   121,   126,   133,   113,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,  -435,  -435,    93,    94,   166,   101,
     123,  -435,  -435,  -435,  -435,   164,  -435,   165,   188,   186,
     210,   212,  -435,   154,   155,   185,  -435,  -435,  -435,  -435,
    -435,   182,   215,   197,   168,   233,   234,   173,   175,   -24,
    -435,    10,  -435,  -435,   217,   216,   179,   180,   189,   198,
     225,  -435,  -435,  -435,    24,   188,  -435,   235,   132,   247,
     254,   258,    -5,   273,   242,   246,  -435,   266,   158,   269,
     222,   223,   244,   216,  -435,  -435,  -435,   224,  -435,   -12,
     205,   272,   292,  -435,  -435,  -435,  -435,    -7,  -435,   290,
     290,   267,  -435,   205,   309,   189,   296,  -435,  -435,  -435,
    -435,  -435,     5,   252,   301,    24,   255,   277,   303,   289,
    -435,   311,   319,   258,   339,   248,   278,  -435,  -435,  -435,
    -435,  -435,  -435,  -435,   287,   318,    31,   343,     1,    38,
    -435,   216,   284,   266,   354,   297,   299,  -435,   341,   304,
    -435,   324,   314,   317,  -435,   312,    95,   360,   205,   367,
     272,  -435,  -435,  -435,  -435,  -435,   365,  -435,   361,   379,
     290,  -435,  -435,  -435,  -435,  -435,   368,  -435,   390,   381,
    -435,   184,   290,   290,   267,   398,   415,  -435,  -435,  -435,
     407,  -435,   374,   414,   341,    -5,    24,   388,   420,   443,
    -435,    61,   311,  -435,   319,  -435,  -435,   395,   402,    86,
      47,   416,   276,   417,   418,    54,   350,   419,  -435,  -435,
    -435,   144,   341,   476,   467,   267,  -435,   146,   468,   421,
    -435,   423,  -435,  -435,  -435,  -435,   455,  -435,   472,   134,
     473,   474,   462,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
     464,  -435,   463,   478,  -435,   290,  -435,  -435,  -435,   469,
    -435,   470,   438,  -435,  -435,  -435,   495,  -435,  -435,  -435,
     436,   388,  -435,   475,   483,   311,    68,   485,  -435,  -435,
     439,  -435,   -12,   441,   442,   444,   110,    75,   445,   446,
    -435,  -435,    19,   468,   447,   421,  -435,  -435,   499,   213,
     308,   308,   479,  -435,   497,   311,  -435,  -435,   482,  -435,
     500,   149,   501,   494,   487,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,   483,   332,   456,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,   465,   484,    82,   357,   459,    68,  -435,
    -435,   502,   364,   507,  -435,  -435,   461,  -435,   -12,   466,
    -435,  -435,  -435,  -435,  -435,   498,  -435,   496,   510,   308,
    -435,  -435,  -435,  -435,  -435,   503,  -435,   504,   479,  -435,
     236,   329,   505,  -435,   512,   311,  -435,   471,   477,   125,
     106,   480,   481,  -435,   486,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,   489,   506,   371,   378,   364,  -435,  -435,   514,
    -435,   509,  -435,   517,   162,   519,   520,   508,  -435,  -435,
    -435,  -435,   329,  -435,  -435,  -435,  -435,   511,  -435,   505,
    -435,   385,   530,  -435,  -435,   488,  -435,   -12,   490,   392,
     491,  -435,   265,   346,   515,  -435,   531,   311,  -435,   522,
    -435,  -435,   492,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
     513,   516,   399,   406,   385,  -435,  -435,   540,   518,   346,
    -435,  -435,  -435,  -435,   529,  -435,   515,  -435,  -435,   413,
     521,  -435,   532,  -435,  -435,   523,  -435
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,   239,   240,   241,   242,   119,   118,     0,   121,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     111,     0,    29,    28,     0,   133,     0,     0,     0,     0,
       0,    27,    34,   120,   130,   121,   117,     0,   124,   123,
       0,     0,     0,     0,     0,     0,    50,    36,     0,     0,
       0,     0,     0,   133,   122,   113,   114,     0,   112,     0,
       0,    53,     0,    61,    57,    58,    59,     0,    60,     0,
       0,   137,    62,     0,     0,     0,     0,    45,    46,    47,
      48,    49,    41,     0,     0,   130,     0,    68,   125,   124,
     123,   126,    55,     0,     0,     0,     0,   200,   201,   202,
     203,   204,   205,   206,   208,     0,     0,     0,     0,     0,
     134,   133,     0,    36,     0,     0,     0,    43,    32,     0,
     131,   135,     0,    78,   115,     0,     0,     0,     0,     0,
      53,    51,   243,   244,   245,   246,    91,    90,     0,     0,
       0,   207,   199,   141,   139,   147,   142,   140,     0,   149,
     150,     0,     0,     0,   137,     0,     0,    37,    35,    44,
       0,    42,     0,     0,    32,     0,   130,     0,     0,     0,
     125,   126,   126,   116,    55,    52,    54,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,    63,
     255,    38,    32,     0,     0,   137,   132,    72,    70,     0,
      64,     0,   128,   127,    56,    92,   162,    89,     0,   124,
     123,     0,     0,   143,   146,   144,   247,   248,   249,   250,
     100,    99,     0,     0,   148,     0,   153,   151,   159,   154,
     152,   161,     0,    40,    33,    30,     0,   136,    74,    73,
       0,     0,    69,    82,    80,   126,     0,     0,    85,    86,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
      39,    31,    75,    70,     0,     0,    79,   129,     0,     0,
       0,     0,   164,    65,   125,   126,   145,   101,   177,    98,
       0,   124,   123,     0,     0,   155,   158,   156,   160,    77,
      76,    71,    83,    80,     0,     0,   210,   211,   212,   213,
     214,   215,   216,   218,     0,     0,     0,     0,     0,   163,
      87,     0,     0,     0,    94,    95,     0,    93,     0,     0,
      81,   251,   252,   253,   254,   109,   108,     0,     0,     0,
     217,   209,   168,   166,   174,   169,   167,   176,   164,    88,
       0,     0,   179,    66,   125,   126,   157,     0,     0,     0,
       0,     0,     0,   165,     0,   220,   221,   222,   223,   224,
     225,   226,   228,     0,     0,     0,     0,   178,    96,     0,
     110,   188,   107,     0,   124,   123,     0,     0,   170,   173,
     171,   175,     0,   227,   219,   183,   181,   184,   182,   179,
      97,     0,     0,   103,   104,     0,   102,     0,     0,     0,
       0,   180,     0,     0,   190,    67,   125,   126,   172,     0,
     185,   186,     0,   230,   231,   232,   233,   234,   235,   236,
     238,     0,     0,     0,     0,   189,   105,     0,     0,     0,
     237,   229,   194,   192,   195,   193,   190,   106,   187,     0,
       0,   191,     0,   196,   197,     0,   198
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,  -435,
    -435,  -435,  -435,  -200,  -435,  -435,   397,   440,  -435,  -435,
    -435,  -435,   424,   383,   337,  -110,  -435,  -435,  -435,  -146,
    -152,  -339,  -435,   251,   275,  -435,   226,   253,  -435,  -435,
    -435,  -435,   524,   493,  -107,  -218,  -134,   -92,  -435,  -172,
     355,  -435,  -435,   187,   214,  -435,   135,   157,  -435,    90,
     103,  -114,  -312,  -358,  -434,  -435,  -435,  -435,  -435,  -435
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   213,    29,    30,   126,    97,   210,   132,
      98,    31,   111,   144,   179,   119,    32,    33,    34,   120,
     200,   321,   173,   292,   248,   219,   316,   294,   188,   272,
     377,    47,    48,    70,    90,   177,   103,    93,   216,   160,
     121,   204,   297,   359,   322,   363,   417,   392,   442,   475,
     454,   156,   355,   414,   472,    49,   189,   273,   378,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     142,   170,   141,   252,   253,   157,   158,   203,   356,   357,
     195,   137,   112,   161,   244,    36,   384,    37,   198,   473,
      50,    51,   165,   146,    41,    42,    43,    44,    86,   339,
     340,   147,   238,   415,    53,   148,   149,   150,   151,   152,
     153,    45,   284,   101,    46,   489,   194,   197,   112,   202,
     154,   155,    52,   139,   113,   198,   140,   114,   115,   116,
     117,   429,   118,   166,   112,   167,   199,   400,   224,   205,
      38,   198,    87,   287,   449,    88,   230,   317,    89,   102,
     176,    54,   246,   278,   264,   318,    55,   235,   236,   237,
     113,   251,   198,   114,   115,   116,   193,   113,   118,   318,
     114,   115,   116,   201,   257,   118,   113,   361,    56,   114,
     115,   116,   262,   113,   118,    57,   114,   115,   116,   276,
     263,   118,   261,   318,    58,   277,   280,   113,   329,    59,
     114,   115,   116,   319,   113,   118,    60,   114,   115,   116,
     334,   113,   118,   422,   114,   115,   116,   382,   258,   118,
     106,   259,   299,    61,   260,   336,   288,   289,    62,    63,
     221,   307,   107,   222,   300,   113,    65,   365,   114,   115,
     116,   427,   330,   118,    64,   331,   290,   419,   332,   366,
     444,   127,   128,   129,   130,   131,   320,   423,    66,    39,
     424,    40,   445,   425,    67,   325,     2,   335,    68,   333,
       3,     4,   282,    71,   283,     5,     6,    69,     7,     8,
       9,    10,    11,    72,   234,    73,    12,    13,    14,    74,
      75,    76,   147,    77,    15,    16,   148,   149,   150,   151,
     152,   153,    78,    80,    79,    17,    81,    82,    83,   477,
      84,   154,   155,   345,    94,   383,   386,    95,   320,    91,
      92,   346,   391,   105,    96,   347,   348,   349,   350,   351,
     352,   395,   100,    99,   113,   108,   404,   114,   115,   116,
     353,   354,   118,   109,   405,   110,   122,   124,   406,   407,
     408,   409,   410,   411,   123,   125,   133,   134,   135,   138,
     428,   143,   426,   412,   413,   462,   182,   183,   184,   185,
     136,   145,   159,   463,   436,   438,   391,   464,   465,   466,
     467,   468,   469,   186,   164,   162,   187,   168,   169,   175,
     171,   174,   470,   471,   266,   267,   268,   269,   147,   172,
     176,   453,   148,   149,   150,   151,   152,   153,   178,   460,
     457,   270,   181,   190,   271,   191,   346,   154,   155,   206,
     347,   348,   349,   350,   351,   352,   192,   208,   211,   209,
     212,   215,   483,   485,   453,   353,   354,   405,   217,   214,
     218,   406,   407,   408,   409,   410,   411,   220,   223,   493,
     371,   372,   373,   374,   463,   225,   412,   413,   464,   465,
     466,   467,   468,   469,   228,   227,   229,   375,   231,   232,
     376,   239,   113,   470,   471,   114,   115,   116,   196,   113,
     118,   233,   114,   115,   116,   279,   113,   118,   240,   114,
     115,   116,   385,   113,   118,   241,   114,   115,   116,   390,
     113,   118,   243,   114,   115,   116,   435,   113,   118,   242,
     114,   115,   116,   437,   113,   118,   250,   114,   115,   116,
     452,   113,   118,   247,   114,   115,   116,   459,   113,   118,
     255,   114,   115,   116,   482,   113,   118,   256,   114,   115,
     116,   484,   113,   118,   249,   114,   115,   116,   492,   285,
     118,   265,   274,   275,   281,   286,   293,   291,   295,   296,
     298,   301,   303,   302,   304,   306,   305,   310,   311,   308,
     309,   312,   315,   323,   324,   314,   326,   327,   344,   328,
     337,   338,   342,   368,   358,   360,   362,   369,   364,   367,
     389,   379,   381,   380,   387,   393,   394,   399,   397,   398,
     418,   396,   440,   401,   402,   443,   420,   446,   448,   447,
     416,   450,   421,   441,   434,   430,   431,   433,   455,   476,
     474,   432,   478,   456,   481,   458,   461,   479,   487,   490,
     207,   254,   495,   226,   341,   163,   313,   180,   343,   370,
     245,   480,   388,   439,   451,   403,   491,   486,   104,     0,
       0,     0,     0,   488,     0,     0,   494,     0,   496,     0,
       0,     0,     0,    85
};

static const yytype_int16 yycheck[] =
{
     110,   135,   109,   221,   222,   119,   120,   159,   320,   321,
     156,   103,    17,   123,   214,     6,   355,     8,    17,   453,
      65,     7,    17,    30,    48,    49,    50,    51,    18,    10,
      11,    38,   204,   391,    31,    42,    43,    44,    45,    46,
      47,    65,   242,    19,    68,   479,   156,   157,    17,   159,
      57,    58,     3,    65,    59,    17,    68,    62,    63,    64,
      65,   400,    67,    58,    17,    60,    65,   379,   178,   161,
      61,    17,    62,   245,   432,    65,   190,   295,    68,    55,
      19,    33,   216,   235,   230,    17,    65,   201,   202,   203,
      59,    30,    17,    62,    63,    64,    65,    59,    67,    17,
      62,    63,    64,    65,    18,    67,    59,   325,     3,    62,
      63,    64,    65,    59,    67,     3,    62,    63,    64,    65,
     230,    67,   229,    17,     3,   235,   236,    59,    18,     3,
      62,    63,    64,    65,    59,    67,     3,    62,    63,    64,
      65,    59,    67,    18,    62,    63,    64,    65,    62,    67,
      18,    65,    18,    40,    68,   307,    10,    11,    65,    65,
      65,   275,    30,    68,    30,    59,    65,    18,    62,    63,
      64,    65,    62,    67,     8,    65,    30,   395,    68,    30,
      18,    23,    24,    25,    26,    27,   296,    62,    65,     6,
      65,     8,    30,    68,    30,   302,     0,   307,    33,   306,
       4,     5,    58,    17,    60,     9,    10,    19,    12,    13,
      14,    15,    16,     3,    30,     3,    20,    21,    22,    65,
      65,    36,    38,    41,    28,    29,    42,    43,    44,    45,
      46,    47,    17,    65,    37,    39,     3,     3,    65,   457,
      65,    57,    58,    30,    65,   355,   356,    67,   358,    32,
      34,    38,   362,    18,    65,    42,    43,    44,    45,    46,
      47,   368,    37,    65,    59,    18,    30,    62,    63,    64,
      57,    58,    67,    19,    38,    17,     3,    31,    42,    43,
      44,    45,    46,    47,    42,    19,    17,    65,    65,    65,
     400,    19,   399,    57,    58,    30,    48,    49,    50,    51,
      56,     9,    35,    38,   414,   415,   416,    42,    43,    44,
      45,    46,    47,    65,    18,     6,    68,    65,    17,    30,
      65,    18,    57,    58,    48,    49,    50,    51,    38,    52,
      19,   441,    42,    43,    44,    45,    46,    47,    19,   449,
     447,    65,     3,    65,    68,    58,    38,    57,    58,    65,
      42,    43,    44,    45,    46,    47,    38,     3,    59,    62,
      19,    37,   472,   473,   474,    57,    58,    38,    54,    65,
      53,    42,    43,    44,    45,    46,    47,    65,    18,   489,
      48,    49,    50,    51,    38,    18,    57,    58,    42,    43,
      44,    45,    46,    47,    33,    30,    17,    65,    30,     9,
      68,     3,    59,    57,    58,    62,    63,    64,    65,    59,
      67,    30,    62,    63,    64,    65,    59,    67,     3,    62,
      63,    64,    65,    59,    67,    18,    62,    63,    64,    65,
      59,    67,    18,    62,    63,    64,    65,    59,    67,    65,
      62,    63,    64,    65,    59,    67,     3,    62,    63,    64,
      65,    59,    67,    65,    62,    63,    64,    65,    59,    67,
      65,    62,    63,    64,    65,    59,    67,    65,    62,    63,
      64,    65,    59,    67,    54,    62,    63,    64,    65,     3,
      67,    65,    65,    65,    65,    18,    65,    19,    65,    34,
      18,    18,    30,    19,    30,    17,    33,    59,     3,    30,
      30,    65,    19,    18,    65,    30,    65,    65,     9,    65,
      65,    65,    65,    19,    35,    18,    34,    30,    18,    18,
      18,    65,    38,    58,    65,    18,    65,    17,    30,    33,
      18,    65,    18,    30,    30,    18,    65,    18,    30,    19,
      35,    30,    65,    34,    38,    65,    65,    58,    18,    18,
      35,    65,    30,    65,    38,    65,    65,    65,    18,    30,
     163,   224,    30,   180,   313,   125,   291,   143,   315,   343,
     215,    58,   358,   416,   439,   388,   486,   474,    85,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    65,    -1,    65,    -1,
      -1,    -1,    -1,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    71,     0,     4,     5,     9,    10,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    39,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    91,    96,    97,    98,   139,     6,     8,    61,     6,
       8,    48,    49,    50,    51,    65,    68,   111,   112,   135,
      65,     7,     3,    31,    33,    65,     3,     3,     3,     3,
       3,    40,    65,    65,     8,    65,    65,    30,    33,    19,
     113,    17,     3,     3,    65,    65,    36,    41,    17,    37,
      65,     3,     3,    65,    65,   112,    18,    62,    65,    68,
     114,    32,    34,   117,    65,    67,    65,    87,    90,    65,
      37,    19,    55,   116,   113,    18,    18,    30,    18,    19,
      17,    92,    17,    59,    62,    63,    64,    65,    67,    95,
      99,   120,     3,    42,    31,    19,    86,    23,    24,    25,
      26,    27,    89,    17,    65,    65,    56,   117,    65,    65,
      68,   114,    95,    19,    93,     9,    30,    38,    42,    43,
      44,    45,    46,    47,    57,    58,   131,   131,   131,    35,
     119,    95,     6,    87,    18,    17,    58,    60,    65,    17,
     116,    65,    52,   102,    18,    30,    19,   115,    19,    94,
      92,     3,    48,    49,    50,    51,    65,    68,   108,   136,
      65,    58,    38,    65,    95,    99,    65,    95,    17,    65,
     100,    65,    95,   100,   121,   117,    65,    86,     3,    62,
      88,    59,    19,    83,    65,    37,   118,    54,    53,   105,
      65,    65,    68,    18,    95,    18,    93,    30,    33,    17,
     131,    30,     9,    30,    30,   131,   131,   131,   119,     3,
       3,    18,    65,    18,    83,   120,   116,    65,   104,    54,
       3,    30,   115,   115,    94,    65,    65,    18,    62,    65,
      68,   114,    65,    95,    99,    65,    48,    49,    50,    51,
      65,    68,   109,   137,    65,    65,    65,    95,   100,    65,
      95,    65,    58,    60,    83,     3,    18,   119,    10,    11,
      30,    19,   103,    65,   107,    65,    34,   122,    18,    18,
      30,    18,    19,    30,    30,    33,    17,   131,    30,    30,
      59,     3,    65,   104,    30,    19,   106,   115,    17,    65,
      95,   101,   124,    18,    65,   114,    65,    65,    65,    18,
      62,    65,    68,   114,    65,    95,   100,    65,    65,    10,
      11,   103,    65,   107,     9,    30,    38,    42,    43,    44,
      45,    46,    47,    57,    58,   132,   132,   132,    35,   123,
      18,   115,    34,   125,    18,    18,    30,    18,    19,    30,
     106,    48,    49,    50,    51,    65,    68,   110,   138,    65,
      58,    38,    65,    95,   101,    65,    95,    65,   124,    18,
      65,    95,   127,    18,    65,   114,    65,    30,    33,    17,
     132,    30,    30,   123,    30,    38,    42,    43,    44,    45,
      46,    47,    57,    58,   133,   133,    35,   126,    18,   115,
      65,    65,    18,    62,    65,    68,   114,    65,    95,   101,
      65,    65,    65,    58,    38,    65,    95,    65,    95,   127,
      18,    34,   128,    18,    18,    30,    18,    19,    30,   133,
      30,   126,    65,    95,   130,    18,    65,   114,    65,    65,
      95,    65,    30,    38,    42,    43,    44,    45,    46,    47,
      57,    58,   134,   134,    35,   129,    18,   115,    30,    65,
      58,    38,    65,    95,    65,    95,   130,    18,    65,   134,
      30,   129,    65,    95,    65,    30,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    82,    83,    83,    84,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    88,    89,    89,    89,    89,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    96,    97,    98,    99,   100,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   105,   105,
     106,   106,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   115,   115,   115,   115,
     116,   116,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   123,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   125,   125,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   128,   128,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   135,
     135,   135,   135,   136,   136,   136,   136,   137,   137,   137,
     137,   138,   138,   138,   138,   139
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     4,     8,     0,     3,     5,     7,
       6,     2,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     7,     4,     0,     3,     0,     3,     1,     1,     1,
       1,     1,     5,     8,     9,     7,     7,     7,     0,     4,
       0,     3,     1,     2,     2,     3,     4,     4,     0,     4,
       0,     3,     1,     3,     4,     4,     4,     6,     7,     3,
       1,     1,     3,     4,     4,     4,     6,     7,     3,     1,
       1,     3,     4,     4,     4,     6,     7,     3,     1,     1,
       3,     2,     4,     4,     4,     6,     7,     3,     1,     1,
       3,     0,     3,     1,     1,     3,     0,     3,     3,     5,
       0,     3,     5,     0,     3,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     5,     3,     5,     3,
       3,     3,     3,     3,     3,     5,     5,     7,     5,     3,
       5,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     5,     3,     5,     3,     0,     3,     0,
       3,     3,     3,     3,     3,     5,     5,     7,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 231 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1685 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 236 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1693 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 241 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1701 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 247 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1709 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 253 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1717 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 259 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1725 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 265 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1734 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 271 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1742 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 277 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1751 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 285 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 0);
			CONTEXT->index_length = 0;
		}
#line 1762 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 292 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 1);
			CONTEXT->index_length = 0;
		}
#line 1773 "yacc_sql.tab.c"
    break;

  case 33: /* create_index_attr_list: COMMA ID create_index_attr_list  */
#line 301 "yacc_sql.y"
                                          {
		CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-1].string));
	}
#line 1781 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 308 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1790 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 315 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1802 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 325 "yacc_sql.y"
                                   {    }
#line 1808 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 330 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1823 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE NOT NULLL  */
#line 341 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-5].number), (yyvsp[-3].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1838 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 352 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1853 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type  */
#line 363 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1868 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type NOT NULLL  */
#line 374 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1883 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NULLABLE  */
#line 385 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1898 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 397 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1904 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 400 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1910 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 401 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1916 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 402 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1922 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 403 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1928 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 404 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1934 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 408 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1943 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES data data_list SEMICOLON  */
#line 417 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length,CONTEXT->data_num,CONTEXT->data_list_r) ;

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->data_num=0;
    }
#line 1963 "yacc_sql.tab.c"
    break;

  case 52: /* data: LBRACE value value_list RBRACE  */
#line 433 "yacc_sql.y"
                                       {
		CONTEXT->data_list_r[CONTEXT->data_num++]=CONTEXT->value_length;
	}
#line 1971 "yacc_sql.tab.c"
    break;

  case 54: /* data_list: COMMA data data_list  */
#line 439 "yacc_sql.y"
                            { 
  		
	  }
#line 1979 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 446 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1987 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 451 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1995 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 454 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 2003 "yacc_sql.tab.c"
    break;

  case 59: /* value: DATEE  */
#line 457 "yacc_sql.y"
           {
			(yyvsp[0].dates) = substr((yyvsp[0].dates),1,strlen((yyvsp[0].dates))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].dates));
		}
#line 2012 "yacc_sql.tab.c"
    break;

  case 60: /* value: SSS  */
#line 461 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 2021 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULLL  */
#line 465 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 2029 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 472 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 2041 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 482 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 2053 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON  */
#line 492 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[0], CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length = 0;
			CONTEXT->from_length = 0;
			CONTEXT->select_length = 0;
			CONTEXT->value_length = 0;
	}
#line 2073 "yacc_sql.tab.c"
    break;

  case 65: /* sub_select: LBRACE SELECT sub_select_attribute FROM ID sub_where RBRACE  */
#line 510 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[1], (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[1], CONTEXT->sub_conditions, CONTEXT->sub_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist++;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub_condition_length = 0;
	}
#line 2090 "yacc_sql.tab.c"
    break;

  case 66: /* sub2_select: LBRACE SELECT sub2_select_attribute FROM ID sub2_where RBRACE  */
#line 525 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[2], (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[2], CONTEXT->sub2_conditions, CONTEXT->sub2_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist++;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub2_condition_length = 0;
	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 67: /* sub_sub_select: LBRACE SELECT sub_sub_select_attribute FROM ID sub_sub_where RBRACE  */
#line 540 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[2], (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[2], CONTEXT->sub_sub_conditions, CONTEXT->sub_sub_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist += 100;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub_sub_condition_length = 0;
	}
#line 2124 "yacc_sql.tab.c"
    break;

  case 69: /* order_by: ORDER BY select_order select_order_list  */
#line 555 "yacc_sql.y"
                                              {
      
    }
#line 2132 "yacc_sql.tab.c"
    break;

  case 71: /* select_order_list: COMMA select_order select_order_list  */
#line 561 "yacc_sql.y"
                                               {

	}
#line 2140 "yacc_sql.tab.c"
    break;

  case 72: /* select_order: ID  */
#line 566 "yacc_sql.y"
           {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2150 "yacc_sql.tab.c"
    break;

  case 73: /* select_order: ID ASC  */
#line 571 "yacc_sql.y"
                 {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2160 "yacc_sql.tab.c"
    break;

  case 74: /* select_order: ID DESC  */
#line 576 "yacc_sql.y"
                  {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2170 "yacc_sql.tab.c"
    break;

  case 75: /* select_order: ID DOT ID  */
#line 581 "yacc_sql.y"
                    {
			OrderBy order;
			orders_init(&order, (yyvsp[-2].string), (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2180 "yacc_sql.tab.c"
    break;

  case 76: /* select_order: ID DOT ID ASC  */
#line 586 "yacc_sql.y"
                        {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2190 "yacc_sql.tab.c"
    break;

  case 77: /* select_order: ID DOT ID DESC  */
#line 591 "yacc_sql.y"
                         {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 2200 "yacc_sql.tab.c"
    break;

  case 79: /* group_by: GROUP BY select_group select_group_list  */
#line 599 "yacc_sql.y"
                                                  {

	}
#line 2208 "yacc_sql.tab.c"
    break;

  case 81: /* select_group_list: COMMA select_group select_group_list  */
#line 605 "yacc_sql.y"
                                               {

	}
#line 2216 "yacc_sql.tab.c"
    break;

  case 82: /* select_group: ID  */
#line 610 "yacc_sql.y"
           {
			GroupBy group;
			groups_init(&group, NULL, (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2226 "yacc_sql.tab.c"
    break;

  case 83: /* select_group: ID DOT ID  */
#line 615 "yacc_sql.y"
                    {
			GroupBy group;
			groups_init(&group, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2236 "yacc_sql.tab.c"
    break;

  case 84: /* sub_select_attribute: sub_aggOp LBRACE STAR RBRACE  */
#line 622 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2246 "yacc_sql.tab.c"
    break;

  case 85: /* sub_select_attribute: sub_aggOp LBRACE NUMBER RBRACE  */
#line 627 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2256 "yacc_sql.tab.c"
    break;

  case 86: /* sub_select_attribute: sub_aggOp LBRACE ID RBRACE  */
#line 632 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2266 "yacc_sql.tab.c"
    break;

  case 87: /* sub_select_attribute: sub_aggOp LBRACE ID DOT ID RBRACE  */
#line 637 "yacc_sql.y"
                                            {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2276 "yacc_sql.tab.c"
    break;

  case 88: /* sub_select_attribute: sub_aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 642 "yacc_sql.y"
                                                                                         {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2286 "yacc_sql.tab.c"
    break;

  case 89: /* sub_select_attribute: sub_aggOp LBRACE RBRACE  */
#line 647 "yacc_sql.y"
                                  {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2296 "yacc_sql.tab.c"
    break;

  case 90: /* sub_select_attribute: STAR  */
#line 652 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2306 "yacc_sql.tab.c"
    break;

  case 91: /* sub_select_attribute: ID  */
#line 657 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2316 "yacc_sql.tab.c"
    break;

  case 92: /* sub_select_attribute: ID DOT ID  */
#line 662 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2326 "yacc_sql.tab.c"
    break;

  case 93: /* sub2_select_attribute: sub2_aggOp LBRACE STAR RBRACE  */
#line 669 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->sub2_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2336 "yacc_sql.tab.c"
    break;

  case 94: /* sub2_select_attribute: sub2_aggOp LBRACE NUMBER RBRACE  */
#line 674 "yacc_sql.y"
                                          {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->sub2_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2346 "yacc_sql.tab.c"
    break;

  case 95: /* sub2_select_attribute: sub2_aggOp LBRACE ID RBRACE  */
#line 679 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->sub2_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2356 "yacc_sql.tab.c"
    break;

  case 96: /* sub2_select_attribute: sub2_aggOp LBRACE ID DOT ID RBRACE  */
#line 684 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->sub2_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2366 "yacc_sql.tab.c"
    break;

  case 97: /* sub2_select_attribute: sub2_aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 689 "yacc_sql.y"
                                                                                          {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2376 "yacc_sql.tab.c"
    break;

  case 98: /* sub2_select_attribute: sub2_aggOp LBRACE RBRACE  */
#line 694 "yacc_sql.y"
                                   {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2386 "yacc_sql.tab.c"
    break;

  case 99: /* sub2_select_attribute: STAR  */
#line 699 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2396 "yacc_sql.tab.c"
    break;

  case 100: /* sub2_select_attribute: ID  */
#line 704 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2406 "yacc_sql.tab.c"
    break;

  case 101: /* sub2_select_attribute: ID DOT ID  */
#line 709 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2416 "yacc_sql.tab.c"
    break;

  case 102: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE STAR RBRACE  */
#line 716 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->sub_sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2426 "yacc_sql.tab.c"
    break;

  case 103: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE NUMBER RBRACE  */
#line 721 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->sub_sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2436 "yacc_sql.tab.c"
    break;

  case 104: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE ID RBRACE  */
#line 726 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->sub_sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2446 "yacc_sql.tab.c"
    break;

  case 105: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE ID DOT ID RBRACE  */
#line 731 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->sub_sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2456 "yacc_sql.tab.c"
    break;

  case 106: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 736 "yacc_sql.y"
                                                                                             {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2466 "yacc_sql.tab.c"
    break;

  case 107: /* sub_sub_select_attribute: sub_sub_aggOp LBRACE RBRACE  */
#line 741 "yacc_sql.y"
                                      {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2476 "yacc_sql.tab.c"
    break;

  case 108: /* sub_sub_select_attribute: STAR  */
#line 746 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2486 "yacc_sql.tab.c"
    break;

  case 109: /* sub_sub_select_attribute: ID  */
#line 751 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2496 "yacc_sql.tab.c"
    break;

  case 110: /* sub_sub_select_attribute: ID DOT ID  */
#line 756 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[2], &attr);
		}
#line 2506 "yacc_sql.tab.c"
    break;

  case 111: /* select_attr: select_attribute attr_list  */
#line 763 "yacc_sql.y"
                                   {

		}
#line 2514 "yacc_sql.tab.c"
    break;

  case 112: /* select_attribute: aggOp LBRACE STAR RBRACE  */
#line 768 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2524 "yacc_sql.tab.c"
    break;

  case 113: /* select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 773 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2534 "yacc_sql.tab.c"
    break;

  case 114: /* select_attribute: aggOp LBRACE ID RBRACE  */
#line 778 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2544 "yacc_sql.tab.c"
    break;

  case 115: /* select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 783 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2554 "yacc_sql.tab.c"
    break;

  case 116: /* select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 788 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2564 "yacc_sql.tab.c"
    break;

  case 117: /* select_attribute: aggOp LBRACE RBRACE  */
#line 793 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2574 "yacc_sql.tab.c"
    break;

  case 118: /* select_attribute: STAR  */
#line 798 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2584 "yacc_sql.tab.c"
    break;

  case 119: /* select_attribute: ID  */
#line 803 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2594 "yacc_sql.tab.c"
    break;

  case 120: /* select_attribute: ID DOT ID  */
#line 808 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2604 "yacc_sql.tab.c"
    break;

  case 122: /* attr_list: COMMA select_attribute attr_list  */
#line 816 "yacc_sql.y"
                                           {

		}
#line 2612 "yacc_sql.tab.c"
    break;

  case 123: /* aggr_select_attr: STAR  */
#line 821 "yacc_sql.y"
        {  
      
		}
#line 2620 "yacc_sql.tab.c"
    break;

  case 124: /* aggr_select_attr: ID  */
#line 824 "yacc_sql.y"
         {

		}
#line 2628 "yacc_sql.tab.c"
    break;

  case 125: /* aggr_select_attr: ID DOT ID  */
#line 827 "yacc_sql.y"
                    {

		}
#line 2636 "yacc_sql.tab.c"
    break;

  case 127: /* aggr_attr_list: COMMA STAR aggr_attr_list  */
#line 833 "yacc_sql.y"
                                {
      
      }
#line 2644 "yacc_sql.tab.c"
    break;

  case 128: /* aggr_attr_list: COMMA ID aggr_attr_list  */
#line 836 "yacc_sql.y"
                              {
      
      }
#line 2652 "yacc_sql.tab.c"
    break;

  case 129: /* aggr_attr_list: COMMA ID DOT ID aggr_attr_list  */
#line 839 "yacc_sql.y"
                                     {
      
  	  }
#line 2660 "yacc_sql.tab.c"
    break;

  case 131: /* rel_list: COMMA ID rel_list  */
#line 847 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-1].string));
		  }
#line 2668 "yacc_sql.tab.c"
    break;

  case 132: /* rel_list: INNER JOIN ID inner_join_on rel_list  */
#line 851 "yacc_sql.y"
                                           {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-2].string));
		  }
#line 2676 "yacc_sql.tab.c"
    break;

  case 134: /* where: WHERE condition condition_list  */
#line 857 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2684 "yacc_sql.tab.c"
    break;

  case 136: /* inner_join_on: ON condition condition_list  */
#line 863 "yacc_sql.y"
                                  {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2692 "yacc_sql.tab.c"
    break;

  case 138: /* condition_list: AND bcondition condition_list  */
#line 869 "yacc_sql.y"
                                    {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2700 "yacc_sql.tab.c"
    break;

  case 139: /* condition: ID comOp value  */
#line 875 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2725 "yacc_sql.tab.c"
    break;

  case 140: /* condition: value comOp value  */
#line 896 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2749 "yacc_sql.tab.c"
    break;

  case 141: /* condition: ID comOp ID  */
#line 916 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2773 "yacc_sql.tab.c"
    break;

  case 142: /* condition: value comOp ID  */
#line 936 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2799 "yacc_sql.tab.c"
    break;

  case 143: /* condition: ID DOT ID comOp value  */
#line 958 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2824 "yacc_sql.tab.c"
    break;

  case 144: /* condition: value comOp ID DOT ID  */
#line 979 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2849 "yacc_sql.tab.c"
    break;

  case 145: /* condition: ID DOT ID comOp ID DOT ID  */
#line 1000 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2872 "yacc_sql.tab.c"
    break;

  case 146: /* condition: ID DOT ID comOp sub_select  */
#line 1019 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2893 "yacc_sql.tab.c"
    break;

  case 147: /* condition: ID comOp sub_select  */
#line 1036 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2915 "yacc_sql.tab.c"
    break;

  case 148: /* condition: sub_select comOp ID DOT ID  */
#line 1054 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2936 "yacc_sql.tab.c"
    break;

  case 149: /* condition: sub_select comOp ID  */
#line 1071 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2958 "yacc_sql.tab.c"
    break;

  case 150: /* condition: sub_select comOp sub2_select  */
#line 1089 "yacc_sql.y"
                {

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 0, NULL, NULL, 0, NULL, NULL, 1, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2978 "yacc_sql.tab.c"
    break;

  case 151: /* bcondition: ID comOp value  */
#line 1107 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3003 "yacc_sql.tab.c"
    break;

  case 152: /* bcondition: value comOp value  */
#line 1128 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3027 "yacc_sql.tab.c"
    break;

  case 153: /* bcondition: ID comOp ID  */
#line 1148 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3051 "yacc_sql.tab.c"
    break;

  case 154: /* bcondition: value comOp ID  */
#line 1168 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 3077 "yacc_sql.tab.c"
    break;

  case 155: /* bcondition: ID DOT ID comOp value  */
#line 1190 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 3102 "yacc_sql.tab.c"
    break;

  case 156: /* bcondition: value comOp ID DOT ID  */
#line 1211 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 3127 "yacc_sql.tab.c"
    break;

  case 157: /* bcondition: ID DOT ID comOp ID DOT ID  */
#line 1232 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3150 "yacc_sql.tab.c"
    break;

  case 158: /* bcondition: ID DOT ID comOp sub2_select  */
#line 1251 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3171 "yacc_sql.tab.c"
    break;

  case 159: /* bcondition: ID comOp sub2_select  */
#line 1268 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3193 "yacc_sql.tab.c"
    break;

  case 160: /* bcondition: sub2_select comOp ID DOT ID  */
#line 1286 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3214 "yacc_sql.tab.c"
    break;

  case 161: /* bcondition: sub2_select comOp ID  */
#line 1303 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3236 "yacc_sql.tab.c"
    break;

  case 163: /* sub_where: WHERE sub_condition sub_condition_list  */
#line 1323 "yacc_sql.y"
                                             {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3244 "yacc_sql.tab.c"
    break;

  case 165: /* sub_condition_list: AND sub_condition sub_condition_list  */
#line 1329 "yacc_sql.y"
                                           {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3252 "yacc_sql.tab.c"
    break;

  case 166: /* sub_condition: ID sub_comOp value  */
#line 1335 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3277 "yacc_sql.tab.c"
    break;

  case 167: /* sub_condition: value sub_comOp value  */
#line 1356 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3301 "yacc_sql.tab.c"
    break;

  case 168: /* sub_condition: ID sub_comOp ID  */
#line 1376 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3325 "yacc_sql.tab.c"
    break;

  case 169: /* sub_condition: value sub_comOp ID  */
#line 1396 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 3351 "yacc_sql.tab.c"
    break;

  case 170: /* sub_condition: ID DOT ID sub_comOp value  */
#line 1418 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 3376 "yacc_sql.tab.c"
    break;

  case 171: /* sub_condition: value sub_comOp ID DOT ID  */
#line 1439 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 3401 "yacc_sql.tab.c"
    break;

  case 172: /* sub_condition: ID DOT ID sub_comOp ID DOT ID  */
#line 1460 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3424 "yacc_sql.tab.c"
    break;

  case 173: /* sub_condition: ID DOT ID sub_comOp sub_sub_select  */
#line 1479 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3445 "yacc_sql.tab.c"
    break;

  case 174: /* sub_condition: ID sub_comOp sub_sub_select  */
#line 1496 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3467 "yacc_sql.tab.c"
    break;

  case 175: /* sub_condition: sub_sub_select sub_comOp ID DOT ID  */
#line 1514 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->sub_comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3488 "yacc_sql.tab.c"
    break;

  case 176: /* sub_condition: sub_sub_select sub_comOp ID  */
#line 1531 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->sub_comp), 1, &left_attr, NULL, 0, NULL, NULL, 0, 1);
			CONTEXT->sub_conditions[CONTEXT->sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3510 "yacc_sql.tab.c"
    break;

  case 178: /* sub2_where: WHERE sub2_condition sub2_condition_list  */
#line 1551 "yacc_sql.y"
                                               {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3518 "yacc_sql.tab.c"
    break;

  case 180: /* sub2_condition_list: AND sub2_condition sub2_condition_list  */
#line 1557 "yacc_sql.y"
                                             {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3526 "yacc_sql.tab.c"
    break;

  case 181: /* sub2_condition: ID sub2_comOp value  */
#line 1563 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3551 "yacc_sql.tab.c"
    break;

  case 182: /* sub2_condition: value sub2_comOp value  */
#line 1584 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3575 "yacc_sql.tab.c"
    break;

  case 183: /* sub2_condition: ID sub2_comOp ID  */
#line 1604 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3599 "yacc_sql.tab.c"
    break;

  case 184: /* sub2_condition: value sub2_comOp ID  */
#line 1624 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 3625 "yacc_sql.tab.c"
    break;

  case 185: /* sub2_condition: ID DOT ID sub2_comOp value  */
#line 1646 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 3650 "yacc_sql.tab.c"
    break;

  case 186: /* sub2_condition: value sub2_comOp ID DOT ID  */
#line 1667 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 3675 "yacc_sql.tab.c"
    break;

  case 187: /* sub2_condition: ID DOT ID sub2_comOp ID DOT ID  */
#line 1688 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub2_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub2_conditions[CONTEXT->sub2_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3698 "yacc_sql.tab.c"
    break;

  case 189: /* sub_sub_where: WHERE sub_sub_condition sub_sub_condition_list  */
#line 1709 "yacc_sql.y"
                                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3706 "yacc_sql.tab.c"
    break;

  case 191: /* sub_sub_condition_list: AND sub_sub_condition sub_sub_condition_list  */
#line 1715 "yacc_sql.y"
                                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 3714 "yacc_sql.tab.c"
    break;

  case 192: /* sub_sub_condition: ID sub_sub_comOp value  */
#line 1721 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3739 "yacc_sql.tab.c"
    break;

  case 193: /* sub_sub_condition: value sub_sub_comOp value  */
#line 1742 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 3763 "yacc_sql.tab.c"
    break;

  case 194: /* sub_sub_condition: ID sub_sub_comOp ID  */
#line 1762 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 3787 "yacc_sql.tab.c"
    break;

  case 195: /* sub_sub_condition: value sub_sub_comOp ID  */
#line 1782 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 3813 "yacc_sql.tab.c"
    break;

  case 196: /* sub_sub_condition: ID DOT ID sub_sub_comOp value  */
#line 1804 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 3838 "yacc_sql.tab.c"
    break;

  case 197: /* sub_sub_condition: value sub_sub_comOp ID DOT ID  */
#line 1825 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 3863 "yacc_sql.tab.c"
    break;

  case 198: /* sub_sub_condition: ID DOT ID sub_sub_comOp ID DOT ID  */
#line 1846 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->sub_sub_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->sub_sub_conditions[CONTEXT->sub_sub_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 3886 "yacc_sql.tab.c"
    break;

  case 199: /* comOp: NOT IN  */
#line 1867 "yacc_sql.y"
                 { CONTEXT->comp = COMP_NOT_IN; }
#line 3892 "yacc_sql.tab.c"
    break;

  case 200: /* comOp: IN  */
#line 1868 "yacc_sql.y"
             { CONTEXT->comp = COMP_IN; }
#line 3898 "yacc_sql.tab.c"
    break;

  case 201: /* comOp: EQ  */
#line 1869 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 3904 "yacc_sql.tab.c"
    break;

  case 202: /* comOp: LT  */
#line 1870 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 3910 "yacc_sql.tab.c"
    break;

  case 203: /* comOp: GT  */
#line 1871 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 3916 "yacc_sql.tab.c"
    break;

  case 204: /* comOp: LE  */
#line 1872 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 3922 "yacc_sql.tab.c"
    break;

  case 205: /* comOp: GE  */
#line 1873 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 3928 "yacc_sql.tab.c"
    break;

  case 206: /* comOp: NE  */
#line 1874 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 3934 "yacc_sql.tab.c"
    break;

  case 207: /* comOp: IS NOT  */
#line 1875 "yacc_sql.y"
                 { CONTEXT->comp = COMP_IS_NOT; }
#line 3940 "yacc_sql.tab.c"
    break;

  case 208: /* comOp: IS  */
#line 1876 "yacc_sql.y"
             { CONTEXT->comp = COMP_IS; }
#line 3946 "yacc_sql.tab.c"
    break;

  case 209: /* sub_comOp: NOT IN  */
#line 1879 "yacc_sql.y"
                 { CONTEXT->sub_comp = COMP_NOT_IN; }
#line 3952 "yacc_sql.tab.c"
    break;

  case 210: /* sub_comOp: IN  */
#line 1880 "yacc_sql.y"
             { CONTEXT->sub_comp = COMP_IN; }
#line 3958 "yacc_sql.tab.c"
    break;

  case 211: /* sub_comOp: EQ  */
#line 1881 "yacc_sql.y"
             { CONTEXT->sub_comp = EQUAL_TO; }
#line 3964 "yacc_sql.tab.c"
    break;

  case 212: /* sub_comOp: LT  */
#line 1882 "yacc_sql.y"
         { CONTEXT->sub_comp = LESS_THAN; }
#line 3970 "yacc_sql.tab.c"
    break;

  case 213: /* sub_comOp: GT  */
#line 1883 "yacc_sql.y"
         { CONTEXT->sub_comp = GREAT_THAN; }
#line 3976 "yacc_sql.tab.c"
    break;

  case 214: /* sub_comOp: LE  */
#line 1884 "yacc_sql.y"
         { CONTEXT->sub_comp = LESS_EQUAL; }
#line 3982 "yacc_sql.tab.c"
    break;

  case 215: /* sub_comOp: GE  */
#line 1885 "yacc_sql.y"
         { CONTEXT->sub_comp = GREAT_EQUAL; }
#line 3988 "yacc_sql.tab.c"
    break;

  case 216: /* sub_comOp: NE  */
#line 1886 "yacc_sql.y"
         { CONTEXT->sub_comp = NOT_EQUAL; }
#line 3994 "yacc_sql.tab.c"
    break;

  case 217: /* sub_comOp: IS NOT  */
#line 1887 "yacc_sql.y"
                 { CONTEXT->sub_comp = COMP_IS_NOT; }
#line 4000 "yacc_sql.tab.c"
    break;

  case 218: /* sub_comOp: IS  */
#line 1888 "yacc_sql.y"
             { CONTEXT->sub_comp = COMP_IS; }
#line 4006 "yacc_sql.tab.c"
    break;

  case 219: /* sub2_comOp: NOT IN  */
#line 1891 "yacc_sql.y"
                 { CONTEXT->sub2_comp = COMP_NOT_IN; }
#line 4012 "yacc_sql.tab.c"
    break;

  case 220: /* sub2_comOp: IN  */
#line 1892 "yacc_sql.y"
             { CONTEXT->sub2_comp = COMP_IN; }
#line 4018 "yacc_sql.tab.c"
    break;

  case 221: /* sub2_comOp: EQ  */
#line 1893 "yacc_sql.y"
             { CONTEXT->sub2_comp = EQUAL_TO; }
#line 4024 "yacc_sql.tab.c"
    break;

  case 222: /* sub2_comOp: LT  */
#line 1894 "yacc_sql.y"
         { CONTEXT->sub2_comp = LESS_THAN; }
#line 4030 "yacc_sql.tab.c"
    break;

  case 223: /* sub2_comOp: GT  */
#line 1895 "yacc_sql.y"
         { CONTEXT->sub2_comp = GREAT_THAN; }
#line 4036 "yacc_sql.tab.c"
    break;

  case 224: /* sub2_comOp: LE  */
#line 1896 "yacc_sql.y"
         { CONTEXT->sub2_comp = LESS_EQUAL; }
#line 4042 "yacc_sql.tab.c"
    break;

  case 225: /* sub2_comOp: GE  */
#line 1897 "yacc_sql.y"
         { CONTEXT->sub2_comp = GREAT_EQUAL; }
#line 4048 "yacc_sql.tab.c"
    break;

  case 226: /* sub2_comOp: NE  */
#line 1898 "yacc_sql.y"
         { CONTEXT->sub2_comp = NOT_EQUAL; }
#line 4054 "yacc_sql.tab.c"
    break;

  case 227: /* sub2_comOp: IS NOT  */
#line 1899 "yacc_sql.y"
                 { CONTEXT->sub2_comp = COMP_IS_NOT; }
#line 4060 "yacc_sql.tab.c"
    break;

  case 228: /* sub2_comOp: IS  */
#line 1900 "yacc_sql.y"
             { CONTEXT->sub2_comp = COMP_IS; }
#line 4066 "yacc_sql.tab.c"
    break;

  case 229: /* sub_sub_comOp: NOT IN  */
#line 1903 "yacc_sql.y"
                 { CONTEXT->sub_sub_comp = COMP_NOT_IN; }
#line 4072 "yacc_sql.tab.c"
    break;

  case 230: /* sub_sub_comOp: IN  */
#line 1904 "yacc_sql.y"
             { CONTEXT->sub_sub_comp = COMP_IN; }
#line 4078 "yacc_sql.tab.c"
    break;

  case 231: /* sub_sub_comOp: EQ  */
#line 1905 "yacc_sql.y"
             { CONTEXT->sub_sub_comp = EQUAL_TO; }
#line 4084 "yacc_sql.tab.c"
    break;

  case 232: /* sub_sub_comOp: LT  */
#line 1906 "yacc_sql.y"
         { CONTEXT->sub_sub_comp = LESS_THAN; }
#line 4090 "yacc_sql.tab.c"
    break;

  case 233: /* sub_sub_comOp: GT  */
#line 1907 "yacc_sql.y"
         { CONTEXT->sub_sub_comp = GREAT_THAN; }
#line 4096 "yacc_sql.tab.c"
    break;

  case 234: /* sub_sub_comOp: LE  */
#line 1908 "yacc_sql.y"
         { CONTEXT->sub_sub_comp = LESS_EQUAL; }
#line 4102 "yacc_sql.tab.c"
    break;

  case 235: /* sub_sub_comOp: GE  */
#line 1909 "yacc_sql.y"
         { CONTEXT->sub_sub_comp = GREAT_EQUAL; }
#line 4108 "yacc_sql.tab.c"
    break;

  case 236: /* sub_sub_comOp: NE  */
#line 1910 "yacc_sql.y"
         { CONTEXT->sub_sub_comp = NOT_EQUAL; }
#line 4114 "yacc_sql.tab.c"
    break;

  case 237: /* sub_sub_comOp: IS NOT  */
#line 1911 "yacc_sql.y"
                 { CONTEXT->sub_sub_comp = COMP_IS_NOT; }
#line 4120 "yacc_sql.tab.c"
    break;

  case 238: /* sub_sub_comOp: IS  */
#line 1912 "yacc_sql.y"
             { CONTEXT->sub_sub_comp = COMP_IS; }
#line 4126 "yacc_sql.tab.c"
    break;

  case 239: /* aggOp: AGG_COUNT  */
#line 1916 "yacc_sql.y"
                    { CONTEXT->aggop = COUNT; }
#line 4132 "yacc_sql.tab.c"
    break;

  case 240: /* aggOp: AGG_MAX  */
#line 1917 "yacc_sql.y"
                  { CONTEXT->aggop = MAX; }
#line 4138 "yacc_sql.tab.c"
    break;

  case 241: /* aggOp: AGG_MIN  */
#line 1918 "yacc_sql.y"
                  { CONTEXT->aggop = MIN; }
#line 4144 "yacc_sql.tab.c"
    break;

  case 242: /* aggOp: AGG_AVG  */
#line 1919 "yacc_sql.y"
                  { CONTEXT->aggop = AVG; }
#line 4150 "yacc_sql.tab.c"
    break;

  case 243: /* sub_aggOp: AGG_COUNT  */
#line 1922 "yacc_sql.y"
                    { CONTEXT->sub_aggop = COUNT; }
#line 4156 "yacc_sql.tab.c"
    break;

  case 244: /* sub_aggOp: AGG_MAX  */
#line 1923 "yacc_sql.y"
                  { CONTEXT->sub_aggop = MAX; }
#line 4162 "yacc_sql.tab.c"
    break;

  case 245: /* sub_aggOp: AGG_MIN  */
#line 1924 "yacc_sql.y"
                  { CONTEXT->sub_aggop = MIN; }
#line 4168 "yacc_sql.tab.c"
    break;

  case 246: /* sub_aggOp: AGG_AVG  */
#line 1925 "yacc_sql.y"
                  { CONTEXT->sub_aggop = AVG; }
#line 4174 "yacc_sql.tab.c"
    break;

  case 247: /* sub2_aggOp: AGG_COUNT  */
#line 1927 "yacc_sql.y"
                    { CONTEXT->sub2_aggop = COUNT; }
#line 4180 "yacc_sql.tab.c"
    break;

  case 248: /* sub2_aggOp: AGG_MAX  */
#line 1928 "yacc_sql.y"
                  { CONTEXT->sub2_aggop = MAX; }
#line 4186 "yacc_sql.tab.c"
    break;

  case 249: /* sub2_aggOp: AGG_MIN  */
#line 1929 "yacc_sql.y"
                  { CONTEXT->sub2_aggop = MIN; }
#line 4192 "yacc_sql.tab.c"
    break;

  case 250: /* sub2_aggOp: AGG_AVG  */
#line 1930 "yacc_sql.y"
                  { CONTEXT->sub2_aggop = AVG; }
#line 4198 "yacc_sql.tab.c"
    break;

  case 251: /* sub_sub_aggOp: AGG_COUNT  */
#line 1933 "yacc_sql.y"
                    { CONTEXT->sub_sub_aggop = COUNT; }
#line 4204 "yacc_sql.tab.c"
    break;

  case 252: /* sub_sub_aggOp: AGG_MAX  */
#line 1934 "yacc_sql.y"
                  { CONTEXT->sub_sub_aggop = MAX; }
#line 4210 "yacc_sql.tab.c"
    break;

  case 253: /* sub_sub_aggOp: AGG_MIN  */
#line 1935 "yacc_sql.y"
                  { CONTEXT->sub_sub_aggop = MIN; }
#line 4216 "yacc_sql.tab.c"
    break;

  case 254: /* sub_sub_aggOp: AGG_AVG  */
#line 1936 "yacc_sql.y"
                  { CONTEXT->sub_sub_aggop = AVG; }
#line 4222 "yacc_sql.tab.c"
    break;

  case 255: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1941 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 4231 "yacc_sql.tab.c"
    break;


#line 4235 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1946 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
