1) I used SSL encryption for communications (4)->(5) and (5)->(6).

2) I stored the all of the data for the corresponding item being bought in
the attribute 'itemBuying' for the servlet sessions to have access to.
Whenever the Buy_Price and other fields of the item are needed to populate
a page, they are retreived from the 'itemBuying' attribute and set as
readonly values on the page. This means that only the credit card
information is passed as a POST parameter, while encrypted in SSL.