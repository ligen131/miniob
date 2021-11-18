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

  size_t sub_sub_condition_length;
  Condition sub_sub_conditions[MAX_NUM];

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


#line 171 "yacc_sql.tab.c"

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
  YYSYMBOL_order_by = 100,                 /* order_by  */
  YYSYMBOL_select_order_list = 101,        /* select_order_list  */
  YYSYMBOL_select_order = 102,             /* select_order  */
  YYSYMBOL_group_by = 103,                 /* group_by  */
  YYSYMBOL_select_group_list = 104,        /* select_group_list  */
  YYSYMBOL_select_group = 105,             /* select_group  */
  YYSYMBOL_sub_select_attribute = 106,     /* sub_select_attribute  */
  YYSYMBOL_select_attr = 107,              /* select_attr  */
  YYSYMBOL_select_attribute = 108,         /* select_attribute  */
  YYSYMBOL_attr_list = 109,                /* attr_list  */
  YYSYMBOL_aggr_select_attr = 110,         /* aggr_select_attr  */
  YYSYMBOL_aggr_attr_list = 111,           /* aggr_attr_list  */
  YYSYMBOL_rel_list = 112,                 /* rel_list  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_inner_join_on = 114,            /* inner_join_on  */
  YYSYMBOL_condition_list = 115,           /* condition_list  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_sub_where = 117,                /* sub_where  */
  YYSYMBOL_sub_condition_list = 118,       /* sub_condition_list  */
  YYSYMBOL_sub_condition = 119,            /* sub_condition  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_aggOp = 121,                    /* aggOp  */
  YYSYMBOL_load_data = 122                 /* load_data  */
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
#define YYLAST   345

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  318

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
       0,   195,   195,   197,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   221,   226,   231,   237,   243,   249,   255,   261,   267,
     274,   281,   289,   291,   297,   304,   313,   315,   319,   330,
     341,   352,   363,   374,   387,   390,   391,   392,   393,   394,
     397,   406,   423,   427,   429,   434,   436,   441,   444,   447,
     451,   455,   461,   471,   481,   499,   513,   515,   519,   521,
     526,   531,   536,   541,   546,   551,   557,   559,   563,   565,
     570,   575,   582,   587,   592,   597,   602,   607,   612,   617,
     622,   629,   634,   639,   644,   649,   654,   659,   664,   669,
     674,   680,   682,   687,   690,   693,   697,   699,   702,   705,
     711,   713,   717,   721,   723,   727,   729,   733,   735,   740,
     761,   781,   801,   823,   844,   865,   884,   901,   919,   936,
     955,   957,   961,   963,   968,   989,  1009,  1029,  1051,  1072,
    1093,  1150,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
    1159,  1163,  1164,  1165,  1166,  1170
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
  "select", "sub_select", "order_by", "select_order_list", "select_order",
  "group_by", "select_group_list", "select_group", "sub_select_attribute",
  "select_attr", "select_attribute", "attr_list", "aggr_select_attr",
  "aggr_attr_list", "rel_list", "where", "inner_join_on", "condition_list",
  "condition", "sub_where", "sub_condition_list", "sub_condition", "comOp",
  "aggOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-211)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -211,    16,  -211,     3,    42,    55,   -47,    79,    19,     2,
      65,    35,    99,   107,   118,   119,   121,    85,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,  -211,  -211,    61,    72,   122,    77,
      78,  -211,  -211,  -211,  -211,   115,  -211,   123,   135,   142,
     157,   158,  -211,   101,   102,   126,  -211,  -211,  -211,  -211,
    -211,   136,   165,   148,   127,   181,   188,   132,   143,    55,
    -211,     1,  -211,  -211,   169,   185,   150,   153,   162,   163,
     192,  -211,  -211,  -211,    15,   135,  -211,   212,    -3,   213,
     214,   215,    -5,   231,   193,   205,  -211,   218,   199,   221,
     174,   175,   186,   185,  -211,  -211,  -211,   176,  -211,     6,
     154,   224,   235,  -211,  -211,  -211,  -211,    71,  -211,   106,
     106,   210,  -211,   154,   240,   162,   229,  -211,  -211,  -211,
    -211,  -211,    -7,   183,   232,    15,   187,   198,   233,   223,
    -211,   236,   237,   215,   251,    90,   194,  -211,  -211,  -211,
    -211,  -211,  -211,  -211,   200,   219,    18,   109,   195,    -5,
    -211,   185,   196,   218,   259,   201,   206,  -211,   245,   202,
    -211,   234,   216,   220,  -211,   203,    26,   248,   154,   254,
     224,  -211,   239,  -211,   241,   258,   106,  -211,  -211,  -211,
    -211,  -211,   246,  -211,   247,   210,   275,   276,  -211,  -211,
    -211,   262,  -211,   217,   263,   245,    -5,    15,   222,   230,
     280,  -211,    22,   236,  -211,   237,  -211,  -211,   225,   226,
      31,    25,   227,   228,  -211,  -211,  -211,    37,   245,   282,
     268,   210,  -211,    13,   269,   238,  -211,   242,  -211,  -211,
    -211,  -211,   255,  -211,   277,    49,   278,   279,   264,  -211,
    -211,  -211,  -211,   243,  -211,  -211,  -211,   294,  -211,  -211,
    -211,   244,   222,  -211,   270,   285,   236,   116,   281,  -211,
    -211,   249,  -211,     6,   250,  -211,  -211,    97,   269,   252,
     238,  -211,  -211,    89,   106,   266,  -211,   287,   236,  -211,
    -211,  -211,  -211,  -211,   285,   253,   131,   140,   116,  -211,
    -211,   288,  -211,   106,  -211,  -211,   283,  -211,   266,  -211,
     147,   256,  -211,   286,  -211,  -211,   257,  -211
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
       0,   151,   152,   153,   154,    99,    98,     0,   101,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    29,    28,     0,   113,     0,     0,     0,     0,
       0,    27,    34,   100,   110,   101,    97,     0,   104,   103,
       0,     0,     0,     0,     0,     0,    50,    36,     0,     0,
       0,     0,     0,   113,   102,    93,    94,     0,    92,     0,
       0,    53,     0,    61,    57,    58,    59,     0,    60,     0,
       0,   117,    62,     0,     0,     0,     0,    45,    46,    47,
      48,    49,    41,     0,     0,   110,     0,    66,   105,   104,
     103,   106,    55,     0,     0,     0,     0,   149,   141,   142,
     143,   144,   145,   146,   148,     0,     0,     0,     0,     0,
     114,   113,     0,    36,     0,     0,     0,    43,    32,     0,
     111,   115,     0,    76,    95,     0,     0,     0,     0,     0,
      53,    51,    89,    88,     0,     0,     0,   147,   150,   121,
     119,   127,   122,   120,   129,   117,     0,     0,    37,    35,
      44,     0,    42,     0,     0,    32,     0,   110,     0,     0,
       0,   105,   106,   106,    96,    55,    52,    54,     0,     0,
       0,     0,     0,     0,   118,    63,   155,    38,    32,     0,
       0,   117,   112,    70,    68,     0,    64,     0,   108,   107,
      56,    90,   130,    87,     0,   104,   103,     0,     0,   123,
     126,   124,   128,     0,    40,    33,    30,     0,   116,    72,
      71,     0,     0,    67,    80,    78,   106,     0,     0,    83,
      84,     0,    82,     0,     0,    39,    31,    73,    68,     0,
       0,    77,   109,     0,     0,   132,    65,   105,   106,   125,
      75,    74,    69,    81,    78,     0,     0,     0,     0,   131,
      85,     0,    79,     0,   136,   134,   137,   135,   132,    86,
       0,     0,   133,     0,   138,   139,     0,   140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,  -211,
    -211,  -211,  -211,  -188,  -211,  -211,   145,   204,  -211,  -211,
    -211,  -211,   167,   139,    96,  -110,  -211,  -211,  -211,  -148,
    -211,    34,    58,  -211,    29,    44,  -211,  -211,   261,   260,
    -108,  -210,  -131,   -96,  -211,  -156,  -145,  -211,    17,    28,
    -114,   182,  -211
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   204,    29,    30,   126,    97,   201,   132,
      98,    31,   111,   144,   179,   119,    32,    33,    34,   120,
     173,   263,   234,   210,   281,   265,   184,    47,    48,    70,
      90,   177,   103,    93,   207,   160,   121,   268,   299,   285,
     156,    49,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     142,   141,   238,   239,   170,   157,   158,   137,   191,    36,
     165,    37,   112,   161,   195,   106,     2,   230,    50,    86,
       3,     4,    52,   259,   260,     5,     6,   107,     7,     8,
       9,    10,    11,    53,   101,   112,    12,    13,    14,   224,
     255,   176,   112,   261,    15,    16,   190,   193,    39,   243,
      40,   166,   237,   167,   113,    17,   282,   114,   115,   116,
     117,   231,   118,    87,    38,   196,    88,   270,   215,    89,
     102,   139,   221,   250,   140,   258,   232,   113,   301,   271,
     114,   115,   116,   189,   113,   118,    51,   114,   115,   116,
     248,   212,   118,   244,   213,   253,   245,   254,    54,   246,
      55,   146,    56,    41,    42,    43,    44,   290,   291,   147,
      57,   249,   247,   148,   149,   150,   151,   152,   153,   295,
      45,    58,    59,    46,    60,    61,    62,   147,   154,   155,
      64,   148,   149,   150,   151,   152,   153,    63,    41,    42,
      43,    44,    65,    66,   147,    67,   154,   155,   148,   149,
     150,   151,   152,   153,    69,   182,    68,   284,   183,    71,
      72,    73,    76,   154,   155,   288,    74,    75,   113,   296,
     297,   114,   115,   116,   192,   113,   118,    77,   114,   115,
     116,   283,    78,   118,    81,    79,   305,   307,   284,   310,
     113,    82,    80,   114,   115,   116,   304,    83,   118,   113,
     314,    91,   114,   115,   116,   306,   113,   118,    84,   114,
     115,   116,   313,   113,   118,    94,   114,   115,   116,    92,
      95,   118,   127,   128,   129,   130,   131,    96,    99,   100,
     105,   108,   110,   109,   122,   123,   124,   125,   133,   134,
     135,   138,   136,   143,   145,   159,   162,   164,   168,   169,
     172,   174,   171,   175,   181,   176,   178,   188,   187,   186,
     194,   197,   199,   200,   203,   202,   214,   205,   211,   218,
     208,   206,   216,   209,   219,   220,   222,   223,   225,   226,
     227,   229,   228,   236,   235,   256,   257,   233,   262,   267,
     241,   242,   251,   252,   274,   269,   272,   276,   273,   286,
     279,   298,   275,   264,   280,   300,   309,   266,   198,   277,
     180,   240,   292,   311,   287,   289,   316,   293,   303,   217,
     278,   315,   317,   302,   294,   312,   308,   185,     0,   163,
      85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104
};

