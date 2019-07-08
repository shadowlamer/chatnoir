const fs = require('fs');

let data = Buffer.alloc(2048);

var screen = fs.readFileSync('../images/font.scr');

const SCREEN_CHAR_WIDTH = 32;

let result = "";


for (let letter=0; letter<64; letter++) {
    pos = letter;
    for (line = 0; line < 8; line ++) {
	result += screen.readUInt8(pos) + ", ";
	pos+=256;
    }
    result += "\n"
}

console.log ("const unsigned char font1[] = {")
console.log(result);
console.log ("};");