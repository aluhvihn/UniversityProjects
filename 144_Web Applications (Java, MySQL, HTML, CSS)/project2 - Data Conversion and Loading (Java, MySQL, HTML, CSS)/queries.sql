/* Find the number of Users in the database. */
SELECT COUNT(*)
FROM Users;

/* Find the number of items in "New York", (i.e., items whose location is exactly the string "New York"). Pay special attention to case sensitivity. You should match the items in "New York" but not in "new york". */
SELECT COUNT(u.UserID)
FROM Users AS u INNER JOIN Items AS i
ON i.SellerID = u.UserID
WHERE BINARY u.Location = 'New York';

/* Find the number of auctions belonging to exactly four categories. */
SELECT COUNT(*) 
FROM   (SELECT ItemID 
        FROM   ItemCategories
        GROUP BY ItemID
        HAVING (Count(Category) = 4)) as T;

/* Find the ID(s) of current (unsold) auction(s) with the highest bid. Remember that the data was captured at the point in time December 20th, 2001, one second after midnight, so you can use this time point to decide which auction(s) are current. Pay special attention to the current auctions without any bid. */
SELECT ItemID
FROM Items 
WHERE Number_of_Bids > 0 AND Currently = (SELECT MAX(Currently)
														              FROM Items
														              WHERE Number_of_Bids > 0 AND
														              Ends > UNIX_TIMESTAMP('2001-12-20 00:00:00'));

/* Find the number of sellers whose rating is higher than 1000. */
SELECT COUNT(DISTINCT u.UserID)
FROM Users AS u INNER JOIN Items AS i
ON u.UserID = i.SellerID
WHERE u.Rating > 1000;

/* Find the number of users who are both sellers and bidders. */
SELECT COUNT(DISTINCT i.SellerID)
FROM Items AS i INNER JOIN Bids AS b
ON i.SellerID = b.UserID;

/* Find the number of categories that include at least one item with a bid of more than $100. */
SELECT COUNT(DISTINCT Category)
FROM ItemCategories AS c INNER JOIN Items AS i
ON c.ItemID = i.ItemID
WHERE Number_of_Bids > 0 AND Currently > 100;