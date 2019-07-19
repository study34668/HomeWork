## 学生成绩管理系统

所有功能均采用指令的形式，输入一行代码回车建后执行一次

### 辅助功能

+ 查看版本

  ```v```

+ 查看帮助

  ```help```

+ 存储

  ```save```

### 查询

+ 查询学生

  ```search student [学号|姓名|all]```

  + ```search student 91``` 

    查询学号为 91 的同学的信息

  + ```search student 张三```

    查询姓名的张三的同学的信息

  + ```search student all```

    查询所有同学信息

+ 查询科目

  ```search subject [课程号|课程名称|all]```

  + ```search subject 1005```

    查询课程号为 1005 的课程

  + ```search subject 程序设计实践```

    查询程序设计实践课的信息

  + ```search subject all```

    查询所有课

+ 查询成绩

  ```search score [学号|姓名|all] [课程号|课程名称|all]```

  + ```search score 91 程序设计实践```

    查询学号为 91 的学生程序设计实践成绩

  + ```search score 张三 all```

    查询张三所有科目成绩

  + ```search score all 1005```
    
    查询课程号为 1005 的课程所有学生的成绩
    
  + ```search score all all```

    查询所有学生所有成绩

+ 查询排名和加权成绩

  ```search rank [学号|姓名|all] ```
  
  + ```search rank 张三```
  
    查询张三的加权和排名
  
  + ```search rank all```
  
    查询所有学生的加权和排名

### 增加

+ 增加学生

  ```add student 学号 姓名```

  + ```add student 91 张三```

    添加名为张三学号是 91 的学生

+ 增加科目

  ```add subject 课程号 课程名称 学分```

  + ```add subject 1005 程序设计实践 2```

    添加程序设计实践课

+ 增加成绩

  ```add score [学号|姓名] [课程号|课程名称] 成绩 ```

  + ```add score 张三 程序设计实践 100```

    张三程序设计实践 100 分

### 修改

+ 修改学生

  ```update student [学号|姓名] 新学号 新姓名```

  + ```update student 张三 90 张三```

    把张三的学号改为 90

+ 修改科目

  ```update subject [课程号|课程名称] 新课程号 新课程名 新学分```

  + ```update subject 1005 1005 程序设计实践 3```

    将程序设计实践的学分改为3

+ 修改成绩

  ```update score [学号|姓名] [课程号|课程名] 新成绩```

  + ```update score 张三 程序设计实践 59```

    把张三的程序设计实践分改为 59

### 删除

+ 删除学生

  ```delete student [学号|姓名]```

  + ```delete student 张三```

    删除张三

+ 删除科目

  + ```delete subject 1005```

    删除程序设计实践

+ 删除成绩

  ```delete score [学号|姓名] [课程号|课程名称]```

  + ```delete score 91 1005```

    删除张三的程序设计实践成绩

### 注意事项

+ 学分只支持整数和 .5 的小数
+ 除了查询功能以外，都需要指定一个学生和科目，所以虽然可以使用名称查询，但重名时请指定代号
+ 删除科目会把所以学生该科的成绩也删除