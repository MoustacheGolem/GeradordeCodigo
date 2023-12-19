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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintatico.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "code.h"
	#include "sintatic_tree.h"

	//#define YYDEBUG 1

	extern FILE *yyin;
	extern FILE *yyout;

	// SEMANTICO
	struct regTabSimb {
		char *nome; /* nome do simbolo */
		char *tipo; /* tipo_int ou tipo_cad ou nsa */
		char *natureza; /* variavel ou procedimento */
		char *usado; /* sim ou nao */
		int locMem;
		struct regTabSimb *prox; /* ponteiro */
	};

	typedef struct regTabSimb regTabSimb;
	regTabSimb *tabSimb = (regTabSimb *)0;
	regTabSimb *colocaSimb();
	int erroSemantico;

	static int proxLocMemVar = 0;
	// FIM SEMANTICO

	// GERA CODIGO
	int locMemId = 0; /* para recuperacao na TS */

	/* TM location number for current instruction emission */
	static int emitLoc = 0 ;

	/* Highest TM location emitted so far
	For use in conjunction with emitSkip,
	emitBackup, and emitRestore */
	static int highEmitLoc = 0;
	// FIM GERA CODIGO

	static int labelIf = 0;
	static int labelFor = 0;
	static int labelWhile = 0;

	char *type_info;
	int val_info = 1;
	static struct astNode* astRoot;

	char* concatNum(char *src, int num);


#line 125 "sintatico.tab.c"

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

