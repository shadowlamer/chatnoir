const fs = require('fs');

let data = Buffer.alloc(2048);

var screen = fs.readFileSync('../images/ground.scr');

const SCREEN_CHAR_WIDTH = 32;

let spritePos = 0;
let result = "";

let c = 0;

let width = 8;
let pos = 0;

for (i = 0; i < 64; i++) {
    for (j=0; j<width; j++) {
        result += screen.readUInt8(pos+j) + ", "
	c++;
	if (c >= 16) { 
		    result += "\n";
		    c = 0;
	}
    }
        pos += SCREEN_CHAR_WIDTH;
}

console.log ("const unsigned char ground0[] = {")
console.log(result);
console.log ("};");