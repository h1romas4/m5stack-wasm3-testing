import * as m5stack from "./arduino";

var width: u32, height: u32;

/** Gets an input pixel in the range [0, s]. */
// @inline
// function pget(x: u32, y: u32): u8 {
//     return load<u8>(y * width + x);
// }

/** Sets an output pixel in the range [s, 2*s]. */
// @inline
// function pset(x: u32, y: u32, v: u8): void {
//     store<u8>(y * width + x, v);
// }

export function draw(w: u32, h: u32): void {
    width  = w;
    height = h;
    let hWidth  = w / 2;
    let hHeight = h / 2;
    for (let r: u32 = 0; r < hWidth; r++) {
        circle(hWidth, hHeight, r, <u8>m5stack.random(256));
    }
}

function circle(x: i32, y: i32, r: i32, color: u8): void {
    let xx  = r;
    let yy  = 0;
    let err = 0;
    let w   = width;
    let xyw = y * w + x;

    while (xx >= yy) {
        store<u8>(xyw + (yy * w + xx), color);
        store<u8>(xyw + (xx * w + yy), color);

        store<u8>(xyw + (xx * w - yy), color);
        store<u8>(xyw + (yy * w - xx), color);

        store<u8>(xyw - (yy * w + xx), color);
        store<u8>(xyw - (xx * w + yy), color);

        store<u8>(xyw - (xx * w - yy), color);
        store<u8>(xyw - (yy * w - xx), color);

        if (err <= 0) {
            yy++;
            err += 2 * yy + 1;
        } else {
            xx--;
            err -= 2 * xx + 1;
        }
    }
}
