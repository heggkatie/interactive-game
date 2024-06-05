# interactive-game
This is a repository for my ENGR103 final

Game Description:

This is a game where, depending on the prompt from the circuit, you must complete the task, whether by pressing a button or increasing the sound levels. Each level comprises a random 5 sequences and increases in difficulty after each round. There are 5 rounds in total. The increase in difficulty decreases the time you have to complete the task. If you fail a level, the board says, “Game Over,” and you lose. You can pause the game by using the switch.

Rules
- Speed increases at each level
- Flipping the switch pauses the game (change)

Outputs      ->    Inputs
- blue LED     ->    press the left button
- green LED    ->    press the right button
- red LED      ->    increase the temperature (the threshold is the observed temperature + 5)
- yellow LED   ->    increase the sound (the threshold is the observed soundLevel + 10)
