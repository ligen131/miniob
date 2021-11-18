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

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 155 "yacc_sql.tab.c"

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
#define YYLAST   328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  313

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
       0,   179,   179,   181,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   205,   210,   215,   221,   227,   233,   239,   245,   251,
     258,   265,   273,   275,   281,   288,   297,   299,   303,   314,
     325,   336,   347,   358,   371,   374,   375,   376,   377,   378,
     381,   390,   407,   411,   413,   418,   420,   425,   428,   431,
     435,   439,   445,   455,   465,   483,   497,   499,   503,   505,
     510,   515,   520,   525,   530,   535,   541,   543,   547,   549,
     554,   559,   566,   571,   576,   581,   586,   591,   596,   601,
     606,   613,   618,   623,   628,   633,   638,   643,   648,   653,
     658,   664,   666,   671,   674,   677,   681,   683,   686,   689,
     695,   697,   701,   705,   707,   711,   713,   717,   719,   724,
     745,   765,   785,   807,   828,   849,   868,   885,   904,   906,
     910,   912,   917,   938,   958,   978,  1000,  1021,  1042,  1099,
    1100,  1101,  1102,  1103,  1104,  1105,  1106,  1107,  1108,  1112,
    1113,  1114,  1115,  1119
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

#define YYPACT_NINF (-202)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -202,    92,  -202,     1,    34,   -19,   -50,    26,    45,    32,
      33,    13,    96,   100,   112,   113,   114,    43,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,    54,    64,   122,    74,
      81,  -202,  -202,  -202,  -202,   117,  -202,   118,   131,   136,
     158,   160,  -202,    99,   101,   129,  -202,  -202,  -202,  -202,
    -202,   134,   161,   140,   115,   176,   183,   127,   138,   -19,
    -202,   -10,  -202,  -202,   155,   162,   145,   150,   157,   159,
     188,  -202,  -202,  -202,    -1,   131,  -202,   208,    -4,   209,
     210,   211,    95,   227,   189,   201,  -202,   214,   147,   217,
     170,   171,   181,   162,  -202,  -202,  -202,   173,  -202,     0,
      31,   220,  -202,  -202,  -202,  -202,    80,  -202,   -22,   205,
    -202,    31,   235,   157,   224,  -202,  -202,  -202,  -202,  -202,
      -7,   178,   228,    -1,   179,   194,   229,   218,  -202,   230,
     231,   211,   248,   187,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,   195,   216,    10,   126,    95,  -202,   162,   190,   214,
     253,   196,   198,  -202,   240,   197,  -202,   223,   207,   212,
    -202,   199,     2,   245,    31,   249,   220,  -202,   -22,  -202,
    -202,   257,  -202,  -202,  -202,   238,  -202,   205,   266,   267,
    -202,  -202,  -202,   254,  -202,   206,   255,   240,    95,    -1,
     213,   221,   271,  -202,    -2,   230,  -202,   231,  -202,  -202,
      17,    84,   215,  -202,  -202,  -202,    51,   240,   273,   259,
     205,  -202,    27,   260,   219,  -202,   222,  -202,  -202,  -202,
     251,  -202,  -202,   252,  -202,   250,   268,  -202,   232,  -202,
    -202,  -202,   283,  -202,  -202,  -202,   225,   213,  -202,   258,
     270,   230,   233,   234,   236,    23,  -202,  -202,    76,   260,
     237,   219,  -202,  -202,  -202,  -202,   261,  -202,   274,    29,
     275,   277,  -202,  -202,  -202,  -202,   270,   135,   276,  -202,
    -202,   239,  -202,     0,  -202,    98,   -22,   262,  -202,   282,
     230,   241,   142,   149,   135,  -202,  -202,   285,   -22,  -202,
    -202,   278,  -202,   262,  -202,   156,   242,  -202,   279,  -202,
    -202,   246,  -202
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
       0,   149,   150,   151,   152,    99,    98,     0,   101,     0,
       0,     0,    23,     0,     0,     0,    24,    25,    26,    22,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    29,    28,     0,   113,     0,     0,     0,     0,
       0,    27,    34,   100,   110,   101,    97,     0,   104,   103,
       0,     0,     0,     0,     0,     0,    50,    36,     0,     0,
       0,     0,     0,   113,   102,    93,    94,     0,    92,     0,
       0,    53,    61,    57,    58,    59,     0,    60,     0,   117,
      62,     0,     0,     0,     0,    45,    46,    47,    48,    49,
      41,     0,     0,   110,     0,    66,   105,   104,   103,   106,
      55,     0,     0,     0,   147,   139,   140,   141,   142,   143,
     144,   146,     0,     0,     0,     0,   114,   113,     0,    36,
       0,     0,     0,    43,    32,     0,   111,   115,     0,    76,
      95,     0,     0,     0,     0,     0,    53,    51,     0,   145,
     148,     0,   121,   119,   127,   122,   120,   117,     0,     0,
      37,    35,    44,     0,    42,     0,     0,    32,     0,   110,
       0,     0,     0,   105,   106,   106,    96,    55,    52,    54,
       0,     0,     0,   118,    63,   153,    38,    32,     0,     0,
     117,   112,    70,    68,     0,    64,     0,   108,   107,    56,
       0,   123,   126,    89,    88,     0,     0,   124,     0,    40,
      33,    30,     0,   116,    72,    71,     0,     0,    67,    80,
      78,   106,     0,     0,     0,     0,    39,    31,    73,    68,
       0,     0,    77,   109,   125,    90,   128,    87,     0,   104,
     103,     0,    75,    74,    69,    81,    78,     0,     0,    83,
      84,     0,    82,     0,    79,     0,     0,   130,    65,   105,
     106,     0,     0,     0,     0,   129,    85,     0,     0,   134,
     132,   135,   133,   130,    86,     0,     0,   131,     0,   136,
     137,     0,   138
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -178,  -202,  -202,   146,   191,  -202,  -202,
    -202,  -202,   169,   137,   105,  -110,  -202,  -202,  -202,   106,
    -202,    56,    70,  -202,    42,    58,  -202,  -202,   256,   243,
    -107,  -201,  -128,   -97,  -202,  -175,  -142,  -202,    18,    28,
    -117,   109,  -202
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   196,    29,    30,   124,    97,   193,   130,
      98,    31,   111,   142,   175,   118,    32,    33,    34,   184,
     169,   248,   223,   202,   262,   250,   235,    47,    48,    70,
      90,   173,   103,    93,   199,   156,   119,   278,   295,   287,
     153,    49,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     140,   154,   139,   227,   228,   166,   135,    36,    86,    37,
     161,   157,   213,   187,   106,    50,   144,   172,   101,   219,
     145,   146,   147,   148,   149,   150,   107,   181,   226,    41,
      42,    43,    44,    51,   181,   151,   152,   244,   245,   240,
      39,   267,    40,   183,   186,   243,    45,   280,    52,    46,
     263,   162,    87,   163,   102,    88,   220,   246,    89,   281,
     188,   210,    38,    53,   207,   137,    54,   204,   138,   112,
     205,   221,   113,   114,   115,   182,   112,   117,    55,   113,
     114,   115,   230,    61,   117,   268,   272,   273,   269,   297,
     112,   270,     2,   113,   114,   115,     3,     4,   117,    56,
     231,     5,     6,    57,     7,     8,     9,    10,    11,   238,
     143,   239,    12,    13,    14,    58,    59,    60,   144,    62,
      15,    16,   145,   146,   147,   148,   149,   150,   291,    63,
      64,    17,    41,    42,    43,    44,   144,   151,   152,    65,
     145,   146,   147,   148,   149,   150,    66,    67,   271,   233,
      69,    68,   234,    71,   112,   151,   152,   113,   114,   115,
     116,    72,   117,    73,    74,    76,    75,   286,   292,   293,
     125,   126,   127,   128,   129,    77,   290,    79,    78,    81,
      80,   305,   300,   302,   286,   112,    82,    91,   113,   114,
     115,   185,    83,   117,   112,   309,    92,   113,   114,   115,
     285,   112,   117,    84,   113,   114,   115,   299,   112,   117,
      94,   113,   114,   115,   301,   112,   117,    95,   113,   114,
     115,   308,    96,   117,    99,   100,   105,   108,   110,   109,
     120,   121,   122,   123,   131,   132,   133,   134,   136,   141,
     155,   158,   160,   164,   167,   165,   168,   170,   171,   172,
     174,   177,   178,   179,   180,   189,   191,   194,   192,   195,
     198,   200,   197,   206,   203,   201,   211,   208,   212,   214,
     215,   217,   216,   218,   225,   224,   241,   242,   222,   247,
     237,   252,   253,   254,   249,   255,   257,   251,   260,   261,
     258,   256,   279,   282,   288,   277,   283,   294,   264,   265,
     296,   266,   275,   304,   289,   190,   298,   310,   306,   311,
     176,   312,   229,   209,   159,   274,   232,   259,   284,   276,
     236,   307,   303,     0,     0,    85,     0,     0,   104
};

