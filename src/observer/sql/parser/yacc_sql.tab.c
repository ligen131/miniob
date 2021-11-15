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
  Value values[MAX_NUM];
  int data_list_r[MAX_NUM];
  Condition conditions[MAX_NUM];
  char *index_list[MAX_NUM];
  CompOp comp;
  AggregationOp aggop;
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
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 146 "yacc_sql.tab.c"

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
  YYSYMBOL_LOAD = 38,                      /* LOAD  */
  YYSYMBOL_DATA = 39,                      /* DATA  */
  YYSYMBOL_INFILE = 40,                    /* INFILE  */
  YYSYMBOL_EQ = 41,                        /* EQ  */
  YYSYMBOL_LT = 42,                        /* LT  */
  YYSYMBOL_GT = 43,                        /* GT  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_NE = 46,                        /* NE  */
  YYSYMBOL_AGG_COUNT = 47,                 /* AGG_COUNT  */
  YYSYMBOL_AGG_MAX = 48,                   /* AGG_MAX  */
  YYSYMBOL_AGG_MIN = 49,                   /* AGG_MIN  */
  YYSYMBOL_AGG_AVG = 50,                   /* AGG_AVG  */
  YYSYMBOL_ORDER = 51,                     /* ORDER  */
  YYSYMBOL_GROUP = 52,                     /* GROUP  */
  YYSYMBOL_BY = 53,                        /* BY  */
  YYSYMBOL_INNER = 54,                     /* INNER  */
  YYSYMBOL_JOIN = 55,                      /* JOIN  */
  YYSYMBOL_NUMBER = 56,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_DATEE = 58,                     /* DATEE  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_PATH = 60,                      /* PATH  */
  YYSYMBOL_SSS = 61,                       /* SSS  */
  YYSYMBOL_STAR = 62,                      /* STAR  */
  YYSYMBOL_STRING_V = 63,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_commands = 65,                  /* commands  */
  YYSYMBOL_command = 66,                   /* command  */
  YYSYMBOL_exit = 67,                      /* exit  */
  YYSYMBOL_help = 68,                      /* help  */
  YYSYMBOL_sync = 69,                      /* sync  */
  YYSYMBOL_begin = 70,                     /* begin  */
  YYSYMBOL_commit = 71,                    /* commit  */
  YYSYMBOL_rollback = 72,                  /* rollback  */
  YYSYMBOL_drop_table = 73,                /* drop_table  */
  YYSYMBOL_show_tables = 74,               /* show_tables  */
  YYSYMBOL_desc_table = 75,                /* desc_table  */
  YYSYMBOL_create_index = 76,              /* create_index  */
  YYSYMBOL_create_index_attr_list = 77,    /* create_index_attr_list  */
  YYSYMBOL_drop_index = 78,                /* drop_index  */
  YYSYMBOL_create_table = 79,              /* create_table  */
  YYSYMBOL_attr_def_list = 80,             /* attr_def_list  */
  YYSYMBOL_attr_def = 81,                  /* attr_def  */
  YYSYMBOL_number = 82,                    /* number  */
  YYSYMBOL_type = 83,                      /* type  */
  YYSYMBOL_ID_get = 84,                    /* ID_get  */
  YYSYMBOL_insert = 85,                    /* insert  */
  YYSYMBOL_data = 86,                      /* data  */
  YYSYMBOL_data_list = 87,                 /* data_list  */
  YYSYMBOL_value_list = 88,                /* value_list  */
  YYSYMBOL_value = 89,                     /* value  */
  YYSYMBOL_delete = 90,                    /* delete  */
  YYSYMBOL_update = 91,                    /* update  */
  YYSYMBOL_select = 92,                    /* select  */
  YYSYMBOL_order_by = 93,                  /* order_by  */
  YYSYMBOL_select_order_list = 94,         /* select_order_list  */
  YYSYMBOL_select_order = 95,              /* select_order  */
  YYSYMBOL_group_by = 96,                  /* group_by  */
  YYSYMBOL_select_group_list = 97,         /* select_group_list  */
  YYSYMBOL_select_group = 98,              /* select_group  */
  YYSYMBOL_select_attr = 99,               /* select_attr  */
  YYSYMBOL_select_attribute = 100,         /* select_attribute  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_aggr_select_attr = 102,         /* aggr_select_attr  */
  YYSYMBOL_aggr_attr_list = 103,           /* aggr_attr_list  */
  YYSYMBOL_rel_list = 104,                 /* rel_list  */
  YYSYMBOL_where = 105,                    /* where  */
  YYSYMBOL_inner_join_on = 106,            /* inner_join_on  */
  YYSYMBOL_condition_list = 107,           /* condition_list  */
  YYSYMBOL_condition = 108,                /* condition  */
  YYSYMBOL_comOp = 109,                    /* comOp  */
  YYSYMBOL_aggOp = 110,                    /* aggOp  */
  YYSYMBOL_load_data = 111                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   238

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   164,   164,   166,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   190,   195,   200,   206,   212,   218,   224,   230,   236,
     243,   251,   253,   259,   266,   275,   277,   281,   292,   305,
     308,   309,   310,   311,   312,   315,   324,   341,   345,   347,
     352,   354,   359,   362,   365,   369,   376,   386,   396,   430,
     432,   436,   438,   443,   448,   453,   458,   463,   468,   474,
     476,   480,   482,   487,   492,   499,   504,   509,   514,   519,
     524,   529,   534,   539,   544,   550,   552,   601,   604,   607,
     611,   613,   616,   619,   657,   659,   663,   667,   669,   673,
     675,   679,   681,   686,   707,   727,   747,   769,   790,   811,
     833,   834,   835,   836,   837,   838,   842,   843,   844,   845,
     849
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
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT",
  "LE", "GE", "NE", "AGG_COUNT", "AGG_MAX", "AGG_MIN", "AGG_AVG", "ORDER",
  "GROUP", "BY", "INNER", "JOIN", "NUMBER", "FLOAT", "DATEE", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "create_index_attr_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "data", "data_list", "value_list", "value",
  "delete", "update", "select", "order_by", "select_order_list",
  "select_order", "group_by", "select_group_list", "select_group",
  "select_attr", "select_attribute", "attr_list", "aggr_select_attr",
  "aggr_attr_list", "rel_list", "where", "inner_join_on", "condition_list",
  "condition", "comOp", "aggOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-182)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -182,     7,  -182,    46,   111,    21,   -50,    11,    37,    15,
      33,     8,    75,    76,    84,    95,   101,    53,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,    51,    59,    61,    62,
    -182,  -182,  -182,  -182,    92,  -182,    90,   105,   108,   123,
     124,  -182,    69,    70,    94,  -182,  -182,  -182,  -182,  -182,
      91,   115,    96,   131,   132,    77,    78,    21,  -182,   -15,
    -182,  -182,   106,   107,    80,    79,    83,    85,  -182,  -182,
    -182,   -11,   105,  -182,   125,    -5,   127,   128,   129,    32,
     145,   109,   118,  -182,   133,    89,   134,    97,    98,   107,
    -182,  -182,  -182,    99,  -182,    22,   -24,   135,  -182,  -182,
    -182,    19,  -182,    31,   120,  -182,   -24,   151,    83,   141,
    -182,  -182,  -182,  -182,  -182,   143,   102,   -11,   103,   112,
     146,   136,  -182,   148,   149,   129,   162,   110,  -182,  -182,
    -182,  -182,  -182,  -182,    38,    44,    32,  -182,   107,   113,
     133,   167,   117,   152,  -182,   137,   122,   126,  -182,   121,
      23,   158,   -24,   159,   135,  -182,    31,  -182,  -182,   153,
    -182,   120,   176,   178,  -182,  -182,  -182,   164,   130,   166,
      32,   -11,   138,   139,   182,  -182,    -4,   148,  -182,   149,
    -182,  -182,    50,   140,  -182,  -182,  -182,  -182,   152,   183,
     120,  -182,    20,   168,   142,  -182,   144,  -182,  -182,  -182,
     160,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   147,   138,
    -182,   161,   169,   148,   150,    48,   168,   154,   142,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,   169,  -182
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
     116,   117,   118,   119,    83,    82,     0,    85,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
      29,    28,     0,    97,     0,     0,     0,     0,    27,    33,
      84,    94,    85,    81,     0,    88,    87,     0,     0,     0,
       0,     0,     0,    45,    35,     0,     0,     0,     0,    97,
      86,    77,    78,     0,    76,     0,     0,    48,    52,    53,
      54,     0,    55,     0,   101,    56,     0,     0,     0,     0,
      40,    41,    42,    43,    44,    38,     0,    94,     0,    59,
      89,    88,    87,    90,    50,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,    98,    97,     0,
      35,     0,     0,    31,    95,    99,     0,    69,    79,     0,
       0,     0,     0,     0,    48,    46,     0,   105,   103,   106,
     104,   101,     0,     0,    36,    34,    39,     0,     0,     0,
       0,    94,     0,     0,     0,    89,    90,    90,    80,    50,
      47,    49,     0,     0,   102,    57,   120,    37,    31,     0,
     101,    96,    63,    61,     0,    58,     0,    92,    91,    51,
       0,   107,   108,    32,    30,   100,    65,    64,     0,     0,
      60,    73,    71,    90,     0,    66,    61,     0,     0,    70,
      93,   109,    68,    67,    62,    74,    71,    72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,    -3,  -182,  -182,    43,    82,  -182,  -182,
    -182,  -182,    63,    30,    13,  -106,  -182,  -182,  -182,  -182,
     -30,   -14,  -182,   -32,   -21,  -182,   155,   156,   114,  -181,
    -126,   -97,  -182,  -147,  -132,  -109,  -182,  -182
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   179,    29,    30,   119,    94,   177,   125,
      95,    31,   107,   136,   163,   113,    32,    33,    34,   157,
     220,   203,   184,   229,   222,    46,    47,    68,    87,   161,
      99,    90,   181,   147,   114,   144,    48,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     134,   154,   129,    83,   145,   207,   208,     2,    97,    49,
     148,     3,     4,   102,   171,   160,     5,     6,    50,     7,
       8,     9,    10,    11,   194,   103,   206,    12,    13,    14,
     216,   217,   108,   109,   110,    15,    16,   112,   168,   170,
      51,    84,   230,    98,    85,    17,    52,    86,   200,   137,
     218,   172,    36,   215,    37,   201,   189,   192,   232,   233,
     138,   139,   140,   141,   142,   143,    53,    54,    40,    41,
      42,    43,   138,   139,   140,   141,   142,   143,    55,    56,
      44,   131,   186,    45,   132,   187,   211,    57,   108,   109,
     110,   111,    60,   112,   108,   109,   110,   167,    58,   112,
     108,   109,   110,   169,    59,   112,   108,   109,   110,   210,
      61,   112,   120,   121,   122,   123,   124,    38,    62,    39,
      63,    64,    65,    66,    67,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    88,    91,
      92,    89,    93,   101,    96,   104,   106,   105,   115,   117,
     116,   126,   118,   128,   135,   146,   127,   149,   130,   151,
     152,   153,   155,   156,   158,   165,   159,   160,   162,   166,
     175,   178,   173,   176,   180,   182,   188,   190,   183,   195,
     185,   196,   197,   193,   199,   205,   214,   219,   228,   198,
     224,   227,   204,   174,   191,   213,   234,   202,   164,   212,
     150,   221,   209,   223,   237,   226,   225,   236,     0,   231,
       0,     0,     0,   235,     0,     0,     0,     0,     0,   133,
       0,     0,    82,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   100
};

