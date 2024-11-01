CREATE TABLE IF NOT EXISTS nodes  (
  point1 VARCHAR,
  point2 VARCHAR,
  cost INTEGER
);


INSERT INTO nodes (point1, point2, cost)
VALUES
  ('a', 'b', 10),
  ('b', 'a', 10),
  ('a', 'c', 15),
  ('c', 'a', 15),
  ('a', 'd', 20),
  ('d', 'a', 20),
  ('b', 'd', 25),
  ('d', 'b', 25),
  ('d', 'c', 30),
  ('c', 'd', 30),
  ('b', 'c', 35),
  ('c', 'b', 35);

WITH RECURSIVE routs AS(
    SELECT DISTINCT
        nodes.point1 "point", 
        nodes.point1 "path", 
        0 "cost"
    FROM 
        nodes
    WHERE 
        point1='a'

    UNION ALL

    SELECT
        nodes.point2, 
        CONCAT(routs.path, ',' , nodes.point2), 
        routs.cost+nodes .cost
    FROM
        routs
        JOIN
        nodes 
        ON 
        routs.point=nodes.point1
    WHERE 
        routs.path NOT LIKE CONCAT('%', nodes .point2, '%') AND 
        LENGTH(path)<6
),

tours AS(
    SELECT 
        r.cost+e.cost "total_cost", 
        concat('{', r.path, ',' ,e.point2, '}') "tour"
    FROM
        (SELECT 
            * 
        FROM 
            routs
        WHERE 
            LENGTH(path)=(SELECT max(LENGTH(path)) FROM routs)) AS r
            JOIN
            nodes AS e
            ON 
            r.point=e.point1
        WHERE e.point2='a'

    ORDER BY total_cost, tour
)

-- ex00

SELECT * FROM tours
WHERE total_cost=(SELECT MIN(total_cost) FROM tours)

-- ex01

-- SELECT *
-- FROM
-- (SELECT * FROM tours
-- WHERE total_cost=(SELECT MIN(total_cost) FROM tours))
-- UNION
-- (SELECT * FROM tours
-- WHERE total_cost=(SELECT MAX(total_cost) FROM tours))