WITH RECURSIVE cte AS (
    SELECT 
        point1, 
        point2, 
        cost, 
        1 AS depth, 
        ARRAY[point1] AS path, 
        ARRAY[cost] AS total, 
        false AS cycle
    FROM nodes
    WHERE point1 = 'a' 
UNION ALL
    SELECT 
        n.point1, 
        n.point2, 
        n.cost + c.cost AS cost, 
        c.depth +1 AS depth, 
        c.path || n.point1 AS path, 
        c.total || n.cost  AS total, 
        n.point1 = ANY (c.path) AS cycle 
    FROM nodes n
    JOIN cte c ON n.point1 = c.point2 AND NOT cycle
),
num_nodes AS (
    SELECT count(*) + 1 AS num
              from (SELECT COUNT(*) AS num 
                    FROM nodes 
                    GROUP BY point1) d1),
full_path AS (
    SELECT cost - total[(SELECT num FROM num_nodes)] AS total_cost, path AS tour 
            FROM cte
            WHERE path[1] = path[5] AND depth = (SELECT num FROM num_nodes)
)

SELECT total_cost, tour::text
    FROM full_path
    WHERE total_cost = (SELECT min(total_cost) FROM full_path)
    GROUP BY 1, 2
    UNION ALL
    SELECT total_cost, tour::text 
    FROM full_path
    WHERE total_cost = (SELECT max(total_cost) FROM full_path)
    GROUP BY 1, 2
    ORDER BY 1, 2;