static const yytype_int16 yycheck[] =
{
     106,   127,    99,    18,   113,   186,   187,     0,    19,    59,
     116,     4,     5,    18,   146,    19,     9,    10,     7,    12,
      13,    14,    15,    16,   171,    30,    30,    20,    21,    22,
      10,    11,    56,    57,    58,    28,    29,    61,   144,   145,
       3,    56,   223,    54,    59,    38,    31,    62,   180,    30,
      30,   148,     6,   200,     8,   181,   162,   166,    10,    11,
      41,    42,    43,    44,    45,    46,    33,    59,    47,    48,
      49,    50,    41,    42,    43,    44,    45,    46,     3,     3,
      59,    59,    59,    62,    62,    62,   192,     3,    56,    57,
      58,    59,    39,    61,    56,    57,    58,    59,     3,    61,
      56,    57,    58,    59,     3,    61,    56,    57,    58,    59,
      59,    61,    23,    24,    25,    26,    27,     6,    59,     8,
      59,    59,    30,    33,    19,    17,     3,     3,    59,    59,
      36,    40,    17,    37,     3,     3,    59,    59,    32,    59,
      61,    34,    59,    18,    59,    18,    17,    19,     3,    31,
      41,    17,    19,    55,    19,    35,    59,     6,    59,    18,
      17,    59,    59,    51,    18,     3,    30,    19,    19,    59,
       3,    19,    59,    56,    37,    53,    18,    18,    52,     3,
      59,     3,    18,    30,    18,     3,     3,    19,    19,    59,
      30,    30,    53,   150,   164,   198,   226,    59,   135,    59,
     118,    59,   189,    59,   236,   219,    59,   228,    -1,    59,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,     0,     4,     5,     9,    10,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    38,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    78,
      79,    85,    90,    91,    92,   111,     6,     8,     6,     8,
      47,    48,    49,    50,    59,    62,    99,   100,   110,    59,
       7,     3,    31,    33,    59,     3,     3,     3,     3,     3,
      39,    59,    59,    59,    59,    30,    33,    19,   101,    17,
       3,     3,    59,    59,    36,    40,    17,    37,     3,     3,
      59,    59,   100,    18,    56,    59,    62,   102,    32,    34,
     105,    59,    61,    59,    81,    84,    59,    19,    54,   104,
     101,    18,    18,    30,    18,    19,    17,    86,    56,    57,
      58,    59,    61,    89,   108,     3,    41,    31,    19,    80,
      23,    24,    25,    26,    27,    83,    17,    59,    55,   105,
      59,    59,    62,   102,    89,    19,    87,    30,    41,    42,
      43,    44,    45,    46,   109,   109,    35,   107,    89,     6,
      81,    18,    17,    59,   104,    59,    51,    93,    18,    30,
      19,   103,    19,    88,    86,     3,    59,    59,    89,    59,
      89,   108,   105,    59,    80,     3,    56,    82,    19,    77,
      37,   106,    53,    52,    96,    59,    59,    62,    18,    89,
      18,    87,   109,    30,   107,     3,     3,    18,    59,    18,
     108,   104,    59,    95,    53,     3,    30,   103,   103,    88,
      59,    89,    59,    77,     3,   107,    10,    11,    30,    19,
      94,    59,    98,    59,    30,    59,    95,    30,    19,    97,
     103,    59,    10,    11,    94,    59,    98,    97
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    77,    78,    79,    80,    80,    81,    81,    82,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    87,
      88,    88,    89,    89,    89,    89,    90,    91,    92,    93,
      93,    94,    94,    95,    95,    95,    95,    95,    95,    96,
      96,    97,    97,    98,    98,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   104,   104,   104,   105,   105,   106,
     106,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     109,   109,   109,   109,   109,   109,   110,   110,   110,   110,
     111
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,     0,     3,     4,     8,     0,     3,     5,     2,     1,
       1,     1,     1,     1,     1,     1,     7,     4,     0,     3,
       0,     3,     1,     1,     1,     1,     5,     8,     9,     0,
       4,     0,     3,     1,     2,     2,     3,     4,     4,     0,
       4,     0,     3,     1,     3,     2,     4,     4,     4,     6,
       7,     3,     1,     1,     3,     0,     3,     1,     1,     3,
       0,     3,     3,     5,     0,     3,     5,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       8
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
#line 190 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1421 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 195 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1429 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 200 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1437 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 206 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1445 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 212 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1453 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 218 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1461 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 224 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 230 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 236 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1487 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 244 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length);
			CONTEXT->index_length = 0;
		}
