# OJ-Neural-Net
A project aiming to somewhat accurately recreate the systems of the game 100% Orange Juice (as it was in 2009) and allow a neural network to play it, as a CLI.
This does not use any content from the game other than text contents (such as the description of cards), and this is not an attempt to cheat the game; this is purely a simulation made for the purpose of me experimenting with neural networks.

# Progress:
Systems -- 90%
The systems that make up the underlying game logic. This is the definitions and functions of the cards, units, enemies, etc.

Game -- 0%
The playable game. Should be very quick to implement after the systems are at 100%.

Neural Network -- 0%
Progress on making the neural network that can play the game.

Training -- 0%
Progress on training the neural network.

Overall -- 30%
How much I estimate is finished.

# Questions
"Why are you doing this?"
I'm interested in neural networks as AI opponents in videogames. I want to make a game one day, and I don't trust deterministic AI opponents to be able to accurately replicate the intricacies of real player-vs-player combat.

"How will you measure its performance?"
I have programmed a "random" AI opponent that picks completely random choices. If the neural network regularly outperforms the AI opponent, this project will be considered a success.
A proper statistical hypothesis test will be conducted when the training is done.

"Why are there so many pointers?"
This was programmed so most of the functions besides a class' own getters are side-affecting void functions. Passing by reference or by pointer was necessary for this system design to work. I probably should've used a pass-by-reference design, but I chose pointers.

"Was AI involved in programming?"
No. Not at all.

# Agent Task Definition
The environment is multi-agent, nondeterministic, static, continuous, and sequential. The environment is partially observable in that the agents do not know the cards in the hands of the other players, but since these are fully unobservable in most circumstances, we don't keep a belief state of it.
WIP