static const yytype_int16 yycheck[] =
{
     110,   118,   109,   204,   205,   133,   103,     6,    18,     8,
      17,   121,   187,   155,    18,    65,    38,    19,    19,   197,
      42,    43,    44,    45,    46,    47,    30,    17,    30,    48,
      49,    50,    51,     7,    17,    57,    58,    10,    11,   217,
       6,    18,     8,   153,   154,   220,    65,    18,     3,    68,
     251,    58,    62,    60,    55,    65,   198,    30,    68,    30,
     157,   178,    61,    31,   174,    65,    33,    65,    68,    59,
      68,   199,    62,    63,    64,    65,    59,    67,    65,    62,
      63,    64,    65,    40,    67,    62,    10,    11,    65,   290,
      59,    68,     0,    62,    63,    64,     4,     5,    67,     3,
     210,     9,    10,     3,    12,    13,    14,    15,    16,    58,
      30,    60,    20,    21,    22,     3,     3,     3,    38,    65,
      28,    29,    42,    43,    44,    45,    46,    47,    30,    65,
       8,    39,    48,    49,    50,    51,    38,    57,    58,    65,
      42,    43,    44,    45,    46,    47,    65,    30,   255,    65,
      19,    33,    68,    17,    59,    57,    58,    62,    63,    64,
      65,     3,    67,     3,    65,    36,    65,   277,   285,   286,
      23,    24,    25,    26,    27,    41,   283,    37,    17,     3,
      65,   298,   292,   293,   294,    59,     3,    32,    62,    63,
      64,    65,    65,    67,    59,   305,    34,    62,    63,    64,
      65,    59,    67,    65,    62,    63,    64,    65,    59,    67,
      65,    62,    63,    64,    65,    59,    67,    67,    62,    63,
      64,    65,    65,    67,    65,    37,    18,    18,    17,    19,
       3,    42,    31,    19,    17,    65,    65,    56,    65,    19,
      35,     6,    18,    65,    65,    17,    52,    18,    30,    19,
      19,     3,    65,    58,    38,    65,     3,    59,    62,    19,
      37,    54,    65,    18,    65,    53,     9,    18,    30,     3,
       3,    65,    18,    18,     3,    54,     3,    18,    65,    19,
      65,    30,    30,    33,    65,    17,     3,    65,    30,    19,
      65,    59,    18,    18,    18,    34,    19,    35,    65,    65,
      18,    65,    65,    18,    65,   159,    65,    65,    30,    30,
     141,    65,   207,   176,   123,   259,   210,   247,   276,   261,
     211,   303,   294,    -1,    -1,    69,    -1,    -1,    85
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
      17,    92,    59,    62,    63,    64,    65,    67,    95,   116,
       3,    42,    31,    19,    86,    23,    24,    25,    26,    27,
      89,    17,    65,    65,    56,   113,    65,    65,    68,   110,
      95,    19,    93,    30,    38,    42,    43,    44,    45,    46,
      47,    57,    58,   120,   120,    35,   115,    95,     6,    87,
      18,    17,    58,    60,    65,    17,   112,    65,    52,   100,
      18,    30,    19,   111,    19,    94,    92,     3,    65,    58,
      38,    17,    65,    95,    99,    65,    95,   116,   113,    65,
      86,     3,    62,    88,    59,    19,    83,    65,    37,   114,
      54,    53,   103,    65,    65,    68,    18,    95,    18,    93,
     120,     9,    30,   115,     3,     3,    18,    65,    18,    83,
     116,   112,    65,   102,    54,     3,    30,   111,   111,    94,
      65,    95,    99,    65,    68,   106,   121,    65,    58,    60,
      83,     3,    18,   115,    10,    11,    30,    19,   101,    65,
     105,    65,    30,    30,    33,    17,    59,     3,    65,   102,
      30,    19,   104,   111,    65,    65,    65,    18,    62,    65,
      68,   110,    10,    11,   101,    65,   105,    34,   117,    18,
      18,    30,    18,    19,   104,    65,    95,   119,    18,    65,
     110,    30,   120,   120,    35,   118,    18,   111,    65,    65,
      95,    65,    95,   119,    18,   120,    30,   118,    65,    95,
      65,    30,    65
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
     116,   116,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   119,   119,   119,   119,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   122
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
       3,     3,     3,     5,     5,     7,     5,     3,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     8
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
#line 205 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1497 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 210 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1505 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 215 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1513 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 221 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1521 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 227 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1529 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 233 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1537 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 239 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1546 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 245 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 251 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1563 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 259 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 0);
			CONTEXT->index_length = 0;
		}
