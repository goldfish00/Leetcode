-- # 1783
/*
Create table If Not Exists Players (player_id int, player_name varchar(20));
Create table If Not Exists Championships (year int, Wimbledon int, Fr_open int, US_open int, Au_open int);
Truncate table Players;
insert into Players (player_id, player_name) values ('1', 'Nadal');
insert into Players (player_id, player_name) values ('2', 'Federer');
insert into Players (player_id, player_name) values ('3', 'Novak');
Truncate table Championships;
insert into Championships (year, Wimbledon, Fr_open, US_open, Au_open) values ('2018', '1', '1', '1', '1');
insert into Championships (year, Wimbledon, Fr_open, US_open, Au_open) values ('2019', '1', '1', '2', '2');
insert into Championships (year, Wimbledon, Fr_open, US_open, Au_open) values ('2020', '2', '1', '2', '2');

SELECT player_id, player_name, COUNT(*) AS grand_slams_count FROM
(SELECT  P1.player_id, P1.player_name FROM Championships C1
JOIN Players P1
ON C1.Au_open = P1.player_id
UNION ALL
SELECT P2.player_id, P2.player_name FROM Championships C2
JOIN Players P2
ON C2.Wimbledon = P2.player_id
UNION ALL
SELECT P3.player_id, P3.player_name FROM Championships C3
JOIN Players P3
ON C3.Fr_open = P3.player_id
UNION ALL
SELECT P4.player_id, P4.player_name FROM Championships C4
JOIN Players P4
ON C4.US_open = P4.player_id) allWinners
GROUP BY player_id, player_name;
*/

-- 175
/*
Create table Person (PersonId int, FirstName varchar(255), LastName varchar(255));
Create table Address (AddressId int, PersonId int, City varchar(255), State varchar(255));
Truncate table Person;
insert into Person (PersonId, LastName, FirstName) values ('1', 'Wang', 'Allen');
Truncate table Address;
insert into Address (AddressId, PersonId, City, State) values ('1', '2', 'New York City', 'New York');

SELECT P.FirstName, P.LastName, A.City, A.State
FROM Address A RIGHT JOIN Person P on A.PersonId = P.PersonId;*/

-- 176
/*
Create table If Not Exists Employee (Id int, Salary int);
Truncate table Employee;
insert into Employee (Id, Salary) values ('1', '100');
insert into Employee (Id, Salary) values ('2', '200');
insert into Employee (Id, Salary) values ('3', '300');

SELECT
(SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT 1, 1) AS SecondHighestSalary
 */

-- 177 Note the use of DECLARE and SET here
/*
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
DECLARE M INT;
SET M = N - 1;
    RETURN (
      # Write your MySQL query statement below.
      SELECT (SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC  LIMIT M, 1)
  );
END*/

-- 178
/*
Create table If Not Exists Scores (Id int, Score DECIMAL(3,2));
Truncate table Scores;
insert into Scores (Id, Score) values ('1', '3.5');
insert into Scores (Id, Score) values ('2', '3.65');
insert into Scores (Id, Score) values ('3', '4.0');
insert into Scores (Id, Score) values ('4', '3.85');
insert into Scores (Id, Score) values ('5', '4.0');
insert into Scores (Id, Score) values ('6', '3.65');

SELECT S.Score, temp.`Rank` from Scores S
JOIN
(SELECT  Score, RANK() over (ORDER BY Score DESC ) AS `Rank` from (SELECT  DISTINCT Score FROM Scores) disScore) temp
ON S.Score = temp.Score
ORDER BY S.Score DESC;

SELECT
  Score,
  @rank := @rank + (@prev <> (@prev := Score)) Rank
FROM
  Scores,
  (SELECT @rank := 0, @prev := -1) init
ORDER BY Score desc;

SELECT
  Score,
  (SELECT count(distinct Score) FROM Scores WHERE Score >= s.Score) Rank
FROM Scores s
ORDER BY Score desc;

SELECT
  Score,
  (SELECT count(*) FROM (SELECT distinct Score s FROM Scores) tmp WHERE s >= Score) Rank
FROM Scores
ORDER BY Score desc;*/

-- 180
/*
Create table If Not Exists Logs (Id int, Num int);
Truncate table Logs;
insert into Logs (Id, Num) values ('1', '1');
insert into Logs (Id, Num) values ('2', '1');
insert into Logs (Id, Num) values ('3', '1');
insert into Logs (Id, Num) values ('4', '2');
insert into Logs (Id, Num) values ('5', '1');
insert into Logs (Id, Num) values ('6', '2');
insert into Logs (Id, Num) values ('7', '2');

SELECT  DISTINCT N1 AS ConsecutiveNums FROM (SELECT L1.Id, L1.Num AS N1, L2.Num AS N2, L3.Num AS N3
FROM Logs L1
JOIN Logs L2
ON L1.Id + 1 = L2.Id
JOIN Logs L3
ON L1.Id + 2 = L3.Id) temp
WHERE N1 = N2 AND N2 = N3*/

-- 181
/*
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, ManagerId int);
Truncate table Employee;
insert into Employee (Id, Name, Salary, ManagerId) values ('1', 'Joe', '70000', '3');
insert into Employee (Id, Name, Salary, ManagerId) values ('2', 'Henry', '80000', '4');
insert into Employee (Id, Name, Salary, ManagerId) values ('3', 'Sam', '60000', 'None');
insert into Employee (Id, Name, Salary, ManagerId) values ('4', 'Max', '90000', 'None');

SELECT E1.Name AS Employee FROM Employee E1
JOIN Employee E2
ON E1.ManagerId = E2.Id AND E1.Salary > E2.Salary */

-- 182
/*
Create table If Not Exists Person (Id int, Email varchar(255));
Truncate table Person;
insert into Person (Id, Email) values ('1', 'a@b.com');
insert into Person (Id, Email) values ('2', 'c@d.com');
insert into Person (Id, Email) values ('3', 'a@b.com');

SELECT Email FROM Person
GROUP BY Email
HAVING COUNT(*) > 1;*/

-- 183
/*
Create table If Not Exists Customers (Id int, Name varchar(255));
Create table If Not Exists Orders (Id int, CustomerId int);

SELECT Name AS Customers FROM
(SELECT C.Id, C.Name, O.Id AS OID FROM Customers C LEFT JOIN Orders O ON C.Id = O.CustomerId) temp
WHERE temp.OID IS NULL
 */

-- 184
/*
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, DepartmentId int);
Create table If Not Exists Department (Id int, Name varchar(255));

SELECT D.Name AS Department, E2.Name AS Employee, E2.Salary FROM Employee E2
JOIN
(SELECT E1.DepartmentId, MAX(Salary) AS Salary FROM Employee E1
GROUP BY DepartmentId) maxSalary
ON E2.DepartmentId = maxSalary.DepartmentId AND E2.Salary = maxSalary.Salary
JOIN Department D on E2.DepartmentId = D.ID*/

-- 185
Create table If Not Exists Employee (Id int, Name varchar(255), Salary int, DepartmentId int);
Create table If Not Exists Department (Id int, Name varchar(255));

SELECT D.Name AS Department, Erank.Name AS Employee, Erank.Salary FROM
(SELECT *, DENSE_RANK() over (PARTITION BY DepartmentId ORDER BY Salary DESC ) AS Srank FROM Employee) Erank
JOIN Department D ON D.Id = Erank.DepartmentId
WHERE Erank.Srank < 4




