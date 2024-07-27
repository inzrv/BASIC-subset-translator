# Compute average of given values.

PRINT "Input n"
INPUT n

IF n < 0 THEN
    PRINT "n should be greater than or equal to 0"
ENDIF

LET f1 = 0
LET f2 = 1
WHILE n > 0 REPEAT
    LET tmp = f1 + f2
    LET f1 = f2
    LET f2 = tmp
    LET n = n - 1
ENDWHILE
PRINT f1