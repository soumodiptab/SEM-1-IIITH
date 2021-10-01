USE `COMPANY`;
WITH 
temp AS
(SELECT Essn as e from WORKS_ON),
temp2 AS
(SELECT DISTINCT Dno from EMPLOYEE,temp where Ssn=temp.e)
SELECT  concat(m.Fname,' ',m.Minit,' ',m.Lname) AS 'Full name',
m.Ssn AS 'ssn',
m.Dno AS 'Dept. Id',
d.Dname AS 'Dept. Name'
from EMPLOYEE m,DEPARTMENT d,temp2
WHERE d.Dnumber=temp2.Dno
AND m.Ssn = d.Mgr_ssn;