static const yytype_int16 yycheck[] =
{
     110,   109,   212,   213,   135,   119,   120,   103,   156,     6,
      17,     8,    17,   123,   159,    18,     0,   205,    65,    18,
       4,     5,     3,    10,    11,     9,    10,    30,    12,    13,
      14,    15,    16,    31,    19,    17,    20,    21,    22,   195,
     228,    19,    17,    30,    28,    29,   156,   157,     6,    18,
       8,    58,    30,    60,    59,    39,   266,    62,    63,    64,
      65,   206,    67,    62,    61,   161,    65,    18,   178,    68,
      55,    65,   186,   221,    68,   231,   207,    59,   288,    30,
      62,    63,    64,    65,    59,    67,     7,    62,    63,    64,
      65,    65,    67,    62,    68,    58,    65,    60,    33,    68,
      65,    30,     3,    48,    49,    50,    51,    10,    11,    38,
       3,   221,   220,    42,    43,    44,    45,    46,    47,    30,
      65,     3,     3,    68,     3,    40,    65,    38,    57,    58,
       8,    42,    43,    44,    45,    46,    47,    65,    48,    49,
      50,    51,    65,    65,    38,    30,    57,    58,    42,    43,
      44,    45,    46,    47,    19,    65,    33,   267,    68,    17,
       3,     3,    36,    57,    58,   273,    65,    65,    59,   283,
     284,    62,    63,    64,    65,    59,    67,    41,    62,    63,
      64,    65,    17,    67,     3,    37,   296,   297,   298,   303,
      59,     3,    65,    62,    63,    64,    65,    65,    67,    59,
     310,    32,    62,    63,    64,    65,    59,    67,    65,    62,
      63,    64,    65,    59,    67,    65,    62,    63,    64,    34,
      67,    67,    23,    24,    25,    26,    27,    65,    65,    37,
      18,    18,    17,    19,     3,    42,    31,    19,    17,    65,
      65,    65,    56,    19,     9,    35,     6,    18,    65,    17,
      52,    18,    65,    30,     3,    19,    19,    38,    58,    65,
      65,    65,     3,    62,    19,    59,    18,    65,    65,    30,
      54,    37,    18,    53,    33,    17,    30,    30,     3,     3,
      18,    18,    65,     3,    54,     3,    18,    65,    19,    34,
      65,    65,    65,    65,    30,    18,    18,     3,    19,    18,
      30,    35,    59,    65,    19,    18,    18,    65,   163,    65,
     143,   215,   278,    30,    65,    65,    30,    65,    65,   180,
     262,    65,    65,   294,   280,   308,   298,   145,    -1,   125,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    85
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,     9,    10,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    39,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    91,    96,    97,    98,   122,     6,     8,    61,     6,
       8,    48,    49,    50,    51,    65,    68,   107,   108,   121,
      65,     7,     3,    31,    33,    65,     3,     3,     3,     3,
       3,    40,    65,    65,     8,    65,    65,    30,    33,    19,
     109,    17,     3,     3,    65,    65,    36,    41,    17,    37,
      65,     3,     3,    65,    65,   108,    18,    62,    65,    68,
     110,    32,    34,   113,    65,    67,    65,    87,    90,    65,
      37,    19,    55,   112,   109,    18,    18,    30,    18,    19,
      17,    92,    17,    59,    62,    63,    64,    65,    67,    95,
      99,   116,     3,    42,    31,    19,    86,    23,    24,    25,
      26,    27,    89,    17,    65,    65,    56,   113,    65,    65,
      68,   110,    95,    19,    93,     9,    30,    38,    42,    43,
      44,    45,    46,    47,    57,    58,   120,   120,   120,    35,
     115,    95,     6,    87,    18,    17,    58,    60,    65,    17,
     112,    65,    52,   100,    18,    30,    19,   111,    19,    94,
      92,     3,    65,    68,   106,   121,    65,    58,    38,    65,
      95,    99,    65,    95,    65,   116,   113,    65,    86,     3,
      62,    88,    59,    19,    83,    65,    37,   114,    54,    53,
     103,    65,    65,    68,    18,    95,    18,    93,    30,    33,
      17,   120,    30,    30,   115,     3,     3,    18,    65,    18,
      83,   116,   112,    65,   102,    54,     3,    30,   111,   111,
      94,    65,    65,    18,    62,    65,    68,   110,    65,    95,
      99,    65,    65,    58,    60,    83,     3,    18,   115,    10,
      11,    30,    19,   101,    65,   105,    65,    34,   117,    18,
      18,    30,    18,    19,    30,    59,     3,    65,   102,    30,
      19,   104,   111,    65,    95,   119,    18,    65,   110,    65,
      10,    11,   101,    65,   105,    30,   120,   120,    35,   118,
      18,   111,   104,    65,    65,    95,    65,    95,   119,    18,
     120,    30,   118,    65,    95,    65,    30,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    82,    83,    83,    84,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    88,    89,    89,    89,    89,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    96,    97,    98,    99,   100,   100,   101,   101,
     102,   102,   102,   102,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   110,   110,   110,   111,   111,   111,   111,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   121,   121,   121,   121,   122
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
       1,     1,     5,     8,     9,     7,     0,     4,     0,     3,
       1,     2,     2,     3,     4,     4,     0,     4,     0,     3,
       1,     3,     4,     4,     4,     6,     7,     3,     1,     1,
       3,     2,     4,     4,     4,     6,     7,     3,     1,     1,
       3,     0,     3,     1,     1,     3,     0,     3,     3,     5,
       0,     3,     5,     0,     3,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     5,     3,     5,     3,
       0,     3,     0,     3,     3,     3,     3,     3,     5,     5,
       7,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     1,     1,     1,     1,     8
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
#line 221 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 226 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 231 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1533 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 237 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1541 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 243 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1549 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 249 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1557 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 255 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1566 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 261 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1574 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 267 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1583 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 275 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 0);
			CONTEXT->index_length = 0;
		}