#line 1574 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-3].string));
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->index_list, CONTEXT->index_length, 1);
			CONTEXT->index_length = 0;
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 33: /* create_index_attr_list: COMMA ID create_index_attr_list  */
#line 275 "yacc_sql.y"
                                          {
		CONTEXT->index_list[CONTEXT->index_length++] = strdup((yyvsp[-1].string));
	}
#line 1593 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 282 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1602 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 289 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1614 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 299 "yacc_sql.y"
                                   {    }
#line 1620 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 304 "yacc_sql.y"
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
#line 1635 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE NOT NULLL  */
#line 315 "yacc_sql.y"
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
#line 1650 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type LBRACE number RBRACE NULLABLE  */
#line 326 "yacc_sql.y"
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
#line 1665 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type  */
#line 337 "yacc_sql.y"
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
#line 1680 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type NOT NULLL  */
#line 348 "yacc_sql.y"
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
#line 1695 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type NULLABLE  */
#line 359 "yacc_sql.y"
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
#line 1710 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 371 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1716 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 374 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1722 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 375 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1728 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 376 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1734 "yacc_sql.tab.c"
    break;

  case 48: /* type: STRING_T  */
#line 377 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1740 "yacc_sql.tab.c"
    break;

  case 49: /* type: FLOAT_T  */
