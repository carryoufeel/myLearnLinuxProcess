PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE user(id int,name char,age int);
INSERT INTO user VALUES(1,'关二哥',20);
INSERT INTO user VALUES(2,'刘大耳朵',21);
INSERT INTO user VALUES(1,'曹阿满',23);
INSERT INTO user VALUES(1,'阿斗',12);
CREATE TABLE user2(id int ,name char ,dt datetime);
INSERT INTO user2 VALUES(1,'zhangsan','2023-08-18 07:08:14');
INSERT INTO user2 VALUES(1,'zhangsan','2022-08-18 15:09:18');
CREATE TABLE user3(id INTEGER PRIMARY KEY ASC,name char,age int,dt datetime);
INSERT INTO user3 VALUES(1,'zhagnssan',10,'2022-08-18 15:15:09');
INSERT INTO user3 VALUES(2,'zhagnssan',10,'2022-08-18 15:16:50');
INSERT INTO user3 VALUES(3,'zhagnssan',10,'2022-08-18 15:16:52');
INSERT INTO user3 VALUES(4,'zhagnssan',10,'2022-08-18 15:16:52');
COMMIT;