#line 1498 "yacc_sql.tab.c"
    break;

  case 32: /* create_index_attr_list: COMMA ID create_index_attr_list  */
#line 253 "yacc_sql.y"
                                          {
		CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-1].string));
	}
#line 1506 "yacc_sql.tab.c"
    break;

  case 33: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 260 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1515 "yacc_sql.tab.c"
    break;

  case 34: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 267 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1527 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 277 "yacc_sql.y"
                                   {    }
#line 1533 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 282 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1548 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type  */
#line 293 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1563 "yacc_sql.tab.c"
    break;

  case 39: /* number: NUMBER  */
#line 305 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1569 "yacc_sql.tab.c"
    break;

  case 40: /* type: INT_T  */
#line 308 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1575 "yacc_sql.tab.c"
    break;

  case 41: /* type: DATE_T  */
#line 309 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1581 "yacc_sql.tab.c"
    break;

  case 42: /* type: TEXT_T  */
#line 310 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1587 "yacc_sql.tab.c"
    break;

  case 43: /* type: STRING_T  */
#line 311 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1593 "yacc_sql.tab.c"
    break;

  case 44: /* type: FLOAT_T  */
#line 312 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1599 "yacc_sql.tab.c"
    break;

  case 45: /* ID_get: ID  */
#line 316 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1608 "yacc_sql.tab.c"
    break;

  case 46: /* insert: INSERT INTO ID VALUES data data_list SEMICOLON  */
