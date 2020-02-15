var w: i32;
var h: i32;

@inline
function get(x: u32, y: u32): u8 {
    return load<u8>(y * w + x);
}

/** Sets an output pixel in the range [s, 2*s]. */
@inline
function set(x: u32, y: u32, v: u8): void {
    store<u8>(y * w + x, v);
}

/** Initializes width and height. Called once from JS. */
export function init(width: i32, height: i32): void {
    w = width;
    h = height;

    var color: u8 = 0;
    // Start by filling output with random live cells.
    for (let y = 0; y < h; ++y) {
        for (let x = 0; x < w; ++x) {
            set(x, y, color);
        }
        color+=2;
    }
}
