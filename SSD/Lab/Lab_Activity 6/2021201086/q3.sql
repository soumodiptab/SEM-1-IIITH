USE `COMPANY`;
SELECT Essn as 'Manager ssn',
COUNT(Pno) as 'Number of projects'
FROM WORKS_ON WHERE Essn=(
    SELECT Mgr_ssn
    FROM DEPARTMENT
    WHERE Dnumber=
    (SELECT Dnum FROM PROJECT WHERE Pname='ProductY')
) GROUP BY Essn;