#line 325 "yacc_sql.y"
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
#line 1628 "yacc_sql.tab.c"
    break;

  case 47: /* data: LBRACE value value_list RBRACE  */
#line 341 "yacc_sql.y"
                                       {
		CONTEXT->data_list_r[CONTEXT->data_num++]=CONTEXT->value_length;
	}
#line 1636 "yacc_sql.tab.c"
    break;

  case 49: /* data_list: COMMA data data_list  */
#line 347 "yacc_sql.y"
                            { 
  		
	  }
#line 1644 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: COMMA value value_list  */
#line 354 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1652 "yacc_sql.tab.c"
    break;

  case 52: /* value: NUMBER  */
#line 359 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1660 "yacc_sql.tab.c"
    break;

  case 53: /* value: FLOAT  */
#line 362 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1668 "yacc_sql.tab.c"
    break;

  case 54: /* value: DATEE  */
#line 365 "yacc_sql.y"
           {
			(yyvsp[0].dates) = substr((yyvsp[0].dates),1,strlen((yyvsp[0].dates))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].dates));
		}
#line 1677 "yacc_sql.tab.c"
    break;

  case 55: /* value: SSS  */
#line 369 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1686 "yacc_sql.tab.c"
    break;

  case 56: /* delete: DELETE FROM ID where SEMICOLON  */
