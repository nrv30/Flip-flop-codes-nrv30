import sys

def categorize(color):
    return \
    (
        "RED" if color[0] > color[1] 
                     and color[0] >  color[2] 
                     and color[1] != color[2] else "GREEN" 
                     if color[1]  >  color[0] 
                     and color[1] >  color[2]
                     and color[0] != color[2] else "BLUE" 
                     if color[2]  >  color[0] 
                     and color[2] >  color[1] 
                     and color[0] != color[1] else "SPECIAL"
    )

colors = []
colors_freq = {}
types = {"RED" : 0, "GREEN" : 0, "BLUE" : 0, "SPECIAL": 0}

if __name__ == '__main__':
    print(f'{sys.argv[1]}')
    with open(sys.argv[1], 'r') as f:
        for line in f:
            colors.append(tuple(line.strip().split(',')))

    # part 1
    for color in colors:
        if color not in colors_freq:
            colors_freq[color] = 1
        else:
            colors_freq[color] += 1
    max_key = ()  
    max_freq = 0
    for color in colors_freq:
        if colors_freq[color] > max_freq:
            max_key = color
            max_freq = colors_freq[color]
    print (max_key)
    
    # part2
    for color in colors:
        types[categorize(color)] += 1
    print(types["GREEN"])

    # part3
    print(types["RED"] * 5 + types["GREEN"] * 2 + types["BLUE"] * 4 + types["SPECIAL"] * 10)