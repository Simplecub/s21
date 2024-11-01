
CREATE OR REPLACE FUNCTION fnc_persons_female() RETURNS TABLE
(
  id bigint ,
  name varchar,
  age integer,
  gender varchar,
  address varchar
)
 AS $$
    SELECT person.id, person.name, person.age, person.gender, person.address
    FROM person WHERE gender = 'female';
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION fnc_persons_male() RETURNS TABLE
(
  id bigint ,
  name varchar,
  age integer,
  gender varchar,
  address varchar
)
 AS $$
    SELECT person.id, person.name, person.age, person.gender, person.address
    FROM person WHERE gender = 'male';
$$ LANGUAGE SQL;

select *
from fnc_persons_female(pgender := 'male');

select *
from fnc_persons_male();