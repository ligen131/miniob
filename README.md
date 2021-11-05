# 2021 OceanBase 数据库大赛

该仓库由偏远小渔村传统弱校队维护，维护人员由 @ligen131 @Bunnycxk @QuartZ-Z 组成。

## 代码提交方式

1. 若为Linux系统清略过此步骤，若为Windows系统请从官网下载`git`并安装: [https://git-scm.com/downloads](https://git-scm.com/downloads) 默认选项安装即可。
2. 单击仓库右上角的`fork`按钮建立本仓库在本人账号下的分支，请特别注意**在你本人的账号下该仓库必须为Private状态**。
3. 通过`git clone https://github.com/[Your_User_Name]/miniob.git`将本仓库克隆到本地。
4. 在本地修改、编译（请见下面How to build，需要Linux系统）、运行代码。
5. 修改完代码之后通过`git push origin master`上传到`dev`分支。在本地第一次上传详见下面Useful Link中的GIthub基本操作。
6. 在github页面`pull request`拉取请求等待合并代码，**请注意不要申请合并到master分支，请申请合并到dev分支**。

## Log

`Lastest Update: 2021-11-05 16:21`

> v0.4.0 2021-11-05 16:21
>
> 妈的，经历了改了许多写法，终于他妈的完成了select-tables。用例测试如下：
>
> ```sql
> create table t(id int,name char(4),da date);
> insert into t values(1,'lige','2021-10-30');
> insert into t values(11,'lige','2021-10-31');
> insert into t values(2,'aset','2000-2-29');
> insert into t values(4,'deft','1976-2-29');
> insert into t values(5,'ghit','2035-1-1');
> insert into t values(6,'jklt','2021-6-30');
> insert into t values(233,'nowt','2021-10-31');
> create table s(id int,name char(4),da date);
> insert into s values(7,'lige','2021-10-30');
> insert into s values(8,'lige','2021-10-31');
> insert into s values(9,'aset','2000-2-29');
> insert into s values(10,'deft','1976-2-29');
> insert into s values(11,'ghit','2035-1-1');
> insert into s values(12,'jklt','2021-6-30');
> insert into s values(233,'nowt','2021-10-31');
> select * from s,t where s.name=t.name;
> select s.name,t.id,t.name from s,t where s.id=t.id;
> select * from s,t where s.id=t.id and s.da>'2021-10-30' and t.da<'2021-10-31' and t.id>1;
> select * from s,t where s.id=t.id;
> select * from s,t where s.id=t.id and t.da>'2021-10-30';
> drop table t;
> drop table s;
> exit;
> ```
>
> 输出：
>
> ```sql
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > s.id | s.name | s.da | t.id | t.name | t.da
> 7 | lige | 2021-10-30 | 1 | lige | 2021-10-30
> 7 | lige | 2021-10-30 | 11 | lige | 2021-10-31
> 8 | lige | 2021-10-31 | 1 | lige | 2021-10-30
> 8 | lige | 2021-10-31 | 11 | lige | 2021-10-31
> 9 | aset | 2000-02-29 | 2 | aset | 2000-02-29
> 10 | deft | 1976-02-29 | 4 | deft | 1976-02-29
> 11 | ghit | 2035-01-01 | 5 | ghit | 2035-01-01
> 12 | jklt | 2021-06-30 | 6 | jklt | 2021-06-30
> 233 | nowt | 2021-10-31 | 233 | nowt | 2021-10-31
> miniob > s.name | t.id | t.name
> ghit | 11 | lige
> nowt | 233 | nowt
> miniob > s.id | s.name | s.da | t.id | t.name | t.da
> miniob > s.id | s.name | s.da | t.id | t.name | t.da
> 11 | ghit | 2035-01-01 | 11 | lige | 2021-10-31
> 233 | nowt | 2021-10-31 | 233 | nowt | 2021-10-31
> miniob > s.id | s.name | s.da | t.id | t.name | t.da
> 11 | ghit | 2035-01-01 | 11 | lige | 2021-10-31
> 233 | nowt | 2021-10-31 | 233 | nowt | 2021-10-31
> miniob > SUCCESS
> miniob > SUCCESS
> ```
>
> *距离上次提交已经三天，这题真的很难受qwq。经历了莫名其妙的各种段错误qwq，最终发现是自己写错了。问了各路大神，改了几种写法，还被一个大一队超了qwq。行吧，能过就行qwq。
>
> *期望得分：60 。
>
> *cxk也逐渐步入正轨，希望能挺进初赛吧。前面竞争已经很激烈了。
>
> v0.3.0 2021-11-02 18:53
>
> 艰难地完成了Update。用例测试如下：
>
> ```sql
> create table t(id int,name char,da date);
> create index da_t on t(da);
> insert into t values(1,'ligen','2021-10-30');
> insert into t values(11,'ligen','2021-10-31');
> insert into t values(2,'aset','2000-2-29');
> insert into t values(4,'deft','1976-2-29');
> insert into t values(5,'ghit','2035-1-1');
> insert into t values(6,'jklt','2021-6-30');
> insert into t values(233,'nowt','2021-10-31');
> select * from t;    
> update t set name='aaa' where da='2021-10-31';
> select * from t;
> update t set name='bbb' where da='2021-10-32';
> select * from t;
> update t set name='ccc' where id=9;
> select * from t;
> update t set name="OK" where da>='1976-2-29';
> select * from t;
> exit;
> ```
>
> 输出：
>
> ```
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | lige | 2021-10-31
> 2 | aset | 2000-02-29
> 4 | deft | 1976-02-29
> 5 | ghit | 2035-01-01
> 6 | jklt | 2021-06-30
> 233 | nowt | 2021-10-31
> miniob > SUCCESS
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | aaa | 2021-10-31
> 2 | aset | 2000-02-29
> 4 | deft | 1976-02-29
> 5 | ghit | 2035-01-01
> 6 | jklt | 2021-06-30
> 233 | aaa | 2021-10-31
> miniob > FAILURE
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | aaa | 2021-10-31
> 2 | aset | 2000-02-29
> 4 | deft | 1976-02-29
> 5 | ghit | 2035-01-01
> 6 | jklt | 2021-06-30
> 233 | aaa | 2021-10-31
> miniob > SUCCESS
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | aaa | 2021-10-31
> 2 | aset | 2000-02-29
> 4 | deft | 1976-02-29
> 5 | ghit | 2035-01-01
> 6 | jklt | 2021-06-30
> 233 | aaa | 2021-10-31
> miniob > SUCCESS
> miniob > id | name | da
> 1 | OK | 2021-10-30
> 11 | OK | 2021-10-31
> 2 | OK | 2000-02-29
> 4 | OK | 1976-02-29
> 5 | OK | 2035-01-01
> 6 | OK | 2021-06-30
> ```
>
> *看了两天，仿照了`Insert/delete/select`的写法，一开始看的真的晕，寻求大佬帮助之后有点思路，希望能过吧qwq。
>
> *期望得分：50
>
> *如果能过目前就能进前50了。
>
> v0.2.0 2021-10-31 22:06
>
> 完成date。顺便修复了一下原代码中两个char类型相接select和where时会出错的情况（如果未来有错误请到`tuple.cpp`的`add_record`中的`case CHARS`和`condition_filter.cpp`的`filter`函数中修改，具体是用到`strncpy`函数那几行）。用例测试如下：
>
> ```sql
> create table t(id int,name char,da date);
> insert into t values(1,'ligen','2021-10-30');
> insert into t values(11,'ligen','2021-10-31');
> insert into t values(2,'aset','2000-2-29');
> insert into t values(3,'fail','2000-100-29');
> insert into t values(4,'deft','1976-2-29');
> insert into t values(5,'ghit','2035-1-1');
> insert into t values(6,'jklt','2021-6-30');
> insert into t values(7,'FAIL','2021-4-31');
> insert into t values(8,'FAI2','2021-2-29');
> insert into t values(233,'nowt','2021-10-31');
> select * from t where da='2021-10-30';
> select * from t where da='2021-11-31';
> select * from t where da>='2021-10-30';
> select * from t where da>'2021-10-30';
> select id,da from t where name='aset';
> select name,da from t where name='fail';
> create index da_t on t(da);
> select * from t;
> drop table t;
> exit;
> ```
>
> 输出：
>
> ```
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > FAILURE
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > FAILURE
> miniob > FAILURE
> miniob > SUCCESS
> miniob > id | name | da
> 1 | lige | 2021-10-30
> miniob > FAILURE
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | lige | 2021-10-31
> 5 | ghit | 2035-01-01
> 233 | nowt | 2021-10-31
> miniob > id | name | da
> 11 | lige | 2021-10-31
> 5 | ghit | 2035-01-01
> 233 | nowt | 2021-10-31
> miniob > miniob > miniob > miniob > id | da
> 2 | 2000-02-29
> miniob > name | da
> miniob > SUCCESS
> miniob > id | name | da
> 1 | lige | 2021-10-30
> 11 | lige | 2021-10-31
> 2 | aset | 2000-02-29
> 4 | deft | 1976-02-29
> 5 | ghit | 2035-01-01
> 6 | jklt | 2021-06-30
> 233 | nowt | 2021-10-31
> miniob > SUCCESS
> ```
>
> *其实date应该很快就写完了的，拖这么久没写别的实是不应该。
>
> *期望得分：40
>
> *如果测试中有update的数据那这10分是拿不到了。接下来写update。
>
> *Upload by ligen131
>
> v0.1.1 2021-10-29 14:49 && v0.1.0 2021-10-28 23:50
>
> 完成drop-table && select-meta。用例测试如下：
>
> ```sql
> help;
> show tables;
> create table t(id int,name char(255));
> insert into t values(233,'aaa');
> insert into t values(131,'bbb');
> insert into t values(233,'ccc');
> insert into t values(114,'aaa');
> insert into t values(555,'ddd');
> select * from t;
> select not_exists_col from not_exists_table where not_exists_col2="aaa";
> select not_exists_col from t where not_exists_col2="aaa";
> select not_exists_col from t where name="aaa";
> select id from t where name="aaa";
> select id from not_exists_table;
> select id from t where aaa="aaa";
> select num from t;
> create index t_id on t(id);
> create index t_name on t(name);
> select * from t;
> delete from t where name='aaa';
> select * from t;
> show tables;
> drop table t;
> show tables;
> select * from t;
> create table t(id int,num int,name char(255));
> insert into t values(666,777,"eee");
> create index t_id on t(id);
> create index t_num on t(num);
> select * from t;
> drop table t;
> exit;
> ```
>
> 输出：
>
> ```
> miniob > show tables;
> desc `table name`;
> create table `table name` (`column name` `column type`, ...);
> drop table `table name`;
> create index `index name` on `table` (`column`);
> insert into `table` values(`value1`,`value2`);
> update `table` set column=value [where `column`=`value`];
> delete from `table` [where `column`=`value`];
> select [ * | `columns` ] from `table`;
> miniob > No table
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > id | name
> 233 | aaa
> 131 | bbb
> 233 | ccc
> 114 | aaa
> 555 | ddd
> miniob > FAILURE
> miniob > FAILURE
> miniob > FAILURE
> miniob > id
> 233
> 114
> miniob > FAILURE
> miniob > FAILURE
> miniob > FAILURE
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > id | name
> 233 | aaa
> 131 | bbb
> 233 | ccc
> 114 | aaa
> 555 | ddd
> miniob > SUCCESS
> miniob > id | name
> 131 | bbb
> 233 | ccc
> 555 | ddd
> miniob > t
> 
> miniob > SUCCESS
> miniob > No table
> miniob > FAILURE
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > SUCCESS
> miniob > id | num | name
> 666 | 777 | eee
> miniob > SUCCESS
> ```
>
> 10-29: 修改元数据未校验输出No data问题，现在会返回FAILURE。
>
> *看工程代码真的好难qwq
>
> *drop table基本实现就是删除.table/.data/.index文件，index因为有多个所以要vector枚举，还要把Buffer Pool中的缓存清理干净（研究了好久qwq）。
>
> *Upload By ligen131
>
> *期望得分：30
>
> v0.0.2 2021-10-20 13:51
>
> 编译完成，上传依赖库文件。
>
> v0.0.1 2021-10-15 23:46
>
> 比赛开始，提交初始代码，创建`dev`分支。

## Useful Link

[OceanBase大赛官网及排名榜](https://open.oceanbase.com/competition/index)

[Problemset && 注意事项](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-topics#)

**[（重要！必读！）OceanBase大赛miniob代码架构框架设计和说明](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-introduction)**

[数据库管理系统实现基础讲义 华中科技大学 谢美意 左琼](https://oceanbase-partner.github.io/lectures-on-dbms-implementation/)

[Git - 菜鸟教程](https://www.runoob.com/git/git-tutorial.html)

[Github仓库上传及下载等基本操作教程](https://www.cnblogs.com/lsdb/p/12123027.html)

## How to build

1. install cmake
2. build libevent

```shell
git submodule add https://github.com/libevent/libevent deps/libevent
cd deps
cd libevent
git checkout release-2.1.12-stable
mkdir build
cd build
cmake .. -DEVENT__DISABLE_OPENSSL=ON
make
sudo make install
```

3. build google test

```shell
git submodule add https://github.com/google/googletest deps/googletest
cd deps
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
```

4. build jsoncpp

```shell
git submodule add https://github.com/open-source-parsers/jsoncpp.git deps/jsoncpp
cd deps
cd jsoncpp
mkdir build
cd build
cmake -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF ..
make
sudo make install
```

5. build miniob

```shell
cd `project home`
mkdir build
cd build
cmake ..
make
```

## 必做题

| 名称            | 分值 | 描述                                                         | 测试用例示例                                                 |
| :-------------- | :--- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 优化buffer pool | 10   | 必做。实现LRU淘汰算法或其它淘汰算法                          |                                                              |
| 查询元数据校验  | 10   | 必做。查询语句中存在不存在的列名、表名等，需要返回失败。需要检查代码，判断是否需要返回错误的地方都返回错误了。 | ``create table t(id int, age int); select * from t where name=’a’; select address from t where id=1; select * from t_1000; select * from t where not_exists_col=1;`` |
| drop table      | 10   | 必做。删除表。清除表相关的资源。                             | ``create table t(id int, age int); create table t(id int, name char); drop table t; create table t(id int, name char);`` |
| 实现update功能  | 10   | 必做。update单个字段即可。                                   | ``update t set age =100 where id=2; update set age=20 where id>100;`` |
| 增加date字段    | 10   | 必做。date测试不会超过2038年2月，不会小于1970年1月1号。注意处理非法的date输入，需要返回FAILURE。 | ``create table t(id int, birthday date); insert into t values(1, ‘2020-09-10’); insert into t values(2, ‘2021-1-2’); select * from t;`` |
| 多表查询        | 10   | 必做。支持多张表的笛卡尔积关联查询。需要实现select * from t1,t2; select t1.*,t2.* from t1,t2;以及select t1.id,t2.id from t1,t2;查询可能会带条件。查询结果展示格式参考单表查询。每一列必须带有表信息，比如: t1.id \| t2.id 1 \| 1 | ``select * from t1,t2; select * from t1,t2 where t1.id=t2.id and t1.age > 10; select * from t1,t2,t3;`` |
| 聚合运算        | 10   | 需要实现max/min/count/avg. 包含聚合字段时，只会出现聚合字段。聚合函数中的参数不会是表达式，比如age +1 | ``select max(age) from t1; select count(*) from t1; select count(1) from t1; select count(id) from t1;`` |

## 选做题

| 名称               | 分值 | 描述                                                         | 测试用例示例                                                 |
| :----------------- | :--- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| 多表join操作       | 20   | INNER JOIN。需要支持join多张表。需要考虑大表问题，不要直接使用笛卡尔积再过滤 | ``select * from t1 inner join t2 on t1.id=t2.id; select * from t1 inner join t2 on t1.id=t2.id inner join t3 on t1.id=t3.id; selec * from t1 inner join t2 on t1.id=t2.id and t2.age>10 where t1.name >=’a’;`` |
| 一次插入多条数据   | 10   | 一次插入的数据要同时成功或失败。                             | ``insert into t1 values(1,1),(2,2),(3,3);``                  |
| 唯一索引           | 10   | 唯一索引：create unique index                                | ``create unique index i_id on t1(id); insert into t1 values(1,1); insert into t1 values(1,2); – failed`` |
| 支持NULL类型       | 10   | 包括但不限于建表、查询和插入。默认情况不允许为NULL，使用nullable关键字表示字段允许为NULL。 Null不区分大小写。 注意NULL字段的对比规则是NULL与**任何** 数据对比，都是FALSE。 | ``create table t1 (id int not null, age int not null, address nullable); create table t1 (id int, age int, address char nullable); insert into t1 values(1,1, null);`` |
| 简单子查询         | 10   | 支持简单的IN(NOT IN)语句； 支持与子查询结果做比较运算； 支持子查询中带聚合函数。 子查询中不会与主查询做关联。 | ``select * from t1 where name in(select name from t2); select * from t1 where t1.age >(select max(t2.age) from t2); select * from t1 where t1.age > (select avg(t2.age) from t2) and t1.age > 20.0; ``NOTE: 表达式中可能存在不同类型值比较 |
| 多列索引           | 20   | 单个索引关联了多个字段                                       | ``create index i_id on t1(id, age);``                        |
| 超长字段           | 20   | 超长字段的长度可能超出一页，比如常见的text,blob等。这里仅要求实现text（text 长度固定4096字节），可以当做字符串实现。 注意：当前的查询，只能支持一次返回少量数据，需要扩展 | ``create table t(id int, age int, info text); insert into t(1,1, ‘a very very long string’); select * from t where id=1;`` |
| 查询条件支持表达式 | 20   | 查询条件中支持运算表达式，这里的运算表达式包括 +-*/。 仅支持基本数据的运算即可，不对date字段做考察。 运算出现异常，按照NULL规则处理。 只需要考虑select。 | ``select * from t1,t2 where t1.age +10 > t2.age *2 + 3-(t1.age +10)/3; select t1.col1+t2.col2 from t1,t2 where t1.age +10 > t2.age *2 + 3-(t1.age +10)/3;`` |
| 复杂子查询         | 20   | 子查询在WHERE条件中，子查询语句支持多张表与AND条件表达式，查询条件支持max/min等 | ``select * from t1 where age in (select id from t2 where t2.name in (select name from t3))`` |
| 排序               | 10   | 支持oder by功能。不指定排序顺序默认为升序(asc)。 不需要支持oder by字段为数字的情况，比如select * from t order by 1; | ``select * from t,t1 where t.id=t1.id order by t.id asc,t1.score desc;`` |
| 分组               | 20   | 支持group by功能。group by中的聚合函数也不要求支持表达式     | ``select t.id, t.name, avg(t.score),avg(t2.age) from t,t2 where t.id=t2.id group by t.id;`` |

## 测试常见问题

### 测试Case

#### 优化buffer pool

题目中要求实现一个LRU算法。但是LRU算法有很多种，所以大家可以按照自己的想法来实现。因为不具备统一性，所以不做统一测试。

可以考虑后期，评出排名后，再检查算法实现。

#### basic 测试

基础测试是隐藏的测试case，是代码本身就有的功能，比如创建表、插入数据等。如果选手把原生仓库代码提交上去，就能够测试通过basic。

#### select-meta 测试

这个测试对应了“元数据校验”。选手们应该先做这个case。

常见测试失败场景有一个是 where 条件校验时 server core了。

#### drop-table case测试失败

目前遇到最多的失败情况是没有校验元数据，比如表删除后，再执行select，按照“元数据校验”规则，应该返回”FAILURE”。

#### date 测试

date测试需要注意校验日期有效性。比如输入”2021-2-31”，一个非法的日期，应该返回”FAILURE”。

date不需要考虑和string(char)做对比。比如 ``select * from t where d > ‘123’; select * from t where d < ‘abc’;`` 不会测试这种场景。但是需要考虑日期与日期的比较，比如``select * from t where d > ‘2021-01-21’;``。

date也不会用来计算平均值。

``select * form t where d=’2021-02-30‘;`` 这种场景在mysql下面是返回空数据集，但是我们现在约定都返回 FAILURE。

> 温馨提示：date 可以使用整数存储，简化处理

#### 浮点数展示问题

按照输出要求，浮点数最多保留两位小数，并且去掉多余的0。目前没有直接的接口能够输出这种格式。比如 printf(“%.2f”, f); 会输出 1.00，printf(“%g”, f); 虽然会删除多余的0，但是数据比较大或者小数位比较多时展示结果也不符合要求。

#### 浮点数与整数转换问题

比如 create table t(a int, b float); 在当前的实现代码中，是不支持insert into t values(1,1); 这种做法的，因为1是整数，而字段`b`是浮点数。那么，我们在比赛中，也不需要考虑这两种转换。

但是有一种例外情况，比如聚合函数运算：`select avg(a) from t;`,需要考虑整数运算出来结果，是一个浮点数。

#### update 测试

update 也要考虑元数据校验，比如更新不存在的表、更新不存在的字段等。

需要考虑不能转换的数据类型更新，比如用字符串更新整型字段。

对于整数与浮点数之间的转换，不做考察。学有余力的同学，可以做一下。

更新需要考虑的几个场景，如果这个case没有过，可以对比一下：

假设存在这个表：

``create table t (id int, name char, col1 int, col2 int);``

表上有个索引

``create index i_id on t (id);``

– 单行更新

``update t set name=’abc’ where id=1;``

– 多行更新

``update t set name=’a’ where col1>2;`` – 假设where条件能查出来多条数据

– 更新索引

``update t set id=4 where name=’c’;``

– 全表更新

``update t set col1=100;``

– where 条件有多个

``update t set name=’abc’ where col1=0 and col2=0;``

一些异常场景：

- 更新不存在的表
- 更新不存在的字段
- 查询条件中包含不合法的字段
- 查询条件查出来的数据集合是空（应该什么都不做，返回成功）
- 使用无法转换的类型更新某个字段，比如使用字符串更新整型字段

#### 多表查询

多表查询的输入SQL，只要是字段，都会带表名。比如不会存在 select id from t1,t2;

不带字段名称的场景（会测试）：select * from t1,t2;

带字段：``select t1.id, t1.age, t2.name from t1,t2 where t1.id=t2.id;``

或者：``select t1.* , t2.name from t1,t2 where t1.id=t2.id;``

多表查询，查询出来单个字段时，也需要加上表名字。原始代码中，会把表名给删除掉。比如select t1.id from t1,t2; 应该输出列名： t1.id。这里需要调整原始代码。输出列名的规则是：单表查询不带表名，多表查询带表名。

不要仅仅使用最简单的笛卡尔积运算，否则可能会内存不足。

#### 聚合运算

不需要考虑聚合字段与普通字段同时出现的场景。比如： ``select id, count(1) from t1;``

必做题中的聚合运算只需要考虑单张表的情况。

字符串可以不考虑AVG运算。

最少需要考虑的场景：

假设有一张表 

```sql
create table t(id int, name char, price float);
select count(*) from t;
select count(id) from t;
select min(id) from t;
select min(name) from t; – 字符串
select max(id) from t;
select max(name) from t;
select avg(id) from t; – 整数做AVG运算，输出可能是浮点数，所以要注意浮点数输出格式
select avg(price) from t;
select avg(price), max(id), max(name) from t;
```

还需要考虑一些异常场景：

```sql
select count(*,id) from t;
select count() from t;
select count(not_exists_col) from t;
```

#### 支持NULL类型

NULL的测试case描述的太过简单，这里做一下补充说明。 NULL的功能在设计时，参考了mariadb的做法。包括NULL的比较规则：`任何` 值与NULL做对比，结果都是FALSE。

因为miniob的特殊性，字段默认都是不能作为NULL的，所以这个测试用例中，要求增加关键字`nullable`，表示字段可以是NULL。

需要考虑的场景

- 建表`` create table t(id int, num int nullable, birthday date nullable); ``表示创建一个表t,字段num和birthday可以是NULL, 而id不能是NULL。

建索引 ``create index i_num on t(num); ``支持在可以为NULL的字段上建索引

需要支持增删改查

```sql
insert into t values(1, 2, '2020-01-01');
insert into t values(1, null, null);
insert into t values(1, null, '2020-02-02'); -- 同学们自己多考虑几种场景
insert into t values(null, 1, '2020-01-02'); -- 应该返回FAILURE，因为ID不能是NULL
select * from t; -- 全表遍历
-- null 条件查询，同学们自己多测试几种场景

select * from t where id is null;
select * from t where id is not null;
select * from t where num is null; 
select * from t where num > null;
select * from t where num <> null;
select * from t where 1=null;
select * from t where 'a'=null;
select * from t where null = null;
select * from t where null is null; -- 注意 = 与 is 的区别
select * from t where '2020-01-31' is null;
```

> 不要忘记多表查询

聚合

```sql
select count(*) from t;
select count(num) from t;
select avg(num) from t;
```

> 字段值是NULL时，比较特殊，不需要统计在内。如果是AVG，不会增加统计行数，也不需要默认值。

## Introduction

miniob设计的目标是让不熟悉数据库设计和实现的同学能够快速的了解与深入学习数据库内核，期望通过miniob相关训练之后，能够对各个数据库内核模块的功能与它们之间的关联有所了解，并能够在使用时，设计出高效的SQL。面向的对象主要是在校学生，并且诸多模块做了简化，比如不考虑并发操作。

注意：此代码仅供学习使用，不考虑任何安全特性。

## OceanBase大赛测试环境说明

> NOTE: miniob代码本身可以在Linux/MacOS上编译测试。

后台测试环境说明：

操作系统：Linux version 4.19.91-23.al7.x86_64

编译器：gcc-8.3.0 （使用clang的同学注意，编译结果可能与gcc稍有不同)

cmake: 3.20.52

make: GNU Make 3.82
