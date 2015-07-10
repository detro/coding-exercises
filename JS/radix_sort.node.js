function radix_sort(input) {
    var output,
        i, j, ilen, jlen,
        m = 1,
        n = 0.1,
        buckets = [],
        max = m + 1;

    function reset_buckets(buckets) {
        var i;

        for (i = 0; i <= 9; ++i) {
            buckets[i] = [];
        }
    }

    while (m <= max) {
        // Prep for next iteration
        // move significant digit left by 1
        m *= 10;
        n *= 10;

        // Prep radix buckets
        reset_buckets(buckets);

        // Cluster numbers into buckets, based on the significant digit we care about
        for (i = 0, ilen = input.length; i < ilen; ++i) {
            buckets[ Math.floor( (input[i] % m) / n ) ].push(input[i]);

            console.log(input[i] + " -> " + Math.floor( (input[i] % m) / n ));

            if (input[i] > max) {
                max = input[i];
            }
        }

        console.log("max: " + max);

        // Read numbers from the buckets in order (from 0 to 9)
        output = [];
        for (i = 0; i <= 9; ++i) {
            for (j = 0, jlen = buckets[i].length; j < jlen; ++j) {
                output.push( buckets[i][j] );
            }
        }

        // the output of this iteration is the input of the next iteration
        input = output;
    }

    return output;
}

var input = [], output,
    i;

for (i = 0; i < 100000; ++i) {
    input.push( Math.floor ( Math.random() * 100000 ) );
}

console.log("INPUT ARRAY:");
console.log(JSON.stringify(input));

console.log("OUTPUT ARRAY:");
output = radix_sort(input);
console.log(JSON.stringify(output));
console.log("MIN: " + output[0]);
console.log("MAX: " + output[ output.length -1 ]);
