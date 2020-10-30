# dining-philosophers
This is an exercise taken from the book "The Art of Multiprocessor Programming" by Maurice Herlihy and Nir Shavit.

The dining philosophers problem was invented by E.W.Dijkstra. 
Consider N philosophers who spend their lives just thinking and feasting. They sit around a circular table with 
N chairs. The table has a big plate of rice. However, there are only five chopsticks available. 
Each philosopher thinks. When he gets hungry, he sits down and picks up the two chopsticks that are closest to him.
if a philosopher can pick up both chopsticks, he can eat for a while. After a philosopher finishes eating, he puts down the 
chopsticks and again starts to think. 

This program simulates the behavior of the philosophers, where each philosopher is a thread and the chopsticks 
are shared objects. It shouldn't be possible for two philosophers to hold the same chopstick at the same time. At the same time,
no philosopher should starve. 