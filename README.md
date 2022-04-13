# MarketMaker
A text-based trading game. You play as a market maker and quote prices to bots, each with a unique strategy.

I created this game to prepare for prop trading interviews.

Rules:
- Each player rolls a die and keeps the number private. 
- At the start of each round, a die visible to all players is rolled.
- Players trade a contract that has a value equal to the sum of all private and public dice. The contract settles at the end of the game.
- You are a market maker and are obligated to provide two-sided quotes. The bots are market takers and don't trade with each other.
- When multiple bots want to trade, one is chosen uniformly at random.
- You are given the opportunity to adjust your quotes after each trade.
- The round ends when nobody wants to trade (or when a hard cap on the number of trades is reached).
- At the end of the game, you are prompted to input your final position. Keeping track of this is an exercise to help prepare for interviews.

The following game settings can be adjusted:
- The number of sides on each die.
- The number of rounds.
- The maximum number of trades each round.

Future features:
- A countdown encouraging you to act fast.
- More intelligent bots.
- Bot speed variable (randomly generated) which influences the probability the bot gets the trade.
