/**
 * Created by justin on 2016-02-27.
 */

// export

// ECMAScript 2015 (6th Edition, ECMA-262)
// The definition of 'Imports' in that specification.

// Syntax
// export { name1, name2, ・, nameN };
// export { variable1 as name1, variable2 as name2, ・, nameN };
// export let name1, name2, ・, nameN; // also var
// export let name1 = ・, name2 = ・, ・, nameN; // also var, const
//
// export default expression;
// export default function (・) { ・ } // also class, function*
// export default function name1(・) { ・ } // also class, function*
// export { name1 as default, ・ };
//
// export * from ・;
// export { name1, name2, ・, nameN } from ・;
// export { import1 as name1, import2 as name2, ・, nameN } from ・;

// Description
// There are two different types of export, each type corresponds to one of the above syntax:
//
// Named exports:
//      export { myFunction }; // exports a function declared earlier
//      export const foo = Math.sqrt(2); // exports a constant
// Default exports (only one per script):
//      export default function() {} // or 'export default class {}'
//      there is no semi-colon here

// Using named exports
// In the module, we could use the following code:
//
// module "my-module.js"
export function cube(x) {
    return x * x * x;
};
const foo = Math.PI + Math.SQRT2;
export { foo };
//
// This way, in another script (cf. import), we could have:
//
// import { cube, foo } from 'my-module.js';
// console.log(cube(3)); // 27
// console.log(foo); // 4.555806215962888

// Using the default export
//
// If we want to export a single value or to have a fallback value for our module, we could use a default export:
//
// module "my-module.js"
export default function (x) {
    return x * x * x;
}
//
// Then, in another script, it will be straightforward to import the default export:
//
// module "my-module.js"
// import cube from 'my-module';
// console.log(cube(3)); // 27



