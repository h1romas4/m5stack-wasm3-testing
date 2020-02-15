import * as m5stack from "./arduino";

var w: i32, h: i32, s: i32;

/** Gets an input pixel in the range [0, s]. */
@inline
function get(x: u32, y: u32): u8 {
    return load<u8>(y * w + x);
}

/** Sets an output pixel in the range [s, 2*s]. */
@inline
function set(x: u32, y: u32, v: u8): void {
    store<u8>(y * w + x, v);
}

export function init(width: i32, height: i32): void {
    w = width;
    h = height;

    // Start by filling output with random live cells.
    for (let y = 0; y < h; ++y) {
        for (let x = 0; x < w; ++x) {
            set(x, y, <u8>m5stack.random(256));
        }
    }
}
