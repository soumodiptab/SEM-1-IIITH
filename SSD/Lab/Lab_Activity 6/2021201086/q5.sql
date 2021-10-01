USE `COMPANY`;
WITH temp
 AS 
 (select 
 Dnumber 
 from DEPT_LOCATIONS 
 group by 
 Dnumber having count(*) > 1)
select
d.Essn as 'Manager ssn',
t.Dnumber as 'Dept. Id',
count(*) as 'No of Dependents'
from
DEPARTMENT t,
DEPENDENT d
where Mgr_ssn=Essn
group by Essn,t.Dnumber
having Essn in (select d.Mgr_ssn
from DEPARTMENT d,temp
where d.Dnumber = temp.Dnumber);
