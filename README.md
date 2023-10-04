# pwbot
A simple bot for Perfect World 1.3.6 . 

Please keep in mind that this bot uses a very old bot technique (for exmaple, MHS-Bot-PW uses it), which was fixed a long time ago, so you won't be able to use it in modern Perfect World, only on some ancient custom servers. This program is just a backend, still needs GUI.

What's done:
- retrieving character info (HP, MP, Target, etc.) from client's memory
- composing moblist and saving it into file
- attacking mobs from moblist

TODO:
- GUI
- handle low HP, MP situations
- attempt to port it to newer Perfect World versions (the most difficult part)

How to use pwbot:
- Open this project on Windows in Code::Blocks and build the project
- IMPORTANT: Please make sure that your Perfect World is ancient enough (1.3.6 or older) and doesn't have any anticheat software built-in. As of 2023, I'm unsure that pure 1.3.6 servers still exist. Most of those "1.3.6" servers are actually 1.5.0+ servers with some content cut to mimick 1.3.6. So pwbot will NOT work on those servers.
- Start your PW client
- Make sure that window title is "Element Client" (or you can change to yours in main.c and rebuild project)
- Log in and enter the game world
- Start pwbot executable with administrator rights
- The pwbot will try to connect to PW client. If it failed, you'll see an error message in console
- If pwbot succeded, you'll see "Awaiting target..." message. This means that pwbot successfully connected to PW client and waits for you to set target on any mob in the game
- Alternately target 5 mobs in game. This will compose a list of mobs which pwbot will use to get targets from
- After that mob list is ready. Press any key to start pwbot
- Done! Now the bot should set targets to mobs from moblist and use skill set at F1 button.