#include "sintatico.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_INTEIRO = 5,                    /* INTEIRO  */
  YYSYMBOL_ESCREVA = 6,                    /* ESCREVA  */
  YYSYMBOL_ENTRADA = 7,                    /* ENTRADA  */
  YYSYMBOL_NUM = 8,                        /* NUM  */
  YYSYMBOL_ID = 9,                         /* ID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_ADD = 14,                       /* ADD  */
  YYSYMBOL_SUB = 15,                       /* SUB  */
  YYSYMBOL_DIV = 16,                       /* DIV  */
  YYSYMBOL_MUL = 17,                       /* MUL  */
  YYSYMBOL_AND = 18,                       /* AND  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_LE = 22,                        /* LE  */
  YYSYMBOL_GE = 23,                        /* GE  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_DIF = 25,                       /* DIF  */
  YYSYMBOL_UMINUS = 26,                    /* UMINUS  */
  YYSYMBOL_THEN = 27,                      /* THEN  */
  YYSYMBOL_28_ = 28,                       /* '{'  */
  YYSYMBOL_29_ = 29,                       /* '}'  */
  YYSYMBOL_30_ = 30,                       /* ';'  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_programa = 36,                  /* programa  */
  YYSYMBOL_declaracoes = 37,               /* declaracoes  */
  YYSYMBOL_linha_decl = 38,                /* linha_decl  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_type = 40,                      /* type  */
  YYSYMBOL_lista_id = 41,                  /* lista_id  */
  YYSYMBOL_lista_cmds = 42,                /* lista_cmds  */
  YYSYMBOL_cmd = 43,                       /* cmd  */
  YYSYMBOL_stmt = 44,                      /* stmt  */
  YYSYMBOL_stmt_if = 45,                   /* stmt_if  */
  YYSYMBOL_stmt_while = 46,                /* stmt_while  */
  YYSYMBOL_stmt_for = 47,                  /* stmt_for  */
  YYSYMBOL_for_atr = 48,                   /* for_atr  */
  YYSYMBOL_for_expr = 49,                  /* for_expr  */
  YYSYMBOL_final_for = 50,                 /* final_for  */
  YYSYMBOL_cmd_saida = 51,                 /* cmd_saida  */
  YYSYMBOL_cmd_entrada = 52,               /* cmd_entrada  */
  YYSYMBOL_cmd_atribuicao = 53,            /* cmd_atribuicao  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_binop = 55,                     /* binop  */
  YYSYMBOL_logop = 56,                     /* logop  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_term2 = 58                      /* term2  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   282


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
      32,    33,     2,     2,    31,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    30,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    28,     2,    29,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    87,    87,   126,   128,   131,   131,   134,   135,   138,
     148,   178,   179,   180,   181,   183,   184,   185,   189,   190,
     191,   194,   203,   221,   234,   247,   249,   252,   256,   257,
     261,   262,   265,   271,   287,   304,   305,   334,   388,   389,
     390,   391,   394,   395,   396,   397,   398,   399,   400,   401,
     404,   408,   421,   425
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "CHAR",
  "INTEIRO", "ESCREVA", "ENTRADA", "NUM", "ID", "IF", "ELSE", "WHILE",
  "FOR", "ADD", "SUB", "DIV", "MUL", "AND", "OR", "LT", "GT", "LE", "GE",
  "EQ", "DIF", "UMINUS", "THEN", "'{'", "'}'", "';'", "','", "'('", "')'",
  "'='", "$accept", "programa", "declaracoes", "linha_decl", "$@1", "type",
  "lista_id", "lista_cmds", "cmd", "stmt", "stmt_if", "stmt_while",
  "stmt_for", "for_atr", "for_expr", "final_for", "cmd_saida",
  "cmd_entrada", "cmd_atribuicao", "expr", "binop", "logop", "term",
  "term2", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,   -33,   -33,     9,   -16,    15,   -33,   -33,     1,   -33,
       6,   -15,   -12,   -10,    10,    28,    29,    36,    38,     1,
     -33,   -33,   -33,   -33,   -33,   -33,    33,    39,    35,    57,
      35,    35,    35,    -5,   -33,     1,   -33,     6,   -33,   -33,
     -33,    14,   -33,    40,   101,    34,    64,   -10,   -33,    -3,
      41,    42,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,    37,    37,   -33,
      46,    47,   -33,    -7,    84,   -33,   -33,   -33,   -33,   -33,
     -33,     1,     1,   -33,    48,    58,   -33,    61,    63,     1,
     -33,    82,   -33,    65,    67,   -33,     1,    81,   -33
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     7,     8,     0,     0,     4,     5,     1,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      18,    19,    20,    15,    16,    17,    10,     0,     0,     0,
       0,     0,     0,     0,     2,    11,    14,     0,     6,    50,
      51,     0,    35,     0,    34,     0,     0,    51,    25,     0,
       0,     0,    13,     9,    38,    39,    41,    40,    48,    49,
      45,    44,    43,    42,    46,    47,    32,     0,     0,    33,
       0,     0,    28,     0,     0,    27,    26,    52,    53,    36,
      37,     0,     0,    30,     0,     0,    29,     0,     0,     0,
      31,    21,    23,     0,     0,    24,     0,     0,    22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -33,   -33,    91,   -33,   -33,   -33,    74,   -19,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -32,    -9,
     -33,   -33,    79,    45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    10,     6,    27,    17,    18,    19,
      20,    21,    22,    49,    73,    84,    23,    24,    25,    41,
      67,    68,    42,    79
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    50,    13,    39,    47,    39,    40,    11,    12,     7,
      13,    14,     8,    15,    16,    26,    52,    28,     1,     2,
      29,    44,    45,    46,    30,    48,    83,    72,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      74,    85,    31,    39,    40,    77,    78,    66,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      32,    33,    87,    88,    37,    34,    43,    70,    35,    38,
      93,    75,    76,    69,    81,    82,    89,    97,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      91,    90,    92,    94,    95,    96,     9,    71,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      98,    53,    51,    80,    86,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65
};

static const yytype_int8 yycheck[] =
{
      19,    33,     9,     8,     9,     8,     9,     6,     7,     0,
       9,    10,    28,    12,    13,     9,    35,    32,     3,     4,
      32,    30,    31,    32,    34,    30,    33,    30,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      49,    73,    32,     8,     9,     8,     9,    33,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      32,    32,    81,    82,    31,    29,     9,    33,    30,    30,
      89,    30,    30,    33,    28,    28,    28,    96,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      29,    33,    29,    11,    29,    28,     5,    33,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      29,    37,    33,    68,    30,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    36,    37,    38,    40,     0,    28,    37,
      39,     6,     7,     9,    10,    12,    13,    42,    43,    44,
      45,    46,    47,    51,    52,    53,     9,    41,    32,    32,
      34,    32,    32,    32,    29,    30,    42,    31,    30,     8,
       9,    54,    57,     9,    54,    54,    54,     9,    30,    48,
      53,    57,    42,    41,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    33,    55,    56,    33,
      33,    33,    30,    49,    54,    30,    30,     8,     9,    58,
      58,    28,    28,    33,    50,    53,    30,    42,    42,    28,
      33,    29,    29,    42,    11,    29,    28,    42,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    39,    38,    40,    40,    41,
      41,    42,    42,    42,    42,    43,    43,    43,    44,    44,
      44,    45,    45,    46,    47,    48,    48,    48,    49,    49,
      50,    50,    51,    52,    53,    54,    54,    54,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     1,     0,     4,     1,     1,     3,
       1,     2,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     7,    11,     7,     8,     1,     2,     2,     1,     2,
       1,     2,     4,     4,     3,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2: /* programa: declaracoes '{' lista_cmds '}'  */