#line 1594 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 282 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 1);
			CONTEXT->index_length = 0;
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 33: /* create_index_attr_list: COMMA ID create_index_attr_list  */
#line 291 "yacc_sql.y"
                                          {
		CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-1].string));
	}
#line 1613 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 298 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1622 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 305 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1634 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 315 "yacc_sql.y"
                                   {    }
#line 1640 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 320 "yacc_sql.y"
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
#line 1655 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE NOT NULLL  */
#line 331 "yacc_sql.y"
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
#line 1670 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 342 "yacc_sql.y"
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
#line 1685 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type  */
#line 353 "yacc_sql.y"
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
#line 1700 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type NOT NULLL  */
#line 364 "yacc_sql.y"
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
#line 1715 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NULLABLE  */
#line 375 "yacc_sql.y"
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
#line 1730 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 387 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1736 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 390 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1742 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 391 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1748 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 392 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1754 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 393 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1760 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 394 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1766 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 398 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1775 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES data data_list SEMICOLON  */
#line 407 "yacc_sql.y"
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
#line 1795 "yacc_sql.tab.c"
    break;

  case 52: /* data: LBRACE value value_list RBRACE  */
#line 423 "yacc_sql.y"
                                       {
		CONTEXT->data_list_r[CONTEXT->data_num++]=CONTEXT->value_length;
	}
