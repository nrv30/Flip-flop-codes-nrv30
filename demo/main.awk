{
    sum += strtonum($0)
    n = length($0)
    for (i = 1; i <= n; i++) {
        c = strtonum(substr($0, i, 1))
        digits[c+1]+=1
    }
    numbers[strtonum($0)]+= 1
}

END {
    min = 1
    min_val = digits[1]
    for (i = 2; i <= 10; i++) {
        if (digits[i] < min_val) {
            min_val = digits[i]
            min = i
        }
    }
    print "The minimally frequent digit is " min-1 " it's value was " min_val

    started = 0
    max = 0
    max_freq
    for (num in numbers) {
        if (!started) {
            max_freq = numbers[num]
            max = num
            started = 1
        } else {
            if (numbers[num] > max_freq) {
                max_freq = numbers[num]
                max = num
            }
        }
    }

    print "answer in part 1 is " sum

    print "The maximally frequent number is " max " it occured " max_freq " number of times"

    print "The answer is " max min-1

    
}