#line 88 "sintatico.y"
        {
		printf("\nok programa\n");
		switch(erroSemantico){
			case(0):
				printf("\nO programa não possui erros semânticos");
			break;
			case(1):
				printf("\nErro semantico: Variavel não declarada");
			break;

			case(2):
				printf("\nErro semantico: variavel ja declarada anteriormente");
			break;

			case(3):
				printf("\nErro semantico: ");
			break;
		}

		buffer:

		if(erroSemantico == 0)
		{
			astNode* dec = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".section .data"), 
								appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, "buffer"),(yyvsp[-3].node)));
			astNode* cmds = appendNodes(createAstNode(AST_SECTION,(union ARG) 0, (union ARG) 0, (union ARG) 0, ".section .text"), (yyvsp[-1].node));
			astRoot = appendNodes(dec,appendNodes(cmds,createAstNode(AST_HALT,(union ARG) 0, (union ARG) 0, (union ARG) 0, "")));
		}
		else
		{
			astRoot = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		}

		YYACCEPT;
	}
#line 1270 "sintatico.tab.c"
    break;

  case 3: /* declaracoes: linha_decl declaracoes  */
#line 126 "sintatico.y"
                                        {(yyval.node) = appendNodes((yyvsp[-1].node), (yyvsp[0].node));}
#line 1276 "sintatico.tab.c"
    break;

  case 4: /* declaracoes: linha_decl  */
#line 128 "sintatico.y"
                                                        {(yyval.node) = (yyvsp[0].node);}
#line 1282 "sintatico.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 131 "sintatico.y"
                 {type_info = (yyvsp[0].cadeia);}
#line 1288 "sintatico.tab.c"
    break;

  case 6: /* linha_decl: type $@1 lista_id ';'  */
#line 131 "sintatico.y"
                                                { (yyval.node) = (yyvsp[-1].node);}
#line 1294 "sintatico.tab.c"
    break;

  case 7: /* type: INT  */
#line 134 "sintatico.y"
                        {(yyval.cadeia) = "type_int"; }
#line 1300 "sintatico.tab.c"
    break;

  case 8: /* type: CHAR  */
#line 135 "sintatico.y"
                        {(yyval.cadeia) = "type_char";}
#line 1306 "sintatico.tab.c"
    break;

  case 9: /* lista_id: ID ',' lista_id  */
#line 139 "sintatico.y"
        {
		if(constaTabSimb((yyvsp[-2].cadeia)))
		{
			erroSemantico = 2; 
		}

		colocaSimb((yyvsp[-2].cadeia),type_info,"variavel","nao",proxLocMemVar++);
		(yyval.node) = appendNodes(createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, (yyvsp[-2].cadeia)), (yyvsp[0].node));
	}
#line 1320 "sintatico.tab.c"
    break;

  case 10: /* lista_id: ID  */
#line 149 "sintatico.y"
        {	
		
		if(constaTabSimb((yyvsp[0].cadeia)))
		{
			erroSemantico = 2;
		}
		colocaSimb((yyvsp[0].cadeia),type_info,"variavel","nao",proxLocMemVar++);
		(yyval.node) = createAstNode(AST_DATA,(union ARG) 0, (union ARG) 0, (union ARG) 0, (yyvsp[0].cadeia));
		
	}
#line 1335 "sintatico.tab.c"
    break;

  case 11: /* lista_cmds: cmd ';'  */
