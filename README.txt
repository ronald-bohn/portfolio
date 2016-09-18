

/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * NAME: Portfolio (v0.5)
 *  
 * AUTHOR: Ronald Bohn
 *  
 * PURPOSE: Demonstrate my capacity to code and document that code accordingly
 *  
 * STATUS: All of the methods are complete and work. Not all of my code is completely bug-free (but what code really
 *  is?) because I am both the creator and the client, so I can prevent pathological inputs by way of plot-armor, 
 *  and also because I wanted to showcase my understanding of a variety of concepts and my capacity to write *clean*
 *  and "chic" code. While I could have included a larger number of input sanitization methods and the like, I opted
 *  not to since -being the only "client" of my libraries -I have no need to worry about pathological inputs, and 
 *  I figured that the reduction of clutter would make my code overall more readable and give you a better taste
 *  for my capabilities. As a result, I only did input sanitization when it was absolutely necessary or when I felt
 *  it could potentially save me stress down the road due to typos and similar human errors. I hope that you find
 *  The code to be as visually pleasing and novel as it was for me to write it. =)
 *  
 * NOTES: I have defined a number of C macros in the header file "useful_definitons.h" in the "utils" folder. I use 
 *  most these for my functions which could have been void return types, but which I made int return types instead. 
 *  I do this because some functions may not have an explicit output, but being able to return a variety of 
 *  different values allows me to diagnose their problems more easily than checking register flags. As a result, I 
 *  wanted to define a convention which would allow me to quickly and easily identify which parts of a method broke 
 *  down. You can take a look at this file if you would like, but in general, the macros should* be fairly 
 *  descriptive about what kind of error is ocurring. 
 *  
 *  Additionally, it should be noted that I may do some unconventional things in this program which are 
 *  outside of convention. I typically do these things either to demonstrate an academic principle 
 *  or to make my code more readable. Last but not least, I am aiming to include a web-crawler component
 *  soon. In conjunction with the things I said about error-checking, it may not be a good idea to redirect any 
 *  output from that component to stdout in front of a classroom full of kids, because even if your starting point
 *  is Princeton University's homepage, you will soon remember that the internet is a bad place, and likewise, it
 *  would be quite impossible for me to screen every individual domain for "bad" content and with this being more
 *  of a demonstration than a piece of software being shipped off to paying clients, I felt my time was better 
 *  divided elsewhere. I hope you enjoy what you see, and if you have any questions or comments, shoot me an email
 *  (or 2!) to ronald.bohn@yahoo.com, and I will try to answer as quickly as possible. 
 *  
 *  Last but not least, as of the writing of this sentence, this portfolio is incomplete. The created libraries are
 *  tested and work, but have not yet been bonded in any meaningful way. You can still view the code and modify it
 *  to test the methods to yourself, however. The next section does not apply to versions lower than v1.0
 * 
 * INSTALLATION/EXECUTION: In your preferred shell, simply type "make" or if on a Unix-based system, type 
 *  "./configure". To run the program, simply type "./portfolio".
 *  
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