#line 378 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1746 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 382 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1755 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES data data_list SEMICOLON  */
#line 391 "yacc_sql.y"
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
#line 1775 "yacc_sql.tab.c"
    break;

  case 52: /* data: LBRACE value value_list RBRACE  */
#line 407 "yacc_sql.y"
                                       {
		CONTEXT->data_list_r[CONTEXT->data_num++]=CONTEXT->value_length;
	}
#line 1783 "yacc_sql.tab.c"
    break;

  case 54: /* data_list: COMMA data data_list  */
#line 413 "yacc_sql.y"
                            { 
  		
	  }
#line 1791 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 420 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1799 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 425 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1807 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 428 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1815 "yacc_sql.tab.c"
    break;

  case 59: /* value: DATEE  */
#line 431 "yacc_sql.y"
           {
			(yyvsp[0].dates) = substr((yyvsp[0].dates),1,strlen((yyvsp[0].dates))-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].dates));
		}
#line 1824 "yacc_sql.tab.c"
    break;

  case 60: /* value: SSS  */
#line 435 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1833 "yacc_sql.tab.c"
    break;

  case 61: /* value: NULLL  */
#line 439 "yacc_sql.y"
               {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1841 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 446 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1853 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 456 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1865 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON  */
#line 466 "yacc_sql.y"
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
#line 1885 "yacc_sql.tab.c"
    break;

  case 65: /* sub_select: LBRACE SELECT sub_select_attribute FROM ID sub_where RBRACE  */
#line 484 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[1], (yyvsp[-2].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[1], CONTEXT->sub_conditions, CONTEXT->sub_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist = 1;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub_condition_length = 0;
	}
