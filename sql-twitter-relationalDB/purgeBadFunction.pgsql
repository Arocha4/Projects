CREATE OR REPLACE FUNCTION purgeBadFunction(censorLimit integer) 
    RETURNS integer AS $$
    DECLARE
    -- badUserID is used to update the tables
    -- deleteCount keep track of deleted users
        badUserID INTEGER;
        deleteCount INTEGER;
    -- We use a cursor to keep track of the set of bad users
    DECLARE badUsers CURSOR FOR
        SELECT posterID
        FROM ChirpPosts
        WHERE censored 
        GROUP BY posterID
        HAVING COUNT(*) > censorLimit;
    BEGIN
        deleteCount := 0;
        OPEN badUsers;
        -- Loops through the cursor
        LOOP
            -- Get each badUserID
            FETCH badUsers INTO badUserID;
            -- If cursor is empty, exit the loop
            EXIT WHEN NOT FOUND;
            -- Increase the count
            deleteCount := deleteCount + 1;
            
            DELETE FROM ChirpUsers 
                WHERE userID = badUserID;
            UPDATE ChirpUsers 
                SET spouseID = NULL 
                WHERE spouseID = badUserID;
            DELETE FROM ChirpPosts 
                WHERE posterID = badUserID;
            DELETE FROM ChirpFollowers 
                WHERE userID = badUserID 
                    OR followerID = badUserID;

        -- Note : The order of DELETE statements can be changed
        -- Note : The DELETE statement on ChirpFollowers can be split into
        -- 2 DELETE statmenets
        END LOOP;
        -- Close the cursor
        CLOSE badUsers;
        RETURN deleteCount;
    END;
    $$ LANGUAGE plpgsql;