#line 1803 "yacc_sql.tab.c"
    break;

  case 54: /* data_list: COMMA data data_list  */
#line 429 "yacc_sql.y"
                            { 
  		
	  }
#line 1811 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 436 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1819 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 441 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1827 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 444 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1835 "yacc_sql.tab.c"
    break;

  case 59: /* value: DATEE  */
#line 447 "yacc_sql.y"
           {
			(yyvsp[0].dates) = substr((yyvsp[0].dates),1,strlen((yyvsp[0].dates))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].dates));
		}
#line 1844 "yacc_sql.tab.c"
    break;

  case 60: /* value: SSS  */
#line 451 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1853 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULLL  */
#line 455 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1861 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 462 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1873 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 472 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1885 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON  */
#line 482 "yacc_sql.y"
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
#line 1905 "yacc_sql.tab.c"
    break;

  case 65: /* sub_select: LBRACE SELECT sub_select_attribute FROM ID sub_where RBRACE  */
#line 500 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[1], (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[1], CONTEXT->sub_conditions, CONTEXT->sub_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist = 1;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub_condition_length = 0;
	}
#line 1922 "yacc_sql.tab.c"
    break;

  case 67: /* order_by: ORDER BY select_order select_order_list  */
#line 515 "yacc_sql.y"
                                              {
      
    }