#line 178 "sintatico.y"
                                                        {(yyval.node) = (yyvsp[-1].node); }
#line 1341 "sintatico.tab.c"
    break;

  case 12: /* lista_cmds: stmt  */
#line 179 "sintatico.y"
                                                                {(yyval.node) = (yyvsp[0].node);}
#line 1347 "sintatico.tab.c"
    break;

  case 13: /* lista_cmds: cmd ';' lista_cmds  */
#line 180 "sintatico.y"
                                                {(yyval.node) = appendNodes((yyvsp[-2].node), (yyvsp[0].node));}
#line 1353 "sintatico.tab.c"
    break;

  case 14: /* lista_cmds: stmt lista_cmds  */
#line 181 "sintatico.y"
                                                        {(yyval.node) = appendNodes((yyvsp[-1].node), (yyvsp[0].node));}
#line 1359 "sintatico.tab.c"
    break;

  case 15: /* cmd: cmd_saida  */
#line 183 "sintatico.y"
                                        {(yyval.node) = (yyvsp[0].node) ;}
#line 1365 "sintatico.tab.c"
    break;

  case 16: /* cmd: cmd_entrada  */
#line 184 "sintatico.y"
                                        {(yyval.node) = (yyvsp[0].node) ;}
#line 1371 "sintatico.tab.c"
    break;

  case 17: /* cmd: cmd_atribuicao  */
#line 185 "sintatico.y"
                                        {(yyval.node) = (yyvsp[0].node) ;}
#line 1377 "sintatico.tab.c"
    break;

  case 18: /* stmt: stmt_if  */
#line 189 "sintatico.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1383 "sintatico.tab.c"
    break;

  case 19: /* stmt: stmt_while  */
#line 190 "sintatico.y"
                                {(yyval.node) = (yyvsp[0].node);}
#line 1389 "sintatico.tab.c"
    break;

  case 20: /* stmt: stmt_for  */
#line 191 "sintatico.y"
                                        {(yyval.node) = (yyvsp[0].node);}
#line 1395 "sintatico.tab.c"
    break;

  case 21: /* stmt_if: IF '(' expr ')' '{' lista_cmds '}'  */
#line 195 "sintatico.y"
        {
		(yyval.node) = 
		appendNodes((yyvsp[-4].node) , 
			appendNodes(createAstNode(AST_JEQ, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("IFEND#", labelIf), ""), 
				appendNodes((yyvsp[-1].node), createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,concatNum("ENDIF#", labelIf)))));
		labelIf++;
		
	}
#line 1408 "sintatico.tab.c"
    break;

  case 22: /* stmt_if: IF '(' expr ')' '{' lista_cmds '}' ELSE '{' lista_cmds '}'  */
#line 204 "sintatico.y"
        {
		astNode* nodeLeft = 
		appendNodes((yyvsp[-8].node) , 
			appendNodes(createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ELSE#",labelIf), ""), 
					appendNodes((yyvsp[-5].node),
						 createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("ENDIF#", labelIf), ""))));

		astNode* nodeRight = 
		appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ELSE#",labelIf)),
			appendNodes((yyvsp[-1].node), createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0, concatNum("ENDIF#",labelIf))));

		
		(yyval.node) = appendNodes(nodeLeft, nodeRight);
		labelIf++;
	}
#line 1428 "sintatico.tab.c"
    break;

  case 23: /* stmt_while: WHILE '(' expr ')' '{' lista_cmds '}'  */
#line 222 "sintatico.y"
        {
		(yyval.node) = 
		appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("WHILE#", labelWhile), ""),
			appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILEB#", labelWhile)) ,
				appendNodes((yyvsp[-1].node),
					appendNodes((yyvsp[-4].node), 
						appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("WHILE#", labelWhile)), 
							createAstNode(AST_JGT, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("WHILEB#", labelWhile), ""))))));
		labelWhile++;
	}
#line 1443 "sintatico.tab.c"
    break;

  case 24: /* stmt_for: FOR '(' for_atr for_expr final_for '{' lista_cmds '}'  */
