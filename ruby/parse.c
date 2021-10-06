/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Apple Note: For the avoidance of doubt, Apple elects to distribute this file under the terms of the BSD license. */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 12 "parse.y"


#if !YYPURE
# error needs pure parser
#endif
#ifndef PARSER_DEBUG
#define PARSER_DEBUG 0
#endif
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
#define YYSTACK_USE_ALLOCA 0

#include "ruby/ruby.h"
#include "ruby/st.h"
#include "ruby/encoding.h"
#include "internal.h"
#include "node.h"
#include "parse.h"
#include "symbol.h"
#include "regenc.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include "probes.h"

#ifndef WARN_PAST_SCOPE
# define WARN_PAST_SCOPE 0
#endif

#define TAB_WIDTH 8

#define YYMALLOC(size)		rb_parser_malloc(parser, (size))
#define YYREALLOC(ptr, size)	rb_parser_realloc(parser, (ptr), (size))
#define YYCALLOC(nelem, size)	rb_parser_calloc(parser, (nelem), (size))
#define YYFREE(ptr)		rb_parser_free(parser, (ptr))
#define YYFPRINTF		rb_parser_printf
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
# define YY_LOCATION_PRINT(File, Loc) \
     rb_parser_printf(parser, "%d.%d-%d.%d", \
		      (Loc).first_line, (Loc).first_column, \
		      (Loc).last_line,  (Loc).last_column)
#endif
#undef malloc
#undef realloc
#undef calloc
#undef free
#define malloc	YYMALLOC
#define realloc	YYREALLOC
#define calloc	YYCALLOC
#define free	YYFREE

enum lex_state_bits {
    EXPR_BEG_bit,		/* ignore newline, +/- is a sign. */
    EXPR_END_bit,		/* newline significant, +/- is an operator. */
    EXPR_ENDARG_bit,		/* ditto, and unbound braces. */
    EXPR_ENDFN_bit,		/* ditto, and unbound braces. */
    EXPR_ARG_bit,		/* newline significant, +/- is an operator. */
    EXPR_CMDARG_bit,		/* newline significant, +/- is an operator. */
    EXPR_MID_bit,		/* newline significant, +/- is an operator. */
    EXPR_FNAME_bit,		/* ignore newline, no reserved words. */
    EXPR_DOT_bit,		/* right after `.' or `::', no reserved words. */
    EXPR_CLASS_bit,		/* immediate after `class', no here document. */
    EXPR_LABEL_bit,		/* flag bit, label is allowed. */
    EXPR_LABELED_bit,		/* flag bit, just after a label. */
    EXPR_FITEM_bit,		/* symbol literal as FNAME. */
    EXPR_MAX_STATE
};
/* examine combinations */
enum lex_state_e {
#define DEF_EXPR(n) EXPR_##n = (1 << EXPR_##n##_bit)
    DEF_EXPR(BEG),
    DEF_EXPR(END),
    DEF_EXPR(ENDARG),
    DEF_EXPR(ENDFN),
    DEF_EXPR(ARG),
    DEF_EXPR(CMDARG),
    DEF_EXPR(MID),
    DEF_EXPR(FNAME),
    DEF_EXPR(DOT),
    DEF_EXPR(CLASS),
    DEF_EXPR(LABEL),
    DEF_EXPR(LABELED),
    DEF_EXPR(FITEM),
    EXPR_VALUE = EXPR_BEG,
    EXPR_BEG_ANY  =  (EXPR_BEG | EXPR_MID | EXPR_CLASS),
    EXPR_ARG_ANY  =  (EXPR_ARG | EXPR_CMDARG),
    EXPR_END_ANY  =  (EXPR_END | EXPR_ENDARG | EXPR_ENDFN)
};
#define IS_lex_state_for(x, ls)	((x) & (ls))
#define IS_lex_state_all_for(x, ls) (((x) & (ls)) == (ls))
#define IS_lex_state(ls)	IS_lex_state_for(lex_state, (ls))
#define IS_lex_state_all(ls)	IS_lex_state_all_for(lex_state, (ls))

# define SET_LEX_STATE(ls) \
    (lex_state = (yydebug ? trace_lex_state(lex_state, (ls), __LINE__) : \
		  (enum lex_state_e)(ls)))
static enum lex_state_e trace_lex_state(enum lex_state_e from, enum lex_state_e to, int line);

typedef VALUE stack_type;

# define BITSTACK_PUSH(stack, n)	((stack) = ((stack)<<1)|((n)&1))
# define BITSTACK_POP(stack)	((stack) = (stack) >> 1)
# define BITSTACK_LEXPOP(stack)	((stack) = ((stack) >> 1) | ((stack) & 1))
# define BITSTACK_SET_P(stack)	((stack)&1)

#define COND_PUSH(n)	BITSTACK_PUSH(cond_stack, (n))
#define COND_POP()	BITSTACK_POP(cond_stack)
#define COND_LEXPOP()	BITSTACK_LEXPOP(cond_stack)
#define COND_P()	BITSTACK_SET_P(cond_stack)

#define CMDARG_PUSH(n)	BITSTACK_PUSH(cmdarg_stack, (n))
#define CMDARG_POP()	BITSTACK_POP(cmdarg_stack)
#define CMDARG_LEXPOP()	BITSTACK_LEXPOP(cmdarg_stack)
#define CMDARG_P()	BITSTACK_SET_P(cmdarg_stack)

struct vtable {
    ID *tbl;
    int pos;
    int capa;
    struct vtable *prev;
};

struct local_vars {
    struct vtable *args;
    struct vtable *vars;
    struct vtable *used;
# if WARN_PAST_SCOPE
    struct vtable *past;
# endif
    struct local_vars *prev;
    stack_type cmdargs;
};

#define DVARS_INHERIT ((void*)1)
#define DVARS_TOPSCOPE NULL
#define DVARS_SPECIAL_P(tbl) (!POINTER_P(tbl))
#define POINTER_P(val) ((VALUE)(val) & ~(VALUE)3)

static int
vtable_size(const struct vtable *tbl)
{
    if (POINTER_P(tbl)) {
        return tbl->pos;
    }
    else {
        return 0;
    }
}

#define VTBL_DEBUG 0

static struct vtable *
vtable_alloc(struct vtable *prev)
{
    struct vtable *tbl = ALLOC(struct vtable);
    tbl->pos = 0;
    tbl->capa = 8;
    tbl->tbl = ALLOC_N(ID, tbl->capa);
    tbl->prev = prev;
    if (VTBL_DEBUG) printf("vtable_alloc: %p\n", (void *)tbl);
    return tbl;
}

static void
vtable_free(struct vtable *tbl)
{
    if (VTBL_DEBUG)printf("vtable_free: %p\n", (void *)tbl);
    if (POINTER_P(tbl)) {
        if (tbl->tbl) {
            xfree(tbl->tbl);
        }
        xfree(tbl);
    }
}

static void
vtable_add(struct vtable *tbl, ID id)
{
    if (!POINTER_P(tbl)) {
        rb_bug("vtable_add: vtable is not allocated (%p)", (void *)tbl);
    }
    if (VTBL_DEBUG) printf("vtable_add: %p, %"PRIsVALUE"\n", (void *)tbl, rb_id2str(id));

    if (tbl->pos == tbl->capa) {
        tbl->capa = tbl->capa * 2;
        REALLOC_N(tbl->tbl, ID, tbl->capa);
    }
    tbl->tbl[tbl->pos++] = id;
}

#ifndef RIPPER
static void
vtable_pop(struct vtable *tbl, int n)
{
    if (tbl->pos < n) rb_bug("vtable_pop: unreachable");
    tbl->pos -= n;
}
#endif

static int
vtable_included(const struct vtable * tbl, ID id)
{
    int i;

    if (POINTER_P(tbl)) {
        for (i = 0; i < tbl->pos; i++) {
            if (tbl->tbl[i] == id) {
                return i+1;
            }
        }
    }
    return 0;
}


typedef struct token_info {
    const char *token;
    int linenum;
    int column;
    int nonspc;
    struct token_info *next;
} token_info;

/*
    Structure of Lexer Buffer:

 lex_pbeg      tokp         lex_p        lex_pend
    |           |              |            |
    |-----------+--------------+------------|
                |<------------>|
                     token
*/
struct parser_params {
    NODE *heap;

    YYSTYPE *lval;

    struct {
	NODE *strterm;
	VALUE (*gets)(struct parser_params*,VALUE);
	VALUE input;
	VALUE lastline;
	VALUE nextline;
	const char *pbeg;
	const char *pcur;
	const char *pend;
	long gets_ptr;
	enum lex_state_e state;
	int paren_nest;
	int lpar_beg;
	int brace_nest;
    } lex;
    stack_type cond_stack;
    stack_type cmdarg_stack;
    int tokidx;
    int toksiz;
    int tokline;
    int heredoc_end;
    int heredoc_indent;
    int heredoc_line_indent;
    char *tokenbuf;
    NODE *deferred_nodes;
    struct local_vars *lvtbl;
    int line_count;
    int ruby_sourceline;	/* current line no. */
    char *ruby_sourcefile; /* current source file */
    VALUE ruby_sourcefile_string;
    rb_encoding *enc;
    token_info *token_info;
    VALUE compile_option;

    VALUE debug_buffer;

    ID cur_arg;

    int last_cr_line;

    unsigned int command_start:1;
    unsigned int eofp: 1;
    unsigned int ruby__end__seen: 1;
    unsigned int yydebug: 1;
    unsigned int has_shebang: 1;
    unsigned int in_defined: 1;
    unsigned int compile_for_eval: 1;
    unsigned int in_kwarg: 1;
    unsigned int in_single: 1;
    unsigned int in_def: 1;
    unsigned int token_seen: 1;
    unsigned int token_info_enabled: 1;
# if WARN_PAST_SCOPE
    unsigned int past_scope_enabled: 1;
# endif
    unsigned int error_p: 1;

#ifndef RIPPER
    /* Ruby core only */

    NODE *eval_tree_begin;
    NODE *eval_tree;
    VALUE debug_lines;
    VALUE coverage;
#else
    /* Ripper only */

    const char *tokp;
    VALUE delayed;
    int delayed_line;
    int delayed_col;

    VALUE value;
    VALUE result;
    VALUE parsing_thread;
#endif
};

#ifdef RIPPER
#define intern_cstr(n,l,en) rb_intern3(n,l,en)
#else
#define intern_cstr(n,l,en) rb_intern3(n,l,en)
#endif

#define STR_NEW(p,n) rb_enc_str_new((p),(n),current_enc)
#define STR_NEW0() rb_enc_str_new(0,0,current_enc)
#define STR_NEW2(p) rb_enc_str_new((p),strlen(p),current_enc)
#define STR_NEW3(p,n,e,func) parser_str_new((p),(n),(e),(func),current_enc)
#define TOK_INTERN() intern_cstr(tok(), toklen(), current_enc)

static int parser_yyerror(struct parser_params*, const char*);
#define yyerror(msg) parser_yyerror(parser, (msg))

#define lex_strterm		(parser->lex.strterm)
#define lex_state		(parser->lex.state)
#define cond_stack		(parser->cond_stack)
#define cmdarg_stack		(parser->cmdarg_stack)
#define paren_nest		(parser->lex.paren_nest)
#define lpar_beg		(parser->lex.lpar_beg)
#define brace_nest		(parser->lex.brace_nest)
#define in_single		(parser->in_single)
#define in_def			(parser->in_def)
#define compile_for_eval	(parser->compile_for_eval)
#define in_defined		(parser->in_defined)
#define tokenbuf		(parser->tokenbuf)
#define tokidx			(parser->tokidx)
#define toksiz			(parser->toksiz)
#define tokline 		(parser->tokline)
#define lex_input		(parser->lex.input)
#define lex_lastline		(parser->lex.lastline)
#define lex_nextline		(parser->lex.nextline)
#define lex_pbeg		(parser->lex.pbeg)
#define lex_p			(parser->lex.pcur)
#define lex_pend		(parser->lex.pend)
#define heredoc_end		(parser->heredoc_end)
#define heredoc_indent		(parser->heredoc_indent)
#define heredoc_line_indent	(parser->heredoc_line_indent)
#define command_start		(parser->command_start)
#define deferred_nodes		(parser->deferred_nodes)
#define lex_gets_ptr		(parser->lex.gets_ptr)
#define lex_gets		(parser->lex.gets)
#define lvtbl			(parser->lvtbl)
#define ruby__end__seen 	(parser->ruby__end__seen)
#define ruby_sourceline 	(parser->ruby_sourceline)
#define ruby_sourcefile 	(parser->ruby_sourcefile)
#define ruby_sourcefile_string	(parser->ruby_sourcefile_string)
#define current_enc		(parser->enc)
#define current_arg		(parser->cur_arg)
#define yydebug 		(parser->yydebug)
#ifdef RIPPER
#else
#define ruby_eval_tree		(parser->eval_tree)
#define ruby_eval_tree_begin	(parser->eval_tree_begin)
#define ruby_debug_lines	(parser->debug_lines)
#define ruby_coverage		(parser->coverage)
#endif

#define CALL_Q_P(q) ((q) == tANDDOT)
#define NODE_CALL_Q(q) (CALL_Q_P(q) ? NODE_QCALL : NODE_CALL)
#define NEW_QCALL(q,r,m,a) NEW_NODE(NODE_CALL_Q(q),r,m,a)

static int yylex(YYSTYPE*, struct parser_params*);

static inline void
set_line_body(NODE *body, int line)
{
    if (!body) return;
    switch (nd_type(body)) {
      case NODE_RESCUE:
      case NODE_ENSURE:
	nd_set_line(body, line);
    }
}

#ifndef RIPPER
#define yyparse ruby_yyparse

static NODE* node_newnode(struct parser_params *, enum node_type, VALUE, VALUE, VALUE);
#define rb_node_newnode(type, a1, a2, a3) node_newnode(parser, (type), (a1), (a2), (a3))

static NODE *cond_gen(struct parser_params*,NODE*);
#define cond(node) cond_gen(parser, (node))
static NODE *new_if_gen(struct parser_params*,NODE*,NODE*,NODE*);
#define new_if(cc,left,right) new_if_gen(parser, (cc), (left), (right))
#define new_unless(cc,left,right) new_if_gen(parser, (cc), (right), (left))
static NODE *logop_gen(struct parser_params*,enum node_type,NODE*,NODE*);
#define logop(type,node1,node2) logop_gen(parser, (type), (node1), (node2))

static NODE *newline_node(NODE*);
static void fixpos(NODE*,NODE*);

static int value_expr_gen(struct parser_params*,NODE*);
static void void_expr_gen(struct parser_params*,NODE*);
static NODE *remove_begin(NODE*);
static NODE *remove_begin_all(NODE*);
#define value_expr(node) value_expr_gen(parser, (node) = remove_begin(node))
#define void_expr0(node) void_expr_gen(parser, (node))
#define void_expr(node) void_expr0((node) = remove_begin(node))
static void void_stmts_gen(struct parser_params*,NODE*);
#define void_stmts(node) void_stmts_gen(parser, (node))
static void reduce_nodes_gen(struct parser_params*,NODE**);
#define reduce_nodes(n) reduce_nodes_gen(parser,(n))
static void block_dup_check_gen(struct parser_params*,NODE*,NODE*);
#define block_dup_check(n1,n2) block_dup_check_gen(parser,(n1),(n2))

static NODE *block_append_gen(struct parser_params*,NODE*,NODE*);
#define block_append(h,t) block_append_gen(parser,(h),(t))
static NODE *list_append_gen(struct parser_params*,NODE*,NODE*);
#define list_append(l,i) list_append_gen(parser,(l),(i))
static NODE *list_concat(NODE*,NODE*);
static NODE *arg_append_gen(struct parser_params*,NODE*,NODE*);
#define arg_append(h,t) arg_append_gen(parser,(h),(t))
static NODE *arg_concat_gen(struct parser_params*,NODE*,NODE*);
#define arg_concat(h,t) arg_concat_gen(parser,(h),(t))
static NODE *literal_concat_gen(struct parser_params*,NODE*,NODE*);
#define literal_concat(h,t) literal_concat_gen(parser,(h),(t))
static int literal_concat0(struct parser_params *, VALUE, VALUE);
static NODE *new_evstr_gen(struct parser_params*,NODE*);
#define new_evstr(n) new_evstr_gen(parser,(n))
static NODE *evstr2dstr_gen(struct parser_params*,NODE*);
#define evstr2dstr(n) evstr2dstr_gen(parser,(n))
static NODE *splat_array(NODE*);

static NODE *call_bin_op_gen(struct parser_params*,NODE*,ID,NODE*);
#define call_bin_op(recv,id,arg1) call_bin_op_gen(parser, (recv),(id),(arg1))
static NODE *call_uni_op_gen(struct parser_params*,NODE*,ID);
#define call_uni_op(recv,id) call_uni_op_gen(parser, (recv),(id))

static NODE *new_args_gen(struct parser_params*,NODE*,NODE*,ID,NODE*,NODE*);
#define new_args(f,o,r,p,t) new_args_gen(parser, (f),(o),(r),(p),(t))
static NODE *new_args_tail_gen(struct parser_params*,NODE*,ID,ID);
#define new_args_tail(k,kr,b) new_args_tail_gen(parser, (k),(kr),(b))
#define new_kw_arg(k) ((k) ? NEW_KW_ARG(0, (k)) : 0)

static VALUE negate_lit(VALUE);
static NODE *ret_args_gen(struct parser_params*,NODE*);
#define ret_args(node) ret_args_gen(parser, (node))
static NODE *arg_blk_pass(NODE*,NODE*);
static NODE *new_yield_gen(struct parser_params*,NODE*);
#define new_yield(node) new_yield_gen(parser, (node))
static NODE *dsym_node_gen(struct parser_params*,NODE*);
#define dsym_node(node) dsym_node_gen(parser, (node))

static NODE *gettable_gen(struct parser_params*,ID);
#define gettable(id) gettable_gen(parser,(id))
static NODE *assignable_gen(struct parser_params*,ID,NODE*);
#define assignable(id,node) assignable_gen(parser, (id), (node))

static NODE *aryset_gen(struct parser_params*,NODE*,NODE*);
#define aryset(node1,node2) aryset_gen(parser, (node1), (node2))
static NODE *attrset_gen(struct parser_params*,NODE*,ID,ID);
#define attrset(node,q,id) attrset_gen(parser, (node), (q), (id))

static void rb_backref_error_gen(struct parser_params*,NODE*);
#define rb_backref_error(n) rb_backref_error_gen(parser,(n))
static NODE *node_assign_gen(struct parser_params*,NODE*,NODE*);
#define node_assign(node1, node2) node_assign_gen(parser, (node1), (node2))

static NODE *new_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs);
static NODE *new_attr_op_assign_gen(struct parser_params *parser, NODE *lhs, ID atype, ID attr, ID op, NODE *rhs);
#define new_attr_op_assign(lhs, type, attr, op, rhs) new_attr_op_assign_gen(parser, (lhs), (type), (attr), (op), (rhs))
static NODE *new_const_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs);
#define new_const_op_assign(lhs, op, rhs) new_const_op_assign_gen(parser, (lhs), (op), (rhs))

static NODE *kwd_append(NODE*, NODE*);

static NODE *new_hash_gen(struct parser_params *parser, NODE *hash);
#define new_hash(hash) new_hash_gen(parser, (hash))

#define new_defined(expr) NEW_DEFINED(remove_begin_all(expr))

static NODE *match_op_gen(struct parser_params*,NODE*,NODE*);
#define match_op(node1,node2) match_op_gen(parser, (node1), (node2))

static ID  *local_tbl_gen(struct parser_params*);
#define local_tbl() local_tbl_gen(parser)

static void fixup_nodes(NODE **);

static VALUE reg_compile_gen(struct parser_params*, VALUE, int);
#define reg_compile(str,options) reg_compile_gen(parser, (str), (options))
static void reg_fragment_setenc_gen(struct parser_params*, VALUE, int);
#define reg_fragment_setenc(str,options) reg_fragment_setenc_gen(parser, (str), (options))
static int reg_fragment_check_gen(struct parser_params*, VALUE, int);
#define reg_fragment_check(str,options) reg_fragment_check_gen(parser, (str), (options))
static NODE *reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match);
#define reg_named_capture_assign(regexp,match) reg_named_capture_assign_gen(parser,(regexp),(match))

static void parser_heredoc_dedent(struct parser_params*,NODE*);
# define heredoc_dedent(str) parser_heredoc_dedent(parser, (str))

#define get_id(id) (id)
#define get_value(val) (val)
#else
#define NODE_RIPPER NODE_CDECL

static inline VALUE
ripper_new_yylval(ID a, VALUE b, VALUE c)
{
    return (VALUE)NEW_CDECL(a, b, c);
}

static inline int
ripper_is_node_yylval(VALUE n)
{
    return RB_TYPE_P(n, T_NODE) && nd_type(RNODE(n)) == NODE_RIPPER;
}

#define value_expr(node) ((void)(node))
#define remove_begin(node) (node)
#define rb_dvar_defined(id) 0
#define rb_local_defined(id) 0
static ID ripper_get_id(VALUE);
#define get_id(id) ripper_get_id(id)
static VALUE ripper_get_value(VALUE);
#define get_value(val) ripper_get_value(val)
static VALUE assignable_gen(struct parser_params*,VALUE);
#define assignable(lhs,node) assignable_gen(parser, (lhs))
static int id_is_var_gen(struct parser_params *parser, ID id);
#define id_is_var(id) id_is_var_gen(parser, (id))

#define node_assign(node1, node2) dispatch2(assign, (node1), (node2))

static VALUE new_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE op, VALUE rhs);
static VALUE new_attr_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE type, VALUE attr, VALUE op, VALUE rhs);
#define new_attr_op_assign(lhs, type, attr, op, rhs) new_attr_op_assign_gen(parser, (lhs), (type), (attr), (op), (rhs))

#endif /* !RIPPER */

#define new_op_assign(lhs, op, rhs) new_op_assign_gen(parser, (lhs), (op), (rhs))

RUBY_FUNC_EXPORTED VALUE rb_parser_reg_compile(struct parser_params* parser, VALUE str, int options, VALUE *errmsg);

static ID formal_argument_gen(struct parser_params*, ID);
#define formal_argument(id) formal_argument_gen(parser, (id))
static ID shadowing_lvar_gen(struct parser_params*,ID);
#define shadowing_lvar(name) shadowing_lvar_gen(parser, (name))
static void new_bv_gen(struct parser_params*,ID);
#define new_bv(id) new_bv_gen(parser, (id))

static void local_push_gen(struct parser_params*,int);
#define local_push(top) local_push_gen(parser,(top))
static void local_pop_gen(struct parser_params*);
#define local_pop() local_pop_gen(parser)
static void local_var_gen(struct parser_params*, ID);
#define local_var(id) local_var_gen(parser, (id))
static void arg_var_gen(struct parser_params*, ID);
#define arg_var(id) arg_var_gen(parser, (id))
static int  local_id_gen(struct parser_params*, ID);
#define local_id(id) local_id_gen(parser, (id))
static ID   internal_id_gen(struct parser_params*);
#define internal_id() internal_id_gen(parser)

static const struct vtable *dyna_push_gen(struct parser_params *);
#define dyna_push() dyna_push_gen(parser)
static void dyna_pop_gen(struct parser_params*, const struct vtable *);
#define dyna_pop(node) dyna_pop_gen(parser, (node))
static int dyna_in_block_gen(struct parser_params*);
#define dyna_in_block() dyna_in_block_gen(parser)
#define dyna_var(id) local_var(id)
static int dvar_defined_gen(struct parser_params*,ID,int);
#define dvar_defined(id) dvar_defined_gen(parser, (id), 0)
#define dvar_defined_get(id) dvar_defined_gen(parser, (id), 1)
static int dvar_curr_gen(struct parser_params*,ID);
#define dvar_curr(id) dvar_curr_gen(parser, (id))

static int lvar_defined_gen(struct parser_params*, ID);
#define lvar_defined(id) lvar_defined_gen(parser, (id))

#define RE_OPTION_ONCE (1<<16)
#define RE_OPTION_ENCODING_SHIFT 8
#define RE_OPTION_ENCODING(e) (((e)&0xff)<<RE_OPTION_ENCODING_SHIFT)
#define RE_OPTION_ENCODING_IDX(o) (((o)>>RE_OPTION_ENCODING_SHIFT)&0xff)
#define RE_OPTION_ENCODING_NONE(o) ((o)&RE_OPTION_ARG_ENCODING_NONE)
#define RE_OPTION_MASK  0xff
#define RE_OPTION_ARG_ENCODING_NONE 32

#define NODE_STRTERM NODE_ZARRAY	/* nothing to gc */
#define NODE_HEREDOC NODE_ARRAY 	/* 1, 3 to gc */
#define SIGN_EXTEND(x,n) (((1<<(n)-1)^((x)&~(~0<<(n))))-(1<<(n)-1))
#define nd_func u1.id
#if SIZEOF_SHORT == 2
#define nd_term(node) ((signed short)(node)->u2.id)
#else
#define nd_term(node) SIGN_EXTEND((node)->u2.id, CHAR_BIT*2)
#endif
#define nd_paren(node) (char)((node)->u2.id >> CHAR_BIT*2)
#define nd_nest u3.cnt

/****** Ripper *******/

#ifdef RIPPER
#define RIPPER_VERSION "0.1.0"

static inline VALUE intern_sym(const char *name);

#include "eventids1.c"
#include "eventids2.c"

static VALUE ripper_dispatch0(struct parser_params*,ID);
static VALUE ripper_dispatch1(struct parser_params*,ID,VALUE);
static VALUE ripper_dispatch2(struct parser_params*,ID,VALUE,VALUE);
static VALUE ripper_dispatch3(struct parser_params*,ID,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch4(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch5(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE,VALUE);
static VALUE ripper_dispatch7(struct parser_params*,ID,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE,VALUE);
static void ripper_error_gen(struct parser_params *parser);
#define ripper_error() ripper_error_gen(parser)

#define dispatch0(n)            ripper_dispatch0(parser, TOKEN_PASTE(ripper_id_, n))
#define dispatch1(n,a)          ripper_dispatch1(parser, TOKEN_PASTE(ripper_id_, n), (a))
#define dispatch2(n,a,b)        ripper_dispatch2(parser, TOKEN_PASTE(ripper_id_, n), (a), (b))
#define dispatch3(n,a,b,c)      ripper_dispatch3(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c))
#define dispatch4(n,a,b,c,d)    ripper_dispatch4(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d))
#define dispatch5(n,a,b,c,d,e)  ripper_dispatch5(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d), (e))
#define dispatch7(n,a,b,c,d,e,f,g) ripper_dispatch7(parser, TOKEN_PASTE(ripper_id_, n), (a), (b), (c), (d), (e), (f), (g))

#define yyparse ripper_yyparse

#define ripper_intern(s) ID2SYM(rb_intern(s))
static VALUE ripper_id2sym(ID);
#ifdef __GNUC__
#define ripper_id2sym(id) (rb_ispunct((int)(id)) ? \
			   ID2SYM(id) : ripper_id2sym(id))
#endif

#define arg_new() dispatch0(args_new)
#define arg_add(l,a) dispatch2(args_add, (l), (a))
#define arg_add_star(l,a) dispatch2(args_add_star, (l), (a))
#define arg_add_block(l,b) dispatch2(args_add_block, (l), (b))
#define arg_add_optblock(l,b) ((b)==Qundef? (l) : dispatch2(args_add_block, (l), (b)))
#define bare_assoc(v) dispatch1(bare_assoc_hash, (v))
#define arg_add_assocs(l,b) arg_add((l), bare_assoc(b))

#define args2mrhs(a) dispatch1(mrhs_new_from_args, (a))
#define mrhs_new() dispatch0(mrhs_new)
#define mrhs_add(l,a) dispatch2(mrhs_add, (l), (a))
#define mrhs_add_star(l,a) dispatch2(mrhs_add_star, (l), (a))

#define mlhs_new() dispatch0(mlhs_new)
#define mlhs_add(l,a) dispatch2(mlhs_add, (l), (a))
#define mlhs_add_star(l,a) dispatch2(mlhs_add_star, (l), (a))

#define params_new(pars, opts, rest, pars2, kws, kwrest, blk) \
        dispatch7(params, (pars), (opts), (rest), (pars2), (kws), (kwrest), (blk))

#define blockvar_new(p,v) dispatch2(block_var, (p), (v))
#define blockvar_add_star(l,a) dispatch2(block_var_add_star, (l), (a))
#define blockvar_add_block(l,a) dispatch2(block_var_add_block, (l), (a))

#define method_optarg(m,a) ((a)==Qundef ? (m) : dispatch2(method_add_arg,(m),(a)))
#define method_arg(m,a) dispatch2(method_add_arg,(m),(a))
#define method_add_block(m,b) dispatch2(method_add_block, (m), (b))

#define escape_Qundef(x) ((x)==Qundef ? Qnil : (x))

static inline VALUE
new_args_gen(struct parser_params *parser, VALUE f, VALUE o, VALUE r, VALUE p, VALUE tail)
{
    NODE *t = (NODE *)tail;
    VALUE k = t->u1.value, kr = t->u2.value, b = t->u3.value;
    return params_new(f, o, r, p, k, kr, escape_Qundef(b));
}
#define new_args(f,o,r,p,t) new_args_gen(parser, (f),(o),(r),(p),(t))

static inline VALUE
new_args_tail_gen(struct parser_params *parser, VALUE k, VALUE kr, VALUE b)
{
    return (VALUE)MEMO_NEW(k, kr, b);
}
#define new_args_tail(k,kr,b) new_args_tail_gen(parser, (k),(kr),(b))

#define new_defined(expr) dispatch1(defined, (expr))

static void parser_heredoc_dedent(struct parser_params*,VALUE);
# define heredoc_dedent(str) parser_heredoc_dedent(parser, (str))

#define FIXME 0

#endif /* RIPPER */

#ifndef RIPPER
# define Qnone 0
# define ifndef_ripper(x) (x)
#else
# define Qnone Qnil
# define ifndef_ripper(x)
#endif

# define rb_warn0(fmt)         WARN_CALL(WARN_ARGS(fmt, 1))
# define rb_warn1(fmt,a)       WARN_CALL(WARN_ARGS(fmt, 2), (a))
# define rb_warn2(fmt,a,b)     WARN_CALL(WARN_ARGS(fmt, 3), (a), (b))
# define rb_warn3(fmt,a,b,c)   WARN_CALL(WARN_ARGS(fmt, 4), (a), (b), (c))
# define rb_warn4(fmt,a,b,c,d) WARN_CALL(WARN_ARGS(fmt, 5), (a), (b), (c), (d))
# define rb_warning0(fmt)         WARNING_CALL(WARNING_ARGS(fmt, 1))
# define rb_warning1(fmt,a)       WARNING_CALL(WARNING_ARGS(fmt, 2), (a))
# define rb_warning2(fmt,a,b)     WARNING_CALL(WARNING_ARGS(fmt, 3), (a), (b))
# define rb_warning3(fmt,a,b,c)   WARNING_CALL(WARNING_ARGS(fmt, 4), (a), (b), (c))
# define rb_warning4(fmt,a,b,c,d) WARNING_CALL(WARNING_ARGS(fmt, 5), (a), (b), (c), (d))
# define rb_warn0L(l,fmt)         WARN_CALL(WARN_ARGS_L(l, fmt, 1))
# define rb_warn1L(l,fmt,a)       WARN_CALL(WARN_ARGS_L(l, fmt, 2), (a))
# define rb_warn2L(l,fmt,a,b)     WARN_CALL(WARN_ARGS_L(l, fmt, 3), (a), (b))
# define rb_warn3L(l,fmt,a,b,c)   WARN_CALL(WARN_ARGS_L(l, fmt, 4), (a), (b), (c))
# define rb_warn4L(l,fmt,a,b,c,d) WARN_CALL(WARN_ARGS_L(l, fmt, 5), (a), (b), (c), (d))
# define rb_warning0L(l,fmt)         WARNING_CALL(WARNING_ARGS_L(l, fmt, 1))
# define rb_warning1L(l,fmt,a)       WARNING_CALL(WARNING_ARGS_L(l, fmt, 2), (a))
# define rb_warning2L(l,fmt,a,b)     WARNING_CALL(WARNING_ARGS_L(l, fmt, 3), (a), (b))
# define rb_warning3L(l,fmt,a,b,c)   WARNING_CALL(WARNING_ARGS_L(l, fmt, 4), (a), (b), (c))
# define rb_warning4L(l,fmt,a,b,c,d) WARNING_CALL(WARNING_ARGS_L(l, fmt, 5), (a), (b), (c), (d))
#ifdef RIPPER
static ID id_warn, id_warning;
# define WARN_S(s) STR_NEW2(s)
# define WARN_I(i) INT2NUM(i)
# define PRIsWARN "s"
# define WARN_ARGS(fmt,n) parser->value, id_warn, n, rb_usascii_str_new_lit(fmt)
# define WARN_ARGS_L(l,fmt,n) WARN_ARGS(fmt,n)
# define WARN_CALL rb_funcall
# define WARNING_ARGS(fmt,n) parser->value, id_warning, n, rb_usascii_str_new_lit(fmt)
# define WARNING_ARGS_L(l, fmt,n) WARNING_ARGS(fmt,n)
# define WARNING_CALL rb_funcall
static void ripper_compile_error(struct parser_params*, const char *fmt, ...);
# define rb_compile_error ripper_compile_error
# define compile_error ripper_compile_error
# define PARSER_ARG parser,
#else
# define WARN_S(s) s
# define WARN_I(i) i
# define PRIsWARN PRIsVALUE
# define WARN_ARGS(fmt,n) WARN_ARGS_L(ruby_sourceline,fmt,n)
# define WARN_ARGS_L(l,fmt,n) ruby_sourcefile, (l), (fmt)
# define WARN_CALL rb_compile_warn
# define WARNING_ARGS(fmt,n) WARN_ARGS(fmt,n)
# define WARNING_ARGS_L(l,fmt,n) WARN_ARGS_L(l,fmt,n)
# define WARNING_CALL rb_compile_warning
# define rb_compile_error rb_compile_error_str
# define compile_error (parser->error_p = 1),rb_compile_error_str
# define PARSER_ARG ruby_sourcefile_string, ruby_sourceline, (void *)current_enc,
#endif

/* Older versions of Yacc set YYMAXDEPTH to a very low value by default (150,
   for instance).  This is too low for Ruby to parse some files, such as
   date/format.rb, therefore bump the value up to at least Bison's default. */
#ifdef OLD_YACC
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif
#endif

static void token_info_push(struct parser_params*, const char *token, size_t len);
static void token_info_pop(struct parser_params*, const char *token, size_t len);
#define token_info_push(token) token_info_push(parser, (token), rb_strlen_lit(token))
#define token_info_pop(token) token_info_pop(parser, (token), rb_strlen_lit(token))


/* Line 268 of yacc.c  */
#line 843 "parse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END_OF_INPUT = 0,
     keyword_class = 258,
     keyword_module = 259,
     keyword_def = 260,
     keyword_undef = 261,
     keyword_begin = 262,
     keyword_rescue = 263,
     keyword_ensure = 264,
     keyword_end = 265,
     keyword_if = 266,
     keyword_unless = 267,
     keyword_then = 268,
     keyword_elsif = 269,
     keyword_else = 270,
     keyword_case = 271,
     keyword_when = 272,
     keyword_while = 273,
     keyword_until = 274,
     keyword_for = 275,
     keyword_break = 276,
     keyword_next = 277,
     keyword_redo = 278,
     keyword_retry = 279,
     keyword_in = 280,
     keyword_do = 281,
     keyword_do_cond = 282,
     keyword_do_block = 283,
     keyword_do_LAMBDA = 284,
     keyword_return = 285,
     keyword_yield = 286,
     keyword_super = 287,
     keyword_self = 288,
     keyword_nil = 289,
     keyword_true = 290,
     keyword_false = 291,
     keyword_and = 292,
     keyword_or = 293,
     keyword_not = 294,
     modifier_if = 295,
     modifier_unless = 296,
     modifier_while = 297,
     modifier_until = 298,
     modifier_rescue = 299,
     keyword_alias = 300,
     keyword_defined = 301,
     keyword_BEGIN = 302,
     keyword_END = 303,
     keyword__LINE__ = 304,
     keyword__FILE__ = 305,
     keyword__ENCODING__ = 306,
     tIDENTIFIER = 307,
     tFID = 308,
     tGVAR = 309,
     tIVAR = 310,
     tCONSTANT = 311,
     tCVAR = 312,
     tLABEL = 313,
     tINTEGER = 314,
     tFLOAT = 315,
     tRATIONAL = 316,
     tIMAGINARY = 317,
     tSTRING_CONTENT = 318,
     tCHAR = 319,
     tNTH_REF = 320,
     tBACK_REF = 321,
     tREGEXP_END = 322,
     tUPLUS = 130,
     tUMINUS = 131,
     tPOW = 132,
     tCMP = 134,
     tEQ = 139,
     tEQQ = 140,
     tNEQ = 141,
     tGEQ = 138,
     tLEQ = 137,
     tANDOP = 148,
     tOROP = 149,
     tMATCH = 142,
     tNMATCH = 143,
     tDOT2 = 128,
     tDOT3 = 129,
     tAREF = 144,
     tASET = 145,
     tLSHFT = 135,
     tRSHFT = 136,
     tANDDOT = 150,
     tCOLON2 = 323,
     tCOLON3 = 324,
     tOP_ASGN = 325,
     tASSOC = 326,
     tLPAREN = 327,
     tLPAREN_ARG = 328,
     tRPAREN = 329,
     tLBRACK = 330,
     tLBRACE = 331,
     tLBRACE_ARG = 332,
     tSTAR = 333,
     tDSTAR = 334,
     tAMPER = 335,
     tLAMBDA = 336,
     tSYMBEG = 337,
     tSTRING_BEG = 338,
     tXSTRING_BEG = 339,
     tREGEXP_BEG = 340,
     tWORDS_BEG = 341,
     tQWORDS_BEG = 342,
     tSYMBOLS_BEG = 343,
     tQSYMBOLS_BEG = 344,
     tSTRING_DBEG = 345,
     tSTRING_DEND = 346,
     tSTRING_DVAR = 347,
     tSTRING_END = 348,
     tLAMBEG = 349,
     tLABEL_END = 350,
     tLOWEST = 351,
     tUMINUS_NUM = 352,
     tLAST_TOKEN = 353
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 787 "parse.y"

    VALUE val;
    NODE *node;
    ID id;
    int num;
    const struct vtable *vars;



/* Line 293 of yacc.c  */
#line 1008 "parse.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 1020 "parse.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   11129

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  146
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  209
/* YYNRULES -- Number of rules.  */
#define YYNRULES  634
/* YYNRULES -- Number of states.  */
#define YYNSTATES  1068

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     145,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,   143,   131,     2,     2,     2,   129,   124,     2,
     139,   140,   127,   125,   137,   126,   144,   128,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   119,   142,
     121,   117,   120,   118,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   136,     2,   141,   123,     2,   138,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   134,   122,   135,   132,     2,    81,    82,
      68,    69,    70,     2,    71,    85,    86,    76,    75,    72,
      73,    74,    79,    80,    83,    84,     2,     2,    77,    78,
      87,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   130,   133
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    18,    21,
      23,    24,    30,    35,    38,    40,    42,    46,    49,    51,
      52,    58,    59,    64,    68,    72,    76,    79,    83,    87,
      91,    95,    99,   104,   106,   110,   114,   121,   127,   133,
     139,   145,   149,   153,   157,   159,   163,   167,   169,   173,
     177,   181,   184,   186,   188,   190,   192,   194,   199,   200,
     206,   208,   211,   215,   220,   226,   231,   237,   240,   243,
     246,   249,   252,   254,   258,   260,   264,   266,   269,   273,
     279,   282,   287,   290,   295,   297,   301,   303,   307,   310,
     314,   316,   320,   322,   324,   329,   333,   337,   341,   345,
     348,   350,   352,   354,   359,   363,   367,   371,   375,   378,
     380,   382,   384,   387,   389,   393,   395,   397,   399,   401,
     403,   405,   407,   409,   411,   413,   414,   419,   421,   423,
     425,   427,   429,   431,   433,   435,   437,   439,   441,   443,
     445,   447,   449,   451,   453,   455,   457,   459,   461,   463,
     465,   467,   469,   471,   473,   475,   477,   479,   481,   483,
     485,   487,   489,   491,   493,   495,   497,   499,   501,   503,
     505,   507,   509,   511,   513,   515,   517,   519,   521,   523,
     525,   527,   529,   531,   533,   535,   537,   539,   541,   543,
     545,   547,   549,   551,   553,   555,   557,   559,   561,   565,
     571,   575,   581,   588,   594,   600,   606,   612,   617,   621,
     625,   629,   633,   637,   641,   645,   649,   653,   658,   661,
     664,   668,   672,   676,   680,   684,   688,   692,   696,   700,
     704,   708,   712,   716,   719,   722,   726,   730,   734,   738,
     739,   744,   751,   753,   755,   757,   760,   765,   768,   772,
     774,   776,   778,   780,   783,   788,   791,   793,   796,   799,
     804,   806,   807,   810,   813,   816,   818,   820,   823,   827,
     832,   834,   836,   840,   845,   848,   850,   852,   854,   856,
     858,   860,   862,   864,   866,   868,   870,   871,   876,   877,
     881,   882,   883,   889,   893,   897,   900,   904,   908,   910,
     915,   919,   921,   922,   929,   934,   938,   941,   943,   946,
     949,   956,   963,   964,   965,   973,   974,   975,   983,   989,
     994,   995,   996,  1006,  1007,  1014,  1015,  1023,  1024,  1030,
    1031,  1032,  1040,  1041,  1042,  1052,  1054,  1056,  1058,  1060,
    1062,  1064,  1066,  1068,  1070,  1072,  1074,  1076,  1078,  1080,
    1082,  1084,  1086,  1088,  1091,  1093,  1095,  1097,  1103,  1105,
    1108,  1110,  1112,  1114,  1118,  1120,  1124,  1126,  1131,  1138,
    1142,  1148,  1151,  1156,  1158,  1162,  1167,  1170,  1173,  1175,
    1178,  1179,  1186,  1195,  1200,  1207,  1212,  1215,  1222,  1225,
    1230,  1237,  1240,  1245,  1248,  1253,  1255,  1257,  1259,  1263,
    1265,  1270,  1272,  1277,  1279,  1283,  1285,  1287,  1288,  1289,
    1290,  1291,  1298,  1303,  1305,  1309,  1313,  1314,  1320,  1323,
    1328,  1334,  1340,  1343,  1344,  1350,  1351,  1357,  1361,  1362,
    1367,  1368,  1373,  1376,  1378,  1383,  1384,  1390,  1391,  1397,
    1403,  1405,  1407,  1414,  1416,  1418,  1420,  1422,  1425,  1427,
    1430,  1432,  1434,  1436,  1438,  1440,  1442,  1444,  1447,  1451,
    1455,  1459,  1463,  1467,  1468,  1472,  1474,  1477,  1481,  1485,
    1486,  1490,  1494,  1498,  1502,  1506,  1507,  1511,  1512,  1516,
    1517,  1520,  1521,  1524,  1525,  1528,  1530,  1531,  1535,  1536,
    1537,  1538,  1539,  1540,  1549,  1551,  1553,  1555,  1557,  1560,
    1562,  1564,  1566,  1568,  1572,  1574,  1577,  1579,  1581,  1583,
    1585,  1587,  1589,  1591,  1593,  1595,  1597,  1599,  1601,  1603,
    1605,  1607,  1609,  1611,  1613,  1615,  1617,  1619,  1621,  1622,
    1627,  1628,  1632,  1633,  1637,  1642,  1645,  1648,  1650,  1653,
    1654,  1661,  1670,  1675,  1682,  1687,  1694,  1697,  1702,  1709,
    1712,  1717,  1720,  1725,  1727,  1728,  1730,  1732,  1734,  1736,
    1738,  1740,  1742,  1744,  1748,  1750,  1754,  1756,  1759,  1761,
    1764,  1766,  1768,  1772,  1774,  1778,  1780,  1782,  1785,  1787,
    1791,  1795,  1797,  1801,  1803,  1807,  1809,  1811,  1814,  1816,
    1818,  1820,  1823,  1826,  1828,  1830,  1831,  1836,  1838,  1841,
    1843,  1847,  1851,  1854,  1859,  1862,  1864,  1866,  1868,  1870,
    1872,  1874,  1876,  1878,  1880,  1882,  1884,  1886,  1888,  1890,
    1892,  1894,  1895,  1897,  1898,  1900,  1903,  1906,  1907,  1909,
    1911,  1913,  1915,  1917,  1920
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     147,     0,    -1,    -1,   148,   149,    -1,   150,   347,    -1,
     354,    -1,   151,    -1,   150,   353,   151,    -1,     1,   151,
      -1,   158,    -1,    -1,    47,   152,   134,   149,   135,    -1,
     154,   268,   235,   271,    -1,   155,   347,    -1,   354,    -1,
     156,    -1,   155,   353,   156,    -1,     1,   158,    -1,   158,
      -1,    -1,    47,   157,   134,   149,   135,    -1,    -1,    45,
     181,   159,   181,    -1,    45,    54,    54,    -1,    45,    54,
      66,    -1,    45,    54,    65,    -1,     6,   182,    -1,   158,
      40,   162,    -1,   158,    41,   162,    -1,   158,    42,   162,
      -1,   158,    43,   162,    -1,   158,    44,   158,    -1,    48,
     134,   154,   135,    -1,   160,    -1,   169,   117,   163,    -1,
     306,    90,   163,    -1,   220,   136,   192,   350,    90,   163,
      -1,   220,   345,    52,    90,   163,    -1,   220,   345,    56,
      90,   163,    -1,   220,    88,    56,    90,   163,    -1,   220,
      88,    52,    90,   163,    -1,   307,    90,   163,    -1,   176,
     117,   200,    -1,   169,   117,   199,    -1,   161,    -1,   176,
     117,   163,    -1,   176,   117,   160,    -1,   163,    -1,   161,
      37,   161,    -1,   161,    38,   161,    -1,    39,   348,   161,
      -1,   131,   163,    -1,   186,    -1,   161,    -1,   168,    -1,
     164,    -1,   257,    -1,   257,   346,   342,   194,    -1,    -1,
      97,   166,   243,   154,   135,    -1,   341,    -1,   167,   194,
      -1,   167,   194,   165,    -1,   220,   345,   342,   194,    -1,
     220,   345,   342,   194,   165,    -1,   220,    88,   342,   194,
      -1,   220,    88,   342,   194,   165,    -1,    32,   194,    -1,
      31,   194,    -1,    30,   193,    -1,    21,   193,    -1,    22,
     193,    -1,   171,    -1,    92,   170,   349,    -1,   171,    -1,
      92,   170,   349,    -1,   173,    -1,   173,   172,    -1,   173,
      98,   175,    -1,   173,    98,   175,   137,   174,    -1,   173,
      98,    -1,   173,    98,   137,   174,    -1,    98,   175,    -1,
      98,   175,   137,   174,    -1,    98,    -1,    98,   137,   174,
      -1,   175,    -1,    92,   170,   349,    -1,   172,   137,    -1,
     173,   172,   137,    -1,   172,    -1,   174,   137,   172,    -1,
     303,    -1,   304,    -1,   220,   136,   192,   350,    -1,   220,
     345,    52,    -1,   220,    88,    52,    -1,   220,   345,    56,
      -1,   220,    88,    56,    -1,    89,    56,    -1,   307,    -1,
     303,    -1,   304,    -1,   220,   136,   192,   350,    -1,   220,
     345,    52,    -1,   220,    88,    52,    -1,   220,   345,    56,
      -1,   220,    88,    56,    -1,    89,    56,    -1,   307,    -1,
      52,    -1,    56,    -1,    89,   177,    -1,   177,    -1,   220,
      88,   177,    -1,    52,    -1,    56,    -1,    53,    -1,   184,
      -1,   185,    -1,   179,    -1,   298,    -1,   180,    -1,   300,
      -1,   181,    -1,    -1,   182,   137,   183,   181,    -1,   122,
      -1,   123,    -1,   124,    -1,    71,    -1,    72,    -1,    73,
      -1,    79,    -1,    80,    -1,   120,    -1,    75,    -1,   121,
      -1,    76,    -1,    74,    -1,    85,    -1,    86,    -1,   125,
      -1,   126,    -1,   127,    -1,    98,    -1,   128,    -1,   129,
      -1,    70,    -1,    99,    -1,   131,    -1,   132,    -1,    68,
      -1,    69,    -1,    83,    -1,    84,    -1,   138,    -1,    49,
      -1,    50,    -1,    51,    -1,    47,    -1,    48,    -1,    45,
      -1,    37,    -1,     7,    -1,    21,    -1,    16,    -1,     3,
      -1,     5,    -1,    46,    -1,    26,    -1,    15,    -1,    14,
      -1,    10,    -1,     9,    -1,    36,    -1,    20,    -1,    25,
      -1,     4,    -1,    22,    -1,    34,    -1,    39,    -1,    38,
      -1,    23,    -1,     8,    -1,    24,    -1,    30,    -1,    33,
      -1,    32,    -1,    13,    -1,    35,    -1,     6,    -1,    17,
      -1,    31,    -1,    11,    -1,    12,    -1,    18,    -1,    19,
      -1,   176,   117,   186,    -1,   176,   117,   186,    44,   186,
      -1,   306,    90,   186,    -1,   306,    90,   186,    44,   186,
      -1,   220,   136,   192,   350,    90,   186,    -1,   220,   345,
      52,    90,   186,    -1,   220,   345,    56,    90,   186,    -1,
     220,    88,    52,    90,   186,    -1,   220,    88,    56,    90,
     186,    -1,    89,    56,    90,   186,    -1,   307,    90,   186,
      -1,   186,    81,   186,    -1,   186,    82,   186,    -1,   186,
     125,   186,    -1,   186,   126,   186,    -1,   186,   127,   186,
      -1,   186,   128,   186,    -1,   186,   129,   186,    -1,   186,
      70,   186,    -1,   130,   302,    70,   186,    -1,    68,   186,
      -1,    69,   186,    -1,   186,   122,   186,    -1,   186,   123,
     186,    -1,   186,   124,   186,    -1,   186,    71,   186,    -1,
     186,   120,   186,    -1,   186,    75,   186,    -1,   186,   121,
     186,    -1,   186,    76,   186,    -1,   186,    72,   186,    -1,
     186,    73,   186,    -1,   186,    74,   186,    -1,   186,    79,
     186,    -1,   186,    80,   186,    -1,   131,   186,    -1,   132,
     186,    -1,   186,    85,   186,    -1,   186,    86,   186,    -1,
     186,    77,   186,    -1,   186,    78,   186,    -1,    -1,    46,
     348,   187,   186,    -1,   186,   118,   186,   348,   119,   186,
      -1,   201,    -1,   186,    -1,   354,    -1,   198,   351,    -1,
     198,   137,   339,   351,    -1,   339,   351,    -1,   139,   192,
     349,    -1,   354,    -1,   190,    -1,   354,    -1,   193,    -1,
     198,   137,    -1,   198,   137,   339,   137,    -1,   339,   137,
      -1,   168,    -1,   198,   197,    -1,   339,   197,    -1,   198,
     137,   339,   197,    -1,   196,    -1,    -1,   195,   193,    -1,
     100,   188,    -1,   137,   196,    -1,   354,    -1,   188,    -1,
      98,   188,    -1,   198,   137,   188,    -1,   198,   137,    98,
     188,    -1,   200,    -1,   188,    -1,   198,   137,   188,    -1,
     198,   137,    98,   188,    -1,    98,   188,    -1,   272,    -1,
     273,    -1,   276,    -1,   277,    -1,   278,    -1,   283,    -1,
     281,    -1,   284,    -1,   305,    -1,   307,    -1,    53,    -1,
      -1,   221,   202,   153,   231,    -1,    -1,    93,   203,   349,
      -1,    -1,    -1,    93,   204,   161,   205,   349,    -1,    92,
     154,   140,    -1,   220,    88,    56,    -1,    89,    56,    -1,
      95,   189,   141,    -1,    96,   338,   135,    -1,    30,    -1,
      31,   139,   193,   349,    -1,    31,   139,   349,    -1,    31,
      -1,    -1,    46,   348,   139,   206,   161,   349,    -1,    39,
     139,   161,   349,    -1,    39,   139,   349,    -1,   167,   263,
      -1,   258,    -1,   258,   263,    -1,   101,   248,    -1,   222,
     162,   232,   154,   234,   231,    -1,   223,   162,   232,   154,
     235,   231,    -1,    -1,    -1,   224,   207,   162,   233,   208,
     154,   231,    -1,    -1,    -1,   225,   209,   162,   233,   210,
     154,   231,    -1,   226,   162,   347,   266,   231,    -1,   226,
     347,   266,   231,    -1,    -1,    -1,   227,   236,    25,   211,
     162,   233,   212,   154,   231,    -1,    -1,   228,   178,   308,
     213,   153,   231,    -1,    -1,   228,    85,   161,   214,   352,
     153,   231,    -1,    -1,   229,   178,   215,   153,   231,    -1,
      -1,    -1,   230,   179,   216,   217,   310,   153,   231,    -1,
      -1,    -1,   230,   336,   344,   218,   179,   219,   310,   153,
     231,    -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1,
     201,    -1,     7,    -1,    11,    -1,    12,    -1,    18,    -1,
      19,    -1,    16,    -1,    20,    -1,     3,    -1,     4,    -1,
       5,    -1,    10,    -1,   352,    -1,    13,    -1,   352,    13,
      -1,   352,    -1,    27,    -1,   235,    -1,    14,   162,   232,
     154,   234,    -1,   354,    -1,    15,   154,    -1,   176,    -1,
     169,    -1,   316,    -1,    92,   239,   349,    -1,   237,    -1,
     238,   137,   237,    -1,   238,    -1,   238,   137,    98,   316,
      -1,   238,   137,    98,   316,   137,   238,    -1,   238,   137,
      98,    -1,   238,   137,    98,   137,   238,    -1,    98,   316,
      -1,    98,   316,   137,   238,    -1,    98,    -1,    98,   137,
     238,    -1,   323,   137,   326,   335,    -1,   323,   335,    -1,
     326,   335,    -1,   334,    -1,   137,   240,    -1,    -1,   319,
     137,   329,   137,   332,   241,    -1,   319,   137,   329,   137,
     332,   137,   319,   241,    -1,   319,   137,   329,   241,    -1,
     319,   137,   329,   137,   319,   241,    -1,   319,   137,   332,
     241,    -1,   319,   137,    -1,   319,   137,   332,   137,   319,
     241,    -1,   319,   241,    -1,   329,   137,   332,   241,    -1,
     329,   137,   332,   137,   319,   241,    -1,   329,   241,    -1,
     329,   137,   319,   241,    -1,   332,   241,    -1,   332,   137,
     319,   241,    -1,   240,    -1,   354,    -1,   244,    -1,   122,
     245,   122,    -1,    78,    -1,   122,   242,   245,   122,    -1,
     348,    -1,   348,   142,   246,   348,    -1,   247,    -1,   246,
     137,   247,    -1,    52,    -1,   315,    -1,    -1,    -1,    -1,
      -1,   249,   250,   253,   251,   252,   254,    -1,   139,   314,
     245,   140,    -1,   314,    -1,   114,   154,   135,    -1,    29,
     154,    10,    -1,    -1,    28,   256,   243,   154,    10,    -1,
     168,   255,    -1,   257,   346,   342,   191,    -1,   257,   346,
     342,   191,   263,    -1,   257,   346,   342,   194,   255,    -1,
     167,   190,    -1,    -1,   220,   345,   342,   259,   191,    -1,
      -1,   220,    88,   342,   260,   190,    -1,   220,    88,   343,
      -1,    -1,   220,   345,   261,   190,    -1,    -1,   220,    88,
     262,   190,    -1,    32,   190,    -1,    32,    -1,   220,   136,
     192,   350,    -1,    -1,   134,   264,   243,   154,   135,    -1,
      -1,    26,   265,   243,   154,    10,    -1,    17,   198,   232,
     154,   267,    -1,   235,    -1,   266,    -1,     8,   269,   270,
     232,   154,   268,    -1,   354,    -1,   188,    -1,   200,    -1,
     354,    -1,    91,   176,    -1,   354,    -1,     9,   154,    -1,
     354,    -1,   301,    -1,   298,    -1,   300,    -1,   274,    -1,
      64,    -1,   275,    -1,   274,   275,    -1,   103,   287,   113,
      -1,   104,   288,   113,    -1,   105,   289,    67,    -1,   106,
     143,   113,    -1,   106,   279,   113,    -1,    -1,   279,   280,
     143,    -1,   290,    -1,   280,   290,    -1,   108,   143,   113,
      -1,   108,   282,   113,    -1,    -1,   282,   280,   143,    -1,
     107,   143,   113,    -1,   107,   285,   113,    -1,   109,   143,
     113,    -1,   109,   286,   113,    -1,    -1,   285,    63,   143,
      -1,    -1,   286,    63,   143,    -1,    -1,   287,   290,    -1,
      -1,   288,   290,    -1,    -1,   289,   290,    -1,    63,    -1,
      -1,   112,   291,   297,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   292,   293,   294,   295,   296,   154,   111,    -1,    54,
      -1,    55,    -1,    57,    -1,   307,    -1,   102,   299,    -1,
     179,    -1,    55,    -1,    54,    -1,    57,    -1,   102,   288,
     113,    -1,   302,    -1,   130,   302,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    52,    -1,    55,    -1,    54,
      -1,    56,    -1,    57,    -1,    34,    -1,    33,    -1,    35,
      -1,    36,    -1,    50,    -1,    49,    -1,    51,    -1,   303,
      -1,   304,    -1,   303,    -1,   304,    -1,    65,    -1,    66,
      -1,    -1,   121,   309,   162,   352,    -1,    -1,   139,   314,
     349,    -1,    -1,   311,   314,   352,    -1,   324,   137,   326,
     335,    -1,   324,   335,    -1,   326,   335,    -1,   334,    -1,
     137,   312,    -1,    -1,   319,   137,   330,   137,   332,   313,
      -1,   319,   137,   330,   137,   332,   137,   319,   313,    -1,
     319,   137,   330,   313,    -1,   319,   137,   330,   137,   319,
     313,    -1,   319,   137,   332,   313,    -1,   319,   137,   332,
     137,   319,   313,    -1,   319,   313,    -1,   330,   137,   332,
     313,    -1,   330,   137,   332,   137,   319,   313,    -1,   330,
     313,    -1,   330,   137,   319,   313,    -1,   332,   313,    -1,
     332,   137,   319,   313,    -1,   312,    -1,    -1,    56,    -1,
      55,    -1,    54,    -1,    57,    -1,   315,    -1,    52,    -1,
     316,    -1,   317,    -1,    92,   239,   349,    -1,   318,    -1,
     319,   137,   318,    -1,    58,    -1,   320,   188,    -1,   320,
      -1,   320,   220,    -1,   320,    -1,   322,    -1,   323,   137,
     322,    -1,   321,    -1,   324,   137,   321,    -1,    70,    -1,
      99,    -1,   325,    52,    -1,   325,    -1,   317,   117,   188,
      -1,   317,   117,   220,    -1,   328,    -1,   329,   137,   328,
      -1,   327,    -1,   330,   137,   327,    -1,   127,    -1,    98,
      -1,   331,    52,    -1,   331,    -1,   124,    -1,   100,    -1,
     333,    52,    -1,   137,   334,    -1,   354,    -1,   305,    -1,
      -1,   139,   337,   161,   349,    -1,   354,    -1,   339,   351,
      -1,   340,    -1,   339,   137,   340,    -1,   188,    91,   188,
      -1,    58,   188,    -1,   103,   287,   115,   188,    -1,    99,
     188,    -1,    52,    -1,    56,    -1,    53,    -1,    52,    -1,
      56,    -1,    53,    -1,   184,    -1,    52,    -1,    53,    -1,
     184,    -1,   144,    -1,    88,    -1,   144,    -1,    87,    -1,
     345,    -1,    88,    -1,    -1,   353,    -1,    -1,   145,    -1,
     348,   140,    -1,   348,   141,    -1,    -1,   145,    -1,   137,
      -1,   142,    -1,   145,    -1,   352,    -1,   353,   142,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   952,   952,   952,   983,   994,  1003,  1011,  1019,  1025,
    1027,  1026,  1047,  1080,  1091,  1100,  1108,  1116,  1122,  1127,
    1126,  1147,  1147,  1155,  1163,  1174,  1185,  1193,  1202,  1211,
    1224,  1237,  1246,  1258,  1259,  1269,  1274,  1295,  1300,  1305,
    1315,  1320,  1331,  1340,  1349,  1352,  1361,  1373,  1374,  1382,
    1390,  1398,  1406,  1409,  1421,  1422,  1425,  1426,  1438,  1437,
    1459,  1469,  1478,  1491,  1500,  1512,  1521,  1533,  1542,  1551,
    1559,  1567,  1577,  1578,  1588,  1589,  1599,  1607,  1615,  1623,
    1632,  1640,  1649,  1657,  1666,  1674,  1685,  1686,  1696,  1704,
    1714,  1722,  1732,  1736,  1740,  1748,  1756,  1764,  1772,  1786,
    1800,  1813,  1822,  1831,  1839,  1847,  1855,  1863,  1877,  1891,
    1903,  1912,  1915,  1923,  1931,  1941,  1942,  1943,  1944,  1949,
    1960,  1961,  1964,  1972,  1975,  1983,  1983,  1993,  1994,  1995,
    1996,  1997,  1998,  1999,  2000,  2001,  2002,  2003,  2004,  2005,
    2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,  2014,  2015,
    2016,  2017,  2018,  2019,  2020,  2021,  2022,  2025,  2025,  2025,
    2026,  2026,  2027,  2027,  2027,  2028,  2028,  2028,  2028,  2029,
    2029,  2029,  2029,  2030,  2030,  2030,  2031,  2031,  2031,  2031,
    2032,  2032,  2032,  2032,  2033,  2033,  2033,  2033,  2034,  2034,
    2034,  2034,  2035,  2035,  2035,  2035,  2036,  2036,  2039,  2048,
    2058,  2063,  2073,  2099,  2104,  2109,  2114,  2124,  2134,  2146,
    2160,  2174,  2182,  2190,  2198,  2206,  2214,  2222,  2231,  2239,
    2247,  2255,  2263,  2271,  2279,  2287,  2295,  2303,  2311,  2319,
    2327,  2335,  2346,  2354,  2362,  2370,  2378,  2386,  2394,  2402,
    2402,  2411,  2421,  2427,  2439,  2440,  2444,  2452,  2462,  2472,
    2473,  2476,  2477,  2478,  2482,  2490,  2500,  2509,  2517,  2527,
    2536,  2545,  2545,  2557,  2567,  2571,  2577,  2585,  2593,  2607,
    2623,  2624,  2627,  2641,  2656,  2666,  2667,  2668,  2669,  2670,
    2671,  2672,  2673,  2674,  2675,  2676,  2685,  2684,  2710,  2710,
    2719,  2723,  2718,  2732,  2740,  2748,  2756,  2769,  2777,  2785,
    2793,  2801,  2809,  2809,  2818,  2826,  2834,  2844,  2845,  2855,
    2859,  2871,  2883,  2883,  2883,  2894,  2894,  2894,  2905,  2916,
    2925,  2927,  2924,  2973,  2972,  2995,  2994,  3017,  3016,  3039,
    3044,  3038,  3065,  3066,  3065,  3091,  3099,  3107,  3115,  3125,
    3137,  3143,  3149,  3155,  3161,  3167,  3173,  3179,  3185,  3191,
    3201,  3207,  3212,  3213,  3220,  3225,  3228,  3229,  3242,  3243,
    3253,  3254,  3257,  3265,  3275,  3283,  3293,  3301,  3310,  3319,
    3327,  3335,  3344,  3356,  3364,  3375,  3379,  3383,  3387,  3393,
    3398,  3403,  3407,  3411,  3415,  3419,  3423,  3431,  3435,  3439,
    3443,  3447,  3451,  3455,  3459,  3463,  3469,  3470,  3476,  3486,
    3495,  3507,  3511,  3521,  3528,  3537,  3545,  3551,  3554,  3559,
    3562,  3551,  3581,  3589,  3595,  3599,  3606,  3605,  3626,  3642,
    3651,  3663,  3677,  3687,  3686,  3703,  3702,  3718,  3727,  3726,
    3743,  3742,  3759,  3767,  3775,  3790,  3789,  3809,  3808,  3829,
    3841,  3842,  3845,  3864,  3867,  3875,  3883,  3886,  3890,  3893,
    3901,  3904,  3905,  3913,  3916,  3933,  3934,  3935,  3945,  3957,
    3989,  4067,  4076,  4087,  4094,  4104,  4112,  4122,  4131,  4142,
    4149,  4167,  4176,  4186,  4195,  4206,  4213,  4224,  4231,  4246,
    4253,  4264,  4271,  4282,  4289,  4330,  4332,  4331,  4347,  4353,
    4357,  4361,  4365,  4346,  4387,  4395,  4403,  4411,  4414,  4425,
    4426,  4427,  4428,  4431,  4442,  4443,  4454,  4455,  4456,  4457,
    4460,  4461,  4462,  4463,  4464,  4467,  4468,  4469,  4470,  4471,
    4472,  4473,  4476,  4489,  4499,  4507,  4517,  4518,  4522,  4521,
    4531,  4540,  4550,  4550,  4564,  4568,  4572,  4576,  4582,  4587,
    4592,  4596,  4600,  4604,  4608,  4612,  4616,  4620,  4624,  4628,
    4632,  4636,  4640,  4644,  4649,  4655,  4665,  4675,  4685,  4697,
    4698,  4705,  4714,  4723,  4742,  4749,  4763,  4772,  4782,  4794,
    4803,  4814,  4822,  4833,  4841,  4851,  4852,  4855,  4860,  4867,
    4879,  4891,  4899,  4915,  4923,  4939,  4940,  4943,  4956,  4967,
    4968,  4971,  4988,  4992,  5002,  5012,  5012,  5041,  5042,  5052,
    5059,  5083,  5095,  5103,  5111,  5125,  5126,  5127,  5130,  5131,
    5132,  5133,  5136,  5137,  5138,  5141,  5146,  5153,  5161,  5171,
    5172,  5182,  5183,  5186,  5187,  5190,  5193,  5196,  5197,  5198,
    5201,  5202,  5205,  5206,  5210
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end-of-input\"", "error", "$undefined", "keyword_class",
  "keyword_module", "keyword_def", "keyword_undef", "keyword_begin",
  "keyword_rescue", "keyword_ensure", "keyword_end", "keyword_if",
  "keyword_unless", "keyword_then", "keyword_elsif", "keyword_else",
  "keyword_case", "keyword_when", "keyword_while", "keyword_until",
  "keyword_for", "keyword_break", "keyword_next", "keyword_redo",
  "keyword_retry", "keyword_in", "keyword_do", "keyword_do_cond",
  "keyword_do_block", "keyword_do_LAMBDA", "keyword_return",
  "keyword_yield", "keyword_super", "keyword_self", "keyword_nil",
  "keyword_true", "keyword_false", "keyword_and", "keyword_or",
  "keyword_not", "modifier_if", "modifier_unless", "modifier_while",
  "modifier_until", "modifier_rescue", "keyword_alias", "keyword_defined",
  "keyword_BEGIN", "keyword_END", "keyword__LINE__", "keyword__FILE__",
  "keyword__ENCODING__", "tIDENTIFIER", "tFID", "tGVAR", "tIVAR",
  "tCONSTANT", "tCVAR", "tLABEL", "tINTEGER", "tFLOAT", "tRATIONAL",
  "tIMAGINARY", "tSTRING_CONTENT", "tCHAR", "tNTH_REF", "tBACK_REF",
  "tREGEXP_END", "\"unary+\"", "\"unary-\"", "\"**\"", "\"<=>\"", "\"==\"",
  "\"===\"", "\"!=\"", "\">=\"", "\"<=\"", "\"&&\"", "\"||\"", "\"=~\"",
  "\"!~\"", "\"..\"", "\"...\"", "\"[]\"", "\"[]=\"", "\"<<\"", "\">>\"",
  "\"&.\"", "\"::\"", "\":: at EXPR_BEG\"", "tOP_ASGN", "\"=>\"", "\"(\"",
  "\"( arg\"", "\")\"", "\"[\"", "\"{\"", "\"{ arg\"", "\"*\"",
  "\"**arg\"", "\"&\"", "\"->\"", "tSYMBEG", "tSTRING_BEG", "tXSTRING_BEG",
  "tREGEXP_BEG", "tWORDS_BEG", "tQWORDS_BEG", "tSYMBOLS_BEG",
  "tQSYMBOLS_BEG", "tSTRING_DBEG", "tSTRING_DEND", "tSTRING_DVAR",
  "tSTRING_END", "tLAMBEG", "tLABEL_END", "tLOWEST", "'='", "'?'", "':'",
  "'>'", "'<'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "tUMINUS_NUM", "'!'", "'~'", "tLAST_TOKEN", "'{'", "'}'", "'['", "','",
  "'`'", "'('", "')'", "']'", "';'", "' '", "'.'", "'\\n'", "$accept",
  "program", "$@1", "top_compstmt", "top_stmts", "top_stmt", "$@2",
  "bodystmt", "compstmt", "stmts", "stmt_or_begin", "$@3", "stmt", "$@4",
  "command_asgn", "expr", "expr_value", "command_call", "block_command",
  "cmd_brace_block", "@5", "fcall", "command", "mlhs", "mlhs_inner",
  "mlhs_basic", "mlhs_item", "mlhs_head", "mlhs_post", "mlhs_node", "lhs",
  "cname", "cpath", "fname", "fsym", "fitem", "undef_list", "$@6", "op",
  "reswords", "arg", "$@7", "arg_value", "aref_args", "paren_args",
  "opt_paren_args", "opt_call_args", "call_args", "command_args", "@8",
  "block_arg", "opt_block_arg", "args", "mrhs_arg", "mrhs", "primary",
  "@9", "$@10", "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17",
  "$@18", "$@19", "@20", "@21", "@22", "@23", "@24", "@25", "@26",
  "primary_value", "k_begin", "k_if", "k_unless", "k_while", "k_until",
  "k_case", "k_for", "k_class", "k_module", "k_def", "k_end", "then", "do",
  "if_tail", "opt_else", "for_var", "f_marg", "f_marg_list", "f_margs",
  "block_args_tail", "opt_block_args_tail", "block_param",
  "opt_block_param", "block_param_def", "opt_bv_decl", "bv_decls", "bvar",
  "lambda", "@27", "@28", "@29", "@30", "f_larglist", "lambda_body",
  "do_block", "@31", "block_call", "method_call", "@32", "@33", "@34",
  "@35", "brace_block", "@36", "@37", "case_body", "cases", "opt_rescue",
  "exc_list", "exc_var", "opt_ensure", "literal", "strings", "string",
  "string1", "xstring", "regexp", "words", "word_list", "word", "symbols",
  "symbol_list", "qwords", "qsymbols", "qword_list", "qsym_list",
  "string_contents", "xstring_contents", "regexp_contents",
  "string_content", "@38", "@39", "@40", "@41", "@42", "@43",
  "string_dvar", "symbol", "sym", "dsym", "numeric", "simple_numeric",
  "user_variable", "keyword_variable", "var_ref", "var_lhs", "backref",
  "superclass", "$@44", "f_arglist", "@45", "args_tail", "opt_args_tail",
  "f_args", "f_bad_arg", "f_norm_arg", "f_arg_asgn", "f_arg_item", "f_arg",
  "f_label", "f_kw", "f_block_kw", "f_block_kwarg", "f_kwarg",
  "kwrest_mark", "f_kwrest", "f_opt", "f_block_opt", "f_block_optarg",
  "f_optarg", "restarg_mark", "f_rest_arg", "blkarg_mark", "f_block_arg",
  "opt_f_block_arg", "singleton", "$@46", "assoc_list", "assocs", "assoc",
  "operation", "operation2", "operation3", "dot_or_colon", "call_op",
  "call_op2", "opt_terms", "opt_nl", "rparen", "rbracket", "trailer",
  "term", "terms", "none", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   130,   131,
     132,   134,   139,   140,   141,   138,   137,   148,   149,   142,
     143,   128,   129,   144,   145,   135,   136,   150,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,    61,    63,    58,
      62,    60,   124,    94,    38,    43,    45,    42,    47,    37,
     352,    33,   126,   353,   123,   125,    91,    44,    96,    40,
      41,    93,    59,    32,    46,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   146,   148,   147,   149,   150,   150,   150,   150,   151,
     152,   151,   153,   154,   155,   155,   155,   155,   156,   157,
     156,   159,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   160,   160,   161,   161,   161,
     161,   161,   161,   162,   163,   163,   164,   164,   166,   165,
     167,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     168,   168,   169,   169,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   171,   171,   172,   172,   173,   173,
     174,   174,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     177,   177,   178,   178,   178,   179,   179,   179,   179,   179,
     180,   180,   181,   181,   182,   183,   182,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   184,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   187,
     186,   186,   186,   188,   189,   189,   189,   189,   190,   191,
     191,   192,   192,   192,   192,   192,   193,   193,   193,   193,
     193,   195,   194,   196,   197,   197,   198,   198,   198,   198,
     199,   199,   200,   200,   200,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   202,   201,   203,   201,
     204,   205,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   206,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   207,   208,   201,   209,   210,   201,   201,   201,
     211,   212,   201,   213,   201,   214,   201,   215,   201,   216,
     217,   201,   218,   219,   201,   201,   201,   201,   201,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   232,   232,   232,   233,   233,   234,   234,   235,   235,
     236,   236,   237,   237,   238,   238,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   240,   240,   240,   240,   241,
     241,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   243,   243,   244,   244,
     244,   245,   245,   246,   246,   247,   247,   249,   250,   251,
     252,   248,   253,   253,   254,   254,   256,   255,   257,   257,
     257,   257,   258,   259,   258,   260,   258,   258,   261,   258,
     262,   258,   258,   258,   258,   264,   263,   265,   263,   266,
     267,   267,   268,   268,   269,   269,   269,   270,   270,   271,
     271,   272,   272,   272,   273,   274,   274,   274,   275,   276,
     277,   278,   278,   279,   279,   280,   280,   281,   281,   282,
     282,   283,   283,   284,   284,   285,   285,   286,   286,   287,
     287,   288,   288,   289,   289,   290,   291,   290,   292,   293,
     294,   295,   296,   290,   297,   297,   297,   297,   298,   299,
     299,   299,   299,   300,   301,   301,   302,   302,   302,   302,
     303,   303,   303,   303,   303,   304,   304,   304,   304,   304,
     304,   304,   305,   305,   306,   306,   307,   307,   309,   308,
     308,   310,   311,   310,   312,   312,   312,   312,   313,   313,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   315,   315,   315,   315,   316,
     316,   317,   318,   318,   319,   319,   320,   321,   321,   322,
     322,   323,   323,   324,   324,   325,   325,   326,   326,   327,
     328,   329,   329,   330,   330,   331,   331,   332,   332,   333,
     333,   334,   335,   335,   336,   337,   336,   338,   338,   339,
     339,   340,   340,   340,   340,   341,   341,   341,   342,   342,
     342,   342,   343,   343,   343,   344,   344,   345,   345,   346,
     346,   347,   347,   348,   348,   349,   350,   351,   351,   351,
     352,   352,   353,   353,   354
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     3,     2,     1,
       0,     5,     4,     2,     1,     1,     3,     2,     1,     0,
       5,     0,     4,     3,     3,     3,     2,     3,     3,     3,
       3,     3,     4,     1,     3,     3,     6,     5,     5,     5,
       5,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     2,     1,     1,     1,     1,     1,     4,     0,     5,
       1,     2,     3,     4,     5,     4,     5,     2,     2,     2,
       2,     2,     1,     3,     1,     3,     1,     2,     3,     5,
       2,     4,     2,     4,     1,     3,     1,     3,     2,     3,
       1,     3,     1,     1,     4,     3,     3,     3,     3,     2,
       1,     1,     1,     4,     3,     3,     3,     3,     2,     1,
       1,     1,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     5,
       3,     5,     6,     5,     5,     5,     5,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     3,     3,     3,     0,
       4,     6,     1,     1,     1,     2,     4,     2,     3,     1,
       1,     1,     1,     2,     4,     2,     1,     2,     2,     4,
       1,     0,     2,     2,     2,     1,     1,     2,     3,     4,
       1,     1,     3,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     3,
       0,     0,     5,     3,     3,     2,     3,     3,     1,     4,
       3,     1,     0,     6,     4,     3,     2,     1,     2,     2,
       6,     6,     0,     0,     7,     0,     0,     7,     5,     4,
       0,     0,     9,     0,     6,     0,     7,     0,     5,     0,
       0,     7,     0,     0,     9,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     5,     1,     2,
       1,     1,     1,     3,     1,     3,     1,     4,     6,     3,
       5,     2,     4,     1,     3,     4,     2,     2,     1,     2,
       0,     6,     8,     4,     6,     4,     2,     6,     2,     4,
       6,     2,     4,     2,     4,     1,     1,     1,     3,     1,
       4,     1,     4,     1,     3,     1,     1,     0,     0,     0,
       0,     6,     4,     1,     3,     3,     0,     5,     2,     4,
       5,     5,     2,     0,     5,     0,     5,     3,     0,     4,
       0,     4,     2,     1,     4,     0,     5,     0,     5,     5,
       1,     1,     6,     1,     1,     1,     1,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     3,
       3,     3,     3,     0,     3,     1,     2,     3,     3,     0,
       3,     3,     3,     3,     3,     0,     3,     0,     3,     0,
       2,     0,     2,     0,     2,     1,     0,     3,     0,     0,
       0,     0,     0,     8,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     3,     0,     3,     4,     2,     2,     1,     2,     0,
       6,     8,     4,     6,     4,     6,     2,     4,     6,     2,
       4,     2,     4,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     2,     1,     2,
       1,     1,     3,     1,     3,     1,     1,     2,     1,     3,
       3,     1,     3,     1,     3,     1,     1,     2,     1,     1,
       1,     2,     2,     1,     1,     0,     4,     1,     2,     1,
       3,     3,     2,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     1,     2,     2,     0,     1,     1,
       1,     1,     1,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       2,     0,     0,     1,     0,   347,   348,   349,     0,   340,
     341,   342,   345,   343,   344,   346,   335,   336,   337,   338,
     298,   261,   261,   516,   515,   517,   518,   623,     0,   623,
      10,     0,   520,   519,   521,   605,   607,   512,   511,   606,
     514,   506,   507,   508,   509,   455,   526,   527,     0,     0,
       0,     0,   290,   634,   634,    84,   407,   481,   479,   481,
     483,   463,   475,   469,   477,     0,     0,     0,     3,   621,
       6,     9,    33,    44,    47,    55,   261,    54,     0,    72,
       0,    76,    86,     0,    52,   242,     0,   286,     0,     0,
     312,   315,   621,     0,     0,     0,     0,    56,   307,   275,
     276,   454,   456,   277,   278,   279,   281,   280,   282,   452,
     453,   451,   504,   522,   523,   283,     0,   284,    60,     5,
       8,   167,   178,   168,   191,   164,   184,   174,   173,   194,
     195,   189,   172,   171,   166,   192,   196,   197,   176,   165,
     179,   183,   185,   177,   170,   186,   193,   188,   187,   180,
     190,   175,   163,   182,   181,   162,   169,   160,   161,   157,
     158,   159,   115,   117,   116,   152,   153,   148,   130,   131,
     132,   139,   136,   138,   133,   134,   154,   155,   140,   141,
     145,   149,   135,   137,   127,   128,   129,   142,   143,   144,
     146,   147,   150,   151,   156,   120,   122,   124,    26,   118,
     119,   121,   123,     0,     0,     0,     0,     0,     0,     0,
     479,     0,   256,     0,   243,   266,    70,   260,   634,     0,
     522,   523,     0,   284,   634,   599,    71,    69,   623,    68,
       0,   634,   432,    67,   623,   624,     0,     0,    21,   239,
       0,     0,   335,   336,   298,   301,   433,     0,   218,     0,
     219,   295,     0,    19,     0,     0,   621,    15,    18,   623,
      74,    14,   623,     0,     0,   627,   627,   244,     0,     0,
     627,   597,   623,     0,     0,     0,    82,   339,     0,    92,
      93,   100,   309,   408,   501,   500,   502,   499,     0,   498,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   505,    51,   233,   234,   630,   631,     4,   632,   622,
       0,     0,     0,     0,     0,     0,     0,   437,   435,   422,
      61,   306,   416,   418,     0,    88,     0,    80,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   618,   430,   634,   617,
     428,     0,    53,     0,     0,     0,     0,   621,     0,   622,
       0,   361,   360,     0,     0,   522,   523,   284,   110,   111,
       0,     0,   113,   530,     0,   522,   523,   284,   327,   187,
     180,   190,   175,   157,   158,   159,   115,   116,   595,   329,
     594,     0,   620,   619,     0,   308,   457,     0,     0,   125,
     602,   295,   267,   604,   263,     0,     0,     0,     0,   257,
     265,   430,   634,   428,     0,     0,     0,   258,   623,     0,
     300,   262,   623,   252,   634,   634,   251,   623,   305,    50,
      23,    25,    24,     0,   302,     0,     0,     0,   430,   428,
       0,    17,     0,   623,   293,    13,   622,    73,   289,   291,
     296,   629,   628,   245,   629,   247,   297,   598,     0,    99,
     505,    90,    85,     0,   430,   634,   428,   554,   485,   488,
     486,   503,   482,   458,   480,   459,   460,   484,   461,   462,
       0,   465,   471,     0,   472,   467,   468,     0,   473,     0,
     474,     0,   633,     7,    27,    28,    29,    30,    31,    48,
      49,   634,   634,    58,    62,   634,     0,    34,   271,     0,
      43,   270,   623,     0,    78,    89,    46,    45,     0,   198,
     266,    42,   216,   223,   228,   229,   230,   225,   227,   237,
     238,   231,   232,   209,   210,   235,   236,   623,   224,   226,
     220,   221,   222,   211,   212,   213,   214,   215,   608,   610,
     609,   611,     0,   261,   427,   623,   608,   610,   609,   611,
       0,   261,     0,   634,   352,     0,   351,     0,     0,     0,
       0,     0,     0,   295,   430,   634,   428,   320,   325,   110,
     111,   112,   528,   323,   430,   634,   428,     0,     0,   330,
     616,   615,   332,   608,   609,   261,    35,   200,    41,   208,
       0,     0,   198,   601,     0,   268,   264,   634,   608,   609,
     623,   608,   609,   600,   299,   625,   248,   253,   255,   304,
      22,     0,   240,     0,    32,   425,   423,   207,     0,    75,
      16,   623,   627,     0,    83,   612,    98,   623,   608,   609,
     560,   557,   556,   555,   558,   566,   575,     0,   586,   576,
     590,   589,   585,   554,   409,   553,   413,   559,   561,   562,
     564,   539,   568,   573,   634,   578,   634,   583,   539,   588,
     539,     0,   537,   489,     0,   464,   466,   476,   470,   478,
     217,   399,   623,     0,   397,   396,     0,   634,     0,   274,
       0,    87,    81,     0,     0,     0,     0,     0,     0,   431,
      65,     0,     0,   434,     0,     0,   429,    63,   634,   350,
     287,   634,   634,   443,   634,   353,   634,   355,   313,   354,
     316,     0,     0,   319,   612,   294,   623,   608,   609,     0,
       0,     0,     0,   110,   111,   114,   623,     0,   623,   532,
       0,   250,   419,    57,   249,     0,   126,   603,   269,   259,
       0,     0,   434,     0,     0,   634,   623,    11,     0,   292,
     246,    91,   434,     0,   373,   364,   366,   623,   362,   623,
     410,     0,     0,   546,   567,     0,   535,   593,   577,     0,
     536,     0,   549,   587,     0,   551,   591,   490,   494,   495,
     496,   487,   497,   395,   623,     0,   562,   380,   570,   571,
     634,   634,   581,   380,   380,   378,   401,     0,     0,     0,
       0,     0,   272,    79,   199,     0,    40,   205,    39,   206,
      66,   426,   626,     0,    37,   203,    38,   204,    64,   424,
     444,   445,   634,   446,     0,   634,   358,     0,     0,   356,
       0,     0,     0,   318,     0,     0,   434,     0,     0,     0,
       0,   434,   328,   596,   554,     0,   554,   333,   420,   421,
     201,     0,   254,   303,    20,   623,     0,   371,     0,   563,
       0,     0,   579,   538,   565,   539,   539,   574,   634,   592,
     539,   584,   539,   562,   539,   491,     0,   398,     0,   386,
     388,     0,   569,     0,   376,   377,     0,   391,     0,   393,
       0,   438,   436,     0,   417,   273,   241,    36,   202,     0,
       0,   448,   359,     0,    12,   450,     0,   310,   311,     0,
       0,   268,   634,   321,     0,   529,   324,   623,     0,     0,
     532,   363,   374,     0,   369,   365,   412,     0,     0,   411,
       0,   542,     0,   544,   534,     0,   550,     0,   547,   552,
     492,   400,   580,   379,   380,   380,   295,   430,   572,   634,
     380,   582,   380,   380,   405,   623,   403,   406,    59,     0,
     447,     0,   522,   523,   284,     0,   449,     0,   314,   317,
     440,   441,   439,     0,   326,   531,   331,   533,     0,     0,
     372,     0,   367,     0,     0,   539,   539,   539,   539,     0,
       0,   383,     0,   385,   612,   294,   375,     0,   392,     0,
     389,   394,     0,   402,   295,   430,   634,   428,   634,   634,
       0,     0,   370,     0,   415,   414,   543,     0,   540,   545,
     548,     0,   380,   380,   380,   380,   404,   612,   294,   623,
     608,   609,   442,   357,   322,   334,   368,   539,   493,   384,
       0,   381,   387,   390,   434,   541,   380,   382
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    68,    69,    70,   240,   572,   573,   256,
     257,   452,   258,   443,    72,    73,   363,    74,    75,   514,
     697,   247,    77,    78,   259,    79,    80,    81,   472,    82,
     213,   382,   383,   195,   196,   197,   198,   610,   561,   200,
      84,   445,   215,   264,   232,   752,   432,   433,   229,   230,
     217,   419,   434,   520,   521,    85,   361,   262,   263,   641,
     631,   365,   851,   366,   852,   739,   993,   742,   740,   597,
     599,   749,   750,   940,   249,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,   720,   575,   728,   848,   849,
     374,   775,   776,   777,   963,   900,   804,   693,   694,   805,
     975,   976,   282,   283,   477,   780,   881,   664,   949,   323,
     515,    97,    98,   718,   711,   570,   562,   321,   512,   511,
     582,   992,   722,   842,   920,   924,    99,   100,   101,   102,
     103,   104,   105,   294,   490,   106,   298,   107,   108,   296,
     300,   290,   288,   292,   482,   684,   683,   797,   895,   960,
    1009,   801,   109,   289,   110,   111,   112,   220,   221,   115,
     222,   223,   593,   741,   865,   866,   883,   783,   666,   667,
     668,   893,   670,   671,   672,   673,   809,   810,   674,   675,
     676,   677,   812,   813,   678,   679,   680,   681,   682,   786,
     401,   598,   269,   435,   225,   118,   635,   564,   602,   596,
     404,   307,   429,   430,   713,   463,   576,   369,   261
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -825
static const yytype_int16 yypact[] =
{
    -825,   119,  2707,  -825,  7450,  -825,  -825,  -825,  6944,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  7567,  7567,  -825,  -825,
    7567,  4059,  3645,  -825,  -825,  -825,  -825,   257,  6808,     9,
    -825,    70,  -825,  -825,  -825,  2955,  3783,  -825,  -825,  3093,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  8971,  8971,
     155,  5143,    -5,  7918,  8269,  7210,  -825,  6672,  -825,  -825,
    -825,     0,    82,   163,   166,  1150,  9088,  8971,  -825,    26,
    -825,  1149,  -825,   136,  -825,  -825,    62,   345,   230,  -825,
     239,  9322,  -825,   302,  3071,   370,   487,  -825,  9205,  9205,
    -825,  -825,  6044,  9435,  9548,  9661,  6535,    63,   160,  -825,
    -825,   325,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,   355,   548,  -825,   349,   604,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,   305,  -825,
    -825,  -825,  -825,   312,  8971,   445,  5275,  8971,  8971,  8971,
    -825,  8971,  -825,   385,  3071,   426,  -825,  -825,   384,   518,
      35,   307,   433,   317,   398,  -825,  -825,  -825,  5927,  -825,
    7567,  7567,  -825,  -825,  6161,  -825,  9205,    91,  -825,   403,
     413,  5407,  -825,  -825,  -825,   415,   418,    62,  -825,   556,
     497,   650,  7684,  -825,  5143,   437,    26,  -825,  1149,     9,
     456,  -825,     9,  9205,   441,   222,   248,  -825,   426,   476,
     248,  -825,     9,   552,  1150,  9774,   480,  -825,   602,   666,
     712,   716,  -825,  -825,  -825,  -825,  -825,  -825,   665,  -825,
     765,   807,   523,   500,   939,   506,    46,   526,   991,   527,
      66,   575,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  6278,
    9205,  9205,  9205,  9205,  7684,  9205,  9205,  -825,  -825,  -825,
     555,  -825,  -825,  -825,  8386,  -825,  5143,  7330,   512,  8386,
    8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,
    8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,  8971,
    8971,  8971,  8971,  8971,  8971,  8971,  -825,  2556,  7567,  -825,
   10063,  4480,   136,   129,   129,  9205,  9205,    26,   642,   519,
     610,  -825,  -825,   744,   643,    75,   108,   109,   809,   869,
    9205,   428,  -825,   550,   779,  -825,  -825,  -825,  -825,    20,
      39,    49,    59,   255,   261,   278,   283,   291,  -825,  -825,
    -825,   316,  -825,  -825, 10144,  -825,  -825,  9088,  9088,  -825,
    -825,   442,  -825,  -825,  -825,   819,  8971,  8971,  7801,  -825,
    -825, 10225,  7567, 10306,  8971,  8971,  8035,  -825,     9,   530,
    -825,  -825,     9,  -825,   538,   542,  -825,   143,  -825,  -825,
    -825,  -825,  -825,  6944,  -825,  8971,  5550,   545, 10225, 10306,
    8971,  1149,   547,     9,  -825,  -825,  6395,   554,  -825,   136,
    -825,  8152,  -825,  -825,  8269,  -825,  -825,  -825,   403,   853,
    -825,  -825,   561,  9774, 10387,  7567, 10468,  1125,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
      57,  -825,  -825,   544,  -825,  -825,  -825,   393,  -825,   565,
    -825,  8971,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,    38,    38,  -825,  -825,    38,  8971,  -825,   567,   572,
    -825,  -825,     9,  9774,   578,  -825,  -825,  -825,   595,  1156,
    -825,  -825,   497,  1664,  1664,  1664,  1664,  1230,  1230,  3485,
    3347,  1664,  1664,  3209,  3209,   687,   687, 10984,  1230,  1230,
     907,   907,  1035,   319,   319,   497,   497,   497,  4197,  3231,
    4335,  3369,   418,   586,  -825,     9,   736,  -825,   791,  -825,
     418,  3921,   717,   721,  -825,  4623,   718,  4909,    43,    43,
     642,  8503,   717,   114, 10549,  7567, 10630,  -825,   136,  -825,
     853,  -825,  -825,  -825, 10711,  7567, 10144,  4480,  9205,  -825,
    -825,  -825,  -825,  -825,  -825,  2356,  -825,  2797,  -825,  3071,
    6944,  8971,  2933,  -825,  8971,   426,  -825,   398,  2817,  3507,
       9,   455,   505,  -825,  -825,  -825,  -825,  7801,  8035,  -825,
    -825,  9205,  3071,   597,  -825,  -825,  -825,  3071,  5550,    24,
    -825,     9,   248,  9774,   561,   401,   395,     9,   416,   452,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  1031,  -825,  -825,
    -825,  -825,  -825,  1402,  -825,  -825,  -825,  -825,  -825,   622,
    -825,   606,  8971,  -825,   613,   704,   625,  -825,   628,   714,
     634,   722,  -825,  -825,   648,  -825,  -825,  -825,  -825,  -825,
     497,  -825,  1116,  5693,  -825,  -825,  5407,    38,  5693,   636,
    8620,  -825,   561,  9774,  9088,  8971,   672,  9088,  9088,  -825,
     555,   418,   652,   799,  9088,  9088,  -825,   555,   418,  -825,
    -825,  8737,   780,  -825,   549,  -825,   780,  -825,  -825,  -825,
    -825,   717,   162,  -825,    60,    78,     9,   327,   330,  9205,
      26,  9205,  4480,  1012,   395,  -825,     9,   717,   143,   657,
    7080,  -825,   160,   345,  -825,  8971,  -825,  -825,  -825,  -825,
    8971,  8971,   536,  8971,  8971,   660,   143,  -825,   671,  -825,
    -825,  -825,   462,  1031,   439,  -825,   670,     9,  -825,     9,
    -825,  8971,  1402,  -825,  -825,   485,  -825,  -825,  -825,   290,
    -825,  1402,  -825,  -825,  1502,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,     9,   695,   702,   690,  9887,  -825,
     692,   625,  -825,   696,   701,  -825,   699,   832,   724,  5407,
     839,  8971,   720,   561,  3071,  8971,  -825,  3071,  -825,  3071,
    -825,  -825,  -825,  9088,  -825,  3071,  -825,  3071,  -825,  -825,
     567,  -825,   760,  -825,  5026,   854,  -825,  9205,   717,  -825,
     717,  5693,  5693,  -825,  8854,  4766,   337,    43,  4480,    26,
     717,  -825,  -825,  -825,  1402,  4480,  1402,  -825,  -825,  -825,
    3071,  8971,  8035,  -825,  -825,     9,  1268,   728,  1242,  -825,
     734,    76,  -825,  -825,  -825,   747,   753,  -825,   625,  -825,
     754,  -825,   756,  -825,   754,  -825,   772,  -825,  9887,  1402,
    -825,   843,   871,   485,  -825,  -825,  1402,  -825,  1502,  -825,
    1081,  -825,  -825,   767,  -825,   766,  3071,  -825,  3071, 10000,
     129,  -825,  -825,  5693,  -825,  -825,   129,  -825,  -825,   717,
     717,  -825,   453,  -825,   717,  -825,  -825,     9,   717,    26,
     657,  -825,   769,  1268,   473,  -825,  -825,  5693,  5407,  -825,
    1402,  -825,  1502,  -825,  -825,  1502,  -825,  1502,  -825,  -825,
    -825,  -825,   871,  -825,   774,   781,  -825, 10792,  -825,   625,
     784,  -825,   787,   784,  -825,   379,  -825,  -825,  -825,   883,
    -825,   931,   142,   215,   246,  4480,  -825,  4623,  -825,  -825,
    -825,  -825,  -825,  5693,  -825,  -825,  -825,  -825,  4480,  1268,
     769,  1268,   788,   917,   811,   754,   805,   754,   754,  5810,
    1402,  -825,  1502,  -825,   810,   813,  -825,  1502,  -825,  1502,
    -825,  -825,  1081,  -825,   256, 10873,  7567, 10954,   721,   549,
     717,   717,   769,  1268,  -825,  -825,  -825,  1502,  -825,  -825,
    -825,   833,   784,   817,   784,   784,  -825,    93,   181,     9,
     270,   298,  -825,  -825,  -825,  -825,   769,   754,  -825,  -825,
    1502,  -825,  -825,  -825,   324,  -825,   784,  -825
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -825,  -825,  -825,  -374,  -825,    37,  -825,  -560,   211,  -825,
     499,  -825,    44,  -825,  -296,    29,   -63,   -57,  -825,  -579,
    -825,   732,    -4,   868,  -142,    -1,   -73,  -825,  -393,     6,
    1594,  -336,   870,   -53,  -825,    -6,  -825,  -825,    32,  -825,
    1061,  -825,  1797,  -825,   -55,   251,  -343,   106,   -11,  -825,
    -387,  -214,    51,  -825,  -305,   -19,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,     3,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,  -825,  -825,  -825,    87,  -358,  -535,   -65,  -639,
    -825,  -812,  -765,   197,   280,   100,  -825,  -422,  -825,  -655,
    -825,   -48,  -825,  -825,  -825,  -825,  -825,  -825,  -825,   226,
    -825,  -825,  -825,  -825,  -825,  -825,  -825,   -97,  -825,  -825,
    -545,  -825,   -47,  -825,  -825,  -825,  -825,  -825,  -825,   881,
    -825,  -825,  -825,  -825,   685,  -825,  -825,  -825,  -825,  -825,
    -825,   775,   928,  -825,   -84,  -825,  -825,  -825,  -825,  -825,
    -825,  -825,    10,  -825,    19,  -825,     8,  1255,  1286,   895,
    1711,  1613,  -825,  -825,    54,  -825,  -443,  -508,  -569,  -824,
    -513,  -105,  -669,  -127,    72,   213,    96,  -825,  -825,  -825,
    -148,  -727,  -805,   101,   224,  -825,  -629,  -825,  -173,  -634,
    -825,  -825,  -825,    61,  -409,  -825,  -258,  -825,  -825,   -83,
    -825,   -43,     1,  -152,  -588,  -213,   -67,   -13,    -2
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -635
static const yytype_int16 yytable[] =
{
     119,   405,   308,   360,   287,    86,   577,    86,   328,   302,
     427,   233,   212,   212,   403,   565,   212,   623,   201,   219,
     219,   319,   238,   219,   531,   308,   364,   202,   236,   367,
     239,   616,   762,   526,   665,   731,   277,   747,   201,   616,
     199,   120,   790,   399,   730,   591,    71,   202,    71,   368,
     260,   267,   271,   465,    86,   623,   309,   467,   278,   772,
     199,   276,   277,   814,   891,   320,   945,   218,   218,   219,
     727,   218,   633,   301,   277,   277,   277,   224,   224,   620,
     644,   224,   438,   845,   278,  -105,   977,   850,   317,   199,
     696,   219,   219,   698,   779,   219,   373,   384,   384,   563,
    -101,   971,   571,  -107,   265,   947,  -105,   457,  -516,   493,
     458,   942,   453,   884,   266,   270,   691,   362,   362,     3,
     478,   362,   216,   226,   880,  -524,   227,  -515,   199,   499,
     702,   830,   647,  -102,  -109,  -288,   423,  -517,   838,  -108,
    -288,   -73,   574,   293,   778,   440,   605,  -518,   856,   896,
     356,   402,  -101,   886,   235,  -101,   441,   442,   861,   494,
     692,   -87,   892,   563,  -516,   571,   449,   479,   305,   480,
     792,   306,   795,   315,   316,   574,   904,   905,  1000,   500,
     315,   316,   860,  -515,   522,   305,   317,   945,   306,   308,
     948,   636,   319,  -517,  -107,   476,   318,   -96,   977,  -608,
     685,   231,   471,  -518,   241,   971,   484,   359,   487,    86,
     491,   251,   -92,   455,   491,   -98,   420,  -609,   636,   623,
     665,   427,   420,   891,   212,   295,   212,   212,  -102,   436,
     884,   219,  -608,   219,   219,  -105,  1032,   219,  -105,   219,
     616,   616,   736,   456,    86,   -93,  -100,   504,   505,   506,
     507,   -99,   746,   260,   954,    86,   277,    86,   745,  -109,
     778,   877,   255,   437,   768,   439,   219,   517,  1056,  -108,
     965,   305,   527,   468,   306,   819,   624,   972,   278,   218,
     626,   218,   470,  -104,  -101,   629,   884,  -101,   235,   224,
     586,   224,   459,   990,   318,   937,   451,   939,   934,   854,
     308,   639,   578,   579,   305,   938,   297,   306,   277,   299,
     823,  -106,    86,   219,   219,   219,   219,    86,   219,   219,
    -609,  1006,   933,  -107,   580,   260,  -107,   219,   636,    86,
     278,   484,   219,   524,   428,  1016,   431,  -103,   636,   362,
     362,   362,   362,  -520,   509,   510,   503,   324,   884,  -519,
     606,   608,  -104,    71,   212,  -106,   436,  -102,   508,   461,
    -102,   219,  -103,   778,    86,   778,  -521,   462,   219,   219,
     701,  -510,   669,   322,   855,   519,   325,   951,   953,  -513,
     519,  1043,   956,   219,   958,   464,   959,   991,  -109,   330,
     660,  -109,   569,   462,   362,   362,   234,  -525,  -108,  -520,
     471,  -108,   235,   759,   600,  -519,   686,   425,   526,   588,
     219,   219,  -104,   686,   661,  -104,   841,   255,   212,   329,
     436,   665,  -521,   665,  -102,   219,   -96,  -510,    58,   770,
     778,  1002,   420,   420,  -109,  -513,   569,   630,  1031,   407,
    -106,   -95,   409,  -106,   119,  -524,   353,   354,   355,    86,
     471,   234,   447,   201,   277,   569,   478,  -339,  -339,    86,
     601,  1064,   202,   623,   -95,   255,  -103,   -97,   844,  -103,
     581,   212,  -101,   436,   -94,   199,   278,   -97,   219,   617,
     589,   569,  -294,  -294,   590,   616,   778,   -94,   778,   769,
      71,   650,   -92,   651,   652,   653,   654,  1036,  1038,  1039,
    1040,   411,   416,   479,   277,   480,  -339,   709,   569,   695,
     695,   729,   729,   695,  -339,   716,  1022,   417,   -96,   815,
     778,   418,   642,   424,   235,   650,   278,   651,   652,   653,
     654,  -294,   450,   -95,  -609,   426,   688,   255,   -96,  -294,
    -608,   -96,   444,   655,   811,   763,   -96,   446,   706,  1065,
     751,   759,   710,   -95,   228,   656,   -95,   231,   669,  -108,
     717,   -95,   985,   847,   844,   807,   712,   330,   987,   -97,
     771,   723,  -104,   -72,   356,   357,   876,   454,    86,   -94,
      86,   212,   460,   436,   659,   660,   478,   806,   219,   -97,
     486,   212,   -97,   436,   753,   764,   863,   -97,   219,   -94,
      86,   219,   -94,   754,   756,   356,   421,   -94,   469,   661,
    1001,   466,   889,   488,   873,   420,   889,   473,   569,   492,
     201,   712,  -106,   358,   277,   879,   871,   748,   569,   202,
     471,   359,   732,   479,   219,   480,   119,   888,  -525,   495,
     498,    86,   199,   356,   448,   501,   278,   527,   712,   525,
     826,   828,   513,  -103,   422,   868,   831,   834,   836,   581,
     766,   502,   359,   751,   890,  -102,   583,   894,   587,   733,
     625,   592,   787,   858,   787,   627,   857,   669,   859,   628,
     634,   638,    71,  1049,   277,   -93,   669,   687,   765,   356,
     474,   -87,   422,   816,   408,   695,    86,   867,   643,    86,
     359,    86,   798,   799,  -266,   800,   278,   219,   689,   700,
     219,   219,   704,    46,    47,   703,   754,   219,   219,   843,
     846,  -109,   846,   941,   846,  -425,   815,   719,   478,   721,
     889,   725,   767,   815,    76,   815,    76,   712,   475,   781,
     450,  -100,   219,   782,   219,    86,   359,   712,    76,    76,
     785,   811,    76,  -522,  -522,   969,   788,   330,   811,   669,
     811,   669,   789,   420,   808,   791,   793,  -108,   362,   636,
     362,   794,   519,  -267,   796,   479,   917,   480,   481,   970,
     816,   973,   199,    76,   926,   995,   724,   -99,   726,   277,
     729,   825,   935,   832,   806,   844,   864,   872,    76,  -523,
    -523,   806,  -522,  -284,  -284,   816,   874,   878,   787,   787,
    -522,   902,   351,   352,   353,   354,   355,   897,   853,   898,
      76,    76,    86,  1005,    76,  1007,   714,   899,   478,   903,
    1008,   356,   584,   906,   862,  -605,   219,   815,   908,   815,
     921,   910,   911,   925,   815,   669,   815,    86,  -523,   914,
     219,   919,  -284,  -104,    86,    86,  -523,  -268,    86,   912,
    -284,    86,   811,   923,   811,   943,   356,   594,    86,   811,
     478,   811,   997,   -95,   946,   479,   362,   480,   483,   277,
     585,   715,   478,  1042,   950,  1044,   787,   815,   359,   833,
     952,   955,  1045,   957,   961,  -606,  -510,  -510,  1027,   966,
     277,   962,   978,  -269,   817,   806,   999,   818,  -106,   820,
    1057,  1010,   811,   907,   909,   595,  -103,   479,  1012,   480,
     485,  1017,   981,   359,  1019,  1033,    86,  1034,   -97,   479,
     846,   480,   483,  1066,   611,   927,   -94,   928,    76,  1024,
    -295,  -295,  1037,  -605,  1058,  -510,  1035,   936,  -605,  -608,
      86,    86,  -609,  -510,  1060,   640,  -513,  -513,   356,   967,
      76,   371,    76,    76,  1053,   388,    76,   787,    76,   839,
     875,   808,   803,    76,  1046,   808,  1023,   330,   808,   869,
     808,  1052,   406,   497,    76,   415,    76,   291,    86,  -295,
      86,   400,   343,   344,   998,    76,    86,  -295,   887,   968,
     964,    86,   478,  -606,     0,  -513,   885,   595,  -606,     0,
       0,     0,    86,  -513,     0,   359,   988,   989,   356,  1025,
       0,   994,   212,     0,   436,   996,   723,   846,     0,   219,
     913,   350,   351,   352,   353,   354,   355,     0,  -612,     0,
       0,    76,    76,    76,    76,    76,    76,    76,    76,   479,
     712,   480,   489,     0,   478,   922,    76,     0,    76,   569,
       0,    76,   929,   930,  1011,  1013,   932,  1026,     0,     0,
    1018,     0,  1020,  1021,     0,   359,     0,   214,   214,     0,
       0,   214,   808,   650,   808,   651,   652,   653,   654,   808,
      76,   808,     0,    76,     0,     0,     0,    76,    76,  -612,
    -612,   479,     0,   480,   496,   330,     0,     0,     0,   248,
     250,     0,    76,     0,   214,   214,     0,  1054,  1055,     0,
     343,   344,     0,   773,     0,     0,     0,   303,   304,   774,
       0,     0,   808,   974,   986,   651,   652,   653,   654,    76,
      76,     0,  1059,  1061,  1062,  1063,  -612,     0,  -612,     0,
       0,  -608,     0,     0,    76,     0,  -612,     0,  1003,  1004,
     351,   352,   353,   354,   355,     0,  1067,     0,   650,     0,
     651,   652,   653,   654,   655,     0,     0,   650,    76,   651,
     652,   653,   654,   655,     0,     0,   656,     0,    76,   310,
     311,   312,   313,   314,     0,   656,  1028,     0,  1029,     0,
     705,     0,     0,     0,  1030,     0,     0,    76,   657,    41,
      42,    43,    44,     0,   658,   659,   660,   657,     0,     0,
    1041,     0,     0,   658,   659,   660,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,     0,
     661,   343,   344,   662,     0,     0,     0,     0,     0,   661,
       0,     0,   662,     0,     0,     0,     0,   113,     0,   113,
       0,   235,     0,     0,   663,   214,     0,     0,   214,   214,
     214,     0,   303,     0,   345,     0,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,     0,     0,   114,   214,
     114,   214,   214,  -243,   650,     0,   651,   652,   653,   654,
     330,     0,     0,     0,     0,     0,   113,    76,     0,    76,
     279,     0,     0,     0,     0,   343,   344,    76,     0,     0,
     650,     0,   651,   652,   653,   654,     0,    76,     0,    76,
      76,     0,     0,     0,   773,     0,   279,   114,     0,     0,
     944,   280,     0,     0,     0,     0,     0,     0,   375,   385,
     385,   385,   348,   349,   350,   351,   352,   353,   354,   355,
     773,     0,     0,    76,     0,     0,     0,   280,     0,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,   376,
     386,   386,   386,     0,     0,   214,     0,     0,     0,     0,
     529,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   556,   557,     0,     0,   214,
       0,     0,     0,     0,     0,    76,     0,     0,    76,     0,
      76,     0,     0,     0,     0,     0,    76,     0,     0,    76,
      76,     0,     0,     0,     0,     0,    76,    76,     0,     0,
       0,     0,     0,     0,   650,     0,   651,   652,   653,   654,
     655,   113,     0,     0,     0,     0,     0,     0,   607,   609,
       0,    76,   656,    76,    76,     0,     0,   612,   214,   214,
       0,     0,     0,   214,     0,   607,   609,   214,     0,     0,
       0,     0,   114,     0,   657,     0,   113,     0,     0,     0,
     658,   659,   660,     0,     0,     0,   632,   113,     0,   113,
       0,   637,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   214,     0,     0,   214,   661,   114,     0,   662,
     279,     0,     0,     0,     0,     0,   214,     0,   114,     0,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,     0,     0,   650,     0,   651,   652,   653,   654,
     655,   280,   690,     0,   113,    76,     0,     0,     0,   113,
       0,     0,   656,     0,     0,     0,    76,   214,     0,    76,
       0,   113,   279,    76,    76,     0,     0,    76,     0,     0,
      76,     0,     0,     0,   657,   114,    83,    76,    83,     0,
     114,   659,   660,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   280,     0,   117,   113,   117,     0,     0,
       0,     0,     0,     0,     0,     0,   661,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   214,     0,     0,    83,   214,   114,     0,     0,
       0,     0,     0,     0,     0,    76,   214,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,     0,   281,     0,
       0,     0,   214,     0,     0,   214,     0,     0,     0,    76,
      76,     0,     0,     0,     0,     0,     0,   372,   214,   214,
       0,     0,     0,     0,   281,     0,     0,     0,     0,     0,
       0,   113,     0,     0,     0,     0,   377,   387,   387,     0,
       0,   113,     0,   116,     0,   116,     0,    76,     0,    76,
       0,     0,     0,     0,     0,    76,     0,     0,   279,     0,
      76,     0,   114,   214,   330,  -635,  -635,  -635,  -635,   335,
     336,    76,   114,  -635,  -635,     0,     0,     0,     0,   343,
     344,     0,     0,     0,     0,     0,     0,     0,    76,   280,
       0,   214,   116,     0,     0,   612,   824,     0,   827,   829,
       0,     0,     0,     0,     0,   835,   837,     0,   279,     0,
       0,     0,   214,     0,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,   280,
       0,     0,     0,     0,     0,     0,   870,     0,     0,   117,
       0,   827,   829,     0,   835,   837,     0,     0,     0,     0,
     113,     0,   113,     0,     0,    83,     0,     0,     0,     0,
       0,     0,   214,     0,     0,     0,    83,     0,    83,     0,
       0,   268,   113,     0,   117,     0,     0,     0,     0,     0,
       0,   114,     0,   114,     0,   117,     0,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   214,   114,     0,     0,   916,     0,   281,     0,
       0,     0,     0,   113,   918,     0,     0,     0,   279,     0,
       0,     0,     0,    83,     0,     0,     0,     0,    83,     0,
       0,     0,     0,     0,     0,   214,     0,   116,     0,     0,
      83,     0,   117,   528,   114,     0,     0,   117,     0,   280,
       0,     0,   918,   214,     0,     0,     0,     0,     0,   117,
     281,     0,     0,     0,     0,     0,     0,     0,   113,     0,
       0,   113,   116,   113,     0,    83,     0,     0,   279,     0,
       0,     0,     0,   116,     0,   116,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,     0,     0,     0,   114,
       0,     0,   114,     0,   114,     0,     0,     0,     0,   280,
       0,     0,     0,     0,     0,     0,     0,   113,     0,     0,
       0,   410,     0,     0,   412,   413,   414,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,     0,     0,     0,     0,   116,     0,     0,   114,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,     0,     0,     0,     0,     0,   117,
       0,     0,     0,   385,     0,     0,     0,     0,     0,   117,
       0,     0,   116,     0,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   281,   214,     0,     0,
       0,     0,     0,     0,   386,     0,     0,     0,     0,   113,
       0,     0,     0,     0,     0,   114,   113,   113,     0,     0,
     113,     0,     0,   113,     0,     0,     0,     0,     0,     0,
     113,   518,     0,     0,     0,     0,   530,     0,     0,     0,
     114,     0,     0,     0,     0,     0,   281,   114,   114,     0,
       0,   114,     0,     0,   114,     0,     0,     0,     0,     0,
       0,   114,     0,   385,     0,     0,     0,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   116,     0,    83,
       0,    83,     0,     0,   982,     0,     0,     0,   113,     0,
       0,     0,     0,     0,   386,     0,     0,     0,   117,     0,
     117,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   113,     0,   983,     0,     0,     0,   114,
     117,     0,     0,     0,   613,   615,     0,     0,     0,     0,
       0,     0,     0,   268,     0,     0,     0,     0,     0,     0,
       0,     0,    83,   114,   114,     0,     0,     0,     0,     0,
     113,     0,   113,     0,     0,     0,     0,     0,   113,     0,
       0,   117,     0,   113,     0,     0,   281,     0,   615,     0,
       0,   268,     0,     0,   113,     0,     0,     0,     0,     0,
       0,   114,     0,   114,     0,     0,     0,     0,     0,   114,
       0,     0,     0,     0,   114,     0,   116,    83,   116,     0,
      83,     0,    83,     0,     0,   114,     0,   802,   528,     0,
       0,     0,     0,     0,     0,     0,   117,     0,   116,   117,
       0,   117,     0,   699,     0,     0,   281,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   116,
       0,     0,     0,     0,     0,   117,  -634,     0,     0,     0,
       0,     0,     0,     0,  -634,  -634,  -634,     0,     0,  -634,
    -634,  -634,     0,  -634,     0,     0,     0,     0,   530,     0,
       0,     0,  -634,  -634,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -634,  -634,     0,  -634,  -634,  -634,  -634,
    -634,     0,     0,     0,   116,     0,     0,   116,   757,   116,
       0,   758,     0,    83,     0,     0,     0,     0,     0,     0,
       0,   387,     0,     0,   615,   268,     0,     0,     0,     0,
       0,     0,   117,     0,     0,     0,     0,     0,    83,     0,
       0,     0,     0,  -634,  -634,    83,    83,     0,     0,    83,
       0,     0,    83,   116,     0,     0,     0,   117,     0,    83,
       0,     0,     0,     0,   117,   117,     0,  -634,   117,   784,
       0,   117,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -634,  -634,     0,     0,     0,   231,  -634,   822,  -634,     0,
    -634,  -634,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   387,     0,   980,     0,     0,     0,    83,   840,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,     0,   984,     0,     0,     0,   117,     0,     0,     0,
       0,    83,    83,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   116,     0,     0,     0,     0,
     117,   117,   116,   116,     0,     0,   116,     0,     0,   116,
       0,     0,     0,     0,     0,     0,   116,     0,   882,    83,
       0,    83,     0,     0,     0,     0,     0,    83,     0,     0,
       0,     0,    83,     0,     0,     0,     0,     0,   117,     0,
     117,     0,     0,    83,     0,     0,   117,     0,   558,   559,
       0,   117,   560,     0,     0,     0,     0,     0,   915,     0,
       0,     0,   117,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,   116,   174,   175,     0,     0,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,   931,     0,     0,   180,   181,     0,     0,   116,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   268,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,     0,   192,   193,     0,
       0,     0,     0,     0,   194,     0,   116,     0,   116,     0,
       0,     0,     0,     0,   116,     0,     0,  -634,     4,   116,
       5,     6,     7,     8,     9,     0,     0,     0,    10,    11,
     116,     0,     0,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,    51,
      52,     0,    53,    54,     0,    55,     0,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,  -612,     0,     0,
       0,     0,     0,     0,     0,  -612,  -612,  -612,     0,     0,
    -612,  -612,  -612,     0,  -612,     0,     0,    65,    66,    67,
       0,   755,     0,  -612,  -612,  -612,  -612,     0,     0,  -634,
       0,     0,  -634,     0,  -612,  -612,     0,  -612,  -612,  -612,
    -612,  -612,     0,     0,     0,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,   338,   339,   340,   341,   342,
       0,     0,   343,   344,     0,     0,     0,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,
       0,     0,  -612,  -612,  -612,  -612,     0,   760,  -612,     0,
       0,     0,     0,     0,  -612,   345,     0,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,     0,  -612,     0,
       0,  -612,     0,     0,  -105,  -612,  -612,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,     0,     0,     0,
       0,  -612,  -612,  -612,  -612,  -510,     0,  -612,  -612,  -612,
       0,  -612,  -612,  -510,  -510,  -510,     0,     0,  -510,  -510,
    -510,     0,  -510,     0,     0,     0,     0,   705,     0,     0,
    -510,     0,  -510,  -510,  -510,     0,     0,     0,     0,     0,
       0,     0,  -510,  -510,     0,  -510,  -510,  -510,  -510,  -510,
       0,     0,     0,   330,   331,   332,   333,   334,   335,   336,
     337,   338,   339,   340,   341,   342,     0,     0,   343,   344,
       0,     0,     0,     0,     0,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,     0,     0,
    -510,  -510,  -510,  -510,     0,  -510,  -510,     0,     0,     0,
       0,   345,  -510,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,     0,     0,     0,  -510,     0,     0,  -510,
       0,     0,  -510,  -510,  -510,  -510,  -510,  -510,  -510,  -510,
    -510,  -510,  -510,  -510,  -510,     0,     0,     0,     0,     0,
    -510,  -510,  -510,  -513,     0,  -510,  -510,  -510,     0,  -510,
    -510,  -513,  -513,  -513,     0,     0,  -513,  -513,  -513,     0,
    -513,     0,     0,     0,     0,     0,     0,     0,  -513,     0,
    -513,  -513,  -513,     0,     0,     0,     0,     0,     0,     0,
    -513,  -513,     0,  -513,  -513,  -513,  -513,  -513,     0,     0,
       0,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,     0,     0,   343,   344,     0,     0,
       0,     0,     0,  -513,  -513,  -513,  -513,  -513,  -513,  -513,
    -513,  -513,  -513,  -513,  -513,  -513,     0,     0,  -513,  -513,
    -513,  -513,     0,  -513,  -513,     0,     0,     0,     0,   345,
    -513,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,     0,     0,     0,  -513,     0,     0,  -513,     0,     0,
    -513,  -513,  -513,  -513,  -513,  -513,  -513,  -513,  -513,  -513,
    -513,  -513,  -513,     0,     0,     0,     0,     0,  -513,  -513,
    -513,  -613,     0,  -513,  -513,  -513,     0,  -513,  -513,  -613,
    -613,  -613,     0,     0,  -613,  -613,  -613,     0,  -613,     0,
       0,     0,     0,     0,     0,     0,     0,  -613,  -613,  -613,
    -613,     0,     0,     0,     0,     0,     0,     0,  -613,  -613,
       0,  -613,  -613,  -613,  -613,  -613,     0,     0,     0,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
    -635,  -635,     0,     0,   343,   344,     0,     0,     0,     0,
       0,  -613,  -613,  -613,  -613,  -613,  -613,  -613,  -613,  -613,
    -613,  -613,  -613,  -613,     0,     0,  -613,  -613,  -613,  -613,
       0,     0,  -613,     0,     0,     0,     0,     0,  -613,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,     0,
       0,     0,  -613,     0,     0,  -613,     0,     0,     0,  -613,
    -613,  -613,  -613,  -613,  -613,  -613,  -613,  -613,  -613,  -613,
    -613,     0,     0,     0,     0,  -613,  -613,  -613,  -613,  -614,
       0,  -613,  -613,  -613,     0,  -613,  -613,  -614,  -614,  -614,
       0,     0,  -614,  -614,  -614,     0,  -614,     0,     0,     0,
       0,     0,     0,     0,     0,  -614,  -614,  -614,  -614,     0,
       0,     0,     0,     0,     0,     0,  -614,  -614,     0,  -614,
    -614,  -614,  -614,  -614,     0,     0,     0,   330,   331,   332,
     333,   334,   335,   336,   337,     0,   339,   340,     0,     0,
       0,     0,   343,   344,     0,     0,     0,     0,     0,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,
    -614,  -614,     0,     0,  -614,  -614,  -614,  -614,     0,     0,
    -614,     0,     0,     0,     0,     0,  -614,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,     0,     0,     0,
    -614,     0,     0,  -614,     0,     0,     0,  -614,  -614,  -614,
    -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,  -614,     0,
       0,     0,     0,  -614,  -614,  -614,  -614,  -294,     0,  -614,
    -614,  -614,     0,  -614,  -614,  -294,  -294,  -294,     0,     0,
    -294,  -294,  -294,     0,  -294,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -294,  -294,  -294,     0,     0,     0,
       0,     0,     0,     0,  -294,  -294,     0,  -294,  -294,  -294,
    -294,  -294,     0,     0,     0,   330,   331,   332,   333,   334,
     335,   336,     0,     0,   339,   340,     0,     0,     0,     0,
     343,   344,     0,     0,     0,     0,     0,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
       0,     0,  -294,  -294,  -294,  -294,     0,   761,  -294,     0,
       0,     0,     0,     0,  -294,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,     0,     0,     0,  -294,     0,
       0,  -294,     0,     0,  -107,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,     0,     0,     0,
       0,     0,  -294,  -294,  -294,  -433,     0,  -294,  -294,  -294,
       0,  -294,  -294,  -433,  -433,  -433,     0,     0,  -433,  -433,
    -433,     0,  -433,     0,     0,     0,     0,     0,     0,     0,
       0,  -433,  -433,  -433,     0,     0,     0,     0,     0,     0,
       0,     0,  -433,  -433,     0,  -433,  -433,  -433,  -433,  -433,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -433,  -433,  -433,  -433,  -433,
    -433,  -433,  -433,  -433,  -433,  -433,  -433,  -433,     0,     0,
    -433,  -433,  -433,  -433,     0,     0,  -433,     0,     0,     0,
       0,     0,  -433,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -433,     0,     0,     0,
       0,     0,     0,  -433,     0,  -433,  -433,  -433,  -433,  -433,
    -433,  -433,  -433,  -433,  -433,     0,     0,     0,     0,  -433,
    -433,  -433,  -433,  -285,   231,  -433,  -433,  -433,     0,  -433,
    -433,  -285,  -285,  -285,     0,     0,  -285,  -285,  -285,     0,
    -285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -285,  -285,  -285,     0,     0,     0,     0,     0,     0,     0,
    -285,  -285,     0,  -285,  -285,  -285,  -285,  -285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,     0,     0,  -285,  -285,
    -285,  -285,     0,     0,  -285,     0,     0,     0,     0,     0,
    -285,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -285,     0,     0,  -285,     0,     0,
       0,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,     0,     0,     0,     0,     0,  -285,  -285,
    -285,  -423,     0,  -285,  -285,  -285,     0,  -285,  -285,  -423,
    -423,  -423,     0,     0,  -423,  -423,  -423,     0,  -423,     0,
       0,     0,     0,     0,     0,     0,     0,  -423,  -423,  -423,
       0,     0,     0,     0,     0,     0,     0,     0,  -423,  -423,
       0,  -423,  -423,  -423,  -423,  -423,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,  -423,  -423,  -423,     0,     0,  -423,  -423,  -423,  -423,
       0,     0,  -423,     0,     0,     0,     0,     0,  -423,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -423,     0,     0,     0,     0,     0,     0,  -423,
       0,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,  -423,
    -423,     0,     0,     0,     0,  -423,  -423,  -423,  -423,  -301,
    -423,  -423,  -423,  -423,     0,  -423,  -423,  -301,  -301,  -301,
       0,     0,  -301,  -301,  -301,     0,  -301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -301,  -301,     0,     0,
       0,     0,     0,     0,     0,     0,  -301,  -301,     0,  -301,
    -301,  -301,  -301,  -301,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,
    -301,  -301,     0,     0,  -301,  -301,  -301,  -301,     0,     0,
    -301,     0,     0,     0,     0,     0,  -301,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -301,     0,     0,     0,     0,     0,     0,  -301,     0,  -301,
    -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,  -301,     0,
       0,     0,     0,     0,  -301,  -301,  -301,  -612,   228,  -301,
    -301,  -301,     0,  -301,  -301,  -612,  -612,  -612,     0,     0,
       0,  -612,  -612,     0,  -612,     0,     0,     0,     0,     0,
       0,     0,     0,  -612,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -612,  -612,     0,  -612,  -612,  -612,
    -612,  -612,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,  -612,
       0,     0,  -612,  -612,  -612,  -612,     0,   707,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -612,     0,
       0,     0,     0,     0,  -105,  -612,     0,  -612,  -612,  -612,
    -612,  -612,  -612,  -612,  -612,  -612,  -612,     0,     0,     0,
       0,  -612,  -612,  -612,   -96,  -294,     0,  -612,     0,  -612,
       0,  -612,  -612,  -294,  -294,  -294,     0,     0,     0,  -294,
    -294,     0,  -294,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -294,  -294,     0,  -294,  -294,  -294,  -294,  -294,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,     0,     0,
    -294,  -294,  -294,  -294,     0,   708,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -294,     0,     0,     0,
       0,     0,  -107,  -294,     0,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,     0,     0,     0,     0,     0,
    -294,  -294,   -98,     0,     0,  -294,     0,  -294,     0,  -294,
    -294,   252,     0,     5,     6,     7,     8,     9,  -634,  -634,
    -634,    10,    11,     0,     0,  -634,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,   253,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -634,     0,   252,  -634,     5,     6,     7,     8,
       9,     0,     0,  -634,    10,    11,     0,  -634,  -634,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,    29,
     253,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,    51,    52,     0,    53,    54,
       0,    55,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -634,     0,   252,  -634,     5,
       6,     7,     8,     9,     0,     0,  -634,    10,    11,     0,
       0,  -634,    12,  -634,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,   253,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,    51,    52,
       0,    53,    54,     0,    55,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    67,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -634,     0,
     252,  -634,     5,     6,     7,     8,     9,     0,     0,  -634,
      10,    11,     0,     0,  -634,    12,     0,    13,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,    20,
      21,    22,    23,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,     0,    28,    29,   253,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
      43,    44,     0,    45,    46,    47,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
       0,    51,    52,     0,    53,    54,     0,    55,     0,     0,
      56,    57,    58,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,   252,     0,     5,
       6,     7,     8,     9,     0,  -634,  -634,    10,    11,    65,
      66,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,  -634,     0,     0,  -634,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
       0,    28,    29,   253,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    50,     0,     0,    51,    52,
       0,    53,    54,     0,    55,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,   252,     0,     5,     6,     7,     8,
       9,     0,     0,     0,    10,    11,    65,    66,    67,    12,
       0,    13,    14,    15,    16,    17,    18,    19,  -634,     0,
       0,  -634,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,    29,
     253,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,   254,    52,     0,    53,    54,
       0,    55,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,   252,     0,     5,     6,
       7,     8,     9,  -634,     0,  -634,    10,    11,  -634,     0,
       0,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,   253,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,   252,     0,
       5,     6,     7,     8,     9,  -634,     0,  -634,    10,    11,
    -634,     0,     0,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,     0,    28,    29,   253,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    50,     0,     0,    51,
      52,     0,    53,    54,     0,    55,     0,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,    66,    67,
       0,     0,  -634,     0,     0,     0,     0,     0,     0,  -634,
       0,     4,  -634,     5,     6,     7,     8,     9,     0,     0,
       0,    10,    11,     0,     0,     0,    12,     0,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,     0,     0,  -634,     0,     0,     0,     0,
       0,     0,  -634,     0,   252,  -634,     5,     6,     7,     8,
       9,     0,     0,  -634,    10,    11,     0,     0,     0,    12,
       0,    13,    14,    15,    16,    17,    18,    19,     0,     0,
       0,     0,     0,    20,    21,    22,    23,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,     0,    28,    29,
     253,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,    51,    52,     0,    53,    54,
       0,    55,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,   252,     0,     5,     6,     7,     8,     9,     0,     0,
       0,    10,    11,    65,    66,    67,    12,     0,    13,    14,
      15,    16,    17,    18,    19,  -634,     0,     0,  -634,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,   253,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,  -634,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      65,    66,    67,    12,     0,    13,    14,    15,    16,    17,
      18,    19,  -634,     0,     0,  -634,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,   203,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   204,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,   206,
      52,     0,    53,    54,     0,   207,   208,   209,    56,    57,
     210,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,    65,   211,    67,
      12,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,   235,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,     0,     0,   206,    52,     0,    53,
      54,     0,     0,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,    16,    17,    18,    19,   305,     0,     0,   306,
       0,    20,    21,    22,    23,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   206,    52,     0,    53,    54,     0,     0,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,     0,     0,     0,    10,
      11,    65,    66,    67,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,   235,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,     0,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,    43,
      44,     0,    45,    46,    47,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,     0,     0,
      51,    52,     0,    53,    54,     0,    55,     0,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,     0,     0,     0,    10,    11,    65,    66,
      67,    12,     0,    13,    14,    15,    16,    17,    18,    19,
     502,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
      28,    29,   253,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   502,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,     0,     0,     0,   145,   146,   147,   389,   390,
     391,   392,   152,   153,   154,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   393,   394,   395,   396,   163,    37,
      38,   397,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   166,   167,   168,   169,   170,   171,
     172,   173,     0,     0,   174,   175,     0,     0,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,     0,   192,   193,     0,     0,
       0,     0,     0,   194,   398,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,     0,
       0,     0,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,     0,     0,     0,     0,     0,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   284,   285,   164,   286,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,   192,   193,     0,     0,     0,     0,     0,
     194,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,     0,     0,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   237,     0,   164,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,   174,   175,     0,
       0,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,   192,
     193,     0,     0,     0,     0,     0,   194,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,     0,     0,     0,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,     0,     0,     0,     0,     0,   155,
     156,   157,   158,   159,   160,   161,   162,   163,     0,     0,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,   174,   175,     0,     0,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,   194,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,     0,     0,     0,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
       0,     0,     0,     0,     0,   155,   156,   157,   158,   159,
     160,   161,   162,   163,     0,     0,   164,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   166,
     167,   168,   169,   170,   171,   172,   173,     0,     0,   174,
     175,     0,     0,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
       0,   192,   193,     5,     6,     7,     0,     9,   194,     0,
       0,    10,    11,     0,     0,     0,    12,     0,    13,    14,
      15,   242,   243,    18,    19,     0,     0,     0,     0,     0,
     244,   245,   246,    23,    24,    25,    26,     0,     0,   203,
       0,     0,     0,     0,     0,     0,   272,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   273,
       0,     0,   206,    52,     0,    53,    54,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
     274,    10,    11,     0,     0,     0,    12,   275,    13,    14,
      15,   242,   243,    18,    19,     0,     0,     0,     0,     0,
     244,   245,   246,    23,    24,    25,    26,     0,     0,   203,
       0,     0,     0,     0,     0,     0,   272,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   273,
       0,     0,   206,    52,     0,    53,    54,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,     0,     0,
     274,    10,    11,     0,     0,     0,    12,   523,    13,    14,
      15,    16,    17,    18,    19,     0,     0,     0,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,     0,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,    51,    52,     0,    53,    54,     0,    55,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      65,    66,    67,    12,     0,    13,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,    20,    21,    22,
      23,    24,    25,    26,     0,     0,   203,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   204,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,   206,
      52,     0,    53,    54,     0,   207,   208,   209,    56,    57,
     210,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,     0,     0,     0,    10,    11,    65,   211,    67,
      12,     0,    13,    14,    15,    16,    17,    18,    19,     0,
       0,     0,     0,     0,    20,    21,    22,    23,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,     0,    28,
      29,     0,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    50,     0,     0,    51,    52,     0,    53,
      54,     0,    55,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,    66,    67,    12,     0,    13,
      14,    15,   242,   243,    18,    19,     0,     0,     0,     0,
       0,   244,   245,   246,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,   204,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   206,    52,     0,    53,    54,     0,   614,
     208,   209,    56,    57,   210,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,    65,   211,    67,    12,     0,    13,    14,    15,   242,
     243,    18,    19,     0,     0,     0,     0,     0,   244,   245,
     246,    23,    24,    25,    26,     0,     0,   203,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,   204,    41,    42,    43,
      44,     0,    45,    46,    47,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
     206,    52,     0,    53,    54,     0,   207,   208,     0,    56,
      57,   210,    59,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    65,   211,
      67,    12,     0,    13,    14,    15,   242,   243,    18,    19,
       0,     0,     0,     0,     0,   244,   245,   246,    23,    24,
      25,    26,     0,     0,   203,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,   204,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,   208,   209,    56,    57,   210,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,    65,   211,    67,    12,     0,
      13,    14,    15,   242,   243,    18,    19,     0,     0,     0,
       0,     0,   244,   245,   246,    23,    24,    25,    26,     0,
       0,   203,     0,     0,     0,     0,     0,     0,    29,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
     204,    41,    42,    43,    44,     0,    45,    46,    47,     0,
      48,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   205,     0,     0,   206,    52,     0,    53,    54,     0,
     614,   208,     0,    56,    57,   210,    59,    60,    61,    62,
      63,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     9,     0,     0,     0,
      10,    11,    65,   211,    67,    12,     0,    13,    14,    15,
     242,   243,    18,    19,     0,     0,     0,     0,     0,   244,
     245,   246,    23,    24,    25,    26,     0,     0,   203,     0,
       0,     0,     0,     0,     0,    29,     0,     0,    32,    33,
      34,    35,    36,    37,    38,    39,    40,   204,    41,    42,
      43,    44,     0,    45,    46,    47,     0,    48,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   205,     0,
       0,   206,    52,     0,    53,    54,     0,     0,   208,     0,
      56,    57,   210,    59,    60,    61,    62,    63,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     9,     0,     0,     0,    10,    11,    65,
     211,    67,    12,     0,    13,    14,    15,    16,    17,    18,
      19,     0,     0,     0,     0,     0,    20,    21,    22,    23,
      24,    25,    26,     0,     0,   203,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    32,    33,    34,    35,    36,
      37,    38,    39,    40,     0,    41,    42,    43,    44,     0,
      45,    46,    47,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   205,     0,     0,   206,    52,
       0,    53,    54,     0,   516,     0,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       9,     0,     0,     0,    10,    11,    65,   211,    67,    12,
       0,    13,    14,    15,   242,   243,    18,    19,     0,     0,
       0,     0,     0,   244,   245,   246,    23,    24,    25,    26,
       0,     0,   203,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    32,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,    43,    44,     0,    45,    46,    47,
       0,    48,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,   206,    52,     0,    53,    54,
       0,   207,     0,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,    65,   211,    67,    12,     0,    13,    14,
      15,   242,   243,    18,    19,     0,     0,     0,     0,     0,
     244,   245,   246,    23,    24,    25,    26,     0,     0,   203,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,    48,    49,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   205,
       0,     0,   206,    52,     0,    53,    54,     0,   821,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
      65,   211,    67,    12,     0,    13,    14,    15,   242,   243,
      18,    19,     0,     0,     0,     0,     0,   244,   245,   246,
      23,    24,    25,    26,     0,     0,   203,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   205,     0,     0,   206,
      52,     0,    53,    54,     0,   516,     0,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,    65,   211,    67,
      12,     0,    13,    14,    15,   242,   243,    18,    19,     0,
       0,     0,     0,     0,   244,   245,   246,    23,    24,    25,
      26,     0,     0,   203,     0,     0,     0,     0,     0,     0,
      29,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,     0,     0,   206,    52,     0,    53,
      54,     0,   614,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,    65,   211,    67,    12,     0,    13,
      14,    15,   242,   243,    18,    19,     0,     0,     0,     0,
       0,   244,   245,   246,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,    29,     0,     0,
      32,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,    48,
      49,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,     0,     0,   206,    52,     0,    53,    54,     0,     0,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,    65,   211,    67,    12,     0,    13,    14,    15,    16,
      17,    18,    19,     0,     0,     0,     0,     0,    20,    21,
      22,    23,    24,    25,    26,     0,     0,   203,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    32,    33,    34,
      35,    36,    37,    38,    39,    40,     0,    41,    42,    43,
      44,     0,    45,    46,    47,     0,    48,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
     206,    52,     0,    53,    54,     0,     0,     0,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,    65,   211,
      67,    12,     0,    13,    14,    15,    16,    17,    18,    19,
       0,     0,     0,     0,     0,    20,    21,    22,    23,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,     0,
       0,    29,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,     0,     0,   206,    52,     0,
      53,    54,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     9,
       0,     0,     0,    10,    11,    65,    66,    67,    12,     0,
      13,    14,    15,   242,   243,    18,    19,     0,     0,     0,
       0,     0,   244,   245,   246,    23,    24,    25,    26,     0,
       0,   203,     0,     0,     0,     0,     0,     0,   272,     0,
       0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
       0,    41,    42,    43,    44,     0,    45,    46,    47,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   273,     0,     0,   326,    52,     0,    53,    54,     0,
     327,     0,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     9,     0,     0,     0,    10,    11,     0,     0,
       0,    12,   274,    13,    14,    15,   242,   243,    18,    19,
       0,     0,     0,     0,     0,   244,   245,   246,    23,    24,
      25,    26,     0,     0,   203,     0,     0,     0,     0,     0,
       0,   272,     0,     0,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    41,    42,    43,    44,     0,    45,
      46,    47,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   370,     0,     0,    51,    52,     0,
      53,    54,     0,    55,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     0,     9,     0,     0,     0,    10,
      11,     0,     0,     0,    12,   274,    13,    14,    15,   242,
     243,    18,    19,     0,     0,     0,     0,     0,   244,   245,
     246,    23,    24,    25,    26,     0,     0,   203,     0,     0,
       0,     0,     0,     0,   272,     0,     0,    32,    33,    34,
     378,    36,    37,    38,   379,    40,     0,    41,    42,    43,
      44,     0,    45,    46,    47,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,     0,     0,   381,     0,     0,
     206,    52,     0,    53,    54,     0,     0,     0,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     9,     0,
       0,     0,    10,    11,     0,     0,     0,    12,   274,    13,
      14,    15,   242,   243,    18,    19,     0,     0,     0,     0,
       0,   244,   245,   246,    23,    24,    25,    26,     0,     0,
     203,     0,     0,     0,     0,     0,     0,   272,     0,     0,
      32,    33,    34,   378,    36,    37,    38,   379,    40,     0,
      41,    42,    43,    44,     0,    45,    46,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     381,     0,     0,   206,    52,     0,    53,    54,     0,     0,
       0,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       0,     9,     0,     0,     0,    10,    11,     0,     0,     0,
      12,   274,    13,    14,    15,   242,   243,    18,    19,     0,
       0,     0,     0,     0,   244,   245,   246,    23,    24,    25,
      26,     0,     0,   203,     0,     0,     0,     0,     0,     0,
     272,     0,     0,    32,    33,    34,    35,    36,    37,    38,
      39,    40,     0,    41,    42,    43,    44,     0,    45,    46,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   273,     0,     0,   326,    52,     0,    53,
      54,     0,     0,     0,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     9,     0,     0,     0,    10,    11,
       0,     0,     0,    12,   274,    13,    14,    15,   242,   243,
      18,    19,     0,     0,     0,     0,     0,   244,   245,   246,
      23,    24,    25,    26,     0,     0,   203,     0,     0,     0,
       0,     0,     0,   272,     0,     0,    32,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,    43,    44,
       0,    45,    46,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   901,     0,     0,   206,
      52,     0,    53,    54,     0,     0,     0,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     0,     9,     0,     0,
       0,    10,    11,     0,     0,     0,    12,   274,    13,    14,
      15,   242,   243,    18,    19,     0,     0,     0,     0,     0,
     244,   245,   246,    23,    24,    25,    26,     0,     0,   203,
       0,     0,     0,     0,     0,     0,   272,     0,     0,    32,
      33,    34,    35,    36,    37,    38,    39,    40,     0,    41,
      42,    43,    44,     0,    45,    46,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   979,
       0,     0,   206,    52,     0,    53,    54,     0,     0,     0,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
       0,     0,     0,     0,     0,   566,   567,     0,     0,   568,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     274,   165,   166,   167,   168,   169,   170,   171,   172,   173,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,     0,   192,   193,   603,   567,     0,     0,
     604,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,   174,   175,     0,     0,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,   618,   559,     0,
       0,   619,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   165,   166,   167,   168,   169,   170,   171,
     172,   173,     0,     0,   174,   175,     0,     0,   176,   177,
     178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,     0,   192,   193,   621,   567,
       0,     0,   622,   194,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,   170,
     171,   172,   173,     0,     0,   174,   175,     0,     0,   176,
     177,   178,   179,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,     0,   192,   193,   645,
     559,     0,     0,   646,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   165,   166,   167,   168,   169,
     170,   171,   172,   173,     0,     0,   174,   175,     0,     0,
     176,   177,   178,   179,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,     0,   192,   193,
     648,   567,     0,     0,   649,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   165,   166,   167,   168,
     169,   170,   171,   172,   173,     0,     0,   174,   175,     0,
       0,   176,   177,   178,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,     0,   192,
     193,   734,   559,     0,     0,   735,   194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   165,   166,   167,
     168,   169,   170,   171,   172,   173,     0,     0,   174,   175,
       0,     0,   176,   177,   178,   179,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,     0,
     192,   193,   737,   567,     0,     0,   738,   194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   166,
     167,   168,   169,   170,   171,   172,   173,     0,     0,   174,
     175,     0,     0,   176,   177,   178,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
       0,   192,   193,   743,   559,     0,     0,   744,   194,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   165,
     166,   167,   168,   169,   170,   171,   172,   173,     0,     0,
     174,   175,     0,     0,   176,   177,   178,   179,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,     0,   192,   193,  1014,   559,     0,     0,  1015,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     165,   166,   167,   168,   169,   170,   171,   172,   173,     0,
       0,   174,   175,     0,     0,   176,   177,   178,   179,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,     0,   192,   193,  1047,   559,     0,     0,  1048,
     194,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   165,   166,   167,   168,   169,   170,   171,   172,   173,
       0,     0,   174,   175,     0,     0,   176,   177,   178,   179,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,     0,   192,   193,  1050,   567,     0,     0,
    1051,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   170,   171,   172,
     173,     0,     0,   174,   175,     0,     0,   176,   177,   178,
     179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   180,   181,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,     0,     0,   343,
     344,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,     0,   192,   193,     0,     0,     0,
       0,     0,   194,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   345,     0,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   235
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-825))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-635))

static const yytype_int16 yycheck[] =
{
       2,    98,    69,    86,    57,     2,   364,     4,    81,    66,
     224,    22,    16,    17,    97,   358,    20,   426,     8,    16,
      17,    76,    28,    20,   329,    92,    89,     8,    27,    92,
      29,   418,   620,   329,   477,   580,    55,   597,    28,   426,
       8,     4,   676,    96,   579,   381,     2,    28,     4,    92,
      51,    53,    54,   266,    51,   464,    69,   270,    55,   647,
      28,    55,    81,   692,   791,    76,   878,    16,    17,    66,
      27,    20,   446,    65,    93,    94,    95,    16,    17,   422,
     473,    20,   234,   722,    81,    25,   910,   726,    26,    57,
     512,    88,    89,   515,   663,    92,    93,    94,    95,   357,
      25,   906,   360,    25,    53,    29,    13,   259,    88,    63,
     262,   876,   254,   782,    53,    54,    78,    88,    89,     0,
      63,    92,    16,    17,   779,    90,    20,    88,    96,    63,
     523,   710,   475,    25,    25,   140,   219,    88,   717,    25,
     145,   117,    13,   143,   657,    54,   404,    88,   736,   804,
      87,    88,   117,   782,   145,    13,    65,    66,   746,   113,
     122,   137,   791,   421,   144,   423,   249,   110,   142,   112,
     678,   145,   680,    37,    38,    13,   810,   811,   943,   113,
      37,    38,   742,   144,   326,   142,    26,   999,   145,   256,
     114,   449,   247,   144,    13,   278,   134,   137,  1022,   139,
     143,   139,   275,   144,   134,  1010,   290,   144,   292,   206,
     294,    56,   137,   256,   298,   137,   218,   139,   476,   628,
     663,   435,   224,   950,   228,   143,   230,   231,    13,   231,
     899,   228,   139,   230,   231,   142,  1001,   234,   145,   236,
     627,   628,   585,   256,   241,   137,   137,   310,   311,   312,
     313,   137,   595,   254,   888,   252,   275,   254,   594,    13,
     773,   774,    51,   234,   638,   236,   263,   324,  1033,    13,
     899,   142,   329,   272,   145,   697,   428,   906,   275,   228,
     432,   230,   274,    13,   142,   437,   955,   145,   145,   228,
     373,   230,   263,   932,   134,   864,   252,   866,   858,   137,
     367,   453,   365,   366,   142,   865,   143,   145,   327,   143,
     703,    13,   309,   310,   311,   312,   313,   314,   315,   316,
     139,   950,   857,   142,   367,   326,   145,   324,   586,   326,
     327,   415,   329,   327,   228,   969,   230,    13,   596,   310,
     311,   312,   313,    88,   315,   316,   309,   117,  1017,    88,
     407,   408,    25,   309,   358,    25,   358,   142,   314,   137,
     145,   358,    25,   876,   361,   878,    88,   145,   365,   366,
     522,    88,   477,    28,   732,   324,   137,   885,   886,    88,
     329,  1010,   890,   380,   892,   137,   894,   932,   142,    70,
     100,   145,   360,   145,   365,   366,   139,    90,   142,   144,
     473,   145,   145,   617,    88,   144,   490,    90,   704,   380,
     407,   408,   142,   497,   124,   145,   721,   206,   422,   117,
     422,   864,   144,   866,   117,   422,    25,   144,   103,   642,
     943,   944,   434,   435,   117,   144,   404,   443,   998,    90,
     142,    25,   137,   145,   446,    90,   127,   128,   129,   446,
     523,   139,   241,   443,   473,   423,    63,    87,    88,   456,
     144,  1049,   443,   872,   137,   254,   142,   137,    15,   145,
      17,   475,   117,   475,   137,   443,   473,    25,   475,   418,
      52,   449,    87,    88,    56,   872,   999,    25,  1001,   641,
     446,    52,   137,    54,    55,    56,    57,  1005,  1006,  1007,
    1008,    56,   117,   110,   523,   112,   136,   562,   476,   511,
     512,   578,   579,   515,   144,   570,   137,    91,   117,   692,
    1033,   137,   461,    90,   145,    52,   523,    54,    55,    56,
      57,   136,    90,   117,   139,   137,   143,   326,   137,   144,
     139,   140,   139,    58,   692,    90,   145,   134,   547,  1057,
     605,   765,   563,   137,   139,    70,   140,   139,   663,   117,
     571,   145,   920,    14,    15,   692,   565,    70,   926,   117,
     643,   573,   117,   117,    87,    88,   137,   140,   575,   117,
     577,   585,   141,   585,    99,   100,    63,   692,   585,   137,
      67,   595,   140,   595,   605,    90,   748,   145,   595,   137,
     597,   598,   140,   605,   610,    87,    88,   145,    56,   124,
     137,   135,   785,   113,   766,   617,   789,   137,   586,   113,
     610,   620,   117,   136,   643,   777,    90,   598,   596,   610,
     703,   144,   581,   110,   631,   112,   638,   785,    90,   113,
     113,   638,   610,    87,    88,    70,   643,   704,   647,   137,
     707,   708,    97,   117,   136,   752,   711,   714,   715,    17,
     631,   142,   144,   718,   791,   117,    56,   794,    25,   582,
     140,   121,   674,   740,   676,   137,   739,   782,   741,   137,
     135,   134,   638,  1026,   703,   137,   791,   143,   627,    87,
      88,   137,   136,   692,    90,   697,   693,   750,   137,   696,
     144,   698,    54,    55,   137,    57,   703,   704,   143,   137,
     707,   708,   117,    65,    66,   137,   718,   714,   715,   721,
     722,   117,   724,   875,   726,   139,   899,    10,    63,     8,
     903,    13,   135,   906,     2,   908,     4,   736,   136,   117,
      90,   137,   739,   137,   741,   742,   144,   746,    16,    17,
     137,   899,    20,    87,    88,   903,    52,    70,   906,   864,
     908,   866,   137,   765,   692,   137,    52,   117,   739,  1027,
     741,   137,   721,   137,    52,   110,   833,   112,   113,   906,
     779,   908,   750,    51,   847,   937,   575,   137,   577,   808,
     857,   119,   859,   141,   899,    15,   139,   137,    66,    87,
      88,   906,   136,    87,    88,   804,   135,   137,   810,   811,
     144,   808,   125,   126,   127,   128,   129,   122,   731,   117,
      88,    89,   819,   950,    92,   952,    90,   137,    63,   137,
     957,    87,    88,   137,   747,    26,   833,  1010,   137,  1012,
     842,   142,    10,   845,  1017,   950,  1019,   844,   136,    10,
     847,    91,   136,   117,   851,   852,   144,   137,   855,   135,
     144,   858,  1010,     9,  1012,   137,    87,    88,   865,  1017,
      63,  1019,   939,   137,   140,   110,   847,   112,   113,   898,
     136,    90,    63,  1010,   137,  1012,   888,  1060,   144,    90,
     137,   137,  1019,   137,   122,    26,    87,    88,   981,    56,
     919,   898,   135,   137,   693,  1010,   137,   696,   117,   698,
    1037,   137,  1060,   813,   814,   136,   117,   110,   137,   112,
     113,   137,   919,   144,   137,   137,   923,    10,   137,   110,
     932,   112,   113,  1060,   115,   848,   137,   850,   206,    56,
      87,    88,   137,   134,   111,   136,   135,   860,   139,   139,
     947,   948,   139,   144,   137,   456,    87,    88,    87,    88,
     228,    93,   230,   231,  1029,    95,   234,   969,   236,   718,
     773,   899,   692,   241,  1022,   903,   975,    70,   906,   753,
     908,  1028,   101,   298,   252,   210,   254,    59,   985,   136,
     987,    96,    85,    86,   940,   263,   993,   144,   785,   903,
     899,   998,    63,   134,    -1,   136,   782,   136,   139,    -1,
      -1,    -1,  1009,   144,    -1,   144,   929,   930,    87,    88,
      -1,   934,  1026,    -1,  1026,   938,  1028,  1029,    -1,  1026,
     819,   124,   125,   126,   127,   128,   129,    -1,    26,    -1,
      -1,   309,   310,   311,   312,   313,   314,   315,   316,   110,
    1049,   112,   113,    -1,    63,   844,   324,    -1,   326,  1027,
      -1,   329,   851,   852,   964,   965,   855,   136,    -1,    -1,
     970,    -1,   972,   973,    -1,   144,    -1,    16,    17,    -1,
      -1,    20,  1010,    52,  1012,    54,    55,    56,    57,  1017,
     358,  1019,    -1,   361,    -1,    -1,    -1,   365,   366,    87,
      88,   110,    -1,   112,   113,    70,    -1,    -1,    -1,    48,
      49,    -1,   380,    -1,    53,    54,    -1,  1030,  1031,    -1,
      85,    86,    -1,    92,    -1,    -1,    -1,    66,    67,    98,
      -1,    -1,  1060,    52,   923,    54,    55,    56,    57,   407,
     408,    -1,  1042,  1043,  1044,  1045,   134,    -1,   136,    -1,
      -1,   139,    -1,    -1,   422,    -1,   144,    -1,   947,   948,
     125,   126,   127,   128,   129,    -1,  1066,    -1,    52,    -1,
      54,    55,    56,    57,    58,    -1,    -1,    52,   446,    54,
      55,    56,    57,    58,    -1,    -1,    70,    -1,   456,    40,
      41,    42,    43,    44,    -1,    70,   985,    -1,   987,    -1,
      44,    -1,    -1,    -1,   993,    -1,    -1,   475,    92,    59,
      60,    61,    62,    -1,    98,    99,   100,    92,    -1,    -1,
    1009,    -1,    -1,    98,    99,   100,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    -1,
     124,    85,    86,   127,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,   127,    -1,    -1,    -1,    -1,     2,    -1,     4,
      -1,   145,    -1,    -1,   139,   204,    -1,    -1,   207,   208,
     209,    -1,   211,    -1,   118,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,    -1,    -1,     2,   228,
       4,   230,   231,   137,    52,    -1,    54,    55,    56,    57,
      70,    -1,    -1,    -1,    -1,    -1,    51,   575,    -1,   577,
      55,    -1,    -1,    -1,    -1,    85,    86,   585,    -1,    -1,
      52,    -1,    54,    55,    56,    57,    -1,   595,    -1,   597,
     598,    -1,    -1,    -1,    92,    -1,    81,    51,    -1,    -1,
      98,    55,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,
      95,    96,   122,   123,   124,   125,   126,   127,   128,   129,
      92,    -1,    -1,   631,    -1,    -1,    -1,    81,    -1,    -1,
     638,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      94,    95,    96,    -1,    -1,   324,    -1,    -1,    -1,    -1,
     329,   330,   331,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,    -1,    -1,   358,
      -1,    -1,    -1,    -1,    -1,   693,    -1,    -1,   696,    -1,
     698,    -1,    -1,    -1,    -1,    -1,   704,    -1,    -1,   707,
     708,    -1,    -1,    -1,    -1,    -1,   714,   715,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    54,    55,    56,    57,
      58,   206,    -1,    -1,    -1,    -1,    -1,    -1,   407,   408,
      -1,   739,    70,   741,   742,    -1,    -1,   416,   417,   418,
      -1,    -1,    -1,   422,    -1,   424,   425,   426,    -1,    -1,
      -1,    -1,   206,    -1,    92,    -1,   241,    -1,    -1,    -1,
      98,    99,   100,    -1,    -1,    -1,   445,   252,    -1,   254,
      -1,   450,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   461,    -1,    -1,   464,   124,   241,    -1,   127,
     275,    -1,    -1,    -1,    -1,    -1,   475,    -1,   252,    -1,
     254,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   819,    -1,    -1,    52,    -1,    54,    55,    56,    57,
      58,   275,   501,    -1,   309,   833,    -1,    -1,    -1,   314,
      -1,    -1,    70,    -1,    -1,    -1,   844,   516,    -1,   847,
      -1,   326,   327,   851,   852,    -1,    -1,   855,    -1,    -1,
     858,    -1,    -1,    -1,    92,   309,     2,   865,     4,    -1,
     314,    99,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   326,   327,    -1,     2,   361,     4,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   581,    -1,    -1,    51,   585,   361,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   923,   595,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,   611,    -1,    -1,   614,    -1,    -1,    -1,   947,
     948,    -1,    -1,    -1,    -1,    -1,    -1,    93,   627,   628,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    -1,
      -1,   446,    -1,    -1,    -1,    -1,    93,    94,    95,    -1,
      -1,   456,    -1,     2,    -1,     4,    -1,   985,    -1,   987,
      -1,    -1,    -1,    -1,    -1,   993,    -1,    -1,   473,    -1,
     998,    -1,   446,   672,    70,    71,    72,    73,    74,    75,
      76,  1009,   456,    79,    80,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1026,   473,
      -1,   700,    51,    -1,    -1,   704,   705,    -1,   707,   708,
      -1,    -1,    -1,    -1,    -1,   714,   715,    -1,   523,    -1,
      -1,    -1,   721,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   523,
      -1,    -1,    -1,    -1,    -1,    -1,   755,    -1,    -1,   206,
      -1,   760,   761,    -1,   763,   764,    -1,    -1,    -1,    -1,
     575,    -1,   577,    -1,    -1,   241,    -1,    -1,    -1,    -1,
      -1,    -1,   781,    -1,    -1,    -1,   252,    -1,   254,    -1,
      -1,    54,   597,    -1,   241,    -1,    -1,    -1,    -1,    -1,
      -1,   575,    -1,   577,    -1,   252,    -1,   254,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   821,   597,    -1,    -1,   825,    -1,   275,    -1,
      -1,    -1,    -1,   638,   833,    -1,    -1,    -1,   643,    -1,
      -1,    -1,    -1,   309,    -1,    -1,    -1,    -1,   314,    -1,
      -1,    -1,    -1,    -1,    -1,   854,    -1,   206,    -1,    -1,
     326,    -1,   309,   329,   638,    -1,    -1,   314,    -1,   643,
      -1,    -1,   871,   872,    -1,    -1,    -1,    -1,    -1,   326,
     327,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   693,    -1,
      -1,   696,   241,   698,    -1,   361,    -1,    -1,   703,    -1,
      -1,    -1,    -1,   252,    -1,   254,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   361,    -1,    -1,    -1,    -1,   693,
      -1,    -1,   696,    -1,   698,    -1,    -1,    -1,    -1,   703,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   742,    -1,    -1,
      -1,   204,    -1,    -1,   207,   208,   209,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     309,    -1,    -1,    -1,    -1,   314,    -1,    -1,   742,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   326,    -1,    -1,
     446,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     456,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   446,
      -1,    -1,    -1,   808,    -1,    -1,    -1,    -1,    -1,   456,
      -1,    -1,   361,    -1,   819,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   473,  1026,    -1,    -1,
      -1,    -1,    -1,    -1,   808,    -1,    -1,    -1,    -1,   844,
      -1,    -1,    -1,    -1,    -1,   819,   851,   852,    -1,    -1,
     855,    -1,    -1,   858,    -1,    -1,    -1,    -1,    -1,    -1,
     865,   324,    -1,    -1,    -1,    -1,   329,    -1,    -1,    -1,
     844,    -1,    -1,    -1,    -1,    -1,   523,   851,   852,    -1,
      -1,   855,    -1,    -1,   858,    -1,    -1,    -1,    -1,    -1,
      -1,   865,    -1,   898,    -1,    -1,    -1,   446,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   456,    -1,   575,
      -1,   577,    -1,    -1,   919,    -1,    -1,    -1,   923,    -1,
      -1,    -1,    -1,    -1,   898,    -1,    -1,    -1,   575,    -1,
     577,   597,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   947,   948,    -1,   919,    -1,    -1,    -1,   923,
     597,    -1,    -1,    -1,   417,   418,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   426,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   638,   947,   948,    -1,    -1,    -1,    -1,    -1,
     985,    -1,   987,    -1,    -1,    -1,    -1,    -1,   993,    -1,
      -1,   638,    -1,   998,    -1,    -1,   643,    -1,   461,    -1,
      -1,   464,    -1,    -1,  1009,    -1,    -1,    -1,    -1,    -1,
      -1,   985,    -1,   987,    -1,    -1,    -1,    -1,    -1,   993,
      -1,    -1,    -1,    -1,   998,    -1,   575,   693,   577,    -1,
     696,    -1,   698,    -1,    -1,  1009,    -1,   684,   704,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   693,    -1,   597,   696,
      -1,   698,    -1,   516,    -1,    -1,   703,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   742,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   638,
      -1,    -1,    -1,    -1,    -1,   742,     0,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     8,     9,    10,    -1,    -1,    13,
      14,    15,    -1,    17,    -1,    -1,    -1,    -1,   581,    -1,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    -1,   693,    -1,    -1,   696,   611,   698,
      -1,   614,    -1,   819,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   808,    -1,    -1,   627,   628,    -1,    -1,    -1,    -1,
      -1,    -1,   819,    -1,    -1,    -1,    -1,    -1,   844,    -1,
      -1,    -1,    -1,    87,    88,   851,   852,    -1,    -1,   855,
      -1,    -1,   858,   742,    -1,    -1,    -1,   844,    -1,   865,
      -1,    -1,    -1,    -1,   851,   852,    -1,   111,   855,   672,
      -1,   858,    -1,    -1,    -1,    -1,    -1,    -1,   865,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     134,   135,    -1,    -1,    -1,   139,   140,   700,   142,    -1,
     144,   145,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   898,    -1,   919,    -1,    -1,    -1,   923,   721,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     819,    -1,   919,    -1,    -1,    -1,   923,    -1,    -1,    -1,
      -1,   947,   948,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   844,    -1,    -1,    -1,    -1,
     947,   948,   851,   852,    -1,    -1,   855,    -1,    -1,   858,
      -1,    -1,    -1,    -1,    -1,    -1,   865,    -1,   781,   985,
      -1,   987,    -1,    -1,    -1,    -1,    -1,   993,    -1,    -1,
      -1,    -1,   998,    -1,    -1,    -1,    -1,    -1,   985,    -1,
     987,    -1,    -1,  1009,    -1,    -1,   993,    -1,    52,    53,
      -1,   998,    56,    -1,    -1,    -1,    -1,    -1,   821,    -1,
      -1,    -1,  1009,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,   923,    79,    80,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   854,    -1,    -1,    98,    99,    -1,    -1,   947,   948,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   872,
      -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,    -1,   131,   132,    -1,
      -1,    -1,    -1,    -1,   138,    -1,   985,    -1,   987,    -1,
      -1,    -1,    -1,    -1,   993,    -1,    -1,     0,     1,   998,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    11,    12,
    1009,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,   109,     0,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,    -1,
      13,    14,    15,    -1,    17,    -1,    -1,   130,   131,   132,
      -1,    44,    -1,    26,    27,    28,    29,    -1,    -1,   142,
      -1,    -1,   145,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    87,    88,    -1,    90,    91,    -1,
      -1,    -1,    -1,    -1,    97,   118,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,   111,    -1,
      -1,   114,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
      -1,   134,   135,   136,   137,     0,    -1,   140,   141,   142,
      -1,   144,   145,     8,     9,    10,    -1,    -1,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      25,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,    86,    87,    88,    -1,    90,    91,    -1,    -1,    -1,
      -1,   118,    97,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,   111,    -1,    -1,   114,
      -1,    -1,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,
     135,   136,   137,     0,    -1,   140,   141,   142,    -1,   144,
     145,     8,     9,    10,    -1,    -1,    13,    14,    15,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      87,    88,    -1,    90,    91,    -1,    -1,    -1,    -1,   118,
      97,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,    -1,    -1,   111,    -1,    -1,   114,    -1,    -1,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,   135,   136,
     137,     0,    -1,   140,   141,   142,    -1,   144,   145,     8,
       9,    10,    -1,    -1,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    97,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,   111,    -1,    -1,   114,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,    -1,    -1,    -1,   134,   135,   136,   137,     0,
      -1,   140,   141,   142,    -1,   144,   145,     8,     9,    10,
      -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    79,    80,    -1,    -1,
      -1,    -1,    85,    86,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
     111,    -1,    -1,   114,    -1,    -1,    -1,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,   134,   135,   136,   137,     0,    -1,   140,
     141,   142,    -1,   144,   145,     8,     9,    10,    -1,    -1,
      13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    87,    88,    -1,    90,    91,    -1,
      -1,    -1,    -1,    -1,    97,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,   111,    -1,
      -1,   114,    -1,    -1,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
      -1,    -1,   135,   136,   137,     0,    -1,   140,   141,   142,
      -1,   144,   145,     8,     9,    10,    -1,    -1,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,    86,    87,    88,    -1,    -1,    91,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,
      -1,    -1,    -1,   118,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,    -1,   134,
     135,   136,   137,     0,   139,   140,   141,   142,    -1,   144,
     145,     8,     9,    10,    -1,    -1,    13,    14,    15,    -1,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,    85,    86,
      87,    88,    -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,
      97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,   114,    -1,    -1,
      -1,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,    -1,    -1,    -1,    -1,   135,   136,
     137,     0,    -1,   140,   141,   142,    -1,   144,   145,     8,
       9,    10,    -1,    -1,    13,    14,    15,    -1,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    -1,    85,    86,    87,    88,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,    -1,   118,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,    -1,    -1,    -1,   134,   135,   136,   137,     0,
     139,   140,   141,   142,    -1,   144,   145,     8,     9,    10,
      -1,    -1,    13,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    -1,    -1,    85,    86,    87,    88,    -1,    -1,
      91,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     111,    -1,    -1,    -1,    -1,    -1,    -1,   118,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
      -1,    -1,    -1,    -1,   135,   136,   137,     0,   139,   140,
     141,   142,    -1,   144,   145,     8,     9,    10,    -1,    -1,
      -1,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      -1,    -1,    85,    86,    87,    88,    -1,    90,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,
      -1,    -1,    -1,    -1,   117,   118,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,    -1,    -1,
      -1,   134,   135,   136,   137,     0,    -1,   140,    -1,   142,
      -1,   144,   145,     8,     9,    10,    -1,    -1,    -1,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    -1,
      85,    86,    87,    88,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,
      -1,    -1,   117,   118,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,
     135,   136,   137,    -1,    -1,   140,    -1,   142,    -1,   144,
     145,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    -1,    -1,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     130,   131,   132,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,     1,   145,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,    -1,    14,    15,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,   131,   132,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,     1,   145,     3,
       4,     5,     6,     7,    -1,    -1,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,   131,   132,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
       1,   145,     3,     4,     5,     6,     7,    -1,    -1,    10,
      11,    12,    -1,    -1,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    -1,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,    -1,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,   130,
     131,   132,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,   142,    -1,    -1,   145,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    12,   130,   131,   132,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,   142,    -1,
      -1,   145,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   130,   131,   132,     1,    -1,     3,     4,
       5,     6,     7,   140,    -1,   142,    11,    12,   145,    -1,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   130,   131,   132,     1,    -1,
       3,     4,     5,     6,     7,   140,    -1,   142,    11,    12,
     145,    -1,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   130,   131,   132,
      -1,    -1,   135,    -1,    -1,    -1,    -1,    -1,    -1,   142,
      -1,     1,   145,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     130,   131,   132,    -1,    -1,   135,    -1,    -1,    -1,    -1,
      -1,    -1,   142,    -1,     1,   145,     3,     4,     5,     6,
       7,    -1,    -1,    10,    11,    12,    -1,    -1,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,   130,   131,   132,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,   142,    -1,    -1,   145,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     130,   131,   132,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,   142,    -1,    -1,   145,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   130,   131,   132,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,   145,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   130,   131,   132,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,   142,    -1,    -1,   145,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,   130,   131,   132,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,   145,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    -1,    11,    12,   130,   131,
     132,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
     142,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   130,   131,   132,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,   131,   132,    -1,    -1,
      -1,    -1,    -1,   138,   139,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    80,    -1,    -1,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,    -1,   131,   132,    -1,    -1,    -1,    -1,    -1,
     138,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,    -1,
      -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,    -1,
     102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    -1,   131,
     132,    -1,    -1,    -1,    -1,    -1,   138,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    99,    -1,    -1,   102,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,   131,   132,    -1,    -1,    -1,
      -1,    -1,   138,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
      -1,   131,   132,     3,     4,     5,    -1,     7,   138,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
     130,    11,    12,    -1,    -1,    -1,    16,   137,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
     130,    11,    12,    -1,    -1,    -1,    16,   137,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     130,   131,   132,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    12,   130,   131,   132,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      46,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,    -1,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   130,   131,   132,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   130,   131,   132,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    98,    99,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   130,   131,
     132,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   130,   131,   132,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    -1,    64,    65,    66,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    99,    -1,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,
      11,    12,   130,   131,   132,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    -1,    64,    65,    66,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,
      -1,    92,    93,    -1,    95,    96,    -1,    -1,    99,    -1,
     101,   102,   103,   104,   105,   106,   107,   108,   109,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,   130,
     131,   132,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    62,    -1,
      64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,
      -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
       7,    -1,    -1,    -1,    11,    12,   130,   131,   132,    16,
      -1,    18,    19,    20,    21,    22,    23,    24,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    -1,    59,    60,    61,    62,    -1,    64,    65,    66,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,
      -1,    98,    -1,    -1,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,   130,   131,   132,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    98,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
     130,   131,   132,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    98,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,   130,   131,   132,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    98,    -1,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,   130,   131,   132,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,   130,   131,   132,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,   130,   131,
     132,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    -1,    -1,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    -1,    11,    12,   130,   131,   132,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    -1,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    62,    -1,    64,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,
      98,    -1,    -1,   101,   102,   103,   104,   105,   106,   107,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,    -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    16,   130,    18,    19,    20,    21,    22,    23,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    -1,    59,    60,    61,    62,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,
      95,    96,    -1,    98,    -1,    -1,   101,   102,   103,   104,
     105,   106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    16,   130,    18,    19,    20,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    -1,    59,    60,    61,
      62,    -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    89,    -1,    -1,
      92,    93,    -1,    95,    96,    -1,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,   109,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,   130,    18,
      19,    20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    62,    -1,    64,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      89,    -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,
      -1,    -1,   101,   102,   103,   104,   105,   106,   107,   108,
     109,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,   130,    18,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      36,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    -1,    59,    60,    61,    62,    -1,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    89,    -1,    -1,    92,    93,    -1,    95,
      96,    -1,    -1,    -1,    -1,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    16,   130,    18,    19,    20,    21,    22,
      23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    62,
      -1,    64,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    92,
      93,    -1,    95,    96,    -1,    -1,    -1,    -1,   101,   102,
     103,   104,   105,   106,   107,   108,   109,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,    -1,     7,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,   130,    18,    19,
      20,    21,    22,    23,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    -1,    59,
      60,    61,    62,    -1,    64,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    89,
      -1,    -1,    92,    93,    -1,    95,    96,    -1,    -1,    -1,
      -1,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      -1,    -1,    -1,    -1,    -1,    52,    53,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     130,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    52,    53,    -1,    -1,
      56,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,   131,   132,    52,    53,    -1,
      -1,    56,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    99,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,    -1,   131,   132,    52,    53,
      -1,    -1,    56,   138,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    99,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,    -1,   131,   132,    52,
      53,    -1,    -1,    56,   138,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    -1,    79,    80,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,    -1,   131,   132,
      52,    53,    -1,    -1,    56,   138,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    79,    80,    -1,
      -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,    -1,   131,
     132,    52,    53,    -1,    -1,    56,   138,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    79,    80,
      -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,    -1,
     131,   132,    52,    53,    -1,    -1,    56,   138,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    79,
      80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
      -1,   131,   132,    52,    53,    -1,    -1,    56,   138,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      79,    80,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,    -1,   131,   132,    52,    53,    -1,    -1,    56,   138,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    80,    -1,    -1,    83,    84,    85,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,    -1,   131,   132,    52,    53,    -1,    -1,    56,
     138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,    -1,   131,   132,    52,    53,    -1,    -1,
      56,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    79,    80,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    99,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    85,
      86,    -1,    -1,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,   131,   132,    -1,    -1,    -1,
      -1,    -1,   138,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,    -1,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   147,   148,     0,     1,     3,     4,     5,     6,     7,
      11,    12,    16,    18,    19,    20,    21,    22,    23,    24,
      30,    31,    32,    33,    34,    35,    36,    39,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    59,    60,    61,    62,    64,    65,    66,    68,    69,
      89,    92,    93,    95,    96,    98,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   130,   131,   132,   149,   150,
     151,   158,   160,   161,   163,   164,   167,   168,   169,   171,
     172,   173,   175,   176,   186,   201,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   257,   258,   272,
     273,   274,   275,   276,   277,   278,   281,   283,   284,   298,
     300,   301,   302,   303,   304,   305,   306,   307,   341,   354,
     151,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    56,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    79,    80,    83,    84,    85,    86,
      98,    99,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   131,   132,   138,   179,   180,   181,   182,   184,
     185,   298,   300,    39,    58,    89,    92,    98,    99,   100,
     103,   131,   168,   176,   186,   188,   193,   196,   198,   220,
     303,   304,   306,   307,   339,   340,   193,   193,   139,   194,
     195,   139,   190,   194,   139,   145,   348,    54,   181,   348,
     152,   134,    21,    22,    30,    31,    32,   167,   186,   220,
     186,    56,     1,    47,    92,   154,   155,   156,   158,   170,
     171,   354,   203,   204,   189,   198,   339,   354,   188,   338,
     339,   354,    46,    89,   130,   137,   175,   201,   220,   303,
     304,   307,   248,   249,    54,    55,    57,   179,   288,   299,
     287,   288,   289,   143,   279,   143,   285,   143,   282,   143,
     286,   302,   163,   186,   186,   142,   145,   347,   352,   353,
      40,    41,    42,    43,    44,    37,    38,    26,   134,   190,
     194,   263,    28,   255,   117,   137,    92,    98,   172,   117,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    85,    86,   118,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,    87,    88,   136,   144,
     345,   202,   161,   162,   162,   207,   209,   162,   347,   353,
      89,   169,   176,   220,   236,   303,   304,   307,    52,    56,
      85,    89,   177,   178,   220,   303,   304,   307,   178,    33,
      34,    35,    36,    49,    50,    51,    52,    56,   139,   179,
     305,   336,    88,   345,   346,   263,   275,    90,    90,   137,
     188,    56,   188,   188,   188,   287,   117,    91,   137,   197,
     354,    88,   136,   345,    90,    90,   137,   197,   193,   348,
     349,   193,   192,   193,   198,   339,   354,   161,   349,   161,
      54,    65,    66,   159,   139,   187,   134,   154,    88,   345,
      90,   158,   157,   170,   140,   347,   353,   349,   349,   161,
     141,   137,   145,   351,   137,   351,   135,   351,   348,    56,
     302,   172,   174,   137,    88,   136,   345,   250,    63,   110,
     112,   113,   290,   113,   290,   113,    67,   290,   113,   113,
     280,   290,   113,    63,   113,   113,   113,   280,   113,    63,
     113,    70,   142,   151,   162,   162,   162,   162,   158,   161,
     161,   265,   264,    97,   165,   256,    98,   163,   188,   198,
     199,   200,   170,   137,   175,   137,   160,   163,   176,   186,
     188,   200,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,    52,    53,
      56,   184,   262,   342,   343,   192,    52,    53,    56,   184,
     261,   342,   153,   154,    13,   232,   352,   232,   162,   162,
     347,    17,   266,    56,    88,   136,   345,    25,   161,    52,
      56,   177,   121,   308,    88,   136,   345,   215,   337,   216,
      88,   144,   344,    52,    56,   342,   163,   186,   163,   186,
     183,   115,   186,   188,    98,   188,   196,   339,    52,    56,
     192,    52,    56,   340,   349,   140,   349,   137,   137,   349,
     181,   206,   186,   149,   135,   342,   342,   186,   134,   349,
     156,   205,   339,   137,   174,    52,    56,   192,    52,    56,
      52,    54,    55,    56,    57,    58,    70,    92,    98,    99,
     100,   124,   127,   139,   253,   312,   314,   315,   316,   317,
     318,   319,   320,   321,   324,   325,   326,   327,   330,   331,
     332,   333,   334,   292,   291,   143,   290,   143,   143,   143,
     186,    78,   122,   243,   244,   354,   243,   166,   243,   188,
     137,   349,   174,   137,   117,    44,   348,    90,    90,   190,
     194,   260,   348,   350,    90,    90,   190,   194,   259,    10,
     231,     8,   268,   354,   154,    13,   154,    27,   233,   352,
     233,   266,   198,   231,    52,    56,   192,    52,    56,   211,
     214,   309,   213,    52,    56,   177,   192,   153,   161,   217,
     218,   190,   191,   194,   354,    44,   181,   188,   188,   197,
      90,    90,   350,    90,    90,   339,   161,   135,   149,   349,
     351,   172,   350,    92,    98,   237,   238,   239,   316,   314,
     251,   117,   137,   313,   188,   137,   335,   354,    52,   137,
     335,   137,   313,    52,   137,   313,    52,   293,    54,    55,
      57,   297,   307,   240,   242,   245,   317,   319,   320,   322,
     323,   326,   328,   329,   332,   334,   348,   154,   154,   243,
     154,    98,   188,   174,   186,   119,   163,   186,   163,   186,
     165,   190,   141,    90,   163,   186,   163,   186,   165,   191,
     188,   200,   269,   354,    15,   235,   354,    14,   234,   235,
     235,   208,   210,   231,   137,   232,   350,   162,   352,   162,
     153,   350,   231,   349,   139,   310,   311,   179,   263,   255,
     186,    90,   137,   349,   135,   239,   137,   316,   137,   349,
     245,   252,   188,   312,   318,   330,   332,   321,   326,   334,
     319,   327,   332,   317,   319,   294,   245,   122,   117,   137,
     241,    89,   220,   137,   335,   335,   137,   241,   137,   241,
     142,    10,   135,   154,    10,   188,   186,   163,   186,    91,
     270,   354,   154,     9,   271,   354,   162,   231,   231,   154,
     154,   188,   154,   233,   153,   352,   231,   314,   153,   314,
     219,   349,   238,   137,    98,   237,   140,    29,   114,   254,
     137,   313,   137,   313,   335,   137,   313,   137,   313,   313,
     295,   122,   220,   240,   329,   332,    56,    88,   322,   326,
     319,   328,   332,   319,    52,   246,   247,   315,   135,    89,
     176,   220,   303,   304,   307,   232,   154,   232,   231,   231,
     235,   266,   267,   212,   231,   349,   231,   352,   310,   137,
     238,   137,   316,   154,   154,   319,   332,   319,   319,   296,
     137,   241,   137,   241,    52,    56,   335,   137,   241,   137,
     241,   241,   137,   348,    56,    88,   136,   345,   154,   154,
     154,   153,   238,   137,    10,   135,   313,   137,   313,   313,
     313,   154,   319,   332,   319,   319,   247,    52,    56,   192,
      52,    56,   268,   234,   231,   231,   238,   319,   111,   241,
     137,   241,   241,   241,   350,   313,   319,   241
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      parser_yyerror (parser, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, parser)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (parser, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, parser); \
      YYFPRINTF (parser, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parser);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct parser_params *parser)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parser)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    struct parser_params *parser;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (parser, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (parser, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parser);
  YYFPRINTF (parser, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop, struct parser_params *parser)
#else
static void
yy_stack_print (yybottom, yytop, parser)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (parser, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (parser, " %d", yybot);
    }
  YYFPRINTF (parser, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top), parser);				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, struct parser_params *parser)
#else
static void
yy_reduce_print (yyvsp, yyrule, parser)
    YYSTYPE *yyvsp;
    int yyrule;
    struct parser_params *parser;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (parser, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (parser, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parser);
      YYFPRINTF (parser, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parser); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
#ifndef yydebug
int yydebug;
#endif
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct parser_params *parser)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parser)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    struct parser_params *parser;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parser);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct parser_params *parser);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (struct parser_params *parser)
#else
int
yyparse (parser)
    struct parser_params *parser;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((parser, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((parser, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((parser, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((parser, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((parser, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 952 "parse.y"
    {
			SET_LEX_STATE(EXPR_BEG);
		    /*%%%*/
			local_push(compile_for_eval || rb_parse_in_main());
		    /*%
			local_push(0);
		    %*/
		    }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 961 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(2) - (2)].node) && !compile_for_eval) {
			    /* last expression should not be void */
			    if (nd_type((yyvsp[(2) - (2)].node)) != NODE_BLOCK) void_expr((yyvsp[(2) - (2)].node));
			    else {
				NODE *node = (yyvsp[(2) - (2)].node);
				while (node->nd_next) {
				    node = node->nd_next;
				}
				void_expr(node->nd_head);
			    }
			}
			ruby_eval_tree = NEW_SCOPE(0, block_append(ruby_eval_tree, (yyvsp[(2) - (2)].node)));
		    /*%
			$$ = $2;
			parser->result = dispatch1(program, $$);
		    %*/
			local_pop();
		    }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 984 "parse.y"
    {
		    /*%%%*/
			void_stmts((yyvsp[(1) - (2)].node));
			fixup_nodes(&deferred_nodes);
		    /*%
		    %*/
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 995 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch2(stmts_add, dispatch0(stmts_new),
						  dispatch0(void_stmt));
		    %*/
		    }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 1004 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = newline_node((yyvsp[(1) - (1)].node));
		    /*%
			$$ = dispatch2(stmts_add, dispatch0(stmts_new), $1);
		    %*/
		    }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 1012 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = block_append((yyvsp[(1) - (3)].node), newline_node((yyvsp[(3) - (3)].node)));
		    /*%
			$$ = dispatch2(stmts_add, $1, $3);
		    %*/
		    }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 1020 "parse.y"
    {
			(yyval.node) = remove_begin((yyvsp[(2) - (2)].node));
		    }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 1027 "parse.y"
    {
		    /*%%%*/
			/* local_push(0); */
		    /*%
		    %*/
		    }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 1034 "parse.y"
    {
		    /*%%%*/
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
							    (yyvsp[(4) - (5)].node));
			/* NEW_PREEXE($4)); */
			/* local_pop(); */
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(BEGIN, $4);
		    %*/
		    }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 1051 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (4)].node);
			if ((yyvsp[(2) - (4)].node)) {
			    (yyval.node) = NEW_RESCUE((yyvsp[(1) - (4)].node), (yyvsp[(2) - (4)].node), (yyvsp[(3) - (4)].node));
			}
			else if ((yyvsp[(3) - (4)].node)) {
			    rb_warn0("else without rescue is useless");
			    (yyval.node) = block_append((yyval.node), (yyvsp[(3) - (4)].node));
			}
			if ((yyvsp[(4) - (4)].node)) {
			    if ((yyval.node)) {
				(yyval.node) = NEW_ENSURE((yyval.node), (yyvsp[(4) - (4)].node));
			    }
			    else {
				(yyval.node) = block_append((yyvsp[(4) - (4)].node), NEW_NIL());
			    }
			}
			fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    /*%
			$$ = dispatch4(bodystmt,
				       escape_Qundef($1),
				       escape_Qundef($2),
				       escape_Qundef($3),
				       escape_Qundef($4));
		    %*/
		    }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 1081 "parse.y"
    {
		    /*%%%*/
			void_stmts((yyvsp[(1) - (2)].node));
			fixup_nodes(&deferred_nodes);
		    /*%
		    %*/
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 1092 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch2(stmts_add, dispatch0(stmts_new),
						  dispatch0(void_stmt));
		    %*/
		    }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 1101 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = newline_node((yyvsp[(1) - (1)].node));
		    /*%
			$$ = dispatch2(stmts_add, dispatch0(stmts_new), $1);
		    %*/
		    }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 1109 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = block_append((yyvsp[(1) - (3)].node), newline_node((yyvsp[(3) - (3)].node)));
		    /*%
			$$ = dispatch2(stmts_add, $1, $3);
		    %*/
		    }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 1117 "parse.y"
    {
			(yyval.node) = remove_begin((yyvsp[(2) - (2)].node));
		    }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 1123 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 1127 "parse.y"
    {
			yyerror("BEGIN is permitted only at toplevel");
		    /*%%%*/
			/* local_push(0); */
		    /*%
		    %*/
		    }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 1135 "parse.y"
    {
		    /*%%%*/
			ruby_eval_tree_begin = block_append(ruby_eval_tree_begin,
							    (yyvsp[(4) - (5)].node));
			/* NEW_PREEXE($4)); */
			/* local_pop(); */
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(BEGIN, $4);
		    %*/
		    }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 1147 "parse.y"
    {SET_LEX_STATE(EXPR_FNAME|EXPR_FITEM);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 1148 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ALIAS((yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch2(alias, $2, $4);
		    %*/
		    }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 1156 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_VALIAS((yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch2(var_alias, $2, $3);
		    %*/
		    }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 1164 "parse.y"
    {
		    /*%%%*/
			char buf[2];
			buf[0] = '$';
			buf[1] = (char)(yyvsp[(3) - (3)].node)->nd_nth;
			(yyval.node) = NEW_VALIAS((yyvsp[(2) - (3)].id), rb_intern2(buf, 2));
		    /*%
			$$ = dispatch2(var_alias, $2, $3);
		    %*/
		    }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 1175 "parse.y"
    {
		    /*%%%*/
			yyerror("can't make alias for the number variables");
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch2(var_alias, $2, $3);
			$$ = dispatch1(alias_error, $$);
			ripper_error();
		    %*/
		    }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 1186 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = dispatch1(undef, $2);
		    %*/
		    }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 1194 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_if((yyvsp[(3) - (3)].node), remove_begin((yyvsp[(1) - (3)].node)), 0);
			fixpos((yyval.node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(if_mod, $3, $1);
		    %*/
		    }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 1203 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_unless((yyvsp[(3) - (3)].node), remove_begin((yyvsp[(1) - (3)].node)), 0);
			fixpos((yyval.node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(unless_mod, $3, $1);
		    %*/
		    }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 1212 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_BEGIN) {
			    (yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node)->nd_body, 0);
			}
			else {
			    (yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 1);
			}
		    /*%
			$$ = dispatch2(while_mod, $3, $1);
		    %*/
		    }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 1225 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_BEGIN) {
			    (yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node)->nd_body, 0);
			}
			else {
			    (yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (3)].node)), (yyvsp[(1) - (3)].node), 1);
			}
		    /*%
			$$ = dispatch2(until_mod, $3, $1);
		    %*/
		    }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 1238 "parse.y"
    {
		    /*%%%*/
			NODE *resq = NEW_RESBODY(0, remove_begin((yyvsp[(3) - (3)].node)), 0);
			(yyval.node) = NEW_RESCUE(remove_begin((yyvsp[(1) - (3)].node)), resq, 0);
		    /*%
			$$ = dispatch2(rescue_mod, $1, $3);
		    %*/
		    }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 1247 "parse.y"
    {
			if (in_def || in_single) {
			    rb_warn0("END in method; use at_exit");
			}
		    /*%%%*/
			(yyval.node) = NEW_POSTEXE(NEW_NODE(
			    NODE_SCOPE, 0 /* tbl */, (yyvsp[(3) - (4)].node) /* body */, 0 /* args */));
		    /*%
			$$ = dispatch1(END, $3);
		    %*/
		    }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 1260 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (3)].node));
			(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    /*%
			$$ = dispatch2(massign, $1, $3);
		    %*/
		    }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 1270 "parse.y"
    {
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = new_op_assign((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 1275 "parse.y"
    {
		    /*%%%*/
			NODE *args;

			value_expr((yyvsp[(6) - (6)].node));
			if (!(yyvsp[(3) - (6)].node)) (yyvsp[(3) - (6)].node) = NEW_ZARRAY();
			args = arg_concat((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
			if ((yyvsp[(5) - (6)].id) == tOROP) {
			    (yyvsp[(5) - (6)].id) = 0;
			}
			else if ((yyvsp[(5) - (6)].id) == tANDOP) {
			    (yyvsp[(5) - (6)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN1((yyvsp[(1) - (6)].node), (yyvsp[(5) - (6)].id), args);
			fixpos((yyval.node), (yyvsp[(1) - (6)].node));
		    /*%
			$$ = dispatch2(aref_field, $1, escape_Qundef($3));
			$$ = dispatch3(opassign, $$, $5, $6);
		    %*/
		    }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 1296 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 1301 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 1306 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id));
			(yyval.node) = new_const_op_assign((yyval.node), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    /*%
			$$ = dispatch2(const_path_field, $1, $3);
			$$ = dispatch3(opassign, $$, $4, $5);
		    %*/
		    }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 1316 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), idCOLON2, (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 1321 "parse.y"
    {
		    /*%%%*/
			rb_backref_error((yyvsp[(1) - (3)].node));
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch2(assign, dispatch1(var_field, $1), $3);
			$$ = dispatch1(assign_error, $$);
			ripper_error();
		    %*/
		    }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 1332 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(assign, $1, $3);
		    %*/
		    }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 1341 "parse.y"
    {
		    /*%%%*/
			(yyvsp[(1) - (3)].node)->nd_value = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    /*%
			$$ = dispatch2(massign, $1, $3);
		    %*/
		    }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 1353 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(assign, $1, $3);
		    %*/
		    }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 1362 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(assign, $1, $3);
		    %*/
		    }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 1375 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = logop(NODE_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ripper_intern("and"), $3);
		    %*/
		    }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 1383 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = logop(NODE_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ripper_intern("or"), $3);
		    %*/
		    }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 1391 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op(cond((yyvsp[(3) - (3)].node)), '!');
		    /*%
			$$ = dispatch2(unary, ripper_intern("not"), $3);
		    %*/
		    }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 1399 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op(cond((yyvsp[(2) - (2)].node)), '!');
		    /*%
			$$ = dispatch2(unary, ripper_id2sym('!'), $2);
		    %*/
		    }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 1410 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		        if (!(yyval.node)) (yyval.node) = NEW_NIL();
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 1427 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_QCALL((yyvsp[(2) - (4)].id), (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch3(call, $1, $2, $3);
			$$ = method_arg($$, $4);
		    %*/
		    }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 1438 "parse.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
		    %*/
		    }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 1448 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(2) - (5)].num));
		    /*%
			$$ = dispatch2(brace_block, escape_Qundef($3), $4);
		    %*/
			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 1460 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_FCALL((yyvsp[(1) - (1)].id), 0);
			nd_set_line((yyval.node), tokline);
		    /*%
		    %*/
		    }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 1470 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node);
			(yyval.node)->nd_args = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = dispatch2(command, $1, $2);
		    %*/
		    }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 1479 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node));
			(yyvsp[(1) - (3)].node)->nd_args = (yyvsp[(2) - (3)].node);
		        (yyvsp[(3) - (3)].node)->nd_iter = (yyvsp[(1) - (3)].node);
			(yyval.node) = (yyvsp[(3) - (3)].node);
			fixpos((yyval.node), (yyvsp[(1) - (3)].node));
		    /*%
			$$ = dispatch2(command, $1, $2);
			$$ = method_add_block($$, $3);
		    %*/
		    }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 1492 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_QCALL((yyvsp[(2) - (4)].id), (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
			fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    /*%
			$$ = dispatch4(command_call, $1, $2, $3, $4);
		    %*/
		    }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 1501 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));
		        (yyvsp[(5) - (5)].node)->nd_iter = NEW_QCALL((yyvsp[(2) - (5)].id), (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].node));
			(yyval.node) = (yyvsp[(5) - (5)].node);
			fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    /*%
			$$ = dispatch4(command_call, $1, $2, $3, $4);
			$$ = method_add_block($$, $5);
		    %*/
		   }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 1513 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CALL((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
			fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    /*%
			$$ = dispatch4(command_call, $1, ID2SYM(idCOLON2), $3, $4);
		    %*/
		    }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 1522 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node));
		        (yyvsp[(5) - (5)].node)->nd_iter = NEW_CALL((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].node));
			(yyval.node) = (yyvsp[(5) - (5)].node);
			fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    /*%
			$$ = dispatch4(command_call, $1, ID2SYM(idCOLON2), $3, $4);
			$$ = method_add_block($$, $5);
		    %*/
		   }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 1534 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_SUPER((yyvsp[(2) - (2)].node));
			fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch1(super, $2);
		    %*/
		    }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 1543 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_yield((yyvsp[(2) - (2)].node));
			fixpos((yyval.node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch1(yield, $2);
		    %*/
		    }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 1552 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_RETURN(ret_args((yyvsp[(2) - (2)].node)));
		    /*%
			$$ = dispatch1(return, $2);
		    %*/
		    }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1560 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BREAK(ret_args((yyvsp[(2) - (2)].node)));
		    /*%
			$$ = dispatch1(break, $2);
		    %*/
		    }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1568 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_NEXT(ret_args((yyvsp[(2) - (2)].node)));
		    /*%
			$$ = dispatch1(next, $2);
		    %*/
		    }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1579 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(mlhs_paren, $2);
		    %*/
		    }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1590 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(NEW_LIST((yyvsp[(2) - (3)].node)), 0);
		    /*%
			$$ = dispatch1(mlhs_paren, $2);
		    %*/
		    }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1600 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (1)].node), 0);
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1608 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(list_append((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)), 0);
		    /*%
			$$ = mlhs_add($1, $2);
		    %*/
		    }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1616 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = mlhs_add_star($1, $3);
		    %*/
		    }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1624 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (5)].node), NEW_POSTARG((yyvsp[(3) - (5)].node),(yyvsp[(5) - (5)].node)));
		    /*%
			$1 = mlhs_add_star($1, $3);
			$$ = mlhs_add($1, $5);
		    %*/
		    }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1633 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (2)].node), -1);
		    /*%
			$$ = mlhs_add_star($1, Qnil);
		    %*/
		    }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1641 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (4)].node), NEW_POSTARG(-1, (yyvsp[(4) - (4)].node)));
		    /*%
			$1 = mlhs_add_star($1, Qnil);
			$$ = mlhs_add($1, $4);
		    %*/
		    }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1650 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, (yyvsp[(2) - (2)].node));
		    /*%
			$$ = mlhs_add_star(mlhs_new(), $2);
		    %*/
		    }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1658 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, NEW_POSTARG((yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node)));
		    /*%
			$2 = mlhs_add_star(mlhs_new(), $2);
			$$ = mlhs_add($2, $4);
		    %*/
		    }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1667 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, -1);
		    /*%
			$$ = mlhs_add_star(mlhs_new(), Qnil);
		    %*/
		    }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1675 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].node)));
		    /*%
			$$ = mlhs_add_star(mlhs_new(), Qnil);
			$$ = mlhs_add($$, $3);
		    %*/
		    }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1687 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(mlhs_paren, $2);
		    %*/
		    }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1697 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIST((yyvsp[(1) - (2)].node));
		    /*%
			$$ = mlhs_add(mlhs_new(), $1);
		    %*/
		    }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1705 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    /*%
			$$ = mlhs_add($1, $2);
		    %*/
		    }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1715 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    /*%
			$$ = mlhs_add(mlhs_new(), $1);
		    %*/
		    }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1723 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = mlhs_add($1, $3);
		    %*/
		    }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1733 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1737 "parse.y"
    {
		        (yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1741 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = aryset((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
		    /*%
			$$ = dispatch2(aref_field, $1, escape_Qundef($3));
		    %*/
		    }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 1749 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch3(field, $1, $2, $3);
		    %*/
		    }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 1757 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), idCOLON2, (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch2(const_path_field, $1, $3);
		    %*/
		    }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1765 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch3(field, $1, $2, $3);
		    %*/
		    }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1773 "parse.y"
    {
		    /*%%%*/
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.node) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id)));
		    /*%
			$$ = dispatch2(const_path_field, $1, $3);
			if (in_def || in_single) {
			    $$ = dispatch1(assign_error, $$);
			    ripper_error();
			}
		    %*/
		    }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1787 "parse.y"
    {
		    /*%%%*/
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.node) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].id)));
		    /*%
			$$ = dispatch1(top_const_field, $2);
			if (in_def || in_single) {
			    $$ = dispatch1(assign_error, $$);
			    ripper_error();
			}
		    %*/
		    }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 1801 "parse.y"
    {
		    /*%%%*/
			rb_backref_error((yyvsp[(1) - (1)].node));
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(var_field, $1);
			$$ = dispatch1(assign_error, $$);
			ripper_error();
		    %*/
		    }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 1814 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    /*%%%*/
			if (!(yyval.node)) (yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(var_field, $$);
		    %*/
		    }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 1823 "parse.y"
    {
		        (yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    /*%%%*/
		        if (!(yyval.node)) (yyval.node) = NEW_BEGIN(0);
		    /*%
		        $$ = dispatch1(var_field, $$);
		    %*/
		    }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 1832 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = aryset((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
		    /*%
			$$ = dispatch2(aref_field, $1, escape_Qundef($3));
		    %*/
		    }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 1840 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch3(field, $1, $2, $3);
		    %*/
		    }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 1848 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), idCOLON2, (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch3(field, $1, ID2SYM(idCOLON2), $3);
		    %*/
		    }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 1856 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = attrset((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch3(field, $1, $2, $3);
		    %*/
		    }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 1864 "parse.y"
    {
		    /*%%%*/
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.node) = NEW_CDECL(0, 0, NEW_COLON2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id)));
		    /*%
			$$ = dispatch2(const_path_field, $1, $3);
			if (in_def || in_single) {
			    $$ = dispatch1(assign_error, $$);
			    ripper_error();
			}
		    %*/
		    }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 1878 "parse.y"
    {
		    /*%%%*/
			if (in_def || in_single)
			    yyerror("dynamic constant assignment");
			(yyval.node) = NEW_CDECL(0, 0, NEW_COLON3((yyvsp[(2) - (2)].id)));
		    /*%
			$$ = dispatch1(top_const_field, $2);
			if (in_def || in_single) {
			    $$ = dispatch1(assign_error, $$);
			    ripper_error();
			}
		    %*/
		    }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 1892 "parse.y"
    {
		    /*%%%*/
			rb_backref_error((yyvsp[(1) - (1)].node));
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(assign_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 1904 "parse.y"
    {
		    /*%%%*/
			yyerror("class/module name must be CONSTANT");
		    /*%
			$$ = dispatch1(class_name_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 1916 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON3((yyvsp[(2) - (2)].id));
		    /*%
			$$ = dispatch1(top_const_ref, $2);
		    %*/
		    }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 1924 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON2(0, (yyval.node));
		    /*%
			$$ = dispatch1(const_ref, $1);
		    %*/
		    }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 1932 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch2(const_path_ref, $1, $3);
		    %*/
		    }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 1945 "parse.y"
    {
			SET_LEX_STATE(EXPR_ENDFN);
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 1950 "parse.y"
    {
			SET_LEX_STATE(EXPR_ENDFN);
		    /*%%%*/
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 1965 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].id)));
		    /*%
			$$ = dispatch1(symbol_literal, $1);
		    %*/
		    }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 1976 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_UNDEF((yyvsp[(1) - (1)].node));
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 1983 "parse.y"
    {SET_LEX_STATE(EXPR_FNAME|EXPR_FITEM);}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 1984 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = block_append((yyvsp[(1) - (4)].node), NEW_UNDEF((yyvsp[(4) - (4)].node)));
		    /*%
			rb_ary_push($1, $4);
		    %*/
		    }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 1993 "parse.y"
    { ifndef_ripper((yyval.id) = '|'); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 1994 "parse.y"
    { ifndef_ripper((yyval.id) = '^'); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 1995 "parse.y"
    { ifndef_ripper((yyval.id) = '&'); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 1996 "parse.y"
    { ifndef_ripper((yyval.id) = tCMP); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 1997 "parse.y"
    { ifndef_ripper((yyval.id) = tEQ); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 1998 "parse.y"
    { ifndef_ripper((yyval.id) = tEQQ); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 1999 "parse.y"
    { ifndef_ripper((yyval.id) = tMATCH); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 2000 "parse.y"
    { ifndef_ripper((yyval.id) = tNMATCH); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 2001 "parse.y"
    { ifndef_ripper((yyval.id) = '>'); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 2002 "parse.y"
    { ifndef_ripper((yyval.id) = tGEQ); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 2003 "parse.y"
    { ifndef_ripper((yyval.id) = '<'); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 2004 "parse.y"
    { ifndef_ripper((yyval.id) = tLEQ); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 2005 "parse.y"
    { ifndef_ripper((yyval.id) = tNEQ); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 2006 "parse.y"
    { ifndef_ripper((yyval.id) = tLSHFT); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 2007 "parse.y"
    { ifndef_ripper((yyval.id) = tRSHFT); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 2008 "parse.y"
    { ifndef_ripper((yyval.id) = '+'); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 2009 "parse.y"
    { ifndef_ripper((yyval.id) = '-'); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 2010 "parse.y"
    { ifndef_ripper((yyval.id) = '*'); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 2011 "parse.y"
    { ifndef_ripper((yyval.id) = '*'); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 2012 "parse.y"
    { ifndef_ripper((yyval.id) = '/'); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 2013 "parse.y"
    { ifndef_ripper((yyval.id) = '%'); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 2014 "parse.y"
    { ifndef_ripper((yyval.id) = tPOW); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 2015 "parse.y"
    { ifndef_ripper((yyval.id) = tDSTAR); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 2016 "parse.y"
    { ifndef_ripper((yyval.id) = '!'); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 2017 "parse.y"
    { ifndef_ripper((yyval.id) = '~'); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 2018 "parse.y"
    { ifndef_ripper((yyval.id) = tUPLUS); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 2019 "parse.y"
    { ifndef_ripper((yyval.id) = tUMINUS); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 2020 "parse.y"
    { ifndef_ripper((yyval.id) = tAREF); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 2021 "parse.y"
    { ifndef_ripper((yyval.id) = tASET); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 2022 "parse.y"
    { ifndef_ripper((yyval.id) = '`'); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 2040 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = node_assign((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(assign, $1, $3);
		    %*/
		    }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 2049 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (5)].node));
		        (yyvsp[(3) - (5)].node) = NEW_RESCUE((yyvsp[(3) - (5)].node), NEW_RESBODY(0,(yyvsp[(5) - (5)].node),0), 0);
			(yyval.node) = node_assign((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node));
		    /*%
			$$ = dispatch2(assign, $1, dispatch2(rescue_mod, $3, $5));
		    %*/
		    }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 2059 "parse.y"
    {
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = new_op_assign((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].node));
		    }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 2064 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(3) - (5)].node));
		        (yyvsp[(3) - (5)].node) = NEW_RESCUE((yyvsp[(3) - (5)].node), NEW_RESBODY(0,(yyvsp[(5) - (5)].node),0), 0);
		    /*%
			$3 = dispatch2(rescue_mod, $3, $5);
		    %*/
			(yyval.node) = new_op_assign((yyvsp[(1) - (5)].node), (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].node));
		    }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 2074 "parse.y"
    {
		    /*%%%*/
			NODE *args;

			value_expr((yyvsp[(6) - (6)].node));
			if (!(yyvsp[(3) - (6)].node)) (yyvsp[(3) - (6)].node) = NEW_ZARRAY();
			if (nd_type((yyvsp[(3) - (6)].node)) == NODE_BLOCK_PASS) {
			    args = NEW_ARGSCAT((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
			}
		        else {
			    args = arg_concat((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
		        }
			if ((yyvsp[(5) - (6)].id) == tOROP) {
			    (yyvsp[(5) - (6)].id) = 0;
			}
			else if ((yyvsp[(5) - (6)].id) == tANDOP) {
			    (yyvsp[(5) - (6)].id) = 1;
			}
			(yyval.node) = NEW_OP_ASGN1((yyvsp[(1) - (6)].node), (yyvsp[(5) - (6)].id), args);
			fixpos((yyval.node), (yyvsp[(1) - (6)].node));
		    /*%
			$1 = dispatch2(aref_field, $1, escape_Qundef($3));
			$$ = dispatch3(opassign, $1, $5, $6);
		    %*/
		    }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 2100 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 2105 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 2110 "parse.y"
    {
			value_expr((yyvsp[(5) - (5)].node));
			(yyval.node) = new_attr_op_assign((yyvsp[(1) - (5)].node), idCOLON2, (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 2115 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON2((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id));
			(yyval.node) = new_const_op_assign((yyval.node), (yyvsp[(4) - (5)].id), (yyvsp[(5) - (5)].node));
		    /*%
			$$ = dispatch2(const_path_field, $1, $3);
			$$ = dispatch3(opassign, $$, $4, $5);
		    %*/
		    }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 2125 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON3((yyvsp[(2) - (4)].id));
			(yyval.node) = new_const_op_assign((yyval.node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch1(top_const_field, $2);
			$$ = dispatch3(opassign, $$, $3, $4);
		    %*/
		    }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 2135 "parse.y"
    {
		    /*%%%*/
			rb_backref_error((yyvsp[(1) - (3)].node));
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(var_field, $1);
			$$ = dispatch3(opassign, $$, $2, $3);
			$$ = dispatch1(assign_error, $$);
			ripper_error();
		    %*/
		    }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 2147 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (3)].node));
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = NEW_DOT2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].node)->nd_lit) &&
			    (yyvsp[(3) - (3)].node) && nd_type((yyvsp[(3) - (3)].node)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].node)->nd_lit)) {
			    deferred_nodes = list_append(deferred_nodes, (yyval.node));
			}
		    /*%
			$$ = dispatch2(dot2, $1, $3);
		    %*/
		    }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 2161 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (3)].node));
			value_expr((yyvsp[(3) - (3)].node));
			(yyval.node) = NEW_DOT3((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
			if ((yyvsp[(1) - (3)].node) && nd_type((yyvsp[(1) - (3)].node)) == NODE_LIT && FIXNUM_P((yyvsp[(1) - (3)].node)->nd_lit) &&
			    (yyvsp[(3) - (3)].node) && nd_type((yyvsp[(3) - (3)].node)) == NODE_LIT && FIXNUM_P((yyvsp[(3) - (3)].node)->nd_lit)) {
			    deferred_nodes = list_append(deferred_nodes, (yyval.node));
			}
		    /*%
			$$ = dispatch2(dot3, $1, $3);
		    %*/
		    }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 2175 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '+', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('+'), $3);
		    %*/
		    }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 2183 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '-', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('-'), $3);
		    %*/
		    }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 2191 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '*', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('*'), $3);
		    %*/
		    }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 2199 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '/', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('/'), $3);
		    %*/
		    }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 2207 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '%', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('%'), $3);
		    %*/
		    }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 2215 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tPOW, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idPow), $3);
		    %*/
		    }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 2223 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CALL(call_bin_op((yyvsp[(2) - (4)].node), tPOW, (yyvsp[(4) - (4)].node)), tUMINUS, 0);
		    /*%
			$$ = dispatch3(binary, $2, ID2SYM(idPow), $4);
			$$ = dispatch2(unary, ID2SYM(idUMinus), $$);
		    %*/
		    }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 2232 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op((yyvsp[(2) - (2)].node), tUPLUS);
		    /*%
			$$ = dispatch2(unary, ID2SYM(idUPlus), $2);
		    %*/
		    }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 2240 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op((yyvsp[(2) - (2)].node), tUMINUS);
		    /*%
			$$ = dispatch2(unary, ID2SYM(idUMinus), $2);
		    %*/
		    }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 2248 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '|', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('|'), $3);
		    %*/
		    }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 2256 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '^', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('^'), $3);
		    %*/
		    }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 2264 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '&', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('&'), $3);
		    %*/
		    }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 2272 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tCMP, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idCmp), $3);
		    %*/
		    }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 2280 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '>', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('>'), $3);
		    %*/
		    }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 2288 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tGEQ, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idGE), $3);
		    %*/
		    }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 2296 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), '<', (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM('<'), $3);
		    %*/
		    }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 2304 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tLEQ, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idLE), $3);
		    %*/
		    }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 2312 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tEQ, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idEq), $3);
		    %*/
		    }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 2320 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tEQQ, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idEqq), $3);
		    %*/
		    }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 2328 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tNEQ, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idNeq), $3);
		    %*/
		    }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 2336 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = match_op((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
                        if (nd_type((yyvsp[(1) - (3)].node)) == NODE_LIT && RB_TYPE_P((yyvsp[(1) - (3)].node)->nd_lit, T_REGEXP)) {
                            (yyval.node) = reg_named_capture_assign((yyvsp[(1) - (3)].node)->nd_lit, (yyval.node));
                        }
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idEqTilde), $3);
		    %*/
		    }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 2347 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tNMATCH, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idNeqTilde), $3);
		    %*/
		    }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 2355 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op(cond((yyvsp[(2) - (2)].node)), '!');
		    /*%
			$$ = dispatch2(unary, ID2SYM('!'), $2);
		    %*/
		    }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 2363 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op((yyvsp[(2) - (2)].node), '~');
		    /*%
			$$ = dispatch2(unary, ID2SYM('~'), $2);
		    %*/
		    }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 2371 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tLSHFT, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idLTLT), $3);
		    %*/
		    }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 2379 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_bin_op((yyvsp[(1) - (3)].node), tRSHFT, (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idGTGT), $3);
		    %*/
		    }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 2387 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = logop(NODE_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idANDOP), $3);
		    %*/
		    }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 2395 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = logop(NODE_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch3(binary, $1, ID2SYM(idOROP), $3);
		    %*/
		    }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 2402 "parse.y"
    {in_defined = 1;}
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 2403 "parse.y"
    {
			in_defined = 0;
		    /*%%%*/
			(yyval.node) = new_defined((yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch1(defined, $4);
		    %*/
		    }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 2412 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (6)].node));
			(yyval.node) = new_if((yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
			fixpos((yyval.node), (yyvsp[(1) - (6)].node));
		    /*%
			$$ = dispatch3(ifop, $1, $3, $6);
		    %*/
		    }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 2422 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 2428 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		        if (!(yyval.node)) (yyval.node) = NEW_NIL();
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 2441 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 2445 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(3) - (4)].node) ? arg_append((yyvsp[(1) - (4)].node), new_hash((yyvsp[(3) - (4)].node))) : (yyvsp[(1) - (4)].node);
		    /*%
			$$ = arg_add_assocs($1, $3);
		    %*/
		    }
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 2453 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node) ? NEW_LIST(new_hash((yyvsp[(1) - (2)].node))) : 0;
		    /*%
			$$ = arg_add_assocs(arg_new(), $1);
		    %*/
		    }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 2463 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(arg_paren, escape_Qundef($2));
		    %*/
		    }
    break;

  case 253:

/* Line 1806 of yacc.c  */
#line 2479 "parse.y"
    {
		      (yyval.node) = (yyvsp[(1) - (2)].node);
		    }
    break;

  case 254:

/* Line 1806 of yacc.c  */
#line 2483 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(3) - (4)].node) ? arg_append((yyvsp[(1) - (4)].node), new_hash((yyvsp[(3) - (4)].node))) : (yyvsp[(1) - (4)].node);
		    /*%
			$$ = arg_add_assocs($1, $3);
		    %*/
		    }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 2491 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node) ? NEW_LIST(new_hash((yyvsp[(1) - (2)].node))) : 0;
		    /*%
			$$ = arg_add_assocs(arg_new(), $1);
		    %*/
		    }
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 2501 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    /*%
			$$ = arg_add(arg_new(), $1);
		    %*/
		    }
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 2510 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = arg_blk_pass((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = arg_add_optblock($1, $2);
		    %*/
		    }
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 2518 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node) ? NEW_LIST(new_hash((yyvsp[(1) - (2)].node))) : 0;
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = arg_add_assocs(arg_new(), $1);
			$$ = arg_add_optblock($$, $2);
		    %*/
		    }
    break;

  case 259:

/* Line 1806 of yacc.c  */
#line 2528 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(3) - (4)].node) ? arg_append((yyvsp[(1) - (4)].node), new_hash((yyvsp[(3) - (4)].node))) : (yyvsp[(1) - (4)].node);
			(yyval.node) = arg_blk_pass((yyval.node), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = arg_add_optblock(arg_add_assocs($1, $3), $4);
		    %*/
		    }
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 2545 "parse.y"
    {
			(yyval.val) = cmdarg_stack;
			CMDARG_PUSH(1);
		    }
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 2550 "parse.y"
    {
			/* CMDARG_POP() */
			cmdarg_stack = (yyvsp[(1) - (2)].val);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 2558 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BLOCK_PASS((yyvsp[(2) - (2)].node));
		    /*%
			$$ = $2;
		    %*/
		    }
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 2568 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 2572 "parse.y"
    {
			(yyval.node) = 0;
		    }
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 2578 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    /*%
			$$ = arg_add(arg_new(), $1);
		    %*/
		    }
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 2586 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_SPLAT((yyvsp[(2) - (2)].node));
		    /*%
			$$ = arg_add_star(arg_new(), $2);
		    %*/
		    }
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 2594 "parse.y"
    {
		    /*%%%*/
			NODE *n1;
			if ((n1 = splat_array((yyvsp[(1) - (3)].node))) != 0) {
			    (yyval.node) = list_append(n1, (yyvsp[(3) - (3)].node));
			}
			else {
			    (yyval.node) = arg_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
			}
		    /*%
			$$ = arg_add($1, $3);
		    %*/
		    }
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 2608 "parse.y"
    {
		    /*%%%*/
			NODE *n1;
			if ((nd_type((yyvsp[(4) - (4)].node)) == NODE_ARRAY) && (n1 = splat_array((yyvsp[(1) - (4)].node))) != 0) {
			    (yyval.node) = list_concat(n1, (yyvsp[(4) - (4)].node));
			}
			else {
			    (yyval.node) = arg_concat((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
			}
		    /*%
			$$ = arg_add_star($1, $4);
		    %*/
		    }
    break;

  case 272:

/* Line 1806 of yacc.c  */
#line 2628 "parse.y"
    {
		    /*%%%*/
			NODE *n1;
			if ((n1 = splat_array((yyvsp[(1) - (3)].node))) != 0) {
			    (yyval.node) = list_append(n1, (yyvsp[(3) - (3)].node));
			}
			else {
			    (yyval.node) = arg_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
			}
		    /*%
			$$ = mrhs_add(args2mrhs($1), $3);
		    %*/
		    }
    break;

  case 273:

/* Line 1806 of yacc.c  */
#line 2642 "parse.y"
    {
		    /*%%%*/
			NODE *n1;
			if (nd_type((yyvsp[(4) - (4)].node)) == NODE_ARRAY &&
			    (n1 = splat_array((yyvsp[(1) - (4)].node))) != 0) {
			    (yyval.node) = list_concat(n1, (yyvsp[(4) - (4)].node));
			}
			else {
			    (yyval.node) = arg_concat((yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
			}
		    /*%
			$$ = mrhs_add_star(args2mrhs($1), $4);
		    %*/
		    }
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 2657 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_SPLAT((yyvsp[(2) - (2)].node));
		    /*%
			$$ = mrhs_add_star(mrhs_new(), $2);
		    %*/
		    }
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 2677 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_FCALL((yyvsp[(1) - (1)].id), 0);
		    /*%
			$$ = method_arg(dispatch1(fcall, $1), arg_new());
		    %*/
		    }
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 2685 "parse.y"
    {
			(yyvsp[(1) - (1)].val) = cmdarg_stack;
			cmdarg_stack = 0;
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
		    %*/
		    }
    break;

  case 287:

/* Line 1806 of yacc.c  */
#line 2695 "parse.y"
    {
			cmdarg_stack = (yyvsp[(1) - (4)].val);
		    /*%%%*/
			if ((yyvsp[(3) - (4)].node) == NULL) {
			    (yyval.node) = NEW_NIL();
			}
			else {
			    set_line_body((yyvsp[(3) - (4)].node), (yyvsp[(2) - (4)].num));
			    (yyval.node) = NEW_BEGIN((yyvsp[(3) - (4)].node));
			}
			nd_set_line((yyval.node), (yyvsp[(2) - (4)].num));
		    /*%
			$$ = dispatch1(begin, $3);
		    %*/
		    }
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 2710 "parse.y"
    {SET_LEX_STATE(EXPR_ENDARG);}
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 2711 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(paren, 0);
		    %*/
		    }
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 2719 "parse.y"
    {
			(yyvsp[(1) - (1)].val) = cmdarg_stack;
			cmdarg_stack = 0;
		    }
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 2723 "parse.y"
    {SET_LEX_STATE(EXPR_ENDARG);}
    break;

  case 292:

/* Line 1806 of yacc.c  */
#line 2724 "parse.y"
    {
			cmdarg_stack = (yyvsp[(1) - (5)].val);
		    /*%%%*/
			(yyval.node) = (yyvsp[(3) - (5)].node);
		    /*%
			$$ = dispatch1(paren, $3);
		    %*/
		    }
    break;

  case 293:

/* Line 1806 of yacc.c  */
#line 2733 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(paren, $2);
		    %*/
		    }
    break;

  case 294:

/* Line 1806 of yacc.c  */
#line 2741 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON2((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id));
		    /*%
			$$ = dispatch2(const_path_ref, $1, $3);
		    %*/
		    }
    break;

  case 295:

/* Line 1806 of yacc.c  */
#line 2749 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_COLON3((yyvsp[(2) - (2)].id));
		    /*%
			$$ = dispatch1(top_const_ref, $2);
		    %*/
		    }
    break;

  case 296:

/* Line 1806 of yacc.c  */
#line 2757 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(2) - (3)].node) == 0) {
			    (yyval.node) = NEW_ZARRAY(); /* zero length array*/
			}
			else {
			    (yyval.node) = (yyvsp[(2) - (3)].node);
			}
		    /*%
			$$ = dispatch1(array, escape_Qundef($2));
		    %*/
		    }
    break;

  case 297:

/* Line 1806 of yacc.c  */
#line 2770 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_hash((yyvsp[(2) - (3)].node));
		    /*%
			$$ = dispatch1(hash, escape_Qundef($2));
		    %*/
		    }
    break;

  case 298:

/* Line 1806 of yacc.c  */
#line 2778 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_RETURN(0);
		    /*%
			$$ = dispatch0(return0);
		    %*/
		    }
    break;

  case 299:

/* Line 1806 of yacc.c  */
#line 2786 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_yield((yyvsp[(3) - (4)].node));
		    /*%
			$$ = dispatch1(yield, dispatch1(paren, $3));
		    %*/
		    }
    break;

  case 300:

/* Line 1806 of yacc.c  */
#line 2794 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_YIELD(0);
		    /*%
			$$ = dispatch1(yield, dispatch1(paren, arg_new()));
		    %*/
		    }
    break;

  case 301:

/* Line 1806 of yacc.c  */
#line 2802 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_YIELD(0);
		    /*%
			$$ = dispatch0(yield0);
		    %*/
		    }
    break;

  case 302:

/* Line 1806 of yacc.c  */
#line 2809 "parse.y"
    {in_defined = 1;}
    break;

  case 303:

/* Line 1806 of yacc.c  */
#line 2810 "parse.y"
    {
			in_defined = 0;
		    /*%%%*/
			(yyval.node) = new_defined((yyvsp[(5) - (6)].node));
		    /*%
			$$ = dispatch1(defined, $5);
		    %*/
		    }
    break;

  case 304:

/* Line 1806 of yacc.c  */
#line 2819 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op(cond((yyvsp[(3) - (4)].node)), '!');
		    /*%
			$$ = dispatch2(unary, ripper_intern("not"), $3);
		    %*/
		    }
    break;

  case 305:

/* Line 1806 of yacc.c  */
#line 2827 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = call_uni_op(cond(NEW_NIL()), '!');
		    /*%
			$$ = dispatch2(unary, ripper_intern("not"), Qnil);
		    %*/
		    }
    break;

  case 306:

/* Line 1806 of yacc.c  */
#line 2835 "parse.y"
    {
		    /*%%%*/
			(yyvsp[(2) - (2)].node)->nd_iter = (yyvsp[(1) - (2)].node);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = method_arg(dispatch1(fcall, $1), arg_new());
			$$ = method_add_block($$, $2);
		    %*/
		    }
    break;

  case 308:

/* Line 1806 of yacc.c  */
#line 2846 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(1) - (2)].node)->nd_args, (yyvsp[(2) - (2)].node));
			(yyvsp[(2) - (2)].node)->nd_iter = (yyvsp[(1) - (2)].node);
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = method_add_block($1, $2);
		    %*/
		    }
    break;

  case 309:

/* Line 1806 of yacc.c  */
#line 2856 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 310:

/* Line 1806 of yacc.c  */
#line 2863 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_if((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node));
			fixpos((yyval.node), (yyvsp[(2) - (6)].node));
		    /*%
			$$ = dispatch3(if, $2, $4, escape_Qundef($5));
		    %*/
		    }
    break;

  case 311:

/* Line 1806 of yacc.c  */
#line 2875 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_unless((yyvsp[(2) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(5) - (6)].node));
			fixpos((yyval.node), (yyvsp[(2) - (6)].node));
		    /*%
			$$ = dispatch3(unless, $2, $4, escape_Qundef($5));
		    %*/
		    }
    break;

  case 312:

/* Line 1806 of yacc.c  */
#line 2883 "parse.y"
    {COND_PUSH(1);}
    break;

  case 313:

/* Line 1806 of yacc.c  */
#line 2883 "parse.y"
    {COND_POP();}
    break;

  case 314:

/* Line 1806 of yacc.c  */
#line 2886 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_WHILE(cond((yyvsp[(3) - (7)].node)), (yyvsp[(6) - (7)].node), 1);
			fixpos((yyval.node), (yyvsp[(3) - (7)].node));
		    /*%
			$$ = dispatch2(while, $3, $6);
		    %*/
		    }
    break;

  case 315:

/* Line 1806 of yacc.c  */
#line 2894 "parse.y"
    {COND_PUSH(1);}
    break;

  case 316:

/* Line 1806 of yacc.c  */
#line 2894 "parse.y"
    {COND_POP();}
    break;

  case 317:

/* Line 1806 of yacc.c  */
#line 2897 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_UNTIL(cond((yyvsp[(3) - (7)].node)), (yyvsp[(6) - (7)].node), 1);
			fixpos((yyval.node), (yyvsp[(3) - (7)].node));
		    /*%
			$$ = dispatch2(until, $3, $6);
		    %*/
		    }
    break;

  case 318:

/* Line 1806 of yacc.c  */
#line 2908 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CASE((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
			fixpos((yyval.node), (yyvsp[(2) - (5)].node));
		    /*%
			$$ = dispatch2(case, $2, $4);
		    %*/
		    }
    break;

  case 319:

/* Line 1806 of yacc.c  */
#line 2917 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CASE(0, (yyvsp[(3) - (4)].node));
		    /*%
			$$ = dispatch2(case, Qnil, $3);
		    %*/
		    }
    break;

  case 320:

/* Line 1806 of yacc.c  */
#line 2925 "parse.y"
    {COND_PUSH(1);}
    break;

  case 321:

/* Line 1806 of yacc.c  */
#line 2927 "parse.y"
    {COND_POP();}
    break;

  case 322:

/* Line 1806 of yacc.c  */
#line 2930 "parse.y"
    {
		    /*%%%*/
			/*
			 *  for a, b, c in e
			 *  #=>
			 *  e.each{|*x| a, b, c = x}
			 *
			 *  for a in e
			 *  #=>
			 *  e.each{|x| a, = x}
			 */
			ID id = internal_id();
			ID *tbl = ALLOC_N(ID, 2);
			NODE *m = NEW_ARGS_AUX(0, 0);
			NODE *args, *scope;

			switch (nd_type((yyvsp[(2) - (9)].node))) {
			  case NODE_MASGN:
			    m->nd_next = node_assign((yyvsp[(2) - (9)].node), NEW_FOR(NEW_DVAR(id), 0, 0));
			    args = new_args(m, 0, id, 0, new_args_tail(0, 0, 0));
			    break;
			  case NODE_LASGN:
			  case NODE_DASGN:
			  case NODE_DASGN_CURR:
			    (yyvsp[(2) - (9)].node)->nd_value = NEW_DVAR(id);
			    m->nd_plen = 1;
			    m->nd_next = (yyvsp[(2) - (9)].node);
			    args = new_args(m, 0, 0, 0, new_args_tail(0, 0, 0));
			    break;
			  default:
			    m->nd_next = node_assign(NEW_MASGN(NEW_LIST((yyvsp[(2) - (9)].node)), 0), NEW_DVAR(id));
			    args = new_args(m, 0, id, 0, new_args_tail(0, 0, 0));
			    break;
			}
			scope = NEW_NODE(NODE_SCOPE, tbl, (yyvsp[(8) - (9)].node), args);
			tbl[0] = 1; tbl[1] = id;
			(yyval.node) = NEW_FOR(0, (yyvsp[(5) - (9)].node), scope);
			fixpos((yyval.node), (yyvsp[(2) - (9)].node));
		    /*%
			$$ = dispatch3(for, $2, $5, $8);
		    %*/
		    }
    break;

  case 323:

/* Line 1806 of yacc.c  */
#line 2973 "parse.y"
    {
			if (in_def || in_single)
			    yyerror("class definition in method body");
			local_push(0);
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
		    %*/
		    }
    break;

  case 324:

/* Line 1806 of yacc.c  */
#line 2984 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CLASS((yyvsp[(2) - (6)].node), (yyvsp[(5) - (6)].node), (yyvsp[(3) - (6)].node));
			set_line_body((yyvsp[(5) - (6)].node), (yyvsp[(4) - (6)].num));
			nd_set_line((yyval.node), (yyvsp[(4) - (6)].num));
		    /*%
			$$ = dispatch3(class, $2, $3, $5);
		    %*/
			local_pop();
		    }
    break;

  case 325:

/* Line 1806 of yacc.c  */
#line 2995 "parse.y"
    {
			(yyval.num) = (in_def << 1) | in_single;
			in_def = 0;
			in_single = 0;
			local_push(0);
		    }
    break;

  case 326:

/* Line 1806 of yacc.c  */
#line 3004 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_SCLASS((yyvsp[(3) - (7)].node), (yyvsp[(6) - (7)].node));
			set_line_body((yyvsp[(6) - (7)].node), nd_line((yyvsp[(3) - (7)].node)));
			fixpos((yyval.node), (yyvsp[(3) - (7)].node));
		    /*%
			$$ = dispatch2(sclass, $3, $6);
		    %*/
			local_pop();
			in_def = ((yyvsp[(4) - (7)].num) >> 1) & 1;
			in_single = (yyvsp[(4) - (7)].num) & 1;
		    }
    break;

  case 327:

/* Line 1806 of yacc.c  */
#line 3017 "parse.y"
    {
			if (in_def || in_single)
			    yyerror("module definition in method body");
			local_push(0);
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
		    %*/
		    }
    break;

  case 328:

/* Line 1806 of yacc.c  */
#line 3028 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MODULE((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
			set_line_body((yyvsp[(4) - (5)].node), (yyvsp[(3) - (5)].num));
			nd_set_line((yyval.node), (yyvsp[(3) - (5)].num));
		    /*%
			$$ = dispatch2(module, $2, $4);
		    %*/
			local_pop();
		    }
    break;

  case 329:

/* Line 1806 of yacc.c  */
#line 3039 "parse.y"
    {
			local_push(0);
			(yyval.id) = current_arg;
			current_arg = 0;
		    }
    break;

  case 330:

/* Line 1806 of yacc.c  */
#line 3044 "parse.y"
    {
			(yyval.num) = in_def;
			in_def = 1;
		    }
    break;

  case 331:

/* Line 1806 of yacc.c  */
#line 3051 "parse.y"
    {
		    /*%%%*/
			NODE *body = remove_begin((yyvsp[(6) - (7)].node));
			reduce_nodes(&body);
			(yyval.node) = NEW_DEFN((yyvsp[(2) - (7)].id), (yyvsp[(5) - (7)].node), body, METHOD_VISI_PRIVATE);
			set_line_body(body, (yyvsp[(1) - (7)].num));
			nd_set_line((yyval.node), (yyvsp[(1) - (7)].num));
		    /*%
			$$ = dispatch3(def, $2, $5, $6);
		    %*/
			local_pop();
			in_def = (yyvsp[(4) - (7)].num) & 1;
			current_arg = (yyvsp[(3) - (7)].id);
		    }
    break;

  case 332:

/* Line 1806 of yacc.c  */
#line 3065 "parse.y"
    {SET_LEX_STATE(EXPR_FNAME);}
    break;

  case 333:

/* Line 1806 of yacc.c  */
#line 3066 "parse.y"
    {
			(yyvsp[(4) - (5)].num) = in_single;
			in_single = 1;
			SET_LEX_STATE(EXPR_ENDFN|EXPR_LABEL); /* force for args */
			local_push(0);
			(yyval.id) = current_arg;
			current_arg = 0;
		    }
    break;

  case 334:

/* Line 1806 of yacc.c  */
#line 3077 "parse.y"
    {
		    /*%%%*/
			NODE *body = remove_begin((yyvsp[(8) - (9)].node));
			reduce_nodes(&body);
			(yyval.node) = NEW_DEFS((yyvsp[(2) - (9)].node), (yyvsp[(5) - (9)].id), (yyvsp[(7) - (9)].node), body);
			set_line_body(body, (yyvsp[(1) - (9)].num));
			nd_set_line((yyval.node), (yyvsp[(1) - (9)].num));
		    /*%
			$$ = dispatch5(defs, $2, $3, $5, $7, $8);
		    %*/
			local_pop();
			in_single = (yyvsp[(4) - (9)].num) & 1;
			current_arg = (yyvsp[(6) - (9)].id);
		    }
    break;

  case 335:

/* Line 1806 of yacc.c  */
#line 3092 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_BREAK(0);
		    /*%
			$$ = dispatch1(break, arg_new());
		    %*/
		    }
    break;

  case 336:

/* Line 1806 of yacc.c  */
#line 3100 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_NEXT(0);
		    /*%
			$$ = dispatch1(next, arg_new());
		    %*/
		    }
    break;

  case 337:

/* Line 1806 of yacc.c  */
#line 3108 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_REDO();
		    /*%
			$$ = dispatch0(redo);
		    %*/
		    }
    break;

  case 338:

/* Line 1806 of yacc.c  */
#line 3116 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_RETRY();
		    /*%
			$$ = dispatch0(retry);
		    %*/
		    }
    break;

  case 339:

/* Line 1806 of yacc.c  */
#line 3126 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		        if (!(yyval.node)) (yyval.node) = NEW_NIL();
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 340:

/* Line 1806 of yacc.c  */
#line 3138 "parse.y"
    {
			token_info_push("begin");
		    }
    break;

  case 341:

/* Line 1806 of yacc.c  */
#line 3144 "parse.y"
    {
			token_info_push("if");
		    }
    break;

  case 342:

/* Line 1806 of yacc.c  */
#line 3150 "parse.y"
    {
			token_info_push("unless");
		    }
    break;

  case 343:

/* Line 1806 of yacc.c  */
#line 3156 "parse.y"
    {
			token_info_push("while");
		    }
    break;

  case 344:

/* Line 1806 of yacc.c  */
#line 3162 "parse.y"
    {
			token_info_push("until");
		    }
    break;

  case 345:

/* Line 1806 of yacc.c  */
#line 3168 "parse.y"
    {
			token_info_push("case");
		    }
    break;

  case 346:

/* Line 1806 of yacc.c  */
#line 3174 "parse.y"
    {
			token_info_push("for");
		    }
    break;

  case 347:

/* Line 1806 of yacc.c  */
#line 3180 "parse.y"
    {
			token_info_push("class");
		    }
    break;

  case 348:

/* Line 1806 of yacc.c  */
#line 3186 "parse.y"
    {
			token_info_push("module");
		    }
    break;

  case 349:

/* Line 1806 of yacc.c  */
#line 3192 "parse.y"
    {
			token_info_push("def");
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
		    %*/
		    }
    break;

  case 350:

/* Line 1806 of yacc.c  */
#line 3202 "parse.y"
    {
			token_info_pop("end");
		    }
    break;

  case 357:

/* Line 1806 of yacc.c  */
#line 3232 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = new_if((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
			fixpos((yyval.node), (yyvsp[(2) - (5)].node));
		    /*%
			$$ = dispatch3(elsif, $2, $4, escape_Qundef($5));
		    %*/
		    }
    break;

  case 359:

/* Line 1806 of yacc.c  */
#line 3244 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = dispatch1(else, $2);
		    %*/
		    }
    break;

  case 362:

/* Line 1806 of yacc.c  */
#line 3258 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    /*%%%*/
		    /*%
			$$ = dispatch1(mlhs_paren, $$);
		    %*/
		    }
    break;

  case 363:

/* Line 1806 of yacc.c  */
#line 3266 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(mlhs_paren, $2);
		    %*/
		    }
    break;

  case 364:

/* Line 1806 of yacc.c  */
#line 3276 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    /*%
			$$ = mlhs_add(mlhs_new(), $1);
		    %*/
		    }
    break;

  case 365:

/* Line 1806 of yacc.c  */
#line 3284 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = mlhs_add($1, $3);
		    %*/
		    }
    break;

  case 366:

/* Line 1806 of yacc.c  */
#line 3294 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (1)].node), 0);
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 367:

/* Line 1806 of yacc.c  */
#line 3302 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(4) - (4)].id), 0);
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (4)].node), (yyval.node));
		    /*%
			$$ = mlhs_add_star($1, $$);
		    %*/
		    }
    break;

  case 368:

/* Line 1806 of yacc.c  */
#line 3311 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(4) - (6)].id), 0);
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (6)].node), NEW_POSTARG((yyval.node), (yyvsp[(6) - (6)].node)));
		    /*%
			$$ = mlhs_add_star($1, $$);
		    %*/
		    }
    break;

  case 369:

/* Line 1806 of yacc.c  */
#line 3320 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (3)].node), -1);
		    /*%
			$$ = mlhs_add_star($1, Qnil);
		    %*/
		    }
    break;

  case 370:

/* Line 1806 of yacc.c  */
#line 3328 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN((yyvsp[(1) - (5)].node), NEW_POSTARG(-1, (yyvsp[(5) - (5)].node)));
		    /*%
			$$ = mlhs_add_star($1, $5);
		    %*/
		    }
    break;

  case 371:

/* Line 1806 of yacc.c  */
#line 3336 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(2) - (2)].id), 0);
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, (yyval.node));
		    /*%
			$$ = mlhs_add_star(mlhs_new(), $$);
		    %*/
		    }
    break;

  case 372:

/* Line 1806 of yacc.c  */
#line 3345 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(2) - (4)].id), 0);
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, NEW_POSTARG((yyval.node), (yyvsp[(4) - (4)].node)));
		    /*%
		      #if 0
		      TODO: Check me
		      #endif
			$$ = mlhs_add_star($$, $4);
		    %*/
		    }
    break;

  case 373:

/* Line 1806 of yacc.c  */
#line 3357 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, -1);
		    /*%
			$$ = mlhs_add_star(mlhs_new(), Qnil);
		    %*/
		    }
    break;

  case 374:

/* Line 1806 of yacc.c  */
#line 3365 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_MASGN(0, NEW_POSTARG(-1, (yyvsp[(3) - (3)].node)));
		    /*%
			$$ = mlhs_add_star(mlhs_new(), Qnil);
		    %*/
		    }
    break;

  case 375:

/* Line 1806 of yacc.c  */
#line 3376 "parse.y"
    {
			(yyval.node) = new_args_tail((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].id));
		    }
    break;

  case 376:

/* Line 1806 of yacc.c  */
#line 3380 "parse.y"
    {
			(yyval.node) = new_args_tail((yyvsp[(1) - (2)].node), Qnone, (yyvsp[(2) - (2)].id));
		    }
    break;

  case 377:

/* Line 1806 of yacc.c  */
#line 3384 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, (yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].id));
		    }
    break;

  case 378:

/* Line 1806 of yacc.c  */
#line 3388 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, Qnone, (yyvsp[(1) - (1)].id));
		    }
    break;

  case 379:

/* Line 1806 of yacc.c  */
#line 3394 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 380:

/* Line 1806 of yacc.c  */
#line 3398 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, Qnone, Qnone);
		    }
    break;

  case 381:

/* Line 1806 of yacc.c  */
#line 3404 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].id), Qnone, (yyvsp[(6) - (6)].node));
		    }
    break;

  case 382:

/* Line 1806 of yacc.c  */
#line 3408 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (8)].node), (yyvsp[(3) - (8)].node), (yyvsp[(5) - (8)].id), (yyvsp[(7) - (8)].node), (yyvsp[(8) - (8)].node));
		    }
    break;

  case 383:

/* Line 1806 of yacc.c  */
#line 3412 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), Qnone, Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 384:

/* Line 1806 of yacc.c  */
#line 3416 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), Qnone, (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 385:

/* Line 1806 of yacc.c  */
#line 3420 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (4)].node), Qnone, (yyvsp[(3) - (4)].id), Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 386:

/* Line 1806 of yacc.c  */
#line 3424 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (2)].node), Qnone, 1, Qnone, new_args_tail(Qnone, Qnone, Qnone));
		    /*%%%*/
		    /*%
                        dispatch1(excessed_comma, $$);
		    %*/
		    }
    break;

  case 387:

/* Line 1806 of yacc.c  */
#line 3432 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), Qnone, (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 388:

/* Line 1806 of yacc.c  */
#line 3436 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (2)].node), Qnone, Qnone, Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 389:

/* Line 1806 of yacc.c  */
#line 3440 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 390:

/* Line 1806 of yacc.c  */
#line 3444 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 391:

/* Line 1806 of yacc.c  */
#line 3448 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (2)].node), Qnone, Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 392:

/* Line 1806 of yacc.c  */
#line 3452 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (4)].node), Qnone, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 393:

/* Line 1806 of yacc.c  */
#line 3456 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, (yyvsp[(1) - (2)].id), Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 394:

/* Line 1806 of yacc.c  */
#line 3460 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 395:

/* Line 1806 of yacc.c  */
#line 3464 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, Qnone, Qnone, (yyvsp[(1) - (1)].node));
		    }
    break;

  case 397:

/* Line 1806 of yacc.c  */
#line 3471 "parse.y"
    {
			command_start = TRUE;
		    }
    break;

  case 398:

/* Line 1806 of yacc.c  */
#line 3477 "parse.y"
    {
			current_arg = 0;
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil,Qnil,Qnil),
                                          escape_Qundef($2));
		    %*/
		    }
    break;

  case 399:

/* Line 1806 of yacc.c  */
#line 3487 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = blockvar_new(params_new(Qnil,Qnil,Qnil,Qnil,Qnil,Qnil,Qnil),
                                          Qnil);
		    %*/
		    }
    break;

  case 400:

/* Line 1806 of yacc.c  */
#line 3496 "parse.y"
    {
			current_arg = 0;
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (4)].node);
		    /*%
			$$ = blockvar_new(escape_Qundef($2), escape_Qundef($3));
		    %*/
		    }
    break;

  case 401:

/* Line 1806 of yacc.c  */
#line 3508 "parse.y"
    {
		      (yyval.node) = 0;
		    }
    break;

  case 402:

/* Line 1806 of yacc.c  */
#line 3512 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = $3;
		    %*/
		    }
    break;

  case 405:

/* Line 1806 of yacc.c  */
#line 3538 "parse.y"
    {
			new_bv(get_id((yyvsp[(1) - (1)].id)));
		    /*%%%*/
		    /*%
			$$ = get_value($1);
		    %*/
		    }
    break;

  case 406:

/* Line 1806 of yacc.c  */
#line 3546 "parse.y"
    {
			(yyval.node) = 0;
		    }
    break;

  case 407:

/* Line 1806 of yacc.c  */
#line 3551 "parse.y"
    {
			(yyval.vars) = dyna_push();
		    }
    break;

  case 408:

/* Line 1806 of yacc.c  */
#line 3554 "parse.y"
    {
			(yyval.num) = lpar_beg;
			lpar_beg = ++paren_nest;
		    }
    break;

  case 409:

/* Line 1806 of yacc.c  */
#line 3559 "parse.y"
    {
			(yyval.num) = ruby_sourceline;
		    }
    break;

  case 410:

/* Line 1806 of yacc.c  */
#line 3562 "parse.y"
    {
			(yyval.val) = cmdarg_stack;
			cmdarg_stack = 0;
		    }
    break;

  case 411:

/* Line 1806 of yacc.c  */
#line 3567 "parse.y"
    {
			lpar_beg = (yyvsp[(2) - (6)].num);
			cmdarg_stack = (yyvsp[(5) - (6)].val);
			CMDARG_LEXPOP();
		    /*%%%*/
			(yyval.node) = NEW_LAMBDA((yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
			nd_set_line((yyval.node), (yyvsp[(4) - (6)].num));
		    /*%
			$$ = dispatch2(lambda, $3, $6);
		    %*/
			dyna_pop((yyvsp[(1) - (6)].vars));
		    }
    break;

  case 412:

/* Line 1806 of yacc.c  */
#line 3582 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (4)].node);
		    /*%
			$$ = dispatch1(paren, $2);
		    %*/
		    }
    break;

  case 413:

/* Line 1806 of yacc.c  */
#line 3590 "parse.y"
    {
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    }
    break;

  case 414:

/* Line 1806 of yacc.c  */
#line 3596 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 415:

/* Line 1806 of yacc.c  */
#line 3600 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    }
    break;

  case 416:

/* Line 1806 of yacc.c  */
#line 3606 "parse.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*% %*/
		    }
    break;

  case 417:

/* Line 1806 of yacc.c  */
#line 3615 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(2) - (5)].num));
		    /*%
			$$ = dispatch2(do_block, escape_Qundef($3), $4);
		    %*/
			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 418:

/* Line 1806 of yacc.c  */
#line 3627 "parse.y"
    {
		    /*%%%*/
			if (nd_type((yyvsp[(1) - (2)].node)) == NODE_YIELD) {
			    compile_error(PARSER_ARG "block given to yield");
			}
			else {
			    block_dup_check((yyvsp[(1) - (2)].node)->nd_args, (yyvsp[(2) - (2)].node));
			}
			(yyvsp[(2) - (2)].node)->nd_iter = (yyvsp[(1) - (2)].node);
			(yyval.node) = (yyvsp[(2) - (2)].node);
			fixpos((yyval.node), (yyvsp[(1) - (2)].node));
		    /*%
			$$ = method_add_block($1, $2);
		    %*/
		    }
    break;

  case 419:

/* Line 1806 of yacc.c  */
#line 3643 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_QCALL((yyvsp[(2) - (4)].id), (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch3(call, $1, $2, $3);
			$$ = method_optarg($$, $4);
		    %*/
		    }
    break;

  case 420:

/* Line 1806 of yacc.c  */
#line 3652 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
			(yyvsp[(5) - (5)].node)->nd_iter = NEW_QCALL((yyvsp[(2) - (5)].id), (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].node));
			(yyval.node) = (yyvsp[(5) - (5)].node);
			fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    /*%
			$$ = dispatch4(command_call, $1, $2, $3, $4);
			$$ = method_add_block($$, $5);
		    %*/
		    }
    break;

  case 421:

/* Line 1806 of yacc.c  */
#line 3664 "parse.y"
    {
		    /*%%%*/
			block_dup_check((yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
			(yyvsp[(5) - (5)].node)->nd_iter = NEW_QCALL((yyvsp[(2) - (5)].id), (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(4) - (5)].node));
			(yyval.node) = (yyvsp[(5) - (5)].node);
			fixpos((yyval.node), (yyvsp[(1) - (5)].node));
		    /*%
			$$ = dispatch4(command_call, $1, $2, $3, $4);
			$$ = method_add_block($$, $5);
		    %*/
		    }
    break;

  case 422:

/* Line 1806 of yacc.c  */
#line 3678 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node);
			(yyval.node)->nd_args = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = method_arg(dispatch1(fcall, $1), $2);
		    %*/
		    }
    break;

  case 423:

/* Line 1806 of yacc.c  */
#line 3687 "parse.y"
    {
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*% %*/
		    }
    break;

  case 424:

/* Line 1806 of yacc.c  */
#line 3693 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_QCALL((yyvsp[(2) - (5)].id), (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(4) - (5)].num));
		    /*%
			$$ = dispatch3(call, $1, $2, $3);
			$$ = method_optarg($$, $5);
		    %*/
		    }
    break;

  case 425:

/* Line 1806 of yacc.c  */
#line 3703 "parse.y"
    {
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*% %*/
		    }
    break;

  case 426:

/* Line 1806 of yacc.c  */
#line 3709 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CALL((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].id), (yyvsp[(5) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(4) - (5)].num));
		    /*%
			$$ = dispatch3(call, $1, ripper_id2sym(idCOLON2), $3);
			$$ = method_optarg($$, $5);
		    %*/
		    }
    break;

  case 427:

/* Line 1806 of yacc.c  */
#line 3719 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CALL((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].id), 0);
		    /*%
			$$ = dispatch3(call, $1, ID2SYM(idCOLON2), $3);
		    %*/
		    }
    break;

  case 428:

/* Line 1806 of yacc.c  */
#line 3727 "parse.y"
    {
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*% %*/
		    }
    break;

  case 429:

/* Line 1806 of yacc.c  */
#line 3733 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_QCALL((yyvsp[(2) - (4)].id), (yyvsp[(1) - (4)].node), idCall, (yyvsp[(4) - (4)].node));
			nd_set_line((yyval.node), (yyvsp[(3) - (4)].num));
		    /*%
			$$ = dispatch3(call, $1, $2, ID2SYM(idCall));
			$$ = method_optarg($$, $4);
		    %*/
		    }
    break;

  case 430:

/* Line 1806 of yacc.c  */
#line 3743 "parse.y"
    {
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*% %*/
		    }
    break;

  case 431:

/* Line 1806 of yacc.c  */
#line 3749 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CALL((yyvsp[(1) - (4)].node), idCall, (yyvsp[(4) - (4)].node));
			nd_set_line((yyval.node), (yyvsp[(3) - (4)].num));
		    /*%
			$$ = dispatch3(call, $1, ID2SYM(idCOLON2),
				       ID2SYM(idCall));
			$$ = method_optarg($$, $4);
		    %*/
		    }
    break;

  case 432:

/* Line 1806 of yacc.c  */
#line 3760 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_SUPER((yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch1(super, $2);
		    %*/
		    }
    break;

  case 433:

/* Line 1806 of yacc.c  */
#line 3768 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ZSUPER();
		    /*%
			$$ = dispatch0(zsuper);
		    %*/
		    }
    break;

  case 434:

/* Line 1806 of yacc.c  */
#line 3776 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(1) - (4)].node) && nd_type((yyvsp[(1) - (4)].node)) == NODE_SELF)
			    (yyval.node) = NEW_FCALL(tAREF, (yyvsp[(3) - (4)].node));
			else
			    (yyval.node) = NEW_CALL((yyvsp[(1) - (4)].node), tAREF, (yyvsp[(3) - (4)].node));
			fixpos((yyval.node), (yyvsp[(1) - (4)].node));
		    /*%
			$$ = dispatch2(aref, $1, escape_Qundef($3));
		    %*/
		    }
    break;

  case 435:

/* Line 1806 of yacc.c  */
#line 3790 "parse.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
                    %*/
		    }
    break;

  case 436:

/* Line 1806 of yacc.c  */
#line 3799 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(2) - (5)].num));
		    /*%
			$$ = dispatch2(brace_block, escape_Qundef($3), $4);
		    %*/
			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 437:

/* Line 1806 of yacc.c  */
#line 3809 "parse.y"
    {
			(yyvsp[(1) - (1)].vars) = dyna_push();
		    /*%%%*/
			(yyval.num) = ruby_sourceline;
		    /*%
                    %*/
		    }
    break;

  case 438:

/* Line 1806 of yacc.c  */
#line 3818 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ITER((yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node));
			nd_set_line((yyval.node), (yyvsp[(2) - (5)].num));
		    /*%
			$$ = dispatch2(do_block, escape_Qundef($3), $4);
		    %*/
			dyna_pop((yyvsp[(1) - (5)].vars));
		    }
    break;

  case 439:

/* Line 1806 of yacc.c  */
#line 3832 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_WHEN((yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));
		    /*%
			$$ = dispatch3(when, $2, $4, escape_Qundef($5));
		    %*/
		    }
    break;

  case 442:

/* Line 1806 of yacc.c  */
#line 3848 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(3) - (6)].node)) {
			    (yyvsp[(3) - (6)].node) = node_assign((yyvsp[(3) - (6)].node), NEW_ERRINFO());
			    (yyvsp[(5) - (6)].node) = block_append((yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node));
			}
			(yyval.node) = NEW_RESBODY((yyvsp[(2) - (6)].node), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
			fixpos((yyval.node), (yyvsp[(2) - (6)].node)?(yyvsp[(2) - (6)].node):(yyvsp[(5) - (6)].node));
		    /*%
			$$ = dispatch4(rescue,
				       escape_Qundef($2),
				       escape_Qundef($3),
				       escape_Qundef($5),
				       escape_Qundef($6));
		    %*/
		    }
    break;

  case 444:

/* Line 1806 of yacc.c  */
#line 3868 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIST((yyvsp[(1) - (1)].node));
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 445:

/* Line 1806 of yacc.c  */
#line 3876 "parse.y"
    {
		    /*%%%*/
			if (!((yyval.node) = splat_array((yyvsp[(1) - (1)].node)))) (yyval.node) = (yyvsp[(1) - (1)].node);
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 447:

/* Line 1806 of yacc.c  */
#line 3887 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 449:

/* Line 1806 of yacc.c  */
#line 3894 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    /*%
			$$ = dispatch1(ensure, $2);
		    %*/
		    }
    break;

  case 452:

/* Line 1806 of yacc.c  */
#line 3906 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_LIT(ID2SYM((yyvsp[(1) - (1)].id)));
		    /*%
			$$ = dispatch1(symbol_literal, $1);
		    %*/
		    }
    break;

  case 454:

/* Line 1806 of yacc.c  */
#line 3917 "parse.y"
    {
		    /*%%%*/
			NODE *node = (yyvsp[(1) - (1)].node);
			if (!node) {
			    node = NEW_STR(STR_NEW0());
			}
			else {
			    node = evstr2dstr(node);
			}
			(yyval.node) = node;
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 457:

/* Line 1806 of yacc.c  */
#line 3936 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch2(string_concat, $1, $2);
		    %*/
		    }
    break;

  case 458:

/* Line 1806 of yacc.c  */
#line 3946 "parse.y"
    {
			heredoc_dedent((yyvsp[(2) - (3)].node));
			heredoc_indent = 0;
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(string_literal, $2);
		    %*/
		    }
    break;

  case 459:

/* Line 1806 of yacc.c  */
#line 3958 "parse.y"
    {
		    /*%%%*/
			NODE *node = (yyvsp[(2) - (3)].node);
		    /*%
		    %*/
			heredoc_dedent((yyvsp[(2) - (3)].node));
			heredoc_indent = 0;
		    /*%%%*/
			if (!node) {
			    node = NEW_XSTR(STR_NEW0());
			}
			else {
			    switch (nd_type(node)) {
			      case NODE_STR:
				nd_set_type(node, NODE_XSTR);
				break;
			      case NODE_DSTR:
				nd_set_type(node, NODE_DXSTR);
				break;
			      default:
				node = NEW_NODE(NODE_DXSTR, Qnil, 1, NEW_LIST(node));
				break;
			    }
			}
			(yyval.node) = node;
		    /*%
			$$ = dispatch1(xstring_literal, $2);
		    %*/
		    }
    break;

  case 460:

/* Line 1806 of yacc.c  */
#line 3990 "parse.y"
    {
		    /*%%%*/
			int options = (yyvsp[(3) - (3)].num);
			NODE *node = (yyvsp[(2) - (3)].node);
			NODE *list, *prev;
			if (!node) {
			    node = NEW_LIT(reg_compile(STR_NEW0(), options));
			}
			else switch (nd_type(node)) {
			  case NODE_STR:
			    {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = reg_compile(src, options);
			    }
			    break;
			  default:
			    node = NEW_NODE(NODE_DSTR, STR_NEW0(), 1, NEW_LIST(node));
			  case NODE_DSTR:
			    if (options & RE_OPTION_ONCE) {
				nd_set_type(node, NODE_DREGX_ONCE);
			    }
			    else {
				nd_set_type(node, NODE_DREGX);
			    }
			    node->nd_cflag = options & RE_OPTION_MASK;
			    if (!NIL_P(node->nd_lit)) reg_fragment_check(node->nd_lit, options);
			    for (list = (prev = node)->nd_next; list; list = list->nd_next) {
				if (nd_type(list->nd_head) == NODE_STR) {
				    VALUE tail = list->nd_head->nd_lit;
				    if (reg_fragment_check(tail, options) && prev && !NIL_P(prev->nd_lit)) {
					VALUE lit = prev == node ? prev->nd_lit : prev->nd_head->nd_lit;
					if (!literal_concat0(parser, lit, tail)) {
					    node = 0;
					    break;
					}
					rb_str_resize(tail, 0);
					prev->nd_next = list->nd_next;
					rb_gc_force_recycle((VALUE)list->nd_head);
					rb_gc_force_recycle((VALUE)list);
					list = prev;
				    }
				    else {
					prev = list;
				    }
                                }
				else {
				    prev = 0;
				}
                            }
			    if (!node->nd_next) {
				VALUE src = node->nd_lit;
				nd_set_type(node, NODE_LIT);
				node->nd_lit = reg_compile(src, options);
			    }
			    break;
			}
			(yyval.node) = node;
		    /*%
			VALUE re = $2, opt = $3, src = 0, err;
			int options = 0;
			if (ripper_is_node_yylval(re)) {
			    $2 = RNODE(re)->nd_rval;
			    src = RNODE(re)->nd_cval;
			}
			if (ripper_is_node_yylval(opt)) {
			    $3 = RNODE(opt)->nd_rval;
			    options = (int)RNODE(opt)->nd_tag;
			}
			if (src && NIL_P(rb_parser_reg_compile(parser, src, options, &err))) {
			    compile_error(PARSER_ARG "%"PRIsVALUE, err);
			}
			$$ = dispatch2(regexp_literal, $2, $3);
		    %*/
		    }
    break;

  case 461:

/* Line 1806 of yacc.c  */
#line 4068 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ZARRAY();
		    /*%
			$$ = dispatch0(words_new);
			$$ = dispatch1(array, $$);
		    %*/
		    }
    break;

  case 462:

/* Line 1806 of yacc.c  */
#line 4077 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(array, $2);
		    %*/
		    }
    break;

  case 463:

/* Line 1806 of yacc.c  */
#line 4087 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(words_new);
		    %*/
		    }
    break;

  case 464:

/* Line 1806 of yacc.c  */
#line 4095 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), evstr2dstr((yyvsp[(2) - (3)].node)));
		    /*%
			$$ = dispatch2(words_add, $1, $2);
		    %*/
		    }
    break;

  case 466:

/* Line 1806 of yacc.c  */
#line 4113 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch2(word_add, $1, $2);
		    %*/
		    }
    break;

  case 467:

/* Line 1806 of yacc.c  */
#line 4123 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ZARRAY();
		    /*%
			$$ = dispatch0(symbols_new);
			$$ = dispatch1(array, $$);
		    %*/
		    }
    break;

  case 468:

/* Line 1806 of yacc.c  */
#line 4132 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(array, $2);
		    %*/
		    }
    break;

  case 469:

/* Line 1806 of yacc.c  */
#line 4142 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(symbols_new);
		    %*/
		    }
    break;

  case 470:

/* Line 1806 of yacc.c  */
#line 4150 "parse.y"
    {
		    /*%%%*/
			(yyvsp[(2) - (3)].node) = evstr2dstr((yyvsp[(2) - (3)].node));
			if (nd_type((yyvsp[(2) - (3)].node)) == NODE_DSTR) {
			    nd_set_type((yyvsp[(2) - (3)].node), NODE_DSYM);
			}
			else {
			    nd_set_type((yyvsp[(2) - (3)].node), NODE_LIT);
			    (yyvsp[(2) - (3)].node)->nd_lit = rb_str_intern((yyvsp[(2) - (3)].node)->nd_lit);
			}
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    /*%
			$$ = dispatch2(symbols_add, $1, $2);
		    %*/
		    }
    break;

  case 471:

/* Line 1806 of yacc.c  */
#line 4168 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ZARRAY();
		    /*%
			$$ = dispatch0(qwords_new);
			$$ = dispatch1(array, $$);
		    %*/
		    }
    break;

  case 472:

/* Line 1806 of yacc.c  */
#line 4177 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(array, $2);
		    %*/
		    }
    break;

  case 473:

/* Line 1806 of yacc.c  */
#line 4187 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_ZARRAY();
		    /*%
			$$ = dispatch0(qsymbols_new);
			$$ = dispatch1(array, $$);
		    %*/
		    }
    break;

  case 474:

/* Line 1806 of yacc.c  */
#line 4196 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(array, $2);
		    %*/
		    }
    break;

  case 475:

/* Line 1806 of yacc.c  */
#line 4206 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(qwords_new);
		    %*/
		    }
    break;

  case 476:

/* Line 1806 of yacc.c  */
#line 4214 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    /*%
			$$ = dispatch2(qwords_add, $1, $2);
		    %*/
		    }
    break;

  case 477:

/* Line 1806 of yacc.c  */
#line 4224 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(qsymbols_new);
		    %*/
		    }
    break;

  case 478:

/* Line 1806 of yacc.c  */
#line 4232 "parse.y"
    {
		    /*%%%*/
			VALUE lit;
			lit = (yyvsp[(2) - (3)].node)->nd_lit;
			(yyvsp[(2) - (3)].node)->nd_lit = ID2SYM(rb_intern_str(lit));
			nd_set_type((yyvsp[(2) - (3)].node), NODE_LIT);
			(yyval.node) = list_append((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));
		    /*%
			$$ = dispatch2(qsymbols_add, $1, $2);
		    %*/
		    }
    break;

  case 479:

/* Line 1806 of yacc.c  */
#line 4246 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(string_content);
		    %*/
		    }
    break;

  case 480:

/* Line 1806 of yacc.c  */
#line 4254 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch2(string_add, $1, $2);
		    %*/
		    }
    break;

  case 481:

/* Line 1806 of yacc.c  */
#line 4264 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = dispatch0(xstring_new);
		    %*/
		    }
    break;

  case 482:

/* Line 1806 of yacc.c  */
#line 4272 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = literal_concat((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch2(xstring_add, $1, $2);
		    %*/
		    }
    break;

  case 483:

/* Line 1806 of yacc.c  */
#line 4282 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = ripper_new_yylval(0, dispatch0(regexp_new), 0);
		    %*/
		    }
    break;

  case 484:

/* Line 1806 of yacc.c  */
#line 4290 "parse.y"
    {
		    /*%%%*/
			NODE *head = (yyvsp[(1) - (2)].node), *tail = (yyvsp[(2) - (2)].node);
			if (!head) {
			    (yyval.node) = tail;
			}
			else if (!tail) {
			    (yyval.node) = head;
			}
			else {
			    switch (nd_type(head)) {
			      case NODE_STR:
				nd_set_type(head, NODE_DSTR);
				break;
			      case NODE_DSTR:
				break;
			      default:
				head = list_append(NEW_DSTR(Qnil), head);
				break;
			    }
			    (yyval.node) = list_append(head, tail);
			}
		    /*%
		        VALUE s1 = 1, s2 = 0, n1 = $1, n2 = $2;
			if (ripper_is_node_yylval(n1)) {
			    s1 = RNODE(n1)->nd_cval;
			    n1 = RNODE(n1)->nd_rval;
			}
			if (ripper_is_node_yylval(n2)) {
			    s2 = RNODE(n2)->nd_cval;
			    n2 = RNODE(n2)->nd_rval;
			}
			$$ = dispatch2(regexp_add, n1, n2);
			if (!s1 && s2) {
			    $$ = ripper_new_yylval(0, $$, s2);
			}
		    %*/
		    }
    break;

  case 486:

/* Line 1806 of yacc.c  */
#line 4332 "parse.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
			SET_LEX_STATE(EXPR_BEG);
		    }
    break;

  case 487:

/* Line 1806 of yacc.c  */
#line 4338 "parse.y"
    {
			lex_strterm = (yyvsp[(2) - (3)].node);
		    /*%%%*/
			(yyval.node) = NEW_EVSTR((yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch1(string_dvar, $3);
		    %*/
		    }
    break;

  case 488:

/* Line 1806 of yacc.c  */
#line 4347 "parse.y"
    {
			(yyvsp[(1) - (1)].val) = cond_stack;
			(yyval.val) = cmdarg_stack;
			cond_stack = 0;
			cmdarg_stack = 0;
		    }
    break;

  case 489:

/* Line 1806 of yacc.c  */
#line 4353 "parse.y"
    {
			(yyval.node) = lex_strterm;
			lex_strterm = 0;
		    }
    break;

  case 490:

/* Line 1806 of yacc.c  */
#line 4357 "parse.y"
    {
			(yyval.num) = lex_state;
			SET_LEX_STATE(EXPR_BEG);
		    }
    break;

  case 491:

/* Line 1806 of yacc.c  */
#line 4361 "parse.y"
    {
			(yyval.num) = brace_nest;
			brace_nest = 0;
		    }
    break;

  case 492:

/* Line 1806 of yacc.c  */
#line 4365 "parse.y"
    {
			(yyval.num) = heredoc_indent;
			heredoc_indent = 0;
		    }
    break;

  case 493:

/* Line 1806 of yacc.c  */
#line 4370 "parse.y"
    {
			cond_stack = (yyvsp[(1) - (8)].val);
			cmdarg_stack = (yyvsp[(2) - (8)].val);
			lex_strterm = (yyvsp[(3) - (8)].node);
			SET_LEX_STATE((yyvsp[(4) - (8)].num));
			brace_nest = (yyvsp[(5) - (8)].num);
			heredoc_indent = (yyvsp[(6) - (8)].num);
			heredoc_line_indent = -1;
		    /*%%%*/
			if ((yyvsp[(7) - (8)].node)) (yyvsp[(7) - (8)].node)->flags &= ~NODE_FL_NEWLINE;
			(yyval.node) = new_evstr((yyvsp[(7) - (8)].node));
		    /*%
			$$ = dispatch1(string_embexpr, $7);
		    %*/
		    }
    break;

  case 494:

/* Line 1806 of yacc.c  */
#line 4388 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_GVAR((yyvsp[(1) - (1)].id));
		    /*%
			$$ = dispatch1(var_ref, $1);
		    %*/
		    }
    break;

  case 495:

/* Line 1806 of yacc.c  */
#line 4396 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_IVAR((yyvsp[(1) - (1)].id));
		    /*%
			$$ = dispatch1(var_ref, $1);
		    %*/
		    }
    break;

  case 496:

/* Line 1806 of yacc.c  */
#line 4404 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = NEW_CVAR((yyvsp[(1) - (1)].id));
		    /*%
			$$ = dispatch1(var_ref, $1);
		    %*/
		    }
    break;

  case 498:

/* Line 1806 of yacc.c  */
#line 4415 "parse.y"
    {
			SET_LEX_STATE(EXPR_END);
		    /*%%%*/
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    /*%
			$$ = dispatch1(symbol, $2);
		    %*/
		    }
    break;

  case 503:

/* Line 1806 of yacc.c  */
#line 4432 "parse.y"
    {
			SET_LEX_STATE(EXPR_END);
		    /*%%%*/
			(yyval.node) = dsym_node((yyvsp[(2) - (3)].node));
		    /*%
			$$ = dispatch1(dyna_symbol, $2);
		    %*/
		    }
    break;

  case 505:

/* Line 1806 of yacc.c  */
#line 4444 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (2)].node);
			(yyval.node)->nd_lit = negate_lit((yyval.node)->nd_lit);
		    /*%
			$$ = dispatch2(unary, ID2SYM(idUMinus), $2);
		    %*/
		    }
    break;

  case 515:

/* Line 1806 of yacc.c  */
#line 4467 "parse.y"
    {ifndef_ripper((yyval.id) = keyword_nil);}
    break;

  case 516:

/* Line 1806 of yacc.c  */
#line 4468 "parse.y"
    {ifndef_ripper((yyval.id) = keyword_self);}
    break;

  case 517:

/* Line 1806 of yacc.c  */
#line 4469 "parse.y"
    {ifndef_ripper((yyval.id) = keyword_true);}
    break;

  case 518:

/* Line 1806 of yacc.c  */
#line 4470 "parse.y"
    {ifndef_ripper((yyval.id) = keyword_false);}
    break;

  case 519:

/* Line 1806 of yacc.c  */
#line 4471 "parse.y"
    {ifndef_ripper((yyval.id) = keyword__FILE__);}
    break;

  case 520:

/* Line 1806 of yacc.c  */
#line 4472 "parse.y"
    {ifndef_ripper((yyval.id) = keyword__LINE__);}
    break;

  case 521:

/* Line 1806 of yacc.c  */
#line 4473 "parse.y"
    {ifndef_ripper((yyval.id) = keyword__ENCODING__);}
    break;

  case 522:

/* Line 1806 of yacc.c  */
#line 4477 "parse.y"
    {
		    /*%%%*/
			if (!((yyval.node) = gettable((yyvsp[(1) - (1)].id)))) (yyval.node) = NEW_BEGIN(0);
		    /*%
			if (id_is_var(get_id($1))) {
			    $$ = dispatch1(var_ref, $1);
			}
			else {
			    $$ = dispatch1(vcall, $1);
			}
		    %*/
		    }
    break;

  case 523:

/* Line 1806 of yacc.c  */
#line 4490 "parse.y"
    {
		    /*%%%*/
			if (!((yyval.node) = gettable((yyvsp[(1) - (1)].id)))) (yyval.node) = NEW_BEGIN(0);
		    /*%
			$$ = dispatch1(var_ref, $1);
		    %*/
		    }
    break;

  case 524:

/* Line 1806 of yacc.c  */
#line 4500 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    /*%%%*/
		    /*%
			$$ = dispatch1(var_field, $$);
		    %*/
		    }
    break;

  case 525:

/* Line 1806 of yacc.c  */
#line 4508 "parse.y"
    {
		        (yyval.node) = assignable((yyvsp[(1) - (1)].id), 0);
		    /*%%%*/
		    /*%
			$$ = dispatch1(var_field, $$);
		    %*/
		    }
    break;

  case 528:

/* Line 1806 of yacc.c  */
#line 4522 "parse.y"
    {
			SET_LEX_STATE(EXPR_BEG);
			command_start = TRUE;
		    }
    break;

  case 529:

/* Line 1806 of yacc.c  */
#line 4527 "parse.y"
    {
			(yyval.node) = (yyvsp[(3) - (4)].node);
		    }
    break;

  case 530:

/* Line 1806 of yacc.c  */
#line 4531 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = Qnil;
		    %*/
		    }
    break;

  case 531:

/* Line 1806 of yacc.c  */
#line 4541 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(paren, $2);
		    %*/
			SET_LEX_STATE(EXPR_BEG);
			command_start = TRUE;
		    }
    break;

  case 532:

/* Line 1806 of yacc.c  */
#line 4550 "parse.y"
    {
			(yyval.num) = parser->in_kwarg;
			parser->in_kwarg = 1;
			lex_state |= EXPR_LABEL; /* force for args */
		    }
    break;

  case 533:

/* Line 1806 of yacc.c  */
#line 4556 "parse.y"
    {
			parser->in_kwarg = !!(yyvsp[(1) - (3)].num);
			(yyval.node) = (yyvsp[(2) - (3)].node);
			SET_LEX_STATE(EXPR_BEG);
			command_start = TRUE;
		    }
    break;

  case 534:

/* Line 1806 of yacc.c  */
#line 4565 "parse.y"
    {
			(yyval.node) = new_args_tail((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), (yyvsp[(4) - (4)].id));
		    }
    break;

  case 535:

/* Line 1806 of yacc.c  */
#line 4569 "parse.y"
    {
			(yyval.node) = new_args_tail((yyvsp[(1) - (2)].node), Qnone, (yyvsp[(2) - (2)].id));
		    }
    break;

  case 536:

/* Line 1806 of yacc.c  */
#line 4573 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, (yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].id));
		    }
    break;

  case 537:

/* Line 1806 of yacc.c  */
#line 4577 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, Qnone, (yyvsp[(1) - (1)].id));
		    }
    break;

  case 538:

/* Line 1806 of yacc.c  */
#line 4583 "parse.y"
    {
			(yyval.node) = (yyvsp[(2) - (2)].node);
		    }
    break;

  case 539:

/* Line 1806 of yacc.c  */
#line 4587 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, Qnone, Qnone);
		    }
    break;

  case 540:

/* Line 1806 of yacc.c  */
#line 4593 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].id), Qnone, (yyvsp[(6) - (6)].node));
		    }
    break;

  case 541:

/* Line 1806 of yacc.c  */
#line 4597 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (8)].node), (yyvsp[(3) - (8)].node), (yyvsp[(5) - (8)].id), (yyvsp[(7) - (8)].node), (yyvsp[(8) - (8)].node));
		    }
    break;

  case 542:

/* Line 1806 of yacc.c  */
#line 4601 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node), Qnone, Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 543:

/* Line 1806 of yacc.c  */
#line 4605 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].node), Qnone, (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 544:

/* Line 1806 of yacc.c  */
#line 4609 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (4)].node), Qnone, (yyvsp[(3) - (4)].id), Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 545:

/* Line 1806 of yacc.c  */
#line 4613 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (6)].node), Qnone, (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 546:

/* Line 1806 of yacc.c  */
#line 4617 "parse.y"
    {
			(yyval.node) = new_args((yyvsp[(1) - (2)].node), Qnone, Qnone, Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 547:

/* Line 1806 of yacc.c  */
#line 4621 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].id), Qnone, (yyvsp[(4) - (4)].node));
		    }
    break;

  case 548:

/* Line 1806 of yacc.c  */
#line 4625 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (6)].node), (yyvsp[(3) - (6)].id), (yyvsp[(5) - (6)].node), (yyvsp[(6) - (6)].node));
		    }
    break;

  case 549:

/* Line 1806 of yacc.c  */
#line 4629 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (2)].node), Qnone, Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 550:

/* Line 1806 of yacc.c  */
#line 4633 "parse.y"
    {
			(yyval.node) = new_args(Qnone, (yyvsp[(1) - (4)].node), Qnone, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 551:

/* Line 1806 of yacc.c  */
#line 4637 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, (yyvsp[(1) - (2)].id), Qnone, (yyvsp[(2) - (2)].node));
		    }
    break;

  case 552:

/* Line 1806 of yacc.c  */
#line 4641 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
		    }
    break;

  case 553:

/* Line 1806 of yacc.c  */
#line 4645 "parse.y"
    {
			(yyval.node) = new_args(Qnone, Qnone, Qnone, Qnone, (yyvsp[(1) - (1)].node));
		    }
    break;

  case 554:

/* Line 1806 of yacc.c  */
#line 4649 "parse.y"
    {
			(yyval.node) = new_args_tail(Qnone, Qnone, Qnone);
			(yyval.node) = new_args(Qnone, Qnone, Qnone, Qnone, (yyval.node));
		    }
    break;

  case 555:

/* Line 1806 of yacc.c  */
#line 4656 "parse.y"
    {
		    /*%%%*/
			yyerror("formal argument cannot be a constant");
			(yyval.id) = 0;
		    /*%
			$$ = dispatch1(param_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 556:

/* Line 1806 of yacc.c  */
#line 4666 "parse.y"
    {
		    /*%%%*/
			yyerror("formal argument cannot be an instance variable");
			(yyval.id) = 0;
		    /*%
			$$ = dispatch1(param_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 557:

/* Line 1806 of yacc.c  */
#line 4676 "parse.y"
    {
		    /*%%%*/
			yyerror("formal argument cannot be a global variable");
			(yyval.id) = 0;
		    /*%
			$$ = dispatch1(param_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 558:

/* Line 1806 of yacc.c  */
#line 4686 "parse.y"
    {
		    /*%%%*/
			yyerror("formal argument cannot be a class variable");
			(yyval.id) = 0;
		    /*%
			$$ = dispatch1(param_error, $1);
			ripper_error();
		    %*/
		    }
    break;

  case 560:

/* Line 1806 of yacc.c  */
#line 4699 "parse.y"
    {
			formal_argument(get_id((yyvsp[(1) - (1)].id)));
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 561:

/* Line 1806 of yacc.c  */
#line 4706 "parse.y"
    {
			ID id = get_id((yyvsp[(1) - (1)].id));
			arg_var(id);
			current_arg = id;
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 562:

/* Line 1806 of yacc.c  */
#line 4715 "parse.y"
    {
			current_arg = 0;
		    /*%%%*/
			(yyval.node) = NEW_ARGS_AUX((yyvsp[(1) - (1)].id), 1);
		    /*%
			$$ = get_value($1);
		    %*/
		    }
    break;

  case 563:

/* Line 1806 of yacc.c  */
#line 4724 "parse.y"
    {
			ID tid = internal_id();
			arg_var(tid);
		    /*%%%*/
			if (dyna_in_block()) {
			    (yyvsp[(2) - (3)].node)->nd_value = NEW_DVAR(tid);
			}
			else {
			    (yyvsp[(2) - (3)].node)->nd_value = NEW_LVAR(tid);
			}
			(yyval.node) = NEW_ARGS_AUX(tid, 1);
			(yyval.node)->nd_next = (yyvsp[(2) - (3)].node);
		    /*%
			$$ = dispatch1(mlhs_paren, $2);
		    %*/
		    }
    break;

  case 565:

/* Line 1806 of yacc.c  */
#line 4750 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (3)].node);
			(yyval.node)->nd_plen++;
			(yyval.node)->nd_next = block_append((yyval.node)->nd_next, (yyvsp[(3) - (3)].node)->nd_next);
			rb_gc_force_recycle((VALUE)(yyvsp[(3) - (3)].node));
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 566:

/* Line 1806 of yacc.c  */
#line 4764 "parse.y"
    {
			ID id = get_id((yyvsp[(1) - (1)].id));
			arg_var(formal_argument(id));
			current_arg = id;
			(yyval.id) = (yyvsp[(1) - (1)].id);
		    }
    break;

  case 567:

/* Line 1806 of yacc.c  */
#line 4773 "parse.y"
    {
			current_arg = 0;
			(yyval.node) = assignable((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].node));
		    /*%%%*/
			(yyval.node) = new_kw_arg((yyval.node));
		    /*%
			$$ = rb_assoc_new($$, $2);
		    %*/
		    }
    break;

  case 568:

/* Line 1806 of yacc.c  */
#line 4783 "parse.y"
    {
			current_arg = 0;
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), (NODE *)-1);
		    /*%%%*/
			(yyval.node) = new_kw_arg((yyval.node));
		    /*%
			$$ = rb_assoc_new($$, 0);
		    %*/
		    }
    break;

  case 569:

/* Line 1806 of yacc.c  */
#line 4795 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (2)].id), (yyvsp[(2) - (2)].node));
		    /*%%%*/
			(yyval.node) = new_kw_arg((yyval.node));
		    /*%
			$$ = rb_assoc_new($$, $2);
		    %*/
		    }
    break;

  case 570:

/* Line 1806 of yacc.c  */
#line 4804 "parse.y"
    {
			(yyval.node) = assignable((yyvsp[(1) - (1)].id), (NODE *)-1);
		    /*%%%*/
			(yyval.node) = new_kw_arg((yyval.node));
		    /*%
			$$ = rb_assoc_new($$, 0);
		    %*/
		    }
    break;

  case 571:

/* Line 1806 of yacc.c  */
#line 4815 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 572:

/* Line 1806 of yacc.c  */
#line 4823 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = kwd_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 573:

/* Line 1806 of yacc.c  */
#line 4834 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 574:

/* Line 1806 of yacc.c  */
#line 4842 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = kwd_append((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 577:

/* Line 1806 of yacc.c  */
#line 4856 "parse.y"
    {
			shadowing_lvar(get_id((yyvsp[(2) - (2)].id)));
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    }
    break;

  case 578:

/* Line 1806 of yacc.c  */
#line 4861 "parse.y"
    {
			(yyval.id) = internal_id();
			arg_var((yyval.id));
		    }
    break;

  case 579:

/* Line 1806 of yacc.c  */
#line 4868 "parse.y"
    {
			current_arg = 0;
			(yyval.node) = assignable((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].node));
		    /*%%%*/
			(yyval.node) = NEW_OPT_ARG(0, (yyval.node));
		    /*%
			$$ = rb_assoc_new($$, $3);
		    %*/
		    }
    break;

  case 580:

/* Line 1806 of yacc.c  */
#line 4880 "parse.y"
    {
			current_arg = 0;
			(yyval.node) = assignable((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].node));
		    /*%%%*/
			(yyval.node) = NEW_OPT_ARG(0, (yyval.node));
		    /*%
			$$ = rb_assoc_new($$, $3);
		    %*/
		    }
    break;

  case 581:

/* Line 1806 of yacc.c  */
#line 4892 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 582:

/* Line 1806 of yacc.c  */
#line 4900 "parse.y"
    {
		    /*%%%*/
			NODE *opts = (yyvsp[(1) - (3)].node);

			while (opts->nd_next) {
			    opts = opts->nd_next;
			}
			opts->nd_next = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 583:

/* Line 1806 of yacc.c  */
#line 4916 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (1)].node);
		    /*%
			$$ = rb_ary_new3(1, $1);
		    %*/
		    }
    break;

  case 584:

/* Line 1806 of yacc.c  */
#line 4924 "parse.y"
    {
		    /*%%%*/
			NODE *opts = (yyvsp[(1) - (3)].node);

			while (opts->nd_next) {
			    opts = opts->nd_next;
			}
			opts->nd_next = (yyvsp[(3) - (3)].node);
			(yyval.node) = (yyvsp[(1) - (3)].node);
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 587:

/* Line 1806 of yacc.c  */
#line 4944 "parse.y"
    {
		    /*%%%*/
			if (!is_local_id((yyvsp[(2) - (2)].id)))
			    yyerror("rest argument must be local variable");
		    /*% %*/
			arg_var(shadowing_lvar(get_id((yyvsp[(2) - (2)].id))));
		    /*%%%*/
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    /*%
			$$ = dispatch1(rest_param, $2);
		    %*/
		    }
    break;

  case 588:

/* Line 1806 of yacc.c  */
#line 4957 "parse.y"
    {
		    /*%%%*/
			(yyval.id) = internal_id();
			arg_var((yyval.id));
		    /*%
			$$ = dispatch1(rest_param, Qnil);
		    %*/
		    }
    break;

  case 591:

/* Line 1806 of yacc.c  */
#line 4972 "parse.y"
    {
		    /*%%%*/
			if (!is_local_id((yyvsp[(2) - (2)].id)))
			    yyerror("block argument must be local variable");
			else if (!dyna_in_block() && local_id((yyvsp[(2) - (2)].id)))
			    yyerror("duplicated block argument name");
		    /*% %*/
			arg_var(shadowing_lvar(get_id((yyvsp[(2) - (2)].id))));
		    /*%%%*/
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    /*%
			$$ = dispatch1(blockarg, $2);
		    %*/
		    }
    break;

  case 592:

/* Line 1806 of yacc.c  */
#line 4989 "parse.y"
    {
			(yyval.id) = (yyvsp[(2) - (2)].id);
		    }
    break;

  case 593:

/* Line 1806 of yacc.c  */
#line 4993 "parse.y"
    {
		    /*%%%*/
			(yyval.id) = 0;
		    /*%
			$$ = Qundef;
		    %*/
		    }
    break;

  case 594:

/* Line 1806 of yacc.c  */
#line 5003 "parse.y"
    {
		    /*%%%*/
			value_expr((yyvsp[(1) - (1)].node));
			(yyval.node) = (yyvsp[(1) - (1)].node);
		        if (!(yyval.node)) (yyval.node) = NEW_NIL();
		    /*%
			$$ = $1;
		    %*/
		    }
    break;

  case 595:

/* Line 1806 of yacc.c  */
#line 5012 "parse.y"
    {SET_LEX_STATE(EXPR_BEG);}
    break;

  case 596:

/* Line 1806 of yacc.c  */
#line 5013 "parse.y"
    {
		    /*%%%*/
			if ((yyvsp[(3) - (4)].node) == 0) {
			    yyerror("can't define singleton method for ().");
			}
			else {
			    switch (nd_type((yyvsp[(3) - (4)].node))) {
			      case NODE_STR:
			      case NODE_DSTR:
			      case NODE_XSTR:
			      case NODE_DXSTR:
			      case NODE_DREGX:
			      case NODE_LIT:
			      case NODE_ARRAY:
			      case NODE_ZARRAY:
				yyerror("can't define singleton method for literals");
			      default:
				value_expr((yyvsp[(3) - (4)].node));
				break;
			    }
			}
			(yyval.node) = (yyvsp[(3) - (4)].node);
		    /*%
			$$ = dispatch1(paren, $3);
		    %*/
		    }
    break;

  case 598:

/* Line 1806 of yacc.c  */
#line 5043 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = (yyvsp[(1) - (2)].node);
		    /*%
			$$ = dispatch1(assoclist_from_args, $1);
		    %*/
		    }
    break;

  case 600:

/* Line 1806 of yacc.c  */
#line 5060 "parse.y"
    {
		    /*%%%*/
			NODE *assocs = (yyvsp[(1) - (3)].node);
			NODE *tail = (yyvsp[(3) - (3)].node);
			if (!assocs) {
			    assocs = tail;
			}
			else if (tail) {
			    if (assocs->nd_head &&
				!tail->nd_head && nd_type(tail->nd_next) == NODE_ARRAY &&
				nd_type(tail->nd_next->nd_head) == NODE_HASH) {
				/* DSTAR */
				tail = tail->nd_next->nd_head->nd_head;
			    }
			    assocs = list_concat(assocs, tail);
			}
			(yyval.node) = assocs;
		    /*%
			$$ = rb_ary_push($1, $3);
		    %*/
		    }
    break;

  case 601:

/* Line 1806 of yacc.c  */
#line 5084 "parse.y"
    {
		    /*%%%*/
			if (nd_type((yyvsp[(1) - (3)].node)) == NODE_STR) {
			    nd_set_type((yyvsp[(1) - (3)].node), NODE_LIT);
			    (yyvsp[(1) - (3)].node)->nd_lit = rb_fstring((yyvsp[(1) - (3)].node)->nd_lit);
			}
			(yyval.node) = list_append(NEW_LIST((yyvsp[(1) - (3)].node)), (yyvsp[(3) - (3)].node));
		    /*%
			$$ = dispatch2(assoc_new, $1, $3);
		    %*/
		    }
    break;

  case 602:

/* Line 1806 of yacc.c  */
#line 5096 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append(NEW_LIST(NEW_LIT(ID2SYM((yyvsp[(1) - (2)].id)))), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch2(assoc_new, $1, $2);
		    %*/
		    }
    break;

  case 603:

/* Line 1806 of yacc.c  */
#line 5104 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = list_append(NEW_LIST(dsym_node((yyvsp[(2) - (4)].node))), (yyvsp[(4) - (4)].node));
		    /*%
			$$ = dispatch2(assoc_new, dispatch1(dyna_symbol, $2), $4);
		    %*/
		    }
    break;

  case 604:

/* Line 1806 of yacc.c  */
#line 5112 "parse.y"
    {
		    /*%%%*/
			if (nd_type((yyvsp[(2) - (2)].node)) == NODE_HASH &&
			    !((yyvsp[(2) - (2)].node)->nd_head && (yyvsp[(2) - (2)].node)->nd_head->nd_alen))
			    (yyval.node) = 0;
			else
			    (yyval.node) = list_append(NEW_LIST(0), (yyvsp[(2) - (2)].node));
		    /*%
			$$ = dispatch1(assoc_splat, $2);
		    %*/
		    }
    break;

  case 617:

/* Line 1806 of yacc.c  */
#line 5154 "parse.y"
    {
		    /*%%%*/
			(yyval.id) = '.';
		    /*%
		        $$ = ripper_id2sym('.');
		    %*/
		    }
    break;

  case 618:

/* Line 1806 of yacc.c  */
#line 5162 "parse.y"
    {
		    /*%%%*/
			(yyval.id) = tANDDOT;
		    /*%
		        $$ = ripper_id2sym(idANDDOT);
		    %*/
		    }
    break;

  case 620:

/* Line 1806 of yacc.c  */
#line 5173 "parse.y"
    {
		    /*%%%*/
			(yyval.id) = tCOLON2;
		    /*%
		        $$ = ripper_id2sym(idCOLON2);
		    %*/
		    }
    break;

  case 630:

/* Line 1806 of yacc.c  */
#line 5201 "parse.y"
    {yyerrok;}
    break;

  case 633:

/* Line 1806 of yacc.c  */
#line 5206 "parse.y"
    {yyerrok;}
    break;

  case 634:

/* Line 1806 of yacc.c  */
#line 5210 "parse.y"
    {
		    /*%%%*/
			(yyval.node) = 0;
		    /*%
			$$ = Qundef;
		    %*/
		    }
    break;



/* Line 1806 of yacc.c  */
#line 11540 "parse.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      parser_yyerror (parser, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        parser_yyerror (parser, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
		      yytoken, &yylval, parser);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp, parser);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  parser_yyerror (parser, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, parser);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parser);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 5218 "parse.y"

# undef parser
# undef yylex
# undef yylval
# define yylval  (*parser->lval)

static int parser_regx_options(struct parser_params*);
static int parser_tokadd_string(struct parser_params*,int,int,int,long*,rb_encoding**);
static void parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc);
static int parser_parse_string(struct parser_params*,NODE*);
static int parser_here_document(struct parser_params*,NODE*);


# define nextc()                      parser_nextc(parser)
# define pushback(c)                  parser_pushback(parser, (c))
# define newtok()                     parser_newtok(parser)
# define tokspace(n)                  parser_tokspace(parser, (n))
# define tokadd(c)                    parser_tokadd(parser, (c))
# define tok_hex(numlen)              parser_tok_hex(parser, (numlen))
# define read_escape(flags,e)         parser_read_escape(parser, (flags), (e))
# define tokadd_escape(e)             parser_tokadd_escape(parser, (e))
# define regx_options()               parser_regx_options(parser)
# define tokadd_string(f,t,p,n,e)     parser_tokadd_string(parser,(f),(t),(p),(n),(e))
# define parse_string(n)              parser_parse_string(parser,(n))
# define tokaddmbc(c, enc)            parser_tokaddmbc(parser, (c), (enc))
# define here_document(n)             parser_here_document(parser,(n))
# define heredoc_identifier()         parser_heredoc_identifier(parser)
# define heredoc_restore(n)           parser_heredoc_restore(parser,(n))
# define whole_match_p(e,l,i)         parser_whole_match_p(parser,(e),(l),(i))
# define number_literal_suffix(f)     parser_number_literal_suffix(parser, (f))
# define set_number_literal(v, t, f)  parser_set_number_literal(parser, (v), (t), (f))
# define set_integer_literal(v, f)    parser_set_integer_literal(parser, (v), (f))

#ifndef RIPPER
# define set_yylval_str(x) (yylval.node = NEW_STR(x))
# define set_yylval_num(x) (yylval.num = (x))
# define set_yylval_id(x)  (yylval.id = (x))
# define set_yylval_name(x)  (yylval.id = (x))
# define set_yylval_literal(x) (yylval.node = NEW_LIT(x))
# define set_yylval_node(x) (yylval.node = (x))
# define yylval_id() (yylval.id)
#else
static inline VALUE
ripper_yylval_id(ID x)
{
    return ripper_new_yylval(x, ID2SYM(x), 0);
}
# define set_yylval_str(x) (yylval.val = (x))
# define set_yylval_num(x) (yylval.val = ripper_new_yylval((x), 0, 0))
# define set_yylval_id(x)  (void)(x)
# define set_yylval_name(x) (void)(yylval.val = ripper_yylval_id(x))
# define set_yylval_literal(x) (void)(x)
# define set_yylval_node(x) (void)(x)
# define yylval_id() yylval.id
#endif

#ifndef RIPPER
#define ripper_flush(p) (void)(p)
#define dispatch_scan_event(t) ((void)0)
#define dispatch_delayed_token(t) ((void)0)
#define has_delayed_token() (0)
#else
#define ripper_flush(p) ((p)->tokp = (p)->lex.pcur)

#define yylval_rval (*(RB_TYPE_P(yylval.val, T_NODE) ? &yylval.node->nd_rval : &yylval.val))

static inline VALUE
intern_sym(const char *name)
{
    ID id = rb_intern_const(name);
    return ID2SYM(id);
}

static int
ripper_has_scan_event(struct parser_params *parser)
{

    if (lex_p < parser->tokp) rb_raise(rb_eRuntimeError, "lex_p < tokp");
    return lex_p > parser->tokp;
}

static VALUE
ripper_scan_event_val(struct parser_params *parser, int t)
{
    VALUE str = STR_NEW(parser->tokp, lex_p - parser->tokp);
    VALUE rval = ripper_dispatch1(parser, ripper_token2eventid(t), str);
    ripper_flush(parser);
    return rval;
}

static void
ripper_dispatch_scan_event(struct parser_params *parser, int t)
{
    if (!ripper_has_scan_event(parser)) return;
    yylval_rval = ripper_scan_event_val(parser, t);
}
#define dispatch_scan_event(t) ripper_dispatch_scan_event(parser, t)

static void
ripper_dispatch_delayed_token(struct parser_params *parser, int t)
{
    int saved_line = ruby_sourceline;
    const char *saved_tokp = parser->tokp;

    ruby_sourceline = parser->delayed_line;
    parser->tokp = lex_pbeg + parser->delayed_col;
    yylval_rval = ripper_dispatch1(parser, ripper_token2eventid(t), parser->delayed);
    parser->delayed = Qnil;
    ruby_sourceline = saved_line;
    parser->tokp = saved_tokp;
}
#define dispatch_delayed_token(t) ripper_dispatch_delayed_token(parser, t)
#define has_delayed_token() (!NIL_P(parser->delayed))
#endif /* RIPPER */

#include "ruby/regex.h"
#include "ruby/util.h"

/* We remove any previous definition of `SIGN_EXTEND_CHAR',
   since ours (we hope) works properly with all combinations of
   machines, compilers, `char' and `unsigned char' argument types.
   (Per Bothner suggested the basic approach.)  */
#undef SIGN_EXTEND_CHAR
#if __STDC__
# define SIGN_EXTEND_CHAR(c) ((signed char)(c))
#else  /* not __STDC__ */
/* As in Harbison and Steele.  */
# define SIGN_EXTEND_CHAR(c) ((((unsigned char)(c)) ^ 128) - 128)
#endif

#define parser_encoding_name()  (current_enc->name)
#define parser_mbclen()  mbclen((lex_p-1),lex_pend,current_enc)
#define is_identchar(p,e,enc) (rb_enc_isalnum((unsigned char)(*(p)),(enc)) || (*(p)) == '_' || !ISASCII(*(p)))
#define parser_is_identchar() (!parser->eofp && is_identchar((lex_p-1),lex_pend,current_enc))

#define parser_isascii() ISASCII(*(lex_p-1))

static int
token_info_get_column(struct parser_params *parser, const char *pend)
{
    int column = 1;
    const char *p;
    for (p = lex_pbeg; p < pend; p++) {
	if (*p == '\t') {
	    column = (((column - 1) / TAB_WIDTH) + 1) * TAB_WIDTH;
	}
	column++;
    }
    return column;
}

static int
token_info_has_nonspaces(struct parser_params *parser, const char *pend)
{
    const char *p;
    for (p = lex_pbeg; p < pend; p++) {
	if (*p != ' ' && *p != '\t') {
	    return 1;
	}
    }
    return 0;
}

#undef token_info_push
static void
token_info_push(struct parser_params *parser, const char *token, size_t len)
{
    token_info *ptinfo;
    const char *t = lex_p - len;

    if (!parser->token_info_enabled) return;
    ptinfo = ALLOC(token_info);
    ptinfo->token = token;
    ptinfo->linenum = ruby_sourceline;
    ptinfo->column = token_info_get_column(parser, t);
    ptinfo->nonspc = token_info_has_nonspaces(parser, t);
    ptinfo->next = parser->token_info;

    parser->token_info = ptinfo;
}

#undef token_info_pop
static void
token_info_pop(struct parser_params *parser, const char *token, size_t len)
{
    int linenum;
    token_info *ptinfo = parser->token_info;
    const char *t = lex_p - len;

    if (!ptinfo) return;
    parser->token_info = ptinfo->next;
    linenum = ruby_sourceline;
    if (parser->token_info_enabled &&
	linenum != ptinfo->linenum && !ptinfo->nonspc &&
	!token_info_has_nonspaces(parser, t) &&
	token_info_get_column(parser, t) != ptinfo->column) {
	rb_warn3L(linenum,
		  "mismatched indentations at '%s' with '%s' at %d",
		  WARN_S(token), WARN_S(ptinfo->token), WARN_I(ptinfo->linenum));
    }

    xfree(ptinfo);
}

static int
parser_precise_mbclen(struct parser_params *parser, const char *p)
{
    int len = rb_enc_precise_mbclen(p, lex_pend, current_enc);
    if (!MBCLEN_CHARFOUND_P(len)) {
	compile_error(PARSER_ARG "invalid multibyte char (%s)", parser_encoding_name());
	return -1;
    }

    return len;
}

static int
parser_yyerror(struct parser_params *parser, const char *msg)
{
#ifndef RIPPER
    const int max_line_margin = 30;
    const char *p, *pe;
    const char *pre = "", *post = "";
    const char *code = "", *caret = "", *newline = "";
    char *buf;
    long len;
    int i;

    p = lex_p;
    while (lex_pbeg <= p) {
	if (*p == '\n') break;
	p--;
    }
    p++;

    pe = lex_p;
    while (pe < lex_pend) {
	if (*pe == '\n') break;
	pe++;
    }

    len = pe - p;
    if (len > 4) {
	char *p2;

	if (len > max_line_margin * 2 + 10) {
	    if (lex_p - p > max_line_margin) {
		p = rb_enc_prev_char(p, lex_p - max_line_margin, pe, rb_enc_get(lex_lastline));
		pre = "...";
	    }
	    if (pe - lex_p > max_line_margin) {
		pe = rb_enc_prev_char(lex_p, lex_p + max_line_margin, pe, rb_enc_get(lex_lastline));
		post = "...";
	    }
	    len = pe - p;
	}
	i = (int)(lex_p - p);
	buf = ALLOCA_N(char, i+2);
	code = p;
	caret = p2 = buf;
	while (i-- > 0) {
	    *p2++ = *p++ == '\t' ? '\t' : ' ';
	}
	*p2++ = '^';
	*p2 = '\0';
	newline = "\n";
    }
    else {
	len = 0;
    }
    compile_error(PARSER_ARG "%s%s""%s%.*s%s%s""%s%s",
		  msg, newline,
		  pre, (int)len, code, post, newline,
		  pre, caret);
#else
    dispatch1(parse_error, STR_NEW2(msg));
    ripper_error();
#endif /* !RIPPER */
    return 0;
}

static void parser_prepare(struct parser_params *parser);

#ifndef RIPPER
static VALUE
debug_lines(VALUE fname)
{
    ID script_lines;
    CONST_ID(script_lines, "SCRIPT_LINES__");
    if (rb_const_defined_at(rb_cObject, script_lines)) {
	VALUE hash = rb_const_get_at(rb_cObject, script_lines);
	if (RB_TYPE_P(hash, T_HASH)) {
	    VALUE lines = rb_ary_new();
	    rb_hash_aset(hash, fname, lines);
	    return lines;
	}
    }
    return 0;
}

static VALUE
coverage(VALUE fname, int n)
{
    VALUE coverages = rb_get_coverages();
    if (RTEST(coverages) && RBASIC(coverages)->klass == 0) {
	VALUE lines = n > 0 ? rb_ary_tmp_new_fill(n) : rb_ary_tmp_new(0);
	rb_hash_aset(coverages, fname, lines);
	return lines;
    }
    return 0;
}

static int
e_option_supplied(struct parser_params *parser)
{
    return strcmp(ruby_sourcefile, "-e") == 0;
}

static VALUE
yycompile0(VALUE arg)
{
    int n;
    NODE *tree;
    struct parser_params *parser = (struct parser_params *)arg;

    if (!compile_for_eval && rb_safe_level() == 0) {
	ruby_debug_lines = debug_lines(ruby_sourcefile_string);
	if (ruby_debug_lines && ruby_sourceline > 0) {
	    VALUE str = STR_NEW0();
	    n = ruby_sourceline;
	    do {
		rb_ary_push(ruby_debug_lines, str);
	    } while (--n);
	}

	if (!e_option_supplied(parser)) {
	    ruby_coverage = coverage(ruby_sourcefile_string, ruby_sourceline);
	}
    }
    parser->last_cr_line = ruby_sourceline - 1;

    parser_prepare(parser);
#ifndef RIPPER
#define RUBY_DTRACE_PARSE_HOOK(name) \
    if (RUBY_DTRACE_PARSE_##name##_ENABLED()) { \
	RUBY_DTRACE_PARSE_##name(ruby_sourcefile, ruby_sourceline); \
    }
    RUBY_DTRACE_PARSE_HOOK(BEGIN);
#endif
    n = yyparse((void*)parser);
#ifndef RIPPER
    RUBY_DTRACE_PARSE_HOOK(END);
#endif
    ruby_debug_lines = 0;
    ruby_coverage = 0;
    compile_for_eval = 0;

    lex_strterm = 0;
    lex_p = lex_pbeg = lex_pend = 0;
    lex_lastline = lex_nextline = 0;
    if (parser->error_p) {
	return 0;
    }
    tree = ruby_eval_tree;
    if (!tree) {
	tree = NEW_NIL();
    }
    else {
	tree->nd_body = NEW_PRELUDE(ruby_eval_tree_begin, tree->nd_body, parser->compile_option);
    }
    return (VALUE)tree;
}

static NODE*
yycompile(struct parser_params *parser, VALUE fname, int line)
{
    ruby_sourcefile_string = rb_str_new_frozen(fname);
    ruby_sourcefile = RSTRING_PTR(fname);
    ruby_sourceline = line - 1;
    return (NODE *)rb_suppress_tracing(yycompile0, (VALUE)parser);
}
#endif /* !RIPPER */

static rb_encoding *
must_be_ascii_compatible(VALUE s)
{
    rb_encoding *enc = rb_enc_get(s);
    if (!rb_enc_asciicompat(enc)) {
	rb_raise(rb_eArgError, "invalid source encoding");
    }
    return enc;
}

static VALUE
lex_get_str(struct parser_params *parser, VALUE s)
{
    char *beg, *end, *start;
    long len;

    beg = RSTRING_PTR(s);
    len = RSTRING_LEN(s);
    start = beg;
    if (lex_gets_ptr) {
	if (len == lex_gets_ptr) return Qnil;
	beg += lex_gets_ptr;
	len -= lex_gets_ptr;
    }
    end = memchr(beg, '\n', len);
    if (end) len = ++end - beg;
    lex_gets_ptr += len;
    return rb_str_subseq(s, beg - start, len);
}

static VALUE
lex_getline(struct parser_params *parser)
{
    VALUE line = (*lex_gets)(parser, lex_input);
    if (NIL_P(line)) return line;
    must_be_ascii_compatible(line);
#ifndef RIPPER
    if (ruby_debug_lines) {
	rb_enc_associate(line, current_enc);
	rb_ary_push(ruby_debug_lines, line);
    }
    if (ruby_coverage) {
	rb_ary_push(ruby_coverage, Qnil);
    }
#endif
    return line;
}

static const rb_data_type_t parser_data_type;

#ifndef RIPPER
static NODE*
parser_compile_string(VALUE vparser, VALUE fname, VALUE s, int line)
{
    struct parser_params *parser;
    NODE *node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    lex_gets = lex_get_str;
    lex_gets_ptr = 0;
    lex_input = rb_str_new_frozen(s);
    lex_pbeg = lex_p = lex_pend = 0;
    compile_for_eval = !!rb_parse_in_eval();

    node = yycompile(parser, fname, line);
    RB_GC_GUARD(vparser); /* prohibit tail call optimization */

    return node;
}

NODE*
rb_compile_string(const char *f, VALUE s, int line)
{
    must_be_ascii_compatible(s);
    return parser_compile_string(rb_parser_new(), rb_filesystem_str_new_cstr(f), s, line);
}

NODE*
rb_parser_compile_string(VALUE vparser, const char *f, VALUE s, int line)
{
    return rb_parser_compile_string_path(vparser, rb_filesystem_str_new_cstr(f), s, line);
}

NODE*
rb_parser_compile_string_path(VALUE vparser, VALUE f, VALUE s, int line)
{
    must_be_ascii_compatible(s);
    return parser_compile_string(vparser, f, s, line);
}

NODE*
rb_compile_cstr(const char *f, const char *s, int len, int line)
{
    VALUE str = rb_str_new(s, len);
    return parser_compile_string(rb_parser_new(), rb_filesystem_str_new_cstr(f), str, line);
}

NODE*
rb_parser_compile_cstr(VALUE vparser, const char *f, const char *s, int len, int line)
{
    VALUE str = rb_str_new(s, len);
    return parser_compile_string(vparser, rb_filesystem_str_new_cstr(f), str, line);
}

static VALUE
lex_io_gets(struct parser_params *parser, VALUE io)
{
    return rb_io_gets(io);
}

NODE*
rb_compile_file(const char *f, VALUE file, int start)
{
    VALUE vparser = rb_parser_new();

    return rb_parser_compile_file(vparser, f, file, start);
}

NODE*
rb_parser_compile_file(VALUE vparser, const char *f, VALUE file, int start)
{
    return rb_parser_compile_file_path(vparser, rb_filesystem_str_new_cstr(f), file, start);
}

NODE*
rb_parser_compile_file_path(VALUE vparser, VALUE fname, VALUE file, int start)
{
    struct parser_params *parser;
    NODE *node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    lex_gets = lex_io_gets;
    lex_input = file;
    lex_pbeg = lex_p = lex_pend = 0;
    compile_for_eval = !!rb_parse_in_eval();

    node = yycompile(parser, fname, start);
    RB_GC_GUARD(vparser); /* prohibit tail call optimization */

    return node;
}
#endif  /* !RIPPER */

#define STR_FUNC_ESCAPE 0x01
#define STR_FUNC_EXPAND 0x02
#define STR_FUNC_REGEXP 0x04
#define STR_FUNC_QWORDS 0x08
#define STR_FUNC_SYMBOL 0x10
#define STR_FUNC_INDENT 0x20
#define STR_FUNC_LABEL  0x40

enum string_type {
    str_label  = STR_FUNC_LABEL,
    str_squote = (0),
    str_dquote = (STR_FUNC_EXPAND),
    str_xquote = (STR_FUNC_EXPAND),
    str_regexp = (STR_FUNC_REGEXP|STR_FUNC_ESCAPE|STR_FUNC_EXPAND),
    str_sword  = (STR_FUNC_QWORDS),
    str_dword  = (STR_FUNC_QWORDS|STR_FUNC_EXPAND),
    str_ssym   = (STR_FUNC_SYMBOL),
    str_dsym   = (STR_FUNC_SYMBOL|STR_FUNC_EXPAND)
};

static VALUE
parser_str_new(const char *p, long n, rb_encoding *enc, int func, rb_encoding *enc0)
{
    VALUE str;

    str = rb_enc_str_new(p, n, enc);
    if (!(func & STR_FUNC_REGEXP) && rb_enc_asciicompat(enc)) {
	if (rb_enc_str_coderange(str) == ENC_CODERANGE_7BIT) {
	}
	else if (enc0 == rb_usascii_encoding() && enc != rb_utf8_encoding()) {
	    rb_enc_associate(str, rb_ascii8bit_encoding());
	}
    }

    return str;
}

#define lex_goto_eol(parser) ((parser)->lex.pcur = (parser)->lex.pend)
#define lex_eol_p() (lex_p >= lex_pend)
#define peek(c) peek_n((c), 0)
#define peek_n(c,n) (lex_p+(n) < lex_pend && (c) == (unsigned char)lex_p[n])
#define peekc() peekc_n(0)
#define peekc_n(n) (lex_p+(n) < lex_pend ? (unsigned char)lex_p[n] : -1)

static inline int
parser_nextc(struct parser_params *parser)
{
    int c;

    if (lex_p == lex_pend) {
	VALUE v = lex_nextline;
	lex_nextline = 0;
	if (!v) {
	    if (parser->eofp)
		return -1;

	    if (!lex_input || NIL_P(v = lex_getline(parser))) {
		parser->eofp = 1;
		lex_goto_eol(parser);
		return -1;
	    }
	}
	{
#ifdef RIPPER
	    if (parser->tokp < lex_pend) {
		if (!has_delayed_token()) {
		    parser->delayed = rb_str_buf_new(1024);
		    rb_enc_associate(parser->delayed, current_enc);
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		    parser->delayed_line = ruby_sourceline;
		    parser->delayed_col = (int)(parser->tokp - lex_pbeg);
		}
		else {
		    rb_str_buf_cat(parser->delayed,
				   parser->tokp, lex_pend - parser->tokp);
		}
	    }
#endif
	    if (heredoc_end > 0) {
		ruby_sourceline = heredoc_end;
		heredoc_end = 0;
	    }
	    ruby_sourceline++;
	    parser->line_count++;
	    lex_pbeg = lex_p = RSTRING_PTR(v);
	    lex_pend = lex_p + RSTRING_LEN(v);
	    ripper_flush(parser);
	    lex_lastline = v;
	}
    }
    c = (unsigned char)*lex_p++;
    if (c == '\r') {
	if (peek('\n')) {
	    lex_p++;
	    c = '\n';
	}
	else if (ruby_sourceline > parser->last_cr_line) {
	    parser->last_cr_line = ruby_sourceline;
	    rb_warn0("encountered \\r in middle of line, treated as a mere space");
	}
    }

    return c;
}

static void
parser_pushback(struct parser_params *parser, int c)
{
    if (c == -1) return;
    lex_p--;
    if (lex_p > lex_pbeg && lex_p[0] == '\n' && lex_p[-1] == '\r') {
	lex_p--;
    }
}

#define was_bol() (lex_p == lex_pbeg + 1)

#define tokfix() (tokenbuf[tokidx]='\0')
#define tok() tokenbuf
#define toklen() tokidx
#define toklast() (tokidx>0?tokenbuf[tokidx-1]:0)

static char*
parser_newtok(struct parser_params *parser)
{
    tokidx = 0;
    tokline = ruby_sourceline;
    if (!tokenbuf) {
	toksiz = 60;
	tokenbuf = ALLOC_N(char, 60);
    }
    if (toksiz > 4096) {
	toksiz = 60;
	REALLOC_N(tokenbuf, char, 60);
    }
    return tokenbuf;
}

static char *
parser_tokspace(struct parser_params *parser, int n)
{
    tokidx += n;

    if (tokidx >= toksiz) {
	do {toksiz *= 2;} while (toksiz < tokidx);
	REALLOC_N(tokenbuf, char, toksiz);
    }
    return &tokenbuf[tokidx-n];
}

static void
parser_tokadd(struct parser_params *parser, int c)
{
    tokenbuf[tokidx++] = (char)c;
    if (tokidx >= toksiz) {
	toksiz *= 2;
	REALLOC_N(tokenbuf, char, toksiz);
    }
}

static int
parser_tok_hex(struct parser_params *parser, size_t *numlen)
{
    int c;

    c = scan_hex(lex_p, 2, numlen);
    if (!*numlen) {
	yyerror("invalid hex escape");
	return 0;
    }
    lex_p += *numlen;
    return c;
}

#define tokcopy(n) memcpy(tokspace(n), lex_p - (n), (n))

/* return value is for ?\u3042 */
static int
parser_tokadd_utf8(struct parser_params *parser, rb_encoding **encp,
                   int string_literal, int symbol_literal, int regexp_literal)
{
    /*
     * If string_literal is true, then we allow multiple codepoints
     * in \u{}, and add the codepoints to the current token.
     * Otherwise we're parsing a character literal and return a single
     * codepoint without adding it
     */

    int codepoint;
    size_t numlen;

    if (regexp_literal) { tokadd('\\'); tokadd('u'); }

    if (peek('{')) {  /* handle \u{...} form */
	do {
            if (regexp_literal) { tokadd(*lex_p); }
	    nextc();
	    codepoint = scan_hex(lex_p, 6, &numlen);
	    if (numlen == 0)  {
		yyerror("invalid Unicode escape");
		return 0;
	    }
	    if (codepoint > 0x10ffff) {
		yyerror("invalid Unicode codepoint (too large)");
		return 0;
	    }
	    lex_p += numlen;
            if (regexp_literal) {
                tokcopy((int)numlen);
            }
            else if (codepoint >= 0x80) {
		*encp = rb_utf8_encoding();
		if (string_literal) tokaddmbc(codepoint, *encp);
	    }
	    else if (string_literal) {
		tokadd(codepoint);
	    }
	} while (string_literal && (peek(' ') || peek('\t')));

	if (!peek('}')) {
	    yyerror("unterminated Unicode escape");
	    return 0;
	}

        if (regexp_literal) { tokadd('}'); }
	nextc();
    }
    else {			/* handle \uxxxx form */
	codepoint = scan_hex(lex_p, 4, &numlen);
	if (numlen < 4) {
	    yyerror("invalid Unicode escape");
	    return 0;
	}
	lex_p += 4;
        if (regexp_literal) {
            tokcopy(4);
        }
	else if (codepoint >= 0x80) {
	    *encp = rb_utf8_encoding();
	    if (string_literal) tokaddmbc(codepoint, *encp);
	}
	else if (string_literal) {
	    tokadd(codepoint);
	}
    }

    return codepoint;
}

#define ESCAPE_CONTROL 1
#define ESCAPE_META    2

static int
parser_read_escape(struct parser_params *parser, int flags,
		   rb_encoding **encp)
{
    int c;
    size_t numlen;

    switch (c = nextc()) {
      case '\\':	/* Backslash */
	return c;

      case 'n':	/* newline */
	return '\n';

      case 't':	/* horizontal tab */
	return '\t';

      case 'r':	/* carriage-return */
	return '\r';

      case 'f':	/* form-feed */
	return '\f';

      case 'v':	/* vertical tab */
	return '\13';

      case 'a':	/* alarm(bell) */
	return '\007';

      case 'e':	/* escape */
	return 033;

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	pushback(c);
	c = scan_oct(lex_p, 3, &numlen);
	lex_p += numlen;
	return c;

      case 'x':	/* hex constant */
	c = tok_hex(&numlen);
	if (numlen == 0) return 0;
	return c;

      case 'b':	/* backspace */
	return '\010';

      case 's':	/* space */
	return ' ';

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	if ((c = nextc()) == '\\') {
	    if (peek('u')) goto eof;
	    return read_escape(flags|ESCAPE_META, encp) | 0x80;
	}
	else if (c == -1 || !ISASCII(c)) goto eof;
	else {
	    return ((c & 0xff) | 0x80);
	}

      case 'C':
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc())== '\\') {
	    if (peek('u')) goto eof;
	    c = read_escape(flags|ESCAPE_CONTROL, encp);
	}
	else if (c == '?')
	    return 0177;
	else if (c == -1 || !ISASCII(c)) goto eof;
	return c & 0x9f;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return '\0';

      default:
	return c;
    }
}

static void
parser_tokaddmbc(struct parser_params *parser, int c, rb_encoding *enc)
{
    int len = rb_enc_codelen(c, enc);
    rb_enc_mbcput(c, tokspace(len), enc);
}

static int
parser_tokadd_escape(struct parser_params *parser, rb_encoding **encp)
{
    int c;
    int flags = 0;
    size_t numlen;

  first:
    switch (c = nextc()) {
      case '\n':
	return 0;		/* just ignore */

      case '0': case '1': case '2': case '3': /* octal constant */
      case '4': case '5': case '6': case '7':
	{
	    ruby_scan_oct(--lex_p, 3, &numlen);
	    if (numlen == 0) goto eof;
	    lex_p += numlen;
	    tokcopy((int)numlen + 1);
	}
	return 0;

      case 'x':	/* hex constant */
	{
	    tok_hex(&numlen);
	    if (numlen == 0) return -1;
	    tokcopy((int)numlen + 2);
	}
	return 0;

      case 'M':
	if (flags & ESCAPE_META) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	flags |= ESCAPE_META;
	goto escaped;

      case 'C':
	if (flags & ESCAPE_CONTROL) goto eof;
	if ((c = nextc()) != '-') {
	    pushback(c);
	    goto eof;
	}
	tokcopy(3);
	goto escaped;

      case 'c':
	if (flags & ESCAPE_CONTROL) goto eof;
	tokcopy(2);
	flags |= ESCAPE_CONTROL;
      escaped:
	if ((c = nextc()) == '\\') {
	    goto first;
	}
	else if (c == -1) goto eof;
	tokadd(c);
	return 0;

      eof:
      case -1:
        yyerror("Invalid escape character syntax");
	return -1;

      default:
        tokadd('\\');
	tokadd(c);
    }
    return 0;
}

static int
parser_regx_options(struct parser_params *parser)
{
    int kcode = 0;
    int kopt = 0;
    int options = 0;
    int c, opt, kc;

    newtok();
    while (c = nextc(), ISALPHA(c)) {
        if (c == 'o') {
            options |= RE_OPTION_ONCE;
        }
        else if (rb_char_to_option_kcode(c, &opt, &kc)) {
	    if (kc >= 0) {
		if (kc != rb_ascii8bit_encindex()) kcode = c;
		kopt = opt;
	    }
	    else {
		options |= opt;
	    }
        }
        else {
	    tokadd(c);
        }
    }
    options |= kopt;
    pushback(c);
    if (toklen()) {
	tokfix();
	compile_error(PARSER_ARG "unknown regexp option%s - %s",
		      toklen() > 1 ? "s" : "", tok());
    }
    return options | RE_OPTION_ENCODING(kcode);
}

static void
dispose_string(VALUE str)
{
    rb_str_free(str);
    rb_gc_force_recycle(str);
}

static int
parser_tokadd_mbchar(struct parser_params *parser, int c)
{
    int len = parser_precise_mbclen(parser, lex_p-1);
    if (len < 0) return -1;
    tokadd(c);
    lex_p += --len;
    if (len > 0) tokcopy(len);
    return c;
}

#define tokadd_mbchar(c) parser_tokadd_mbchar(parser, (c))

static inline int
simple_re_meta(int c)
{
    switch (c) {
      case '$': case '*': case '+': case '.':
      case '?': case '^': case '|':
      case ')': case ']': case '}': case '>':
	return TRUE;
      default:
	return FALSE;
    }
}

static int
parser_update_heredoc_indent(struct parser_params *parser, int c)
{
    if (heredoc_line_indent == -1) {
	if (c == '\n') heredoc_line_indent = 0;
    }
    else {
	if (c == ' ') {
	    heredoc_line_indent++;
	    return TRUE;
	}
	else if (c == '\t') {
	    int w = (heredoc_line_indent / TAB_WIDTH) + 1;
	    heredoc_line_indent = w * TAB_WIDTH;
	    return TRUE;
	}
	else if (c != '\n') {
	    if (heredoc_indent > heredoc_line_indent) {
		heredoc_indent = heredoc_line_indent;
	    }
	    heredoc_line_indent = -1;
	}
    }
    return FALSE;
}

static int
parser_tokadd_string(struct parser_params *parser,
		     int func, int term, int paren, long *nest,
		     rb_encoding **encp)
{
    int c;
    int has_nonascii = 0;
    rb_encoding *enc = *encp;
    char *errbuf = 0;
    static const char mixed_msg[] = "%s mixed within %s source";

#define mixed_error(enc1, enc2) if (!errbuf) {	\
	size_t len = sizeof(mixed_msg) - 4;	\
	len += strlen(rb_enc_name(enc1));	\
	len += strlen(rb_enc_name(enc2));	\
	errbuf = ALLOCA_N(char, len);		\
	snprintf(errbuf, len, mixed_msg,	\
		 rb_enc_name(enc1),		\
		 rb_enc_name(enc2));		\
	yyerror(errbuf);			\
    }
#define mixed_escape(beg, enc1, enc2) do {	\
	const char *pos = lex_p;		\
	lex_p = (beg);				\
	mixed_error((enc1), (enc2));		\
	lex_p = pos;				\
    } while (0)

    while ((c = nextc()) != -1) {
	if (heredoc_indent > 0) {
	    parser_update_heredoc_indent(parser, c);
	}

	if (paren && c == paren) {
	    ++*nest;
	}
	else if (c == term) {
	    if (!nest || !*nest) {
		pushback(c);
		break;
	    }
	    --*nest;
	}
	else if ((func & STR_FUNC_EXPAND) && c == '#' && lex_p < lex_pend) {
	    int c2 = *lex_p;
	    if (c2 == '$' || c2 == '@' || c2 == '{') {
		pushback(c);
		break;
	    }
	}
	else if (c == '\\') {
	    const char *beg = lex_p - 1;
	    c = nextc();
	    switch (c) {
	      case '\n':
		if (func & STR_FUNC_QWORDS) break;
		if (func & STR_FUNC_EXPAND) continue;
		tokadd('\\');
		break;

	      case '\\':
		if (func & STR_FUNC_ESCAPE) tokadd(c);
		break;

	      case 'u':
		if ((func & STR_FUNC_EXPAND) == 0) {
		    tokadd('\\');
		    break;
		}
		parser_tokadd_utf8(parser, &enc, 1,
				   func & STR_FUNC_SYMBOL,
                                   func & STR_FUNC_REGEXP);
		if (has_nonascii && enc != *encp) {
		    mixed_escape(beg, enc, *encp);
		}
		continue;

	      default:
		if (c == -1) return -1;
		if (!ISASCII(c)) {
		    if ((func & STR_FUNC_EXPAND) == 0) tokadd('\\');
		    goto non_ascii;
		}
		if (func & STR_FUNC_REGEXP) {
		    if (c == term && !simple_re_meta(c)) {
			tokadd(c);
			continue;
		    }
		    pushback(c);
		    if ((c = tokadd_escape(&enc)) < 0)
			return -1;
		    if (has_nonascii && enc != *encp) {
			mixed_escape(beg, enc, *encp);
		    }
		    continue;
		}
		else if (func & STR_FUNC_EXPAND) {
		    pushback(c);
		    if (func & STR_FUNC_ESCAPE) tokadd('\\');
		    c = read_escape(0, &enc);
		}
		else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
		    /* ignore backslashed spaces in %w */
		}
		else if (c != term && !(paren && c == paren)) {
		    tokadd('\\');
		    pushback(c);
		    continue;
		}
	    }
	}
	else if (!parser_isascii()) {
	  non_ascii:
	    has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
	    if (tokadd_mbchar(c) == -1) return -1;
	    continue;
	}
	else if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	    pushback(c);
	    break;
	}
        if (c & 0x80) {
	    has_nonascii = 1;
	    if (enc != *encp) {
		mixed_error(enc, *encp);
		continue;
	    }
        }
	tokadd(c);
    }
    *encp = enc;
    return c;
}

#define NEW_STRTERM(func, term, paren) \
	rb_node_newnode(NODE_STRTERM, (func), (term) | ((paren) << (CHAR_BIT * 2)), 0)

#ifdef RIPPER
static void
ripper_flush_string_content(struct parser_params *parser, rb_encoding *enc)
{
    VALUE content = yylval.val;
    if (!ripper_is_node_yylval(content))
	content = ripper_new_yylval(0, 0, content);
    if (has_delayed_token()) {
	ptrdiff_t len = lex_p - parser->tokp;
	if (len > 0) {
	    rb_enc_str_buf_cat(parser->delayed, parser->tokp, len, enc);
	}
	dispatch_delayed_token(tSTRING_CONTENT);
	parser->tokp = lex_p;
	RNODE(content)->nd_rval = yylval.val;
    }
    dispatch_scan_event(tSTRING_CONTENT);
    if (yylval.val != content)
	RNODE(content)->nd_rval = yylval.val;
    yylval.val = content;
}

#define flush_string_content(enc) ripper_flush_string_content(parser, (enc))
#else
#define flush_string_content(enc) ((void)(enc))
#endif

RUBY_FUNC_EXPORTED const unsigned int ruby_global_name_punct_bits[(0x7e - 0x20 + 31) / 32];
/* this can be shared with ripper, since it's independent from struct
 * parser_params. */
#ifndef RIPPER
#define BIT(c, idx) (((c) / 32 - 1 == idx) ? (1U << ((c) % 32)) : 0)
#define SPECIAL_PUNCT(idx) ( \
	BIT('~', idx) | BIT('*', idx) | BIT('$', idx) | BIT('?', idx) | \
	BIT('!', idx) | BIT('@', idx) | BIT('/', idx) | BIT('\\', idx) | \
	BIT(';', idx) | BIT(',', idx) | BIT('.', idx) | BIT('=', idx) | \
	BIT(':', idx) | BIT('<', idx) | BIT('>', idx) | BIT('\"', idx) | \
	BIT('&', idx) | BIT('`', idx) | BIT('\'', idx) | BIT('+', idx) | \
	BIT('0', idx))
const unsigned int ruby_global_name_punct_bits[] = {
    SPECIAL_PUNCT(0),
    SPECIAL_PUNCT(1),
    SPECIAL_PUNCT(2),
};
#undef BIT
#undef SPECIAL_PUNCT
#endif

static int
parser_peek_variable_name(struct parser_params *parser)
{
    int c;
    const char *p = lex_p;

    if (p + 1 >= lex_pend) return 0;
    c = *p++;
    switch (c) {
      case '$':
	if ((c = *p) == '-') {
	    if (++p >= lex_pend) return 0;
	    c = *p;
	}
	else if (is_global_name_punct(c) || ISDIGIT(c)) {
	    return tSTRING_DVAR;
	}
	break;
      case '@':
	if ((c = *p) == '@') {
	    if (++p >= lex_pend) return 0;
	    c = *p;
	}
	break;
      case '{':
	lex_p = p;
	command_start = TRUE;
	return tSTRING_DBEG;
      default:
	return 0;
    }
    if (!ISASCII(c) || c == '_' || ISALPHA(c))
	return tSTRING_DVAR;
    return 0;
}

static int
parser_parse_string(struct parser_params *parser, NODE *quote)
{
    int func = (int)quote->nd_func;
    int term = nd_term(quote);
    int paren = nd_paren(quote);
    int c, space = 0;
    rb_encoding *enc = current_enc;

    if (func == -1) return tSTRING_END;
    c = nextc();
    if ((func & STR_FUNC_QWORDS) && ISSPACE(c)) {
	do {c = nextc();} while (ISSPACE(c));
	space = 1;
    }
    if (c == term && !quote->nd_nest) {
	if (func & STR_FUNC_QWORDS) {
	    quote->nd_func = -1;
	    return ' ';
	}
	if (!(func & STR_FUNC_REGEXP)) return tSTRING_END;
        set_yylval_num(regx_options());
	dispatch_scan_event(tREGEXP_END);
	return tREGEXP_END;
    }
    if (space) {
	pushback(c);
	return ' ';
    }
    newtok();
    if ((func & STR_FUNC_EXPAND) && c == '#') {
	int t = parser_peek_variable_name(parser);
	if (t) return t;
	tokadd('#');
	c = nextc();
    }
    pushback(c);
    if (tokadd_string(func, term, paren, &quote->nd_nest,
		      &enc) == -1) {
	if (parser->eofp) {
	    if (func & STR_FUNC_REGEXP) {
		compile_error(PARSER_ARG "unterminated regexp meets end of file");
	    }
	    else {
		compile_error(PARSER_ARG "unterminated string meets end of file");
	    }
	    quote->nd_func = -1;
	}
    }

    tokfix();
    set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
    flush_string_content(enc);

    return tSTRING_CONTENT;
}

static int
parser_heredoc_identifier(struct parser_params *parser)
{
    int c = nextc(), term, func = 0;
    int token = tSTRING_BEG;
    long len;
    int indent = 0;

    if (c == '-') {
	c = nextc();
	func = STR_FUNC_INDENT;
    }
    else if (c == '~') {
	c = nextc();
	func = STR_FUNC_INDENT;
	indent = INT_MAX;
    }
    switch (c) {
      case '\'':
	func |= str_squote; goto quoted;
      case '"':
	func |= str_dquote; goto quoted;
      case '`':
	token = tXSTRING_BEG;
	func |= str_xquote; goto quoted;

      quoted:
	newtok();
	tokadd(func);
	term = c;
	while ((c = nextc()) != -1 && c != term) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	if (c == -1) {
	    compile_error(PARSER_ARG "unterminated here document identifier");
	    return 0;
	}
	break;

      default:
	if (!parser_is_identchar()) {
	    pushback(c);
	    if (func & STR_FUNC_INDENT) {
		pushback(indent > 0 ? '~' : '-');
	    }
	    return 0;
	}
	newtok();
	tokadd(func |= str_dquote);
	do {
	    if (tokadd_mbchar(c) == -1) return 0;
	} while ((c = nextc()) != -1 && parser_is_identchar());
	pushback(c);
	break;
    }

    tokfix();
    dispatch_scan_event(tHEREDOC_BEG);
    len = lex_p - lex_pbeg;
    lex_goto_eol(parser);
    lex_strterm = rb_node_newnode(NODE_HEREDOC,
				  STR_NEW(tok(), toklen()),	/* nd_lit */
				  len,				/* nd_nth */
				  lex_lastline);		/* nd_orig */
    nd_set_line(lex_strterm, ruby_sourceline);
    ripper_flush(parser);
    heredoc_indent = indent;
    heredoc_line_indent = 0;
    return token;
}

static void
parser_heredoc_restore(struct parser_params *parser, NODE *here)
{
    VALUE line;

    lex_strterm = 0;
    line = here->nd_orig;
    lex_lastline = line;
    lex_pbeg = RSTRING_PTR(line);
    lex_pend = lex_pbeg + RSTRING_LEN(line);
    lex_p = lex_pbeg + here->nd_nth;
    heredoc_end = ruby_sourceline;
    ruby_sourceline = nd_line(here);
    dispose_string(here->nd_lit);
    rb_gc_force_recycle((VALUE)here);
    ripper_flush(parser);
}

static int
dedent_string(VALUE string, int width)
{
    char *str;
    long len;
    int i, col = 0;

    RSTRING_GETMEM(string, str, len);
    for (i = 0; i < len && col < width; i++) {
	if (str[i] == ' ') {
	    col++;
	}
	else if (str[i] == '\t') {
	    int n = TAB_WIDTH * (col / TAB_WIDTH + 1);
	    if (n > width) break;
	    col = n;
	}
	else {
	    break;
	}
    }
    MEMMOVE(str, str + i, char, len - i);
    rb_str_set_len(string, len - i);
    return i;
}

#ifndef RIPPER
static void
parser_heredoc_dedent(struct parser_params *parser, NODE *root)
{
    NODE *node, *str_node;
    int bol = TRUE;
    int indent = heredoc_indent;

    if (indent <= 0) return;

    node = str_node = root;

    if (!root) return;
    if (nd_type(root) == NODE_ARRAY) str_node = root->nd_head;

    while (str_node) {
	VALUE lit = str_node->nd_lit;
	if (bol) dedent_string(lit, indent);
	bol = TRUE;

	str_node = 0;
	while ((node = node->nd_next) != 0 && nd_type(node) == NODE_ARRAY) {
	    if ((str_node = node->nd_head) != 0) {
		enum node_type type = nd_type(str_node);
		if (type == NODE_STR || type == NODE_DSTR) break;
		bol = FALSE;
		str_node = 0;
	    }
	}
    }
}
#else /* RIPPER */
static void
parser_heredoc_dedent(struct parser_params *parser, VALUE array)
{
    if (heredoc_indent <= 0) return;

    dispatch2(heredoc_dedent, array, INT2NUM(heredoc_indent));
}

static VALUE
parser_dedent_string(VALUE self, VALUE input, VALUE width)
{
    int wid, col;

    StringValue(input);
    wid = NUM2UINT(width);
    rb_str_modify(input);
    col = dedent_string(input, wid);
    return INT2NUM(col);
}
#endif

static int
parser_whole_match_p(struct parser_params *parser,
    const char *eos, long len, int indent)
{
    const char *p = lex_pbeg;
    long n;

    if (indent) {
	while (*p && ISSPACE(*p)) p++;
    }
    n = lex_pend - (p + len);
    if (n < 0) return FALSE;
    if (n > 0 && p[len] != '\n') {
	if (p[len] != '\r') return FALSE;
	if (n <= 1 || p[len+1] != '\n') return FALSE;
    }
    return strncmp(eos, p, len) == 0;
}

#define NUM_SUFFIX_R   (1<<0)
#define NUM_SUFFIX_I   (1<<1)
#define NUM_SUFFIX_ALL 3

static int
parser_number_literal_suffix(struct parser_params *parser, int mask)
{
    int c, result = 0;
    const char *lastp = lex_p;

    while ((c = nextc()) != -1) {
	if ((mask & NUM_SUFFIX_I) && c == 'i') {
	    result |= (mask & NUM_SUFFIX_I);
	    mask &= ~NUM_SUFFIX_I;
	    /* r after i, rational of complex is disallowed */
	    mask &= ~NUM_SUFFIX_R;
	    continue;
	}
	if ((mask & NUM_SUFFIX_R) && c == 'r') {
	    result |= (mask & NUM_SUFFIX_R);
	    mask &= ~NUM_SUFFIX_R;
	    continue;
	}
	if (!ISASCII(c) || ISALPHA(c) || c == '_') {
	    lex_p = lastp;
	    return 0;
	}
	pushback(c);
	if (c == '.') {
	    c = peekc_n(1);
	    if (ISDIGIT(c)) {
		yyerror("unexpected fraction part after numeric literal");
		lex_p += 2;
		while (parser_is_identchar()) nextc();
	    }
	}
	break;
    }
    return result;
}

static int
parser_set_number_literal(struct parser_params *parser, VALUE v, int type, int suffix)
{
    if (suffix & NUM_SUFFIX_I) {
	v = rb_complex_raw(INT2FIX(0), v);
	type = tIMAGINARY;
    }
    set_yylval_literal(v);
    return type;
}

static int
parser_set_integer_literal(struct parser_params *parser, VALUE v, int suffix)
{
    int type = tINTEGER;
    if (suffix & NUM_SUFFIX_R) {
	v = rb_rational_raw1(v);
	type = tRATIONAL;
    }
    return set_number_literal(v, type, suffix);
}

#ifdef RIPPER
static void
ripper_dispatch_heredoc_end(struct parser_params *parser)
{
    VALUE str;
    if (has_delayed_token())
	dispatch_delayed_token(tSTRING_CONTENT);
    str = STR_NEW(parser->tokp, lex_pend - parser->tokp);
    ripper_dispatch1(parser, ripper_token2eventid(tHEREDOC_END), str);
    lex_goto_eol(parser);
    ripper_flush(parser);
}

#define dispatch_heredoc_end() ripper_dispatch_heredoc_end(parser)
#else
#define dispatch_heredoc_end() ((void)0)
#endif

static int
parser_here_document(struct parser_params *parser, NODE *here)
{
    int c, func, indent = 0;
    const char *eos, *p, *pend;
    long len;
    VALUE str = 0;
    rb_encoding *enc = current_enc;

    eos = RSTRING_PTR(here->nd_lit);
    len = RSTRING_LEN(here->nd_lit) - 1;
    indent = (func = *eos++) & STR_FUNC_INDENT;

    if ((c = nextc()) == -1) {
      error:
	compile_error(PARSER_ARG "can't find string \"%s\" anywhere before EOF", eos);
#ifdef RIPPER
	if (!has_delayed_token()) {
	    dispatch_scan_event(tSTRING_CONTENT);
	}
	else {
	    if (str) {
		rb_str_append(parser->delayed, str);
	    }
	    else if ((len = lex_p - parser->tokp) > 0) {
		if (!(func & STR_FUNC_REGEXP) && rb_enc_asciicompat(enc)) {
		    int cr = ENC_CODERANGE_UNKNOWN;
		    rb_str_coderange_scan_restartable(parser->tokp, lex_p, enc, &cr);
		    if (cr != ENC_CODERANGE_7BIT &&
			current_enc == rb_usascii_encoding() &&
			enc != rb_utf8_encoding()) {
			enc = rb_ascii8bit_encoding();
		    }
		}
		rb_enc_str_buf_cat(parser->delayed, parser->tokp, len, enc);
	    }
	    dispatch_delayed_token(tSTRING_CONTENT);
	}
	lex_goto_eol(parser);
#endif
      restore:
	heredoc_restore(lex_strterm);
	return 0;
    }
    if (was_bol() && whole_match_p(eos, len, indent)) {
	dispatch_heredoc_end();
	heredoc_restore(lex_strterm);
	return tSTRING_END;
    }

    if (!(func & STR_FUNC_EXPAND)) {
	do {
	    p = RSTRING_PTR(lex_lastline);
	    pend = lex_pend;
	    if (pend > p) {
		switch (pend[-1]) {
		  case '\n':
		    if (--pend == p || pend[-1] != '\r') {
			pend++;
			break;
		    }
		  case '\r':
		    --pend;
		}
	    }

	    if (heredoc_indent > 0) {
		long i = 0;
		while (p + i < pend && parser_update_heredoc_indent(parser, p[i]))
		    i++;
		heredoc_line_indent = 0;
	    }

	    if (str)
		rb_str_cat(str, p, pend - p);
	    else
		str = STR_NEW(p, pend - p);
	    if (pend < lex_pend) rb_str_cat(str, "\n", 1);
	    lex_goto_eol(parser);
	    if (heredoc_indent > 0) {
		set_yylval_str(str);
		flush_string_content(enc);
		return tSTRING_CONTENT;
	    }
	    if (nextc() == -1) {
		if (str) {
		    dispose_string(str);
		    str = 0;
		}
		goto error;
	    }
	} while (!whole_match_p(eos, len, indent));
    }
    else {
	/*	int mb = ENC_CODERANGE_7BIT, *mbp = &mb;*/
	newtok();
	if (c == '#') {
	    int t = parser_peek_variable_name(parser);
	    if (t) return t;
	    tokadd('#');
	    c = nextc();
	}
	do {
	    pushback(c);
	    if ((c = tokadd_string(func, '\n', 0, NULL, &enc)) == -1) {
		if (parser->eofp) goto error;
		goto restore;
	    }
	    if (c != '\n') {
	      flush:
		set_yylval_str(STR_NEW3(tok(), toklen(), enc, func));
		flush_string_content(enc);
		return tSTRING_CONTENT;
	    }
	    tokadd(nextc());
	    if (heredoc_indent > 0) {
		lex_goto_eol(parser);
		goto flush;
	    }
	    /*	    if (mbp && mb == ENC_CODERANGE_UNKNOWN) mbp = 0;*/
	    if ((c = nextc()) == -1) goto error;
	} while (!whole_match_p(eos, len, indent));
	str = STR_NEW3(tok(), toklen(), enc, func);
    }
    dispatch_heredoc_end();
#ifdef RIPPER
    str = ripper_new_yylval(ripper_token2eventid(tSTRING_CONTENT),
			    yylval.val, str);
#endif
    heredoc_restore(lex_strterm);
    lex_strterm = NEW_STRTERM(-1, 0, 0);
    set_yylval_str(str);
    return tSTRING_CONTENT;
}

#include "lex.c"

static void
arg_ambiguous_gen(struct parser_params *parser, char c)
{
#ifndef RIPPER
    rb_warning1("ambiguous first argument; put parentheses or a space even after `%c' operator", WARN_I(c));
#else
    dispatch1(arg_ambiguous, rb_usascii_str_new(&c, 1));
#endif
}
#define arg_ambiguous(c) (arg_ambiguous_gen(parser, (c)), 1)

static ID
formal_argument_gen(struct parser_params *parser, ID lhs)
{
    switch (id_type(lhs)) {
      case ID_LOCAL:
	break;
#ifndef RIPPER
      case ID_CONST:
	yyerror("formal argument cannot be a constant");
	return 0;
      case ID_INSTANCE:
	yyerror("formal argument cannot be an instance variable");
	return 0;
      case ID_GLOBAL:
	yyerror("formal argument cannot be a global variable");
	return 0;
      case ID_CLASS:
	yyerror("formal argument cannot be a class variable");
	return 0;
      default:
	yyerror("formal argument must be local variable");
	return 0;
#else
      default:
	lhs = dispatch1(param_error, lhs);
	ripper_error();
	return 0;
#endif
    }
    shadowing_lvar(lhs);
    return lhs;
}

static int
lvar_defined_gen(struct parser_params *parser, ID id)
{
    return (dyna_in_block() && dvar_defined_get(id)) || local_id(id);
}

/* emacsen -*- hack */
static long
parser_encode_length(struct parser_params *parser, const char *name, long len)
{
    long nlen;

    if (len > 5 && name[nlen = len - 5] == '-') {
	if (rb_memcicmp(name + nlen + 1, "unix", 4) == 0)
	    return nlen;
    }
    if (len > 4 && name[nlen = len - 4] == '-') {
	if (rb_memcicmp(name + nlen + 1, "dos", 3) == 0)
	    return nlen;
	if (rb_memcicmp(name + nlen + 1, "mac", 3) == 0 &&
	    !(len == 8 && rb_memcicmp(name, "utf8-mac", len) == 0))
	    /* exclude UTF8-MAC because the encoding named "UTF8" doesn't exist in Ruby */
	    return nlen;
    }
    return len;
}

static void
parser_set_encode(struct parser_params *parser, const char *name)
{
    int idx = rb_enc_find_index(name);
    rb_encoding *enc;
    VALUE excargs[3];

    if (idx < 0) {
	excargs[1] = rb_sprintf("unknown encoding name: %s", name);
      error:
	excargs[0] = rb_eArgError;
	excargs[2] = rb_make_backtrace();
	rb_ary_unshift(excargs[2], rb_sprintf("%"PRIsVALUE":%d", ruby_sourcefile_string, ruby_sourceline));
	rb_exc_raise(rb_make_exception(3, excargs));
    }
    enc = rb_enc_from_index(idx);
    if (!rb_enc_asciicompat(enc)) {
	excargs[1] = rb_sprintf("%s is not ASCII compatible", rb_enc_name(enc));
	goto error;
    }
    parser->enc = enc;
#ifndef RIPPER
    if (ruby_debug_lines) {
	VALUE lines = ruby_debug_lines;
	long i, n = RARRAY_LEN(lines);
	for (i = 0; i < n; ++i) {
	    rb_enc_associate_index(RARRAY_AREF(lines, i), idx);
	}
    }
#endif
}

static int
comment_at_top(struct parser_params *parser)
{
    const char *p = lex_pbeg, *pend = lex_p - 1;
    if (parser->line_count != (parser->has_shebang ? 2 : 1)) return 0;
    while (p < pend) {
	if (!ISSPACE(*p)) return 0;
	p++;
    }
    return 1;
}

typedef long (*rb_magic_comment_length_t)(struct parser_params *parser, const char *name, long len);
typedef void (*rb_magic_comment_setter_t)(struct parser_params *parser, const char *name, const char *val);

static void
magic_comment_encoding(struct parser_params *parser, const char *name, const char *val)
{
    if (!comment_at_top(parser)) {
	return;
    }
    parser_set_encode(parser, val);
}

static int
parser_get_bool(struct parser_params *parser, const char *name, const char *val)
{
    switch (*val) {
      case 't': case 'T':
	if (strcasecmp(val, "true") == 0) {
	    return TRUE;
	}
	break;
      case 'f': case 'F':
	if (strcasecmp(val, "false") == 0) {
	    return FALSE;
	}
	break;
    }
    rb_compile_warning(ruby_sourcefile, ruby_sourceline, "invalid value for %s: %s", name, val);
    return -1;
}

static void
parser_set_token_info(struct parser_params *parser, const char *name, const char *val)
{
    int b = parser_get_bool(parser, name, val);
    if (b >= 0) parser->token_info_enabled = b;
}

static void
parser_set_compile_option_flag(struct parser_params *parser, const char *name, const char *val)
{
    int b;

    if (parser->token_seen) {
	rb_warning1("`%s' is ignored after any tokens", WARN_S(name));
	return;
    }

    b = parser_get_bool(parser, name, val);
    if (b < 0) return;

    if (!parser->compile_option)
	parser->compile_option = rb_ident_hash_new();
    rb_hash_aset(parser->compile_option, ID2SYM(rb_intern(name)),
		 (b ? Qtrue : Qfalse));
}

# if WARN_PAST_SCOPE
static void
parser_set_past_scope(struct parser_params *parser, const char *name, const char *val)
{
    int b = parser_get_bool(parser, name, val);
    if (b >= 0) parser->past_scope_enabled = b;
}
# endif

struct magic_comment {
    const char *name;
    rb_magic_comment_setter_t func;
    rb_magic_comment_length_t length;
};

static const struct magic_comment magic_comments[] = {
    {"coding", magic_comment_encoding, parser_encode_length},
    {"encoding", magic_comment_encoding, parser_encode_length},
    {"frozen_string_literal", parser_set_compile_option_flag},
    {"warn_indent", parser_set_token_info},
# if WARN_PAST_SCOPE
    {"warn_past_scope", parser_set_past_scope},
# endif
};

static const char *
magic_comment_marker(const char *str, long len)
{
    long i = 2;

    while (i < len) {
	switch (str[i]) {
	  case '-':
	    if (str[i-1] == '*' && str[i-2] == '-') {
		return str + i + 1;
	    }
	    i += 2;
	    break;
	  case '*':
	    if (i + 1 >= len) return 0;
	    if (str[i+1] != '-') {
		i += 4;
	    }
	    else if (str[i-1] != '-') {
		i += 2;
	    }
	    else {
		return str + i + 2;
	    }
	    break;
	  default:
	    i += 3;
	    break;
	}
    }
    return 0;
}

static int
parser_magic_comment(struct parser_params *parser, const char *str, long len)
{
    int indicator = 0;
    VALUE name = 0, val = 0;
    const char *beg, *end, *vbeg, *vend;
#define str_copy(_s, _p, _n) ((_s) \
	? (void)(rb_str_resize((_s), (_n)), \
	   MEMCPY(RSTRING_PTR(_s), (_p), char, (_n)), (_s)) \
	: (void)((_s) = STR_NEW((_p), (_n))))

    if (len <= 7) return FALSE;
    if (!!(beg = magic_comment_marker(str, len))) {
	if (!(end = magic_comment_marker(beg, str + len - beg)))
	    return FALSE;
	indicator = TRUE;
	str = beg;
	len = end - beg - 3;
    }

    /* %r"([^\\s\'\":;]+)\\s*:\\s*(\"(?:\\\\.|[^\"])*\"|[^\"\\s;]+)[\\s;]*" */
    while (len > 0) {
	const struct magic_comment *p = magic_comments;
	char *s;
	int i;
	long n = 0;

	for (; len > 0 && *str; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		continue;
	    }
	    if (!ISSPACE(*str)) break;
	}
	for (beg = str; len > 0; str++, --len) {
	    switch (*str) {
	      case '\'': case '"': case ':': case ';':
		break;
	      default:
		if (ISSPACE(*str)) break;
		continue;
	    }
	    break;
	}
	for (end = str; len > 0 && ISSPACE(*str); str++, --len);
	if (!len) break;
	if (*str != ':') {
	    if (!indicator) return FALSE;
	    continue;
	}

	do str++; while (--len > 0 && ISSPACE(*str));
	if (!len) break;
	if (*str == '"') {
	    for (vbeg = ++str; --len > 0 && *str != '"'; str++) {
		if (*str == '\\') {
		    --len;
		    ++str;
		}
	    }
	    vend = str;
	    if (len) {
		--len;
		++str;
	    }
	}
	else {
	    for (vbeg = str; len > 0 && *str != '"' && *str != ';' && !ISSPACE(*str); --len, str++);
	    vend = str;
	}
	if (indicator) {
	    while (len > 0 && (*str == ';' || ISSPACE(*str))) --len, str++;
	}
	else {
	    while (len > 0 && (ISSPACE(*str))) --len, str++;
	    if (len) return FALSE;
	}

	n = end - beg;
	str_copy(name, beg, n);
	s = RSTRING_PTR(name);
	for (i = 0; i < n; ++i) {
	    if (s[i] == '-') s[i] = '_';
	}
	do {
	    if (STRNCASECMP(p->name, s, n) == 0 && !p->name[n]) {
		n = vend - vbeg;
		if (p->length) {
		    n = (*p->length)(parser, vbeg, n);
		}
		str_copy(val, vbeg, n);
		(*p->func)(parser, p->name, RSTRING_PTR(val));
		break;
	    }
	} while (++p < magic_comments + numberof(magic_comments));
#ifdef RIPPER
	str_copy(val, vbeg, vend - vbeg);
	dispatch2(magic_comment, name, val);
#endif
    }

    return TRUE;
}

static void
set_file_encoding(struct parser_params *parser, const char *str, const char *send)
{
    int sep = 0;
    const char *beg = str;
    VALUE s;

    for (;;) {
	if (send - str <= 6) return;
	switch (str[6]) {
	  case 'C': case 'c': str += 6; continue;
	  case 'O': case 'o': str += 5; continue;
	  case 'D': case 'd': str += 4; continue;
	  case 'I': case 'i': str += 3; continue;
	  case 'N': case 'n': str += 2; continue;
	  case 'G': case 'g': str += 1; continue;
	  case '=': case ':':
	    sep = 1;
	    str += 6;
	    break;
	  default:
	    str += 6;
	    if (ISSPACE(*str)) break;
	    continue;
	}
	if (STRNCASECMP(str-6, "coding", 6) == 0) break;
    }
    for (;;) {
	do {
	    if (++str >= send) return;
	} while (ISSPACE(*str));
	if (sep) break;
	if (*str != '=' && *str != ':') return;
	sep = 1;
	str++;
    }
    beg = str;
    while ((*str == '-' || *str == '_' || ISALNUM(*str)) && ++str < send);
    s = rb_str_new(beg, parser_encode_length(parser, beg, str - beg));
    parser_set_encode(parser, RSTRING_PTR(s));
    rb_str_resize(s, 0);
}

static void
parser_prepare(struct parser_params *parser)
{
    int c = nextc();
    parser->token_info_enabled = !compile_for_eval && RTEST(ruby_verbose);
    switch (c) {
      case '#':
	if (peek('!')) parser->has_shebang = 1;
	break;
      case 0xef:		/* UTF-8 BOM marker */
	if (lex_pend - lex_p >= 2 &&
	    (unsigned char)lex_p[0] == 0xbb &&
	    (unsigned char)lex_p[1] == 0xbf) {
	    parser->enc = rb_utf8_encoding();
	    lex_p += 2;
	    lex_pbeg = lex_p;
	    return;
	}
	break;
      case EOF:
	return;
    }
    pushback(c);
    parser->enc = rb_enc_get(lex_lastline);
    deferred_nodes = 0;
}

#define IS_ARG() IS_lex_state(EXPR_ARG_ANY)
#define IS_END() IS_lex_state(EXPR_END_ANY)
#define IS_BEG() (IS_lex_state(EXPR_BEG_ANY) || IS_lex_state_all(EXPR_ARG|EXPR_LABELED))
#define IS_SPCARG(c) (IS_ARG() && space_seen && !ISSPACE(c))
#define IS_LABEL_POSSIBLE() (\
	(IS_lex_state(EXPR_LABEL|EXPR_ENDFN) && !cmd_state) || \
	IS_ARG())
#define IS_LABEL_SUFFIX(n) (peek_n(':',(n)) && !peek_n(':', (n)+1))
#define IS_AFTER_OPERATOR() IS_lex_state(EXPR_FNAME | EXPR_DOT)

#ifndef RIPPER
#define ambiguous_operator(op, syn) ( \
    rb_warning0("`"op"' after local variable or literal is interpreted as binary operator"), \
    rb_warning0("even though it seems like "syn""))
#else
#define ambiguous_operator(op, syn) dispatch2(operator_ambiguous, ripper_intern(op), rb_str_new_cstr(syn))
#endif
#define warn_balanced(op, syn) ((void) \
    (!IS_lex_state_for(last_state, EXPR_CLASS|EXPR_DOT|EXPR_FNAME|EXPR_ENDFN|EXPR_ENDARG) && \
     space_seen && !ISSPACE(c) && \
     (ambiguous_operator(op, syn), 0)))

static VALUE
parse_rational(struct parser_params *parser, char *str, int len, int seen_point)
{
    VALUE v;
    char *point = &str[seen_point];
    size_t fraclen = len-seen_point-1;
    memmove(point, point+1, fraclen+1);
    v = rb_cstr_to_inum(str, 10, FALSE);
    return rb_rational_new(v, rb_int_positive_pow(10, fraclen));
}

static int
parse_numeric(struct parser_params *parser, int c)
{
    int is_float, seen_point, seen_e, nondigit;
    int suffix;

    is_float = seen_point = seen_e = nondigit = 0;
    SET_LEX_STATE(EXPR_END);
    newtok();
    if (c == '-' || c == '+') {
	tokadd(c);
	c = nextc();
    }
    if (c == '0') {
#define no_digits() do {yyerror("numeric literal without digits"); return 0;} while (0)
	int start = toklen();
	c = nextc();
	if (c == 'x' || c == 'X') {
	    /* hexadecimal */
	    c = nextc();
	    if (c != -1 && ISXDIGIT(c)) {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (!ISXDIGIT(c)) break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 16, FALSE), suffix);
	}
	if (c == 'b' || c == 'B') {
	    /* binary */
	    c = nextc();
	    if (c == '0' || c == '1') {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (c != '0' && c != '1') break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 2, FALSE), suffix);
	}
	if (c == 'd' || c == 'D') {
	    /* decimal */
	    c = nextc();
	    if (c != -1 && ISDIGIT(c)) {
		do {
		    if (c == '_') {
			if (nondigit) break;
			nondigit = c;
			continue;
		    }
		    if (!ISDIGIT(c)) break;
		    nondigit = 0;
		    tokadd(c);
		} while ((c = nextc()) != -1);
	    }
	    pushback(c);
	    tokfix();
	    if (toklen() == start) {
		no_digits();
	    }
	    else if (nondigit) goto trailing_uc;
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(rb_cstr_to_inum(tok(), 10, FALSE), suffix);
	}
	if (c == '_') {
	    /* 0_0 */
	    goto octal_number;
	}
	if (c == 'o' || c == 'O') {
	    /* prefixed octal */
	    c = nextc();
	    if (c == -1 || c == '_' || !ISDIGIT(c)) {
		no_digits();
	    }
	}
	if (c >= '0' && c <= '7') {
	    /* octal */
	  octal_number:
	    do {
		if (c == '_') {
		    if (nondigit) break;
		    nondigit = c;
		    continue;
		}
		if (c < '0' || c > '9') break;
		if (c > '7') goto invalid_octal;
		nondigit = 0;
		tokadd(c);
	    } while ((c = nextc()) != -1);
	    if (toklen() > start) {
		pushback(c);
		tokfix();
		if (nondigit) goto trailing_uc;
		suffix = number_literal_suffix(NUM_SUFFIX_ALL);
		return set_integer_literal(rb_cstr_to_inum(tok(), 8, FALSE), suffix);
	    }
	    if (nondigit) {
		pushback(c);
		goto trailing_uc;
	    }
	}
	if (c > '7' && c <= '9') {
	  invalid_octal:
	    yyerror("Invalid octal digit");
	}
	else if (c == '.' || c == 'e' || c == 'E') {
	    tokadd('0');
	}
	else {
	    pushback(c);
	    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
	    return set_integer_literal(INT2FIX(0), suffix);
	}
    }

    for (;;) {
	switch (c) {
	  case '0': case '1': case '2': case '3': case '4':
	  case '5': case '6': case '7': case '8': case '9':
	    nondigit = 0;
	    tokadd(c);
	    break;

	  case '.':
	    if (nondigit) goto trailing_uc;
	    if (seen_point || seen_e) {
		goto decode_num;
	    }
	    else {
		int c0 = nextc();
		if (c0 == -1 || !ISDIGIT(c0)) {
		    pushback(c0);
		    goto decode_num;
		}
		c = c0;
	    }
	    seen_point = toklen();
	    tokadd('.');
	    tokadd(c);
	    is_float++;
	    nondigit = 0;
	    break;

	  case 'e':
	  case 'E':
	    if (nondigit) {
		pushback(c);
		c = nondigit;
		goto decode_num;
	    }
	    if (seen_e) {
		goto decode_num;
	    }
	    nondigit = c;
	    c = nextc();
	    if (c != '-' && c != '+' && !ISDIGIT(c)) {
		pushback(c);
		nondigit = 0;
		goto decode_num;
	    }
	    tokadd(nondigit);
	    seen_e++;
	    is_float++;
	    tokadd(c);
	    nondigit = (c == '-' || c == '+') ? c : 0;
	    break;

	  case '_':	/* `_' in number just ignored */
	    if (nondigit) goto decode_num;
	    nondigit = c;
	    break;

	  default:
	    goto decode_num;
	}
	c = nextc();
    }

  decode_num:
    pushback(c);
    if (nondigit) {
	char tmp[30];
      trailing_uc:
	snprintf(tmp, sizeof(tmp), "trailing `%c' in number", nondigit);
	yyerror(tmp);
    }
    tokfix();
    if (is_float) {
	int type = tFLOAT;
	VALUE v;

	suffix = number_literal_suffix(seen_e ? NUM_SUFFIX_I : NUM_SUFFIX_ALL);
	if (suffix & NUM_SUFFIX_R) {
	    type = tRATIONAL;
	    v = parse_rational(parser, tok(), toklen(), seen_point);
	}
	else {
	    double d = strtod(tok(), 0);
	    if (errno == ERANGE) {
		rb_warning1("Float %s out of range", WARN_S(tok()));
		errno = 0;
	    }
	    v = DBL2NUM(d);
	}
	return set_number_literal(v, type, suffix);
    }
    suffix = number_literal_suffix(NUM_SUFFIX_ALL);
    return set_integer_literal(rb_cstr_to_inum(tok(), 10, FALSE), suffix);
}

static int
parse_qmark(struct parser_params *parser)
{
    rb_encoding *enc;
    register int c;

    if (IS_END()) {
	SET_LEX_STATE(EXPR_VALUE);
	return '?';
    }
    c = nextc();
    if (c == -1) {
	compile_error(PARSER_ARG "incomplete character syntax");
	return 0;
    }
    if (rb_enc_isspace(c, current_enc)) {
	if (!IS_ARG()) {
	    int c2 = 0;
	    switch (c) {
	      case ' ':
		c2 = 's';
		break;
	      case '\n':
		c2 = 'n';
		break;
	      case '\t':
		c2 = 't';
		break;
	      case '\v':
		c2 = 'v';
		break;
	      case '\r':
		c2 = 'r';
		break;
	      case '\f':
		c2 = 'f';
		break;
	    }
	    if (c2) {
		rb_warn1("invalid character syntax; use ?\\%c", WARN_I(c2));
	    }
	}
      ternary:
	pushback(c);
	SET_LEX_STATE(EXPR_VALUE);
	return '?';
    }
    newtok();
    enc = current_enc;
    if (!parser_isascii()) {
	if (tokadd_mbchar(c) == -1) return 0;
    }
    else if ((rb_enc_isalnum(c, current_enc) || c == '_') &&
	     lex_p < lex_pend && is_identchar(lex_p, lex_pend, current_enc)) {
	goto ternary;
    }
    else if (c == '\\') {
	if (peek('u')) {
	    nextc();
	    c = parser_tokadd_utf8(parser, &enc, 0, 0, 0);
	    if (0x80 <= c) {
		tokaddmbc(c, enc);
	    }
	    else {
		tokadd(c);
	    }
	}
	else if (!lex_eol_p() && !(c = *lex_p, ISASCII(c))) {
	    nextc();
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	else {
	    c = read_escape(0, &enc);
	    tokadd(c);
	}
    }
    else {
	tokadd(c);
    }
    tokfix();
    set_yylval_str(STR_NEW3(tok(), toklen(), enc, 0));
    SET_LEX_STATE(EXPR_END);
    return tCHAR;
}

static int
parse_percent(struct parser_params *parser, const int space_seen, const enum lex_state_e last_state)
{
    register int c;

    if (IS_BEG()) {
	int term;
	int paren;

	c = nextc();
      quotation:
	if (c == -1 || !ISALNUM(c)) {
	    term = c;
	    c = 'Q';
	}
	else {
	    term = nextc();
	    if (rb_enc_isalnum(term, current_enc) || !parser_isascii()) {
		yyerror("unknown type of %string");
		return 0;
	    }
	}
	if (c == -1 || term == -1) {
	    compile_error(PARSER_ARG "unterminated quoted string meets end of file");
	    return 0;
	}
	paren = term;
	if (term == '(') term = ')';
	else if (term == '[') term = ']';
	else if (term == '{') term = '}';
	else if (term == '<') term = '>';
	else paren = 0;

	switch (c) {
	  case 'Q':
	    lex_strterm = NEW_STRTERM(str_dquote, term, paren);
	    return tSTRING_BEG;

	  case 'q':
	    lex_strterm = NEW_STRTERM(str_squote, term, paren);
	    return tSTRING_BEG;

	  case 'W':
	    lex_strterm = NEW_STRTERM(str_dword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tWORDS_BEG;

	  case 'w':
	    lex_strterm = NEW_STRTERM(str_sword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tQWORDS_BEG;

	  case 'I':
	    lex_strterm = NEW_STRTERM(str_dword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tSYMBOLS_BEG;

	  case 'i':
	    lex_strterm = NEW_STRTERM(str_sword, term, paren);
	    do {c = nextc();} while (ISSPACE(c));
	    pushback(c);
	    return tQSYMBOLS_BEG;

	  case 'x':
	    lex_strterm = NEW_STRTERM(str_xquote, term, paren);
	    return tXSTRING_BEG;

	  case 'r':
	    lex_strterm = NEW_STRTERM(str_regexp, term, paren);
	    return tREGEXP_BEG;

	  case 's':
	    lex_strterm = NEW_STRTERM(str_ssym, term, paren);
	    SET_LEX_STATE(EXPR_FNAME|EXPR_FITEM);
	    return tSYMBEG;

	  default:
	    yyerror("unknown type of %string");
	    return 0;
	}
    }
    if ((c = nextc()) == '=') {
	set_yylval_id('%');
	SET_LEX_STATE(EXPR_BEG);
	return tOP_ASGN;
    }
    if (IS_SPCARG(c) || (IS_lex_state(EXPR_FITEM) && c == 's')) {
	goto quotation;
    }
    SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
    pushback(c);
    warn_balanced("%%", "string literal");
    return '%';
}

static int
tokadd_ident(struct parser_params *parser, int c)
{
    do {
	if (tokadd_mbchar(c) == -1) return -1;
	c = nextc();
    } while (parser_is_identchar());
    pushback(c);
    return 0;
}

static ID
tokenize_ident(struct parser_params *parser, const enum lex_state_e last_state)
{
    ID ident = TOK_INTERN();

    set_yylval_name(ident);

    return ident;
}

static int
parse_numvar(struct parser_params *parser)
{
    size_t len;
    int overflow;
    unsigned long n = ruby_scan_digits(tok()+1, toklen()-1, 10, &len, &overflow);
    const unsigned long nth_ref_max =
	((FIXNUM_MAX < INT_MAX) ? FIXNUM_MAX : INT_MAX) >> 1;
    /* NTH_REF is left-shifted to be ORed with back-ref flag and
     * turned into a Fixnum, in compile.c */

    if (overflow || n > nth_ref_max) {
	/* compile_error()? */
	rb_warn1("`%s' is too big for a number variable, always nil", WARN_S(tok()));
	return 0;		/* $0 is $PROGRAM_NAME, not NTH_REF */
    }
    else {
	return (int)n;
    }
}

static int
parse_gvar(struct parser_params *parser, const enum lex_state_e last_state)
{
    register int c;

    SET_LEX_STATE(EXPR_END);
    newtok();
    c = nextc();
    switch (c) {
      case '_':		/* $_: last read line string */
	c = nextc();
	if (parser_is_identchar()) {
	    tokadd('$');
	    tokadd('_');
	    break;
	}
	pushback(c);
	c = '_';
	/* fall through */
      case '~':		/* $~: match-data */
      case '*':		/* $*: argv */
      case '$':		/* $$: pid */
      case '?':		/* $?: last status */
      case '!':		/* $!: error string */
      case '@':		/* $@: error position */
      case '/':		/* $/: input record separator */
      case '\\':		/* $\: output record separator */
      case ';':		/* $;: field separator */
      case ',':		/* $,: output field separator */
      case '.':		/* $.: last read line number */
      case '=':		/* $=: ignorecase */
      case ':':		/* $:: load path */
      case '<':		/* $<: reading filename */
      case '>':		/* $>: default output handle */
      case '\"':		/* $": already loaded files */
	tokadd('$');
	tokadd(c);
	goto gvar;

      case '-':
	tokadd('$');
	tokadd(c);
	c = nextc();
	if (parser_is_identchar()) {
	    if (tokadd_mbchar(c) == -1) return 0;
	}
	else {
	    pushback(c);
	    pushback('-');
	    return '$';
	}
      gvar:
	set_yylval_name(TOK_INTERN());
	return tGVAR;

      case '&':		/* $&: last match */
      case '`':		/* $`: string before last match */
      case '\'':		/* $': string after last match */
      case '+':		/* $+: string matches last paren. */
	if (IS_lex_state_for(last_state, EXPR_FNAME)) {
	    tokadd('$');
	    tokadd(c);
	    goto gvar;
	}
	set_yylval_node(NEW_BACK_REF(c));
	return tBACK_REF;

      case '1': case '2': case '3':
      case '4': case '5': case '6':
      case '7': case '8': case '9':
	tokadd('$');
	do {
	    tokadd(c);
	    c = nextc();
	} while (c != -1 && ISDIGIT(c));
	pushback(c);
	if (IS_lex_state_for(last_state, EXPR_FNAME)) goto gvar;
	tokfix();
	set_yylval_node(NEW_NTH_REF(parse_numvar(parser)));
	return tNTH_REF;

      default:
	if (!parser_is_identchar()) {
	    if (c == -1 || ISSPACE(c)) {
		compile_error(PARSER_ARG "`$' without identifiers is not allowed as a global variable name");
	    }
	    else {
		pushback(c);
		compile_error(PARSER_ARG "`$%c' is not allowed as a global variable name", c);
	    }
	    return 0;
	}
      case '0':
	tokadd('$');
    }

    if (tokadd_ident(parser, c)) return 0;
    SET_LEX_STATE(EXPR_END);
    tokenize_ident(parser, last_state);
    return tGVAR;
}

static int
parse_atmark(struct parser_params *parser, const enum lex_state_e last_state)
{
    int result = tIVAR;
    register int c = nextc();

    newtok();
    tokadd('@');
    if (c == '@') {
	result = tCVAR;
	tokadd('@');
	c = nextc();
    }
    if (c == -1 || ISSPACE(c)) {
	if (result == tIVAR) {
	    compile_error(PARSER_ARG "`@' without identifiers is not allowed as an instance variable name");
	}
	else {
	    compile_error(PARSER_ARG "`@@' without identifiers is not allowed as a class variable name");
	}
	return 0;
    }
    else if (ISDIGIT(c) || !parser_is_identchar()) {
	pushback(c);
	if (result == tIVAR) {
	    compile_error(PARSER_ARG "`@%c' is not allowed as an instance variable name", c);
	}
	else {
	    compile_error(PARSER_ARG "`@@%c' is not allowed as a class variable name", c);
	}
	return 0;
    }

    if (tokadd_ident(parser, c)) return 0;
    SET_LEX_STATE(EXPR_END);
    tokenize_ident(parser, last_state);
    return result;
}

static int
parse_ident(struct parser_params *parser, int c, int cmd_state)
{
    int result = 0;
    int mb = ENC_CODERANGE_7BIT;
    const enum lex_state_e last_state = lex_state;
    ID ident;

    do {
	if (!ISASCII(c)) mb = ENC_CODERANGE_UNKNOWN;
	if (tokadd_mbchar(c) == -1) return 0;
	c = nextc();
    } while (parser_is_identchar());
    if ((c == '!' || c == '?') && !peek('=')) {
	tokadd(c);
    }
    else {
	pushback(c);
    }
    tokfix();

    if (toklast() == '!' || toklast() == '?') {
	result = tFID;
    }
    else {
	if (IS_lex_state(EXPR_FNAME)) {
	    register int c = nextc();
	    if (c == '=' && !peek('~') && !peek('>') &&
		(!peek('=') || (peek_n('>', 1)))) {
		result = tIDENTIFIER;
		tokadd(c);
		tokfix();
	    }
	    else {
		pushback(c);
	    }
	}
	if (result == 0 && ISUPPER(tok()[0])) {
	    result = tCONSTANT;
	}
	else {
	    result = tIDENTIFIER;
	}
    }

    if (IS_LABEL_POSSIBLE()) {
	if (IS_LABEL_SUFFIX(0)) {
	    SET_LEX_STATE(EXPR_ARG|EXPR_LABELED);
	    nextc();
	    set_yylval_name(TOK_INTERN());
	    return tLABEL;
	}
    }
    if (mb == ENC_CODERANGE_7BIT && !IS_lex_state(EXPR_DOT)) {
	const struct kwtable *kw;

	/* See if it is a reserved word.  */
	kw = rb_reserved_word(tok(), toklen());
	if (kw) {
	    enum lex_state_e state = lex_state;
	    SET_LEX_STATE(kw->state);
	    if (IS_lex_state_for(state, EXPR_FNAME)) {
		set_yylval_name(rb_intern2(tok(), toklen()));
		return kw->id[0];
	    }
	    if (IS_lex_state(EXPR_BEG)) {
		command_start = TRUE;
	    }
	    if (kw->id[0] == keyword_do) {
		if (lpar_beg && lpar_beg == paren_nest) {
		    lpar_beg = 0;
		    --paren_nest;
		    return keyword_do_LAMBDA;
		}
		if (COND_P()) return keyword_do_cond;
		if (CMDARG_P() && !IS_lex_state_for(state, EXPR_CMDARG))
		    return keyword_do_block;
		if (IS_lex_state_for(state, (EXPR_BEG | EXPR_ENDARG)))
		    return keyword_do_block;
		return keyword_do;
	    }
	    if (IS_lex_state_for(state, (EXPR_BEG | EXPR_LABELED)))
		return kw->id[0];
	    else {
		if (kw->id[0] != kw->id[1])
		    SET_LEX_STATE(EXPR_BEG | EXPR_LABEL);
		return kw->id[1];
	    }
	}
    }

    if (IS_lex_state(EXPR_BEG_ANY | EXPR_ARG_ANY | EXPR_DOT)) {
	if (cmd_state) {
	    SET_LEX_STATE(EXPR_CMDARG);
	}
	else {
	    SET_LEX_STATE(EXPR_ARG);
	}
    }
    else if (lex_state == EXPR_FNAME) {
	SET_LEX_STATE(EXPR_ENDFN);
    }
    else {
	SET_LEX_STATE(EXPR_END);
    }

    ident = tokenize_ident(parser, last_state);
    if (!IS_lex_state_for(last_state, EXPR_DOT|EXPR_FNAME) &&
	(result == tIDENTIFIER) && /* not EXPR_FNAME, not attrasgn */
	lvar_defined(ident)) {
	SET_LEX_STATE(EXPR_END|EXPR_LABEL);
    }
    return result;
}

static int
parser_yylex(struct parser_params *parser)
{
    register int c;
    int space_seen = 0;
    int cmd_state;
    int label;
    enum lex_state_e last_state;
    int fallthru = FALSE;
    int token_seen = parser->token_seen;

    if (lex_strterm) {
	int token;
	if (nd_type(lex_strterm) == NODE_HEREDOC) {
	    token = here_document(lex_strterm);
	    if (token == tSTRING_END) {
		lex_strterm = 0;
		SET_LEX_STATE(EXPR_END);
	    }
	}
	else {
	    token = parse_string(lex_strterm);
	    if ((token == tSTRING_END) && (lex_strterm->nd_func & STR_FUNC_LABEL)) {
		if (((IS_lex_state(EXPR_BEG | EXPR_ENDFN) && !COND_P()) || IS_ARG()) &&
		    IS_LABEL_SUFFIX(0)) {
		    nextc();
		    token = tLABEL_END;
		}
	    }
	    if (token == tSTRING_END || token == tREGEXP_END || token == tLABEL_END) {
		rb_gc_force_recycle((VALUE)lex_strterm);
		lex_strterm = 0;
		SET_LEX_STATE(token == tLABEL_END ? EXPR_BEG|EXPR_LABEL : EXPR_END);
	    }
	}
	return token;
    }
    cmd_state = command_start;
    command_start = FALSE;
    parser->token_seen = TRUE;
  retry:
    last_state = lex_state;
    switch (c = nextc()) {
      case '\0':		/* NUL */
      case '\004':		/* ^D */
      case '\032':		/* ^Z */
      case -1:			/* end of script. */
	return 0;

	/* white spaces */
      case ' ': case '\t': case '\f': case '\r':
      case '\13': /* '\v' */
	space_seen = 1;
#ifdef RIPPER
	while ((c = nextc())) {
	    switch (c) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		break;
	      default:
		goto outofloop;
	    }
	}
      outofloop:
	pushback(c);
	dispatch_scan_event(tSP);
#endif
	goto retry;

      case '#':		/* it's a comment */
	parser->token_seen = token_seen;
	/* no magic_comment in shebang line */
	if (!parser_magic_comment(parser, lex_p, lex_pend - lex_p)) {
	    if (comment_at_top(parser)) {
		set_file_encoding(parser, lex_p, lex_pend);
	    }
	}
	lex_p = lex_pend;
        dispatch_scan_event(tCOMMENT);
        fallthru = TRUE;
	/* fall through */
      case '\n':
	parser->token_seen = token_seen;
	c = (IS_lex_state(EXPR_BEG|EXPR_CLASS|EXPR_FNAME|EXPR_DOT) &&
	     !IS_lex_state(EXPR_LABELED));
	if (c || IS_lex_state_all(EXPR_ARG|EXPR_LABELED)) {
            if (!fallthru) {
                dispatch_scan_event(tIGNORED_NL);
            }
            fallthru = FALSE;
	    if (!c && parser->in_kwarg) {
		goto normal_newline;
	    }
	    goto retry;
	}
	while (1) {
	    switch (c = nextc()) {
	      case ' ': case '\t': case '\f': case '\r':
	      case '\13': /* '\v' */
		space_seen = 1;
		break;
	      case '&':
	      case '.': {
		dispatch_delayed_token(tIGNORED_NL);
		if (peek('.') == (c == '&')) {
		    pushback(c);
		    dispatch_scan_event(tSP);
		    goto retry;
		}
	      }
	      default:
		--ruby_sourceline;
		lex_nextline = lex_lastline;
	      case -1:		/* EOF no decrement*/
		lex_goto_eol(parser);
#ifdef RIPPER
		if (c != -1) {
		    parser->tokp = lex_p;
		}
#endif
		goto normal_newline;
	    }
	}
      normal_newline:
	command_start = TRUE;
	SET_LEX_STATE(EXPR_BEG);
	return '\n';

      case '*':
	if ((c = nextc()) == '*') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tPOW);
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_SPCARG(c)) {
		rb_warning0("`**' interpreted as argument prefix");
		c = tDSTAR;
	    }
	    else if (IS_BEG()) {
		c = tDSTAR;
	    }
	    else {
		warn_balanced("**", "argument prefix");
		c = tPOW;
	    }
	}
	else {
	    if (c == '=') {
                set_yylval_id('*');
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    if (IS_SPCARG(c)) {
		rb_warning0("`*' interpreted as argument prefix");
		c = tSTAR;
	    }
	    else if (IS_BEG()) {
		c = tSTAR;
	    }
	    else {
		warn_balanced("*", "argument prefix");
		c = '*';
	    }
	}
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	return c;

      case '!':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    SET_LEX_STATE(EXPR_ARG);
	    if (c == '@') {
		return '!';
	    }
	}
	else {
	    SET_LEX_STATE(EXPR_BEG);
	}
	if (c == '=') {
	    return tNEQ;
	}
	if (c == '~') {
	    return tNMATCH;
	}
	pushback(c);
	return '!';

      case '=':
	if (was_bol()) {
	    /* skip embedded rd document */
	    if (strncmp(lex_p, "begin", 5) == 0 && ISSPACE(lex_p[5])) {
		int first_p = TRUE;

		lex_goto_eol(parser);
		dispatch_scan_event(tEMBDOC_BEG);
		for (;;) {
		    lex_goto_eol(parser);
		    if (!first_p) {
			dispatch_scan_event(tEMBDOC);
		    }
		    first_p = FALSE;
		    c = nextc();
		    if (c == -1) {
			compile_error(PARSER_ARG "embedded document meets end of file");
			return 0;
		    }
		    if (c != '=') continue;
		    if (c == '=' && strncmp(lex_p, "end", 3) == 0 &&
			(lex_p + 3 == lex_pend || ISSPACE(lex_p[3]))) {
			break;
		    }
		}
		lex_goto_eol(parser);
		dispatch_scan_event(tEMBDOC_END);
		goto retry;
	    }
	}

	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	if ((c = nextc()) == '=') {
	    if ((c = nextc()) == '=') {
		return tEQQ;
	    }
	    pushback(c);
	    return tEQ;
	}
	if (c == '~') {
	    return tMATCH;
	}
	else if (c == '>') {
	    return tASSOC;
	}
	pushback(c);
	return '=';

      case '<':
	last_state = lex_state;
	c = nextc();
	if (c == '<' &&
	    !IS_lex_state(EXPR_DOT | EXPR_CLASS) &&
	    !IS_END() &&
	    (!IS_ARG() || IS_lex_state(EXPR_LABELED) || space_seen)) {
	    int token = heredoc_identifier();
	    if (token) return token;
	}
	if (IS_AFTER_OPERATOR()) {
	    SET_LEX_STATE(EXPR_ARG);
	}
	else {
	    if (IS_lex_state(EXPR_CLASS))
		command_start = TRUE;
	    SET_LEX_STATE(EXPR_BEG);
	}
	if (c == '=') {
	    if ((c = nextc()) == '>') {
		return tCMP;
	    }
	    pushback(c);
	    return tLEQ;
	}
	if (c == '<') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tLSHFT);
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    warn_balanced("<<", "here document");
	    return tLSHFT;
	}
	pushback(c);
	return '<';

      case '>':
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	if ((c = nextc()) == '=') {
	    return tGEQ;
	}
	if (c == '>') {
	    if ((c = nextc()) == '=') {
                set_yylval_id(tRSHFT);
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tRSHFT;
	}
	pushback(c);
	return '>';

      case '"':
	label = (IS_LABEL_POSSIBLE() ? str_label : 0);
	lex_strterm = NEW_STRTERM(str_dquote | label, '"', 0);
	return tSTRING_BEG;

      case '`':
	if (IS_lex_state(EXPR_FNAME)) {
	    SET_LEX_STATE(EXPR_ENDFN);
	    return c;
	}
	if (IS_lex_state(EXPR_DOT)) {
	    if (cmd_state)
		SET_LEX_STATE(EXPR_CMDARG);
	    else
		SET_LEX_STATE(EXPR_ARG);
	    return c;
	}
	lex_strterm = NEW_STRTERM(str_xquote, '`', 0);
	return tXSTRING_BEG;

      case '\'':
	label = (IS_LABEL_POSSIBLE() ? str_label : 0);
	lex_strterm = NEW_STRTERM(str_squote | label, '\'', 0);
	return tSTRING_BEG;

      case '?':
	return parse_qmark(parser);

      case '&':
	if ((c = nextc()) == '&') {
	    SET_LEX_STATE(EXPR_BEG);
	    if ((c = nextc()) == '=') {
                set_yylval_id(tANDOP);
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tANDOP;
	}
	else if (c == '=') {
            set_yylval_id('&');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	else if (c == '.') {
	    SET_LEX_STATE(EXPR_DOT);
	    return tANDDOT;
	}
	pushback(c);
	if (IS_SPCARG(c)) {
	    rb_warning0("`&' interpreted as argument prefix");
	    c = tAMPER;
	}
	else if (IS_BEG()) {
	    c = tAMPER;
	}
	else {
	    warn_balanced("&", "argument prefix");
	    c = '&';
	}
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	return c;

      case '|':
	if ((c = nextc()) == '|') {
	    SET_LEX_STATE(EXPR_BEG);
	    if ((c = nextc()) == '=') {
                set_yylval_id(tOROP);
		SET_LEX_STATE(EXPR_BEG);
		return tOP_ASGN;
	    }
	    pushback(c);
	    return tOROP;
	}
	if (c == '=') {
            set_yylval_id('|');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG|EXPR_LABEL);
	pushback(c);
	return '|';

      case '+':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    SET_LEX_STATE(EXPR_ARG);
	    if (c == '@') {
		return tUPLUS;
	    }
	    pushback(c);
	    return '+';
	}
	if (c == '=') {
            set_yylval_id('+');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous('+'))) {
	    SET_LEX_STATE(EXPR_BEG);
	    pushback(c);
	    if (c != -1 && ISDIGIT(c)) {
		return parse_numeric(parser, '+');
	    }
	    return tUPLUS;
	}
	SET_LEX_STATE(EXPR_BEG);
	pushback(c);
	warn_balanced("+", "unary operator");
	return '+';

      case '-':
	c = nextc();
	if (IS_AFTER_OPERATOR()) {
	    SET_LEX_STATE(EXPR_ARG);
	    if (c == '@') {
		return tUMINUS;
	    }
	    pushback(c);
	    return '-';
	}
	if (c == '=') {
            set_yylval_id('-');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	if (c == '>') {
	    SET_LEX_STATE(EXPR_ENDFN);
	    return tLAMBDA;
	}
	if (IS_BEG() || (IS_SPCARG(c) && arg_ambiguous('-'))) {
	    SET_LEX_STATE(EXPR_BEG);
	    pushback(c);
	    if (c != -1 && ISDIGIT(c)) {
		return tUMINUS_NUM;
	    }
	    return tUMINUS;
	}
	SET_LEX_STATE(EXPR_BEG);
	pushback(c);
	warn_balanced("-", "unary operator");
	return '-';

      case '.':
	SET_LEX_STATE(EXPR_BEG);
	if ((c = nextc()) == '.') {
	    if ((c = nextc()) == '.') {
		return tDOT3;
	    }
	    pushback(c);
	    return tDOT2;
	}
	pushback(c);
	if (c != -1 && ISDIGIT(c)) {
	    yyerror("no .<digit> floating literal anymore; put 0 before dot");
	}
	SET_LEX_STATE(EXPR_DOT);
	return '.';

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	return parse_numeric(parser, c);

      case ')':
      case ']':
	paren_nest--;
      case '}':
	COND_LEXPOP();
	CMDARG_LEXPOP();
	if (c == ')')
	    SET_LEX_STATE(EXPR_ENDFN);
	else
	    SET_LEX_STATE(EXPR_ENDARG);
	if (c == '}') {
	    if (!brace_nest--) c = tSTRING_DEND;
	}
	return c;

      case ':':
	c = nextc();
	if (c == ':') {
	    if (IS_BEG() || IS_lex_state(EXPR_CLASS) || IS_SPCARG(-1)) {
		SET_LEX_STATE(EXPR_BEG);
		return tCOLON3;
	    }
	    SET_LEX_STATE(EXPR_DOT);
	    return tCOLON2;
	}
	if (IS_END() || ISSPACE(c) || c == '#') {
	    pushback(c);
	    warn_balanced(":", "symbol literal");
	    SET_LEX_STATE(EXPR_BEG);
	    return ':';
	}
	switch (c) {
	  case '\'':
	    lex_strterm = NEW_STRTERM(str_ssym, c, 0);
	    break;
	  case '"':
	    lex_strterm = NEW_STRTERM(str_dsym, c, 0);
	    break;
	  default:
	    pushback(c);
	    break;
	}
	SET_LEX_STATE(EXPR_FNAME);
	return tSYMBEG;

      case '/':
	if (IS_BEG()) {
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	if ((c = nextc()) == '=') {
            set_yylval_id('/');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	pushback(c);
	if (IS_SPCARG(c)) {
	    (void)arg_ambiguous('/');
	    lex_strterm = NEW_STRTERM(str_regexp, '/', 0);
	    return tREGEXP_BEG;
	}
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	warn_balanced("/", "regexp literal");
	return '/';

      case '^':
	if ((c = nextc()) == '=') {
            set_yylval_id('^');
	    SET_LEX_STATE(EXPR_BEG);
	    return tOP_ASGN;
	}
	SET_LEX_STATE(IS_AFTER_OPERATOR() ? EXPR_ARG : EXPR_BEG);
	pushback(c);
	return '^';

      case ';':
	SET_LEX_STATE(EXPR_BEG);
	command_start = TRUE;
	return ';';

      case ',':
	SET_LEX_STATE(EXPR_BEG|EXPR_LABEL);
	return ',';

      case '~':
	if (IS_AFTER_OPERATOR()) {
	    if ((c = nextc()) != '@') {
		pushback(c);
	    }
	    SET_LEX_STATE(EXPR_ARG);
	}
	else {
	    SET_LEX_STATE(EXPR_BEG);
	}
	return '~';

      case '(':
	if (IS_BEG()) {
	    c = tLPAREN;
	}
	else if (IS_SPCARG(-1)) {
	    c = tLPAREN_ARG;
	}
	paren_nest++;
	COND_PUSH(0);
	CMDARG_PUSH(0);
	SET_LEX_STATE(EXPR_BEG|EXPR_LABEL);
	return c;

      case '[':
	paren_nest++;
	if (IS_AFTER_OPERATOR()) {
	    SET_LEX_STATE(EXPR_ARG);
	    if ((c = nextc()) == ']') {
		if ((c = nextc()) == '=') {
		    return tASET;
		}
		pushback(c);
		return tAREF;
	    }
	    pushback(c);
	    lex_state |= EXPR_LABEL;
	    return '[';
	}
	else if (IS_BEG()) {
	    c = tLBRACK;
	}
	else if (IS_ARG() && (space_seen || IS_lex_state(EXPR_LABELED))) {
	    c = tLBRACK;
	}
	SET_LEX_STATE(EXPR_BEG|EXPR_LABEL);
	COND_PUSH(0);
	CMDARG_PUSH(0);
	return c;

      case '{':
	++brace_nest;
	if (lpar_beg && lpar_beg == paren_nest) {
	    SET_LEX_STATE(EXPR_BEG);
	    lpar_beg = 0;
	    --paren_nest;
	    COND_PUSH(0);
	    CMDARG_PUSH(0);
	    return tLAMBEG;
	}
	if (IS_lex_state(EXPR_LABELED))
	    c = tLBRACE;      /* hash */
	else if (IS_lex_state(EXPR_ARG_ANY | EXPR_END | EXPR_ENDFN))
	    c = '{';          /* block (primary) */
	else if (IS_lex_state(EXPR_ENDARG))
	    c = tLBRACE_ARG;  /* block (expr) */
	else
	    c = tLBRACE;      /* hash */
	COND_PUSH(0);
	CMDARG_PUSH(0);
	SET_LEX_STATE(EXPR_BEG);
	if (c != tLBRACE_ARG) lex_state |= EXPR_LABEL;
	if (c != tLBRACE) command_start = TRUE;
	return c;

      case '\\':
	c = nextc();
	if (c == '\n') {
	    space_seen = 1;
	    dispatch_scan_event(tSP);
	    goto retry; /* skip \\n */
	}
	pushback(c);
	return '\\';

      case '%':
	return parse_percent(parser, space_seen, last_state);

      case '$':
	return parse_gvar(parser, last_state);

      case '@':
	return parse_atmark(parser, last_state);

      case '_':
	if (was_bol() && whole_match_p("__END__", 7, 0)) {
	    ruby__end__seen = 1;
	    parser->eofp = 1;
#ifndef RIPPER
	    return -1;
#else
            lex_goto_eol(parser);
            dispatch_scan_event(k__END__);
            return 0;
#endif
	}
	newtok();
	break;

      default:
	if (!parser_is_identchar()) {
	    compile_error(PARSER_ARG  "Invalid char `\\x%02X' in expression", c);
	    goto retry;
	}

	newtok();
	break;
    }

    return parse_ident(parser, c, cmd_state);
}

static int
yylex(YYSTYPE *lval, struct parser_params *parser)
{
    int t;

    parser->lval = lval;
    lval->val = Qundef;
    t = parser_yylex(parser);
    if (has_delayed_token())
	dispatch_delayed_token(t);
    else if (t != 0)
	dispatch_scan_event(t);

    return t;
}

#ifndef RIPPER
static NODE*
node_newnode(struct parser_params *parser, enum node_type type, VALUE a0, VALUE a1, VALUE a2)
{
    NODE *n = (rb_node_newnode)(type, a0, a1, a2);
    nd_set_line(n, ruby_sourceline);
    return n;
}

static enum node_type
nodetype(NODE *node)			/* for debug */
{
    return (enum node_type)nd_type(node);
}

static int
nodeline(NODE *node)
{
    return nd_line(node);
}

static NODE*
newline_node(NODE *node)
{
    if (node) {
	node = remove_begin(node);
	node->flags |= NODE_FL_NEWLINE;
    }
    return node;
}

static void
fixpos(NODE *node, NODE *orig)
{
    if (!node) return;
    if (!orig) return;
    if (orig == (NODE*)1) return;
    nd_set_line(node, nd_line(orig));
}

static void
parser_warning(struct parser_params *parser, NODE *node, const char *mesg)
{
    rb_compile_warning(ruby_sourcefile, nd_line(node), "%s", mesg);
}
#define parser_warning(node, mesg) parser_warning(parser, (node), (mesg))

static void
parser_warn(struct parser_params *parser, NODE *node, const char *mesg)
{
    rb_compile_warn(ruby_sourcefile, nd_line(node), "%s", mesg);
}
#define parser_warn(node, mesg) parser_warn(parser, (node), (mesg))

static NODE*
block_append_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    NODE *end, *h = head, *nd;

    if (tail == 0) return head;

    if (h == 0) return tail;
    switch (nd_type(h)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_SELF:
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	parser_warning(h, "unused literal ignored");
	return tail;
      default:
	h = end = NEW_BLOCK(head);
	end->nd_end = end;
	fixpos(end, head);
	head = end;
	break;
      case NODE_BLOCK:
	end = h->nd_end;
	break;
    }

    nd = end->nd_head;
    switch (nd_type(nd)) {
      case NODE_RETURN:
      case NODE_BREAK:
      case NODE_NEXT:
      case NODE_REDO:
      case NODE_RETRY:
	if (RTEST(ruby_verbose)) {
	    parser_warning(tail, "statement not reached");
	}
	break;

      default:
	break;
    }

    if (nd_type(tail) != NODE_BLOCK) {
	tail = NEW_BLOCK(tail);
	tail->nd_end = tail;
    }
    end->nd_next = tail;
    h->nd_end = tail->nd_end;
    return head;
}

/* append item to the list */
static NODE*
list_append_gen(struct parser_params *parser, NODE *list, NODE *item)
{
    NODE *last;

    if (list == 0) return NEW_LIST(item);
    if (list->nd_next) {
	last = list->nd_next->nd_end;
    }
    else {
	last = list;
    }

    list->nd_alen += 1;
    last->nd_next = NEW_LIST(item);
    list->nd_next->nd_end = last->nd_next;
    return list;
}

/* concat two lists */
static NODE*
list_concat(NODE *head, NODE *tail)
{
    NODE *last;

    if (head->nd_next) {
	last = head->nd_next->nd_end;
    }
    else {
	last = head;
    }

    head->nd_alen += tail->nd_alen;
    last->nd_next = tail;
    if (tail->nd_next) {
	head->nd_next->nd_end = tail->nd_next->nd_end;
    }
    else {
	head->nd_next->nd_end = tail;
    }

    return head;
}

static int
literal_concat0(struct parser_params *parser, VALUE head, VALUE tail)
{
    if (NIL_P(tail)) return 1;
    if (!rb_enc_compatible(head, tail)) {
	compile_error(PARSER_ARG "string literal encodings differ (%s / %s)",
		      rb_enc_name(rb_enc_get(head)),
		      rb_enc_name(rb_enc_get(tail)));
	rb_str_resize(head, 0);
	rb_str_resize(tail, 0);
	return 0;
    }
    rb_str_buf_append(head, tail);
    return 1;
}

/* concat two string literals */
static NODE *
literal_concat_gen(struct parser_params *parser, NODE *head, NODE *tail)
{
    enum node_type htype;
    NODE *headlast;
    VALUE lit;

    if (!head) return tail;
    if (!tail) return head;

    htype = nd_type(head);
    if (htype == NODE_EVSTR) {
	NODE *node = NEW_DSTR(STR_NEW0());
	head = list_append(node, head);
	htype = NODE_DSTR;
    }
    if (heredoc_indent > 0) {
	switch (htype) {
	  case NODE_STR:
	    nd_set_type(head, NODE_DSTR);
	  case NODE_DSTR:
	    return list_append(head, tail);
	  default:
	    break;
	}
    }
    switch (nd_type(tail)) {
      case NODE_STR:
	if (htype == NODE_DSTR && (headlast = head->nd_next->nd_end->nd_head) &&
	    nd_type(headlast) == NODE_STR) {
	    htype = NODE_STR;
	    lit = headlast->nd_lit;
	}
	else {
	    lit = head->nd_lit;
	}
	if (htype == NODE_STR) {
	    if (!literal_concat0(parser, lit, tail->nd_lit)) {
	      error:
		rb_gc_force_recycle((VALUE)head);
		rb_gc_force_recycle((VALUE)tail);
		return 0;
	    }
	    rb_gc_force_recycle((VALUE)tail);
	}
	else {
	    list_append(head, tail);
	}
	break;

      case NODE_DSTR:
	if (htype == NODE_STR) {
	    if (!literal_concat0(parser, head->nd_lit, tail->nd_lit))
		goto error;
	    tail->nd_lit = head->nd_lit;
	    rb_gc_force_recycle((VALUE)head);
	    head = tail;
	}
	else if (NIL_P(tail->nd_lit)) {
	  append:
	    head->nd_alen += tail->nd_alen - 1;
	    head->nd_next->nd_end->nd_next = tail->nd_next;
	    head->nd_next->nd_end = tail->nd_next->nd_end;
	    rb_gc_force_recycle((VALUE)tail);
	}
	else if (htype == NODE_DSTR && (headlast = head->nd_next->nd_end->nd_head) &&
		 nd_type(headlast) == NODE_STR) {
	    lit = headlast->nd_lit;
	    if (!literal_concat0(parser, lit, tail->nd_lit))
		goto error;
	    tail->nd_lit = Qnil;
	    goto append;
	}
	else {
	    nd_set_type(tail, NODE_ARRAY);
	    tail->nd_head = NEW_STR(tail->nd_lit);
	    list_concat(head, tail);
	}
	break;

      case NODE_EVSTR:
	if (htype == NODE_STR) {
	    nd_set_type(head, NODE_DSTR);
	    head->nd_alen = 1;
	}
	list_append(head, tail);
	break;
    }
    return head;
}

static NODE *
evstr2dstr_gen(struct parser_params *parser, NODE *node)
{
    if (nd_type(node) == NODE_EVSTR) {
	node = list_append(NEW_DSTR(STR_NEW0()), node);
    }
    return node;
}

static NODE *
new_evstr_gen(struct parser_params *parser, NODE *node)
{
    NODE *head = node;

    if (node) {
	switch (nd_type(node)) {
	  case NODE_STR: case NODE_DSTR: case NODE_EVSTR:
	    return node;
	}
    }
    return NEW_EVSTR(head);
}

static NODE *
call_bin_op_gen(struct parser_params *parser, NODE *recv, ID id, NODE *arg1)
{
    value_expr(recv);
    value_expr(arg1);
    return NEW_CALL(recv, id, NEW_LIST(arg1));
}

static NODE *
call_uni_op_gen(struct parser_params *parser, NODE *recv, ID id)
{
    value_expr(recv);
    return NEW_CALL(recv, id, 0);
}

static NODE*
match_op_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    value_expr(node1);
    value_expr(node2);
    if (node1) {
	switch (nd_type(node1)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH2(node1, node2);

	  case NODE_LIT:
	    if (RB_TYPE_P(node1->nd_lit, T_REGEXP)) {
		return NEW_MATCH2(node1, node2);
	    }
	}
    }

    if (node2) {
	switch (nd_type(node2)) {
	  case NODE_DREGX:
	  case NODE_DREGX_ONCE:
	    return NEW_MATCH3(node2, node1);

	  case NODE_LIT:
	    if (RB_TYPE_P(node2->nd_lit, T_REGEXP)) {
		return NEW_MATCH3(node2, node1);
	    }
	}
    }

    return NEW_CALL(node1, tMATCH, NEW_LIST(node2));
}

# if WARN_PAST_SCOPE
static int
past_dvar_p(struct parser_params *parser, ID id)
{
    struct vtable *past = lvtbl->past;
    while (past) {
	if (vtable_included(past, id)) return 1;
	past = past->prev;
    }
    return 0;
}
# endif

static NODE*
gettable_gen(struct parser_params *parser, ID id)
{
    switch (id) {
      case keyword_self:
	return NEW_SELF();
      case keyword_nil:
	return NEW_NIL();
      case keyword_true:
	return NEW_TRUE();
      case keyword_false:
	return NEW_FALSE();
      case keyword__FILE__:
	return NEW_STR(rb_str_dup(ruby_sourcefile_string));
      case keyword__LINE__:
	return NEW_LIT(INT2FIX(tokline));
      case keyword__ENCODING__:
	return NEW_LIT(rb_enc_from_encoding(current_enc));
    }
    switch (id_type(id)) {
      case ID_LOCAL:
	if (dyna_in_block() && dvar_defined(id)) {
	    if (id == current_arg) {
		rb_warn1("circular argument reference - %"PRIsWARN, rb_id2str(id));
	    }
	    return NEW_DVAR(id);
	}
	if (local_id(id)) {
	    if (id == current_arg) {
		rb_warn1("circular argument reference - %"PRIsWARN, rb_id2str(id));
	    }
	    return NEW_LVAR(id);
	}
# if WARN_PAST_SCOPE
	if (!in_defined && RTEST(ruby_verbose) && past_dvar_p(parser, id)) {
	    rb_warning1("possible reference to past scope - %"PRIsWARN, rb_id2str(id));
	}
# endif
	/* method call without arguments */
	return NEW_VCALL(id);
      case ID_GLOBAL:
	return NEW_GVAR(id);
      case ID_INSTANCE:
	return NEW_IVAR(id);
      case ID_CONST:
	return NEW_CONST(id);
      case ID_CLASS:
	return NEW_CVAR(id);
    }
    compile_error(PARSER_ARG "identifier %"PRIsVALUE" is not valid to get", rb_id2str(id));
    return 0;
}

static NODE *
kwd_append(NODE *kwlist, NODE *kw)
{
    if (kwlist) {
	NODE *kws = kwlist;
	while (kws->nd_next) {
	    kws = kws->nd_next;
	}
	kws->nd_next = kw;
    }
    return kwlist;
}
#else  /* !RIPPER */
static int
id_is_var_gen(struct parser_params *parser, ID id)
{
    if (is_notop_id(id)) {
	switch (id & ID_SCOPE_MASK) {
	  case ID_GLOBAL: case ID_INSTANCE: case ID_CONST: case ID_CLASS:
	    return 1;
	  case ID_LOCAL:
	    if (dyna_in_block() && dvar_defined(id)) return 1;
	    if (local_id(id)) return 1;
	    /* method call without arguments */
	    return 0;
	}
    }
    compile_error(PARSER_ARG "identifier %s is not valid to get", rb_id2str(id));
    return 0;
}
#endif /* !RIPPER */

static const char lex_state_names[][13] = {
    "EXPR_BEG",    "EXPR_END",    "EXPR_ENDARG", "EXPR_ENDFN",  "EXPR_ARG",
    "EXPR_CMDARG", "EXPR_MID",    "EXPR_FNAME",  "EXPR_DOT",    "EXPR_CLASS",
    "EXPR_LABEL",  "EXPR_LABELED","EXPR_FITEM",
};

static VALUE
append_lex_state_name(enum lex_state_e state, VALUE buf)
{
    int i, sep = 0;
    unsigned int mask = 1;
    static const char none[] = "EXPR_NONE";

    for (i = 0; i < EXPR_MAX_STATE; ++i, mask <<= 1) {
	if ((unsigned)state & mask) {
	    if (sep) {
		rb_str_cat(buf, "|", 1);
	    }
	    sep = 1;
	    rb_str_cat_cstr(buf, lex_state_names[i]);
	}
    }
    if (!sep) {
	rb_str_cat(buf, none, sizeof(none)-1);
    }
    return buf;
}

static enum lex_state_e
trace_lex_state(enum lex_state_e from, enum lex_state_e to, int line)
{
    VALUE mesg;
    mesg = rb_str_new_cstr("lex_state: ");
    append_lex_state_name(from, mesg);
    rb_str_cat_cstr(mesg, " -> ");
    append_lex_state_name(to, mesg);
    rb_str_catf(mesg, " at line %d\n", line);
    rb_io_write(rb_stdout, mesg);
    return to;
}

#ifdef RIPPER
static VALUE
assignable_gen(struct parser_params *parser, VALUE lhs)
#else
static NODE*
assignable_gen(struct parser_params *parser, ID id, NODE *val)
#endif
{
#ifdef RIPPER
    ID id = get_id(lhs);
# define assignable_result(x) get_value(lhs)
# define parser_yyerror(parser, x) (dispatch1(assign_error, lhs), ripper_error())
#else
# define assignable_result(x) (x)
#endif
    if (!id) return assignable_result(0);
    switch (id) {
      case keyword_self:
	yyerror("Can't change the value of self");
	goto error;
      case keyword_nil:
	yyerror("Can't assign to nil");
	goto error;
      case keyword_true:
	yyerror("Can't assign to true");
	goto error;
      case keyword_false:
	yyerror("Can't assign to false");
	goto error;
      case keyword__FILE__:
	yyerror("Can't assign to __FILE__");
	goto error;
      case keyword__LINE__:
	yyerror("Can't assign to __LINE__");
	goto error;
      case keyword__ENCODING__:
	yyerror("Can't assign to __ENCODING__");
	goto error;
    }
    switch (id_type(id)) {
      case ID_LOCAL:
	if (dyna_in_block()) {
	    if (dvar_curr(id)) {
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	    else if (dvar_defined(id)) {
		return assignable_result(NEW_DASGN(id, val));
	    }
	    else if (local_id(id)) {
		return assignable_result(NEW_LASGN(id, val));
	    }
	    else {
		dyna_var(id);
		return assignable_result(NEW_DASGN_CURR(id, val));
	    }
	}
	else {
	    if (!local_id(id)) {
		local_var(id);
	    }
	    return assignable_result(NEW_LASGN(id, val));
	}
	break;
      case ID_GLOBAL:
	return assignable_result(NEW_GASGN(id, val));
      case ID_INSTANCE:
	return assignable_result(NEW_IASGN(id, val));
      case ID_CONST:
	if (!in_def && !in_single)
	    return assignable_result(NEW_CDECL(id, val, 0));
	yyerror("dynamic constant assignment");
	break;
      case ID_CLASS:
	return assignable_result(NEW_CVASGN(id, val));
      default:
	compile_error(PARSER_ARG "identifier %"PRIsVALUE" is not valid to set", rb_id2str(id));
    }
  error:
    return assignable_result(0);
#undef assignable_result
#undef parser_yyerror
}

static int
is_private_local_id(ID name)
{
    VALUE s;
    if (name == idUScore) return 1;
    if (!is_local_id(name)) return 0;
    s = rb_id2str(name);
    if (!s) return 0;
    return RSTRING_PTR(s)[0] == '_';
}

#define LVAR_USED ((ID)1 << (sizeof(ID) * CHAR_BIT - 1))

static int
shadowing_lvar_0(struct parser_params *parser, ID name)
{
    if (is_private_local_id(name)) return 1;
    if (dyna_in_block()) {
	if (dvar_curr(name)) {
	    yyerror("duplicated argument name");
	}
	else if (dvar_defined_get(name) || local_id(name)) {
	    rb_warning1("shadowing outer local variable - %"PRIsWARN, rb_id2str(name));
	    vtable_add(lvtbl->vars, name);
	    if (lvtbl->used) {
		vtable_add(lvtbl->used, (ID)ruby_sourceline | LVAR_USED);
	    }
	    return 0;
	}
    }
    else {
	if (local_id(name)) {
	    yyerror("duplicated argument name");
	}
    }
    return 1;
}

static ID
shadowing_lvar_gen(struct parser_params *parser, ID name)
{
    shadowing_lvar_0(parser, name);
    return name;
}

static void
new_bv_gen(struct parser_params *parser, ID name)
{
    if (!name) return;
    if (!is_local_id(name)) {
	compile_error(PARSER_ARG "invalid local variable - %"PRIsVALUE,
		      rb_id2str(name));
	return;
    }
    if (!shadowing_lvar_0(parser, name)) return;
    dyna_var(name);
}

#ifndef RIPPER
static NODE *
aryset_gen(struct parser_params *parser, NODE *recv, NODE *idx)
{
    return NEW_ATTRASGN(recv, tASET, idx);
}

static void
block_dup_check_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (node2 && node1 && nd_type(node1) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "both block arg and actual block given");
    }
}

static NODE *
attrset_gen(struct parser_params *parser, NODE *recv, ID atype, ID id)
{
    if (!CALL_Q_P(atype)) id = rb_id_attrset(id);
    return NEW_ATTRASGN(recv, id, 0);
}

static void
rb_backref_error_gen(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_NTH_REF:
	compile_error(PARSER_ARG "Can't set variable $%ld", node->nd_nth);
	break;
      case NODE_BACK_REF:
	compile_error(PARSER_ARG "Can't set variable $%c", (int)node->nd_nth);
	break;
    }
}

static NODE *
arg_concat_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node2) return node1;
    switch (nd_type(node1)) {
      case NODE_BLOCK_PASS:
	if (node1->nd_head)
	    node1->nd_head = arg_concat(node1->nd_head, node2);
	else
	    node1->nd_head = NEW_LIST(node2);
	return node1;
      case NODE_ARGSPUSH:
	if (nd_type(node2) != NODE_ARRAY) break;
	node1->nd_body = list_concat(NEW_LIST(node1->nd_body), node2);
	nd_set_type(node1, NODE_ARGSCAT);
	return node1;
      case NODE_ARGSCAT:
	if (nd_type(node2) != NODE_ARRAY ||
	    nd_type(node1->nd_body) != NODE_ARRAY) break;
	node1->nd_body = list_concat(node1->nd_body, node2);
	return node1;
    }
    return NEW_ARGSCAT(node1, node2);
}

static NODE *
arg_append_gen(struct parser_params *parser, NODE *node1, NODE *node2)
{
    if (!node1) return NEW_LIST(node2);
    switch (nd_type(node1))  {
      case NODE_ARRAY:
	return list_append(node1, node2);
      case NODE_BLOCK_PASS:
	node1->nd_head = arg_append(node1->nd_head, node2);
	return node1;
      case NODE_ARGSPUSH:
	node1->nd_body = list_append(NEW_LIST(node1->nd_body), node2);
	nd_set_type(node1, NODE_ARGSCAT);
	return node1;
    }
    return NEW_ARGSPUSH(node1, node2);
}

static NODE *
splat_array(NODE* node)
{
    if (nd_type(node) == NODE_SPLAT) node = node->nd_head;
    if (nd_type(node) == NODE_ARRAY) return node;
    return 0;
}

static NODE *
node_assign_gen(struct parser_params *parser, NODE *lhs, NODE *rhs)
{
    if (!lhs) return 0;

    switch (nd_type(lhs)) {
      case NODE_GASGN:
      case NODE_IASGN:
      case NODE_IASGN2:
      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_MASGN:
      case NODE_CDECL:
      case NODE_CVASGN:
	lhs->nd_value = rhs;
	break;

      case NODE_ATTRASGN:
      case NODE_CALL:
	lhs->nd_args = arg_append(lhs->nd_args, rhs);
	break;

      default:
	/* should not happen */
	break;
    }

    return lhs;
}

static int
value_expr_gen(struct parser_params *parser, NODE *node)
{
    int cond = 0;

    if (!node) {
	rb_warning0("empty expression");
    }
    while (node) {
	switch (nd_type(node)) {
	  case NODE_RETURN:
	  case NODE_BREAK:
	  case NODE_NEXT:
	  case NODE_REDO:
	  case NODE_RETRY:
	    if (!cond) yyerror("void value expression");
	    /* or "control never reach"? */
	    return FALSE;

	  case NODE_BLOCK:
	    while (node->nd_next) {
		node = node->nd_next;
	    }
	    node = node->nd_head;
	    break;

	  case NODE_BEGIN:
	    node = node->nd_body;
	    break;

	  case NODE_IF:
	    if (!node->nd_body) {
		node = node->nd_else;
		break;
	    }
	    else if (!node->nd_else) {
		node = node->nd_body;
		break;
	    }
	    if (!value_expr(node->nd_body)) return FALSE;
	    node = node->nd_else;
	    break;

	  case NODE_AND:
	  case NODE_OR:
	    cond = 1;
	    node = node->nd_2nd;
	    break;

	  default:
	    return TRUE;
	}
    }

    return TRUE;
}

static void
void_expr_gen(struct parser_params *parser, NODE *node)
{
    const char *useless = 0;

    if (!RTEST(ruby_verbose)) return;

    if (!node) return;
    switch (nd_type(node)) {
      case NODE_CALL:
	switch (node->nd_mid) {
	  case '+':
	  case '-':
	  case '*':
	  case '/':
	  case '%':
	  case tPOW:
	  case tUPLUS:
	  case tUMINUS:
	  case '|':
	  case '^':
	  case '&':
	  case tCMP:
	  case '>':
	  case tGEQ:
	  case '<':
	  case tLEQ:
	  case tEQ:
	  case tNEQ:
	    useless = rb_id2name(node->nd_mid);
	    break;
	}
	break;

      case NODE_LVAR:
      case NODE_DVAR:
      case NODE_GVAR:
      case NODE_IVAR:
      case NODE_CVAR:
      case NODE_NTH_REF:
      case NODE_BACK_REF:
	useless = "a variable";
	break;
      case NODE_CONST:
	useless = "a constant";
	break;
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	useless = "a literal";
	break;
      case NODE_COLON2:
      case NODE_COLON3:
	useless = "::";
	break;
      case NODE_DOT2:
	useless = "..";
	break;
      case NODE_DOT3:
	useless = "...";
	break;
      case NODE_SELF:
	useless = "self";
	break;
      case NODE_NIL:
	useless = "nil";
	break;
      case NODE_TRUE:
	useless = "true";
	break;
      case NODE_FALSE:
	useless = "false";
	break;
      case NODE_DEFINED:
	useless = "defined?";
	break;
    }

    if (useless) {
	rb_warn1L(nd_line(node), "possibly useless use of %s in void context", WARN_S(useless));
    }
}

static void
void_stmts_gen(struct parser_params *parser, NODE *node)
{
    if (!RTEST(ruby_verbose)) return;
    if (!node) return;
    if (nd_type(node) != NODE_BLOCK) return;

    for (;;) {
	if (!node->nd_next) return;
	void_expr0(node->nd_head);
	node = node->nd_next;
    }
}

static NODE *
remove_begin(NODE *node)
{
    NODE **n = &node, *n1 = node;
    while (n1 && nd_type(n1) == NODE_BEGIN && n1->nd_body) {
	*n = n1 = n1->nd_body;
    }
    return node;
}

static NODE *
remove_begin_all(NODE *node)
{
    NODE **n = &node, *n1 = node;
    while (n1 && nd_type(n1) == NODE_BEGIN) {
	*n = n1 = n1->nd_body;
    }
    return node;
}

static void
reduce_nodes_gen(struct parser_params *parser, NODE **body)
{
    NODE *node = *body;

    if (!node) {
	*body = NEW_NIL();
	return;
    }
#define subnodes(n1, n2) \
    ((!node->n1) ? (node->n2 ? (body = &node->n2, 1) : 0) : \
     (!node->n2) ? (body = &node->n1, 1) : \
     (reduce_nodes(&node->n1), body = &node->n2, 1))

    while (node) {
	int newline = (int)(node->flags & NODE_FL_NEWLINE);
	switch (nd_type(node)) {
	  end:
	  case NODE_NIL:
	    *body = 0;
	    return;
	  case NODE_RETURN:
	    *body = node = node->nd_stts;
	    if (newline && node) node->flags |= NODE_FL_NEWLINE;
	    continue;
	  case NODE_BEGIN:
	    *body = node = node->nd_body;
	    if (newline && node) node->flags |= NODE_FL_NEWLINE;
	    continue;
	  case NODE_BLOCK:
	    body = &node->nd_end->nd_head;
	    break;
	  case NODE_IF:
	    if (subnodes(nd_body, nd_else)) break;
	    return;
	  case NODE_CASE:
	    body = &node->nd_body;
	    break;
	  case NODE_WHEN:
	    if (!subnodes(nd_body, nd_next)) goto end;
	    break;
	  case NODE_ENSURE:
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  case NODE_RESCUE:
	    if (node->nd_else) {
		body = &node->nd_resq;
		break;
	    }
	    if (!subnodes(nd_head, nd_resq)) goto end;
	    break;
	  default:
	    return;
	}
	node = *body;
	if (newline && node) node->flags |= NODE_FL_NEWLINE;
    }

#undef subnodes
}

static int
is_static_content(NODE *node)
{
    if (!node) return 1;
    switch (nd_type(node)) {
      case NODE_HASH:
	if (!(node = node->nd_head)) break;
      case NODE_ARRAY:
	do {
	    if (!is_static_content(node->nd_head)) return 0;
	} while ((node = node->nd_next) != 0);
      case NODE_LIT:
      case NODE_STR:
      case NODE_NIL:
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_ZARRAY:
	break;
      default:
	return 0;
    }
    return 1;
}

static int
assign_in_cond(struct parser_params *parser, NODE *node)
{
    switch (nd_type(node)) {
      case NODE_MASGN:
	yyerror("multiple assignment in conditional");
	return 1;

      case NODE_LASGN:
      case NODE_DASGN:
      case NODE_DASGN_CURR:
      case NODE_GASGN:
      case NODE_IASGN:
	break;

      default:
	return 0;
    }

    if (!node->nd_value) return 1;
    if (is_static_content(node->nd_value)) {
	/* reports always */
	parser_warn(node->nd_value, "found = in conditional, should be ==");
    }
    return 1;
}

static void
warn_unless_e_option(struct parser_params *parser, NODE *node, const char *str)
{
    if (!e_option_supplied(parser)) parser_warn(node, str);
}

static void
warning_unless_e_option(struct parser_params *parser, NODE *node, const char *str)
{
    if (!e_option_supplied(parser)) parser_warning(node, str);
}

static void
fixup_nodes(NODE **rootnode)
{
    NODE *node, *next, *head;

    for (node = *rootnode; node; node = next) {
	enum node_type type;
	VALUE val;

	next = node->nd_next;
	head = node->nd_head;
	rb_gc_force_recycle((VALUE)node);
	*rootnode = next;
	switch (type = nd_type(head)) {
	  case NODE_DOT2:
	  case NODE_DOT3:
	    val = rb_range_new(head->nd_beg->nd_lit, head->nd_end->nd_lit,
			       type == NODE_DOT3);
	    rb_gc_force_recycle((VALUE)head->nd_beg);
	    rb_gc_force_recycle((VALUE)head->nd_end);
	    nd_set_type(head, NODE_LIT);
	    head->nd_lit = val;
	    break;
	  default:
	    break;
	}
    }
}

static NODE *cond0(struct parser_params*,NODE*);

static NODE*
range_op(struct parser_params *parser, NODE *node)
{
    enum node_type type;

    if (node == 0) return 0;

    type = nd_type(node);
    value_expr(node);
    if (type == NODE_LIT && FIXNUM_P(node->nd_lit)) {
	warn_unless_e_option(parser, node, "integer literal in conditional range");
	return NEW_CALL(node, tEQ, NEW_LIST(NEW_GVAR(rb_intern("$."))));
    }
    return cond0(parser, node);
}

static int
literal_node(NODE *node)
{
    if (!node) return 1;	/* same as NODE_NIL */
    switch (nd_type(node)) {
      case NODE_LIT:
      case NODE_STR:
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_DREGX:
      case NODE_DREGX_ONCE:
      case NODE_DSYM:
	return 2;
      case NODE_TRUE:
      case NODE_FALSE:
      case NODE_NIL:
	return 1;
    }
    return 0;
}

static NODE*
cond0(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    assign_in_cond(parser, node);

    switch (nd_type(node)) {
      case NODE_DSTR:
      case NODE_EVSTR:
      case NODE_STR:
	rb_warn0("string literal in condition");
	break;

      case NODE_DREGX:
      case NODE_DREGX_ONCE:
	warning_unless_e_option(parser, node, "regex literal in condition");
	return NEW_MATCH2(node, NEW_GVAR(rb_intern("$_")));

      case NODE_AND:
      case NODE_OR:
	node->nd_1st = cond0(parser, node->nd_1st);
	node->nd_2nd = cond0(parser, node->nd_2nd);
	break;

      case NODE_DOT2:
      case NODE_DOT3:
	node->nd_beg = range_op(parser, node->nd_beg);
	node->nd_end = range_op(parser, node->nd_end);
	if (nd_type(node) == NODE_DOT2) nd_set_type(node,NODE_FLIP2);
	else if (nd_type(node) == NODE_DOT3) nd_set_type(node, NODE_FLIP3);
	if (!e_option_supplied(parser)) {
	    int b = literal_node(node->nd_beg);
	    int e = literal_node(node->nd_end);
	    if ((b == 1 && e == 1) || (b + e >= 2 && RTEST(ruby_verbose))) {
		parser_warn(node, "range literal in condition");
	    }
	}
	break;

      case NODE_DSYM:
	parser_warning(node, "literal in condition");
	break;

      case NODE_LIT:
	if (RB_TYPE_P(node->nd_lit, T_REGEXP)) {
	    warn_unless_e_option(parser, node, "regex literal in condition");
	    nd_set_type(node, NODE_MATCH);
	}
	else {
	    parser_warning(node, "literal in condition");
	}
      default:
	break;
    }
    return node;
}

static NODE*
cond_gen(struct parser_params *parser, NODE *node)
{
    if (node == 0) return 0;
    return cond0(parser, node);
}

static NODE*
new_if_gen(struct parser_params *parser, NODE *cc, NODE *left, NODE *right)
{
    if (!cc) return right;
    cc = cond0(parser, cc);
    return newline_node(NEW_IF(cc, left, right));
}

static NODE*
logop_gen(struct parser_params *parser, enum node_type type, NODE *left, NODE *right)
{
    value_expr(left);
    if (left && (enum node_type)nd_type(left) == type) {
	NODE *node = left, *second;
	while ((second = node->nd_2nd) != 0 && (enum node_type)nd_type(second) == type) {
	    node = second;
	}
	node->nd_2nd = NEW_NODE(type, second, right, 0);
	return left;
    }
    return NEW_NODE(type, left, right, 0);
}

static void
no_blockarg(struct parser_params *parser, NODE *node)
{
    if (node && nd_type(node) == NODE_BLOCK_PASS) {
	compile_error(PARSER_ARG "block argument should not be given");
    }
}

static NODE *
ret_args_gen(struct parser_params *parser, NODE *node)
{
    if (node) {
	no_blockarg(parser, node);
	if (nd_type(node) == NODE_ARRAY) {
	    if (node->nd_next == 0) {
		node = node->nd_head;
	    }
	    else {
		nd_set_type(node, NODE_VALUES);
	    }
	}
    }
    return node;
}

static NODE *
new_yield_gen(struct parser_params *parser, NODE *node)
{
    if (node) no_blockarg(parser, node);

    return NEW_YIELD(node);
}

static VALUE
negate_lit(VALUE lit)
{
    int type = TYPE(lit);
    switch (type) {
      case T_FIXNUM:
	lit = LONG2FIX(-FIX2LONG(lit));
	break;
      case T_BIGNUM:
      case T_RATIONAL:
      case T_COMPLEX:
	lit = rb_funcallv(lit, tUMINUS, 0, 0);
	break;
      case T_FLOAT:
#if USE_FLONUM
	if (FLONUM_P(lit)) {
	    lit = DBL2NUM(-RFLOAT_VALUE(lit));
	    break;
	}
#endif
	RFLOAT(lit)->float_value = -RFLOAT_VALUE(lit);
	break;
      default:
	rb_bug("unknown literal type (%d) passed to negate_lit", type);
	break;
    }
    return lit;
}

static NODE *
arg_blk_pass(NODE *node1, NODE *node2)
{
    if (node2) {
	node2->nd_head = node1;
	return node2;
    }
    return node1;
}


static NODE*
new_args_gen(struct parser_params *parser, NODE *m, NODE *o, ID r, NODE *p, NODE *tail)
{
    int saved_line = ruby_sourceline;
    struct rb_args_info *args = tail->nd_ainfo;

    args->pre_args_num   = m ? rb_long2int(m->nd_plen) : 0;
    args->pre_init       = m ? m->nd_next : 0;

    args->post_args_num  = p ? rb_long2int(p->nd_plen) : 0;
    args->post_init      = p ? p->nd_next : 0;
    args->first_post_arg = p ? p->nd_pid : 0;

    args->rest_arg       = r;

    args->opt_args       = o;

    ruby_sourceline = saved_line;

    return tail;
}

static NODE*
new_args_tail_gen(struct parser_params *parser, NODE *k, ID kr, ID b)
{
    int saved_line = ruby_sourceline;
    struct rb_args_info *args;
    NODE *node;

    args = ZALLOC(struct rb_args_info);
    node = NEW_NODE(NODE_ARGS, 0, 0, args);

    args->block_arg      = b;
    args->kw_args        = k;

    if (k) {
	/*
	 * def foo(k1: 1, kr1:, k2: 2, **krest, &b)
	 * variable order: k1, kr1, k2, &b, internal_id, krest
	 * #=> <reorder>
	 * variable order: kr1, k1, k2, internal_id, krest, &b
	 */
	ID kw_bits;
	NODE *kwn = k;
	struct vtable *required_kw_vars = vtable_alloc(NULL);
	struct vtable *kw_vars = vtable_alloc(NULL);
	int i;

	while (kwn) {
	    NODE *val_node = kwn->nd_body->nd_value;
	    ID vid = kwn->nd_body->nd_vid;

	    if (val_node == (NODE *)-1) {
		vtable_add(required_kw_vars, vid);
	    }
	    else {
		vtable_add(kw_vars, vid);
	    }

	    kwn = kwn->nd_next;
	}

	kw_bits = internal_id();
	if (kr && is_junk_id(kr)) vtable_pop(lvtbl->args, 1);
	vtable_pop(lvtbl->args, vtable_size(required_kw_vars) + vtable_size(kw_vars) + (b != 0));

	for (i=0; i<vtable_size(required_kw_vars); i++) arg_var(required_kw_vars->tbl[i]);
	for (i=0; i<vtable_size(kw_vars); i++) arg_var(kw_vars->tbl[i]);
	vtable_free(required_kw_vars);
	vtable_free(kw_vars);

	arg_var(kw_bits);
	if (kr) arg_var(kr);
	if (b) arg_var(b);

	args->kw_rest_arg = NEW_DVAR(kw_bits);
	args->kw_rest_arg->nd_cflag = kr;
    }
    else if (kr) {
	if (b) vtable_pop(lvtbl->args, 1); /* reorder */
	arg_var(kr);
	if (b) arg_var(b);
	args->kw_rest_arg = NEW_DVAR(kr);
    }

    ruby_sourceline = saved_line;
    return node;
}

static NODE*
dsym_node_gen(struct parser_params *parser, NODE *node)
{
    VALUE lit;

    if (!node) {
	return NEW_LIT(ID2SYM(idNULL));
    }

    switch (nd_type(node)) {
      case NODE_DSTR:
	nd_set_type(node, NODE_DSYM);
	break;
      case NODE_STR:
	lit = node->nd_lit;
	node->nd_lit = ID2SYM(rb_intern_str(lit));
	nd_set_type(node, NODE_LIT);
	break;
      default:
	node = NEW_NODE(NODE_DSYM, Qnil, 1, NEW_LIST(node));
	break;
    }
    return node;
}

static int
append_literal_keys(st_data_t k, st_data_t v, st_data_t h)
{
    NODE *node = (NODE *)v;
    NODE **result = (NODE **)h;
    node->nd_alen = 2;
    node->nd_next->nd_end = node->nd_next;
    node->nd_next->nd_next = 0;
    if (*result)
	list_concat(*result, node);
    else
	*result = node;
    return ST_CONTINUE;
}

static NODE *
remove_duplicate_keys(struct parser_params *parser, NODE *hash)
{
    st_table *literal_keys = st_init_numtable_with_size(hash->nd_alen / 2);
    NODE *result = 0;
    while (hash && hash->nd_head && hash->nd_next) {
	NODE *head = hash->nd_head;
	NODE *value = hash->nd_next;
	NODE *next = value->nd_next;
	VALUE key = (VALUE)head;
	st_data_t data;
	if (nd_type(head) == NODE_LIT &&
	    st_lookup(literal_keys, (key = head->nd_lit), &data)) {
	    rb_compile_warn(ruby_sourcefile, nd_line((NODE *)data),
			    "key %+"PRIsVALUE" is duplicated and overwritten on line %d",
			    head->nd_lit, nd_line(head));
	    head = ((NODE *)data)->nd_next;
	    head->nd_head = block_append(head->nd_head, value->nd_head);
	}
	else {
	    st_insert(literal_keys, (st_data_t)key, (st_data_t)hash);
	}
	hash = next;
    }
    st_foreach(literal_keys, append_literal_keys, (st_data_t)&result);
    st_free_table(literal_keys);
    if (hash) {
	if (!result) result = hash;
	else list_concat(result, hash);
    }
    return result;
}

static NODE *
new_hash_gen(struct parser_params *parser, NODE *hash)
{
    if (hash) hash = remove_duplicate_keys(parser, hash);
    return NEW_HASH(hash);
}
#endif /* !RIPPER */

#ifndef RIPPER
static NODE *
new_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs)
{
    NODE *asgn;

    if (lhs) {
	ID vid = lhs->nd_vid;
	if (op == tOROP) {
	    lhs->nd_value = rhs;
	    asgn = NEW_OP_ASGN_OR(gettable(vid), lhs);
	    if (is_notop_id(vid)) {
		switch (id_type(vid)) {
		  case ID_GLOBAL:
		  case ID_INSTANCE:
		  case ID_CLASS:
		    asgn->nd_aid = vid;
		}
	    }
	}
	else if (op == tANDOP) {
	    lhs->nd_value = rhs;
	    asgn = NEW_OP_ASGN_AND(gettable(vid), lhs);
	}
	else {
	    asgn = lhs;
	    asgn->nd_value = NEW_CALL(gettable(vid), op, NEW_LIST(rhs));
	}
    }
    else {
	asgn = NEW_BEGIN(0);
    }
    return asgn;
}

static NODE *
new_attr_op_assign_gen(struct parser_params *parser, NODE *lhs,
		       ID atype, ID attr, ID op, NODE *rhs)
{
    NODE *asgn;

    if (op == tOROP) {
	op = 0;
    }
    else if (op == tANDOP) {
	op = 1;
    }
    asgn = NEW_OP_ASGN2(lhs, CALL_Q_P(atype), attr, op, rhs);
    fixpos(asgn, lhs);
    return asgn;
}

static NODE *
new_const_op_assign_gen(struct parser_params *parser, NODE *lhs, ID op, NODE *rhs)
{
    NODE *asgn;

    if (op == tOROP) {
	op = 0;
    }
    else if (op == tANDOP) {
	op = 1;
    }
    if (lhs) {
	asgn = NEW_OP_CDECL(lhs, op, rhs);
    }
    else {
	asgn = NEW_BEGIN(0);
    }
    fixpos(asgn, lhs);
    return asgn;
}
#else
static VALUE
new_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE op, VALUE rhs)
{
    return dispatch3(opassign, lhs, op, rhs);
}

static VALUE
new_attr_op_assign_gen(struct parser_params *parser, VALUE lhs, VALUE type, VALUE attr, VALUE op, VALUE rhs)
{
    VALUE recv = dispatch3(field, lhs, type, attr);
    return dispatch3(opassign, recv, op, rhs);
}
#endif

static void
warn_unused_var(struct parser_params *parser, struct local_vars *local)
{
    int i, cnt;
    ID *v, *u;

    if (!local->used) return;
    v = local->vars->tbl;
    u = local->used->tbl;
    cnt = local->used->pos;
    if (cnt != local->vars->pos) {
	rb_bug("local->used->pos != local->vars->pos");
    }
    for (i = 0; i < cnt; ++i) {
	if (!v[i] || (u[i] & LVAR_USED)) continue;
	if (is_private_local_id(v[i])) continue;
	rb_warn1L((int)u[i], "assigned but unused variable - %"PRIsWARN, rb_id2str(v[i]));
    }
}

static void
local_push_gen(struct parser_params *parser, int inherit_dvars)
{
    struct local_vars *local;

    local = ALLOC(struct local_vars);
    local->prev = lvtbl;
    local->args = vtable_alloc(0);
    local->vars = vtable_alloc(inherit_dvars ? DVARS_INHERIT : DVARS_TOPSCOPE);
    local->used = !(inherit_dvars &&
		    (ifndef_ripper(compile_for_eval || e_option_supplied(parser))+0)) &&
	RTEST(ruby_verbose) ? vtable_alloc(0) : 0;
# if WARN_PAST_SCOPE
    local->past = 0;
# endif
    local->cmdargs = cmdarg_stack;
    cmdarg_stack = 0;
    lvtbl = local;
}

static void
local_pop_gen(struct parser_params *parser)
{
    struct local_vars *local = lvtbl->prev;
    if (lvtbl->used) {
	warn_unused_var(parser, lvtbl);
	vtable_free(lvtbl->used);
    }
# if WARN_PAST_SCOPE
    while (lvtbl->past) {
	struct vtable *past = lvtbl->past;
	lvtbl->past = past->prev;
	vtable_free(past);
    }
# endif
    vtable_free(lvtbl->args);
    vtable_free(lvtbl->vars);
    cmdarg_stack = lvtbl->cmdargs;
    xfree(lvtbl);
    lvtbl = local;
}

#ifndef RIPPER
static ID*
local_tbl_gen(struct parser_params *parser)
{
    int cnt_args = vtable_size(lvtbl->args);
    int cnt_vars = vtable_size(lvtbl->vars);
    int cnt = cnt_args + cnt_vars;
    int i, j;
    ID *buf;

    if (cnt <= 0) return 0;
    buf = ALLOC_N(ID, cnt + 1);
    MEMCPY(buf+1, lvtbl->args->tbl, ID, cnt_args);
    /* remove IDs duplicated to warn shadowing */
    for (i = 0, j = cnt_args+1; i < cnt_vars; ++i) {
	ID id = lvtbl->vars->tbl[i];
	if (!vtable_included(lvtbl->args, id)) {
	    buf[j++] = id;
	}
    }
    if (--j < cnt) REALLOC_N(buf, ID, (cnt = j) + 1);
    buf[0] = cnt;
    return buf;
}
#endif

static void
arg_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->args, id);
}

static void
local_var_gen(struct parser_params *parser, ID id)
{
    vtable_add(lvtbl->vars, id);
    if (lvtbl->used) {
	vtable_add(lvtbl->used, (ID)ruby_sourceline);
    }
}

static int
local_id_gen(struct parser_params *parser, ID id)
{
    struct vtable *vars, *args, *used;

    vars = lvtbl->vars;
    args = lvtbl->args;
    used = lvtbl->used;

    while (vars && POINTER_P(vars->prev)) {
	vars = vars->prev;
	args = args->prev;
	if (used) used = used->prev;
    }

    if (vars && vars->prev == DVARS_INHERIT) {
	return rb_local_defined(id);
    }
    else if (vtable_included(args, id)) {
	return 1;
    }
    else {
	int i = vtable_included(vars, id);
	if (i && used) used->tbl[i-1] |= LVAR_USED;
	return i != 0;
    }
}

static const struct vtable *
dyna_push_gen(struct parser_params *parser)
{
    lvtbl->args = vtable_alloc(lvtbl->args);
    lvtbl->vars = vtable_alloc(lvtbl->vars);
    if (lvtbl->used) {
	lvtbl->used = vtable_alloc(lvtbl->used);
    }
    return lvtbl->args;
}

static void
dyna_pop_vtable(struct parser_params *parser, struct vtable **vtblp)
{
    struct vtable *tmp = *vtblp;
    *vtblp = tmp->prev;
# if WARN_PAST_SCOPE
    if (parser->past_scope_enabled) {
	tmp->prev = lvtbl->past;
	lvtbl->past = tmp;
	return;
    }
# endif
    vtable_free(tmp);
}

static void
dyna_pop_1(struct parser_params *parser)
{
    struct vtable *tmp;

    if ((tmp = lvtbl->used) != 0) {
	warn_unused_var(parser, lvtbl);
	lvtbl->used = lvtbl->used->prev;
	vtable_free(tmp);
    }
    dyna_pop_vtable(parser, &lvtbl->args);
    dyna_pop_vtable(parser, &lvtbl->vars);
}

static void
dyna_pop_gen(struct parser_params *parser, const struct vtable *lvargs)
{
    while (lvtbl->args != lvargs) {
	dyna_pop_1(parser);
	if (!lvtbl->args) {
	    struct local_vars *local = lvtbl->prev;
	    xfree(lvtbl);
	    lvtbl = local;
	}
    }
    dyna_pop_1(parser);
}

static int
dyna_in_block_gen(struct parser_params *parser)
{
    return POINTER_P(lvtbl->vars) && lvtbl->vars->prev != DVARS_TOPSCOPE;
}

static int
dvar_defined_gen(struct parser_params *parser, ID id, int get)
{
    struct vtable *vars, *args, *used;
    int i;

    args = lvtbl->args;
    vars = lvtbl->vars;
    used = lvtbl->used;

    while (POINTER_P(vars)) {
	if (vtable_included(args, id)) {
	    return 1;
	}
	if ((i = vtable_included(vars, id)) != 0) {
	    if (used) used->tbl[i-1] |= LVAR_USED;
	    return 1;
	}
	args = args->prev;
	vars = vars->prev;
	if (get) used = 0;
	if (used) used = used->prev;
    }

    if (vars == DVARS_INHERIT) {
        return rb_dvar_defined(id);
    }

    return 0;
}

static int
dvar_curr_gen(struct parser_params *parser, ID id)
{
    return (vtable_included(lvtbl->args, id) ||
	    vtable_included(lvtbl->vars, id));
}

#ifndef RIPPER
static void
reg_fragment_setenc_gen(struct parser_params* parser, VALUE str, int options)
{
    int c = RE_OPTION_ENCODING_IDX(options);

    if (c) {
	int opt, idx;
	rb_char_to_option_kcode(c, &opt, &idx);
	if (idx != ENCODING_GET(str) &&
	    rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
            goto error;
	}
	ENCODING_SET(str, idx);
    }
    else if (RE_OPTION_ENCODING_NONE(options)) {
        if (!ENCODING_IS_ASCII8BIT(str) &&
            rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
            c = 'n';
            goto error;
        }
	rb_enc_associate(str, rb_ascii8bit_encoding());
    }
    else if (current_enc == rb_usascii_encoding()) {
	if (rb_enc_str_coderange(str) != ENC_CODERANGE_7BIT) {
	    /* raise in re.c */
	    rb_enc_associate(str, rb_usascii_encoding());
	}
	else {
	    rb_enc_associate(str, rb_ascii8bit_encoding());
	}
    }
    return;

  error:
    compile_error(PARSER_ARG
        "regexp encoding option '%c' differs from source encoding '%s'",
        c, rb_enc_name(rb_enc_get(str)));
}

static int
reg_fragment_check_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE err;
    reg_fragment_setenc(str, options);
    err = rb_reg_check_preprocess(str);
    if (err != Qnil) {
        err = rb_obj_as_string(err);
        compile_error(PARSER_ARG "%"PRIsVALUE, err);
	return 0;
    }
    return 1;
}

typedef struct {
    struct parser_params* parser;
    rb_encoding *enc;
    NODE *succ_block;
    NODE *fail_block;
    int num;
} reg_named_capture_assign_t;

static int
reg_named_capture_assign_iter(const OnigUChar *name, const OnigUChar *name_end,
          int back_num, int *back_refs, OnigRegex regex, void *arg0)
{
    reg_named_capture_assign_t *arg = (reg_named_capture_assign_t*)arg0;
    struct parser_params* parser = arg->parser;
    rb_encoding *enc = arg->enc;
    long len = name_end - name;
    const char *s = (const char *)name;
    ID var;

    arg->num++;

    if (arg->succ_block == 0) {
        arg->succ_block = NEW_BEGIN(0);
        arg->fail_block = NEW_BEGIN(0);
    }

    if (!len || (*name != '_' && ISASCII(*name) && !rb_enc_islower(*name, enc)) ||
	(len < MAX_WORD_LENGTH && rb_reserved_word(s, (int)len)) ||
	!rb_enc_symname2_p(s, len, enc)) {
        return ST_CONTINUE;
    }
    var = intern_cstr(s, len, enc);
    if (dvar_defined(var) || local_id(var)) {
        rb_warning1("named capture conflicts a local variable - %"PRIsWARN,
                    rb_id2str(var));
    }
    arg->succ_block = block_append(arg->succ_block,
        newline_node(node_assign(assignable(var,0),
            NEW_CALL(
              gettable(rb_intern("$~")),
              idAREF,
              NEW_LIST(NEW_LIT(ID2SYM(var))))
            )));
    arg->fail_block = block_append(arg->fail_block,
        newline_node(node_assign(assignable(var,0), NEW_LIT(Qnil))));
    return ST_CONTINUE;
}

static NODE *
reg_named_capture_assign_gen(struct parser_params* parser, VALUE regexp, NODE *match)
{
    reg_named_capture_assign_t arg;

    arg.parser = parser;
    arg.enc = rb_enc_get(regexp);
    arg.succ_block = 0;
    arg.fail_block = 0;
    arg.num = 0;
    onig_foreach_name(RREGEXP(regexp)->ptr, reg_named_capture_assign_iter, &arg);

    if (arg.num == 0)
        return match;

    return
        block_append(
            newline_node(match),
            NEW_IF(gettable(rb_intern("$~")),
                block_append(
                    newline_node(arg.succ_block),
                    newline_node(
                        NEW_CALL(
                          gettable(rb_intern("$~")),
                          rb_intern("begin"),
                          NEW_LIST(NEW_LIT(INT2FIX(0)))))),
                block_append(
                    newline_node(arg.fail_block),
                    newline_node(
                        NEW_LIT(Qnil)))));
}

static VALUE
parser_reg_compile(struct parser_params* parser, VALUE str, int options)
{
    reg_fragment_setenc(str, options);
    return rb_reg_compile(str, options & RE_OPTION_MASK, ruby_sourcefile, ruby_sourceline);
}

static VALUE
reg_compile_gen(struct parser_params* parser, VALUE str, int options)
{
    VALUE re;
    VALUE err;

    err = rb_errinfo();
    re = parser_reg_compile(parser, str, options);
    if (NIL_P(re)) {
	VALUE m = rb_attr_get(rb_errinfo(), idMesg);
	rb_set_errinfo(err);
	if (!NIL_P(err)) {
	    rb_str_append(rb_str_cat(rb_attr_get(err, idMesg), "\n", 1), m);
	}
	else {
	    compile_error(PARSER_ARG "%"PRIsVALUE, m);
	}
	return Qnil;
    }
    return re;
}

VALUE
rb_parser_reg_compile(struct parser_params* parser, VALUE str, int options, VALUE *errmsg)
{
    VALUE err = rb_errinfo();
    VALUE re = parser_reg_compile(parser, str, options);
    if (NIL_P(re)) {
	*errmsg = rb_attr_get(rb_errinfo(), idMesg);
	rb_set_errinfo(err);
    }
    return re;
}

NODE*
rb_parser_append_print(VALUE vparser, NODE *node)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }

    node = block_append(node,
			NEW_FCALL(rb_intern("print"),
				  NEW_ARRAY(NEW_GVAR(rb_intern("$_")))));
    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

NODE *
rb_parser_while_loop(VALUE vparser, NODE *node, int chop, int split)
{
    NODE *prelude = 0;
    NODE *scope = node;
    struct parser_params *parser;

    if (!node) return node;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);

    node = node->nd_body;

    if (nd_type(node) == NODE_PRELUDE) {
	prelude = node;
	node = node->nd_body;
    }
    if (split) {
	node = block_append(NEW_GASGN(rb_intern("$F"),
				      NEW_CALL(NEW_GVAR(rb_intern("$_")),
					       rb_intern("split"), 0)),
			    node);
    }
    if (chop) {
	node = block_append(NEW_CALL(NEW_GVAR(rb_intern("$_")),
				     rb_intern("chop!"), 0), node);
    }

    node = NEW_OPT_N(node);

    if (prelude) {
	prelude->nd_body = node;
	scope->nd_body = prelude;
    }
    else {
	scope->nd_body = node;
    }

    return scope;
}

void
rb_init_parse(void)
{
    /* just to suppress unused-function warnings */
    (void)nodetype;
    (void)nodeline;
}
#endif /* !RIPPER */

static ID
internal_id_gen(struct parser_params *parser)
{
    ID id = (ID)vtable_size(lvtbl->args) + (ID)vtable_size(lvtbl->vars);
    id += ((tLAST_TOKEN - ID_INTERNAL) >> ID_SCOPE_SHIFT) + 1;
    return ID_STATIC_SYM | ID_INTERNAL | (id << ID_SCOPE_SHIFT);
}

static void
parser_initialize(struct parser_params *parser)
{
    /* note: we rely on TypedData_Make_Struct to set most fields to 0 */
    command_start = TRUE;
    ruby_sourcefile_string = Qnil;
#ifdef RIPPER
    parser->delayed = Qnil;
    parser->result = Qnil;
    parser->parsing_thread = Qnil;
#endif
    parser->debug_buffer = Qnil;
    parser->enc = rb_utf8_encoding();
}

#ifdef RIPPER
#define parser_mark ripper_parser_mark
#define parser_free ripper_parser_free
#endif

static void
parser_mark(void *ptr)
{
    struct parser_params *parser = (struct parser_params*)ptr;

    rb_gc_mark((VALUE)lex_strterm);
    rb_gc_mark((VALUE)deferred_nodes);
    rb_gc_mark(lex_input);
    rb_gc_mark(lex_lastline);
    rb_gc_mark(lex_nextline);
    rb_gc_mark(ruby_sourcefile_string);
#ifndef RIPPER
    rb_gc_mark((VALUE)ruby_eval_tree_begin);
    rb_gc_mark((VALUE)ruby_eval_tree);
    rb_gc_mark(ruby_debug_lines);
    rb_gc_mark(parser->compile_option);
#else
    rb_gc_mark(parser->delayed);
    rb_gc_mark(parser->value);
    rb_gc_mark(parser->result);
    rb_gc_mark(parser->parsing_thread);
#endif
    rb_gc_mark(parser->debug_buffer);
#ifdef YYMALLOC
    rb_gc_mark((VALUE)parser->heap);
#endif
}

static void
parser_free(void *ptr)
{
    struct parser_params *parser = (struct parser_params*)ptr;
    struct local_vars *local, *prev;

    if (tokenbuf) {
        xfree(tokenbuf);
    }
    for (local = lvtbl; local; local = prev) {
	if (local->vars) xfree(local->vars);
	prev = local->prev;
	xfree(local);
    }
    {
	token_info *ptinfo;
	while ((ptinfo = parser->token_info) != 0) {
	    parser->token_info = ptinfo->next;
	    xfree(ptinfo);
	}
    }
    xfree(ptr);
}

static size_t
parser_memsize(const void *ptr)
{
    struct parser_params *parser = (struct parser_params*)ptr;
    struct local_vars *local;
    size_t size = sizeof(*parser);

    size += toksiz;
    for (local = lvtbl; local; local = local->prev) {
	size += sizeof(*local);
	if (local->vars) size += local->vars->capa * sizeof(ID);
    }
    return size;
}

static const rb_data_type_t parser_data_type = {
#ifndef RIPPER
    "parser",
#else
    "ripper",
#endif
    {
	parser_mark,
	parser_free,
	parser_memsize,
    },
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

#ifndef RIPPER
#undef rb_reserved_word

const struct kwtable *
rb_reserved_word(const char *str, unsigned int len)
{
    return reserved_word(str, len);
}

VALUE
rb_parser_new(void)
{
    struct parser_params *p;
    VALUE parser = TypedData_Make_Struct(0, struct parser_params,
					 &parser_data_type, p);
    parser_initialize(p);
    return parser;
}
#endif

#ifdef RIPPER
#define rb_parser_end_seen_p ripper_parser_end_seen_p
#define rb_parser_encoding ripper_parser_encoding
#define rb_parser_get_yydebug ripper_parser_get_yydebug
#define rb_parser_set_yydebug ripper_parser_set_yydebug
static VALUE ripper_parser_end_seen_p(VALUE vparser);
static VALUE ripper_parser_encoding(VALUE vparser);
static VALUE ripper_parser_get_yydebug(VALUE self);
static VALUE ripper_parser_set_yydebug(VALUE self, VALUE flag);

/*
 *  call-seq:
 *    ripper#error?   -> Boolean
 *
 *  Return true if parsed source has errors.
 */
static VALUE
ripper_error_p(VALUE vparser)
{
    struct parser_params *parser;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    return parser->error_p ? Qtrue : Qfalse;
}
#endif

/*
 *  call-seq:
 *    ripper#end_seen?   -> Boolean
 *
 *  Return true if parsed source ended by +\_\_END\_\_+.
 */
VALUE
rb_parser_end_seen_p(VALUE vparser)
{
    struct parser_params *parser;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    return ruby__end__seen ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper#encoding   -> encoding
 *
 *  Return encoding of the source.
 */
VALUE
rb_parser_encoding(VALUE vparser)
{
    struct parser_params *parser;

    TypedData_Get_Struct(vparser, struct parser_params, &parser_data_type, parser);
    return rb_enc_from_encoding(current_enc);
}

/*
 *  call-seq:
 *    ripper.yydebug   -> true or false
 *
 *  Get yydebug.
 */
VALUE
rb_parser_get_yydebug(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    return yydebug ? Qtrue : Qfalse;
}

/*
 *  call-seq:
 *    ripper.yydebug = flag
 *
 *  Set yydebug.
 */
VALUE
rb_parser_set_yydebug(VALUE self, VALUE flag)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    yydebug = RTEST(flag);
    return flag;
}

#ifndef RIPPER
#ifdef YYMALLOC
#define HEAPCNT(n, size) ((n) * (size) / sizeof(YYSTYPE))
#define NEWHEAP() rb_node_newnode(NODE_ALLOCA, 0, (VALUE)parser->heap, 0)
#define ADD2HEAP(n, c, p) ((parser->heap = (n))->u1.node = (p), \
			   (n)->u3.cnt = (c), (p))

void *
rb_parser_malloc(struct parser_params *parser, size_t size)
{
    size_t cnt = HEAPCNT(1, size);
    NODE *n = NEWHEAP();
    void *ptr = xmalloc(size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_calloc(struct parser_params *parser, size_t nelem, size_t size)
{
    size_t cnt = HEAPCNT(nelem, size);
    NODE *n = NEWHEAP();
    void *ptr = xcalloc(nelem, size);

    return ADD2HEAP(n, cnt, ptr);
}

void *
rb_parser_realloc(struct parser_params *parser, void *ptr, size_t size)
{
    NODE *n;
    size_t cnt = HEAPCNT(1, size);

    if (ptr && (n = parser->heap) != NULL) {
	do {
	    if (n->u1.node == ptr) {
		n->u1.node = ptr = xrealloc(ptr, size);
		if (n->u3.cnt) n->u3.cnt = cnt;
		return ptr;
	    }
	} while ((n = n->u2.node) != NULL);
    }
    n = NEWHEAP();
    ptr = xrealloc(ptr, size);
    return ADD2HEAP(n, cnt, ptr);
}

void
rb_parser_free(struct parser_params *parser, void *ptr)
{
    NODE **prev = &parser->heap, *n;

    while ((n = *prev) != NULL) {
	if (n->u1.node == ptr) {
	    *prev = n->u2.node;
	    rb_gc_force_recycle((VALUE)n);
	    break;
	}
	prev = &n->u2.node;
    }
    xfree(ptr);
}
#endif

void
rb_parser_printf(struct parser_params *parser, const char *fmt, ...)
{
    va_list ap;
    VALUE mesg = parser->debug_buffer;

    if (NIL_P(mesg)) parser->debug_buffer = mesg = rb_str_new(0, 0);
    va_start(ap, fmt);
    rb_str_vcatf(mesg, fmt, ap);
    va_end(ap);
    if (RSTRING_END(mesg)[-1] == '\n') {
	rb_io_write(rb_stdout, mesg);
	parser->debug_buffer = Qnil;
    }
}
#endif

#ifdef RIPPER
#ifdef RIPPER_DEBUG
extern int rb_is_pointer_to_heap(VALUE);

/* :nodoc: */
static VALUE
ripper_validate_object(VALUE self, VALUE x)
{
    if (x == Qfalse) return x;
    if (x == Qtrue) return x;
    if (x == Qnil) return x;
    if (x == Qundef)
        rb_raise(rb_eArgError, "Qundef given");
    if (FIXNUM_P(x)) return x;
    if (SYMBOL_P(x)) return x;
    if (!rb_is_pointer_to_heap(x))
        rb_raise(rb_eArgError, "invalid pointer: %p", x);
    switch (BUILTIN_TYPE(x)) {
      case T_STRING:
      case T_OBJECT:
      case T_ARRAY:
      case T_BIGNUM:
      case T_FLOAT:
      case T_COMPLEX:
      case T_RATIONAL:
        return x;
      case T_NODE:
	if (nd_type(x) != NODE_RIPPER) {
	    rb_raise(rb_eArgError, "NODE given: %p", x);
	}
	return ((NODE *)x)->nd_rval;
      default:
        rb_raise(rb_eArgError, "wrong type of ruby object: %p (%s)",
                 x, rb_obj_classname(x));
    }
    return x;
}
#endif

#define validate(x) ((x) = get_value(x))

static VALUE
ripper_dispatch0(struct parser_params *parser, ID mid)
{
    return rb_funcall(parser->value, mid, 0);
}

static VALUE
ripper_dispatch1(struct parser_params *parser, ID mid, VALUE a)
{
    validate(a);
    return rb_funcall(parser->value, mid, 1, a);
}

static VALUE
ripper_dispatch2(struct parser_params *parser, ID mid, VALUE a, VALUE b)
{
    validate(a);
    validate(b);
    return rb_funcall(parser->value, mid, 2, a, b);
}

static VALUE
ripper_dispatch3(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c)
{
    validate(a);
    validate(b);
    validate(c);
    return rb_funcall(parser->value, mid, 3, a, b, c);
}

static VALUE
ripper_dispatch4(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    return rb_funcall(parser->value, mid, 4, a, b, c, d);
}

static VALUE
ripper_dispatch5(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d, VALUE e)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    validate(e);
    return rb_funcall(parser->value, mid, 5, a, b, c, d, e);
}

static VALUE
ripper_dispatch7(struct parser_params *parser, ID mid, VALUE a, VALUE b, VALUE c, VALUE d, VALUE e, VALUE f, VALUE g)
{
    validate(a);
    validate(b);
    validate(c);
    validate(d);
    validate(e);
    validate(f);
    validate(g);
    return rb_funcall(parser->value, mid, 7, a, b, c, d, e, f, g);
}

static const struct kw_assoc {
    ID id;
    const char *name;
} keyword_to_name[] = {
    {keyword_class,	"class"},
    {keyword_module,	"module"},
    {keyword_def,	"def"},
    {keyword_undef,	"undef"},
    {keyword_begin,	"begin"},
    {keyword_rescue,	"rescue"},
    {keyword_ensure,	"ensure"},
    {keyword_end,	"end"},
    {keyword_if,	"if"},
    {keyword_unless,	"unless"},
    {keyword_then,	"then"},
    {keyword_elsif,	"elsif"},
    {keyword_else,	"else"},
    {keyword_case,	"case"},
    {keyword_when,	"when"},
    {keyword_while,	"while"},
    {keyword_until,	"until"},
    {keyword_for,	"for"},
    {keyword_break,	"break"},
    {keyword_next,	"next"},
    {keyword_redo,	"redo"},
    {keyword_retry,	"retry"},
    {keyword_in,	"in"},
    {keyword_do,	"do"},
    {keyword_do_cond,	"do"},
    {keyword_do_block,	"do"},
    {keyword_return,	"return"},
    {keyword_yield,	"yield"},
    {keyword_super,	"super"},
    {keyword_self,	"self"},
    {keyword_nil,	"nil"},
    {keyword_true,	"true"},
    {keyword_false,	"false"},
    {keyword_and,	"and"},
    {keyword_or,	"or"},
    {keyword_not,	"not"},
    {modifier_if,	"if"},
    {modifier_unless,	"unless"},
    {modifier_while,	"while"},
    {modifier_until,	"until"},
    {modifier_rescue,	"rescue"},
    {keyword_alias,	"alias"},
    {keyword_defined,	"defined?"},
    {keyword_BEGIN,	"BEGIN"},
    {keyword_END,	"END"},
    {keyword__LINE__,	"__LINE__"},
    {keyword__FILE__,	"__FILE__"},
    {keyword__ENCODING__, "__ENCODING__"},
    {0, NULL}
};

static const char*
keyword_id_to_str(ID id)
{
    const struct kw_assoc *a;

    for (a = keyword_to_name; a->id; a++) {
        if (a->id == id)
            return a->name;
    }
    return NULL;
}

#undef ripper_id2sym
static VALUE
ripper_id2sym(ID id)
{
    const char *name;
    char buf[8];

    if (ISASCII(id)) {
        buf[0] = (char)id;
        buf[1] = '\0';
        return ID2SYM(rb_intern2(buf, 1));
    }
    if ((name = keyword_id_to_str(id))) {
        return ID2SYM(rb_intern(name));
    }
    if (!rb_id2str(id)) {
	rb_bug("cannot convert ID to string: %ld", (unsigned long)id);
    }
    return ID2SYM(id);
}

static ID
ripper_get_id(VALUE v)
{
    NODE *nd;
    if (!RB_TYPE_P(v, T_NODE)) return 0;
    nd = (NODE *)v;
    if (nd_type(nd) != NODE_RIPPER) return 0;
    return nd->nd_vid;
}

static VALUE
ripper_get_value(VALUE v)
{
    NODE *nd;
    if (v == Qundef) return Qnil;
    if (!RB_TYPE_P(v, T_NODE)) return v;
    nd = (NODE *)v;
    if (nd_type(nd) != NODE_RIPPER) return Qnil;
    return nd->nd_rval;
}

static void
ripper_error_gen(struct parser_params *parser)
{
    parser->error_p = TRUE;
}

static void
ripper_compile_error(struct parser_params *parser, const char *fmt, ...)
{
    VALUE str;
    va_list args;

    va_start(args, fmt);
    str = rb_vsprintf(fmt, args);
    va_end(args);
    rb_funcall(parser->value, rb_intern("compile_error"), 1, str);
    ripper_error_gen(parser);
}

static VALUE
ripper_lex_get_generic(struct parser_params *parser, VALUE src)
{
    return rb_io_gets(src);
}

static VALUE
ripper_s_allocate(VALUE klass)
{
    struct parser_params *p;
    VALUE self = TypedData_Make_Struct(klass, struct parser_params,
				       &parser_data_type, p);
    p->value = self;
    return self;
}

#define ripper_initialized_p(r) ((r)->lex.input != 0)

/*
 *  call-seq:
 *    Ripper.new(src, filename="(ripper)", lineno=1) -> ripper
 *
 *  Create a new Ripper object.
 *  _src_ must be a String, an IO, or an Object which has #gets method.
 *
 *  This method does not starts parsing.
 *  See also Ripper#parse and Ripper.parse.
 */
static VALUE
ripper_initialize(int argc, VALUE *argv, VALUE self)
{
    struct parser_params *parser;
    VALUE src, fname, lineno;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    rb_scan_args(argc, argv, "12", &src, &fname, &lineno);
    if (RB_TYPE_P(src, T_FILE)) {
        lex_gets = ripper_lex_get_generic;
    }
    else {
        StringValue(src);
        lex_gets = lex_get_str;
    }
    lex_input = src;
    parser->eofp = 0;
    if (NIL_P(fname)) {
        fname = STR_NEW2("(ripper)");
	OBJ_FREEZE(fname);
    }
    else {
	StringValueCStr(fname);
	fname = rb_str_new_frozen(fname);
    }
    parser_initialize(parser);

    ruby_sourcefile_string = fname;
    ruby_sourcefile = RSTRING_PTR(fname);
    ruby_sourceline = NIL_P(lineno) ? 0 : NUM2INT(lineno) - 1;

    return Qnil;
}

struct ripper_args {
    struct parser_params *parser;
    int argc;
    VALUE *argv;
};

static VALUE
ripper_parse0(VALUE parser_v)
{
    struct parser_params *parser;

    TypedData_Get_Struct(parser_v, struct parser_params, &parser_data_type, parser);
    parser_prepare(parser);
    ripper_yyparse((void*)parser);
    return parser->result;
}

static VALUE
ripper_ensure(VALUE parser_v)
{
    struct parser_params *parser;

    TypedData_Get_Struct(parser_v, struct parser_params, &parser_data_type, parser);
    parser->parsing_thread = Qnil;
    return Qnil;
}

/*
 *  call-seq:
 *    ripper#parse
 *
 *  Start parsing and returns the value of the root action.
 */
static VALUE
ripper_parse(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (!NIL_P(parser->parsing_thread)) {
        if (parser->parsing_thread == rb_thread_current())
            rb_raise(rb_eArgError, "Ripper#parse is not reentrant");
        else
            rb_raise(rb_eArgError, "Ripper#parse is not multithread-safe");
    }
    parser->parsing_thread = rb_thread_current();
    rb_ensure(ripper_parse0, self, ripper_ensure, self);

    return parser->result;
}

/*
 *  call-seq:
 *    ripper#column   -> Integer
 *
 *  Return column number of current parsing line.
 *  This number starts from 0.
 */
static VALUE
ripper_column(VALUE self)
{
    struct parser_params *parser;
    long col;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    col = parser->tokp - lex_pbeg;
    return LONG2NUM(col);
}

/*
 *  call-seq:
 *    ripper#filename   -> String
 *
 *  Return current parsing filename.
 */
static VALUE
ripper_filename(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    return ruby_sourcefile_string;
}

/*
 *  call-seq:
 *    ripper#lineno   -> Integer
 *
 *  Return line number of current parsing line.
 *  This number starts from 1.
 */
static VALUE
ripper_lineno(VALUE self)
{
    struct parser_params *parser;

    TypedData_Get_Struct(self, struct parser_params, &parser_data_type, parser);
    if (!ripper_initialized_p(parser)) {
        rb_raise(rb_eArgError, "method called for uninitialized object");
    }
    if (NIL_P(parser->parsing_thread)) return Qnil;
    return INT2NUM(ruby_sourceline);
}

#ifdef RIPPER_DEBUG
/* :nodoc: */
static VALUE
ripper_assert_Qundef(VALUE self, VALUE obj, VALUE msg)
{
    StringValue(msg);
    if (obj == Qundef) {
        rb_raise(rb_eArgError, "%"PRIsVALUE, msg);
    }
    return Qnil;
}

/* :nodoc: */
static VALUE
ripper_value(VALUE self, VALUE obj)
{
    return ULONG2NUM(obj);
}
#endif


void
Init_ripper(void)
{
    ripper_init_eventids1();
    ripper_init_eventids2();
    id_warn = rb_intern_const("warn");
    id_warning = rb_intern_const("warning");

    InitVM(ripper);
}

void
InitVM_ripper(void)
{
    VALUE Ripper;

    Ripper = rb_define_class("Ripper", rb_cObject);
    /* version of Ripper */
    rb_define_const(Ripper, "Version", rb_usascii_str_new2(RIPPER_VERSION));
    rb_define_alloc_func(Ripper, ripper_s_allocate);
    rb_define_method(Ripper, "initialize", ripper_initialize, -1);
    rb_define_method(Ripper, "parse", ripper_parse, 0);
    rb_define_method(Ripper, "column", ripper_column, 0);
    rb_define_method(Ripper, "filename", ripper_filename, 0);
    rb_define_method(Ripper, "lineno", ripper_lineno, 0);
    rb_define_method(Ripper, "end_seen?", rb_parser_end_seen_p, 0);
    rb_define_method(Ripper, "encoding", rb_parser_encoding, 0);
    rb_define_method(Ripper, "yydebug", rb_parser_get_yydebug, 0);
    rb_define_method(Ripper, "yydebug=", rb_parser_set_yydebug, 1);
    rb_define_method(Ripper, "error?", ripper_error_p, 0);
#ifdef RIPPER_DEBUG
    rb_define_method(rb_mKernel, "assert_Qundef", ripper_assert_Qundef, 2);
    rb_define_method(rb_mKernel, "rawVALUE", ripper_value, 1);
    rb_define_method(rb_mKernel, "validate_object", ripper_validate_object, 1);
#endif

    rb_define_singleton_method(Ripper, "dedent_string", parser_dedent_string, 2);
    rb_define_private_method(Ripper, "dedent_string", parser_dedent_string, 2);

    ripper_init_eventids1_table(Ripper);
    ripper_init_eventids2_table(Ripper);

# if 0
    /* Hack to let RDoc document SCRIPT_LINES__ */

    /*
     * When a Hash is assigned to +SCRIPT_LINES__+ the contents of files loaded
     * after the assignment will be added as an Array of lines with the file
     * name as the key.
     */
    rb_define_global_const("SCRIPT_LINES__", Qnil);
#endif

}
#endif /* RIPPER */

