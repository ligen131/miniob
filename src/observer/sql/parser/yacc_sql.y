
%{

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

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        ASC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
		DATE_T
		TEXT_T
        STRING_T
        FLOAT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
		IN
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		AGG_COUNT
		AGG_MAX
		AGG_MIN
		AGG_AVG
        ORDER
		GROUP
        BY
		INNER
		JOIN
		IS
		NOT
		NULLL
		NULLABLE
		UNIQUE

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *dates;
  char *string;
  int number;
  float floats;
  char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <dates> DATEE
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON 
		{
			CONTEXT->index_list[CONTEXT->index_length++] = strdup($7);
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, CONTEXT->index_list, CONTEXT->index_length, 0);
			CONTEXT->index_length = 0;
		}
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID create_index_attr_list RBRACE SEMICOLON 
		{
			CONTEXT->index_list[CONTEXT->index_length++] = strdup($8);
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, CONTEXT->index_list, CONTEXT->index_length, 1);
			CONTEXT->index_length = 0;
		}
    ;
create_index_attr_list:
	/* empty */
	| COMMA ID create_index_attr_list {
		CONTEXT->index_list[CONTEXT->index_length++] = strdup($2);
	}
	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    | ID_get type LBRACE number RBRACE NOT NULLL
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    | ID_get type LBRACE number RBRACE NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    | ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    | ID_get type NOT NULLL
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    | ID_get type NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | DATE_T { $$=DATES; }
	   | TEXT_T { $$=TEXTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES data data_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length,CONTEXT->data_num,CONTEXT->data_list_r) ;

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->data_num=0;
    };
data:
	LBRACE value value_list RBRACE {
		CONTEXT->data_list_r[CONTEXT->data_num++]=CONTEXT->value_length;
	}
	;
data_list:
	/* empty */
    | COMMA data data_list  { 
  		
	  }
	;

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |DATEE {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
	|NULLL {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where order_by group_by SEMICOLON
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[0], $4);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[0], CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length = 0;
			CONTEXT->from_length = 0;
			CONTEXT->select_length = 0;
			CONTEXT->value_length = 0;
	}
	;
sub_select:
    LBRACE SELECT sub_select_attribute FROM ID sub_where RBRACE
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection[1], $5);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection[1], CONTEXT->sub_conditions, CONTEXT->sub_condition_length);

			CONTEXT->ssql->sstr.selection[0].is_sub_query_exist = 1;//"sub select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->sub_condition_length = 0;
	}
	;
order_by:
	/* empty */
    | ORDER BY select_order select_order_list {
      
    }
  ;
select_order_list:
	/* empty */
	| COMMA select_order select_order_list {

	}
  ;
select_order:
	ID {
			OrderBy order;
			orders_init(&order, NULL, $1, ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
	| ID ASC {
			OrderBy order;
			orders_init(&order, NULL, $1, ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
	| ID DESC {
			OrderBy order;
			orders_init(&order, NULL, $1, ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
	| ID DOT ID {
			OrderBy order;
			orders_init(&order, $1, $3, ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
	| ID DOT ID ASC {
			OrderBy order;
			orders_init(&order, $1, $3, ORDER_ASC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
	| ID DOT ID DESC {
			OrderBy order;
			orders_init(&order, $1, $3, ORDER_DESC);
			selects_append_orders(&CONTEXT->ssql->sstr.selection[0], &order);
	}
  ;
group_by:
	/* empty */
	| GROUP BY select_group select_group_list {

	}
  ;
select_group_list:
	/* empty */
	| COMMA select_group select_group_list {

	}
  ;
select_group:
	ID {
			GroupBy group;
			groups_init(&group, NULL, $1);
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
	| ID DOT ID {
			GroupBy group;
			groups_init(&group, $1, $3);
			selects_append_groups(&CONTEXT->ssql->sstr.selection[0], &group);
	}
  ;
sub_select_attribute:
	sub_aggOp LBRACE STAR RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
	| sub_aggOp LBRACE NUMBER RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array($3), CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
	| sub_aggOp LBRACE ID RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, $3, CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
	| sub_aggOp LBRACE ID DOT ID RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, $3, $5, CONTEXT->sub_aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
	| sub_aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
	| sub_aggOp LBRACE RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
    | STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
    | ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
  	| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[1], &attr);
		}
    ;
select_attr:
	select_attribute attr_list {

		}
	;
select_attribute:
	aggOp LBRACE STAR RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
	| aggOp LBRACE NUMBER RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, int_to_char_array($3), CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
	| aggOp LBRACE ID RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, $3, CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
	| aggOp LBRACE ID DOT ID RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, $3, $5, CONTEXT->aggop);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
	| aggOp LBRACE aggr_select_attr COMMA aggr_select_attr aggr_attr_list RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
	| aggOp LBRACE RBRACE {
			RelAttr attr;
			relation_attr_init_(&attr, NULL, "*", AGG_INVALID);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
    | STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
    | ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
  	| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection[0], &attr);
		}
    ;
attr_list:
    /* empty */
	| COMMA select_attribute attr_list {

		}
  	;
aggr_select_attr:
    STAR{  
      
		}
    | ID {

		}
  	| ID DOT ID {

		}
    ;
aggr_attr_list:
    /* empty */
    | COMMA STAR aggr_attr_list {
      
      }
    | COMMA ID aggr_attr_list {
      
      }
    | COMMA ID DOT ID aggr_attr_list {
      
  	  }
  	;


rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], $2);
		  }
    ;
    | INNER JOIN ID inner_join_on rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection[0], $3);
		  }
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
inner_join_on:
	/* empty */
    | ON condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
	;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

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
		|value comOp value 
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
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

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
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

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
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
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
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

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
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

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
    |ID DOT ID comOp sub_select
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);

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
	|ID comOp sub_select
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

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
    |sub_select comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $3, $5);

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
	|sub_select comOp ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $3);

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
    ;
