USE `COMPANY`;
WITH temp
AS
(SELECT super_ssn,
COUNT(*) AS super_count
FROM EMPLOYEE
WHERE super_ssn IS NOT NULL
GROUP BY super_ssn),
temp2 AS
(SELECT 
CONCAT(fname, ' ', minit, ' ', lname) AS fullname,
ssn ,
super_count,
Dno
FROM EMPLOYEE, temp
WHERE ssn = temp.super_ssn)
select
fullname as 'Full name',
ssn,
Dname as 'Dept. Name',
super_count as 'Number of employees'
from temp2,DEPARTMENT
where
Dno=Dnumber
ORDER BY super_count;
