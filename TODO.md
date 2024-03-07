- [ ] quote ' ' " "
- Additional feature: dquote

## LUCAS HOMEWORK (becoz he didnt ask sin liang to speedrun)
1. FIX DA MEM LEAKS []
2. DO THE $ sign brrrr [x]
3. Integrate tokenizer with AST [x]
4. ping me (100 years later due to no china power)

1. Expand Dollar Sign (NOT $(echo...))
2. Build AST (DO NOT Convert to left right node)
3. Traverse, identify $(echo...)
4. If exist, run the lowest one, then redirect to replace the current $()
FOR EXAMPLE:
wc -l | $(echo $(ls))
run ls first, then redirect ls output to a variable (current_node -> cmd)
wc -l | $(echo Makefile  README.md  TODO.md  includes  lib  minishell  objs  srcs  test.c  test1.py  testing.c)
run echo..., then redirect its output to variable
wc -l | Makefile  README.md  TODO.md  includes  lib  minishell  objs  srcs  test.c  test1.py  testing.c
5. Only then, contact sin liang for further wisdom instructions (enlightments)