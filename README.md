0x16. C - Simple Shell

Collaborator: Promise Tshepiso

It handlse the “end of file” condition (Ctrl+D) implement built-ins(exit, env, etc). handle special characters : ", ', `, , *, &, #, ||, && able to move the cursor. handle commands with arguments. Handle variables replacement Handle comments (#) take a file as a command line argument The prompt is displayed again each time a command has been executed.(Simple shell 0.1) The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.(Simple shell 0.1) The command lines are made only of one word. No arguments will be passed to programs.(Simple shell 0.1) If an executable cannot be found, print an error message and display the prompt again. Handle errors.

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output. The only difference is when you print an error, the name of the program must be equivalent to your argv[0]
