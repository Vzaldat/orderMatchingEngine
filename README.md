Order Matching Engine written in CPP by Vishal Datta Budaraju

The Engine takes in the order which has following parameters -
    1. Id,
    2. Order Type
    3. Order Side
    4. Price
    5. Quantity
    6. Time of order 

The engine takes in multiple orders and matches them with the counter parts - Buy orders of a certain type go to sell orders of the same type etc.

There is a OrderBook class that handles the asks(sell) and bids(buys) and matches the asks to bids

There are multiple tests in test folder and maintaining a small UI from ncurses to place an order.

