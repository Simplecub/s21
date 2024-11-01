CREATE INDEX IF NOT EXISTS idx_person_name ON person(UPPER(name));
SET enable_seqscan = off;
EXPLAIN ANALYZE 
Select *
from person
WHERE UPPER(name) = 'KATE';