1. Relational Schema:

Items(ItemID, Name, Currently, Buy_Price, First_Bid, Number_of_Bids, Latitude, Longitude, Location, Country, Started, Ends, SellerID, Description)
	Key: ItemID

Users(UserID, Rating, Location, Country)
	Key: UserID

ItemCategories(Category, ItemID)
	Key: Category, ItemID

Bids(UserID, Time, ItemID, Amount)
	Key: UserID, Time

---------------------------------------------
2. Functional Dependencies:

ItemID -> Name, Currently, Buy_Price, First_Bid, Number_of_Bids, Latitude, Longitude, Location, Country, Started, Ends, SellerID, Description

UserID -> Rating, Location, Country

UserID, Time -> ItemID, Amount

---------------------------------------------
3. Yes, all my relations are in BCNF.

---------------------------------------------
4. Yes, all the relations are in 4NF.