<div id='toc'>
</div>
# QT_ATM_with_mysql
### EASY ATM SYSTEM

#### 1、环境修改
(1) 将mysql.cpp中的数据库配置修改为你的配置：   
`` db.setHostName("localhost");//数据库地址``   
`` db.setDatabaseName("test"); // 数据库名称``    
`` db.setPort(3306);//数据库端口``    
`` db.setUserName("root"); // 用户名``    
`` db.setPassword("root"); // 密码``    
(2) 记得将MySQL的libmysql.dll文件复制到系统盘下Windows目录下    
(3) 数据库结构如下
> user表    
+-------+--------------+------+-----+---------+----------------+    
| Field | Type         | Null | Key | Default | Extra          |    
+-------+--------------+------+-----+---------+----------------+    
| id    | int(11)      | NO   | PRI | NULL    | auto_increment |    
| name  | text         | YES  |     | NULL    |                |    
| pwd   | text         | YES  |     | NULL    |                |    
| money | double(20,2) | YES  |     | 0.00    |                |    
| type  | int(11)      | YES  |     | NULL    |                |    
+-------+--------------+------+-----+---------+----------------+     

-

> record表    
+--------+--------------+------+-----+---------+----------------+    
| Field  | Type         | Null | Key | Default | Extra          |    
+--------+--------------+------+-----+---------+----------------+    
| id     | int(11)      | NO   | PRI | NULL    | auto_increment |    
| from_u | text         | NO   |     | NULL    |                |    
| to_u   | text         | NO   |     | NULL    |                |    
| money  | double(20,2) | NO   |     | NULL    |                |    
| time   | datetime     | NO   |     | NULL    |                |    
| status | text         | YES  |     | NULL    |                |    
| type   | text         | YES  |     | NULL    |                |    
+--------+--------------+------+-----+---------+----------------+    

建表语句就不写了，可以根据上面的结构来写  
注：在交易往来用户选项中，可以双击用户查看详细记录
#### 运行效果图
![截图](/ScreenShots/截图1.png)

![截图](/ScreenShots/截图5.png)

![截图](/ScreenShots/截图13.png)

![截图](/ScreenShots/截图16.png)
> 在交易往来用户选项中，可以双击用户查看详细记录

![截图](/ScreenShots/截图19.png)
<script src="http://jfamily.me/md-toc.js"></script>
