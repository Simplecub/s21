DROP FUNCTION IF EXISTS fnc_persons_female, fnc_persons_male;

CREATE OR REPLACE FUNCTION fnc_persons(pgender varchar default 'female'  ) RETURNS TABLE
(
  id bigint ,
  name varchar,
  age integer,
  gender varchar,
  address varchar
)
 AS $$
    SELECT person.id, person.name, person.age, person.gender, person.address
    FROM person WHERE gender = pgender;
$$ LANGUAGE SQL;


select *
from fnc_persons(pgender := 'male');

select *
from fnc_persons();