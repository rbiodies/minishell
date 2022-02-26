# Minishell
### ***The aim of the project is:***
To write a shell. This project is about creating own bash and learning a lot about processes and file descriptors. Shell should:
- Handle ’ (single quote).
- Handle " (double quote).
- Implement ;.
- Implement redirections (<, >, <<, >>).
- Implement pipes (| character).
- Handle environment variables ($ followed by a sequence of characters).
- Handle $?.
- Handle ctrl-C, ctrl-D and ctrl-\.
- Implement the following builtins:
  - echo -n
  - cd
  - pwd
  - export
  - unset
  - env
  - exit
### ***Run:***
```
$> make readline
```
>To install GNU Readline. GNU Readline is a software library that provides line-editing and history capabilities for interactive programs with a command-line interface, such as Bash. The function readline () prints a prompt and then reads and returns a single line of text from the user.
```
$> make
$> ./minishell
~/minishell$
```
### Have fun with that beautiful minishell and enjoy it!
