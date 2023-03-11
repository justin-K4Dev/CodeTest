
/*
 * Writing to Buffers
 */ 
{
    var buf1 = new Buffer(10);
    var buf2 = new Buffer([10, 20, 30, 40, 50]);
    var buf3 = new Buffer("Simply Easy Learning", "utf-8");

    var buf4 = new Buffer(256);
    len = buf4.write("Simply Easy Learning");

    console.log("Octets written : " + len);
}


/*
 * Reading from Buffers
 */
{
    var buf = new Buffer(26);
    for (var i = 0; i < 26 ; i++) {
        buf[i] = i + 97;
    }
    
    console.log(buf.toString('ascii'));        // outputs: abcdefghijklmnopqrstuvwxyz
    console.log(buf.toString('ascii', 0, 5));   // outputs: abcde
    console.log(buf.toString('utf8', 0, 5));    // outputs: abcde
    console.log(buf.toString(undefined, 0, 5)); // encoding defaults to 'utf8', outputs abcde
}


/*
 * Convert Buffer to JSON
 */
{
    var buf = new Buffer('Simply Easy Learning');
    var json = buf.toJSON();
    
    console.log(json);
}


/*
 * Concatenate Buffers
 */
{
    var buf1 = new Buffer('TutorialsPoint ');
    var buf2 = new Buffer('Simply Easy Learning');
    var buf3 = Buffer.concat([buf1, buf2]);

    console.log("buf3 content: " + buf3.toString());
}


/*
 * Compare Buffers
 */
{
    var buf1 = new Buffer('ABC');
    var buf2 = new Buffer('ABCD');
    var result = buf2.compare(buf1);
    
    if (result < 0) {
        console.log(buf1 + " comes before " + buf2);
    } else if (result == 0) {
        console.log(buf1 + " is same as " + buf2);
    } else {
        console.log(buf1 + " comes after " + buf2);
    }
}


/*
 * Copy Buffer
 */
{
    var buf1 = new Buffer('ABC');
    //copy a buffer
    var buf2 = new Buffer(3);
    buf1.copy(buf2);

    console.log("buf2 content: " + buf2.toString());
}


/*
 * Slice Buffer
 */
{
    var buf1 = new Buffer('TutorialsPoint');
    //slicing a buffer
    var buf2 = buf1.slice(0, 9);
    console.log("buf2 content: " + buf2.toString());
}


/*
 * Buffer Length
 */
{
    var buf = new Buffer('TutorialsPoint');
    //length of the buffer
    console.log("buf length: " + buf.length);
}
