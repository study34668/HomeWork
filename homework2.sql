MySQL

//建表
create table class (cid int unsigned primary key auto_increment, caption varchar(20) );

create table teacher (tid int unsigned primary key auto_increment, tname varchar(20) );

create table course (cid int unsigned primary key auto_increment, cname varchar(100), 
teacher_id int unsigned, foreign key (teacher_id) references teacher (tid) );

create table student (sid int unsigned primary key auto_increment, sname varchar(20), 
gender varchar(5), class_id int unsigned, foreign key (class_id) references class (cid) );

create table score (sid int unsigned primary key auto_increment, student_id int unsigned, 
course_id int unsigned, number int unsigned, foreign key (student_id) references student (sid), 
foreign key (course_id) references course (cid) );


//查找与 ## 选修课程完全一样的学生
select a.sid,sname from student a right join score b on a.sid=b.student_id 
group by a.sid,a.sname having a.sid != ## 
and sum(course_id) = (select sum(course_id) from score where student_id= ## ) 
and a.sid not in (select distinct student_id from score 
where course_id not in (select course_id from score where student_id= ## ) );

//查找课程最高分和最低分
select course_id as 课程ID, max(number) as 最高分, min(number) as 最低分 from score group by course_id;

ASC 升序  DESC 降序

//查找学生平均成绩
select student_id as 学号, sname as 姓名, avg(number) as 平均成绩 
from score sc left join student st on sc.student_id=st.sid 
group by student_id order by avg(number) ASC;

//查找学生及格率
select student_id as 学号, sname as 姓名, sum(number>=60)/count(number) *100  as '及格率(%)' 
from score sc left join student st on sc.student_id=st.sid 
group by student_id order by '及格率(%)' DESC;

//查找科目平均成绩
select course_id as 科目, tname as 老师, avg(number) as 平均成绩 
from score s left join course c on s.course_id=c.cid left join teacher t on c.teacher_id=t.tid 
group by course_id order by avg(number) DESC;

//查找各科前 ## 名
select cname as 科目, sname as 姓名, number as 成绩 
from course c left join score s on c.cid=s.course_id left join student st on s.student_id=st.sid 
where (select count(number) from score where course_id=s.course_id and number>s.number) < ## 
order by course_id ASC, number DESC;

//查找课程选修人数
select cname as 课程, count(student_id) as 人数 
from score s left join course c on s.course_id=c.cid 
group by course_id;

//查找选修了 ## 门课程的学生
select a.sid as 学号, sname as 姓名 
from student a left join score b on a.sid=b.student_id 
group by student_id having count(course_id) = ## ;

//查找男女各几人
select gender as 性别, count(sname) as 人数 from student group by gender;

//查找名字中有一定格式 ## 的学生
select sid as 学号, sname as 姓名, gender as 性别, class_id as 班级 from student where sname like (' ## ');

 % : 匹配任意多字符  _ : 匹配一个字符

//查找同名同姓同学的数量
select sname as 姓名, count(sname) as 人数 from student group by sname having 人数 > 1;

//查找科目平均成绩并按成绩和科目代号排序
select course_id as 课程代号, cname as 课程, avg(number) as 平均成绩 
from score left join course on course_id=cid group by course_id 
order by 平均成绩 ASC, course_id DESC;

//查找平均成绩大于 ## 的学生
select a.sid as 学号, sname as 姓名, avg(number) as 平均成绩 
from student a left join score b on a.sid=b.student_id 
group by a.sid having 平均成绩 > ## ;

//查找 学了 %% 科 或 科目编号为 %%   且 成绩低于或高于 ## 的学生姓名
select b.sid as 学号, sname as 姓名, number as 分数 
from score a left join student b on a.student_id=b.sid left join course c on a.course_id=c.cid 
where cname = ' %% ' course_id = ' %% ' and number <> ## ;

//查找选修了 ## 老师课程的同学最高分
select cname as 科目, sname as 姓名, max(number) as 成绩 
from score a left join student b on a.student_id=b.sid left join course c on a.course_id=c.cid left join teacher t on t.tid=c.teacher_id 
where tname=' ## ' group by course_id;

//查找成绩相同的同学
select student_id as 学号, sname as 姓名, number as 成绩 
from score a left join student b on a.student_id=b.sid 
where (select count(course_id) from score where number=a.number) > 1;

//查找至少选了 ## 门课的学生
select student_id as 学号, sname as 姓名 
from score a left join student b on a.student_id=b.sid 
group by student_id having count(course_id) >= ## ;

//查找所有学生都选修的课程
select course_id as 课程代码, cname as 课程 
from score a left join course b on a.course_id=b.cid 
group by course_id having count(student_id) = (select count(sid) from student);

//查找 ## 门以上不及格学生及其平均成绩
select student_id as 学号, sname as 姓名, avg(number) as 平均成绩 
from score a left join student b on a.student_id=b.sid
group by student_id having sum(case when number<60 then 1 else 0 end) > ## ;

//查找 ## 号课程分数小于60的学生(降序排列)
select student_id as 学号, sname as 姓名, number as 成绩 
from score a left join student b on a.student_id=b.sid 
where course_id=2 and number<60 order by number DESC;







