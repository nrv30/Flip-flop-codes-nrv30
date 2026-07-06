function adjust(temp, target) 
{
    if (temp > target) {
        return (temp - target) * COOL_RATE
    } else if (temp < target) {
        return (target - temp) * HEAT_RATE
    }
}

BEGIN \
{
    MIN_TEMP = 60
    HEAT_RATE = 1
    COOL_RATE = 5

    # passed as command-line arg
    EMPLOYEES_COUNT = file_length / 2
    print "EMPLOYEES_COUNT " EMPLOYEES_COUNT
    sum = 0
    curr_idx = 1
    flag = 0
}

{
    temp = strtonum($0)
    if (flag == 0 && curr_idx <= EMPLOYEES_COUNT) {
        temps[curr_idx] = temp
        curr_idx++
        next
    }

    if (flag == 0) {
        curr_idx = 1
        flag = 1
    }

    if (curr_idx <= EMPLOYEES_COUNT) {
        targets[curr_idx] = temp
        curr_idx++
    }
}

END \
{
    for (i = 1; i <= EMPLOYEES_COUNT; i++) {
        sum += adjust(temps[i], targets[i])
    } 
    print "Sum: " sum
}