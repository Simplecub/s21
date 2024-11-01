
CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop int DEFAULT 10)  
RETURNS TABLE (num_fib int) AS $$
  WITH RECURSIVE num_fibonacci AS (
      SELECT 0 AS current_num, 1 AS next_num
      UNION ALL
      SELECT 
        next_num as current_num,
        next_num + current_num AS next_num
        FROM num_fibonacci
        WHERE next_num < pstop
  )
  SELECT current_num FROM num_fibonacci;
$$ LANGUAGE SQL;


select * from fnc_fibonacci(100);
select * from fnc_fibonacci();