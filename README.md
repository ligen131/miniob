# 2021 OceanBase 数据库大赛

该仓库由偏远小渔村传统弱校队维护，维护人员由 @ligen131 @Bunnycxk @QuartZ-Z 组成。

## Useful Link

[OceanBase大赛官网](https://open.oceanbase.com/competition/index)

[数据库管理系统实现基础讲义 华中科技大学 谢美意 左琼](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/)

[Git - 菜鸟教程](https://www.runoob.com/git/git-tutorial.html)

## 代码提交方式

1. 根据操作系统从官网下载`git`并安装: [https://git-scm.com/downloads](https://git-scm.com/downloads) 默认选项安装即可。
2. 单击仓库右上角的`fork`按钮建立本仓库在本人账号下的分支。
3. 通过`git clone https://github.com/ligen131/miniob.git`将本仓库克隆到本地。

## 预选赛赛题示例

## 必做题

| 名称            | 描述                                                         | 测试用例示例                                                 |
| :-------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 优化buffer pool | 必做。实现LRU淘汰算法或其它淘汰算法                          |                                                              |
| drop table      | 必做。删除表。清除表相关的资源。                             | ```create table t(id int, age int); create table t(id int, name char); drop table t; create table t(id int, name char);``` |
| 实现update功能  | 必做。update单个字段即可。                                   | update t set age =100 where id=2; update set age=20 where id>100; |
| 增加date字段    | 必做。date测试不会超过2038年2月。注意处理非法的date输入。    | create table t(id int, birthday date); insert into t values(1, ‘2020-09-10’); insert into t values(2, ‘2021-1-2’); select * from t; |
| 查询元数据校验  | 必做。查询语句中存在不存在的列名、表名等，需要返回失败。需要检查代码，判断是否需要返回错误的地方都返回错误了。 | create table t(id int, age int); select * from t where name=’a’; select address from t where id=1; select * from t_1000; |
| 多表查询        | 必做。支持多张表的笛卡尔积关联查询。需要实现select * from t1,t2; select t1.*,t2.* from t1,t2;以及select t1.id,t2.id from t1,t2;查询可能会带条件。查询结果展示格式参考单表查询。每一列必须带有表信息，比如: t1.id \| t2.id 1 \| 1 | select * from t1,t2; select * from t1,t2 where t1.id=t2.id and t1.age > 10; select * from t1,t2,t3; |
| 聚合运算        | 需要实现max/min/count/avg. 包含聚合字段时，只会出现聚合字段。聚合函数中的参数不会是表达式，比如age +1 | select max(age) from t1; select count(*) from t1; select count(1) from t1; select count(id) from t1; |

## 选做题

| 名称               | 分值 | 描述                                                         | 测试用例示例                                                 |
| :----------------- | :--- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 多表join操作       | 20   | INNER JOIN。需要支持join多张表。需要考虑大表问题，不要直接使用笛卡尔积再过滤 | select * from t1 inner join t2 on t1.id=t2.id; select * from t1 inner join t2 on t1.id=t2.id inner join t3 on t1.id=t3.id; selec * from t1 inner join t2 on t1.id=t2.id and t2.age>10 where t1.name >=’a’; |
| 一次插入多条数据   | 10   | 一次插入的数据要同时成功或失败。                             | insert into t1 values(1,1),(2,2),(3,3);                      |
| 唯一索引           | 10   | 唯一索引：create unique index                                | create unique index i_id on t1(id); insert into t1 values(1,1); insert into t1 values(1,2); – failed |
| 支持NULL类型       | 10   | 包括但不限于建表、查询和插入。默认情况不允许为NULL，使用nullable关键字表示字段允许为NULL。 Null不区分大小写 | create table t1 (id int not null, age int not null, address nullable); create table t1 (id int, age int, address char nullable); insert into t1 values(1,1, null); |
| 简单子查询         | 10   | 支持简单的IN(NOT IN)语句； 支持与子查询结果做比较运算； 支持子查询中带聚合函数。 子查询中不会与主查询做关联。 | select * from t1 where name in(select name from t2); select * from t1 where t1.age >(select max(t2.age) from t2); select * from t1 where t1.age > (select avg(t2.age) from t2) and t1.age > 20.0; NOTE: 表达式中可能存在不同类型值比较 |
| 多列索引           | 20   | 单个索引关联了多个字段                                       | create index i_id on t1(id, age);                            |
| 超长字段           | 20   | 超长字段的长度可能超出一页，比如常见的text,blob等。这里仅要求实现text（text 长度固定4096字节），可以当做字符串实现。 注意：当前的查询，只能支持一次返回少量数据，需要扩展 | create table t(id int, age int, info text); insert into t(1,1, ‘a very very long string’); select * from t where id=1; |
| 查询条件支持表达式 | 20   | 查询条件中支持运算表达式，这里的运算表达式包括 +-*/。 仅支持基本数据的运算即可，不对date字段做考察。 运算出现异常，按照NULL规则处理。 只需要考虑select。 | select * from t1,t2 where t1.age +10 > t2.age *2 + 3-(t1.age +10)/3; select t1.col1+t2.col2 from t1,t2 where t1.age +10 > t2.age *2 + 3-(t1.age +10)/3; |
| 复杂子查询         | 20   | 子查询在WHERE条件中，子查询语句支持多张表与AND条件表达式，查询条件支持max/min等 | select * from t1 where age in (select id from t2 where t2.name in (select name from t3)) |
| 排序               | 10   | 支持oder by功能。不指定排序顺序默认为升序(asc)。 不需要支持oder by字段为数字的情况，比如select * from t order by 1; | select * from t,t1 where t.id=t1.id order by t.id asc,t1.score desc; |
| 分组               | 20   | 支持group by功能。group by中的聚合函数也不要求支持表达式     | select t.id, t.name, avg(t.score),avg(t2.age) from t,t2 where t.id=t2.id group by t.id; |