#line 1902 "yacc_sql.tab.c"
    break;

  case 67: /* order_by: ORDER BY select_order select_order_list  */
#line 499 "yacc_sql.y"
                                              {
      
    }
#line 1910 "yacc_sql.tab.c"
    break;

  case 69: /* select_order_list: COMMA select_order select_order_list  */
#line 505 "yacc_sql.y"
                                               {

	}
#line 1918 "yacc_sql.tab.c"
    break;

  case 70: /* select_order: ID  */
#line 510 "yacc_sql.y"
           {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1928 "yacc_sql.tab.c"
    break;

  case 71: /* select_order: ID ASC  */
#line 515 "yacc_sql.y"
                 {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1938 "yacc_sql.tab.c"
    break;

  case 72: /* select_order: ID DESC  */
#line 520 "yacc_sql.y"
                  {
			OrderBy order;
			orders_init(&order, NULL, (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1948 "yacc_sql.tab.c"
    break;

  case 73: /* select_order: ID DOT ID  */
#line 525 "yacc_sql.y"
                    {
			OrderBy order;
			orders_init(&order, (yyvsp[-2].string), (yyvsp[0].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1958 "yacc_sql.tab.c"
    break;

  case 74: /* select_order: ID DOT ID ASC  */
#line 530 "yacc_sql.y"
                        {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1968 "yacc_sql.tab.c"
    break;

  case 75: /* select_order: ID DOT ID DESC  */
#line 535 "yacc_sql.y"
                         {
			OrderBy order;
			orders_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
#line 1978 "yacc_sql.tab.c"
    break;

  case 77: /* group_by: GROUP BY select_group select_group_list  */
#line 543 "yacc_sql.y"
                                                  {

	}
#line 1986 "yacc_sql.tab.c"
    break;

  case 79: /* select_group_list: COMMA select_group select_group_list  */
#line 549 "yacc_sql.y"
                                               {

	}
#line 1994 "yacc_sql.tab.c"
    break;

  case 80: /* select_group: ID  */
#line 554 "yacc_sql.y"
           {
			GroupBy group;
			groups_init(&group, NULL, (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2004 "yacc_sql.tab.c"
    break;

  case 81: /* select_group: ID DOT ID  */
#line 559 "yacc_sql.y"
                    {
			GroupBy group;
			groups_init(&group, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
#line 2014 "yacc_sql.tab.c"
    break;

  case 82: /* sub_select_attribute: aggOp LBRACE STAR RBRACE  */
#line 566 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2024 "yacc_sql.tab.c"
    break;

  case 83: /* sub_select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 571 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2034 "yacc_sql.tab.c"
    break;

  case 84: /* sub_select_attribute: aggOp LBRACE ID RBRACE  */
#line 576 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2044 "yacc_sql.tab.c"
    break;

  case 85: /* sub_select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 581 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2054 "yacc_sql.tab.c"
    break;

  case 86: /* sub_select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 586 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2064 "yacc_sql.tab.c"
    break;

  case 87: /* sub_select_attribute: aggOp LBRACE RBRACE  */
#line 591 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2074 "yacc_sql.tab.c"
    break;

  case 88: /* sub_select_attribute: STAR  */
#line 596 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2084 "yacc_sql.tab.c"
    break;

  case 89: /* sub_select_attribute: ID  */
#line 601 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2094 "yacc_sql.tab.c"
    break;

  case 90: /* sub_select_attribute: ID DOT ID  */
#line 606 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
#line 2104 "yacc_sql.tab.c"
    break;

  case 91: /* select_attr: select_attribute attr_list  */
#line 613 "yacc_sql.y"
                                   {

		}
#line 2112 "yacc_sql.tab.c"
    break;

  case 92: /* select_attribute: aggOp LBRACE STAR RBRACE  */
#line 618 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2122 "yacc_sql.tab.c"
    break;

  case 93: /* select_attribute: aggOp LBRACE NUMBER RBRACE  */
#line 623 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array((yyvsp[-1].number)), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2132 "yacc_sql.tab.c"
    break;

  case 94: /* select_attribute: aggOp LBRACE ID RBRACE  */
#line 628 "yacc_sql.y"
                                 {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2142 "yacc_sql.tab.c"
    break;

  case 95: /* select_attribute: aggOp LBRACE ID DOT ID RBRACE  */
#line 633 "yacc_sql.y"
                                        {
			RelAttr attr;
			relation_attr_init_(&attr, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2152 "yacc_sql.tab.c"
    break;

  case 96: /* select_attribute: aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE  */
#line 638 "yacc_sql.y"
                                                                                     {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2162 "yacc_sql.tab.c"
    break;

  case 97: /* select_attribute: aggOp LBRACE RBRACE  */
#line 643 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2172 "yacc_sql.tab.c"
    break;

  case 98: /* select_attribute: STAR  */
#line 648 "yacc_sql.y"
           {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2182 "yacc_sql.tab.c"
    break;

  case 99: /* select_attribute: ID  */
#line 653 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2192 "yacc_sql.tab.c"
    break;

  case 100: /* select_attribute: ID DOT ID  */
#line 658 "yacc_sql.y"
                    {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
#line 2202 "yacc_sql.tab.c"
    break;

  case 102: /* attr_list: COMMA select_attribute attr_list  */
#line 666 "yacc_sql.y"
                                           {

		}
#line 2210 "yacc_sql.tab.c"
    break;

  case 103: /* aggr_select_attr: STAR  */
#line 671 "yacc_sql.y"
        {  
      
		}
#line 2218 "yacc_sql.tab.c"
    break;

  case 104: /* aggr_select_attr: ID  */
#line 674 "yacc_sql.y"
         {

		}
#line 2226 "yacc_sql.tab.c"
    break;

  case 105: /* aggr_select_attr: ID DOT ID  */
#line 677 "yacc_sql.y"
                    {

		}
#line 2234 "yacc_sql.tab.c"
    break;

  case 107: /* aggr_attr_list: COMMA STAR aggr_attr_list  */
#line 683 "yacc_sql.y"
                                {
      
      }
#line 2242 "yacc_sql.tab.c"
    break;

  case 108: /* aggr_attr_list: COMMA ID aggr_attr_list  */
#line 686 "yacc_sql.y"
                              {
      
      }
#line 2250 "yacc_sql.tab.c"
    break;

  case 109: /* aggr_attr_list: COMMA ID DOT ID aggr_attr_list  */
#line 689 "yacc_sql.y"
                                     {
      
  	  }
#line 2258 "yacc_sql.tab.c"
    break;

  case 111: /* rel_list: COMMA ID rel_list  */
#line 697 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-1].string));
		  }
#line 2266 "yacc_sql.tab.c"
    break;

  case 112: /* rel_list: INNER JOIN ID inner_join_on rel_list  */
#line 701 "yacc_sql.y"
                                           {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], (yyvsp[-2].string));
		  }
#line 2274 "yacc_sql.tab.c"
    break;

  case 114: /* where: WHERE condition condition_list  */
#line 707 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2282 "yacc_sql.tab.c"
    break;

  case 116: /* inner_join_on: ON condition condition_list  */
#line 713 "yacc_sql.y"
                                  {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2290 "yacc_sql.tab.c"
    break;

  case 118: /* condition_list: AND condition condition_list  */
#line 719 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2298 "yacc_sql.tab.c"
    break;

  case 119: /* condition: ID comOp value  */
#line 725 "yacc_sql.y"
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
#line 2323 "yacc_sql.tab.c"
    break;

  case 120: /* condition: value comOp value  */
#line 746 "yacc_sql.y"
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
#line 2347 "yacc_sql.tab.c"
    break;

  case 121: /* condition: ID comOp ID  */
#line 766 "yacc_sql.y"
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
#line 2371 "yacc_sql.tab.c"
    break;

  case 122: /* condition: value comOp ID  */
#line 786 "yacc_sql.y"
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
#line 2397 "yacc_sql.tab.c"
    break;

  case 123: /* condition: ID DOT ID comOp value  */
#line 808 "yacc_sql.y"
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
#line 2422 "yacc_sql.tab.c"
    break;

  case 124: /* condition: value comOp ID DOT ID  */
#line 829 "yacc_sql.y"
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
#line 2447 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID DOT ID comOp ID DOT ID  */
#line 850 "yacc_sql.y"
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
#line 2470 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp sub_select  */
#line 869 "yacc_sql.y"
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
#line 2491 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID comOp sub_select  */
#line 886 "yacc_sql.y"
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
#line 2513 "yacc_sql.tab.c"
    break;

  case 129: /* sub_where: WHERE sub_condition sub_condition_list  */
#line 906 "yacc_sql.y"
                                             {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2521 "yacc_sql.tab.c"
    break;

  case 131: /* sub_condition_list: AND sub_condition sub_condition_list  */
#line 912 "yacc_sql.y"
                                           {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2529 "yacc_sql.tab.c"
    break;

  case 132: /* sub_condition: ID comOp value  */
#line 918 "yacc_sql.y"
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
#line 2554 "yacc_sql.tab.c"
    break;

  case 133: /* sub_condition: value comOp value  */
#line 939 "yacc_sql.y"
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
#line 2578 "yacc_sql.tab.c"
    break;

  case 134: /* sub_condition: ID comOp ID  */
#line 959 "yacc_sql.y"
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
#line 2602 "yacc_sql.tab.c"
    break;

  case 135: /* sub_condition: value comOp ID  */
#line 979 "yacc_sql.y"
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
#line 2628 "yacc_sql.tab.c"
    break;

  case 136: /* sub_condition: ID DOT ID comOp value  */
#line 1001 "yacc_sql.y"
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
#line 2653 "yacc_sql.tab.c"
    break;

  case 137: /* sub_condition: value comOp ID DOT ID  */
#line 1022 "yacc_sql.y"
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
#line 2678 "yacc_sql.tab.c"
    break;

  case 138: /* sub_condition: ID DOT ID comOp ID DOT ID  */
#line 1043 "yacc_sql.y"
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
#line 2701 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: EQ  */
#line 1099 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2707 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: LT  */
#line 1100 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2713 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: GT  */
#line 1101 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2719 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: LE  */
#line 1102 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2725 "yacc_sql.tab.c"
    break;

  case 143: /* comOp: GE  */
#line 1103 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2731 "yacc_sql.tab.c"
    break;

  case 144: /* comOp: NE  */
#line 1104 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2737 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: IS NOT  */
#line 1105 "yacc_sql.y"
                 { CONTEXT->comp = COMP_IS_NOT; }
#line 2743 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: IS  */
#line 1106 "yacc_sql.y"
             { CONTEXT->comp = COMP_IS; }
#line 2749 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: IN  */
#line 1107 "yacc_sql.y"
             { CONTEXT->comp = COMP_IN; }
#line 2755 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: NOT IN  */
#line 1108 "yacc_sql.y"
                 { CONTEXT->comp = COMP_NOT_IN; }
#line 2761 "yacc_sql.tab.c"
    break;

  case 149: /* aggOp: AGG_COUNT  */
#line 1112 "yacc_sql.y"
                    { CONTEXT->aggop = COUNT; }
#line 2767 "yacc_sql.tab.c"
    break;

  case 150: /* aggOp: AGG_MAX  */
#line 1113 "yacc_sql.y"
                  { CONTEXT->aggop = MAX; }
#line 2773 "yacc_sql.tab.c"
    break;

  case 151: /* aggOp: AGG_MIN  */
#line 1114 "yacc_sql.y"
                  { CONTEXT->aggop = MIN; }
#line 2779 "yacc_sql.tab.c"
    break;

  case 152: /* aggOp: AGG_AVG  */
#line 1115 "yacc_sql.y"
                  { CONTEXT->aggop = AVG; }
#line 2785 "yacc_sql.tab.c"
    break;

  case 153: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1120 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2794 "yacc_sql.tab.c"
    break;


#line 2798 "yacc_sql.tab.c"

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

#line 1125 "yacc_sql.y"

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
