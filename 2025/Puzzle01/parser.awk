function peek(str, i, n) {
    if (i + 1 > n) {
        return 0
    } 
    return substr($0, i + 1, 1)
}

{
    counter = 0
    n = length($0)
    i = 1
    while (i <= n) {
        c = substr($0, i, 1)
        if (c == "b") {
            nextc = peek($0, i, n)
            if (nextc == "a") {
                i += 2
                counter += 1
            } else {
                i += 1
            }
        } else if (c == "n") {
            nextc = peek($0, i, n) 
            if (nextc == "a") {
                counter += 1
                i+=2
            } else if (nextc == "e") {
                counter = 0
                break
            } else {
                i += 1
            }
        } else {
            i += 1
        }
    }
    sum += counter
}

END {
    print sum
}