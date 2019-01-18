.name       "ex"
.comment    "excom"

p1: live %-1
    ld %23,r2
    fork %:p2
    fork %:p2

p2: sti r2,%24,%24
    ld %42,r2
    live %-1
    fork %:p3

p3: sti r2,%24,%24
    ld %36,r2