#line 1930 "yacc_sql.tab.c"
    break;

  case 69: /* select_order_list: COMMA select_order select_order_list  */
#line 521 "yacc_sql.y"
                                               {

	}
#line 1938 "yacc_sql.tab.c"
    break;

  case 70: /* select_order: ID  */
#line 526 "yacc_sql.y"
           {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1948 "yacc_sql.tab.c"
    break;

  case 71: /* select_order: ID ASC  */
#line 531 "yacc_sql.y"
                 {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1958 "yacc_sql.tab.c"
    break;

  case 72: /* select_order: ID DESC  */
#line 536 "yacc_sql.y"
                  {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1968 "yacc_sql.tab.c"
    break;

  case 73: /* select_order: ID DOT ID  */
#line 541 "yacc_sql.y"
                    {
			OrderBy order;
			orders_init(&order, (yyvsp[-2].string), (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1978 "yacc_sql.tab.c"
    break;

  case 74: /* select_order: ID DOT ID ASC  */
#line 546 "yacc_sql.y"
                        {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1988 "yacc_sql.tab.c"
    break;

  case 75: /* select_order: ID DOT ID DESC  */
#line 551 "yacc_sql.y"
                         {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1998 "yacc_sql.tab.c"
    break;

  case 77: /* group_by: GROUP BY select_group select_group_list  */
#line 559 "yacc_sql.y"
                                                  {

	}
#line 2006 "yacc_sql.tab.c"
    break;

  case 79: /* select_group_list: COMMA select_group select_group_list  */
#line 565 "yacc_sql.y"
                                               {

	}
#line 2014 "yacc_sql.tab.c"
    break;

  case 80: /* select_group: ID  */
#line 570 "yacc_sql.y"
           {
			GroupBy group;
			groups_init(&group, NULL, (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2024 "yacc_sql.tab.c"
    break;

  case 81: /* select_group: ID DOT ID  */
#line 575 "yacc_sql.y"
                    {
			GroupBy group;
			groups_init(&group, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2034 "yacc_sql.tab.c"
    break;

  case 82: /* sub_select_attribute: aggOp LBRACE STAR RBRACE  */
#line 582 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2044 "yacc_sql.tab.c"
    break;

  case 83: /* sub_select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 587 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2054 "yacc_sql.tab.c"
    break;

  case 84: /* sub_select_attribute: aggOp LBRACE ID RBRACE  */
#line 592 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2064 "yacc_sql.tab.c"
    break;

  case 85: /* sub_select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 597 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2074 "yacc_sql.tab.c"
    break;

  case 86: /* sub_select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 602 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2084 "yacc_sql.tab.c"
    break;

  case 87: /* sub_select_attribute: aggOp LBRACE RBRACE  */
#line 607 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2094 "yacc_sql.tab.c"
    break;

  case 88: /* sub_select_attribute: STAR  */
#line 612 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2104 "yacc_sql.tab.c"
    break;

  case 89: /* sub_select_attribute: ID  */
#line 617 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2114 "yacc_sql.tab.c"
    break;

  case 90: /* sub_select_attribute: ID DOT ID  */
#line 622 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2124 "yacc_sql.tab.c"
    break;

  case 91: /* select_attr: select_attribute attr_list  */
#line 629 "yacc_sql.y"
                                   {

		}
#line 2132 "yacc_sql.tab.c"
    break;

  case 92: /* select_attribute: aggOp LBRACE STAR RBRACE  */
#line 634 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2142 "yacc_sql.tab.c"
    break;

  case 93: /* select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 639 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2152 "yacc_sql.tab.c"
    break;

  case 94: /* select_attribute: aggOp LBRACE ID RBRACE  */
#line 644 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2162 "yacc_sql.tab.c"
    break;

  case 95: /* select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 649 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2172 "yacc_sql.tab.c"
    break;

  case 96: /* select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 654 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2182 "yacc_sql.tab.c"
    break;

  case 97: /* select_attribute: aggOp LBRACE RBRACE  */
#line 659 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2192 "yacc_sql.tab.c"
    break;

  case 98: /* select_attribute: STAR  */
#line 664 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2202 "yacc_sql.tab.c"
    break;

  case 99: /* select_attribute: ID  */
#line 669 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2212 "yacc_sql.tab.c"
    break;

  case 100: /* select_attribute: ID DOT ID  */
#line 674 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2222 "yacc_sql.tab.c"
    break;

  case 102: /* attr_list: COMMA select_attribute attr_list  */
#line 682 "yacc_sql.y"
                                           {

		}
#line 2230 "yacc_sql.tab.c"
    break;

  case 103: /* aggr_select_attr: STAR  */
#line 687 "yacc_sql.y"
        {  
      
		}
#line 2238 "yacc_sql.tab.c"
    break;

  case 104: /* aggr_select_attr: ID  */
#line 690 "yacc_sql.y"
         {

		}
#line 2246 "yacc_sql.tab.c"
    break;

  case 105: /* aggr_select_attr: ID DOT ID  */
#line 693 "yacc_sql.y"
                    {

		}
#line 2254 "yacc_sql.tab.c"
    break;

  case 107: /* aggr_attr_list: COMMA STAR aggr_attr_list  */
#line 699 "yacc_sql.y"
                                {
      
      }
#line 2262 "yacc_sql.tab.c"
    break;

  case 108: /* aggr_attr_list: COMMA ID aggr_attr_list  */
#line 702 "yacc_sql.y"
                              {
      
      }
#line 2270 "yacc_sql.tab.c"
    break;

  case 109: /* aggr_attr_list: COMMA ID DOT ID aggr_attr_list  */
#line 705 "yacc_sql.y"
                                     {
      
  	  }
#line 2278 "yacc_sql.tab.c"
    break;

  case 111: /* rel_list: COMMA ID rel_list  */
#line 713 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-1].string));
		  }
#line 2286 "yacc_sql.tab.c"
    break;

  case 112: /* rel_list: INNER JOIN ID inner_join_on rel_list  */
#line 717 "yacc_sql.y"
                                           {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-2].string));
		  }
#line 2294 "yacc_sql.tab.c"
    break;

  case 114: /* where: WHERE condition condition_list  */
#line 723 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2302 "yacc_sql.tab.c"
    break;

  case 116: /* inner_join_on: ON condition condition_list  */
#line 729 "yacc_sql.y"
                                  {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2310 "yacc_sql.tab.c"
    break;

  case 118: /* condition_list: AND condition condition_list  */
#line 735 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2318 "yacc_sql.tab.c"
    break;

  case 119: /* condition: ID comOp value  */
#line 741 "yacc_sql.y"
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
#line 2343 "yacc_sql.tab.c"
    break;

  case 120: /* condition: value comOp value  */
#line 762 "yacc_sql.y"
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
#line 2367 "yacc_sql.tab.c"
    break;

  case 121: /* condition: ID comOp ID  */
#line 782 "yacc_sql.y"
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
#line 2391 "yacc_sql.tab.c"
    break;

  case 122: /* condition: value comOp ID  */
#line 802 "yacc_sql.y"
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
#line 2417 "yacc_sql.tab.c"
    break;

  case 123: /* condition: ID DOT ID comOp value  */
#line 824 "yacc_sql.y"
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
#line 2442 "yacc_sql.tab.c"
    break;

  case 124: /* condition: value comOp ID DOT ID  */
#line 845 "yacc_sql.y"
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
#line 2467 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID DOT ID comOp ID DOT ID  */
#line 866 "yacc_sql.y"
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
#line 2490 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp sub_select  */
#line 885 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 1);
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
#line 2511 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID comOp sub_select  */
#line 902 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Condition condition;
			condition_init_(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, 1);
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
#line 2533 "yacc_sql.tab.c"
    break;

  case 128: /* condition: sub_select comOp ID DOT ID  */
#line 920 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 1);
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
#line 2554 "yacc_sql.tab.c"
    break;

  case 129: /* condition: sub_select comOp ID  */
#line 937 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init_(&condition, Exchange_CompOp(CONTEXT->comp), 1, &left_attr, NULL, 0, NULL, NULL, 1);
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
#line 2576 "yacc_sql.tab.c"
    break;

  case 131: /* sub_where: WHERE sub_condition sub_condition_list  */
#line 957 "yacc_sql.y"
                                             {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2584 "yacc_sql.tab.c"
    break;

  case 133: /* sub_condition_list: AND sub_condition sub_condition_list  */
#line 963 "yacc_sql.y"
                                           {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2592 "yacc_sql.tab.c"
    break;

  case 134: /* sub_condition: ID comOp value  */
#line 969 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2617 "yacc_sql.tab.c"
    break;

  case 135: /* sub_condition: value comOp value  */
#line 990 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
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
#line 2641 "yacc_sql.tab.c"
    break;

  case 136: /* sub_condition: ID comOp ID  */
#line 1010 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2665 "yacc_sql.tab.c"
    break;

  case 137: /* sub_condition: value comOp ID  */
#line 1030 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2691 "yacc_sql.tab.c"
    break;

  case 138: /* sub_condition: ID DOT ID comOp value  */
#line 1052 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2716 "yacc_sql.tab.c"
    break;

  case 139: /* sub_condition: value comOp ID DOT ID  */
#line 1073 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2741 "yacc_sql.tab.c"
    break;

  case 140: /* sub_condition: ID DOT ID comOp ID DOT ID  */
#line 1094 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2764 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: EQ  */
#line 1150 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2770 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: LT  */
#line 1151 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2776 "yacc_sql.tab.c"
    break;

  case 143: /* comOp: GT  */
#line 1152 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2782 "yacc_sql.tab.c"
    break;

  case 144: /* comOp: LE  */
#line 1153 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2788 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: GE  */
#line 1154 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2794 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: NE  */
#line 1155 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2800 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: IS NOT  */
#line 1156 "yacc_sql.y"
                 { CONTEXT->comp = COMP_IS_NOT; }
#line 2806 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: IS  */
#line 1157 "yacc_sql.y"
             { CONTEXT->comp = COMP_IS; }
#line 2812 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: IN  */
#line 1158 "yacc_sql.y"
             { CONTEXT->comp = COMP_IN; }
#line 2818 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: NOT IN  */
#line 1159 "yacc_sql.y"
                 { CONTEXT->comp = COMP_NOT_IN; }
#line 2824 "yacc_sql.tab.c"
    break;

  case 151: /* aggOp: AGG_COUNT  */
#line 1163 "yacc_sql.y"
                    { CONTEXT->aggop = COUNT; }
#line 2830 "yacc_sql.tab.c"
    break;

  case 152: /* aggOp: AGG_MAX  */
#line 1164 "yacc_sql.y"
                  { CONTEXT->aggop = MAX; }
#line 2836 "yacc_sql.tab.c"
    break;

  case 153: /* aggOp: AGG_MIN  */
#line 1165 "yacc_sql.y"
                  { CONTEXT->aggop = MIN; }
#line 2842 "yacc_sql.tab.c"
    break;

  case 154: /* aggOp: AGG_AVG  */
#line 1166 "yacc_sql.y"
                  { CONTEXT->aggop = AVG; }
#line 2848 "yacc_sql.tab.c"
    break;

  case 155: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1171 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2857 "yacc_sql.tab.c"
    break;


#line 2861 "yacc_sql.tab.c"

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

#line 1176 "yacc_sql.y"

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