#line 377 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1698 "yacc_sql.tab.c"
    break;

  case 57: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 387 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1710 "yacc_sql.tab.c"
    break;

  case 58: /* select: SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON  */
#line 397 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length = 0;
			CONTEXT->from_length = 0;
			CONTEXT->select_length = 0;
			CONTEXT->value_length = 0;
	}
#line 1730 "yacc_sql.tab.c"
    break;

  case 60: /* order_by: ORDER BY select_order select_order_list  */
#line 432 "yacc_sql.y"
                                              {
      
    }
#line 1738 "yacc_sql.tab.c"
    break;

  case 62: /* select_order_list: COMMA select_order select_order_list  */
#line 438 "yacc_sql.y"
                                               {

	}
#line 1746 "yacc_sql.tab.c"
    break;

  case 63: /* select_order: ID  */
#line 443 "yacc_sql.y"
           {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1756 "yacc_sql.tab.c"
    break;

  case 64: /* select_order: ID ASC  */
#line 448 "yacc_sql.y"
                 {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1766 "yacc_sql.tab.c"
    break;

  case 65: /* select_order: ID DESC  */
#line 453 "yacc_sql.y"
                  {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1776 "yacc_sql.tab.c"
    break;

  case 66: /* select_order: ID DOT ID  */
#line 458 "yacc_sql.y"
                    {
			OrderBy order;
			orders_init(&order, (yyvsp[-2].string), (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1786 "yacc_sql.tab.c"
    break;

  case 67: /* select_order: ID DOT ID ASC  */
#line 463 "yacc_sql.y"
                        {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1796 "yacc_sql.tab.c"
    break;

  case 68: /* select_order: ID DOT ID DESC  */
#line 468 "yacc_sql.y"
                         {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, &order);
	}
#line 1806 "yacc_sql.tab.c"
    break;

  case 70: /* group_by: GROUP BY select_group select_group_list  */
#line 476 "yacc_sql.y"
                                                  {

	}
#line 1814 "yacc_sql.tab.c"
    break;

  case 72: /* select_group_list: COMMA select_group select_group_list  */
#line 482 "yacc_sql.y"
                                               {

	}
#line 1822 "yacc_sql.tab.c"
    break;

  case 73: /* select_group: ID  */
#line 487 "yacc_sql.y"
           {
			GroupBy group;
			groups_init(&group, NULL, (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection, &group);
	}
#line 1832 "yacc_sql.tab.c"
    break;

  case 74: /* select_group: ID DOT ID  */
#line 492 "yacc_sql.y"
                    {
			GroupBy group;
			groups_init(&group, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection, &group);
	}
#line 1842 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: select_attribute attr_list  */
#line 499 "yacc_sql.y"
                                   {

		}
#line 1850 "yacc_sql.tab.c"
    break;

  case 76: /* select_attribute: aggOp LBRACE STAR RBRACE  */
#line 504 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1860 "yacc_sql.tab.c"
    break;

  case 77: /* select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 509 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1870 "yacc_sql.tab.c"
    break;

  case 78: /* select_attribute: aggOp LBRACE ID RBRACE  */
#line 514 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1880 "yacc_sql.tab.c"
    break;

  case 79: /* select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 519 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1890 "yacc_sql.tab.c"
    break;

  case 80: /* select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 524 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1900 "yacc_sql.tab.c"
    break;

  case 81: /* select_attribute: aggOp LBRACE RBRACE  */
#line 529 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1910 "yacc_sql.tab.c"
    break;

  case 82: /* select_attribute: STAR  */
#line 534 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 83: /* select_attribute: ID  */
#line 539 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1930 "yacc_sql.tab.c"
    break;

  case 84: /* select_attribute: ID DOT ID  */
#line 544 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1940 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA select_attribute attr_list  */
#line 552 "yacc_sql.y"
                                           {

		}
#line 1948 "yacc_sql.tab.c"
    break;

  case 87: /* aggr_select_attr: STAR  */
#line 601 "yacc_sql.y"
        {  
      
		}
#line 1956 "yacc_sql.tab.c"
    break;

  case 88: /* aggr_select_attr: ID  */
#line 604 "yacc_sql.y"
         {

		}
#line 1964 "yacc_sql.tab.c"
    break;

  case 89: /* aggr_select_attr: ID DOT ID  */
#line 607 "yacc_sql.y"
                    {

		}
#line 1972 "yacc_sql.tab.c"
    break;

  case 91: /* aggr_attr_list: COMMA STAR aggr_attr_list  */
#line 613 "yacc_sql.y"
                                {
      
      }
#line 1980 "yacc_sql.tab.c"
    break;

  case 92: /* aggr_attr_list: COMMA ID aggr_attr_list  */
#line 616 "yacc_sql.y"
                              {
      
      }
#line 1988 "yacc_sql.tab.c"
    break;

  case 93: /* aggr_attr_list: COMMA ID DOT ID aggr_attr_list  */
#line 619 "yacc_sql.y"
                                     {
      
  	  }
#line 1996 "yacc_sql.tab.c"
    break;

  case 95: /* rel_list: COMMA ID rel_list  */
#line 659 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2004 "yacc_sql.tab.c"
    break;

  case 96: /* rel_list: INNER JOIN ID inner_join_on rel_list  */
#line 663 "yacc_sql.y"
                                           {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
		  }
#line 2012 "yacc_sql.tab.c"
    break;

  case 98: /* where: WHERE condition condition_list  */
#line 669 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2020 "yacc_sql.tab.c"
    break;

  case 100: /* inner_join_on: ON condition condition_list  */
#line 675 "yacc_sql.y"
                                  {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2028 "yacc_sql.tab.c"
    break;

  case 102: /* condition_list: AND condition condition_list  */
#line 681 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2036 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID comOp value  */
#line 687 "yacc_sql.y"
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
#line 2061 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value comOp value  */
#line 708 "yacc_sql.y"
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
#line 2085 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID comOp ID  */
#line 728 "yacc_sql.y"
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
#line 2109 "yacc_sql.tab.c"
    break;

  case 106: /* condition: value comOp ID  */
#line 748 "yacc_sql.y"
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
#line 2135 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID DOT ID comOp value  */
#line 770 "yacc_sql.y"
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
#line 2160 "yacc_sql.tab.c"
    break;

  case 108: /* condition: value comOp ID DOT ID  */
#line 791 "yacc_sql.y"
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
#line 2185 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp ID DOT ID  */
#line 812 "yacc_sql.y"
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
#line 2208 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: EQ  */
#line 833 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2214 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: LT  */
#line 834 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2220 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: GT  */
#line 835 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2226 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: LE  */
#line 836 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2232 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: GE  */
#line 837 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: NE  */
#line 838 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 116: /* aggOp: AGG_COUNT  */
#line 842 "yacc_sql.y"
                    { CONTEXT->aggop = COUNT; }
#line 2250 "yacc_sql.tab.c"
    break;

  case 117: /* aggOp: AGG_MAX  */
#line 843 "yacc_sql.y"
                  { CONTEXT->aggop = MAX; }
#line 2256 "yacc_sql.tab.c"
    break;

  case 118: /* aggOp: AGG_MIN  */
#line 844 "yacc_sql.y"
                  { CONTEXT->aggop = MIN; }
#line 2262 "yacc_sql.tab.c"
    break;

  case 119: /* aggOp: AGG_AVG  */
#line 845 "yacc_sql.y"
                  { CONTEXT->aggop = AVG; }
#line 2268 "yacc_sql.tab.c"
    break;

  case 120: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 850 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2277 "yacc_sql.tab.c"
    break;


#line 2281 "yacc_sql.tab.c"

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

#line 855 "yacc_sql.y"

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
