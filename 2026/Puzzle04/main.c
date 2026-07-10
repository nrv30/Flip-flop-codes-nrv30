// flip flop codes day 4
// note: this code is meant to be compiled as plugins for Fred text editor
// it doesn't compile by itself
#define CUT_HEIGHT 400
DEF_PLUGIN_EDITOR_HOOK("Part1", "solves puzzle Part1", Part1) {
    Temp scratch = scratch_begin(NULL);
    
    uint64_t line_count = ed_line_count(ctx);
    uint64_t cut_line   = line_count - CUT_HEIGHT - 1;
    uint64_t counter    = 0;
    
    // iterate the lines form cut to head
    for (uint64_t line = cut_line; line > 1; --line) {
        EditorOffsetRange line_rng;
        ed_byte_range_at_line(ctx, line, &line_rng);
        String8 line_txt;
        
        // get the string and iterate it
        ed_string_at_range(scratch.arena, ctx, &line_rng, &line_txt);
        for (uint64_t i = 0; i < line_txt.size; ++i) {
            char c = line_txt.str[i];
            if (c == 'o') {
                counter++;
            } else if (c == '/') {
                break;
            }
        }
    }
    feed_queue_info(str8_fmt(scratch.arena, "%d", counter));
    scratch_end(scratch);
}

typedef enum SIDE {
    LEFT,
    RIGHT,
} SIDE;

DEF_PLUGIN_EDITOR_HOOK("Part2", "solves puzzle part 2", Part2) {
    Temp scratch = scratch_begin(NULL);
     
    uint64_t line_count     = ed_line_count(ctx);
    uint64_t counter        = 0;
    SIDE side;
    int32_t started         = 1;
    
    for (uint64_t line = line_count - 1; line > 1; --line) {
        SIDE curr_side;
        EditorOffsetRange line_rng;
        ed_byte_range_at_line(ctx, line, &line_rng);
        String8 line_txt;     
        
        // get the string and iterate it
        ed_string_at_range(scratch.arena, ctx, &line_rng, &line_txt);
        for (uint64_t i = 0; i < line_txt.size; ++i) {
            char c = line_txt.str[i];
            if (c == 'o') {
                if (i == line_txt.size-1) {
                    curr_side = RIGHT;
                } else {
                    curr_side = LEFT;
                }
                if (started == 1) {
                    started = 0;
                    side = curr_side;
                    continue;
                }
                
                if (curr_side != side) {
                    counter++;
                    side = curr_side;
                }
                
            } else if (c == '/') {
                break;
            }
        }
    }
    
    feed_queue_info(str8_fmt(scratch.arena, "%d", counter));
    
    scratch_end(scratch);
}

typedef struct Leaf {
    uint64_t line_number;
    int flag;
    SIDE side;
} Leaf;

typedef struct LeafArray {
    Leaf* array;
    uint64_t size;
    uint64_t capacity;
} LeafArray;

DEF_PLUGIN_EDITOR_HOOK("Part 3", "Solves part 3", Part3) {
    Temp scratch = scratch_begin(NULL);
    
    uint64_t line_count = ed_line_count(ctx);
    LeafArray leaves = {0};
    leaves.capacity = line_count - 1 - 3;
    leaves.array = push_array(scratch.arena, Leaf, leaves.capacity);
    
    // initialize the leaves
    for (uint64_t line = line_count - 1; line > 1; --line) {
        EditorOffsetRange line_rng;
        ed_byte_range_at_line(ctx, line, &line_rng);
        String8 line_txt;
        ed_string_at_range(scratch.arena, ctx, &line_rng, &line_txt);
        for (uint64_t i = 0; i < line_txt.size; ++i) {
            char c = line_txt.str[i];
            if (c == 'o') {
                if (i == line_txt.size-1) {
                    leaves.array[leaves.size] = (Leaf) {line, 1, RIGHT};
                } else {
                    leaves.array[leaves.size] = (Leaf) {line, 1, LEFT};
                }
                leaves.size++;
            }
        }
    }
        
    uint64_t counter;
    for (;;) {
        int started = 1;
        SIDE side;
        int prev_index = -1;
        int last_valid_index = -1;
        for (uint64_t i = 0; i < leaves.size; ++i) {
            // ignore fallen leaves
            if (leaves.array[i].flag == 0) {
                continue;
            }
            
            prev_index = last_valid_index;
            last_valid_index = i;
            
            SIDE newside = leaves.array[i].side;
            if (started == 1) {                
                side = newside;
                started = 0;
                continue;
            }
            
            // switching sides leaf must fall
            if (newside != side) {
                leaves.array[prev_index].flag = 0;
                feed_queue_info(str8_fmt(scratch.arena, "jumped on line_number %d", leaves.array[i-1].line_number));
                int str1 = (side == LEFT) ? 69 : 420;
                int str2 = (newside == LEFT) ? 69 : 420;
                feed_queue_info(str8_fmt(scratch.arena, "side is %d and newside is %d", str1, str2));
                side = newside;
                // swapped = 0;
            }
        }
        
        if (last_valid_index > 0) {
            feed_queue_info(str8_fmt(scratch.arena, "jumped to flower on line number %d", leaves.array[last_valid_index].line_number));
            leaves.array[last_valid_index].flag = 0;
        }
        
        // if there were no non-1 flags
        if (started == 1) {
            break;
        }
        
        counter++;
        feed_queue_info(str8_fmt(scratch.arena, "-----%d------", counter));
    }
    
    feed_queue_info(str8_fmt(scratch.arena, "%d", counter));    
    scratch_end(scratch);
}