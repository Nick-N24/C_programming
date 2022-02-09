Nicholas Newton
lab 11 mini project

some info on grame mechanics (not all of them)

using gfx2, I noticed sometimes there is flickering in specific parts, but it does not affect the program at all

the accuracy is based on click events, it also increases the total clicks when the ball is not hit after 4 seconds

after 4 seconds and no hit, the ball resets position and decreases a second off the timer

the timer was setup based on the usleep value
	the target was moving well with usleep set in the program (.01 seconds), so the timer adds .01, but only displays non-decimal values, so it doesnt change until a second has passed

when red is hit under 10 seconds, 2 seconds are added to the timer
when yelllow is hit under 10 seconds 1 second is added to the timer

the target hitting machanics was as close I could get it with the computing speed
to hit properly, aim towards the front part of the target where it is moving, if doing this, the hit within the ring should work

the target moves at a random velocity from a random position after every reset

the program is written so it can be played multiple times without ending and re-running it. It always has a way to loop back to the title, which also resets the game variables
also, each screen is written with while loops and gfx_event_waiting(), this is intended so that animations and such could be added later without needing to edit the loop

>highscore mechanics
reading and writing is used with hardcoded "highscore.txt" which is used to save the values when the program ends
the highscores file is included, it is read into the struct starting with index 1 when the end screen is called
the current player struct values are stored in the 0 index
the new score is copied to the end of the struct
the file is then sorted with the new score and printed
this sorted version is also saved from index 1 to the end. it overwrites the previous highscore.txt file

this program can also be easily altered to remove the target motion and aim at still targets, just remove the velocity/motion component and set the no-hit timer to a lower number