sub_where:
    /* empty */ 
    | WHERE sub_condition sub_condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
sub_condition_list:
    /* empty */
    | AND sub_condition sub_condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
sub_condition:
    ID sub_comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

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
		|value sub_comOp value 
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
		|ID sub_comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

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
    |value sub_comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

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
    |ID DOT ID sub_comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
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
    |value sub_comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

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
    |ID DOT ID sub_comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

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
    // |ID DOT ID sub_comOp sub_select
	// 	{
	// 		RelAttr left_attr;
	// 		relation_attr_init(&left_attr, $1, $3);

	// 		Condition condition;
	// 		condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, NULL, 1);
	// 		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	// 		// $$=( Condition *)malloc(sizeof( Condition));
	// 		// $$->left_is_attr = 1;		//属性
	// 		// $$->left_attr.relation_name=$1;
	// 		// $$->left_attr.attribute_name=$3;
	// 		// $$->comp =CONTEXT->comp;
	// 		// $$->right_is_attr = 1;		//属性
	// 		// $$->right_attr.relation_name=$5;
	// 		// $$->right_attr.attribute_name=$7;
    // }
	// |ID sub_comOp sub_select
	// 	{
	// 		RelAttr left_attr;
	// 		relation_attr_init(&left_attr, NULL, $1);

	// 		Condition condition;
	// 		condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, NULL, 1);
	// 		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	// 		// $$=( Condition *)malloc(sizeof( Condition));
	// 		// $$->left_is_attr = 1;
	// 		// $$->left_attr.relation_name=NULL;
	// 		// $$->left_attr.attribute_name=$1;
	// 		// $$->comp = CONTEXT->comp;
	// 		// $$->right_is_attr = 1;
	// 		// $$->right_attr.relation_name=NULL;
	// 		// $$->right_attr.attribute_name=$3;

	// 	}
    ;

comOp:
	  NOT IN { CONTEXT->comp = COMP_NOT_IN; }
	| IN { CONTEXT->comp = COMP_IN; }
  	| EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
	| IS NOT { CONTEXT->comp = COMP_IS_NOT; }
	| IS { CONTEXT->comp = COMP_IS; }
    ;
sub_comOp:
	  NOT IN { CONTEXT->sub_comp = COMP_NOT_IN; }
	| IN { CONTEXT->sub_comp = COMP_IN; }
  	| EQ { CONTEXT->sub_comp = EQUAL_TO; }
    | LT { CONTEXT->sub_comp = LESS_THAN; }
    | GT { CONTEXT->sub_comp = GREAT_THAN; }
    | LE { CONTEXT->sub_comp = LESS_EQUAL; }
    | GE { CONTEXT->sub_comp = GREAT_EQUAL; }
    | NE { CONTEXT->sub_comp = NOT_EQUAL; }
	| IS NOT { CONTEXT->sub_comp = COMP_IS_NOT; }
	| IS { CONTEXT->sub_comp = COMP_IS; }
    ;

aggOp:
  	  AGG_COUNT { CONTEXT->aggop = COUNT; }
  	| AGG_MAX { CONTEXT->aggop = MAX; }
  	| AGG_MIN { CONTEXT->aggop = MIN; }
  	| AGG_AVG { CONTEXT->aggop = AVG; }
    ;
sub_aggOp:
  	  AGG_COUNT { CONTEXT->sub_aggop = COUNT; }
  	| AGG_MAX { CONTEXT->sub_aggop = MAX; }
  	| AGG_MIN { CONTEXT->sub_aggop = MIN; }
  	| AGG_AVG { CONTEXT->sub_aggop = AVG; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
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
