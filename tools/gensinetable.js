const PI=3.141522654
const tableSize = 256;

let table = [];

for (i = 0; i < tableSize; i++) {
  let angle = (PI * 2 / tableSize) * i;
  let sine = Math.round(Math.sin(angle) * 127);
  table[i] = sine;
}

let result = "const char sine[] = {" + table.join(", ") + "};";

console.log(result);