#line 235 "sintatico.y"
        {
		(yyval.node) = appendNodes((yyvsp[-5].node), 
				appendNodes(createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("FOR#", labelFor)),
					appendNodes((yyvsp[-4].node),
						appendNodes(createAstNode(AST_JLE, (union ARG) RS, (union ARG) ZERO, (union ARG) concatNum("ENDFOR#", labelFor), ""),
							appendNodes((yyvsp[-1].node),
								appendNodes((yyvsp[-3].node),
									appendNodes(createAstNode(AST_JEQ, (union ARG) ZERO, (union ARG) ZERO, (union ARG) concatNum("FOR#", labelFor), ""), 
										createAstNode(AST_LABEL, (union ARG) 0, (union ARG) 0, (union ARG) 0,  concatNum("ENDFOR#", labelFor)))))))));
	}
#line 1458 "sintatico.tab.c"
    break;

  case 25: /* for_atr: ';'  */
#line 248 "sintatico.y"
        { (yyval.node) = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", ""); }
#line 1464 "sintatico.tab.c"
    break;

  case 26: /* for_atr: term ';'  */
#line 251 "sintatico.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1470 "sintatico.tab.c"
    break;

  case 27: /* for_atr: cmd_atribuicao ';'  */
#line 253 "sintatico.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1476 "sintatico.tab.c"
    break;

  case 28: /* for_expr: ';'  */
#line 256 "sintatico.y"
                                { (yyval.node) = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", ""); }
#line 1482 "sintatico.tab.c"
    break;

  case 29: /* for_expr: expr ';'  */
#line 257 "sintatico.y"
                                        { (yyval.node) = (yyvsp[-1].node) ;}
#line 1488 "sintatico.tab.c"
    break;

  case 30: /* final_for: ')'  */
#line 261 "sintatico.y"
                 { (yyval.node) = createAstNode(AST_NONE, (union ARG) ZERO, (union ARG) ZERO, (union ARG) "", "") ;}
#line 1494 "sintatico.tab.c"
    break;

  case 31: /* final_for: cmd_atribuicao ')'  */
#line 262 "sintatico.y"
                                              { (yyval.node) = (yyvsp[-1].node) ;}
#line 1500 "sintatico.tab.c"
    break;

  case 32: /* cmd_saida: ESCREVA '(' expr ')'  */
#line 266 "sintatico.y"
        { 
		(yyval.node) = appendNodes((yyvsp[-1].node), createAstNode(AST_OUT, (union ARG) RS, (union ARG) 0, (union ARG) 0, ""));
	}
#line 1508 "sintatico.tab.c"
    break;

  case 33: /* cmd_entrada: ENTRADA '(' ID ')'  */
#line 272 "sintatico.y"
        { 
		
		if (!constaTabSimb((yyvsp[-1].cadeia))) 
		{
		  	erroSemantico = 1;
		  	(yyval.node) = appendNodes((yyvsp[-1].cadeia), createAstNode(AST_ERROR, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""));
		} else
		{
			locMemId = recuperaLocMemId((yyvsp[-1].cadeia));
			(yyval.node) = appendNodes(createAstNode(AST_IN, (union ARG) RS, (union ARG) 0, (union ARG) 0, ""), 
					createAstNode(AST_LD, (union ARG) RS, (union ARG) 0, (union ARG) AC, (yyvsp[-1].cadeia)));
		}
	}
#line 1526 "sintatico.tab.c"
    break;

  case 34: /* cmd_atribuicao: ID '=' expr  */
#line 288 "sintatico.y"
        {	
		
		if (!constaTabSimb((yyvsp[-2].cadeia))) 
		{
		  	erroSemantico = 1;
		  	(yyval.node) = appendNodes((yyvsp[0].node), createAstNode(AST_ERROR, (union ARG) 0, (union ARG) 0, (union ARG) 0, ""));
		} else
		{
			locMemId = recuperaLocMemId((yyvsp[-2].cadeia));
			(yyval.node) = appendNodes((yyvsp[0].node), createAstNode(AST_ST, (union ARG) RS, (union ARG) 0, (union ARG) AC, (yyvsp[-2].cadeia)));
		}
		
	}
#line 1544 "sintatico.tab.c"
    break;

  case 35: /* expr: term  */
#line 304 "sintatico.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1550 "sintatico.tab.c"
    break;

  case 36: /* expr: expr binop term2  */
#line 306 "sintatico.y"
        {
        switch((yyvsp[-1].inteiro)){
			case 1:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_ADD, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 2:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_SUB, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 3:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_MUL, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 4:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_DIV, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;
		}
	}
#line 1582 "sintatico.tab.c"
    break;

  case 37: /* expr: expr logop term2  */
#line 335 "sintatico.y"
        {
        switch((yyvsp[-1].inteiro)){
			case 1:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_GE, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 2:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_LE, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 3:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_GT, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 4:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_LT, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 5:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_EQ, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 6:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_DIF, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 7:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_AND, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;

			case 8:
				(yyval.node) = appendNodes((yyvsp[-2].node), 
						appendNodes((yyvsp[0].node), 
							createAstNode(AST_OR, (union ARG) RS, (union ARG) RS, (union ARG) AC, "")));
			break;
		}
	}
#line 1638 "sintatico.tab.c"
    break;

  case 38: /* binop: ADD  */
#line 388 "sintatico.y"
                {(yyval.inteiro) = 1;}
#line 1644 "sintatico.tab.c"
    break;

  case 39: /* binop: SUB  */
#line 389 "sintatico.y"
                        {(yyval.inteiro) = 2;}
#line 1650 "sintatico.tab.c"
    break;

  case 40: /* binop: MUL  */
#line 390 "sintatico.y"
                        {(yyval.inteiro) = 3;}
#line 1656 "sintatico.tab.c"
    break;

  case 41: /* binop: DIV  */
#line 391 "sintatico.y"
                        {(yyval.inteiro) = 4;}
#line 1662 "sintatico.tab.c"
    break;

  case 42: /* logop: GE  */
#line 394 "sintatico.y"
                        {(yyval.inteiro) = 1;}
#line 1668 "sintatico.tab.c"
    break;

  case 43: /* logop: LE  */
#line 395 "sintatico.y"
                        {(yyval.inteiro) = 2;}
#line 1674 "sintatico.tab.c"
    break;

  case 44: /* logop: GT  */
#line 396 "sintatico.y"
                        {(yyval.inteiro) = 3;}
#line 1680 "sintatico.tab.c"
    break;

  case 45: /* logop: LT  */
#line 397 "sintatico.y"
                        {(yyval.inteiro) = 4;}
#line 1686 "sintatico.tab.c"
    break;

  case 46: /* logop: EQ  */
#line 398 "sintatico.y"
                        {(yyval.inteiro) = 5;}
#line 1692 "sintatico.tab.c"
    break;

  case 47: /* logop: DIF  */
#line 399 "sintatico.y"
                        {(yyval.inteiro) = 6;}
#line 1698 "sintatico.tab.c"
    break;

  case 48: /* logop: AND  */
#line 400 "sintatico.y"
                        {(yyval.inteiro) = 7;}
#line 1704 "sintatico.tab.c"
    break;

  case 49: /* logop: OR  */
#line 401 "sintatico.y"
                        {(yyval.inteiro) = 8;}
#line 1710 "sintatico.tab.c"
    break;

  case 50: /* term: NUM  */
#line 405 "sintatico.y"
        {
		(yyval.node) = createAstNode(AST_ADDI, (union ARG) RS, (union ARG) ZERO,(union ARG)(yyvsp[0].inteiro), "");
	}
#line 1718 "sintatico.tab.c"
    break;

  case 51: /* term: ID  */
#line 409 "sintatico.y"
        {
		if (!constaTabSimb((yyvsp[0].cadeia))) 
		{
		  erroSemantico = 1;
		  (yyval.node) = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		} else {
		  locMemId = recuperaLocMemId((yyvsp[0].cadeia));
		  (yyval.node) = createAstNode(AST_LD, (union ARG) RS, (union ARG)0, (union ARG) AC, (yyvsp[0].cadeia));
		}
	}
#line 1733 "sintatico.tab.c"
    break;

  case 52: /* term2: NUM  */
#line 422 "sintatico.y"
        {
		(yyval.node) = createAstNode(AST_ADDI, (union ARG) AC, (union ARG) ZERO, (union ARG) (yyvsp[0].inteiro), "");
	}
#line 1741 "sintatico.tab.c"
    break;

  case 53: /* term2: ID  */
#line 426 "sintatico.y"
        {
		if (!constaTabSimb((yyvsp[0].cadeia))) 
		{
		  erroSemantico = 1;
		  (yyval.node) = createAstNode(AST_ERROR,(union ARG) 0, (union ARG) 0, (union ARG) 0, "");
		} else {
		  locMemId = recuperaLocMemId((yyvsp[0].cadeia));
		   (yyval.node) = appendNodes(createAstNode(AST_LD, (union ARG) AU, (union ARG)0, (union ARG)0, "")  ,createAstNode(AST_ADD, (union ARG) AC, (union ARG) ZERO, (union ARG) AU, "")) ;
		}
	}
#line 1756 "sintatico.tab.c"
    break;


#line 1760 "sintatico.tab.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 438 "sintatico.y"



// ------------------------------------------------ SEMANTICO ------------------------------------------------

// TODO se for fazer função fazer removeSimb = código para remvoer node de lista de encadeada

regTabSimb *colocaSimb(char *nomeSimb, char *tipoSimb, char *naturezaSimb, char *usadoSimb,int loc){
	regTabSimb *ptr;
	ptr = (regTabSimb *) malloc (sizeof(regTabSimb));

	ptr->nome= (char *) malloc(strlen(nomeSimb)+1);
	ptr->tipo= (char *) malloc(strlen(tipoSimb)+1);
	ptr->natureza= (char *) malloc(strlen(naturezaSimb)+1);
	ptr->usado= (char *) malloc(strlen(usadoSimb)+1);

	strcpy (ptr->nome,nomeSimb);
	strcpy (ptr->tipo,tipoSimb);
	strcpy (ptr->natureza,naturezaSimb);
	strcpy (ptr->usado,usadoSimb);
	ptr->locMem= loc;

	ptr->prox= (struct regTabSimb *)tabSimb;
	tabSimb= ptr;
	return ptr;
}

int constaTabSimb(char *nomeSimb) {
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0) return 1;
	return 0;
}

int recuperaLocMemId(char *nomeSimb) {
	regTabSimb *ptr;
	for (ptr=tabSimb; ptr!=(regTabSimb *)0; ptr=(regTabSimb *)ptr->prox)
	  if (strcmp(ptr->nome,nomeSimb)==0) return ptr->locMem;
	return -1;
}

char* concatNum(char *src, int num) {
	int length = strlen(src) + snprintf(NULL, 0, "%d", num) + 1;
 	char *result = malloc(length);

    if (result == NULL) {
        return NULL;  
	}

    sprintf(result, "%s%d", src, num);

    return result;
}

// printar estrutura da tabela de simbulos
void imprimeTabSimb(regTabSimb *tabSimb) {
  regTabSimb *ptr;
	printf("TabSimb:\n");
  for (ptr = tabSimb; ptr != NULL; ptr = ptr->prox) {
    printf("  Nome: %s ,", ptr->nome);
    printf("Tipo: %s ,", ptr->tipo);
    printf("Natureza: %s ,", ptr->natureza);
    printf("Usado: %s ,", ptr->usado);
    printf("LocMem: %d\n", ptr->locMem);
  }
}
// FIM GERA CODIGO


void generateCode(FILE* file, astNode* node)
{
	if(node == NULL)
	{
		return;
	}
	if(node->left != NULL)
	{
		generateCode(file, node->left);
	}
	if(node->right != NULL)
	{
		generateCode(file, node->right);
	}
	writeCode(file, node);
}



int main(argc, argv) int argc; char **argv;
	{
	yydebug=1;

	erroSemantico=0;

	yyin = fopen("entrada.cm","rt");
	yyout = fopen("saida.s","wt");

	yyparse ();
	generateCode(yyout, astRoot);
	imprimeTabSimb(tabSimb);
	//emitComment("End of execution.");
	// emitRO("HALT",0,0,0,"");

	fclose(yyin);
	fclose(yyout);
	
}
yyerror (s) /* Called by yyparse on error */
	char *s;
{
	printf ("Problema com a analise sintatica: %s!\n", s);
}
