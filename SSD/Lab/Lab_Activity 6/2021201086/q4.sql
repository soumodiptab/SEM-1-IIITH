USE `COMPANY`;
WITH temp as
(
SELECT Essn
    FROM DEPENDENT
    WHERE Sex='F'
    GROUP BY Essn
    HAVING count(*)>=2
)
SELECT
d.Dnumber AS 'Dept. Id',
d.Dname AS 'Dept. Name',
count(loc.Dlocation) AS 'Number of locations'
FROM DEPARTMENT d, DEPT_LOCATIONS loc
WHERE 
d.Dnumber=loc.Dnumber 
and d.Mgr_ssn IN(
select * from temp
)
GROUP BY loc.Dnumber;
