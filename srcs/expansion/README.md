COMMAND "expr $? + $?"

EXPECTED OUTPUT
(exit_status) + (exit_status)

OUR OUTPUT
expr doesnt execute register non-integer input

REASON
there's a space after the first $? exit status value
