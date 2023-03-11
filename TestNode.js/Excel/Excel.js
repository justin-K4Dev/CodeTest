//
// Excel
//

var Parser = require('parse-xlsx');

sheet = new Parser('./Excel/sample.xlsx', 'Transcript');

// get values in a column 
console.log('\nValues in column `XYZ`:', sheet.values('XYZ'), "\n");