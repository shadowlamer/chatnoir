const fs = require('fs');

let data = Buffer.alloc(2048);

var screen = fs.readFileSync('../images/walls.scr');

const SCREEN_CHAR_WIDTH = 32;
const wallSizes = [4, 3, 2, 2, 1, 1, 1, 1];

let spritePos = 0;
let result = "";

let c = 0;

let width = 0;
let pos = 0;

for (distance = 0; distance<8; distance ++) {
    pos = spritePos;
    width = wallSizes[distance];
    
    for (i = 0; i < 64; i++) {
        if (((pos >> 5) & 0x07) >= distance) {
            for (j=0; j<width; j++) {
		result += screen.readUInt8(pos+j) + ", "
		c++;
		if (c >= 16) { 
		    result += "\n";
		    c = 0;
		}
	    }
	}
        pos += SCREEN_CHAR_WIDTH;
    }
    for (i = 0; i < 64; i++) {
        if (((pos >> 5) & 0x07) <= (7 - distance)) {
            for (j=0; j<width; j++) {
		result += screen.readUInt8(pos+j) + ", "
		c++;
		if (c >= 16) { 
		    result += "\n";
		    c = 0;
		}
	    }
	}
        pos += SCREEN_CHAR_WIDTH;
    }
    spritePos += width;
    result += "\n";
}

console.log ("const unsigned char bush0[] = {")
console.log(result);
console.log ("};");